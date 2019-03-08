;------------------------------------------------------------------------------
; 		RECT + FRAME
;------------------------------------------------------------------------------

.model tiny
.code

public print_rect, print_frame
extrn COLOR:abs, LENGHT:abs, SYMBOL:abs, COLOR_FRAME:abs, HEIGHT:abs

;------------------------------------------------------------------------------
;Рисование вертикальной линии
;EXPECT:   bx - start point
;DESTROY:  cx
;------------------------------------------------------------------------------
vert_line proc
	xor cx, cx
vert_line_loop:
	mov byte ptr es:[bx], SYMBOL
	mov byte ptr es:[bx + 1], COLOR_FRAME
	add bx, 80 * 2
	inc cx
	cmp cx, HEIGHT
jbe vert_line_loop
          ret
vert_line endp


;-----------------------------------------------------------------------------
;Рисование горизонтальной линии
;EXPECT:  bx - start point
;DESTROY: сх
;-----------------------------------------------------------------------------
horiz_line proc
	xor cx, cx
horiz_line_loop:
	mov byte ptr es:[bx], SYMBOL
	mov byte ptr es:[bx + 1], COLOR_FRAME
	add bx, 1 * 2
	inc cx
	cmp cx, LENGHT
jbe horiz_line_loop
	   ret
horiz_line endp


;-----------------------------------------------------------------------------
;Рисование рамки
;Expected bx - start point
;Destroyed dx, cx
;------------------------------------------------------------------------------
print_frame proc
        mov dx, bx
	call vert_line
	call horiz_line
        mov bx, dx
	call horiz_line	
	sub bx, 1 * 2
	call vert_line
            ret
print_frame endp


;-----------------------------------------------------------------------------
;Рисование прямоугольника             
;ОЖИДАЕТ        cx - HEIGHT, bx - BASE               
;ИЗМЕНЯЕТ       ax 
;
;------------------------------------------------------------------------------  
print_rect proc
	inc cx
again:
	mov ax, 1
	print_line:
		add bx, 2
		mov byte ptr es:[bx], SYMBOL
		mov byte ptr es:[bx + 1], COLOR
		add ax, 1 		
	cmp ax, LENGHT
	jbe print_line

	sub bx, LENGHT
	sub bx, LENGHT
	add bx, 80 * 2	
loop again
	   ret
print_rect endp

end

;------------------------------------------------------------------------------
;
;
;-------------------------------------------------------------------------------