;-----------------------------------------------------------------------------
;   Функция печати строки, оканчивающейся на '$', начиная с заданной точки.			
;------------------------------------------------------------------------------			
;EXPECT bx - point, di - address of string		
;DESTROY bx, al, di
;------------------------------------------------------------------------------
.model tiny
.code

extrn COLOR:abs
public print_string, strlen

print_string proc
	xor cx, cx
	next:
		mov al, byte ptr [di]
		cmp al, '$'
		je return
		mov byte ptr es:[bx], al
		mov byte ptr es:[bx + 1], COLOR
		add bx, 1 * 2
		inc di
	jmp next
return:      ret
print_string endp


;-------------------------------------------------------------------------------
;				STRLEN
;-------------------------------------------------------------------------------
;EXPECT: di - address of string
;DESTROY: si, ax
;RETURN: cx - lenght of string
;------------------------------------------------------------------------------

strlen proc
	push es
	push di

	mov ax, ds
	mov es, ax

	mov si, di
	xor cx, cx
	dec cx
	mov al, '$'
	cld
	repne scasb
	sub di, si
	mov cx, di
	dec cx

	pop di
	pop es
	ret
strlen	endp
end

;-----------------------------------------------------------------------------
;
;
;
;-----------------------------------------------------------------------------

