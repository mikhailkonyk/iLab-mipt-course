;------------------------------------------------------------------------------
;			INTEGER -> STR INTEGER                       
;EXPECT: ax - number, di - pointer to str
;DESTROY: di, cx, dx, bx, ax
;	
;------------------------------------------------------------------------------

.model tiny
.code
public digtostr
	
digtostr proc
	push es
	mov cx, ds
	mov es, cx
	mov cx, 5
	add di, 4
	xor dx, dx
	mov bx, ax
	std

	next:
	
	mov ax, bx
	xor dx, dx 
	div op
	mov bx, ax
	mov al, dl
	add al, '0'
	stosb 
	
	loop next

	pop es	

	ret
digtostr endp

.data

op 	dw 	10

.data

end

;-----------------------------------------------------------------------------
;
;-----------------------------------------------------------------------------

