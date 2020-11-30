#ifndef _ALLSUBSETSUMS_H_
#define _ALLSUBSETSUMS_H_

#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn ((int)2e6+5)
// extern const double pi;
// extern int t, len, l, r[maxn * 2];

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

struct Complex
{ //复数
	double x, y;
	Complex(double t1 = 0, double t2 = 0) { x = t1, y = t2; }
};

// extern Complex Aa[maxn * 2], Bb[maxn * 2], Cc[maxn * 2];
inline Complex operator+(Complex a, Complex b) { return Complex(a.x + b.x, a.y + b.y); }
inline Complex operator-(Complex a, Complex b) { return Complex(a.x - b.x, a.y - b.y); }
inline Complex operator*(Complex a, Complex b) { return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

void fdft(Complex *a, int n, int flag);
int GetMaxInt(vector<int> A);
set<solutionElement> OP(set<solutionElement> A, set<solutionElement> B, int u);
vector<int> OP2(vector<int> A, vector<int> B, int u);
set<solutionElement> AllSubsetSumsSharp(int S[], int u, int n);
vector<solutionElement> SetToVector(set<solutionElement> object);
vector<int> AllSubsetSums(int S[], int u, int n);
set<int> FilterRepeatingInt(vector<int> obj);

#endif
