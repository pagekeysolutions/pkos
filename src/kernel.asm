bits 32
section .multiboot
	dd 0x1BADB002	; Magic number
	dd 0x0			; Flags
	dd - (0x1BADB002 + 0x0)	; Checksum

section .text

global start
global print_char_with_asm

extern main			; Defined in kernel.c

print_char_with_asm:
	; OFFSET = (ROW * 80) + COL
	mov eax, [esp + 8] 		; eax = row
	mov edx, 80						; 80 (number of cols per row)
	mul edx								; now eax = row * 80
	add eax, [esp + 12] 	; now eax = row * 80 + col
	mov edx, 2						; * 2 because 2 bytes per char on screen
	mul edx
	mov edx, 0xb8000			; vid mem start in edx
	add edx, eax					; Add our calculated offset
	mov eax, [esp + 4] 		; char c
	mov [edx], al
	ret

start:
	cli				; Disable interrupts
	mov esp, stack_space
	call main
	hlt

section .bss
resb 8192			; 8KB for stack
stack_space:
