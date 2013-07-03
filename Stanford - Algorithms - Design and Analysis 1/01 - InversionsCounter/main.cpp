#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

unsigned long findInversions(vector<long>& input);

int main()
{
    std::vector<long> inputData(0);

    ifstream infile("IntegerArray.txt");

    string buf;
    long value;
    stringstream str_str;

    while (!infile.eof())
    {
        buf.clear();

        infile >> buf;



        if (buf.length() == 0)
           continue;

        str_str << buf;

        str_str >> value;
        str_str.clear();

        inputData.push_back(value);
    }

    unsigned long inversions = findInversions(inputData);

    cout << "Number of inversions: " << inversions << endl;

    getchar();

    return 0;
}


unsigned long findInversions(vector<long>& input)
{
    int size = input.size();

	if (size <= 1)
		return 0L;

    unsigned long inversions = 0;

	vector<long> subset1(size/2);
	vector<long> subset2(size - size/2);

	copy(input.begin(), input.begin() + subset1.size(), subset1.begin());
	copy(input.begin() + subset1.size(), input.end(), subset2.begin());

	inversions += findInversions(subset1);

	inversions += findInversions(subset2);


    int size1 = subset1.size();
    int size2 = subset2.size();

    int i = 0, j = 0, c = 0;

    while (i < size1 && j < size2)
    {
        if (subset1[i] < subset2[j])
        {
            input[c++] = subset1[i++];
            continue;
        }
        else
        {
            input[c++] = subset2[j++];
            inversions += size1 - i;
        }
    }

    while (i < size1 && c < size)
      input[c++] = subset1[i++];

    while (j < size2 && c < size)
      input[c++] = subset2[j++];

    return inversions;
}
