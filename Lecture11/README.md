# Lecture 11
* Musoeun 엔진 제작

- scene 클래스 : 
1. ScreenBuffer(화면 배열)와 화면의 크기를 저장
2. Scene에서 사용하고 있는 Object의 리스트를 std::vector를 이용해서 뱀  만들기
3. Draw를 통해 Active한 Object의 Render를 호출한 후 ScreenBuffer를 cout으로 화면에 한번 그림.

- Object 클래스
1. Render()에는 Scene에서 제공하는 ScreenBuffer를 매개변수로 받고, 거기다가 이것저것 그릴 내용을 그릴것 (Object의 모양을 그릴것)
2. position x,y 값을 가진 Object 생성 필요.
3. 다양한 Object를 만드려면 이 클래스를 상속해서 만들기 (SnakeBody : public Object)

// 뱀 오브젝트의 움직임과 Component는 아직 구현 못함

//뱀 오브젝트를 스크린에 출력하는 건 처음 타이틀의 게임 시작으로 들어오시면 확인 가능합니다.
