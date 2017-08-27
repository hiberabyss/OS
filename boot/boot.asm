CYLS equ 10
SECTIONS equ 18
MAX_RETRY equ 5
; LOADER_MEM_START ; loaded from nasm

FAT12_BITMAP_MEM_START equ 0xa000
FAT12_BITMAP_SIZE equ 9
FAT12_BITMAP_START equ 1

FAT12_ROOT_MEM_SEG equ 0x800
FAT12_ROOT_TABLE_SIZE equ 9

FAT12_ROOT_SIZE equ 14
FAT12_ROOT_MEM_ADDR_START equ (FAT12_ROOT_MEM_SEG * 16)
FAT12_ROOT_MEM_ADDR_END equ (FAT12_ROOT_MEM_SEG * 16 + FAT12_ROOT_SIZE * 512)

FAT12_MAP_START_SECT equ 1

FAT12_ROOT_FIRST_SECT_NUM equ 19
FAT12_NAME_SIZE equ 11

FAT12_PER_DIR_META_SIZE equ 32

ASM_FUNC equ 0x7e00
ASM_VARIABLE equ 0x7f00

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
	jmp main

read_one_sect:
	; void read_one_sect(short int sect_idx, char *buf)
	; input: AX as sect number
	mov eax, [esp+4]
	mov es, [esp+8]
	mov ebx, [esp+12]
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

	ret 2

fin:
	HLT                     ; 让CPU停止，等待指令
	JMP     fin             ; 无限循环

find_file_sec_idx: ; 0x7c79
	; short int find_file_sect_idx(const char *)
	; ax is the output
	mov cx, [esp+4]
	xor ebx, ebx
	mov bx, FAT12_ROOT_MEM_ADDR_START
next_file_item:
	push ebx
	push ecx
	call 0:is_filename_equal
	add sp, 8
	cmp al, 1
	je get_sector_num
	add bx, FAT12_PER_DIR_META_SIZE
	cmp bx, FAT12_ROOT_MEM_ADDR_END
	je fin
	jmp next_file_item

get_sector_num:
	mov ax, [bx + 0x1a]
	ret 2

is_filename_equal:
	; bool is_name_equal(const char *, const char *)
	; al is the result
	mov ebx, [esp+8]
	mov edx, [esp+4]
	xor esi, esi
	mov si, 0 ; FAT12_NAME_SIZE
	mov al, 1

per_char_cmp:
	mov cl, [ebx + esi]
	mov ch, [edx + esi]
	cmp ch, cl
	jne not_equal

	inc si
	cmp si, FAT12_NAME_SIZE
	jne per_char_cmp
	ret 2

not_equal:
	mov eax, 0
	ret 2

read_sects:
	; es:bx as target mem addr
	; si number of sects to be read
	; mov si, FAT12_ROOT_TABLE_SIZE
	push si
	push ax
	push ebx
	mov bx, es
	push ebx
	push eax
	call 0:read_one_sect
	add esp, 12
	pop ax
	pop si

	inc ax
	add bx, 0x200
	dec si
	cmp si, 0
	jne read_sects

	ret

print_char:
	; void print_char(const char)
	mov eax, [esp+4]
	mov ah, 0xe
	mov bx, 15
	int 0x10
	ret 2

enter_vga_mode:
	mov al, 0x13
	mov ah, 0
	int 0x10
	ret 2

loader_name db "LOADER  BIN"

main:
	; read all root meta, 14 sects
	mov ax, FAT12_ROOT_MEM_SEG
	mov es, ax
	mov bx, 0
	mov ax, FAT12_ROOT_FIRST_SECT_NUM
	mov si, 14
	call read_sects ; 0x7ca6

	; read all fat bitmap, 9 sects
	mov bx, 0
	mov es, bx
	mov bx, FAT12_BITMAP_MEM_START
	mov ax, FAT12_BITMAP_START
	mov si, FAT12_BITMAP_SIZE
	call read_sects

	push dword loader_name
	call 0:find_file_sec_idx ; 0x7c6f
	add sp, 4
	mov [ASM_VARIABLE], ax
	add ax, 31
	push dword LOADER_MEM_START
	push dword 0
	push eax
	call 0:read_one_sect
	add sp, 6

	; save function address
	; lea ax, fin
	mov word [ASM_FUNC], fin
	mov word [ASM_FUNC + 4], print_char ; 0x7d12
	mov word [ASM_FUNC + 8], is_filename_equal ; 0x7d12
	mov word [ASM_FUNC + 12], find_file_sec_idx
	mov word [ASM_FUNC + 16], read_one_sect
	mov word [ASM_FUNC + 20], enter_vga_mode

	jmp LOADER_MEM_START

	times 510 - ($ - $$) db 0

	DB      0x55, 0xaa
