#include <iostream>
#include<conio.h>
#include<Windows.h>
#include<time.h>
using namespace std;

const int Up = 1, Down = 2, Right = 3, Left = 4;

struct pos
{
	int r, c;
};
struct level1Herdal
{
	int r, c;
};
struct Snake
{
	pos* ps;
	char sym;      //sym for the body of snake
	char hsym;      //sym for the head of snake
	int Ssize;
	int Sdirection;
	int Ukey, Dkey, Rkey, Lkey;
	int score;
	int speedDelay;
	char coloure;
};

HANDLE txt = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Sinit(Snake& S,int i, int& row, int& col, pos& fpos, char& fsym)
{
		S.score = 0;
		S.speedDelay = 150;
		S.Ssize = 4;
		S.sym = -37;

		switch (i)
		{
		case 0:
			S.Sdirection = Right;
			S.hsym = 1;
			S.ps = new pos[S.Ssize];
			S.Ukey = 'H', S.Dkey = 'P', S.Rkey = 'M', S.Lkey = 'K';
			//S[i].Ukey = 'w', S[i].Dkey = 's', S[i].Rkey = 'd', S[i].Lkey = 'a';
			for (int j = 0; j < S.Ssize; j++)
			{
				S.ps[j].r = row / 2;    //To put snake initially at the mid of boundries
				S.ps[j].c = col / 2;
			}
			S.coloure = 10;
			break;
		case 1:
			S.Sdirection = Left;
			S.hsym = 4;   //dimond
			S.ps = new pos[S.Ssize];
			S.Ukey = 't', S.Dkey = 'g', S.Rkey = 'h', S.Lkey = 'f';
			for (int j = 0; j < S.Ssize; j++)
			{
				S.ps[j].r = 6;    
				S.ps[j].c = col / 2;
			}
			S.coloure = 11;
			break;
		case 2:
			S.Sdirection = Up;
			S.hsym = 5;//leaf
			S.ps = new pos[S.Ssize];
			S.Ukey = 'i', S.Dkey = 'k', S.Rkey = 'l', S.Lkey = 'j';
			for (int j = 0; j < S.Ssize; j++)
			{
				S.ps[j].r = (row / 2)-2;    
				S.ps[j].c = (col / 2)- (col / 4);
			}
			S.coloure = 12;
			break;
		case 3:
			S.Sdirection = Down;
			S.hsym = -22;//sun
			S.ps = new pos[S.Ssize];
			S.Ukey = 'w', S.Dkey = 's', S.Rkey = 'd', S.Lkey = 'a';
			//S[i].Ukey = 'x', S[i].Dkey = 'v', S[i].Rkey = 'c', S[i].Lkey = 'z';
			for (int j = 0; j < S.Ssize; j++)
			{
				S.ps[j].r = (row / 2) - 2;    
				S.ps[j].c = (col / 2) + (col / 4);
			}
			S.coloure = 13;
			break;
		}
}

void init(Snake*& S,int& SAsize, int& row, int& col, pos& fpos, char& fsym, pos& fpos2, char& fsym2)
{
	do {
		cout << "Enter the number of Palyers 1-4\n";
		cin >> SAsize;
	} while (SAsize<1&& SAsize>4);
	(const int)SAsize;
	S = new Snake[SAsize];
	for (int i = 0; i < SAsize; i++) 
	  Sinit(S[i],i, row, col, fpos, fsym);
	fpos.r = 10;
	fpos.c = 10;
	fsym = '$';
	
	fpos2.r = 0;
	fpos2.c = 0;
	fsym2 = 2;
}

void DisplaySnake(const Snake* S, int SAsize)
{
	
	for (int i=0; i < SAsize; i++)
	{
		SetConsoleTextAttribute(txt, S[i].coloure);
		gotoRowCol(S[i].ps[0].r, S[i].ps[0].c);
		cout << S[i].hsym;
		for (int j = 1; j < S[i].Ssize; j++)
		{
			gotoRowCol(S[i].ps[j].r, S[i].ps[j].c);
			cout << S[i].sym;
		}
		SetConsoleTextAttribute(txt, 7);
	}
	
}

