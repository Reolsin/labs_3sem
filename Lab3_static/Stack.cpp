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

	Cell::Cell(double d, const char s[len + 1] = "") : v(d), str("")
	{
		if (string_is_correct(s))
			strcpy_s(str, s);
		else throw std::exception("Failed to add string to structure!");
	}

	Stack::Stack(Cell c[], int n) : top(0)
	{
		if (n <= SZ) {
			for (; top < n; top++) {
				a[top].v = c[top].v;
				strcpy_s(a[top].str, c[top].str);
			}
		}
		else throw std::exception("Too many rows to write!");
	}

	Stack& Stack::operator+=(const Cell& c)
	{
		if (not_full()) {
			a[top].v = c.v;
			strcpy_s(a[top++].str, c.str);
		}
		else throw std::exception("Stack overflow!");
		return *this;
	}

	Stack& Stack::operator()(Cell& c)
	{
		if (not_empty()) {
			c.v = a[--top].v;
			strcpy_s(c.str, a[top].str);
		}
		else
			throw std::exception("Stack empty!");
		return *this;
	}

	std::istream& operator>>(std::istream& s, Cell& c)
	{
		double v;
		char str[c.len+1];
		s >> v; s.get();
		s.getline(str, c.len + 1);
		if (s.good()) {
			c.v = v;
			strcpy_s(c.str, str);
		}
		else
			throw std::exception("Failed to enter structure!");
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
		s << "Stack status|";
		if (st.top == 0)
			s << "empty|";
		else
			for (int i = st.top - 1; i >= 0; --i)
				s << st.a[i] << '|';
		return s;
	}
}
