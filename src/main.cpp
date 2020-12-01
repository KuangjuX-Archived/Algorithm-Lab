#include "AllSubsetSums.h"
using namespace std;

inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}

int main()
{
	//initialize
	// int u = 10;
	// int A[] = {2,3,6,9,10};
	// int Size = sizeof(A) / sizeof(*A);
	cout<<"Please enter q to quit and c to continue:\n";
	char c; 
	int Size,u;
	c = getchar();
	while(c != 'q'){
		cout<<"Please enter the size of set:\n";
		Size = read();
		int* A = new int[Size];
		cout<<"Please enter the positive numbers of the set\n";
		for(int i = 0 ; i<Size; i++){
			A[i] = read();
		}
		cout<<"Please enter the up to the set:\n";
		u = read();

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
		cout<<"Please enter q to quit and c to continue:\n";
		c = getchar();
	}

	

	//test for OP2
	// int q[] = {0, 3, 4};
	// vector<int> a(q, q + 3);

	// int w[] = {0, 2, 6, 5};
	// vector<int> b(w, w + 4);
	// vector<int> c = OP2(a, b, 10);
	cout<<"\033[35mBye~ \033[34mBye~\033[0m \n";
	system("pause");
	return 0;
}