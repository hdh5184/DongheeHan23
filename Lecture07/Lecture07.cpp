#include <iostream>

using namespace std;

class Animal {
public:
	Animal() { // ������
		cout << "Animal ������ (ź��)" << endl;
	}
	virtual ~Animal() { // �Ҹ�
		cout << "Animal �Ҹ��� (���)" << endl;
	}

	virtual void Talk() { // virtual�� �ƴ� ��� Animal�� Talk�� ȣ���, �ڽ� Ŭ������ Talk�� ������ �θ��� Talk ȣ���
		cout << "Animal �����Ҹ�" << endl;
	}
};

class Cat : public Animal {
public:
	Cat() { // ������
		cout << "Cat ������ (ź��)" << endl;
	}
	~Cat() { // �Ҹ�
		cout << "Cat �Ҹ��� (���)" << endl;
	}

	void Talk() {
		cout << "Cat �����Ҹ�" << endl;
	}
};

class Tiger : public Cat{ // Cat : �θ� Ŭ���� / Tiger : �ڽ� Ŭ����
public:
	Tiger() {
		cout << "Tiger ������ (ź��)" << endl;
	}
	~Tiger() {
		cout << "Tiger �Ҹ��� (���)" << endl;
	}

	void Talk() {
		cout << "Tiger �����Ҹ�" << endl;
	}
};

class Hamster : public Animal {
public:
	Hamster() {
		cout << "Hamster ������ " << endl;
	}
	~Hamster() {
		cout << "Hamster �Ҹ��� " << endl;
	}

	void Talk() {
		cout << "Hamster �����Ҹ�" << endl;
	}
};

int main() {
	cout << "�׽�Ʈ �ؽ�Ʈ" << endl;
	cout << endl;

	

	int animalNum = 3;
	Animal** ani = new Animal * [animalNum];

	ani[0] = new Tiger();
	ani[1] = new Cat();
	ani[2] = new Hamster();
	cout << "\n" << endl;

	for (int i = 0; i < animalNum; i++)
	{
		ani[i]->Talk();		// Animal�� Talk�� ȣ���
		delete(ani[i]);
		cout << "\n" << endl;
	}


}