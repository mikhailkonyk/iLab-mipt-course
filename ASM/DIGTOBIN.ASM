;------------------------------------------------------------------------------
;				 INTEGER -> BIN
;------------------------------------------------------------------------------
;EXPECT: ax - number, di - pointer to str
;DESTROY: ax dx cx di	
;------------------------------------------------------------------------------

.model tiny
.code
public digtobin

digtobin proc
	push es
	mov dx, ax
	add di, 15
	mov ax, ds
	mov es, ax
	mov cx, 16
	std
	next:
		mov ax, dx
		and al, 1
		add al, '0'	
		stosb	
		shr dx, 1
	loop next
	pop es
	ret
digtobin endp 

end 
;-----------------------------------------------------------------------------
;
;
;-----------------------------------------------------------------------------