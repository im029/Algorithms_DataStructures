#include <vector>
#include <iostream>

/**
	count_sort.hpp
	purpose: sorts a vector using count sort
	@author: Ishant Malik; Algorithm taken from CLRS
	@version: 1.0.0 08/04/2018
*/
void count_sort(std::vector<std::vector<int > *> *const arr, std::vector<std::vector<int> *> *const arr2, const int key)
{
	// variable to store range of numbers at given place value. initally we assume that first one is the range
	int k = arr->at(0)->at(key);
	// find the range by finding maximum of the elements at given place value
	for (unsigned int i = 1; i < arr->size(); i++)
		if (k < arr->at(i)->at(key))
			k = arr->at(i)->at(key);

	// create an auxiliary array and initally set elements to zero
	std::vector<int> aux_array;
	for (int i = 0; i <= k; i++)
		aux_array.push_back(0);
	
	// count the numbers.
	for (int j = 0; j < arr->size(); j++)
		aux_array[arr->at(j)->at(key)] = aux_array[arr->at(j)->at(key)] + 1;

	// cumulate the values
	for (int i = 1; i <= k; i++)
		aux_array[i] = aux_array[i] + aux_array[i - 1];


	// sort the values by placing them at correct positions in array B
	for (int j = arr->size() - 1; j >= 0; j--)
	{
		arr2->at(aux_array[arr->at(j)->at(key)] - 1) = arr->at(j);
		aux_array[arr->at(j)->at(key)] = aux_array[arr->at(j)->at(key)] - 1;
	}

	//reorder the arr1 to match arr2 for next iteration
	for (int i = 0; i < arr2->size(); i++)
		arr->at(i) = arr2->at(i);
}