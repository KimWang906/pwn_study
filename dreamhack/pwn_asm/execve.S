mov rax, 0x68732f6e69622f ; ASCII '/bin/bash' | rax에 문자
push rax
mov rdi, rsp    ; rdi = "/bin/sh\x00" | push한 rax의 주소를 가리키고 있는 rsp를 rdi에 복사 
xor rsi, rsi    ; rsi = NULL
xor rdx, rdx    ; rdx = NULL
mov rax, 0x3b   ; rax = sys_execve(0x3b)
syscall         ; execve("/bin/bash", null, null)
