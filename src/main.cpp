#include "AllSubsetSums.h"
#include <cstdio>
#include <sstream>
using namespace std;

#define DEBUG
// #define TEST

#define MAX (1<<16)
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}

string readTillSpace(char* buffer){
	string s;
	int i=0;
	while(buffer[i]!=' '){
		s+=buffer[i];
		i++;
	}
	return s;
}

int main()
{
#ifdef DEBUG

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
#endif

#ifdef TEST

		FILE* file = fopen("../testcases/example.txt","r");
		// freopen("../testcases/result.txt","w+",stdout);
		while(!feof(file)){
			// char * buffer = new char[MAX];
			// fgets(buffer,MAX,file);
			// printf("%s",buffer);
			for(int i=0; i<3; i++){
				char* size = new char[4];
				int SIZE = atoi(fgets(size,4,file));
				char* up = new char[10];
				int UP = atoi(fgets(up,10,file));
				char* buffer = new char[MAX];
				fgets(buffer,MAX,file);
				// printf("%d\n",SIZE);
				// printf("%d\n",UP);
				// printf("%s\n",buffer);
				int* S = new int[SIZE+5];
				std::istringstream stringStream(buffer);

				for (size_t i = 0; (i < SIZE) && (stringStream >> S[i]); ++i) {}
				for(int i = 0;i<SIZE;i++){printf("%d ",S[i]);}
				printf("\n");
				set<int> res = FilterRepeatingInt(AllSubsetSums(S,UP,SIZE));
				cout << "The set of all realizable subset sums of S up to " << UP << " is: \n";
				for (set<int>::iterator i = res.begin(); i != res.end(); i++)
				{
					cout << *i << " ";
				}
				cout << endl;
			}
		}
		fclose(file);

#endif
	

	cout<<"\033[35mBye~ \033[34mBye~\033[0m \n";
	system("pause");
	return 0;
}