void RemoveSnake(Snake* S,int SAsize)
{
	for (int i = 0; i < SAsize; i++)
	 for (int j = 0; j < S[i].Ssize; j++)
	 {
		gotoRowCol(S[i].ps[j].r, S[i].ps[j].c);            
		cout << " ";
	 }
}

void DirectionChange(char kbEnteredch, char kbEnteredch2, Snake*& S, int SAsize)
{
	if (kbEnteredch == 224)
	{
		for (int i = 0; i < SAsize; i++)
		{
			if (kbEnteredch2 == S[i].Ukey && S[i].Sdirection != Down)
				S[i].Sdirection = Up;
			if (kbEnteredch2 == S[i].Dkey && S[i].Sdirection != Up)
				S[i].Sdirection = Down;
			if (kbEnteredch2 == S[i].Rkey && S[i].Sdirection != Left)
				S[i].Sdirection = Right;
			if (kbEnteredch2 == S[i].Lkey && S[i].Sdirection != Right)
				S[i].Sdirection = Left;
		}
	}
	else
	{
		for (int i = 0; i < SAsize; i++)
		{
			if (kbEnteredch == S[i].Ukey && S[i].Sdirection != Down)
				S[i].Sdirection = Up;
			if (kbEnteredch == S[i].Dkey && S[i].Sdirection != Up)
				S[i].Sdirection = Down;
			if (kbEnteredch == S[i].Rkey && S[i].Sdirection != Left)
				S[i].Sdirection = Right;
			if (kbEnteredch == S[i].Lkey && S[i].Sdirection != Right)
				S[i].Sdirection = Left;
		}
	}
}
void diplayBoundry(int row, int col)
{
	for (int i = 1; i < row; i++)
	{
		gotoRowCol(i, 0);
		cout << (char)-70;
		gotoRowCol(i, col);
		cout << (char)-70;
	}
	for (int i = 0; i < col + 1; i++)
	{
		gotoRowCol(0, i);
		cout << (char)-51;
		gotoRowCol(row, i);
		cout << (char)-51;
	}
}

void MoveSnake(Snake* S,int SAsize, const int row, const int col)
{
	for (int si = 0; si < SAsize; si++)
	{
		for (int i = S[si].Ssize - 1; i - 1 >= 0; i--)   //To move whole body one pos next withi the array
		{
			S[si].ps[i] = S[si].ps[i - 1];
		}
		switch (S[si].Sdirection)
		{
		case Up:
			S[si].ps[0].r--;
			if (S[si].ps[0].r == -1)
			{
				S[si].ps[0].r = row - 1;
				diplayBoundry(row, col);
			}
			break;
		case Down:
			S[si].ps[0].r++;
			if (S[si].ps[0].r == row)
			{
				S[si].ps[0].r = 1;
				diplayBoundry(row, col);
			}
			break;
		case Left:
			S[si].ps[0].c--;
			if (S[si].ps[0].c == -1)
			{
				S[si].ps[0].c = col - 1;
				diplayBoundry(row, col);
			}
			break;
		case Right:
			S[si].ps[0].c++;
			if (S[si].ps[0].c == col)
			{
				S[si].ps[0].c = 1;
				diplayBoundry(row, col);
			}
			break;
		}
	}


}

void foodDisplay(char fsym, pos fpos)
{
	SetConsoleTextAttribute(txt, 12);
	gotoRowCol(fpos.r, fpos.c);
	cout << fsym;
	SetConsoleTextAttribute(txt, 7);
}
bool foodEaten(const Snake& S, pos fpos, int row, int col)
{
	return (S.ps[0].r == fpos.r) && (S.ps[0].c == fpos.c);
}

bool food2Eaten(const Snake& S, pos fpos2, int row, int col)
{
	return (S.ps[0].r == fpos2.r) && (S.ps[0].c == fpos2.c);
}


void SnakeExpande(Snake& S)
{
	pos* tempHA = new pos[S.Ssize + 1];
	for (int i = 0; i < S.Ssize; i++)
		tempHA[i + 1] = S.ps[i];   //i+1 used so that we have first index empty of our new array and we canbe able to make new head
	tempHA[0] = tempHA[1];
	delete[]S.ps;
	S.ps = tempHA;
	S.Ssize++;
	S.score++;
	if (S.score == 20)
		S.speedDelay -= 50;
	if (S.score == 40)
		S.speedDelay -= 50;
}


bool validFpos(Snake*& S,int SAsize, const pos fpos, const pos fpos2, level1Herdal* L1H, int L1size,pos L2pos)   //*************should put L2pos here too
{
	for (int i = 0; i < SAsize; i++)
	   for (int j = 0; j < S[i].Ssize; j++)
		   if (((S[i].ps[j].r == fpos.r) && (S[i].ps[j].c == fpos.c)) || ((S[i].ps[j].r == fpos2.r) && (S[i].ps[j].c == fpos2.c))
			   || ((S[i].ps[j].r == L2pos.r) && (S[i].ps[j].c == L2pos.c)))
			   return false;
	for(int i=0;i<L1size;i++)
		if ((L1H[i].r == fpos.r) && (L1H[i].c == fpos.c))
			return false;
	return true;
}

void regeneratefood(Snake*& S,int SAsize, pos& fpos, pos& fpos2, int row, int col, level1Herdal* L1H,int L1size, pos L2pos)
{
	do {
		fpos.r = rand() % row; //taking mod with bounry row will automatically give new value within the boundry.
							   //So now we only have to check that food isn,t created on snake location
		fpos.c = rand() % col;
	} while (!validFpos(S,SAsize, fpos, fpos2,L1H,L1size, L2pos));
}

void regeneratefood2(Snake*& S,int SAsize, pos& fpos, pos& fpos2, int row, int col, level1Herdal* L1H,int L1size, pos L2pos)
{
	do {
		fpos2.r = rand() % row; //taking mod with bounry row will automatically give new value within the boundry.
							   //So now we only have to check that food isn,t created on snake location
		fpos2.c = rand() % col;
	} while (!validFpos(S,SAsize, fpos, fpos2,L1H,L1size, L2pos));
}

void DisplayLayout(int row, int col, Snake* S, int SAsize)
{
	for (int i = 0; i < SAsize; i++)
	{
		SetConsoleTextAttribute(txt, S[i].coloure);
		gotoRowCol(10 * i, col + 4);
		cout << "Current Score of " << i + 1 << " is: " << S[i].score;
		gotoRowCol((10 * i) + 2, col + 4);
		cout << "Current SPEED Delayof " << i + 1 << " is: " << S[i].speedDelay;

		gotoRowCol((10 * i) + 4, col + 4);
		cout << "Conrols are:   ";
		cout << (char)S[i].Ukey;
		gotoRowCol((10 * i) + 5, 13 + col + 4);
		cout << (char)S[i].Lkey << " " << (char)S[i].Dkey << " " << (char)S[i].Rkey;
	}
	SetConsoleTextAttribute(txt, 7);

}
void RemoveDisplayLayout(int row, int col, Snake* S, int SAsize)
{
	for (int i = 0; i < SAsize; i++)
	{
		SetConsoleTextAttribute(txt, S[i].coloure);
		gotoRowCol(10 * i, col + 4);
		cout << "                                              ";
		gotoRowCol((10 * i) + 2, col + 4);
		cout << "                                        ";

		gotoRowCol((10 * i) + 4, col + 4);
		cout << "                       ";
		cout << "    ";
		gotoRowCol((10 * i) + 5, 13 + col + 4);
		cout << "         ";
	}
	SetConsoleTextAttribute(txt, 7);
}

