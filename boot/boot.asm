CYLS equ 10
SECTIONS equ 18
MAX_RETRY equ 5
LOADER_ADDR_SEG equ 0x7e0
FAT12_ROOT_MEM_SEG equ 0x800
FAT12_ROOT_TABLE_SIZE equ 9

FAT12_ROOT_SIZE equ 14
FAT12_ROOT_MEM_ADDR_START equ (FAT12_ROOT_MEM_SEG * 16)
FAT12_ROOT_MEM_ADDR_END equ (FAT12_ROOT_MEM_SEG * 16 + FAT12_ROOT_SIZE * 512)

FAT12_MAP_START_SECT equ 1

FAT12_ROOT_FIRST_SECT_NUM equ 19
FAT12_NAME_SIZE equ 11

FAT12_PER_DIR_META_SIZE equ 32

ORG     0x7c00          ; 指明程序装载地址

JMP short entry
NOP
%include "fat12_meta.inc"

entry: ; 0x7c3e
	MOV     AX, 0            ; 初始化寄存器
	MOV     SS, AX
	MOV     SP, 0x7c00
	MOV     DS, AX
	MOV     ES, AX

mov ax, FAT12_ROOT_MEM_SEG
mov es, ax
mov bx, 0
mov ax, FAT12_ROOT_FIRST_SECT_NUM
mov si, 14
call read_sects ; 0x7ca6

call find_loader_sect ; 0x7c6f
mov bx, 0
mov es, bx
mov bx, LOADER_ADDR_SEG
mov si, 1 ; 0x7c66
call read_sects

jmp LOADER_ADDR_SEG

find_loader_sect:
	; ax is the output
	mov bx, FAT12_ROOT_MEM_ADDR_START
next_file_item:
	call is_loader
	cmp al, 1
	je get_sector_num
	add bx, FAT12_PER_DIR_META_SIZE
	cmp bx, FAT12_ROOT_MEM_ADDR_END
	je fin
	jmp next_file_item

get_sector_num:
	mov ax, [bx + 0x1a]
	add ax, 31
	ret

is_loader:
	; [bx] is the dir item
	; al is the result
	mov si, 0 ; FAT12_NAME_SIZE
	mov al, 1

per_char_cmp:
	mov ch, [loader_name + si]
	mov cl, [bx + si]
	cmp ch, cl ; msg[si], bx[si]
	jne not_equal

	inc si
	cmp si, FAT12_NAME_SIZE
	jne per_char_cmp
	ret

not_equal:
	mov al, 0
	ret

read_sects:
	; es:bx as target mem addr
	; si number of sects to be read
	; mov si, FAT12_ROOT_TABLE_SIZE
	push ax
	push si
	call read_one_sect
	pop si
	pop ax

	inc ax
	add bx, 0x200
	dec si
	cmp si, 0
	jne read_sects

	ret

read_one_sect:
	; input: AX as sect number
	; ch = N / 36
	mov dl, 36
	div dl
	mov ch, al

	; dh = (N % 36) / 18
	mov al, ah
	mov ah, 0
	mov dl, 18
	div dl
	mov dh, al

	; cl = (N % 36) % 18 + 1
	mov cl, ah
	inc cl

	mov dl, 0
	mov ah, 2
	mov al, 1

	mov si, MAX_RETRY
retry:
	cmp si, 0
	je fin
	dec si
	int 0x13
	jc retry

	ret

loader_name db "LOADER  BIN"

fin:
	HLT                     ; 让CPU停止，等待指令
	JMP     fin             ; 无限循环

msg:
	DB      0x0a, 0x0a      ; 换行两次
	DB      "hello, myos"
	DB      0

	times 510 - ($ - $$) db 0

	DB      0x55, 0xaa