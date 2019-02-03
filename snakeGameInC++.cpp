#include<iostream>
#include<time.h>
#include<queue>
#include<vector>
using namespace std;
#define n 7
#define m 7
/* adding fruit  */
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
	while(temp.empty()){
		X x=temp.front();
		vrow.push_back(x.r);
		vcol.push_back(x.c);
		temp.pop();
	}
	for(int i=0,j=0;i<n ;i++)
	{
		if(j<vrow.size() && vrow[j]==i)
			j++;
		else{
			vr.push_back(i);
		}
	}
	for(int i=0,j=0; i<m; i++)
	{
		if(j<vcol.size() && vcol[j]==i)
			j++;
		else{
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
		}
	}	
	a[fr][fc]='@';
}

/*******************************
return 1 game in progress
return -1 game over
*******************************/

int  movement(char a[n][m], char move)
{
	bool isFruit = false;		
	// obj x2 to move head to new pos.
	// x2 other feature to clean traces of tail left after single move (set to ' ').
	X x2=q.back();		//----> x2 object have coord of head now
	//--->up
	if( move=='w' && x2.r -1>=0 && a[x2.r-1][x2.c]!='-' &&a[x2.r-1][x2.c]!='|' &&a[x2.r-1][x2.c]!='1')
		{
			if(a[x2.r-1][x2.c]=='@')
				isFruit=true;
				
			a[x2.r-1][x2.c]='0';	//---->head
			a[x2.r][x2.c]='1';		//---->tail
			q.push(X(x2.r-1,x2.c));
		}
	//--->down	
	else if(move=='s' && x2.r +1<n && a[x2.r+1][x2.c]!='-' &&a[x2.r+1][x2.c]!='|' &&a[x2.r+1][x2.c]!='1')
		{
			if(a[x2.r+1][x2.c]=='@')
				isFruit=true;
				
			a[x2.r+1][x2.c]='0';
			a[x2.r][x2.c]='1';
			q.push(X(x2.r+1,x2.c));
		}
	//--->left
	else if(move=='a' && x2.c-1>=0 && a[x2.r][x2.c-1]!='-' &&a[x2.r][x2.c-1]!='|' &&a[x2.r][x2.c-1]!='1')
		{
			if(a[x2.r][x2.c-1]=='@')
				isFruit=true;
			
			a[x2.r][x2.c-1]='0';
			a[x2.r][x2.c]='1';
			q.push(X(x2.r,x2.c-1));
		}
	//--->right
	else if(move=='d' && x2.c+1<m && a[x2.r][x2.c+1]!='-' &&a[x2.r][x2.c+1]!='|' &&a[x2.r][x2.c+1]!='1')
		{
			if(a[x2.r][x2.c+1]=='@')
				isFruit=true;
				
			a[x2.r][x2.c+1]='0';
			a[x2.r][x2.c]='1';
			q.push(X(x2.r,x2.c+1));
		}
	//--->rule's voilation
	else{
		return -1;
	}
	
	if(isFruit==false){

		//-->clearing tail previous pos.
		x2=q.front();
		a[x2.r][x2.c]=' ';
		q.pop();
	}
	else{
		fruit(a);
	}
	return 1;
}

void  grid(char a[n][m])
{
	int returnValue;
	
	do{
	system("cls");
	char move;		//--> move w, a, s, d.
	cout<<"---------"<<endl;
	for( int i=0;i<n;i++)
	{	cout<<"|";
		for(int  j=0;j<m;j++)
		{
			cout<<a[i][j];
		}	
		cout<<"|"<<endl;
	}
	cout<<"---------"<<endl;
	cout<<endl<<"************************************"<<endl;
	cout<<"Press:\nw for up\na for left\ns for down\nd for right\nq for quit\n"<<endl<<"Press move: ";
	cin>>move;
	if(move=='q'){
		cout<<"Game Quit"<<endl;
		system("pause");
		return ;		
	}
	returnValue = movement( a, move);
	}while(returnValue==1);				// ---> true until game in progress
	
	// return -1 then,
		cout<<"Game Over"<<endl;
		system("pause");
		return ;
}

int main()
{
	char arr[][m]={ {' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' '}  };
	snakeGen(arr);
	fruit(arr);
	grid(arr);
}
