#include <iostream>
#include <algorithm>
#include <vector>

int main(void)
{
	std::cout << "How many integers are there? ";
	int n;
	std::cin >> n;

	std::vector<int> arr(n);
	
	std::cout << "Enter integers: ";
	for (int i = 0; i < n; i++)
		std::cin >> arr[i];
	
	std::cout << "Enter the given sum S: ";
	int sum;
	std::cin >> sum;
	
	bool m[n+1][sum+1];
	for (int j = 0; j < n; j++)
		m[j][0] = false;
	for (int j = 0; j < sum; j++)
		m[0][j] = false;

	for (int i = 1; i < n; i++)
		for (int j = 0; j < sum; j++)
			if (arr[i] > j)
				m[i][j] = false;
			else
				m[i][j] = m[i - 1][j - arr[i]];

	if (m[n][sum])
		std::cout << "Subset exists." << std::endl;
	else
		std::cout << "Subset does not exist." << std::endl;

	return 0;
}