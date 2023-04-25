#include <stdio.h>
#include <string.h>
unsigned long hashcode = 0x21DD09EC; // 568134124

unsigned long check_password(const char* p) {
        int* ip = (int*)p; // int 형으로 변환
        int i;
        int res = 0;
        for(i = 0; i < 5; i++) {
                // 4byte씩 잘려서 배열로 만들어진다.
                // 따라서 Hashcode 0x21DD09EC와 같아지려면 반복문의 수만큼 나누어주면 된다.
                // 그러나 반복문의 수만큼 나누어 곱했을 때, 0x4의 값이 부족하므로 마지막으로 더해지는 값에는 몫 += 0x4를 해야한다.
                res += ip[i]; // res = ip[0] + ip[1] + ip[2] + ip[3] + ip[4]
                printf("%d\n", ip[i]);
        }
        return res;
}

int main(int argc, char* argv[]){
        if(argc<2){
                printf("usage : %s [passcode]\n", argv[0]);
                return 0;
        }
        if(strlen(argv[1]) != 20){
                printf("passcode length should be 20 bytes\n");
                return 0;
        }

        if(hashcode == check_password( argv[1] )){
                system("/bin/cat flag");
                return 0;
        }
        else
                printf("wrong passcode.\n");
        return 0;
}