bool SnakeDead(Snake* S,int& SAsize,int row, int col)
{
	for (int i = 0; i < SAsize; i++)
	 for (int j = 2; j < S[i].Ssize; j++)
		 if ((S[i].ps[0].r == S[i].ps[j].r) && (S[i].ps[0].c == S[i].ps[j].c))
		 {
			 if (i == 0 && SAsize == 1)
			 {
				 gotoRowCol(row + 6, 0);
				 cout << "SNAKE DEAD";
				 exit(0);
			 }
			 for (int trans = i; trans < SAsize - 1; trans++)
			 {
				 S[trans] = S[trans + 1];
			 }
			 RemoveSnake(S, SAsize);
			 RemoveDisplayLayout(row, col, S, SAsize);
			 //for (int i = 0; i < S[SAsize - 1].Ssize; i++)
				// S[SAsize - 1].ps[i] = { 200, 200 };
			SAsize--;
			DisplayLayout(row, col, S, SAsize);
			return true;
		}
	return false;
}
bool SnakeTouchL2(Snake* S, int& SAsize, pos& L2pos, int row, int col)
{
	for (int si = 0; si < SAsize; si++)
		for (int j = 0; j < S[si].Ssize; j++)
			if ((L2pos.r == S[si].ps[j].r) && (L2pos.c == S[si].ps[j].c))
			{
				if (si == 0 && SAsize == 1)
				{
					gotoRowCol(row + 6, 0);
					cout << "SNAKE DEAD";
					exit(0);
				}
				for (int trans = si; trans < SAsize - 1; trans++)
				{
					S[trans] = S[trans + 1];
				}
				//for (int i = 0; i < S[SAsize - 1].Ssize; i++)
				   // S[SAsize - 1].ps[i] = { 200, 200 };
				RemoveSnake(S, SAsize);
				RemoveDisplayLayout(row, col, S, SAsize);
				SAsize--;
				DisplayLayout(row, col, S, SAsize);
				return true;
			}
	return false;
}

void restposS(Snake* S, int SAsize, int i, int row, int col)
{
	switch (i)
	{
	case 0:
		S[i].Sdirection = Right;
		for (int j = 0; j < S[i].Ssize; j++)
		{
			S[i].ps[j].r = row / 2;
			S[i].ps[j].c = col / 2;
		}
		break;
	case 1:
		S[i].Sdirection = Left;
		for (int j = 0; j < S[i].Ssize; j++)
		{
			S[i].ps[j].r = 6;
			S[i].ps[j].c = col / 2;
		}
		break;
	case 2:
		S[i].Sdirection = Up;
		for (int j = 0; j < S[i].Ssize; j++)
		{
			S[i].ps[j].r = (row / 2) - 2;
			S[i].ps[j].c = (col / 2) - (col / 4);
		}
		break;
	case 3:
		S[i].Sdirection = Down;
		for (int j = 0; j < S[i].Ssize; j++)
		{
			S[i].ps[j].r = (row / 2) - 2;
			S[i].ps[j].c = (col / 2) + (col / 4);
		}
		break;
	}
}
bool SnakeTouchAnotherSnake(Snake* S, int SAsize,int row, int col)
{
	for (int i = 0; i < SAsize; i++)
		for (int si = 0; si < SAsize; si++)
		  for (int j = 1; j < S[i].Ssize; j++)
			  if ((S[i].ps[0].r == S[si].ps[j].r) && (S[i].ps[0].c == S[si].ps[j].c) && si != i)
			  {
				  RemoveSnake(S, SAsize);
				  restposS(S, SAsize, i, row, col);
				  S[si].score-=5;
				  S[i].score-=5;
				  return true;
			   }
	return false;
}


bool SnakeTouchL1(Snake* S, int SAsize, level1Herdal* L1H, int L1size,int row ,int col)
{
	for (int i = 0; i < L1size; i++)
		for (int si = 0; si < SAsize; si++)
		  for (int j = 0; j < S[si].Ssize; j++)
			  if ((L1H[i].r == S[si].ps[j].r) && (L1H[i].c == S[si].ps[j].c))
			  {
				  RemoveSnake(S, SAsize);
				  restposS(S, SAsize, si, row, col);
				  S[si].score--;
				  return true;
			  }
	return false;
}



