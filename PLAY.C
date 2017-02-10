#include<stdio.h>
#include<conio.h>
#include<alloc.h>

#define UP 72
#define BACKSPACE 8
#define max(a,b) (a>b)?a:b
int in=1;
typedef struct player
{
	char name[30];
	int run,wkt,t_match;
	float avg,eco;

}player;

typedef struct team
{
	char name[30];
	int win,loss,t_match;
	player p[11];
}team;
typedef struct player_live
{
	char name[20];
	int run_scored,ball_played,wkt,run_given,ball_del,t_match;
}player_live;

struct ball
{
	int score,type;	   /*   0 - Wicket
				1 - Normal delivery
				2 - Wide Ball
				3 - No Ball	*/

	struct ball *next;
};
struct over
{
	struct ball *ball;
	struct over *next;
};
typedef struct team_live
{
	char name[20];
	int score,wkt;
	struct over *over;
	player_live p[11];
}team_live;
void game(team_live *, team_live *, int);
void display(team_live *,int , int );
void main()
{
	FILE *fp;
	int i,t,ov;
	team team1,team2;
	team_live t1,t2;
	char s[20][30],path[80],bat;
	fp=fopen("c:\\tc\\team\\teaml.dat","r");
	i=0;
	clrscr();
	while(!feof(fp))
	{
		printf("\n%d. ",i);
		fread(&s[i],sizeof(*s),1,fp);
		printf("%s",s[i]);
		i++;
	}
	fclose(fp);

	printf("Choose two teams\n ");

	printf("Team A ?\t ");
	scanf("%d",&t);
	strcpy(path,"c:\\tc\\team\\");
	strcat(path,s[t]);
	strcat(path,".dat");
	fp=fopen(path,"r");
	printf("%s",path);
	fread(&team1,sizeof(team),1,fp);
	fclose(fp);
	printf("\nTeam B ?\t ");
	scanf("%d",&t);
	strcpy(path,"c:\\tc\\team\\");
	strcat(path,s[t]);
	strcat(path,".dat");
	printf("%s",path);
	fp=fopen(path,"r");
	fread(&team2,sizeof(team),1,fp);

	printf("\nEnter the no of overs  \t ");
	scanf("%d",&ov);
	fflush(stdin);
	printf("\nBatting team\t");
	scanf("%c",&bat);

	clrscr();


	strcpy(t1.name,team1.name);
	strcpy(t2.name,team2.name);
	t1.over=t2.over=NULL;
	t1.score=0;
	t1.wkt=0;
	t2.score=0;
	t2.wkt=0;
	for(i=0;i<11;i++)
	{
		strcpy(t1.p[i].name,team1.p[i].name);
		strcpy(t2.p[i].name,team2.p[i].name);
		t1.p[i].run_scored=0;
		t1.p[i].ball_played=0;
		t1.p[i].ball_del=0;
		t1.p[i].wkt=0;
		t1.p[i].run_given=0;
		t1.p[i].t_match=team1.p[i].t_match;
		t2.p[i].run_scored=0;
		t2.p[i].ball_played=0;
		t2.p[i].ball_del=0;
		t2.p[i].wkt=0;
		t2.p[i].run_given=0;
		t2.p[i].t_match=team2.p[i].t_match;
	}
	if(bat=='a' || bat=='A')
	{
		game(&t1,&t2,ov);
		game(&t2,&t1,ov);
	}
	else
	{
		game(&t2,&t1,ov);
		game(&t1,&t2,ov);
	}





}
//*f_ball - newover->ball
void game(team_live *A, team_live *B, int over)
{
	int batsman1=0,batsman2=1,bowler=6,temp,over_count=0,ball_count,limit;
	struct over *l_over,*newover;
	struct ball *l_ball,*newball;
	char s[5];
	B->over=NULL;
	l_over=B->over;
	A->p[batsman1].t_match++;
	A->p[batsman2].t_match++;
	while(over_count<over)
	{
		clrscr();

		gotoxy(1,1);
		printf("+------------------------------+------------------------------+");
		printf("\n|\t%s Vs %s",A->name,B->name);
		gotoxy(32,2);
		printf("|        CRICKET MANAGER       |");
		printf("\n+------------------------------+------------------------------+");
		newover=(struct over*)malloc(sizeof(struct over));
		newover->next=NULL;
		newover->ball=NULL;
		limit=6;
		for(ball_count=0;ball_count<limit;ball_count++)
		{
			newball=(struct ball*)malloc(sizeof(struct ball));
			newball->next=NULL;
			gotoxy(70,15);
			printf("%d/%d",A->score,A->wkt);
			if(B->score>0)
			{
				gotoxy(68,12);
				printf("Target : %d",(B->score)+1);
			}
			gotoxy(1,4);
			printf("+------------------------------+------------------------------+");
			printf("\n| BATSMAN : %s                 ",A->p[batsman1].name);
			gotoxy(32,5);
			printf("| BOWLER : %s                  ",B->p[bowler].name);
			gotoxy(63,5);
			printf("|");
			printf("\n+------------------------------+------------------------------+");

			printf("\n\n+------------------------------+------------------------------+");
			printf("\n|          Over:Ball           |              Runs            |");
			printf("\n+------------------------------+------------------------------+");
			again:
			gotoxy(1,11+(ball_count*2));
			printf("|            %2d.%d              |                              |",over_count+1,ball_count+1);
			printf("\n+------------------------------+------------------------------+");
			gotoxy(40,11+(ball_count*2));
			fflush(stdin);
			scanf("%s",s);
			if(s[0]=='W')
				newball->type=0;
			else if (s[0]=='0'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=0;
			}
			else if (s[0]=='1'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=1;
			}
			else if (s[0]=='2'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=2;
			}
			else if (s[0]=='3'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=3;
			}
			else if (s[0]=='4'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=4;
			}
			else if (s[0]=='5'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=5;
			}
			else if (s[0]=='6'&& s[1]=='\0')
			{
				newball->type=1;
				newball->score=6;
			}
			else if(s[0]=='w' && s[1]=='d')
				newball->type=2;
			else if(s[0]=='n'&& s[2]=='\0')
			{
				newball->type=3;
				if(s[1]=='0')
					newball->score=0;
				else if(s[1]=='1')
					newball->score=1;
				else if(s[1]=='2')
					newball->score=2;
				else if(s[1]=='3')
					newball->score=3;
				else if(s[1]=='4')
					newball->score=4;
				else if(s[1]=='5')
					newball->score=5;
				else if(s[1]=='6')
					newball->score=6;
				else goto again;
			}
			else goto again;
			if(newball->type==0)         //wicket
			{
				A->p[batsman1].ball_played++;
				batsman1=max(batsman1,batsman2)+1;
				A->p[batsman1].t_match++;
				newball->score=0;
				A->wkt++;
				B->p[bowler].ball_del++;
				B->p[bowler].wkt++;
				if(A->wkt==10)
				{
					display(A, over_count, ball_count);
					return;
				}
			}
			if(newball->type==1)   	     //normal  delivery
			{
				A->p[batsman1].run_scored+=newball->score;
				A->p[batsman1].ball_played++;
				B->p[bowler].run_given+=newball->score;
				B->p[bowler].ball_del++;
				if(newball->score==1 || newball->score==3)
				{
					temp=batsman1;
					batsman1=batsman2;
					batsman2=temp;
				}
			}
			if(newball->type==2)         //wide ball
			{
				newball->score=1;
				B->p[bowler].run_given+=newball->score;
				limit++;

			}
			if(newball->type==3)         //no ball
			{

				A->p[batsman1].run_scored+=newball->score;
				A->p[batsman1].ball_played++;
				B->p[bowler].ball_del++;
				if(newball->score==1 || newball->score==3)
				{
					temp=batsman1;
					batsman1=batsman2;
					batsman2=temp;
				}
				newball->score++;
				B->p[bowler].run_given+=newball->score;
			}
			A->score+=newball->score;
			if(newover->ball!=NULL)
			{
				l_ball=newball;
				l_ball=l_ball->next;
			}
			else
			{
				newover->ball=l_ball=newball;
			}

		}
		temp=batsman1;
		batsman1=batsman2;
		batsman2=temp;
		if(bowler==10)
			bowler=0;
		else
			bowler++;
		over_count++;
		if(B->over!=NULL)
		{
			l_over=newover;
			l_over=l_over->next;
		}
		else
		{
			B->over=l_over=newover;
		}

	}
	display(A,over,0);

}

