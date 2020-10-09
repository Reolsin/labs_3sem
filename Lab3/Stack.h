#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

namespace Lab3_s {

	struct Cell
	{
		static const int len = 10;
		double v;
		char str[len+1];
	};

	std::istream& operator>>(std::istream&, Cell&);
	std::ostream& operator<<(std::ostream&, const Cell&);

	class Stack
	{
	private:
		static const int len = 10;
		static const int SZ = 10;
		int top;
		Cell a[SZ];
	public:
		Stack() : top(0) {}
		int push(const double, const char[len + 1]);
		int push(const Cell&);
		int pop(Cell&);
		Stack& operator+=(const Cell& c) { this->push(c); return *this; }
		Stack& operator()(Cell& c) { this->pop(c); return *this; }
		Stack& copy(const Stack&);
		Stack& move(Stack&);
		int Status();
		int getSZ() const { return SZ; }
		int gettop() const { return top; }
		friend std::istream& operator>>(std::istream&, Stack&);
		friend std::ostream& operator<<(std::ostream&, const Stack&);
	};

	bool string_is_correct(const char*, int);
}
#endif
