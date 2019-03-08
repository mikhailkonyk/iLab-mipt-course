;------------------------------------------------------------------------------
;				STR -> INT
;------------------------------------------------------------------------------
;EXPECT: di - pointer to str, dl - base of number system
;DESTROY: ax, si
;RETURN: bx - number
;------------------------------------------------------------------------------
.model tiny
.code
extrn strlen:near
public strtodig

strtodig proc
	push es
	mov ax, ds
	mov es, ax
	call strlen
	mov si, di    		   
       	add si, cx     		  
	dec si
	mov endptr, si
	xor bx, bx
 	xor ax, ax

	std
	go:
		xor ax, ax
		push di		  
		lodsb      	  ; put symbol to al !!! lodsb use DS SI !!!
				  ;		     !!! scasb use ES DI !!!			  
		mov di, offset character
		add di, 15
		mov cx, 15	  ;
		repne scasb 	  ; find address of symbol, in di we have
				  ; pointer to symbol in 'character'
		xor ah, ah        
		sub di, offset character
		inc di	   
		mov ax, di	  ; put calculated number to ax
				
		pop di		  
		mov cx, endptr
		dec cx	  
		sub cx, si  	  ; now cx is index from the end
		
		cmp cx, 0
		je next
				
			multiply:
			mul dl
			loop multiply
	  	
		next:
		add bx, ax		
			
		cmp si, di
		jb return	
	jmp go
	
return:	pop es
	ret
strtodig endp
	
.data
endptr      dw 0
character   db '0123456789ABCDEF'

end

;-----------------------------------------------------------------------------
;
;
;-----------------------------------------------------------------------------

