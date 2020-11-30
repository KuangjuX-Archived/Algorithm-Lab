#include <iostream>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

struct solutionElement
{
	int num;
	int sum;
	solutionElement(int a, int b) : num(a), sum(b){};
	bool operator<(const solutionElement &element) const
	{
		if (num == element.num)
			return sum < element.sum;
		else
			return num < element.num;
	}
};

//OP: Two Tuple op Two Tuple
set<solutionElement> OP(set<solutionElement> A, set<solutionElement> B, int u)
{
	set<solutionElement> C;
	for (set<solutionElement>::iterator i = A.begin(); i != A.end(); i++)
	{
		for (set<solutionElement>::iterator j = B.begin(); j != B.end(); j++)
		{
			if ((*i).sum + (*j).sum <= u)
			{
				C.insert(solutionElement((*i).num + (*j).num, (*i).sum + (*j).sum));
			}
		}
	}
	return C;
}

vector<int> OP2(vector<int> A, vector<int> B, int u)
{
	// int lenC = 0;
	// int* C = new int[lenA * lenB + 5];
	vector<int> C;
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			if (A[i] + B[j] <= u)
			{
				C.push_back(A[i] + B[j]);
			}
		}
	}
	// for(int i=0 ; i<C.size(); i++){
	// 	cout<<"Ci:"<<C[i]<<endl;
	// }
	return C;
}

//n: length of S
//input one tuple & output two tuple
set<solutionElement> AllSubsetSumsSharp(int S[], int u, int n)
{
	if (n == 1)
	{
		set<solutionElement> res;
		res.insert(solutionElement(0, 0));
		res.insert(solutionElement(1, S[0]));
		return res;
	}

	return OP(AllSubsetSumsSharp(S, u, n / 2), AllSubsetSumsSharp(S + n / 2, u, n - n / 2), u);
}

vector<solutionElement> SetToVector(set<solutionElement> object)
{
	vector<solutionElement> res;
	for (set<solutionElement>::iterator i = object.begin(); i != object.end(); i++)
	{
		res.push_back(solutionElement((*i).num, (*i).sum));
	}
	return res;
}

set<int> FilterRepeatingInt(vector<int> obj)
{
	set<int> res;
	for (int i = 0; i < obj.size(); i++)
	{
		res.insert(obj[i]);
	}
	return res;
}

vector<int> AllSubsetSums(int S[], int u, int n)
{
	int b = sqrt(n * log2((float)n));
	//int** R = new int*[todo];
	//int* res = new int[todo];
	vector<vector<int>> R;
	vector<int> res;
	for (int l = 0; l <= b - 1; l++)
	{
		//int* Sl = new int[n + 5];
		//int lenSl = 0;
		//Sl <- S (cross) {}
		vector<int> S1;
		for (int i = 0; i < n; i++)
		{
			if (S[i] % b == l % b)
			{
				S1.push_back(S[i]);
			}
		}
		//check if type is integer
		//Ql <- {}
		//int* Ql = new int[lenSl];
		int *Q1 = new int[S1.size() + 5];
		for (int i = 0; i < S1.size(); i++)
		{
			Q1[i] = (S1[i] - l) / b;
		}

		vector<solutionElement> SQ;
		SQ = SetToVector(AllSubsetSumsSharp(Q1, (int)(u / b), S1.size()));
		/*debug*/
		// for(int i = 0; i<SQ.size(); i++){
		// 	cout<<"SQ1:"<<endl;
		// 	cout<<SQ[i].sum<<endl;
		// }

		//Rl <- {}
		//int* Rl = new int[l];
		vector<int> Rl;
		// cout<<"l:"<<l<<endl;
		// if(l == 0)continue; //hasuer comment
		// else{ //hasuer comment
		for (int i = 0; i < SQ.size(); i++)
		{
			Rl.push_back(SQ[i].sum * b + SQ[i].num * l);
		}
		// } //hasuer comment
		R.push_back(vector<int>(Rl));
	}

	res = R[0];
	for (int l = 0; l < b - 1; l++)
	{
		//cout<<R[l]<<endl;
		res = OP2(res, R[l + 1], u);
		//cout<<R[l]<<endl;
	}
	return res;
}
int main()
{
	//initialize
	int u = 5;
	int A[] = {1, 4, 5, 6, 9};
	int Size = sizeof(A) / sizeof(*A);
	
	// test for AllSubsetSumsSharp
	set<solutionElement> C = AllSubsetSumsSharp(A, Size, u);
	cout << "The set of all realizable subset sums along with the size of the subset that realizes each sum of S up to " << u << " is: \n";
	cout << "size    sum\n";
	cout << "-----------\n";
	for (set<solutionElement>::iterator i = C.begin(); i != C.end(); i++)
	{
		cout << " " <<(*i).num << "       " << (*i).sum << endl;
	}

	// test for AllSubsetSums
	set<int> res = FilterRepeatingInt(AllSubsetSums(A, 5, 5));
	cout << "The set of all realizable subset sums of S up to " << u << " is: \n";
	for (set<int>::iterator i = res.begin(); i != res.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
