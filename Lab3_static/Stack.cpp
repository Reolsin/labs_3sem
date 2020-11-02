#include "Stack.h"

namespace Stack_static {

	bool Cell::string_is_correct(const char* s) // why const char* and not just char* ?
	{
		int i = 0;
		while ((*(s) != '\0') && (i++ < (len + 1)))
			s++;
		if (*(s))
			return false;
		return true;
	}

	Cell::Cell(double d, const char s[len + 1]) : v(d) //  using char array as an argument is risky
	{
		if (string_is_correct(s))
			strcpy_s(str, s);
		else throw std::exception("Failed to add string to structure!");
	}

	Stack::Stack(const Cell c[], int n) : top(0) // would be better to user pointer to the array
	{
		if ((n >= 0 ) && (n <= SZ))
			while(top < n)
				a[top] = c[top++];
		else throw std::exception("Int parameter is out of range!");
	}

	Stack& Stack::operator+=(const Cell& c)
	{
		if (not_full()) // really cool
			a[top++] = c;
		else throw std::exception("Stack overflow!");
		return *this;
	}

	Stack& Stack::operator()(Cell& c)
	{
		if (not_empty()) //really cool
			c = a[--top];
		else throw std::exception("Stack is empty!");
		return *this;
	}

	std::istream& operator>>(std::istream& s, Cell& c)
	{
		double v;
		char str[c.len+1];
		s >> v; 
		s.get();
		s.getline(str, c.len + 1);
		if (s.good())
			c = Cell(v, str);
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
			for (int i = st.top - 1; i > 0; --i) // will it work if st.top == 1? 
				s << st.a[i] << '|' << st.a[0];
		}
		return s;
	}
}
