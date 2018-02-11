#include <algorithm>
#include <vector>
#include <functional>  
#include <queue>
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <math.h>
#include <random>
#include <set>
#include <string>
#include <map>
#include <climits>
using namespace std;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi; 
typedef vector<vector<char>> vvc; 
#define pb push_back
ifstream inputfile;
ofstream outputfile;

clock_t start,finish;
double tt;

class Game
{
public:
	struct cmp
	{
		bool operator()(pair<int,int> p , pair<int,int> q)
		{
			return p.second < q.second;
		}
	};
	vvc board;
	int cost;
	
	typedef priority_queue<pair<int,int>, vector<pair<int,int>>,cmp> PQ;
	queue<pair<int,int>> points;

	PQ components;
	int origin;

	Game(const vvc& board, int cost=0, int origin=-1)
	{
		this->board = board;
		this->cost=cost;
		this->origin=-1;
		

	}
	
	Game()
	{
		this->cost=0;
		this->origin=-1;
	}
	Game(int n, int cost=0,int origin=-1)
	{
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j)
			{
				this->board[i][j]='0';
			}
		}
		this->cost=cost;
		this->origin = origin;

	}
	
	bool isTerminal()
	{
		int n= board.size();
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j)
			{
				if(board[i][j]!='*')
					return false;
			}
		}
		return true;
	}

	void disp_board()
	{
		for(int i=0;i<board.size();++i)
		{
			for(int j=0;j<board.size();++j)
			{
				outputfile<<board[i][j];
			}
			outputfile<<endl;
		}
	}
	void printPoints()
	{
		queue<pair<int,int>> q = points;
		while(!q.empty())
		{
			pair<int,int> ele = q.front();
			q.pop();
			cout<<ele.first<<" "<<ele.second<<endl;
		}
		cout<<endl;
	}

	void disp_components()
	{
		PQ q1 = components;
		while(!q1.empty())
		{
			pair<int,int> p1 = q1.top();
			cout<<p1.first<<" : "<<p1.second<<endl;
			q1.pop();
		}
		cout<<"******";
	}

	void getMoves()
	{
		int n =board.size();
		vvi marked(n, vector<int>(n,0));
		queue<int> q1;
		int r,c,nr,nc;
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j)
			{
				if(marked[i][j]==1)
					continue;

				if(board[i][j]=='*')
					continue;
				
				int pos = i*n+j;
				char fruit = board[i][j];
				q1.push(pos);
				int comp_value=0;
				while(!q1.empty())
				{
					int index = q1.front();
					q1.pop();

					r = index/n;
					c = index%n;
					marked[r][c]=1;
					comp_value+=1;
					nr= r+1;
					nc =c ;

					
					if(nr<n && marked[nr][nc]==0 && board[nr][nc]== fruit)
					{
						q1.push(nr*n+nc);
						marked[nr][nc]=1;
						
					}

					nr= r-1;
					nc=c;


					if(nr>=0 && marked[nr][nc]==0 && board[nr][nc]== fruit)
					{
						q1.push(nr*n+nc);
						marked[nr][nc]=1;
						
					}
					
					nr=r;
					nc= c-1;

					if(nc>=0 && marked[nr][nc]==0 && board[nr][nc]== fruit)
					{
						q1.push(nr*n+nc);
						marked[nr][nc]=1;
						
					}
					
					nr=r;
					nc= c+1;

					if(nc<n && marked[nr][nc]==0 && board[nr][nc]== fruit)
					{
						q1.push(nr*n+nc);
						marked[nr][nc]=1;
						
					}
					
				}

				components.push(make_pair(pos,comp_value*comp_value));
				
			}
		}

	}

	

	

	void gravity()
	{
		int n = board.size();
		
		for(int i=0;i<n;++i)
		{
			int n_fruits= 0;
			int index=n;
			for(int j=n-1;j>=0;--j)
			{
				
				if(board[j][i]!='*')
				{
					--index;
					board[index][i]= this->board[j][i];
				}



			}
			
			while(index>0)
				{
					
					--index;
					board[index][i]= '*';
					
				}
			
			
		}

	}



};

