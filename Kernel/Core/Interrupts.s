.global IRQCall0
.type IRQCall0, @function

.global IRQCall1
.type IRQCall1, @function

.global IRQCall2
.type IRQCall2, @function

.global IRQCall3
.type IRQCall3, @function

.global IRQCall4
.type IRQCall4, @function

.global IRQCall5
.type IRQCall5, @function

.global IRQCall6
.type IRQCall6, @function

.global IRQCall7
.type IRQCall7, @function

.global IRQCall8
.type IRQCall8, @function

.global IRQCall9
.type IRQCall9, @function

.global IRQCall10
.type IRQCall10, @function

.global IRQCall11
.type IRQCall11, @function

.global IRQCall12
.type IRQCall12, @function

.global IRQCall13
.type IRQCall13, @function

.global IRQCall14
.type IRQCall14, @function

.global IRQCall15
.type IRQCall15, @function

IRQCall0:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $0, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall1:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $1, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall2:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $2, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall3:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $3, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall4:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $4, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall5:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $5, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall6:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $6, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall7:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $7, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall8:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $8, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall9:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $9, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall10:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $10, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall11:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $11, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall12:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $12, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
	
IRQCall13:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $13, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall14:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $14, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq

IRQCall15:
    push %rax
    push %rcx
    push %rdx
    push %rbx
    push %rbp
    push %rsi
    push %rdi
	push %rax
	movq $15, %rax
	call IRQHandler
	pop %rax
    pop %rdi    
    pop %rsi    
    pop %rbp    
    pop %rbx    
    pop %rdx    
    pop %rcx
    pop %rax
	iretq
