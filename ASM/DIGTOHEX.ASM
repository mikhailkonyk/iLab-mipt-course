;------------------------------------------------------------------------------
;				INTEGER -> HEX
;------------------------------------------------------------------------------
;Expect ax - number, di - pointer to str    
;Destroy cx, di, si, ax, dx	
;------------------------------------------------------------------------------

.model tiny
.code

public digtohex

digtohex proc
	push es
	mov cx, 4
	add di, 3
	mov dx, ax
	mov ax, ds
	mov es, ax
	std
	next:
		mov ax, dx
                and ax, 000fh
		mov si, ax
                mov al, character[si]
		stosb 	
		shr dx, 4
	loop next
	pop es
        ret                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
digtohex endp

.data

character db '0123456789ABCDEF'

end 
	
;-----------------------------------------------------------------------------
;
;
;-----------------------------------------------------------------------------