Game nextMove(Game g1,bool turn, int x, int y)
	{
		
		if (g1.board[x][y]=='*')
		{
			
			return g1;
		}

		int n = g1.board.size();
		
		
		int bestPos= x*n+y;
		
		
		if(g1.origin == -1)
			g1.origin = bestPos;
		queue<int> q1;
		q1.push(bestPos);
		
		char fruit = g1.board[x][y];

		int heuristic_value=0;
		int r,c,nr,nc;
		while(!q1.empty())
		{
			int index = q1.front();
			q1.pop();
			r = index/n;
			c = index%n;
			g1.board[r][c]='*';
			heuristic_value+=1;
			nr= r+1;
			nc =c ;

			if(nr<n && g1.board[nr][nc]== fruit)
			{
				q1.push(nr*n+nc);
				g1.board[nr][nc]='*';

			}

			nr= r-1;
			nc=c;

			if(nr>=0 && g1.board[nr][nc]== fruit)
			{
				q1.push(nr*n+nc);
				g1.board[nr][nc]='*';

			}

			nr=r;
			nc= c+1;

			if(nc<n && g1.board[nr][nc]== fruit)
			{
				q1.push(nr*n+nc);
				g1.board[nr][nc]='*';

			}

			nr=r;
			nc= c-1;

			if(nc>=0 && g1.board[nr][nc]== fruit)
			{
				q1.push(nr*n+nc);
				g1.board[nr][nc]='*';

			}


		}
		g1.gravity();
		
		if(turn)
			g1.cost+= heuristic_value*heuristic_value;
		else
			g1.cost-= heuristic_value*heuristic_value;

		
		
		g1.points.push(make_pair(bestPos,heuristic_value));
		g1.components= Game::PQ();
		
		return g1;



	}
void disp(const vvc& v)
{
	for(int i=0;i<v.size();++i)
	{
		for(int j=0;j<v.size();++j)
		{
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
}
void disp_int(const vvi& v)
{
	for(int i=0;i<v.size();++i)
	{
		for(int j=0;j<v.size();++j)
		{
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
}

void printQueue(Game::PQ p1)
{
	Game::PQ temp =p1;
	while(!temp.empty())
	{
		pair<int,int> ele = temp.top();
		temp.pop();
		cout<<ele.first<<" "<<ele.second<<endl;
	}

}

bool fin=false;


#if 1
Game alphabeta(Game g1, int alpha, int beta,int depth, bool maximize, int max_depth, double &time)
{
	
	finish=clock();

	tt= double(finish- start)/ CLOCKS_PER_SEC;

	if(tt > time/2)
	{
		fin=true;
		return g1;
	}
	if(depth== max_depth || g1.isTerminal())
	{

		return g1;
	}

	
	int n = g1.board.size();
	if(maximize)
	{
		g1.getMoves();
		Game::PQ q1= g1.components;
		int max_hue = INT_MIN;
		Game newState= Game();
		Game maxState= Game();
		maxState.cost= INT_MIN;
		pair<int,int> point;
		
		while(!q1.empty())
		{
			
			point = q1.top();
			
			q1.pop();
			newState = nextMove(g1,maximize,point.first/n, point.first%n);
			
			newState = alphabeta(newState, alpha,beta, depth+1, false,max_depth,time);

			if(fin)
				break;
			if(newState.cost > maxState.cost)
			{
				maxState = newState;
			}

			alpha= max(alpha,maxState.cost);
			if( beta <= alpha)
				break;



		}
		return maxState;

		
		
	}
	else
	{
		g1.getMoves();
		Game newState= Game();
		Game minState= Game();
		minState.cost = INT_MAX;
		//Game temp(g1);
		pair<int,int> point;
		Game::PQ q1= g1.components;
		
		while(!q1.empty())
		{
			
			point = q1.top();
			
			q1.pop();
			newState= nextMove(g1,maximize,point.first/n, point.first%n);
			
			newState = alphabeta(newState, alpha,beta, depth+1, true, max_depth,time);
			
			if(fin)
				break;
			if(newState.cost < minState.cost)
			{
				minState= newState;
			}

			beta = min(beta,minState.cost);
			if( beta <= alpha)
				break;


		}
		return minState;

	}
}


void display_output(Game ans,Game original)
{
	outputfile.clear();
	outputfile.seekp(0);
	int n = original.board.size();
	int pos = ans.origin;
	char cindex = (char)(pos%n)+'A';
	int rindex= pos/n+1;
	outputfile<<cindex<<rindex<<endl;
	
	Game final = nextMove(original, true, pos/n, pos%n);
	final.disp_board();


}
#endif

int main()
{

	ios_base::sync_with_stdio(false);
	int n,p;
	double time;
	inputfile.open("tc3.txt");
	inputfile>>n>>p>>time;

	
	outputfile.open("op3.txt");
	vvc v(n,vector<char>(n,0));
	char ch;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
		{
			inputfile>>ch;
			v[i][j]= ch;
			
		}	

	}
	
	int pt = -1; // initial point -> dummy 
	
	Game g1 = Game(v);
	
	start=clock();
	
	for(int max_depth=1; max_depth<=5; ++max_depth)
	{
		
		Game ans = alphabeta(g1,INT_MIN,INT_MAX,0,true, max_depth,time);
		if(fin)
			break;
		int pos = ans.origin;
		char cindex = (char)(pos%n)+'A';
		int rindex= pos/n+1;
		
		display_output(ans,g1);
		finish =clock();
		
		if(ans.isTerminal())
			break;
		

	}
	
	inputfile.close();
	outputfile.close();

}