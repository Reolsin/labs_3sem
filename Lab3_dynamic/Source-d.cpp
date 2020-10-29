#include "../Library_dynamic/Stack.h"

int getint(std::istream& s)
{
	int n;
	const char* err = "";
	do {
		std::cout << err;
		err = "Error. Enter number.\n";
		s.clear();
		s.ignore(s.rdbuf()->in_avail());
		s >> n;
	} while (!s.good());
	s.get();
	return n;
}

int getindex_in_range(int start, int end) {
	int i;
	const char* msg = "";
	do {
		std::cout << msg;
		i = getint(std::cin);
		msg = "Error out of range\n";
	} while ((i < start) || (i > end));
	return i;
}

int dialog(const char* msgs[], int N)
{
	int rc;
	do {
		system("cls");
		for (int i = 0; i < N; i++)
			std::cout << msgs[i] << std::endl;
		rc = getint(std::cin);
	} while (!std::cin.good());
	return rc;
}

int main()
{
	const char* msgs[] = { "0.Quit", "1.Pop", "2.Push", "3.Status", "4.Get SZ", "5.Get top", "6.Print" };
	int rc;
	int n;
	Stack_dynamic::Stack S;
	Stack_dynamic::Cell c;
	while (rc = dialog(msgs, 7)) {
		switch (rc) {
		case 1:
			try {
				S(c);
				std::cout << c << std::endl;
			}
			catch (std::exception& e) { std::cout << e.what() << std::endl; }
			break;
		case 2:
			std::cout << "Enter number of cells to add:" << std::endl;
			n = getindex_in_range(0, INT_MAX);
			for (int i = 0; i < n; i++) {
				try {
					std::cin >> S;
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					i--;
				}
			}
			break;
		case 3:
			std::cout << "is full: " << S.is_full() << std::endl;
			std::cout << "not empty: " << S.not_empty() << std::endl;
			break;
		case 4:
			std::cout << S.getSZ() << std::endl;
			break;
		case 5:
			std::cout << S.gettop() << std::endl;
			break;
		case 6:
			std::cout << S << std::endl;
			break;
		default:
			std::cout << "Incorrect input." << std::endl;
			break;
		}
		std::cout << "Type any symbol to continue..."; std::cin.get();
	}
	return 0;
}
