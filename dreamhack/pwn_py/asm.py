from pwn import *
context.arch = 'amd64' # 익스플로잇 대상 아키텍처 'x86-64'
code = shellcraft.sh() # 셸을 실행하는 셸 코드
code = asm(code)       # 셸 코드를 기계어로 어셈블
print(code)