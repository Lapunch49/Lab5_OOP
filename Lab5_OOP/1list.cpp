#include <iostream>
#include <stdio.h>

using namespace std;

class Base {
public:	
	int x;
	float a;

	Base() {
		printf("Base()\n");
		x = 0;
		a = 0;
		printf("x = %d,a = %.2f\n", x, a );
	}
	Base(Base* obj) {
		printf("Base(Base* obj)\n");
		x = obj->x;
		a = obj->a;
		printf("x = %d,a = %.2f\n", x, a);
	}
	Base(Base& obj) {
		printf("Base(Base& obj)\n");
		x = obj.x;
		a = obj.a;
		printf("x = %d,a = %.2f\n", x, a);
	}
	virtual ~Base() {
		printf("~Base()\n");
		x = 0;
		a = false;
	}
};

class Desc : public Base {
public:	
	int y; 
	float b;

	Desc():Base() {
		printf("Desc()\n");
		y = 0;
		b = false;
		printf("x = %d,a = %.2f, y = %d, b = %.2f\n", x, a, y, b);
	}
	Desc(Desc *obj) :Base(obj) {
		printf("Desc(Desc *obj)\n");
		y = obj->y;
		b = obj->b;
		printf("x = %d,a = %.2f, y = %d, b = %.2f\n", x, a, y, b);
	}
	Desc(Desc &obj) :Base(obj) {
		printf("Desc(Desc &obj)\n");
		y = obj.y;
		b = obj.b;
		printf("x = %d,a = %.2f, y = %d, b = %.2f\n", x, a, y, b);
	}
	~Desc(){
		printf("~Desc()\n");
		y = 0; 
		b = false;
		printf("x = %d,a = %.2f, y = %d, b = %.2f\n", x, a, y, b);
	}
};

void func1(Base obj) {
	printf("func1(Base obj)\n");
	obj.x = 4;
	obj.a = 7.8;
}

void func2(Base* obj) {
	printf("func2(Base* obj)\n");
	obj->x = 4;
	obj->a = 7.8;
}

void func3(Base& obj) {
	printf("func3(Base& obj)\n");
	obj.x = 4;
	obj.a = 7.8;
}


Base func1() {
	Base b;
	b.x = 6; 
	b.a = 3.4;
	return b;
}

Base* func2() {
	Base b;
	b.x = 6;
	b.a = 3.4;
	return &b;
}

Base& func3() {
	Base b;
	b.x = 6;
	b.a = 3.4;
	return b;
}

void output_state(Base& obj) {
	printf("x = %d, a = %.2f\n\n", obj.x, obj.a);
}

Base back_state(Base& obj) {
	obj.x = 0;
	obj.a = 0;
	return obj;
}

int main() {
	// ипользование функций, принимающих разные Base, с параметром Base
	{
		Base b1;
		printf("\n");

		func1(b1);
		printf("x = %d, a = %.2f\n\n", b1.x, b1.a);
		b1.x = 0; b1.a = 0;

		func1(&b1);
		printf("x = %d, a = %.2f\n\n", b1.x, b1.a);
		b1.x = 0; b1.a = 0;

		func2(&b1);
		printf("x = %d, a = %.2f\n\n", b1.x, b1.a);
		b1.x = 0; b1.a = 0;

		func3(b1);
		printf("x = %d, a = %.2f\n\n", b1.x, b1.a);

		Base* b2 = new Base();
		printf("\n");

		func1(b2);
		printf("x = %d, a = %.2f\n\n", b2->x, b2->a);
		b2->x = 0; b2->a = 0;

		func1(*b2);
		printf("x = %d, a = %.2f\n\n", b2->x, b2->a);
		b2->x = 0; b2->a = 0;

		func2(b2);
		printf("x = %d, a = %.2f\n\n", b2->x, b2->a);
		b2->x = 0; b2->a = 0;

		func3(*b2);
		printf("x = %d, a = %.2f\n\n", b2->x, b2->a);

		delete b2;
	}
	printf("-----------------------------------------\n");
	//использование функций, принимающих разные Base, с параметром Desc
	{
		Desc d1;
		printf("\n");

		func1(d1);
		printf("x = %d, a = %.2f\n\n", d1.x, d1.a);
		d1.x = 0; d1.a = 0;

		func1(&d1);
		printf("x = %d, a = %.2f\n\n", d1.x, d1.a);
		d1.x = 0; d1.a = 0;

		func2(&d1);
		printf("x = %d, a = %.2f\n\n", d1.x, d1.a);
		d1.x = 0; d1.a = 0;

		func3(d1);
		printf("x = %d, a = %.2f\n\n", d1.x, d1.a);
		d1.x = 0; d1.a = 0;

		Desc* d2 = new Desc();
		printf("\n");

		func1(d2);
		printf("x = %d, a = %.2f\n\n", d2->x, d2->a);
		d2->x = 0; d2->a = 0;

		func1(*d2);
		printf("x = %d, a = %.2f\n\n", d2->x, d2->a);
		d2->x = 0; d2->a = 0;

		func2(d2);
		printf("x = %d, a = %.2f\n\n", d2->x, d2->a);
		d2->x = 0; d2->a = 0;

		func3(*d2);
		printf("x = %d, a = %.2f\n\n", d2->x, d2->a);
		d2->x = 0; d2->a = 0;

		delete d2;
	}
	printf("-----------------------------------------\n");
	// проверка механизма возврата объектов из функции
	{
		Base b1 = &(func1());
		Base* b2 = &(func1());
	}
	
	return 0;
}