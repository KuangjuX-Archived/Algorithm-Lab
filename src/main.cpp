#include "AllSubsetSums.h"
using namespace std;

int main()
{
	//initialize
	int u = 10;
	int A[] = {2,3,6,9,10};
	int Size = sizeof(A) / sizeof(*A);

	// test for AllSubsetSumsSharp
	set<solutionElement> C = AllSubsetSumsSharp(A, u, Size);
	cout << "The set of all realizable subset sums along with the size of the subset that realizes each sum of S up to " << u << " is: \n";
	cout << "size    sum\n";
	cout << "-----------\n";
	for (set<solutionElement>::iterator i = C.begin(); i != C.end(); i++)
	{
		cout << " " << (*i).num << "       " << (*i).sum << endl;
	}

	//test for AllSubsetSums
	set<int> res = FilterRepeatingInt(AllSubsetSums(A, u, Size));
	cout << "The set of all realizable subset sums of S up to " << u << " is: \n";
	for (set<int>::iterator i = res.begin(); i != res.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	//test for OP2
	// int q[] = {0, 3, 4};
	// vector<int> a(q, q + 3);

	// int w[] = {0, 2, 6, 5};
	// vector<int> b(w, w + 4);
	// vector<int> c = OP2(a, b, 10);
	system("pause");
	return 0;
}