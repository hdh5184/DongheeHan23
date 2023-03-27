# Lecture 04
* 별 문자가 반복 출력될 때 Esc키를 누르면 반복이 중단되어 프로그램을 종료시키는 실행 파일 생성하는 과제
* (cpp 파일은 test.cpp / 실행 파일은 test.exe로 저장함)

- Windows PowerShell을 이용해보았다.
- git bash를 사용하는 것과의 차이가 있다.

- c++ 사용하면서 함수 사용 시 해당 함수에 포함된 헤더를 상단에 #include해야 한다.
- getch(입력된 키의 정보 가져옴) 함수 사용 시 헤더는 <conio.h>를 포함

- 윈도우는 cp949 인코딩을, 리눅스는 UTF8 인코딩을 사용하다보니 Windows PowerShell 사용할 때 한글을 출력하는 실행파일을 실행하면 글자가 깨지는 현상이 일어난다.
