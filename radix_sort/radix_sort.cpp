#include "headers\count_sort_rad.hpp"
#include <cmath>

// store integer as a vector
std::vector<int> *store(int, const int);

int main(void) 
{
	// these are our two arrays which will be used to sort
	std::vector<std::vector<int> *> A;
	std::vector<std::vector<int> *> B;

	std::cout << "How many elements you want to sort? " << std::endl;
	int n;
	std::cin >> n;

	// ask for the range from user
	std::cout << "What is the range of elements? " << std::endl;
	int k;
	std::cin >> k;

	// get the number of digits in range
	int no_of_digits = log10(k) + 1;


	// store the number in vector
	std::cout << "Enter " << n << " elements" << std::endl;
	for (int i = 0; i < n; i++)
	{
		int num;
		std::cin >> num;

		if (num > k)
		{
			std::cout << "Element is larger than range." << std::endl;
			// free allocated memory
			for (int i = 0; i < A.size(); i++)
				delete A[i];
			return -1;
		}

		A.push_back(store(num, no_of_digits));
	}

	// resize B to match size of A
	B.resize(A.size());

	// sort the place value using count_sort. i is the place value
	for (int i = 0; i < no_of_digits; i++)
		count_sort(&A, &B, i);

	// display sorted vector
	std::cout << "Numbers after Sorting" << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = A[i]->size() - 1; j >= 0; j--)
			std::cout << A[i]->at(j);
		std::cout << " ";
	}
	std::cout << std::endl;
	system("pause");

	// free allocated memory
	for (int i = 0; i < A.size(); i++)
		delete A[i];
	return 0;
}

// function to store data
std::vector<int> *store(int num, const int no_of_digits)
{
	// create temporary vector to store the num
	std::vector<int> *temp = new  std::vector<int>;
	// resize so that number fits into this vector. this also pads the digit if required.
	temp->resize(no_of_digits);
	int i = 0;
	// store the number in reverse order i.e. if number is 547 store it as 745
	while (num)
	{
		int d = num % 10;
		num = num / 10;
		temp->at(i) = d;
		i++;
	}
	return temp;
}