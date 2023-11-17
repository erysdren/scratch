
	cpu	8086
	bits	16
	section	.text

	struc	regs
	r_ax	resw	1
	r_bx	resw	1
	r_cx	resw	1
	r_dx	resw	1
	r_si	resw	1
	r_di	resw	1
	r_flags	resw	1
	endstruc

	struc	segs
	r_es	resw	1
	r_ds	resw	1
	r_fs	resw	1
	r_gs	resw	1
	r_cs	resw	1
	r_ss	resw	1
	endstruc

	a_n	equ	4
	a_in	equ	6
	a_out	equ	8
	a_segs	equ	10

	global	int86x
int86x:
	push	bp
	mov	bp,sp	
	push	es		; [bp-2] - shouldn't be necessary but watcom says it's preserved
	push	si		; [bp-4]
	push	di		; [bp-6]
	pushf			; [bp-8]
	sub	sp,4		; [bp-10] & [bp-12]

	;; patch in interrupt number - would not work in protected mode
	mov	al,[bp+a_n]
	mov	[cs:.intinstr+1],al

	;; get new es & ds onto stack for now
	mov	bx,[bp+a_segs]
	push	ds		; save the old one
	push	word [bx+r_es]
	push	word [bx+r_ds]

	;; load registers from in
	mov	bx,[bp+a_in]
	mov	ax,[bx+r_ax]
	mov	cx,[bx+r_cx]
	mov	dx,[bx+r_dx]
	mov	si,[bx+r_si]
	mov	di,[bx+r_di]
	push	word [bx+r_flags]
	popf
	mov	bx,[bx+r_bx]

	;; load new seg regs from stack
	pop	ds
	pop	es

	;; flush prefetch queue, and call the interrupt
	jmp short	.intinstr
	.intinstr:
	int	00h

	;; assume ds & es scrambled for now, careful, use only ss:
	mov	[bp-10],ax	; preserve ax, bx to stack
	mov	[bp-12],bx
	mov	ax,ds
	pop	ds		; original ds restored, ok to use [bx] again
	
	mov	bx,[bp+a_segs]	; save seg regs
	mov	[bx+r_es],es
	mov	[bx+r_ds],ax
	
	mov	bx,[bp+a_out] 	; save out regs
	pop	word [bx+r_bx]	; restore from stack
	pop	word [bx+r_ax]
	mov	[bx+r_cx],cx	; save from regs
	mov	[bx+r_dx],dx
	mov	[bx+r_si],si
	mov	[bx+r_di],di
	pushf
	pop	word [bx+r_flags]

	popf
	pop	di
	pop	si
	pop	es
	mov	sp,bp
	pop	bp
	ret
