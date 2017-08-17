extern choose ; int choose(int a, int b)

[section .data]
num1 dd 3
num2 dd 4

[section .text]
global _start
global myprint

_start:
	push dword [num2]
	push dword [num1]
	call choose
	add esp, 8
	jmp exit

exit:
	mov ebx, 0
	mov eax, 1
	int 0x80

; void myprint(char *msg, int len)
myprint:
	mov ecx, [esp+4] ; msg
	mov edx, [esp+8] ; len
	mov ebx, 1
	mov eax, 4
	int 0x80
	ret
