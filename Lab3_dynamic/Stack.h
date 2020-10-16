#ifndef _STACK_H_D_
#define _STACK_H_D_
#include <iostream>

namespace Stack_dynamic {

	struct Cell
	{
		double v;
		char* str;

		Cell(double d = 0, const char* s = "");
		Cell(const Cell&);
		Cell(Cell&& c) noexcept : v(c.v), str(c.str) { c.str = nullptr; }
		~Cell() { delete[] str; } 

		Cell& operator=(const Cell&);
		Cell& operator=(Cell&&) noexcept;

		friend std::istream& operator>>(std::istream&, Cell&);
		friend std::ostream& operator<<(std::ostream&, const Cell&);
	};

	class Stack {
	private:
		static const int Q = 10;
		int SZ;
		int top;
		Cell* a;
	public:
		Stack() : SZ(Q), top(0), a(new Cell[Q]) {}
		Stack(const Stack&);
		Stack(Stack&& st) noexcept : SZ(st.SZ), top(st.top), a(st.a) { st.a = nullptr; }
		Stack(const Cell[], int);
		~Stack() { delete[] a; }

		Stack& operator=(const Stack&);
		Stack& operator=(Stack&&) noexcept;
		Stack& operator+=(const Cell&);
		Stack& operator()(Cell&);

		inline bool not_empty() const { return top > 0; }
		inline bool is_full() const { return top == SZ; }
		inline int getSZ() const { return SZ; }
		inline int gettop() const { return top; }

		friend std::istream& operator>>(std::istream&, Stack&);
		friend std::ostream& operator<<(std::ostream&, const Stack&);
	};

	template<class T>
	void swap(T& a1, T& a2)
	{
		T tmp = a1; a1 = a2; a2 = tmp;
	}
}
#endif
