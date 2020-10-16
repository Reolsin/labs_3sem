#include "Stack.h"

namespace Stack_dynamic {

	void copy(char* dest, const char* source)
	{
		while (*source != '\0')
			*dest++ = *source++;
		*dest = '\0';
	}

	Cell::Cell(double d, const char* s) : v(d)
	{
		str = new char[strlen(s) + 1];
		copy(str, s);
	}

	Cell::Cell(const Cell& c) : v(c.v), str(c.str)
	{
		str = new char[strlen(c.str) + 1];
		copy(str, c.str);
	}

	Cell& Cell::operator=(const Cell& c)
	{
		v = c.v;
		delete[] str;
		str = new char[strlen(c.str) + 1];
		copy(str, c.str);
		return *this;
	}

	Cell& Cell::operator=(Cell&& c) noexcept
	{
		swap(v, c.v);
		swap(str, c.str);
		return *this;
	}

	Stack::Stack(const Stack& st) : top(st.top), SZ(st.SZ)
	{
		a = new Cell[SZ];
		for (int i = 0; i < top; i++)
			a[i] = st.a[i];
	}

	Stack::Stack(const Cell c[], int n) : top(0)
	{
		if (n >= 0) {
			SZ = (1 + n / Q) * Q;
			a = new Cell[SZ];
			while (top < n) {
				a[top] = c[top];
				top++;
			}
		}
		else throw std::exception("Second parametr cant be negative");
	}

	Stack& Stack::operator=(const Stack& S)
	{
		if (this != &S) {
			top = S.top;
			SZ = S.SZ;
			delete[] a;
			a = new Cell[SZ];
			for (int i = 0; i < top; i++)
				a[i] = S.a[i];
		}
		return *this;
	}

	Stack& Stack::operator=(Stack&& S) noexcept
	{
		swap(top, S.top);
		swap(SZ, S.SZ);
		swap(a, S.a);
		return *this;
	}

	Stack& Stack::operator+=(const Cell& c)
	{
		if (is_full()) {
			SZ += Q;
			Cell* tmp = a;
			a = new Cell[SZ];
			for (int i = 0; i < top; i++)
				a[i] = tmp[i];
			delete[] tmp;
		}
		a[top++] = c;
		return *this;
	}

	Stack& Stack::operator()(Cell& c)
	{
		if (not_empty())
			c = a[--top];
		else throw std::exception("Stack is empty!");
		return *this;
	}

	char* getstr(std::istream& s) {
		const int L = 5;
		char buf[L + 1];
		char* tmp, * ptr = nullptr;
		int n = 0, l = 0, i;
		do {
			s.get(buf, L + 1);
			l = strlen(buf);
			tmp = ptr;
			ptr = new char[n + l + 1];
			if (tmp)
				for (i = 0; i < n; i++)
					ptr[i] = tmp[i];
			delete[] tmp;
			for (i = n; i < n + l + 1; i++)
				ptr[i] = buf[i - n];
			n += l;
		} while (l == L);
		if (!s.good() && ptr) {
			s.ignore(1);
			s.clear();
		}
		return ptr;
	}

	std::istream& operator>>(std::istream& s, Cell& c)
	{
		double v;
		char* str = nullptr;
		s >> v; s.get();
		if (s.good())
			str = getstr(s);
		if (str)
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
		s << "Stack status -->> ";
		if (st.top == 0)
			s << "empty";
		else {
			for (int i = st.top - 1; i > 0; --i)
				s << st.a[i] << '|'; s << st.a[0];
		}
		return s;
	}
}
