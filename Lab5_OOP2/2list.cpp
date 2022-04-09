#include <stdio.h>
#include <string>
#include <iostream>
#include <locale.h>

using namespace std;

class Animal {
private:
	string name;
public:
	Animal() {
		printf("\nAnimal()\n");
	}
	Animal(string name) {
		this->name = name;
		printf("\nAnimal(string name)\n");
	}
	virtual ~Animal() {
		printf("~Animal()\n");
	}
	virtual void sound() {
		printf("\n");
	}
	virtual string classname() {
		return "Animal";
	}
	virtual bool isA(string classname) {
		return classname == "Animal";
	}
};

class Cat : public Animal{
public:
	Cat() {
		printf("Cat()\n");
	}
	Cat(string name):Animal(name) {
		printf("Cat(string name)\n");
	}
	~Cat() {
		printf("~Cat()\n");
	}
	void sound() {
		printf("mew-mew\n");
	}
	void purr() {
		printf("Cat::purr()\n");
	}
	string classname() {
		return "Cat";
	}
	bool isA(string classname) {
		return classname == "Cat" || Animal::isA(classname);
	}
};

class Dog : public Animal {
public:
	Dog() {
		printf("Dog()\n");
	}
	Dog(string name) :Animal(name) {
		printf("Dog(string name)\n");
	}
	~Dog() {
		printf("~Dog()");
	}
	void sound() {
		printf("wow-wow\n");
	}
	void whine() {
		printf("Dog::whine()\n");
	}
	string classname() {
		return "Dog";
	}
	bool isA(string classname) {
		return classname == "Dog" || Animal::isA(classname);
	}
};

class MaineCoon : public Cat {
public:
	MaineCoon() {
		printf("MaineCoon()\n");
	}
	MaineCoon(string name) :Cat(name) {
		printf("MaineCoon(string name)\n");
	}
	~MaineCoon() {
		printf("~MaineCoon()\n");
	}
	void sound() {
		printf("meeew-meeew\n");
	}
	void have_lynx_tips() {
		printf("MaineCoon::have_lynx_tips()\n");
	}
	string classname() {
		return "MaineCoon";
	}
	bool isA(string classname) {
		return classname == "MaineCoon" || Cat::isA(classname);
	}
};

class Retriever : public Dog {
public:
	Retriever() {
		printf("Retriever()\n");
	}
	Retriever(string name) :Dog(name) {
		printf("Retriever(string name)\n");
	}
	~Retriever() {
		printf("~Retriever()");
	}
	void sound() {
		printf("wow-wow-wow\n");
	}
	void have_drooping_ears() {
		printf("Retriever::have_drooping_ears()\n");
	}
	string classname() {
		return "Retriever";
	}
	bool isA(string classname) {
		return classname == "Retriever" || Dog::isA(classname);
	}
};

class GoldenRetriever : public Retriever {
public:
	GoldenRetriever() {
		printf("GoldenRetriever()\n");
	}
	GoldenRetriever(string name) :Retriever(name) {
		printf("GoldenRetriever(string name)\n");
	}
	~GoldenRetriever() {
		printf("~GoldenRetriever()");
	}
	void sound() {
		printf("woow-woow\n");
	}
	void shed_golden_hair() {
		printf("GoldenRetriever::shed_golden_hair()\n");
	}
	string classname() {
		return "GoldenRetriever";
	}
	bool isA(string classname) {
		return classname == "GoldenRetriever" || Retriever::isA(classname);
	}
};

Animal* rand_pet() {
	int r = rand() % 5;
	switch (r)
	{
	case 0: return new Cat();
	case 1: return new Dog();
	case 2: return new MaineCoon();
	case 3: return new Retriever();
	default: return new GoldenRetriever();
	}
}

