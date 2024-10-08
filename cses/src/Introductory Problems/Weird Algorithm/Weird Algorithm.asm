section .data
	IN_BUFF_SIZE equ 1000
	in_buff_pos: dq 0
	in_buff_end: dq 0

	OUT_BUFF_SIZE equ 1000
	out_buff_pos: dq 0

section .bss
	in_buff: resb IN_BUFF_SIZE
	out_buff: resb OUT_BUFF_SIZE

section .text
global _start

_start:
	call _read_int64

	push rbx
	mov rbx, rax

_start__1:
	mov rdi, rbx
	call _write_int64
	mov rdi, ' '
	call _write_char

	cmp rbx, 1
	je _start__4

	mov rdx, rbx
	and rdx, 1

	cmp rdx, 1
	je _start__2

	shr rbx, 1
	jmp _start__3

_start__2:
	mov rax, rbx
	shl rax, 1
	add rbx, rax
	inc rbx

_start__3:
	jmp _start__1

_start__4:
	mov rdi, 0xA
	call _write_char

	mov rdi, 0x0
	jmp _exit

; ----------------------------------------

; RAX -> 64 bit integer
_read_int64:
	; Ignore garbage chars
	call _read_char

	cmp al, '0'
	jl _read_int64
	cmp al, '9'
	jg _read_int64

	push rbx
	mov rbx, 0

_read_int64__1:
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
	jl _read_int64__2
	cmp al, '9'
	jg _read_int64__2

	jmp _read_int64__1

_read_int64__2:
	mov rax, 0
	mov rax, rbx
	pop rbx
	ret

; ----------------------------------------

; RDI <- 64 bit integer
_write_int64:
	cmp rdi, 0
	jne _write_int64__1

	mov rdi, '0'

	call _write_char
	ret

_write_int64__1:
	push rbx
	mov rbx, 0

	mov rcx, 10
	mov rax, rdi

_write_int64__2:
	mov rdx, 0
	div rcx

	sub rsp, 1
	add rdx, '0'
	inc rbx
	mov [rsp], dl

	cmp rax, 0
	jne _write_int64__2

_write_int64__3:
	mov al, [rsp]
	mov rdi, rax
	call _write_char
	dec rbx
	inc rsp

	cmp rbx, 0
	jg _write_int64__3
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
