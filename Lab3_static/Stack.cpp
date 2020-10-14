#include "Stack.h"
#include <iostream>

namespace Stack_static {

	bool Cell::string_is_correct(const char* s)
	{
		int i = 0;
		while ((*s != '\0') && (i++ < len + 1))
			s++;
		if (*s)
			return false;
		return true;
	}

	Cell::Cell(double d, const char s[len + 1]) : v(d)
	{
		if (string_is_correct(s))
			strcpy_s(str, s);
		else throw std::exception("Failed to add string to structure!");
	}

	Stack::Stack(const Cell c[], int n) : top(0)
	{
		if ((0 < n) && (n <= SZ))
			for (; top < n; top++)
				a[top] = c[top];
		else throw std::exception("Int parametr is out of range!");
	}

	Stack& Stack::operator+=(const Cell& c)
	{
		if (top < SZ)
			a[top++] = c;
		else throw std::exception("Stack overflow!");
		return *this;
	}

	Stack& Stack::operator()(Cell& c)
	{
		if (top > 0)
			c = a[--top];
		else throw std::exception("Stack is empty!");
		return *this;
	}

	std::istream& operator>>(std::istream& s, Cell& c)
	{
		double v;
		char str[c.len+1];
		s >> v; s.get();
		s.getline(str, c.len + 1);
		if (s.good())
			c = { v, str };
		else throw std::exception("Failed to create structure!");
		return s;
	}

	std::istream& operator>>(std::istream& s, Stack& st)
	{
		Cell tmp;
		s >> tmp;
		st += tmp;
		return s;
	}

	std::ostream& operator<<(std::ostream& s, const Cell& c)
	{
		s << c.v << ' ' << c.str;
		return s;
	}

	std::ostream& operator<<(std::ostream& s, const Stack& st)
	{
		s << "Stack status >> ";
		if (st.top == 0)
			s << "empty";
		else {
			for (int i = st.top - 1; i > 0; --i)
				s << st.a[i] << '|'; s << st.a[0];
		}
		return s;
	}
}
