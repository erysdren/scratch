; interrupt entry routines
	cpu 8086
	bits 16
	section .text

	; int86 implementation
	global int86
int86:
	push bp
	mov bp, sp
	push bx
	push si
	push di
	pushf

	mov ax, [bp + 4]
	mov [cs:.intop + 1], al	; modify int instruction

	mov [saved_sp], sp
	mov sp, [bp + 6]
	pop ax
	pop bx
	pop cx
	pop dx
	pop si
	pop di
	popf
	mov sp, [saved_sp]

.intop:	int 0xff

	mov [saved_ax], ax
	pushf
	pop ax
	mov sp, [bp + 8]
	add sp, 14	; sp at end of outregs
	push ax		; flags
	mov ax, [saved_ax]
	push di
	push si
	push dx
	push cx
	push bx
	push ax

	mov sp, [saved_sp]
	popf
	pop di
	pop si
	pop bx
	pop bp
	ret

saved_sp dw 0
saved_ax dw 0

; vi:ts=8 sts=8 sw=8 ft=nasm:
