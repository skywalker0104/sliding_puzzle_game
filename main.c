#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <io.h>
#include<fcntl.h>
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}
void border()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),48);
}
void C1()
{
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),70);
}
void C2()
{
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),246);
}

void WHITE()
{
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void L_GREEN()
{
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}

typedef struct{
    int m,n; // chi so hang cot cua ban do
    int A[100][100];// ban do tro choi
    int r,c; // vi tri hangg cot cua o trong
    int move;
}State;

typedef struct{
	char name[20];
	int score;
}Player;

int i,j;
void init_state(State *S,char *s)
{
	FILE *f=fopen(s,"r");
	fscanf(f,"%d%d",&S->m,&S->n);
	for (i=0;i<(S->m);i++)
	{
		for (j=0;j<(S->n);j++)
		{
			fscanf(f,"%d",&S->A[i][j]);
		}
	}
	fscanf(f,"%d%d",&S->r,&S->c);
	//fclose(f);
}
void print_space(int n)
{
	int i;
	for (i=1;i<=n;i++)
	{
		printf(" ");
	}
}
void print_title();
void print_diem();
void print_state(State S)
{
	print_title();

	printf("\n\n\n\n");
	print_space(10); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"C\x00C1\CH CH\x01A0I");
	_setmode(_fileno(stdout), _O_TEXT);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	print_space(10); printf("%cPhim w: day o phia duoi len tren  %c\n",186,186);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"Ph\x00ED\m w: \x0111\x1EA9\y \x00F4 ph\x00ED\a d\x1EDB\i");
	_setmode(_fileno(stdout), _O_TEXT);
	print_space(10); printf("%cPhim s: day o phia tren xuong duoi%c\n",186,186);
	print_space(10); printf("%cPhim a: day o ben phai sang trai  %c\n",186,186);
	print_space(10); printf("%cPhim d: day o ben trai sang phai  %c\n",186,186);
	print_space(10); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
		print_diem();
	border();
	gotoxy(55,10); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,203,205,205,205,205,205,203,205,205,205,205,205,203,205,205,205,205,205,187);
	int k=11;
	for (i=0;i<(S.m);i++)
	{
		gotoxy(55,k);
		for (j=0;j<(S.n);j++)
		{
			border();
			if (j==0) printf("%c",186);
			if (S.A[i][j]==S.m*S.n) printf("     %c",186);
			else if (S.A[i][j]==1 || S.A[i][j]==3 || S.A[i][j]==6 || S.A[i][j]==8 || S.A[i][j]==9 || S.A[i][j]==11 || S.A[i][j]==14 )
			{
				C1();
				printf("%5d",S.A[i][j]);
				WHITE();
				border();
				printf("%c",186);
				WHITE();
			}
			else
			{
				C2();
				printf("%5d",S.A[i][j]);
				WHITE();
				border();
				printf("%c",186);
				WHITE();
			}

			
		}
		
		printf("\n");
		k++;
		gotoxy(55,k);

		if (i==S.m-1) 
		{
			border();
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,202,205,205,205,205,205,202,205,205,205,205,205,202,205,205,205,205,205,188);
			WHITE();
		}
		else
		{
			border();
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",204,205,205,205,205,205,206,205,205,205,205,205,206,205,205,205,205,205,206,205,205,205,205,205,185);
			WHITE();
		}

		k++;
	}
	gotoxy(52,20); printf("%cTYPE S: save and exit          %c\n",186,186);
	gotoxy(52,21);printf("%cTYPE L: load previous save file%c\n",186,186);
}
int up(State S, State *N)
{
	
	if (S.r>0)
	{
		*N=S;
		int temp=N->A[N->r][N->c];
		N->A[N->r][N->c]=N->A[N->r-1][N->c];
		N->A[N->r-1][N->c]=temp;
		N->r--;
		return 1;
	}
	return 0;
}
int down(State S, State *N)
{
	if (S.r<S.m-1)
	{
		*N=S;
		int temp=N->A[N->r][N->c];
		N->A[N->r][N->c]=N->A[N->r+1][N->c];
		N->A[N->r+1][N->c]=temp;
		N->r++;
		return 1;
	}
	return 0;
}
int left(State S, State *N)
{
	if (S.c>0)
	{
		*N=S;
		int temp=N->A[N->r][N->c];
		N->A[N->r][N->c]=N->A[N->r][N->c-1];
		N->A[N->r][N->c-1]=temp;
		N->c--;
		return 1;
	}
	return 0;
}
int right(State S, State *N)
{
	if (S.c<S.n-1)
	{
		*N=S;
		int temp=N->A[N->r][N->c];
		N->A[N->r][N->c]=N->A[N->r][N->c+1];
		N->A[N->r][N->c+1]=temp;
		N->c++;
		return 1;
	}
	return 0;
}
int is_finished(State S)
{
	for (i=0;i<S.m;i++)
	{
		for (j=0;j<S.n;j++)
		{
			if (S.A[i][j]!=i*S.n+j+1)
			return 0;
		}
	}
	return 1;
}

