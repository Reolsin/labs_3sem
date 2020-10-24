#ifndef _STACK_H_ST_
#define _STACK_H_ST_
#include <iostream>

namespace Stack_static {

	struct Cell
	{
		static const int len = 10;
		//structure data
		double v;
		char str[len+1];
		//Structure constructor
		Cell(double d = 0, const char s[len + 1] = "");
		//in-out Structure overloaded operators
		friend std::istream& operator>>(std::istream&, Cell&);
		friend std::ostream& operator<<(std::ostream&, const Cell&);
		//Function for string validation
		bool string_is_correct(const char*);
	};

	class Stack {
	private:
		static const int SZ = 10;
		int top;
		Cell a[SZ];
	public:
		//constructors
		Stack() : top(0) {}
		Stack(const Cell[], int);
		//overloaded operators
		Stack& operator+=(const Cell&); //push
		Stack& operator()(Cell&); //pop
		//getters
		inline bool not_empty() const { return top > 0; }
		inline bool not_full() const { return top < SZ; }
		inline int getSZ() const { return SZ; }
		inline int gettop() const { return top; }
		//in-out Stack overloaded operators
		friend std::istream& operator>>(std::istream&, Stack&);
		friend std::ostream& operator<<(std::ostream&, const Stack&);
	};
}

#endif
