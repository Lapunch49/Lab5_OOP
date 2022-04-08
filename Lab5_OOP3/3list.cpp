#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <Windows.h>

class Point
{
public:
	int x, y;
	Point() {
		printf("Point()\n");
		x = 0;
		y = 0;
		printf("x=%d, y=%d\n", this->x, this->y);
	}
	Point(int x, int y) {
		printf("Point(int x, int y)\n");
		this->x = x;
		this->y = y;
		printf("x=%d, y=%d\n", this->x, this->y);
	}
	Point(const Point& p) {
		printf("Point(const Point &p)\n");
		x = p.x;
		y = p.y;
		printf("x=%d, y=%d\n", this->x, this->y);
	}
	virtual ~Point() {
		printf("Values before deleting: %d, %d\n", x, y);
		printf("~Point()\n");
	}
	void change(int x, int y) {
		printf("change(%d->%d,%d->%d)\n", this->x, x, this->y, y);
		this->x = x;
		this->y = y;
	}
	virtual void draw() { // нарисовать точку на поле
		if (x < 16 && y < 16 && x >= 0 && y >= 0) {
			// запоминаем изнач. координаты каретки в переменных x_ и y_
			CONSOLE_SCREEN_BUFFER_INFO info_xy;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_xy);
			int x_ = info_xy.dwCursorPosition.X;
			int y_ = info_xy.dwCursorPosition.Y;
			// перемещаем каретку в новое место 
			COORD coord;
			coord.X = x * 2 + 2;
			coord.Y = y + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			// печатаем * и возвращаем каретку обратно
			printf("*");
			coord.X = x_;
			coord.Y = y_;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			printf("draw(%d, %d)", x, y);
		}
		else
			printf("can't draw(%d, %d)\n", x, y);
	}
	void erase() { // стереть точку на поле
		if (x < 16 && y < 16 && x >= 0 && y >= 0) {
			// рисуем * черным цветом текста, возвращаем тексту белый цвет
			int bg = 0;
			int text = 0;
			HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((bg << 4) | text));
			Point::draw();
			text = 15;
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((bg << 4) | text));
			printf("\nerase(%d, %d)\n", x, y);
		}
		else
			printf("\ncan't erase(%d, %d)\n", x, y);
	}
};

class ColoredPoint : public Point {
private:
	int color;
public:
	//ColoredPoint():Point(){
	ColoredPoint() {
		printf("ColoredPoint()\n");
		color = 15;
		printf("x=%d, y=%d, color=%d\n", this->x, this->y, this->color);
	}
	ColoredPoint(int x, int y, int color) :Point(x, y) {
		printf("ColoredPoint(int x, int y, int color)\n");
		this->color = color;
		printf("x=%d, y=%d, color=%d\n", this->x, this->y, this->color);
	}
	ColoredPoint(const ColoredPoint& p) {
		printf("ColoredPoint(const ColoredPoint& p)\n");
		x = p.x;
		y = p.y;
		color = p.color;
		printf("x=%d, y=%d, color=%d\n", this->x, this->y, this->color);
	}
	~ColoredPoint() {
		printf("\nValues before deleting: x=%d, y=%d, color=%d\n", x, y, color);
		printf("~ColoredPoint()\n");
	}
	void draw() {
		if (x < 16 && y < 16 && x >= 0 && y >= 0) {
			// меняем цвет перед прорисовкой *, потом возвращаем белый цвет
			int bg = 0;
			int text = color;
			HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((bg << 4) | text));
			Point::draw();
			text = 15; // белый цвет для текста
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((bg << 4) | text));
			printf("\rdraw(%d, %d, color=%d)\n", x, y, color);
		}
		else
			printf("can't draw(%d, %d, color=%d)\n", x, y, color);
	}
	void change(int x, int y, int color) {
		printf("\nchange(%d->%d,%d->%d,%d->%d)\n", this->x, x, this->y, y, this->color, color);
		this->x = x;
		this->y = y;
		this->color = color;
	}
	void change_color(int new_color) {
		printf("change_color(%d->%d)\n", color, new_color);
		color = new_color;
	}
};

int rand_num() {
	int num = 0;
	num = rand() % 16;
	return num;
}

int main() {
	// построение поля 
	printf(" ");
	for (int i = 0; i < 16; ++i)
		printf(" %X", i);
	printf("\n  ");
	for (int i = 0; i < 16; ++i)
		printf("--");
	for (int i = 0; i < 16; ++i)
		printf("\n%X|", i);
	printf("\n\n");

	////////////////////////////////

	Point* common_points[5];
	for (int i = 0; i < 5; ++i) {
		common_points[i] = new Point(rand_num(), rand_num());
		common_points[i]->draw();
		printf("\n");
	}

	Point* points[5];
	for (int i = 0; i < 5; ++i) {
		if (rand() % 2 == 0)
			points[i] = new Point(rand_num(), rand_num());
		else points[i] = new ColoredPoint(rand_num(), rand_num(), rand_num());
		points[i]->draw();
		printf("\n");
	}

	ColoredPoint* colored_points[5];
	for (int i = 0; i < 5; ++i) {
		colored_points[i] = new ColoredPoint(rand_num(), rand_num(), rand_num());
		colored_points[i]->draw();
		printf("\n");
	}

	return 0;
}