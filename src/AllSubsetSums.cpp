#include "AllSubsetSums.h"


const double pi = 3.1415926535898;
int t, len = 1, l, r[maxn * 2];
Complex Aa[maxn * 2], Bb[maxn * 2], Cc[maxn * 2];




void fdft(Complex *a, int n, int flag)
{ //快速将当前多项式从系数表达转换为点值表达
	for (int i = 0; i < n; ++i)
		if (i < r[i])
			swap(a[i], a[r[i]]);
	for (int mid = 1; mid < n; mid <<= 1)
	{ //当前区间长度的一半
		Complex w1(cos(pi / mid), flag * sin(pi / mid)), x, y;
		for (int j = 0; j < n; j += (mid << 1))
		{ //j:区间起始点
			Complex w(1, 0);
			for (int k = 0; k < mid; ++k, w = w * w1)
			{ //系数转点值
				x = a[j + k], y = w * a[j + mid + k];
				a[j + k] = x + y;
				a[j + mid + k] = x - y;
			}
		}
	}
}

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
int GetMaxInt(vector<int> A)
{
	int Max = 0;
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] > Max)
			Max = A[i];
	}
	return Max;
}
vector<int> OP2(vector<int> A, vector<int> B, int u)
{
	// cout << "A max" <<  GetMaxInt(A) << endl;
	// cout << "B max" <<  GetMaxInt(B) << endl;
	vector<int> C;
	for (int i = 0; i <= GetMaxInt(A); i ++){
		Aa[i].x = 0;
	}
	for (int i = 0; i < A.size(); i ++){
		Aa[A[i]].x = 1;
	}
	
	for (int i = 0; i < GetMaxInt(B); i ++){
		Bb[i].x = 0;
	}
	for (int i = 0; i < B.size(); i ++){
		Bb[B[i]].x = 1;
	}
	while (len <= GetMaxInt(A) + GetMaxInt(A)){
		len <<= 1, ++l;	
		}		  //idft需要至少l1+l2个点值
	for (int i = 0; i < len; ++i){ //编号的字节长度为l
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	}
	fdft(Aa, len, 1);
	fdft(Bb, len, 1);
	for (int i = 0; i < len; ++i)
		Cc[i] = Aa[i] * Bb[i];
	fdft(Cc, len, -1); //idft
	for (int i = 0; i <= u; i ++){
		if( int(Cc[i].x / len + 0.5) != 0 ){
			C.push_back(i);
		}
	}
	return C;
}

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
	vector<vector<int> > R;
	vector<int> res;
	for (int l = 0; l <= b - 1; l++)
	{
		vector<int> S1;
		for (int i = 0; i < n; i++)
		{
			if (S[i] % b == l % b)
			{
				S1.push_back(S[i]);
			}
		}
		int *Q1 = new int[S1.size() + 5];
		for (int i = 0; i < S1.size(); i++)
		{
			Q1[i] = (S1[i] - l) / b;
		}

		vector<solutionElement> SQ;
		SQ = SetToVector(AllSubsetSumsSharp(Q1, (int)(u / b), S1.size()));
		vector<int> Rl;
		for (int i = 0; i < SQ.size(); i++)
		{
			Rl.push_back(SQ[i].sum * b + SQ[i].num * l);
		}
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