void display(team_live *A,int tovr, int tball)
{
	int i;
	char ch;

	Display:
	clrscr();
	printf("\n\n\n");
	printf("                   INNINGS %d\n", in);
	printf("     Team Name: %s                           Final Score: %d\n", A->name, A->score);
	printf("Overs: %d.%d                                     Wickets: %d\n", tovr, tball, A->wkt);
	printf("                     BATTING ORDER    \n");
	printf("  ----------------------------------------------------------\n");
	printf("   Player Name    |    Balls    |   Runs    |   Strike Rate\n");
	printf("----------------------------------------------------------");
	for(i=0; i<6; i++)
	{
		if(A->p[i].ball_played==0 && A->p[i].run_scored==0)
			printf("\n%3s    |   %d    |   %d    |    -  \n", A->p[i].name, A->p[i].ball_played, A->p[i].run_scored);
		else if(A->p[i].run_scored==0)
			printf("\n%3s    |   %d    |   %d    |   0.00%  \n", A->p[i].name, A->p[i].ball_played, A->p[i].run_scored);
		else
			printf("\n%3s    |   %d    |   %d    |   %.02f%  \n", A->p[i].name, A->p[i].ball_played, A->p[i].run_scored, ((float)((A->p[i].run_scored)/(A->p[i].ball_played))*100));
		printf("------------------------------------------------------------\n");

	}

    fflush(stdin);

    ch=getch();
    if(ch==BACKSPACE)
	    return;

    for(;i<11;i++)
    {
	if(A->p[i].ball_played==0 && A->p[i].run_scored==0)
		printf("\n%3s    |   %d    |   %d    |    -  \n", A->p[i].name, A->p[i].ball_played, A->p[i].run_scored);
	else if(A->p[i].run_scored==0)
		printf("\n%3s    |   %d    |   %d    |   0.00%  \n", A->p[i].name, A->p[i].ball_played, A->p[i].run_scored);
	else
		printf("\n%3s    |   %d    |   %d    |   %.02f%  \n", A->p[i].name, A->p[i].ball_played, A->p[i].run_scored, ((float)((A->p[i].run_scored)/(A->p[i].ball_played))*100));
	printf("------------------------------------------------------------\n");

    }
    ch=getch();
    if(ch==UP)
	goto Display;

	in++;
	getch();
}

