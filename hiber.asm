org 0xc200

mov al, 0x13
mov ah, 0
int 0x10

show_msg:
	MOV     SI, msg
putloop:
	MOV     AL, [SI]
	ADD     SI, 1            ; 给SI加1
	CMP     AL, 0
	JE      fin
	MOV     AH, 0x0e         ; 显示一个文字
	MOV     BX, 15           ; 指定字符颜色
	INT     0x10            ; 调用显卡BIOS
	JMP     putloop

msg:
	DB      0x0a      ; 换行两次
	DB      "new world, so easy"
	DB      0

fin:
	hlt
	jmp fin
