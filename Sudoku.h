#include<iostream>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

class Sudoku{
	public:
		Sudoku();
		void giveQuestion();
		void readIn();
		bool check(int & a,int & i);
		void backtrack(int & a);
		void solve();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		void printmap();
		static const int size=81;
	private:
		int map2[size];
		int map[size];
		int sol;
		int ck[size];
		vector<int>ch[size];
		vector<int>index;
};
