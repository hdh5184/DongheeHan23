#include <iostream>

using namespace std;

class Animal {
public:
	Animal() { // 생성자
		cout << "Animal 생성자 (탄생)" << endl;
	}
	virtual ~Animal() { // 소멸
		cout << "Animal 소멸자 (사망)" << endl;
	}

	virtual void Talk() { // virtual이 아닌 경우 Animal의 Talk만 호출됨, 자식 클래스에 Talk가 없으면 부모의 Talk 호출됨
		cout << "Animal 울음소리" << endl;
	}
};

class Cat : public Animal {
public:
	Cat() { // 생성자
		cout << "Cat 생성자 (탄생)" << endl;
	}
	~Cat() { // 소멸
		cout << "Cat 소멸자 (사망)" << endl;
	}

	void Talk() {
		cout << "Cat 울음소리" << endl;
	}
};

class Tiger : public Cat{ // Cat : 부모 클래스 / Tiger : 자식 클래스
public:
	Tiger() {
		cout << "Tiger 생성자 (탄생)" << endl;
	}
	~Tiger() {
		cout << "Tiger 소멸자 (사망)" << endl;
	}

	void Talk() {
		cout << "Tiger 울음소리" << endl;
	}
};

class Hamster : public Animal {
public:
	Hamster() {
		cout << "Hamster 생성자 " << endl;
	}
	~Hamster() {
		cout << "Hamster 소멸자 " << endl;
	}

	void Talk() {
		cout << "Hamster 울음소리" << endl;
	}
};

int main() {
	cout << "테스트 텍스트" << endl;
	cout << endl;

	

	int animalNum = 3;
	Animal** ani = new Animal * [animalNum];

	ani[0] = new Tiger();
	ani[1] = new Cat();
	ani[2] = new Hamster();
	cout << "\n" << endl;

	for (int i = 0; i < animalNum; i++)
	{
		ani[i]->Talk();		// Animal의 Talk만 호출됨
		delete(ani[i]);
		cout << "\n" << endl;
	}


}