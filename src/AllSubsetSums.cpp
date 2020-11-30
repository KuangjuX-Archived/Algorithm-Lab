#include <iostream>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

struct solutionElement
{
	int num;
	int sum;
	solutionElement(int a, int b):num(a),sum(b){};
	bool operator < (const solutionElement& element)const
	{
		if(num == element.num)return sum < element.sum;
		else return num < element.num;
	}
};

//OP: Two Tuple op Two Tuple
set<solutionElement> OP(set<solutionElement> A, set<solutionElement> B, int u) {
 	set<solutionElement> C;
	for(set<solutionElement>::iterator i = A.begin(); i!=A.end(); i++) {
		for(set<solutionElement>::iterator j = B.begin(); j!=B.end(); j++) {
			if((*i).sum + (*j).sum <= u) {
				C.insert(solutionElement((*i).num+(*j).num, (*i).sum+(*j).sum));
			}
		}
	}
	return C;
}

vector<int> OP2(vector<int> A, vector<int> B, int u) {
	// int lenC = 0;
	// int* C = new int[lenA * lenB + 5];
	vector<int> C;
	for(int i = 0; i < A.size(); i++) {
		for(int j = 0; j < B.size(); j++) {
			if(A[i] + B[j] <= u) {
				cout<<"Ai:"<<A[i]<<endl;
				cout<<"Bj:"<<B[j]<<endl;
				C.push_back(A[i] + B[j]);
			}
		}
	}
	for(int i=0 ; i<C.size(); i++){
		cout<<"Ci:"<<C[i]<<endl;
	}
	return C;
}

//n: length of S
//input one tuple & output two tuple
set<solutionElement> AllSubsetSumsSharp(int S[], int u, int n) {
	if(n == 1) {
		set<solutionElement> res;
		res.insert(solutionElement(0,0));
		res.insert(solutionElement(1,S[0]));
		return res;
	}
	
	return OP(AllSubsetSumsSharp(S, u, n / 2), AllSubsetSumsSharp(S + n / 2, u, n - n / 2), u);
}

vector<solutionElement> SetToVector(set<solutionElement> object){
	vector<solutionElement> res;
	for(set<solutionElement>::iterator i = object.begin(); i != object.end(); i++){
		res.push_back(solutionElement((*i).num,(*i).sum));
	}
	return res;
}

vector<int> AllSubsetSums(int S[], int u, int n) {
	int b = sqrt(n * log2((float)n));
	//int** R = new int*[todo];
	//int* res = new int[todo];
	vector<vector<int>> R;
	vector<int> res;
	for(int l = 0; l <= b - 1; l++) {
		//int* Sl = new int[n + 5];
		//int lenSl = 0;
		//Sl <- S (cross) {}
		vector<int> S1;
		for(int i = 0; i < n; i++) {
			if(S[i] % b == l % b) {
				S1.push_back(S[i]);
			}
		}
		//check if type is integer
		//Ql <- {}
		//int* Ql = new int[lenSl];
		int* Q1 = new int[S1.size()+5];
		for(int i = 0; i < S1.size(); i++){
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
		if(l == 0)continue;
		else{
			for(int i = 0; i < l; i++) {
				Rl.push_back(SQ[i].sum * b + SQ[i].num * l);
			}
		}
		R.push_back(Rl);
	}
	res = R[0];
	for(int l = 0; l < b - 1; l++) {
		cout<<"123"<<endl;
		cout<<res[l]<<endl;
		res = OP2(res, R[l], l);
		cout<<res[l]<<endl;
		cout<<"456"<<endl;
	}
	return res;
}
int main()
{

	int A[] = {1, 2, 3, 4, 5};
	set<solutionElement> C = AllSubsetSumsSharp(A, 5, 5);
	cout<<"res: "<<endl;
	for(set<solutionElement>::iterator i = C.begin(); i!=C.end(); i++){
		cout<<(*i).num<<" "<<(*i).sum<<endl;
	}

	vector<int> res = AllSubsetSums(A, 5, 5);
	cout<<"res2: "<<endl;
	for(int i=0; i<res.size(); i++){
		cout<<res[i]<<" ";
	}
	cout<<endl;
		
}
