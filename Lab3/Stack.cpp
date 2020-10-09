#include "Stack.h"
#include <iostream>

namespace Lab3_s {

	bool string_is_correct(const char* str, int len)
	{
		int i = 0;
		while ((*str != '\0') && (i++ < len + 1))
			str++;
		if (*str)
			return false;
		return true;
	}

	int Stack::push(const double v, const char str[len + 1])
	{
		if (top < SZ)
			if (string_is_correct(str, len)) {
				a[top].v = v;
				strcpy_s(a[top++].str, str);
			}
			else
				throw std::exception("Input string is without null terminator or too long!");
		else
			throw std::exception("Stack overflow!");
		return top;
	}
	
	int Stack::push(const Cell& el)
	{
		if (top < SZ) {
			a[top].v = el.v;
			strcpy_s(a[top++].str, el.str);
		}
		else
			throw std::exception("Stack overflow!");
		return top;
	}

	int Stack::pop(Cell& el)
	{
		int rc = top - 1;
		if (top > 0) {
			el.v = a[--top].v;
			strcpy_s(el.str, a[top].str);
		}
		return rc;
	}
	
	Stack& Stack::copy(const Stack& st)
	{
		Stack tmp(st);
		Cell el;
		while (tmp.pop(el) >= 0)
			push(el);
		return *this;
	}

	Stack& Stack::move(Stack& st)
	{
		Cell el;
		while (st.pop(el) >= 0)
			push(el);
		return *this;
	}

	int Stack::Status()
	{
		if (!top) {
			std::cout << "Stack is empty." << std::endl;
			return -1;
		}
		if (top < SZ) { 
			std::cout << "Stack is partially filled." << std::endl;
			return 1;
		}
		else {
			std::cout << "Stack is full." << std::endl;
			return 0;
		}
	}
	std::istream& operator>>(std::istream& s, Cell& c)
	{
		double v;
		char str[11];
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
		st.push(tmp);
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
