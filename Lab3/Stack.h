#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

namespace Stack_static {

	struct Cell
	{
		static const int len = 10;
		double v;
		char str[len+1];
		Cell() : v(0), str("") {}
		Cell(double, const char[len+1]);
		bool string_is_correct(const char*);
		friend std::istream& operator>>(std::istream&, Cell&);
		friend std::ostream& operator<<(std::ostream&, const Cell&);
	};

	class Stack
	{
	private:
		static const int SZ = 10;
		int top;
		Cell a[SZ];
	public:
		Stack() : top(0) {}
		Stack(Cell[], int);
		Stack& operator+=(const Cell&);
		Stack& operator()(Cell&);
		inline bool not_empty() const { if (top > 0) return true; return false; }
		inline bool not_full() const { if (top < SZ) return true; return false; }
		inline int getSZ() const { return SZ; }
		inline int gettop() const { return top; }
		friend std::istream& operator>>(std::istream&, Stack&);
		friend std::ostream& operator<<(std::ostream&, const Stack&);
	};
}
#endif
