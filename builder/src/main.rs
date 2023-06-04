/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

mod logger;

use clap::Parser;
use color_eyre::{eyre::bail, Result};
use std::{env, fs, path::Path, process::Command};

#[derive(Debug, Parser)]
#[command(author, version)]
struct Args {
    /// Compile kernel in debug mode
    #[arg(short, long, default_value_t = false)]
    debug: bool,
}

fn main() -> Result<()> {
    color_eyre::install()?;

    let args = Args::parse();
    logger::init(3)?;

    let workspace_dir = env!("CARGO_MANIFEST_DIR");
    build_limine(workspace_dir)?;

    let debug = args.debug;
    build_kernel(workspace_dir, debug)?;
    build_iso(workspace_dir, debug)?;

    run_qemu(workspace_dir)?;

    Ok(())
}

fn build_limine(workspace_dir: &str) -> Result<()> {
    env::set_current_dir(format!("{}/third_party", workspace_dir))?;

    log::info!("Compiling Limine...");

    if !Path::new("./limine").exists() {
        bail!("failed to find limine submodule");
    }

    let success = Command::new("make")
        .args(["-C", "./limine"])
        .status()?
        .success();

    if !success {
        bail!("failed to compile limine");
    }

    log::info!("Compiled Limine");

    Ok(())
}

fn build_kernel(workspace_dir: &str, debug: bool) -> Result<()> {
    env::set_current_dir(format!("{}/kernel", workspace_dir))?;

    log::info!("Compiling Kernel...");

    let success = if debug {
        Command::new("cargo")
            .arg("build")
            .args(["-Z", "unstable-options"])
            .args(["--target", "./.cargo/x86_64-hyper_os.json"])
            .status()?
            .success()
    } else {
        Command::new("cargo")
            .arg("build")
            .args(["-Z", "unstable-options"])
            .args(["--target", "./.cargo/x86_64-hyper_os.json"])
            .arg("--release")
            .status()?
            .success()
    };

    if !success {
        bail!("failed to compile the kernel");
    }

    log::info!("Compiled Kernel");

    Ok(())
}

fn build_iso(workspace_dir: &str, debug: bool) -> Result<()> {
    env::set_current_dir(format!("{}/target", workspace_dir))?;

    log::info!("Linking Kernel ISO...");

    let iso_root_path = Path::new("./iso_root/");
    if iso_root_path.exists() {
        fs::remove_dir_all(iso_root_path)?;
    }

    fs::create_dir(iso_root_path)?;

    if debug {
        fs::copy(
            "../kernel/target/x86_64-hyper_os/debug/kernel",
            "./iso_root/kernel.elf",
        )?;
    } else {
        fs::copy(
            "../kernel/target/x86_64-hyper_os/release/kernel",
            "./iso_root/kernel.elf",
        )?;
    }

    fs::copy("../kernel/boot/limine.cfg", "./iso_root/limine.cfg")?;
    fs::copy("../third_party/limine/limine.sys", "./iso_root/limine.sys")?;
    fs::copy(
        "../third_party/limine/limine-cd.bin",
        "./iso_root/limine-cd.bin",
    )?;
    fs::copy(
        "../third_party/limine/limine-cd-efi.bin",
        "./iso_root/limine-cd-efi.bin",
    )?;

    let success = Command::new("xorriso")
        .args(["-as", "mkisofs"])
        .args(["-b", "limine-cd.bin"])
        .arg("-no-emul-boot")
        .args(["-boot-load-size", "4"])
        .arg("-boot-info-table")
        .args(["--efi-boot", "limine-cd-efi.bin"])
        .arg("-efi-boot-part")
        .arg("--efi-boot-image")
        .arg("--protective-msdos-label")
        .arg("./iso_root/")
        .args(["-o", "hyper-os.iso"])
        .status()?
        .success();

    if !success {
        bail!("failed to link iso");
    }

    let success = Command::new("../third_party/limine/limine-deploy")
        .arg("hyper-os.iso")
        .status()?
        .success();

    if !success {
        bail!("failed to deploy iso");
    }

    fs::remove_dir_all(iso_root_path)?;

    log::info!("Linked Kernel ISO");

    Ok(())
}

fn run_qemu(workspace_dir: &str) -> Result<()> {
    env::set_current_dir(format!("{}/target", workspace_dir))?;

    log::info!("Running QEMU");

    let success = Command::new("qemu-system-x86_64")
        .args(["-cdrom", "./hyper-os.iso"])
        .args(["-vga", "std"])
        .args(["-monitor", "stdio"])
        .args(["-m", "512"])
        .args(["-smp", "1"])
        .args(["-d", "int,cpu_reset"])
        .arg("-no-shutdown")
        .arg("-no-reboot")
        .status()?
        .success();

    if !success {
        bail!("failed to run qemu");
    }

    Ok(())
}
