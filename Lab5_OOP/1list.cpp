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
	Base(int x, float a) {
		printf("Base()\n");
		this->x = x;
		this->a = a;
		printf("x = %d,a = %.2f\n", x, a);
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
		a = 0;
	}
	void method1() {
		printf("Base::method1()\n");
		method2();
	}
	void method2() {
		printf("Base::method2()\n\n");
	}
	void method3() {
		printf("Base::method3()\n");
		method4();
	}
	virtual void method4() {
		printf("Base::method4()\n\n");
	}
};

class Desc : public Base {
public:	
	int y; 
	float b;

	Desc():Base() {
		printf("Desc()\n");
		y = 0;
		b = 0;
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
		b = 0;
		printf("x = %d,a = %.2f, y = %d, b = %.2f\n", x, a, y, b);
	}
	void method2() {
		printf("Desc::method2()\n\n");
	}
	void method4() {
		printf("Desc::method4()\n\n");
	}
};

void func1(Base obj) {
	printf("func1(Base obj)\n");
	obj.x = 4;
	obj.a = (float)7.8;
}

void func2(Base* obj) {
	printf("func2(Base* obj)\n");
	obj->x = 4;
	obj->a = (float)7.8;
}

void func3(Base& obj) {
	printf("func3(Base& obj)\n");
	obj.x = 4;
	obj.a = (float)7.8;
}


Base ret1() {
	printf("Base ret1()\n");
	Base b;
	b.x = 6; 
	b.a = 3.4;
	return b;
}

Base ret1_() {
	printf("Base ret1_()\n");
	Base* b = new Base;
	b->x = 6;
	b->a = 3.4;
	return *b;
}

Base* ret2() {
	printf("Base* ret2()\n");
	Base b;
	b.x = 6;
	b.a = 3.4;
	return &b;
}

Base* ret2_() {
	printf("Base* ret2_()\n");
	Base* b = new Base;
	b->x = 6;
	b->a = 3.4;
	return b;
}

Base& ret3() {
	printf("Base& ret3()\n");
	Base b;
	b.x = 6;
	b.a = 3.4;
	return b;
}

Base& ret3_() {
	printf("Base& ret3_()\n");
	Base* b = new Base;
	b->x = 6;
	b->a = 3.4;
	return *b;
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
	// проверка работы конструкторов
	{
		Base b0;
		Base b1(b0);
		Base b2(&b1);
		Base b3 = b2; 

		Desc d0;
		Desc d1(d0);
		Desc d2(&d1);
		Desc d3 = d2;
	}
	printf("============================================\n");
	{
		Base* b0 = new Base();
		Base* b1 = new Base(b0);
		Base* b2 = new Base(*b1);
		Base* b3 = b2;
		Base* b4;

		delete b0;
		delete b1;
		delete b2;
		//delete b3;
		//delete b4;


		Desc* d0 = new Desc();
		Desc* d1 = new Desc(d0);
		Desc* d2 = new Desc(*d1);
		Desc* d3 = d2;
		Desc* d4;

		delete d0;
		delete d1;
		delete d2;
		//delete d3;
		//delete b4;

	}
	printf("-----------------------------------------\n");

	// использование функций, принимающих разные Base, с параметром Base
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
		Base b1;
		b1 = ret1();
		printf("b1_ :: x = %d, a = %.2f\n\n", b1.x, b1.a);
		printf("\n");

		Base b1_;
		b1_ = ret1_();
		printf("b1_ :: x = %d, a = %.2f\n\n", b1_.x, b1_.a);
		printf("\n");

		/*Base* b2;
		b2 = ret2();
		delete b2;
		printf("\n");*/

		Base* b2_;
		b2_ = ret2_();
		printf("b2 :: x = %d, a = %.2f\n\n", b2_->x, b2_->a);
		delete b2_;
		printf("\n");

		Base b3;
		b3 = ret3();
		printf("b3 :: x = %d, a = %.2f\n\n", b3.x, b3.a);
		printf("\n");

		Base b3_;
		b3_ = ret3_();
		printf("b3_ :: x = %d, a = %.2f\n\n", b3_.x, b3_.a);
		printf("\n");

		/*Base* b3_2;
		b3_2 = &(ret3());
		printf("b3_2 :: x = %d, a = %.2f\n\n", b3_2->x, b3_2->a);
		delete b3_2;
		printf("\n");*/

		Base* b3_2_;
		b3_2_ = &(ret3_());
		printf("b3__ :: x = %d, a = %.2f\n\n", b3_2_->x, b3_2_->a);
		delete b3_2_;
		printf("\n");
	}

	printf("-----------------------------------------\n");
	// проверка работы виртуальных, невиртуальных, переопределенных, перекрытых методов 
	{ // метод2 - невиртуальный
		{	
			Base b;
			b.method1();
			b.method2();

			Desc d;
			d.method1();
			d.method2();

			Base* b1 = new Base();
			b1->method1();
			b1->method2();

			Desc* d1 = new Desc();
			d1->method1();
			d1->method2();

			Base* d1_ = new Desc();
			d1_->method1();
			d1_->method2();

			delete b1, d1, d1_;
		}
		printf("============================================\n");
		// метод4 - виртуальный
		{
			Base b;
			b.method3();
			b.method4();

			Desc d;
			d.method3();
			d.method4();

			Base* b1 = new Base();
			b1->method3();
			b1->method4();

			Desc* d1 = new Desc();
			d1->method3();
			d1->method4();

			Base* d1_ = new Desc();
			d1_->method3();
			d1_->method4(); 

			delete b1, d1, d1_;
		}
	}
	return 0;
}