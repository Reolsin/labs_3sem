#include <iostream>
#include "../my_vector/My_vector.h"
#include "conio.h"


using My_vect::My_vector;

class Menu {
	std::string pointer;
	My_vector<std::string> messages;
	void show(int);

public:
	Menu(My_vector<std::string> msgs, std::string p = "<") : \
		messages(msgs), pointer(p) {}

	int get_recall();

	inline bool is_last(int n) { return n == messages.size() - 1; }
};
