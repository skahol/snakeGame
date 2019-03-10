#include<iostream>
#include<time.h>
#include<queue>
#include<vector>
#include<algorithm>
#include<conio.h>		// for kbhit()
using namespace std;
#define n 10
#define m 14
/* adding fruit  */
static int score;
class X
{
	public:
		int r;
		int c;
		X(){		}
		X(int r,int c)
		{
			this->r=r;
			this->c=c;
		}
};

// creating a queue to keep track of snake
// in queue new position(head) will be push ( from back )
// old position(tail) will be poped-out (from front)
queue<X> q;

void snakeGen(char a[n][m])		// call by reference
{
// class object to get current position of head (row,col)
	X x1;		//---> to get head's current position by updating same object.
// This program will create different sequence of  
// random numbers on every program run  
  
// Use current time as seed for random generator 
    srand(time(0));
    
	int hr, hc;
	int tr, tc;
// for head coord in grid
	hr=rand()%n;	
	hc=rand()%m;
// for tail coord in grid
	tr=rand()%3+(hr-1);
	if(tr<0)		// case if head is at corner.
		tr=-tr;
		
	if(tr==hr)
	{
		tc=rand()%3+(hc-1);
		while(tc==hc)
			tc=rand()%3+(hc-1);
			
		if(tc<0)
			tc=-tc;	
		else if(tc>=m)
			tc=rand()%2+(hc-1);
	}
	else {					// --> if(tr<tc || tr>tc) tc=hc;
		tc=hc;		
	}
// head is represented by 0
// body  & tail by 1
	a[hr][hc]='0';
	a[tr][tc]='1';
// initial position of snake  in queue 
	x1.r=tr;
	x1.c=tc;
	q.push(x1);
	x1.r=hr;
	x1.c=hc;
	q.push(x1);
}

void fruit(char a[n][m])
{
	int fr;
	int fc;
	fr=rand()%n;			
	fc=rand()%m;
//--> vector for dynamic allocation
	vector<int> vrow;
	vector<int> vcol;		
// vrow having rows of snake and same for vcol
//-->rows and cols other than snake vr,vc.
	vector<int> vr;		
	vector<int> vc;
	
	queue<X> temp=q;
//--->object to access temp queue each element .
	X x;
	while(!temp.empty()){
		x=temp.front();
		vrow.push_back(x.r);
		vcol.push_back(x.c);
		temp.pop();
	}
	sort(vrow.begin(),vrow.end());
	sort(vcol.begin(),vcol.end());
	int k=0;
	for(int i=0,j=0;i<n ;i++)
	{
		if(j<vrow.size() && vrow[j]==k){
			j++;
		}
		else{					// donot push same value multiple times bcz of using i-- in if condition
			vr.push_back(i);
		}
	}
	k=0;
	for(int i=0,j=0; i<m; i++)
	{
		if(j<vcol.size() && vcol[j]==k){
			j++;
		}
		else{
			k++;
			vc.push_back(i);
		}
	}
	
	for(int i=0;i<vrow.size();i++)		//---> size of vrow and vcol will same, storing coordinates of snake.
	{
		int s=vr.size();
		int s1=vc.size();
		while(vrow[i]==fr && vcol[i]==fc){
			fr=vr[rand()%s];
			fc=vc[rand()%s1];
			if(vrow.size()==n && vcol.size()==m)
			{
				fr=rand()%n;
				fc=rand()%m;
				break;
			}
		}
	}	
	a[fr][fc]='@';
}
void delay(double sec){
	double millisec=1000*sec;
	clock_t start=clock();
	while(clock()<(start+millisec));
}

/*******************************
return 1 game in progress
return -1 game over
*******************************/
bool haveFruit(char a[][m]){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j]=='@')
				return true;
		}
	}
	return false;
}
int  movement(char a[n][m],char move)
{
	bool isFruit = false;
					        	//---> obj x2 to move head to new pos.
	X x2=q.back();				//---> x2 other feature to clean traces of tail left after single move (set to ' ').
				   				//----> x2 object have coord of head now
	if( move=='w' && x2.r -1>=0  && a[x2.r-1][x2.c]!='1') //--->up
		{
			if(a[x2.r-1][x2.c]=='=' || a[x2.r-1][x2.c]=='|')
				return -1;
			
			if(a[x2.r-1][x2.c]=='@')
				isFruit=true;
				
			a[x2.r-1][x2.c]='0';	//---->head
			a[x2.r][x2.c]='1';		//---->tail
			q.push(X(x2.r-1,x2.c));
		}
	else if(move=='s' && x2.r +1<n &&a[x2.r+1][x2.c]!='1') //--->down	
		{
			if(a[x2.r+1][x2.c]=='=' || a[x2.r+1][x2.c]=='|')
				return -1;
				
			if(a[x2.r+1][x2.c]=='@')
				isFruit=true;
				
			a[x2.r+1][x2.c]='0';
			a[x2.r][x2.c]='1';
			q.push(X(x2.r+1,x2.c));
		}
	else if(move=='a' && x2.c-1>=0 &&a[x2.r][x2.c-1]!='1') //--->left
		{
			if(a[x2.r][x2.c-1]=='=' || a[x2.r][x2.c-1]=='|')
				return -1;
				
			if(a[x2.r][x2.c-1]=='@')
				isFruit=true;
			
			a[x2.r][x2.c-1]='0';
			a[x2.r][x2.c]='1';
			q.push(X(x2.r,x2.c-1));
		}
	else if(move=='d' && x2.c+1<m && a[x2.r][x2.c+1]!='1')   //--->right
		{
			if(a[x2.r][x2.c+1]=='=' || a[x2.r][x2.c+1]=='|')
				return -1;
				
			if(a[x2.r][x2.c+1]=='@')
				isFruit=true;
				
			a[x2.r][x2.c+1]='0';
			a[x2.r][x2.c]='1';
			q.push(X(x2.r,x2.c+1));
		}
	else if(move!='a'&& move!='s'&& move!='d'&& move!='w'){		//--->invalid move
			return 1;
	}
	else if(move=='q'){				//---> quiting game
		return 0;		
	}
	else{							//--->rule's voilation
		return -1;
	}
	
	if(!isFruit){					//-->clearing tail previous pos.
		x2=q.front();
		a[x2.r][x2.c]=' ';
		q.pop();
	}
	else{
		score+=10;
		fruit(a);
	}
	
	return 1;
}

void  grid(char a[n][m])
{
	system("cls");
	cout<<"\tSCORE :"<<score<<endl;
	cout<<"\t================"<<endl;
	for( int i=0;i<n;i++)
	{	cout<<"\t|";
		for(int  j=0;j<m;j++)
		{
			cout<<a[i][j];
		}	
		cout<<"|"<<endl;
	}
	cout<<"\t================"<<endl;
	
	if( !haveFruit(a)){		// due to bug 
		fruit(a);
	}
}

int main()
{
	score=0;
	char arr[][m]={ {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
					{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '} };
	snakeGen(arr);
	fruit(arr);
	
	int returnValue=1;
	char move;
	while(1){
		
		if(kbhit()){
			move=getch();
			returnValue = movement( arr, move);
			goto label;
		}		
		if(move=='a' || move=='s' || move=='d' || move=='w')
			returnValue=movement(arr,move);	
	
	label:
	if(score==100){
		cout<<"\tCongractulations!!! Level Completed"<<endl;
		break;
	}
	if(returnValue==0){
		cout<<"\tGame Quit"<<endl;
		break;
	}
	
	if(returnValue==-1){
		cout<<"\tGame Over"<<endl;
		break;
	}
		grid(arr);
		delay(1);
	
	}

}
