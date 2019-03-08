;------------------------------------------------------------------------------
;
;	
;
;------------------------------------------------------------------------------

.model tiny

BASE    = (80 * 3 + 10) * 2  	; начальная точка(левый верхний угол рамки)
SEG     = 0b800h		; начало видеосегмента
HEIGHT  = 10			; высота рамки
LENGHT  = 42			; длина рамки
SYMBOL  = ' '
COLOR   = 1eh
COLOR_FRAME = 4eh
NUMBER  = 3802
STR_BASE =  BASE + 2 * lenght / 6 + 2 * 80

.code

public COLOR, SYMBOL, COLOR_FRAME, HEIGHT, LENGHT 
extrn print_rect:near, print_frame:near, print_string:near
extrn digtohex:near, digtobin:near, digtostr:near, strtodig:near, strlen:near

org 100h
start:
	
	mov ah, 00h		; установка видеорежима
	mov al, 03h		;
	int 10h			;
	mov ax, SEG		; установка начала видеопамяти
	mov es, ax		;

        mov bx, BASE            ; установка начальной точки
        mov cx, HEIGHT          ; передаем в сх значение высоты рамки
        call print_rect         ; рисуем прямоугольник (фон)

        mov bx, BASE            ; рисуем рамку
        call print_frame	;
	
        mov bx, STR_BASE	; выводим сообщение
	mov di, offset msg	;
	call print_string	;

	mov bx, STR_BASE + 2 * 80
	mov di, offset msg0     ; аналогично
	call print_string	;

	mov ax, NUMBER
	mov di, offset digit_str
	call digtostr
	
        mov bx,STR_BASE + 2 * 2 * 80
	mov di, offset msgint
	call print_string
	mov di, offset digit_str
	call print_string 


        mov ax, NUMBER 		; кладем в ах число
        mov di, offset digit_hex; кладем в di адрес строки в которой будет хекс
        call digtohex		; переводим его в 16-ричную систему
	
        mov bx, STR_BASE + 3 * 2 * 80
	mov di, offset msg1	; печатаем хекс
	call print_string 	;
        mov di, offset digit_hex;
        call print_string       ;
	
	mov ax, NUMBER		; кладем в ах число
	mov di, offset digit_bin; кладем в di адрес строки в которой будет бин
	call digtobin		; переводим его в 2-ичную систему

        mov bx,STR_BASE + 4 * 2 * 80
	mov di, offset msg2	; печатаем бин
	call print_string	;
	mov di, offset digit_bin;
	call print_string	;
	
	mov bx,STR_BASE + 6 * 2 * 80
	mov di, offset your_str
	call print_string
	mov di, offset int_str
	call print_string
	
	mov di, offset int_str
	mov dl, 16
	call strtodig

	mov ax, bx
	mov di, offset digit_str
	call digtostr
	mov bx,STR_BASE + 7 * 2 * 80 + 16
	mov di, offset digit_str
	call print_string

	
	mov ax, 4c00h
	int 21h

.data

msg0	  db	  '   reg AX:  $'
msg       db      'Молодец, прога работает!!!', 01h, 02h, 03h, ' $'
msg1	  db	  'hex: $'
msg2	  db	  'bin: $'
msgint	  db	  'int: $'
digit_str db	   5 dup(92), '$'
digit_hex db       4 dup(92), '$'
digit_bin db      16 dup(92), '$'

your_str  db	  'your str: $'
int_str   db	  'EDA$'


end start

;-----------------------------------------------------------------------------
;
;
;
;-----------------------------------------------------------------------------

