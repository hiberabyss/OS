; org 0xc200

extern choose ; int choose(int a, int b)

global _start
global myprint

_start:
	; call choose

; void myprint(char *msg)
myprint:
		MOV     SI, msg
	putloop:
		MOV     AL, [SI]
		ADD     SI, 1            ; 给SI加1
		CMP     AL, 0
		JE      fin
		MOV     AH,0x0e         ; 显示一个文字
		MOV     BX,15           ; 指定字符颜色
		INT     0x10            ; 调用显卡BIOS
		JMP     putloop

msg:
	DB      0x0a, 0x0a      ; 换行两次
	DB      "hello, test"
	DB      0

fin:
	HLT                     ; 让CPU停止，等待指令
	JMP     fin             ; 无限循环
