#include "Menu.h"

void Menu::show(int pos)
{
	for (int i = 0, n = (60 - messages.size()) / 2; i < n; i++)
		std::cout << std::endl;
		for (size_t i = 0; i < messages.size(); i++) {
		std::cout << messages[i];
		if (pos == i)
			std::cout << pointer;
		std::cout << std::endl;
	}
}

int Menu::get_recall()
{
	int rc = 0;
	int switcher;
	system("cls");
	do {
		show(rc);
		switcher = _getch();
		if (switcher == 224)
			switcher = _getch();
		switch (switcher) {
		case 72:
			rc = (messages.size() + rc - 1) % messages.size();
			break;
		case 80:
			rc = (messages.size() + rc + 1) % messages.size();
			break;
		}
		system("cls");
	} while (switcher != 13);
		return rc;
}
