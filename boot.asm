CYLS equ 10
SECTIONS equ 18

ORG     0x7c00          ; 指明程序装载地址

; fat format
	JMP short entry
	NOP

	DB		'HARIBOTE'		; 启动扇区名称（8字节）
	DW		512				; 每个扇区（sector）大小（必须512字节）
	DB		1				; 簇（cluster）大小（必须为1个扇区）
	DW		1				; FAT起始位置（一般为第一个扇区）
	DB		2				; FAT个数（必须为2）
	DW		224				; 根目录大小（一般为224项）
	DW		2880			; 该磁盘大小（必须为2880扇区1440*1024/512）
	DB		0xf0			; 磁盘类型（必须为0xf0）
	DW		9				; FAT的长度（必??9扇区）
	DW		18				; 一个磁道（track）有几个扇区（必须为18）
	DW		2				; 磁头数（必??2）
	DD		0				; 不使用分区，必须是0
	DD		0			; 重写一次磁盘大小
	DB		0,0,0x29		; 意义不明（固定）
	DD		0x0				; （可能是）卷标号码
	DB		"HARIBOTEOS "	; 磁盘的名称（必须为11字?，不足填空格）
	DB		"FAT12   "		; 磁盘格式名称（必??8字?，不足填空格）

entry:
	MOV     AX, 0            ; 初始化寄存器
	MOV     SS, AX
	MOV     SP, 0x7c00
	MOV     DS, AX
	MOV     ES, AX

load_fd:
	mov ax, 0x820
	mov es, ax 
	mov ch, 0
	mov dh, 0
	mov cl, 2

read_loop
	mov si, 0

retry:
	mov bx, 0
	mov ah, 0x02
	mov al, 1
	mov dl, 0 ; dl is driver index
	int 0x13
	jnc next

	add si, 1
	cmp si, 5
	jae fin

	mov ah, 0x00
	mov dl, 0x00
	int 0x13
	jmp retry

next:
	mov ax, es
	add ax, 0x020
	mov es, ax
	add cl, 1
	cmp cl, SECTIONS
	jbe read_loop

	mov cl, 1
	add dh, 1
	cmp dh, 2
	jb read_loop

	mov dh, 0
	add ch, 1
	cmp ch, CYLS
	jb read_loop

jmp 0xc200

show_msg:
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

fin:
	HLT                     ; 让CPU停止，等待指令
	JMP     fin             ; 无限循环

msg:
	DB      0x0a, 0x0a      ; 换行两次
	DB      "hello, myos"
	DB      0

	times 510 - ($ - $$) db 0

	DB      0x55, 0xaa
