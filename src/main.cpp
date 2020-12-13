#include "AllSubsetSums.h"
#include <cstdio>
#include <sstream>
#include <sys/time.h>
#include <ctime>
using namespace std;

// #define DEBUG
#define TEST

#define MAX (1<<16)
#define TIMECOVERT ((double)1e6)
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
		freopen("../testcases/time.txt","w+",stdout);
		while(!feof(file)){
			for(int i=0; i<3; i++){
				char* size = new char[4];
				int SIZE = atoi(fgets(size,4,file));
				char* up = new char[10];
				int UP = atoi(fgets(up,10,file));
				char* buffer = new char[MAX];
				fgets(buffer,MAX,file);
				int* S = new int[SIZE+5];
				std::istringstream stringStream(buffer);

				for (size_t i = 0; (i < SIZE) && (stringStream >> S[i]); ++i) {}
				// printf("The number of the set:%d\n",SIZE);
				struct timeval start_time, end_time;
				// cout<<SIZE<<endl;
				// cout<<UP<<endl;
				// printf("%d ",SIZE);
				gettimeofday(&start_time,NULL);
				set<int> res = FilterRepeatingInt(AllSubsetSums(S,UP,SIZE));
				gettimeofday(&end_time,NULL);
				long long int start,end;
				start = start_time.tv_sec*TIMECOVERT+start_time.tv_usec;
				end = end_time.tv_sec*TIMECOVERT+end_time.tv_usec;
				long double span_time;
				span_time = (end-start)/(TIMECOVERT);
				// printf("%d %.6LFs\n", SIZE, span_time);
				cout<<SIZE<<" "<<span_time<<endl;

				// cout << "The set of all realizable subset sums of S up to " << UP << " is: \n";
			// 	for (set<int>::iterator i = res.begin(); i != res.end(); i++)
			// 	{
			// 		cout<<*i<<" ";
			// 	}
			// 	cout<<endl;
			}
		}
		fclose(file);

#endif
	

	cout<<"\033[35mBye~ \033[34mBye~\033[0m \n";
	system("pause");
	return 0;
}