#include"Sudoku.h"
using namespace std;

Sudoku::Sudoku(){
	for(int i=0;i<size;++i)
		map[i]=0;
}

void Sudoku::readIn(){
	for(int i=0;i<size;++i)
		scanf("%d",&map[i]);
}

void Sudoku::changeNum(int a,int b){
	int i;
	for(i=0;i<size;++i){
		if(map[i]==a) map[i]=b;
		else if(map[i]==b) map[i]=a;
	}
}

void Sudoku::changeRow(int a,int b){
	int i,c=b*27,tmp;

	for(i=a*27;i<(a*27+27);++i){
		tmp=map[i];
		map[i]=map[c];
		map[c]=tmp;
		++c;
	}
}

void Sudoku::changeCol(int a,int b){
	int i,j,c,tmp;

	c=b*3;
	for(i=a*3;i<size;i+=9){
		tmp=map[i];
		map[i]=map[c];
		map[c]=tmp;
		c+=9;
	}

	c=b*3+1;
	for(i=a*3+1;i<size;i+=9){
		tmp=map[i];
		map[i]=map[c];
		map[c]=tmp;
		c+=9;
	}

	c=b*3+2;
	for(i=a*3+2;i<size;i+=9){
		tmp=map[i];
		map[i]=map[c];
		map[c]=tmp;
		c+=9;
	}

}

void Sudoku::rotate(int n){
	int i,j,k,a,b,c,d,tmp;
	if(n%4==0){}
	else if(n%4==2){
		for(i=0;i<40;++i){
			j=80-i;
			tmp=map[i];
			map[i]=map[j];
			map[j]=tmp;
		}
//		flip(0); flip(1);
	}
	else if(n%4==1){
		k=7;
		for(i=0;i<9;++i){
			for(j=k;j>=0;--j){
				a=i*9+(8-j);
				c=a/9;
				d=a%9;
				b=d*9+c;
				tmp=map[a];
				map[a]=map[b];
				map[b]=tmp;
			}
			--k;
		}
		flip(1);
	}
	else if(n%4==3){
		rotate(1);
		flip(0);
		flip(1);
	}

}

void Sudoku::flip(int n){
	int i,j,a,b,tmp;
	if(n==0){		//vertically
		for(i=0;i<4;++i){
			for(j=0;j<9;++j){
				a=i*9+j;
				b=(72+2*j)-a;
				tmp=map[a];
				map[a]=map[b];
				map[b]=tmp;
			}
		}
	}
	else{		//horizontally
		for(i=0;i<4;++i){
			for(j=0;j<9;++j){
				a=j*9+i;
				b=j*9+(8-i);
				tmp=map[a];
				map[a]=map[b];
				map[b]=tmp;
			}
		}
	}
}

void Sudoku::printmap(){
	for(int i=0;i<size;++i)
		printf("%d%c",map[i],(i+1)%9==0?'\n':' ');

}

void Sudoku::transform(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	printmap();
}


void Sudoku::giveQuestion(){
	int  a[81]={5,3,0,0,7,0,0,0,0,
   				6,0,0,1,9,5,0,0,0,
				0,9,8,0,0,0,0,6,0,
				8,0,0,0,6,0,0,0,3,
				4,0,0,8,0,3,0,0,1,
				7,0,0,0,2,0,0,0,6,
				0,6,0,0,0,0,2,8,0,
				0,0,0,4,1,9,0,0,5,
				0,0,0,0,8,0,0,7,9};
	for(int i=0;i<size;++i){
		map[i]=a[i];
		printf("%d%c",map[i],(i+1)%9==0?'\n':' ');
	}
}



bool Sudoku::check(int a,int i){
	int j,r,c,b;

	//check colume
	c=(a+1)%9-1;
	if((a+1)%9==0) c=8;
	for(j=c;j<size;j+=9){	
		if(ch[a][i]==map[j]) return false;
	}
	
	//check row
	r=((a+1)/9)*9;	
	if((a+1)%9==0) r=r-9;
	for(j=r;j<(r+9);++j){
		if(ch[a][i]==map[j]) return false;
	}

	//check block
	if((a+1)%9!=0 && (a+1)%9<4){		
		if(a<21)	  b=0;
		else if(a<48) b=27;
		else if(a<75) b=54;
	}
	else if((a+1)%9!=0 && (a+1)%9<7){
		if(a<24)	  b=3;
		else if(a<51) b=30;
		else if(a<78) b=57;
	}else if((a+1)%9==0 || (a+1)%9<10){
		if(a<27)	  b=6;
		else if(a<54) b=33;
		else if(a<81) b=60;
	}

	for(j=b;j<(b+3);++j){
		if(ch[a][i]==map[j]) return false;
	}
	for(j=(b+9);j<(b+12);++j){
		if(ch[a][i]==map[j]) return false;
	}
	for(j=(b+18);j<(b+21);++j){
		if(ch[a][i]==map[j]) return false;
	}
	//------------------------------------
	ck[a]=1;
	map[a]=ch[a][i];
	return true;
}