void level1(level1Herdal*& L1H ,int row, int col , const int size )
{
	delete[] L1H;
	L1H = new level1Herdal[size];
	
	for (int i = 0; i < size/4; i++)
	{
		L1H[i].r = row / 4;
		L1H[i].c = (col / 4) + i;
		gotoRowCol(L1H[i].r, L1H[i].c);
		cout << (char)-37;

		L1H[i + (size/4)].r = row / 4;
		L1H[i + (size / 4)].c = (3 * (col / 4)) + i;
		gotoRowCol(L1H[i+ (size / 4)].r, L1H[i+ (size / 4)].c);
		cout << (char)-37;
		
		L1H[i+ (size / 2)].r = (3 * (row / 4));
		L1H[i+ (size / 2)].c = (col / 4) + i;
		gotoRowCol(L1H[i+ (size / 2)].r, L1H[i+ (size / 2)].c);
		cout << (char)-37;

		L1H[i+ (3*(size / 4))].r = (3 * (row / 4));
		L1H[i+ (3 * (size / 4))].c = (3 * (col / 4)) + i;
		gotoRowCol(L1H[i+ (3 * (size / 4))].r, L1H[i+ (3 * (size / 4))].c);
		cout << (char)-37;
	}
}
void level2(Snake* S, int SAsize, pos& L2pos, pos fpos2, char& L2sym, int row, int col, level1Herdal* L1H, int L1size)
{
	L2sym = '*';
	L2pos = { 5,5 };
	regeneratefood(S, SAsize, L2pos,fpos2, row, col, L1H, L1size,L2pos);
	gotoRowCol(L2pos.r, L2pos.c);
	cout << L2sym;
}

