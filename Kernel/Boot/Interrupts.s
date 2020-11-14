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
	pusha
	push %eax
	movl $0, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall1:
	pusha
	push %eax
	movl $1, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall2:
	pusha
	push %eax
	movl $2, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall3:
	pusha
	push %eax
	movl $3, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall4:
	pusha
	push %eax
	movl $4, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall5:
	pusha
	push %eax
	movl $5, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall6:
	pusha
	push %eax
	movl $6, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall7:
	pusha
	push %eax
	movl $7, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall8:
	pusha
	push %eax
	movl $8, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall9:
	pusha
	push %eax
	movl $1, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall10:
	pusha
	push %eax
	movl $10, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall11:
	pusha
	push %eax
	movl $11, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall12:
	pusha
	push %eax
	movl $12, %eax
	call IRQHandler
	pop %eax
	popa
	iret
	
IRQCall13:
	pusha
	push %eax
	movl $13, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall14:
	pusha
	push %eax
	movl $14, %eax
	call IRQHandler
	pop %eax
	popa
	iret

IRQCall15:
	pusha
	push %eax
	movl $15, %eax
	call IRQHandler
	pop %eax
	popa
	iret
