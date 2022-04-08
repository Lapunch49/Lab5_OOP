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
		printf("\nAnimal\n");
	}
	Animal(string name) {
		this->name = name;
		printf("\nAnimal(string name)\n");
	}
	virtual ~Animal() {
		printf("~Animal\n");
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

}