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
	int i,j,c1,c2,c3,tmp;

	c1=b*3;
	c2=b*3+1;
	c3=b*3+2;
	for(i=0;i<9;++i){
		j=a*3+i*9;
		tmp=map[j];
		map[j]=map[c1];
		map[c1]=tmp;
		c1+=9;
		
		j=a*3+1+i*9;
		tmp=map[j];
		map[j]=map[c2];
		map[c2]=tmp;
		c2+=9;
		
		j=a*3+2+i*9;
		tmp=map[j];
		map[j]=map[c3];
		map[c3]=tmp;
		c3+=9;
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

void Sudoku::transform(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);

	for(int i=0;i<size;++i)	
		printf("%d%c",map[i],(i+1)%9==0?'\n':' ');
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



bool Sudoku::check(int& a,int& i){
	int j,k,r,c,b,b1,b2,b3;
	
	//col,row
	c=a%9;
	r=(a/9)*9;	
	
	//block
	b=27*(a/27)+3*((a%9)/3);
	b1=b;
	b2=b+9;
	b3=b+18;

	for(j=0;j<3;++j){
		for(k=0;k<3;++k){
			if(ch[a][i]==map[c]) return false;
			c+=9;
			if(ch[a][i]==map[r]) return false;
			++r;
		}
		if(ch[a][i]==map[b1]) return false;
		if(ch[a][i]==map[b3]) return false;
		if(ch[a][i]==map[b2]) return false;
		b1++;
		b2++;
		b3++;
	}
	//------------------------------------
	ck[a]=1;
	map[a]=ch[a][i];
	return true;
}

void Sudoku::backtrack(int& a){
	int i,j,in,n,aa=a+1;
	in=index[a];
	if(a==(size-1) && ch[in].empty()){
		++sol;
		for(i=0;i<size;++i) map2[i]=map[i];
	}
	if(sol==2)	return;
	

	if(a!=(size-1) && ch[in].empty()) backtrack(aa);
	else{
		for(i=0;i<ch[in].size();++i){
			if(a==(size-1) && check(in,i)){
				++sol;
				if(sol==1){
					for(j=0;j<size;++j) map2[j]=map[j];
				}
			}
			if(a!=(size-1)){
				for(j=a;j<size;++j){
					n=index[j];
					if(ck[n]==1){
						map[n]=0;
						ck[n]=0;
					}
				}
			}
	
			if(ch[in][i]!=0){
				if(check(in,i)){
					backtrack(aa);
				}
			}

		}
	}
	return;
}


void Sudoku::solve(){
	int f,chck=1;
	int i,j,k,l,m,tmp,t[10]={0},r,c,b,col[9][10],row[9][10];
	int a[9]={1,2,3,4,5,6,7,8,9};
	int flag=0,fgr[10]={0},fgc[10]={0},fgb[10]={0},gr,gc,gb,in[81]={0};
	for(i=0;i<9;++i){
		for(j=0;j<10;++j){
			col[i][j]=0; row[i][j]=0;
		}
	}
	
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
			
			c=i%9;	//check colume	
			r=(i/9)*9;	//check row
			
			for(j=0;j<9;++j){
				//check col
				tmp=map[c];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					ch[i][tmp-1]=0;
		/*			if(tmp!=9) ch[i].erase(ch[i].begin()+(tmp-1));
					if(tmp==9) ch[i].pop_back();
					ch[i].insert(ch[i].begin()+tmp-1,0);
		*/
				}
				c+=9;

				//check row
				tmp=map[r];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					ch[i][tmp-1]=0;
/*					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+(tmp-1));
					ch[i].insert(ch[i].begin()+tmp-1,0);
*/				}
				++r;
			}
			//-----------------------------------------
			b=27*(i/27)+3*((i%9)/3);	//check block
			for(j=b;j<(b+3);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					ch[i][tmp-1]=0;
/*					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+tmp-1);
					ch[i].insert(ch[i].begin()+tmp-1,0);
*/				}
			}
			for(j=(b+9);j<(b+12);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					ch[i][tmp-1]=0;
/*					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+tmp-1);
					ch[i].insert(ch[i].begin()+tmp-1,0);
*/				}
			}
			for(j=(b+18);j<(b+21);++j){
				tmp=map[j];
				if(tmp!=0 && t[tmp]==0){
					t[tmp]=1;
					ch[i][tmp-1]=0;
/*					if(tmp==9) ch[i].pop_back();
					if(tmp!=9) ch[i].erase(ch[i].begin()+tmp-1);
					ch[i].insert(ch[i].begin()+tmp-1,0);
*/				}
			}
			//---------------------------------------------
			for(j=0;j<10;++j)	t[j]=0;
		
			for(j=ch[i].size();j>0;--j){
				if(ch[i][j-1]==0) 
					ch[i].erase(ch[i].begin()+j-1);
			}

			if(map[i]==0 && ch[i].empty()){
				flag=1;
				break;
			}
			else if(ch[i].size()==1){
				map[i]=ch[i][0];
				ch[i].clear();
			}
		}
		else ch[i].clear();
	}
	
	//backtracking-------------------------------------
	while(chck!=0){	
		chck=0;
		for(i=0;i<size;++i){
			if(map[i]==0){
				if(ch[i].size()==1){
					map[i]=ch[i][0];
					ch[i].clear();
				}
			}
		}

		for(i=0;i<size;++i){
			if(map[i]==0){
				for(j=ch[i].size();j>0;j--){
					k=j-1;
					if(!check(i,k)){
						ch[i].erase(ch[i].begin()+k);
						ck[i]=0; 
						map[i]=0;
					}
					else{
						tmp=ch[i][k];
						col[i%9][tmp]+=1;
						row[i/9][tmp]+=1;
						ck[i]=0; 
						map[i]=0;
					}	
				}
			}
			if(map[i]==0 && ch[i].empty()){
				flag=1;
				break;
			}
	//		else ch[i].clear();
		}
		for(m=0;m<9;++m){
			for(j=1;j<10;++j){
				if(row[m][j]==1){
					chck=1;
					for(k=m*9;k<(m*9+9);++k){
						for(l=0;l<ch[k].size();++l){
							if(ch[k][l]==j){
								map[k]=j;
								ch[k].clear();
							}
						}
					}
				}
				else if(col[m][j]==1){
					chck=1;
					for(k=m;k<size;k+=9){
						for(l=0;l<ch[k].size();++l){
							if(ch[k][l]==j){
								map[k]=j;
								ch[k].clear();
							}
						}
					}
				}
			}
		}
		for(i=0;i<9;++i){
			for(j=0;j<10;++j){
				col[i][j]=0; row[i][j]=0;
			}
		}
	}
	
	if(flag==0){
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
		for(i=0;i<size;i+=27){	//check block
			for(j=0;j<9;j+=3){
				for(k=(i+j);k<(i+j+3);++k){
					gb=map[k];
					if(gb!=0) fgb[gb]++;
					if(fgb[gb]==2){flag=1; break;}
				}
				for(k=(i+j+9);k<(i+j+12);++k){
					gb=map[k];
					if(gb!=0) fgb[gb]++;
					if(fgb[gb]==2){flag=1; break;}
				}
				for(k=(i+j+18);k<(i+j+21);++k){
					gb=map[k];
					if(gb!=0) fgb[gb]++;
					if(fgb[gb]==2){flag=1; break;}
				}
				for(k=0;k<10;++k) fgb[k]=0;
			}
		}
	}

	chck=0;
	for(i=0;i<size;++i){
		if(!ch[i].empty()) chck=1;	
	}
	if(chck==0){
		for(i=0;i<size;++i) map2[i]=map[i];
		sol=1; flag=1;
	}
	
	if(flag==0){
		for(i=0;i<10;++i){
			for(j=0;j<size;++j){
				if(in[j]==0 && ch[j].empty()){
					index.push_back(j);
					in[j]=1;
				}
				else if(in[j]==0 && ch[j].size()==i){
					index.push_back(j);
					in[j]=1;
				}
			}
		}
		int tt=0;
		backtrack(tt);
	}

	if(sol==0) printf("0\n");
	else if(sol==2) printf("2\n");
	else if(sol==1){
		printf("1\n");
		for(i=0;i<size;i++)
			printf("%d%c",map2[i],(i+1)%9==0?'\n':' ');
	}
	sol=0;

}
