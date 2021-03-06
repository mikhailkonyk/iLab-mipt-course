;------------------------------------------------------------------------------
;
;	
;
;------------------------------------------------------------------------------

.model tiny

BASE    = (80 * 3 + 10) * 2  	; ��砫쭠� �窠(���� ���孨� 㣮� ࠬ��)
SEG     = 0b800h		; ��砫� �����ᥣ����
HEIGHT  = 10			; ���� ࠬ��
LENGHT  = 42			; ����� ࠬ��
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
	
	mov ah, 00h		; ��⠭���� �����०���
	mov al, 03h		;
	int 10h			;
	mov ax, SEG		; ��⠭���� ��砫� ����������
	mov es, ax		;

        mov bx, BASE            ; ��⠭���� ��砫쭮� �窨
        mov cx, HEIGHT          ; ��।��� � �� ���祭�� ����� ࠬ��
        call print_rect         ; ��㥬 ��אַ㣮�쭨� (䮭)

        mov bx, BASE            ; ��㥬 ࠬ��
        call print_frame	;
	
        mov bx, STR_BASE	; �뢮��� ᮮ�饭��
	mov di, offset msg	;
	call print_string	;

	mov bx, STR_BASE + 2 * 80
	mov di, offset msg0     ; �������筮
	call print_string	;

	mov ax, NUMBER
	mov di, offset digit_str
	call digtostr
	
        mov bx,STR_BASE + 2 * 2 * 80
	mov di, offset msgint
	call print_string
	mov di, offset digit_str
	call print_string 


        mov ax, NUMBER 		; ������ � �� �᫮
        mov di, offset digit_hex; ������ � di ���� ��ப� � ���ன �㤥� 奪�
        call digtohex		; ��ॢ���� ��� � 16-���� ��⥬�
	
        mov bx, STR_BASE + 3 * 2 * 80
	mov di, offset msg1	; ���⠥� 奪�
	call print_string 	;
        mov di, offset digit_hex;
        call print_string       ;
	
	mov ax, NUMBER		; ������ � �� �᫮
	mov di, offset digit_bin; ������ � di ���� ��ப� � ���ன �㤥� ���
	call digtobin		; ��ॢ���� ��� � 2-���� ��⥬�

        mov bx,STR_BASE + 4 * 2 * 80
	mov di, offset msg2	; ���⠥� ���
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
msg       db      '�������, �ண� ࠡ�⠥�!!!', 01h, 02h, 03h, ' $'
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