void init_state_2(State *S,State N)
{
	//FILE *f=fopen(s,"r");
	//fscanf(f,"%d%d",&S->m,&S->n);
	S->m=4; S->n=4;
	S->r=3; S->c=3;
	S->move=0;
	for (i=0;i<(S->m);i++)
	{
		for (j=0;j<(S->n);j++)
		{
			S->A[i][j]=i*S->n+j+1;
		}
	}
	srand(time(0));
	i=rand();
	while (1)
	{
		int ran=rand();
		if (ran%2==0) if(up(*S,&N)) *S=N;
		if (ran%3==0) if(down(*S,&N)) *S=N;
		if (ran%5==0) if(left(*S,&N)) *S=N;
		if (ran%7==0) if(right(*S,&N)) *S=N;
		i--;
		if (i==0) break;
	}
}
void save(State S, char *ch)
{
	FILE *f=fopen(ch,"w");
	fprintf(f,"%d %d\n",S.m,S.n);
	for (i=0;i<S.m;i++)
	{
		for (j=0;j<S.n;j++)
		{
			fprintf(f,"%d ",S.A[i][j]);
		} fprintf(f,"\n");
	}
	fprintf(f,"%d %d\n%d",S.r,S.c,S.move);
	
	fclose(f);
}
void load(State *S,char *ch)
{
	FILE *f=fopen(ch,"r");
	fscanf(f,"%d%d",&S->m,&S->n);
	for (i=0;i<(S->m);i++)
	{
		for (j=0;j<(S->n);j++)
		{
			fscanf(f,"%d",&S->A[i][j]);
		}
	}
	fscanf(f,"%d%d",&S->r,&S->c);
	fscanf(f,"%d",&S->move);
}
Player bang_diem[6];
void print_diem()
{
	FILE *f=fopen("highscore.txt","r");
	for (i=0;i<5;i++)
	{
		fscanf(f,"%s %d\n",&bang_diem[i].name,&bang_diem[i].score);
	}
	L_GREEN();
	gotoxy(85,9);printf("________<<HIGHSCORE>>________\n");
	for (i=0;i<5;i++)
	{
		gotoxy(85,10+i); printf("%c%d. %-20s %3d%c\n",186,i+1,bang_diem[i].name,bang_diem[i].score,186);
	}
	gotoxy(85,10+i); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
	WHITE();
	fclose(f);
}
void sapxep_diem()
{
	Player temp;
	for (i=0;i<6;i++)
	{
		for (j=i;j<6;j++)
		{
			if (bang_diem[i].score>bang_diem[j].score)
			{
				temp=bang_diem[i];
				bang_diem[i]=bang_diem[j];
				bang_diem[j]=temp;
			}
		}
		
	}
	FILE *f=fopen("highscore.txt","w");
	for (i=0;i<5;i++)
	{
		fprintf(f,"%s %d\n",bang_diem[i].name,bang_diem[i].score);
	}
	fclose(f);
}
void print_title()
{
	gotoxy(0,0);
	L_GREEN();
 	print_space(18);printf("           ____ .________        __________                     .__\n");         
    print_space(18);printf("          /_   ||   ____/        \\______   \\__ _________________|  |   ____\n"); 
 	print_space(18);printf("          |   ||____  \\   ______ |     ___/  |  \\___   /\\___   /  | _/ __ \\\n");
 	print_space(18);printf("          |   |/       \\ /_____/ |    |   |  |  //    /  /    /|  |_\\  ___/\n"); 
 	print_space(18);printf("          |___/______  /         |____|   |____//_____ \\/_____ \\____/\\___  >\n");
    print_space(18);printf("                     \\/                               \\/      \\/         \\/\n");
    WHITE();
}

void maximizewindow(){
	HANDLE handle = GetConsoleWindow();
	ShowWindow(handle, SW_SHOWMAXIMIZED);
}

int main()
{
	system("cls");
	maximizewindow();
	PlaySound(TEXT("G:\\Sliding Puzzles\\bm.wav"),NULL,SND_ASYNC|SND_LOOP);
	State S,N;
	S.move=0;
//	srand(time(0));
	init_state_2(&S,N);
	print_state(S);
	
	while(!is_finished(S))
	{
	//	Sleep(250);
		char ch=getch();
		if (ch==83)
		{
			save(S,"save.txt");
			L_GREEN();
			gotoxy(52,22);
			printf("<<GAME SAVED>>\n");
			WHITE();
			break;
		}
		if (ch==76)
		{
			load(&S,"save.txt");
			system("cls");
			print_state(S);
			L_GREEN();
			print_space(52);
			printf("<<LOAD COMPLETED>>\n");
			WHITE();
		}
    	if (ch=='d') // move right
    	{
   			if (left(S,&N)) S=N;
   			print_state(S);
   			S.move++;
		}
		if (ch=='a') // move left
    	{
   			if (right(S,&N)) S=N;
   			print_state(S);
   			S.move++;
		}
		if (ch=='w') // move up
    	{
   			if(down(S,&N)) S=N;
   			print_state(S);
   			S.move++;
		}
		if (ch=='s') // move down
   		{
   			if(up(S,&N)) S=N;
   			print_state(S);
   			S.move++;
		}
	}
    if (is_finished(S)) 
    {
    	L_GREEN();
    	print_space(52);		printf("<<YOU WIN>>\n");
		print_space(52); printf("<<YOU SOVLED THE PUZZLE WITH %d MOVES>>\n",S.move);
		WHITE();
		char ch[20];
		L_GREEN();
		printf("NHAP TEN CUA BAN:");
		scanf("%s",ch);
		WHITE();
		strcpy(bang_diem[5].name,ch);
		bang_diem[5].score=S.move;
		sapxep_diem();
	}
    
    return 0;
}
