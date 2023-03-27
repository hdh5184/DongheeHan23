#include <iostream>
#include <conio.h>

int main(){
	while(true){
		std::cout<<'*'<<std::endl;
		if(_kbhit()){			 //키보드 입력 확인이 되면 실행
			if(_getch() == 27) 	 //esc 입력 시
			break;	
		}
	}

	return 0;
}
