#include "rb_tree.h"

int main(void)
{
	rb_tree t;

	char ch = 'y';
	while (ch == 'y' || ch == 'Y')
	{
		std::cout << "\tWhat do you want to do?" << std::endl;
		std::cout << "1. Insert into tree" << std::endl;
		std::cout << "2. Print Inorder" << std::endl;
		std::cout << "3. Search" << std::endl << std::endl;

		std::cout << "Enter choice: ";
		
		int sel;
		std::cin >> sel;

		int ele;
		switch (sel)
		{
		case 1:
			std::cout << std::endl << "Enter the element you want to insert: ";
			std::cin >> ele;
			t.rb_insert(ele);
			break;
		case 2:
			std::cout << std::endl;
			t.print();
			std::cout << std::endl << std::endl;
			break;
		case 3:
			std::cout << std::endl << "Enter the element you want to search: ";
			std::cin >> ele;
			t.search(ele);
			break;
		default:
			std::cout << "Invalid choice" << std::endl;
			break;
		}

		std::cout << "Do you want to continute (Y/N)? ";
		std::cin >> ch;
		std::cout << std::endl;
	}
}