/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

use limine::{
    LimineFramebufferRequest, LimineFramebufferResponse, LimineTerminalRequest,
    LimineTerminalResponse,
};

static FRAMEBUFFER: LimineFramebufferRequest = LimineFramebufferRequest::new(0);
static TERMINAL: LimineTerminalRequest = LimineTerminalRequest::new(0);

pub struct BootInformation {
    pub framebuffer: &'static LimineFramebufferResponse,
    pub terminal: &'static LimineTerminalResponse,
}

impl BootInformation {
    pub fn load() -> Self {
        Self {
            framebuffer: FRAMEBUFFER.get_response().get().unwrap(),
            terminal: TERMINAL.get_response().get().unwrap(),
        }
    }
}
