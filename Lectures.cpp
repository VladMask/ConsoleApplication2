#include <iostream>
#include <fstream>

using namespace std;

int DaysNumber(string month, int year) // getting numer of days in appropriate month by it's name
{
	if ((month == "January,") or (month == "December,") or (month == "August,") or
		(month == "July,") or (month == "May,") or (month == "March,") or (month == "October,"))
		return 31;
	else if (month == "February,")
		if (((year % 4 == 0) and (year % 100 != 0)) or (year % 400 == 0))
			return 29;
		else
			return 28;
	else if ((month == "April,") or (month == "June,") or (month == "September,") or (month == "November"))
		return 30;
	
}

double* GetData(string file_name, int* arr_size)
{
	ifstream fin;					//definig input file
	fin.open(file_name);			//opening file

	fin.ignore(255, '\n');			// ignoring first two lines
	fin.ignore(255, '\n');

	string month;
	int year;

	fin >> month;
	fin >> year;

	int size;

	size = DaysNumber(month, year) + 1;			// getting number of days to create array with right size

	*arr_size = size;						// retuning to main size of array

	double* data = new double[size];		// creating array of data
	for (int i = 0; i < size; i++)			
	{
		data[i] = -1;
	}

	bool* flags = new bool[size];			// array of flags for checking repeated data
	for (int i = 0; i < size; i++)
	{
		flags[i] = false;
	}

	int i, j;	//array of errors would have 0 or 1 if data invalid or repeated
					//lines ord_num and wrong data
	i = 1;
	j = 3;
	int* errors = new int[i * j];           // array for handling errors
	int ln_order_number = 4;				// line's order number. Using to recognize error lines

	while (!fin.eof())						//reading data from file
	{
		int index;
		int temp_ind;
		fin >> temp_ind;
		if (temp_ind <= size - 1)
		{
			if (!flags[temp_ind])
			{
				index = temp_ind;
				fin >> data[index];
				flags[index] = true;
				cout << index << "\t" << data[index] << "\n";
				ln_order_number++;
			}
			else
			{
				i++;
				errors[(i - 1) * 0] = 1;
				errors[(i - 1) * 1] = temp_ind;
				errors[(i - 1) * 2] = ln_order_number;
				//cout << "\n\nHERE ERRORS \t" << errors[(i - 1) * 0] << "\t" << errors[(i - 1) * 1] << "\t" << errors[(i - 1) * 2] << "\tRepeated" << "\n\n";
				fin.ignore(255, '\n');
				ln_order_number++;
			}
		}
		else
		{
			i++;
			errors[(i - 1) * 0] = 0;
			errors[(i - 1) * 1] = temp_ind;
			errors[(i - 1) * 2] = ln_order_number;
			//cout << "\n\nHERE ERRORS \t" << errors[(i - 1) * 0] << "\t" << errors[(i - 1) * 1] << "\t" << errors[(i - 1) * 2] << "\tOut of range" << "\n\n";
			fin.ignore(255, '\n');
			ln_order_number++;
		}
	}
	fin.close();
	return data;
}

float AverageValue(double* data, int size)
{
	float sum = 0;
	for (int i = 1; i < size; i++)
	{
		if (data[i] != -1.0)
			sum += data[i];
	}
	return sum / (size - 1);
}

double MaxValue(double* data, int size)
{
	double max = -1000;
	for (int i = 0; i < size; i++) 
	{
		if (data[i] > max)
			max = data[i];
	}
	return max;
}

double MinValue(double* data, int size)
{
	double min = 1000;
	for (int i = 0; i < size; i++)
	{
		if (data[i] != -1)
			if (data[i] < min)
				min = data[i];
	}
	return min;
}

int main()
{
	int size;
	double* data;			//pointer on array of data
	
	data = GetData("Precip.txt", &size);		// getting aray of data from file	
	//cout << "\n\n\n" << AverageValue(data, size);
	//cout << "\n\n\n" << MaxValue(data, size);
	//cout << "\n\n\n" << MinValue(data, size);
	
}