void Sudoku::backtrack(int a){
	int i,j;
	if(a==(size-1) && ch[a].empty()){
		++sol;
		for(i=0;i<size;++i) map2[i]=map[i];
	}
	if(sol==2){
		return;
	}

	if(a!=(size-1) && ch[a].empty()) backtrack(a+1);
	else{
		for(i=0;i<ch[a].size();++i){
			if(a==(size-1) && check(a,i)){
				++sol;
				if(sol==1){
					for(j=0;j<size;++j) map2[j]=map[j];
				}
			}
			if(a!=(size-1)){
				for(j=a;j<size;++j){
					if(ck[j]==1){
						map[j]=0;
						ck[j]=0;
					}
				}
			}
	
			if(ch[a][i]!=0){
				if(check(a,i)){
					backtrack(a+1);
				}
			}

		}
	}
	return;
}


void Sudoku::solve(){
	int f;
	int i,j,tmp,t[10]={0},r,c,b;
	int a[9]={1,2,3,4,5,6,7,8,9};
	for(i=0;i<size;++i){
		map2[i]=0;
		ck[i]=0;
		ch[i].clear();
		ch[i].insert(ch[i].begin(),a,a+9);
	}
	sol=0;
	//possible numbers.
	for(i=0;i<size;++i){
		if(map[i]==0){
			//----------------------------------------
			c=(i+1)%9-1;	//check colume
			if((i+1)%9==0) c=8;
			for(j=c;j<size;j+=9){	
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					if(tmp!=9) ch[i].erase(ch[i].begin()+(tmp-1));
					if(tmp==9) ch[i].pop_back();
					ch[i].insert(ch[i].begin()+tmp-1,0);
				}
			}
			//-----------------------------------------
			r=((i+1)/9)*9;	//check row
			if((i+1)%9==0) r=r-9;
			for(j=r;j<(r+9);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+(tmp-1));
					ch[i].insert(ch[i].begin()+tmp-1,0);
				}
			}
			//-----------------------------------------
			if((i+1)%9!=0 && (i+1)%9<4){		//check block
				if(i<21)	  b=0;
				else if(i<48) b=27;
				else if(i<75) b=54;
			}
			else if((i+1)%9!=0 && (i+1)%9<7){
				if(i<24)	  b=3;
				else if(i<51) b=30;
				else if(i<78) b=57;
			}else if((i+1)%9==0 || (i+1)%9<10){
				if(i<27)	  b=6;
				else if(i<54) b=33;
				else if(i<81) b=60;
			}
			for(j=b;j<(b+3);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+tmp-1);
					ch[i].insert(ch[i].begin()+tmp-1,0);
				}
			}
			for(j=(b+9);j<(b+12);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+tmp-1);
					ch[i].insert(ch[i].begin()+tmp-1,0);
				}
			}
			for(j=(b+18);j<(b+21);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+tmp-1);
					ch[i].insert(ch[i].begin()+tmp-1,0);
				}
			}
			//---------------------------------------------
			for(j=0;j<10;++j)	t[j]=0;
		}
		else{ch[i].clear();}
	}

	for(i=0;i<size;++i){
		if(!ch[i].empty()){
			for(j=ch[i].size();j>0;--j){
				if(ch[i][j-1]==0) ch[i].erase(ch[i].begin()+j-1);
			}
		}
	}
	
	for(i=0;i<size;++i){
		if(ch[i].size()==1){
			map[i]=ch[i][0];
			ch[i].clear();
		}
	}
	//backtracking-------------------------------------
	int flag=0,fgr[10]={0},fgc[10]={0},gr,gc;
	for(i=0;i<9;++i){	//check row and col----------------
		for(j=0;j<9;++j){
			gr=map[i*9+j];
			gc=map[i+j*9];
			if(gr!=0) fgr[gr]++;
			if(fgr[gr]==2){ flag=1; break;}
			if(gc!=0) fgc[gc]++;
			if(fgc[gc]==2){ flag=1; break;}
		}
		for(j=0;j<10;++j){fgr[j]=0;  fgc[j]=0;}
	}

	for(i=0;i<size;i++){
		if(map[i]==0 && ch[i].empty()) flag=1;
	}

	
	if(flag==0) backtrack(0);

	if(sol==0) printf("0\n");
	else if(sol==2) printf("2\n");
	else if(sol==1){
		printf("1\n");
		for(i=0;i<size;i++)
			printf("%d%c",map2[i],(i+1)%9==0?'\n':' ');
	}
	sol=0;

}
