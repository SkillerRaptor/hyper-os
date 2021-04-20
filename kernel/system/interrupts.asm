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

global interrupt_handler_0
extern c_interrupt_handler_0
interrupt_handler_0:
    pushaq
	call c_interrupt_handler_0
	popaq
	iretq

global interrupt_handler_1
extern c_interrupt_handler_1
interrupt_handler_1:
    pushaq
	call c_interrupt_handler_1
	popaq
	iretq

global interrupt_handler_2
extern c_interrupt_handler_2
interrupt_handler_2:
    pushaq
	call c_interrupt_handler_2
	popaq
	iretq

global interrupt_handler_3
extern c_interrupt_handler_3
interrupt_handler_3:
    pushaq
	call c_interrupt_handler_3
	popaq
	iretq

global interrupt_handler_4
extern c_interrupt_handler_4
interrupt_handler_4:
    pushaq
	call c_interrupt_handler_4
	popaq
	iretq

global interrupt_handler_5
extern c_interrupt_handler_5
interrupt_handler_5:
    pushaq
	call c_interrupt_handler_5
	popaq
	iretq

global interrupt_handler_6
extern c_interrupt_handler_6
interrupt_handler_6:
    pushaq
	call c_interrupt_handler_6
	popaq
	iretq

global interrupt_handler_7
extern c_interrupt_handler_7
interrupt_handler_7:
    pushaq
	call c_interrupt_handler_7
	popaq
	iretq

global interrupt_handler_8
extern c_interrupt_handler_8
interrupt_handler_8:
    pushaq
	call c_interrupt_handler_8
	popaq
	iretq

global interrupt_handler_9
extern c_interrupt_handler_9
interrupt_handler_9:
    pushaq
	call c_interrupt_handler_9
	popaq
	iretq

global interrupt_handler_10
extern c_interrupt_handler_10
interrupt_handler_10:
    pushaq
	call c_interrupt_handler_10
    popaq
	iretq

global interrupt_handler_11
extern c_interrupt_handler_11
interrupt_handler_11:
    pushaq
	call c_interrupt_handler_11
    popaq
	iretq

global interrupt_handler_12
extern c_interrupt_handler_12
interrupt_handler_12:
    pushaq
	call c_interrupt_handler_12
    popaq
	iretq

global interrupt_handler_13
extern c_interrupt_handler_13
interrupt_handler_13:
    pushaq
	call c_interrupt_handler_13
    popaq
	iretq

global interrupt_handler_14
extern c_interrupt_handler_14
interrupt_handler_14:
    pushaq
	call c_interrupt_handler_14
    popaq
	iretq

global interrupt_handler_15
extern c_interrupt_handler_15
interrupt_handler_15:
    pushaq
	call c_interrupt_handler_15
    popaq
	iretq

global exception_handler_0
extern c_exception_handler_0
exception_handler_0:
    pushaq
	call c_exception_handler_0
    popaq
	iretq

global exception_handler_1
extern c_exception_handler_1
exception_handler_1:
    pushaq
	call c_exception_handler_1
	popaq
	iretq

global exception_handler_2
extern c_exception_handler_2
exception_handler_2:
    pushaq
	call c_exception_handler_2
	popaq
	iretq

global exception_handler_3
extern c_exception_handler_3
exception_handler_3:
    pushaq
	call c_exception_handler_3
	popaq
	iretq

global exception_handler_4
extern c_exception_handler_4
exception_handler_4:
    pushaq
	call c_exception_handler_4
	popaq
	iretq

global exception_handler_5
extern c_exception_handler_5
exception_handler_5:
    pushaq
	call c_exception_handler_5
	popaq
	iretq

global exception_handler_6
extern c_exception_handler_6
exception_handler_6:
    pushaq
	call c_exception_handler_6
	popaq
	iretq

global exception_handler_7
extern c_exception_handler_7
exception_handler_7:
    pushaq
	call c_exception_handler_7
	popaq
	iretq

global exception_handler_8
extern c_exception_handler_8
exception_handler_8:
    pushaq
	call c_exception_handler_8
	popaq
	iretq

global exception_handler_10
extern c_exception_handler_10
exception_handler_10:
    pushaq
	call c_exception_handler_10
	popaq
	iretq

global exception_handler_11
extern c_exception_handler_11
exception_handler_11:
    pushaq
	call c_exception_handler_11
	popaq
	iretq

global exception_handler_12
extern c_exception_handler_12
exception_handler_12:
    pushaq
	call c_exception_handler_12
	popaq
	iretq

global exception_handler_13
extern c_exception_handler_13
exception_handler_13:
    pushaq
	call c_exception_handler_13
	popaq
	iretq

global exception_handler_14
extern c_exception_handler_14
exception_handler_14:
    pushaq
	call c_exception_handler_14
	popaq
	iretq

global exception_handler_16
extern c_exception_handler_16
exception_handler_16:
    pushaq
	call c_exception_handler_16
	popaq
	iretq

global exception_handler_17
extern c_exception_handler_17
exception_handler_17:
    pushaq
	call c_exception_handler_17
	popaq
	iretq

global exception_handler_18
extern c_exception_handler_18
exception_handler_18:
    pushaq
	call c_exception_handler_18
	popaq
	iretq

global exception_handler_19
extern c_exception_handler_19
exception_handler_19:
    pushaq
	call c_exception_handler_19
	popaq
	iretq

global exception_handler_20
extern c_exception_handler_20
exception_handler_20:
    pushaq
	call c_exception_handler_20
	popaq
	iretq

global exception_handler_30
extern c_exception_handler_30
exception_handler_30:
    pushaq
	call c_exception_handler_30
	popaq
	iretq
