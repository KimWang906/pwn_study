section .text
global _start
_start:
    ; 파일 열기
    mov eax, 0x05 ; SYS_OPEN
    mov ebx, filename ; 파일 이름 설정
    xor ecx, ecx ; O_RDONLY
    int 0x80

    ; 파일 핸들 저장
    mov ebx, eax

    ; 파일 크기 구하기
    mov eax, 0x2A ; SYS_FSTAT
    mov ecx, eax ; ECX에 파일 핸들 복사
    lea edx, [filesize] ; EDX에 파일 크기를 저장할 메모리 주소 지정
    int 0x80

    ; 파일 크기를 eax 레지스터에 저장
    mov eax, [filesize]

    ; 파일 읽기
    push eax ; 읽을 바이트 수
    push buf ; 읽은 데이터를 저장할 버퍼의 메모리 주소
    push ebx ; 파일 핸들
    mov eax, 0x03 ; SYS_READ
    xor ecx, ecx ; ECX = 0
    int 0x80

    ; 파일 닫기
    mov eax, 0x06 ; SYS_CLOSE
    mov ebx, eax ; EBX에 파일 핸들 복사
    int 0x80

    ; 문자열 쓰기
    mov eax, 0x04 ; SYS_WRITE
    mov ebx, 0x01 ; STDOUT
    lea ecx, [buf] ; 출력할 문자열의 메모리 주소
    mov edx, eax ; 출력할 바이트 수
    int 0x80

    ; 종료
    mov eax, 0x01 ; SYS_EXIT
    xor ebx, ebx ; 반환값 0
    int 0x80

filename db '/home/shell_basic/flag_name_is_loooooong', 0
buf times 1024 db 0
filesize dd 0
