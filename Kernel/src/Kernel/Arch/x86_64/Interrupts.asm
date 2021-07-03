;
; Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
;
; SPDX-License-Identifier: MIT
;

%macro pushaq 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popaq 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

extern idt_handlers

%macro interrupt_handler_a 1
    global interrupt_handler_%1

    interrupt_handler_%1:
        push 0
        push %1
        pushaq
        cld
        mov rdi, rsp
        mov rax, [idt_handlers + %1 * 8]
        call rax
        popaq
        add rsp, 0x10
        iretq
%endmacro

%macro interrupt_handler_b 1
    global interrupt_handler_%1

    interrupt_handler_%1:
        push %1
        pushaq
        cld
        mov rdi, rsp
        mov rax, [idt_handlers + %1 * 8]
        call rax
        popaq
        add rsp, 0x10
        iretq
%endmacro

interrupt_handler_a 0
interrupt_handler_a 1
interrupt_handler_a 2
interrupt_handler_a 3
interrupt_handler_a 4
interrupt_handler_a 5
interrupt_handler_a 6
interrupt_handler_a 7
interrupt_handler_b 8
interrupt_handler_a 9
interrupt_handler_b 10
interrupt_handler_b 11
interrupt_handler_b 12
interrupt_handler_b 13
interrupt_handler_b 14
interrupt_handler_a 15
interrupt_handler_a 16
interrupt_handler_b 17
interrupt_handler_a 18
interrupt_handler_a 19
interrupt_handler_a 20
interrupt_handler_a 21
interrupt_handler_a 22
interrupt_handler_a 23
interrupt_handler_a 24
interrupt_handler_a 25
interrupt_handler_a 26
interrupt_handler_a 27
interrupt_handler_a 28
interrupt_handler_a 29
interrupt_handler_b 30
interrupt_handler_a 31
interrupt_handler_a 32
interrupt_handler_a 33
interrupt_handler_a 34
interrupt_handler_a 35
interrupt_handler_a 36
interrupt_handler_a 37
interrupt_handler_a 38
interrupt_handler_a 39
interrupt_handler_a 40
interrupt_handler_a 41
interrupt_handler_a 42
interrupt_handler_a 43
interrupt_handler_a 44
interrupt_handler_a 45
interrupt_handler_a 46
interrupt_handler_a 47
interrupt_handler_a 48
interrupt_handler_a 49
interrupt_handler_a 50
interrupt_handler_a 51
interrupt_handler_a 52
interrupt_handler_a 53
interrupt_handler_a 54
interrupt_handler_a 55
interrupt_handler_a 56
interrupt_handler_a 57
interrupt_handler_a 58
interrupt_handler_a 59
interrupt_handler_a 60
interrupt_handler_a 61
interrupt_handler_a 62
interrupt_handler_a 63
interrupt_handler_a 64
interrupt_handler_a 65
interrupt_handler_a 66
interrupt_handler_a 67
interrupt_handler_a 68
interrupt_handler_a 69
interrupt_handler_a 70
interrupt_handler_a 71
interrupt_handler_a 72
interrupt_handler_a 73
interrupt_handler_a 74
interrupt_handler_a 75
interrupt_handler_a 76
interrupt_handler_a 77
interrupt_handler_a 78
interrupt_handler_a 79
interrupt_handler_a 80
interrupt_handler_a 81
interrupt_handler_a 82
interrupt_handler_a 83
interrupt_handler_a 84
interrupt_handler_a 85
interrupt_handler_a 86
interrupt_handler_a 87
interrupt_handler_a 88
interrupt_handler_a 89
interrupt_handler_a 90
interrupt_handler_a 91
interrupt_handler_a 92
interrupt_handler_a 93
interrupt_handler_a 94
interrupt_handler_a 95
interrupt_handler_a 96
interrupt_handler_a 97
interrupt_handler_a 98
interrupt_handler_a 99
interrupt_handler_a 100
interrupt_handler_a 101
interrupt_handler_a 102
interrupt_handler_a 103
interrupt_handler_a 104
interrupt_handler_a 105
interrupt_handler_a 106
interrupt_handler_a 107
interrupt_handler_a 108
interrupt_handler_a 109
interrupt_handler_a 110
interrupt_handler_a 111
interrupt_handler_a 112
interrupt_handler_a 113
interrupt_handler_a 114
interrupt_handler_a 115
interrupt_handler_a 116
interrupt_handler_a 117
interrupt_handler_a 118
interrupt_handler_a 119
interrupt_handler_a 120
interrupt_handler_a 121
interrupt_handler_a 122
interrupt_handler_a 123
interrupt_handler_a 124
interrupt_handler_a 125
interrupt_handler_a 126
interrupt_handler_a 127
interrupt_handler_a 128
interrupt_handler_a 129
interrupt_handler_a 130
interrupt_handler_a 131
interrupt_handler_a 132
interrupt_handler_a 133
interrupt_handler_a 134
interrupt_handler_a 135
interrupt_handler_a 136
interrupt_handler_a 137
interrupt_handler_a 138
interrupt_handler_a 139
interrupt_handler_a 140
interrupt_handler_a 141
interrupt_handler_a 142
interrupt_handler_a 143
interrupt_handler_a 144
interrupt_handler_a 145
interrupt_handler_a 146
interrupt_handler_a 147
interrupt_handler_a 148
interrupt_handler_a 149
interrupt_handler_a 150
interrupt_handler_a 151
interrupt_handler_a 152
interrupt_handler_a 153
interrupt_handler_a 154
interrupt_handler_a 155
interrupt_handler_a 156
interrupt_handler_a 157
interrupt_handler_a 158
interrupt_handler_a 159
interrupt_handler_a 160
interrupt_handler_a 161
interrupt_handler_a 162
interrupt_handler_a 163
interrupt_handler_a 164
interrupt_handler_a 165
interrupt_handler_a 166
interrupt_handler_a 167
interrupt_handler_a 168
interrupt_handler_a 169
interrupt_handler_a 170
interrupt_handler_a 171
interrupt_handler_a 172
interrupt_handler_a 173
interrupt_handler_a 174
interrupt_handler_a 175
interrupt_handler_a 176
interrupt_handler_a 177
interrupt_handler_a 178
interrupt_handler_a 179
interrupt_handler_a 180
interrupt_handler_a 181
interrupt_handler_a 182
interrupt_handler_a 183
interrupt_handler_a 184
interrupt_handler_a 185
interrupt_handler_a 186
interrupt_handler_a 187
interrupt_handler_a 188
interrupt_handler_a 189
interrupt_handler_a 190
interrupt_handler_a 191
interrupt_handler_a 192
interrupt_handler_a 193
interrupt_handler_a 194
interrupt_handler_a 195
interrupt_handler_a 196
interrupt_handler_a 197
interrupt_handler_a 198
interrupt_handler_a 199
interrupt_handler_a 200
interrupt_handler_a 201
interrupt_handler_a 202
interrupt_handler_a 203
interrupt_handler_a 204
interrupt_handler_a 205
interrupt_handler_a 206
interrupt_handler_a 207
interrupt_handler_a 208
interrupt_handler_a 209
interrupt_handler_a 210
interrupt_handler_a 211
interrupt_handler_a 212
interrupt_handler_a 213
interrupt_handler_a 214
interrupt_handler_a 215
interrupt_handler_a 216
interrupt_handler_a 217
interrupt_handler_a 218
interrupt_handler_a 219
interrupt_handler_a 220
interrupt_handler_a 221
interrupt_handler_a 222
interrupt_handler_a 223
interrupt_handler_a 224
interrupt_handler_a 225
interrupt_handler_a 226
interrupt_handler_a 227
interrupt_handler_a 228
interrupt_handler_a 229
interrupt_handler_a 230
interrupt_handler_a 231
interrupt_handler_a 232
interrupt_handler_a 233
interrupt_handler_a 234
interrupt_handler_a 235
interrupt_handler_a 236
interrupt_handler_a 237
interrupt_handler_a 238
interrupt_handler_a 239
interrupt_handler_a 240
interrupt_handler_a 241
interrupt_handler_a 242
interrupt_handler_a 243
interrupt_handler_a 244
interrupt_handler_a 245
interrupt_handler_a 246
interrupt_handler_a 247
interrupt_handler_a 248
interrupt_handler_a 249
interrupt_handler_a 250
interrupt_handler_a 251
interrupt_handler_a 252
interrupt_handler_a 253
interrupt_handler_a 254
interrupt_handler_a 255
