#include "AllSubsetSums.h"
#define maxn ((int)2e6+5)
const double pi = 3.1415926535898;
int t, len = 1, l, r[maxn * 2];

using namespace std;

void FFT(Complex *a, int n, int flag,int *order)
{ //快速将当前多项式从系数表达转换为点值表达
	for (int i = 0; i < n; ++i)
		if (i < order[i])
		swap(a[i], a[order[i]]);
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

int GetMaxNum(set<solutionElement> A)
{
	int Max=0;
	for (auto i = A.begin(); i != A.end(); i++)
		{
			if((*i).num > Max)
				{
					Max = (*i).num;
				}
		}
	return Max;
}


int GetMaxSum(set<solutionElement> A)
{
	int Max=0;
	for (auto i = A.begin(); i != A.end(); i++)
		{
			if((*i).sum > Max)
				{
					Max = (*i).sum;
				}
		}
	return Max;
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


//OP: Two Tuple op Two Tuple
set<solutionElement> OP(set<solutionElement> A, set<solutionElement> B, int u)
{
	// set<solutionElement> C;
	// for (set<solutionElement>::iterator i = A.begin(); i != A.end(); i++)
	// {
	// 	for (set<solutionElement>::iterator j = B.begin(); j != B.end(); j++)
	// 	{
	// 		if ((*i).sum + (*j).sum <= u)
	// 		{
	// 			C.insert(solutionElement((*i).num + (*j).num, (*i).sum + (*j).sum));
	// 		}
	// 	}
	// }
	// return C;
	set<solutionElement> C;
	int Sizesum = 1, Sizenum=1, l=0,l2=0;
	int* r = new int[maxn * 2];
	int* r2 = new int[maxn * 2];
	int MaxSum=GetMaxSum(A)+GetMaxSum(B);
	int MaxNum=GetMaxNum(A)+GetMaxNum(B);
	
	while (Sizesum <= MaxSum){
		Sizesum <<= 1, ++l;	
	}		  //对于和，FTT需要至少MaxSum个点值
	for (int i = 0; i < Sizesum; ++i){ //编号的字节长度为l
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	}
	
	while (Sizenum <= MaxNum){
		Sizenum <<= 1, ++l2;	
	}		  //对于个数，FFT需要至少MaxNum个点值
	for (int i = 0; i < Sizenum; ++i){ //编号的字节长度为l
		r2[i] = (r2[i >> 1] >> 1) | ((i & 1) << (l2 - 1));
	}
	
	Complex* Aa = new Complex[Sizesum];
	Complex* Bb = new Complex[Sizenum];//Aa，Bb为临时一维数组
	Complex **arrayA=new Complex*[Sizenum];
	for(int i=0;i<Sizenum;i++)
		arrayA[i]=new Complex[Sizesum];
	Complex **arrayB=new Complex*[Sizenum];
	for(int i=0;i<Sizenum;i++)
		arrayB[i]=new Complex[Sizesum];
	Complex **arrayC=new Complex*[Sizenum];
	for(int i=0;i<Sizenum;i++)
		arrayC[i]=new Complex[Sizesum];//二维复数矩阵
	
	for (int i = 0; i < Sizenum; i ++){
		for(int j=0; j< Sizesum; j++) {
			arrayA[i][j].x=0;
		}
	}
	for (set<solutionElement>::iterator i = A.begin(); i != A.end(); i++){
		arrayA[(*i).num][(*i).sum]=1;
	}
	//初始化
	for (int i = 0; i < Sizenum; i ++){
		for(int j=0; j< Sizesum; j++) {
			arrayB[i][j].x=0;
		}
	}
	
	for (set<solutionElement>::iterator i = B.begin(); i != B.end(); i++){
		arrayB[(*i).num][(*i).sum]=1;
	}
	//对arrayA行进行FFT
	for (int i=0; i < Sizenum; i++){
		for(int j=0; j < Sizesum; j++) {
			Aa[j]=arrayA[i][j];
		}
		FFT(Aa, Sizesum, 1, r);
		for(int j=0; j < Sizesum; j++) {
			arrayA[i][j]=Aa[j];
		}
	}
	//对arrayA列进行FFT
	for (int i=0; i < Sizesum; i++){
		for(int j=0; j < Sizenum; j++) {
			Bb[j]=arrayA[j][i];
		}
		FFT(Bb, Sizenum, 1, r2);
		for(int j=0; j < Sizenum; j++) {
			arrayA[j][i]=Bb[j];
		}
	}
	//对arrayB行进行FFT
	for (int i=0; i < Sizenum; i++){
		for(int j=0; j < Sizesum; j++) {
			Aa[j]=arrayB[i][j];
		}
		FFT(Aa, Sizesum, 1, r);
		for(int j=0; j < Sizesum; j++) {
			arrayB[i][j]=Aa[j];
		}
	}
	//对arrayB列进行FFT
	for (int i=0; i < Sizesum; i++){
		for(int j=0; j < Sizenum; j++) {
			Bb[j]=arrayB[j][i];
		}
		FFT(Bb, Sizenum, 1, r2);
		for(int j=0; j < Sizenum; j++) {
			arrayB[j][i]=Bb[j];
		}
	}
	//两个矩阵对应值积
	for (int i=0; i < Sizenum; i++){
		for(int j=0; j < Sizesum; j++) {
			arrayC[i][j]=arrayA[i][j] * arrayB[i][j];
		}
	}
	//对arrayC行进行IFFT
	for (int i=0; i < Sizenum; i++){
		for(int j=0; j < Sizesum; j++) {
			Aa[j]=arrayC[i][j];
		}
		FFT(Aa, Sizesum, -1, r);
		for(int j=0; j < Sizesum; j++) {
			arrayC[i][j]=Aa[j];
		}
	}
	//对arrayC列进行IFFT
	for (int i=0; i < Sizesum; i++){
		for(int j=0; j < Sizenum; j++) {
			Bb[j]=arrayC[j][i];
		}
		FFT(Bb, Sizenum, -1, r2);
		for(int j=0; j < Sizenum; j++) {
			if(int(Bb[j].x / (Sizesum * Sizenum) + 0.5) != 0) {
				solutionElement temp(j,i);
				C.insert(temp);
			}
		}
	}
	
	for(int i=0; i < MaxNum; i++)
		delete[] arrayA[i];
	delete[] arrayA;
	for(int i=0; i < MaxNum; i++)
		delete[] arrayB[i];
	delete[] arrayB;
	for(int i=0; i < MaxNum; i++)
		delete[] arrayC[i];
		
	delete[] arrayC;
	delete[] Aa;
	delete[] r;
	delete[] r2;
	return C;
}


vector<int> OP2(vector<int> A, vector<int> B, int u)
{
	int l=0,len=1;
	int* r = new int[maxn * 2];
	Complex* Aa = new Complex[maxn*2];
	Complex* Bb = new Complex[maxn*2];
	Complex* Cc = new Complex[maxn*2];
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
	while (len <= GetMaxInt(A) + GetMaxInt(B)){
		len <<= 1, ++l;	
	}		  //idft需要至少l1+l2个点值
	for (int i = 0; i < len; ++i){ //编号的字节长度为l
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	}
	FFT(Aa, len, 1,r);
	FFT(Bb, len, 1,r);
	for (int i = 0; i < len; ++i)
		Cc[i] = Aa[i] * Bb[i];
	FFT(Cc, len, -1,r); //idft
	for (int i = 0; i <= u; i ++){
		if( int(Cc[i].x / len + 0.5) != 0 ){
			C.push_back(i);
		}
	}
	delete[] Aa;
	delete[] Bb;
	delete[] Cc;
	delete[] r;
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

	if(n == 0){
		set<solutionElement> res;
		res.insert(solutionElement(0,0));
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

vector<int> SetIntToVector(set<int> obj)
{
	vector<int> res;
	int j = 0;
	for (set<int>::iterator iter = obj.begin(); iter != obj.end(); iter++, j++)
	{
		res.push_back(*iter);
	}
	return res;
}

vector<int> AllSubsetSums(int S[], int u, int n)
{
	int INVALIDSIZE = 0;
	int b = sqrt(n * log2((float)n));
	vector<vector<int>> R;
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
		if (S1.size() == 0)
		{
			INVALIDSIZE++;
		}
		else
		{
			int *Q1 = new int[S1.size() + 5];
			for (int i = 0; i < S1.size(); i++)
			{
				Q1[i] = (S1[i] - l) / b;
			}

			vector<solutionElement> SQ;

			SQ = SetToVector(AllSubsetSumsSharp(Q1, (int)(u / b), S1.size()));

			set<int> Rl;
			for (int i = 0; i < SQ.size(); i++)
			{
				Rl.insert(SQ[i].sum * b + SQ[i].num * l);
			}
			vector<int> r = SetIntToVector(Rl);
			R.push_back(vector<int>(r));
		}
	}

	res = R[0];
	for (int l = 1; l <= b - 1 - INVALIDSIZE; l++)
	{
		//cout<<R[l]<<endl;
		res = OP2(res, R[l], u);
		//cout<<R[l]<<endl;
	}
	return res;
}

