#include "../Library_static/Stack.h"

int dialog(const char* msgs[], int N)
{
	int rc;
	do {
		system("cls");
		for (int i = 0; i < N; i++)
			std::cout << msgs[i] << std::endl;
		std::cin >> rc; std::cin.ignore(1);
	} while (!std::cin.good());
	return rc;
}

int main()
{
	const char* msgs[] = { "0.Quit", "1.Pop", "2.Push", "3.Status", "4.Get SZ", "5.Get top", "6.Print" };
	int rc;
	Stack_static::Stack S;
	Stack_static::Cell c;
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
			try {
				std::cin >> S;
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
			}
			break;
		case 3:
			std::cout << "not full: " << S.not_full() << std::endl;
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