void GameInfo()
{
	cout << "U have to chose Sankes from 1-4\n\n";
	cout << "Individual Scores and their control\n\n will be displayed !!!\n\n\n\n"
		<<"Game has Bonous food too(only for Multiplayers) -->score+5\n\n"
		    <<" Game has 3 DIFFRENT LEVELS !\n\n\n In Level 1 just avoid stricking\n\n others(if u do your score will be\n\n reduced(of both) and u will be "
		<<"repositioned) and if u hit yourself\n\n U ARE DONE- DEAD\n\n\n Level 2 will start when all snakes has\n\n score more than 3 ,This level\n\n"
		<<" will have HARDELS walls if u\n\n HIT your score will be\n\n reduced and u will be repositioned)\n\n\n "
		<<"LEVEL 3 has bombs in it * if u HIT U ARE DEAD\n\n"
		<< " Control shown as H K P M for Snake 1 are Up,down,Left,right arrow keys on ur keyboad\n\n";
}
int main()
{
	GameInfo();
	system("pause");
	system("cls");
	int row = 50, col = 60;   //Num of rows and cols to dife boundry 
	Snake* S;
	level1Herdal* L1H;
	const int L1size = 40;
	L1H = new level1Herdal[L1size]{};
	pos L2pos{-50,-50};
	char L2sym=' ';
	int L1run = 0;
	int L2run = 0;

	int SAsize=0;
	pos fpos;
	char fsym;
	pos fpos2;
	char fsym2;
	char kbEnteredch;
	char kbEnteredch2='/';
	time_t st = time(0);
	time_t et = time(0);
	time_t Totalt = time(0);

	init(S,SAsize, row, col, fpos, fsym, fpos2, fsym2);
	(const int)SAsize;
	foodDisplay(fsym, fpos);
	diplayBoundry(row, col);
	DisplayLayout(row, col, S,SAsize);
	int f2count=0;
	while (1)
	{
		
		int scorePassed = 0;
		int scorePassedL2 = 0;
		for (int i = 0; i < SAsize; i++)
		{
			if (S[i].score >= 3)   //S[i].score == 3 here 3 is saying if that snake has 3 score Scorepassed++ thus if all snakes has score 3
				                   //only then scorePassed will be == SAsize
				scorePassed++;
			if (S[i].score >= 5)
				scorePassedL2++;
		}
		if (scorePassed == SAsize)
		{
			if (L1run == 0)
			{
				gotoRowCol(row + 2, col + 3);
				cout << "Entering in level 2\n";
				level1(L1H, row, col, L1size);
				L1run++;
			}
		}
		if (scorePassedL2 == SAsize)
		{
			if (L2run == 0)
			{
				gotoRowCol(row + 2, col + 3);
				cout << "Entering in level 3\n";
				level2(S, SAsize, L2pos,fpos2, L2sym, row, col, L1H, L1size);
				L2run++;
			}
		}
		if (_kbhit())
		{
			kbEnteredch = _getch();
			if ((int)kbEnteredch == 224)
				kbEnteredch2 = _getch();
			DirectionChange(kbEnteredch, kbEnteredch2, S,SAsize);
			//break;
		}
		RemoveSnake(S,SAsize);
		MoveSnake(S, SAsize, row, col);
		//diplayBoundry(row, col);
		DisplaySnake(S, SAsize);

		for (int i = 0; i < SAsize; i++)
		{
			if (foodEaten(S[i], fpos, row, col))
			{
				RemoveDisplayLayout(row, col, S, SAsize);
				regeneratefood(S,SAsize, fpos, fpos2, row, col, L1H, L1size, L2pos);
				SnakeExpande(S[i]);
				foodDisplay(fsym, fpos);
				DisplayLayout(row, col, S, SAsize);

			}
		}

		

		if (SnakeDead(S,SAsize,row,col))
		{
			gotoRowCol(row + 2, col + 3);
			cout << "SAKE EAT HIMSEALF!!! SNAKE DEAD\n";
			gotoRowCol(row + 2, col + 3);
			cout << "                                   ";
		}
		if (SnakeTouchAnotherSnake(S, SAsize,row,col))
		{
			RemoveDisplayLayout(row, col, S, SAsize);
			gotoRowCol(row + 2, col + 3);
			cout << "Snake Hit  Score -5\n";
			Sleep(1000);
			DisplayLayout(row, col, S, SAsize);
			gotoRowCol(row + 2, col + 3);
			cout << "            ";
		}
		if (SnakeTouchL1(S, SAsize, L1H, L1size,row,col))
		{
			DisplayLayout(row, col, S, SAsize);
			level1(L1H, row, col, L1size);
			gotoRowCol(row + 3, 0);
			cout << "Snake Hit Walls score -1 !!!\n";
			Sleep(1000);
			gotoRowCol(row + 3, 0);
			cout << "                             ";
		}
		if (SnakeTouchL2(S, SAsize, L2pos, row, col))
		{
			level2(S, SAsize, L2pos,fpos2, L2sym, row, col, L1H, L1size);
			DisplayLayout(row, col, S, SAsize);
		}
		Sleep(100);
		et = time(0);
		Totalt = et - st;
		gotoRowCol(row + 1, 0);
		cout << Totalt;
		
		if (Totalt == 20 && SAsize > 1)
		{
			f2count = 0;
			st = time(0);
			gotoRowCol(row + 1, 0);
			cout << "   ";
		}

			if (Totalt==10 && f2count == 0 &&SAsize>1)
			{
				regeneratefood2(S, SAsize, fpos, fpos2, row, col, L1H, L1size, L2pos);
				foodDisplay(fsym2, fpos2);
				DisplayLayout(row, col, S, SAsize);
				f2count++;
				f2count++;

			}
			else if(Totalt == 19 && SAsize > 1)
			{
				gotoRowCol(fpos2.r, fpos2.c);
				cout << " ";
				fpos2.r = 0, fpos2.c = 0;

			}
			for (int i = 0; i < SAsize; i++)
			{
				if (food2Eaten(S[i], fpos2, row, col) && SAsize > 1)
				{
					S[i].score += 5;
					DisplayLayout(row, col, S, SAsize);
				}
			}
		
	}

}
