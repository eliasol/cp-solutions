section .data
	IN_BUFF_SIZE equ 10000
	in_buff_pos: dq 0
	in_buff_end: dq 0

	OUT_BUFF_SIZE equ 10000
	out_buff_pos: dq 0

section .bss
	in_buff: resb IN_BUFF_SIZE
	out_buff: resb OUT_BUFF_SIZE

	N: resq 1
	V: resq 1000001

section .text
global _start

_start:
	call _read_uint64
	mov [N], rax

	push rbx
	mov rbx, 0

_start__1:
	call _read_uint64
	mov r10, rax

	mov rcx, 1

_start__2:
	mov rdx, 0
	mov rax, r10
	div rcx

	cmp rdx, 0
	jne _start__3

	inc qword [V + rcx * 8]

	cmp rax, rcx
	je _start__3

	inc qword [V + rax * 8]

_start__3:
	inc rcx

	mov rax, rcx
	mul rax

	cmp rax, r10
	jle _start__2

	inc rbx
	cmp rbx, [N]
	jl _start__1

	mov rcx, 1000000

_start__4:
	cmp qword [V + rcx * 8], 1
	jg _start__5
	loop _start__4

_start__5:
	mov rdi, rcx
	call _write_uint64

	pop rbx

	mov rdi, 0x0
	jmp _exit

; ----------------------------------------

; RDI <- Number of elements (64 bit unsigned integer)
; RSI <- Size of single element (64 bit unsigned integer)
; RAX -> Address of allocation
_malloc:
	; compute actual size of allocation
	mov rax, rdi
	mul rsi

	add rax, 8
	push rax

	mov rsi, rax
	mov rax, 9
	xor rdi, rdi
	mov rdx, 0x3
	mov r10, 0x22
	mov r8, -1
	xor r9, r9
	syscall

	pop rsi
	mov [rax], rsi

	add rax, 8

	ret

; ----------------------------------------

; RDI <- Address of memory to free
_free:
	mov rax, 11
	mov rsi, [rdi]
	syscall

	ret

; ----------------------------------------

; RAX -> 64 bit unsigned integer
_read_uint64:
	; Ignore garbage chars
	call _read_char

	cmp al, '0'
	jl _read_uint64
	cmp al, '9'
	jg _read_uint64

	push rbx
	mov rbx, 0

_read_uint64__1:
	mov rdx, rbx
	shl rdx, 3
	mov rcx, rbx
	shl rcx, 1
	mov rbx, rdx
	add rbx, rcx

	mov rdx, 0
	mov dl, al
	sub dl, '0'
	add rbx, rdx

	call _read_char
	cmp al, '0'
	jl _read_uint64__2
	cmp al, '9'
	jg _read_uint64__2

	jmp _read_uint64__1

_read_uint64__2:
	mov rax, 0
	mov rax, rbx
	pop rbx
	ret

; ----------------------------------------

; RDI <- 64 bit unsigned integer
_write_uint64:
	cmp rdi, 0
	jne _write_uint64__1

	mov rdi, '0'

	call _write_char
	ret

_write_uint64__1:
	push rbx
	mov rbx, 0

	mov rcx, 10
	mov rax, rdi

_write_uint64__2:
	mov rdx, 0
	div rcx

	sub rsp, 1
	add rdx, '0'
	inc rbx
	mov [rsp], dl

	cmp rax, 0
	jne _write_uint64__2

_write_uint64__3:
	mov al, [rsp]
	mov rdi, rax
	call _write_char
	dec rbx
	inc rsp

	cmp rbx, 0
	jg _write_uint64__3
	pop rbx
	ret

; ----------------------------------------

; RAX -> 8 bit char
_read_char:
	; Check if we are at the end of buffer
	cmp qword [in_buff_pos], IN_BUFF_SIZE
	jne _read_char__1

	mov qword [in_buff_pos], 0
	mov qword [in_buff_end], 0

_read_char__1:
	; Check if buffer needs to be refilled
	mov rax, [in_buff_pos]
	cmp rax, [in_buff_end]
	jne _read_char__2

	call _fill_in_buff

_read_char__2:
	mov rsi, [in_buff_pos]
	mov rax, 0
	mov al, [in_buff + rsi]
	inc qword [in_buff_pos]
	ret

; -----------------------------------------

; RDI <- 8 bit char
_write_char:
	cmp qword [out_buff_pos], OUT_BUFF_SIZE
	jne _write_char__1

	push rdi
	call _flush_out_buff
	pop rdi

_write_char__1:
	mov rsi, [out_buff_pos]
	mov rax, rdi
	mov [out_buff + rsi], al
	inc qword [out_buff_pos]
	ret

; -----------------------------------------

_fill_in_buff:
	mov rax, 0x0
	mov rdi, 0x0
	lea rsi, [in_buff]
	add rsi, [in_buff_end]
	mov rdx, IN_BUFF_SIZE
	sub rdx, [in_buff_end]
	syscall

	add [in_buff_end], rax
	ret

; -----------------------------------------

_flush_out_buff:
	mov rax, 0x1
	mov rdi, 0x1
	lea rsi, [out_buff]
	mov rdx, [out_buff_pos]
	syscall

	mov qword [out_buff_pos], 0
	ret

; -----------------------------------------

; RDI <- exit code
; does not return
_exit:
	push rdi
	call _flush_out_buff
	pop rdi

	mov rax, 0x3C
	syscall