int main() {
	printf("-----create objects of various classes-----\n");
	Animal* pets[10];
	for (int i = 0; i < 10; ++i) {
		printf("\n%d ", i);
		pets[i] = rand_pet();
	}

	printf("\n\n-----work with classname method-----\n");
	for (int i = 0; i < 10; ++i) {
		if (pets[i]->classname() == "MaineCoon" || pets[i]->classname() == "Cat") {
			cout << i << " " << pets[i]->classname() << " -> ";
			((Cat*)pets[i])->purr();
		}
	}
	printf("\n");
	for (int i = 0; i < 10; ++i) {
		if (pets[i]->classname() == "GoldenRetriever" || pets[i]->classname() == "Retriever" || pets[i]->classname() == "Dog") {
			cout << i << " " << pets[i]->classname() << " -> ";
			((Dog*)pets[i])->whine();
		}
	}

	printf("\n\n-----work with isA method-----\n");
	for (int i = 0; i < 10; ++i) {
		if (pets[i]->isA("Cat")) {
			cout << i << " " << pets[i]->classname() << " -> ";
			((Cat*)pets[i])->purr();
		}
	}
	printf("\n");
	for (int i = 0; i < 10; ++i) {
		if (pets[i]->isA("Retriever")) {
			cout << i << " " << pets[i]->classname() << " -> ";
			((Retriever*)pets[i])->have_drooping_ears();
		}
	}

	printf("\n\n-----dangerous type casting-----\n");
	for (int i = 0; i < 10; ++i) {
		cout << i << " " << pets[i]->classname() << " -> ";
		((MaineCoon*)pets[i])->have_lynx_tips();
	}
	
	printf("\n\n-----using dynamic cast-----\n");
	for (int i = 0; i < 10; ++i) {
		if (dynamic_cast<Cat*>(pets[i]) != NULL) {
			cout << i << " " << pets[i]->classname() << " -> ";
			dynamic_cast<Cat*>(pets[i])->purr();
		}
	}
	printf("\n");
	for (int i = 0; i < 10; ++i) {
		GoldenRetriever* goldDog = dynamic_cast<GoldenRetriever*>(pets[i]);
		if (goldDog != nullptr) {
			cout << i << " " << pets[i]->classname() << " -> ";
			goldDog->shed_golden_hair();
			goldDog->have_drooping_ears();
		}
	}

	printf("\n\n-----using smart pointers-----\n");

	// unique_ptr

	unique_ptr<Dog> unq = unique_ptr<Dog>(new Dog());
	unq->sound();

	Dog* d1 = new Dog("Rex");
	auto unq1 = unique_ptr<Dog>(d1);
	(*unq1).classname();
	// освобождаем unq1
	Dog* d2 = unq1.release(); //
	delete d2;

	Dog* d3 = new Dog("Bob");
	auto unq2 = unique_ptr<Dog>(d3);
	unq1 = std::move(unq2); // освободили unq2 - теперь он пуст, а unq1 указывает на объект "Bob"

	unique_ptr<Dog> unq3;
	unq3 = std::move(unq1); // освободили unq1 - теперь он пуст, а unq3 указывает на объект "Bob"

	Dog* ptr = unq3.get(); // продолжает указывать на объект, поэтому не можем удалить ptr
	ptr->whine();
	//delete ptr;

	unique_ptr<Dog> unq4 = std::make_unique<Dog>("Mars");
	//unq4.reset();

	auto& ref = unq4; // создали ссылку на умн. указатель
	ref->sound();

	ref.reset(); 
	printf("\n");

	// shared_ptr

	shared_ptr<Cat> shr1 = shared_ptr<Cat>(new Cat("Rose"));
	auto shr2 = make_shared<Cat>("Milka");
	shr1.swap(shr2); // теперь shr1 указывает на "Milka", а shr2 - на "Rose"

	auto shr3 = shr2;
	int n = shr3.use_count();
	printf("%d\n", n);

	shr3.reset(); // теперь shr3 не указывает на "Rose", но этот объект не удаляется, т.к. на него еще указывает shr2
	n = shr2.use_count();
	printf("%d\n", n);

	shr2.reset(); // теперь и shr2 не указывает на "Rose", поэтому вызовется деструктор для "Rose"
	n = shr2.use_count();
	printf("%d\n", n);
}