/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use std::{
    error::Error,
    ffi::OsString,
    fs::{self, DirEntry},
    path::Path,
};

fn visit_directory(directory: &Path, callback: &mut dyn FnMut(&DirEntry)) -> std::io::Result<()> {
    if !directory.is_dir() {
        return Ok(());
    }

    for entry in fs::read_dir(directory)? {
        let entry = entry?;
        let path = entry.path();

        if path.is_dir() {
            visit_directory(&path, callback)?;
            continue;
        }

        callback(&entry);
    }

    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut inc_files = vec![];

    visit_directory(Path::new("src"), &mut |entry| {
        let path = entry.path();

        match path.extension() {
            Some(extension) if extension.eq(&OsString::from("inc")) => {
                let path = path.to_str().expect("Invalid UTF-8 for file path");
                inc_files.push(path.to_string())
            }
            _ => (),
        }
    })?;

    inc_files = inc_files
        .iter()
        .map(|e| {
            let e = e.split("/").collect::<Vec<_>>();
            e[..e.len() - 1].join("/").to_string()
        })
        .collect::<Vec<_>>();

    visit_directory(Path::new("src"), &mut |entry: &DirEntry| {
        let path = entry.path();

        let object_os = path.file_name().expect("Failed to get file name");
        let object_file = object_os.to_str().expect("Invalid UTF-8 for file name");

        match path.extension() {
            Some(extension) if extension.eq(&OsString::from("asm")) => {
                let mut build = nasm_rs::Build::new();

                build
                    .file(&path)
                    .flag("-felf64")
                    .target("x86_64-unknown-none");

                println!("{:?}", inc_files);

                for include in &inc_files {
                    build.include(include);
                }

                build
                    .compile(object_file)
                    .expect("Failed to compile assembly");

                println!("cargo:rustc-link-lib=static={}", object_file);
            }

            _ => (),
        }
    })?;

    println!("cargo:rerun-if-changed=.cargo/kernel.ld");

    Ok(())
}
