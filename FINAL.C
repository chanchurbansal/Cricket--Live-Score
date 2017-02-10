#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<alloc.h>
#include<string.h>

#define BACKSPACE 8
#define ENTER 13
#define UP 72
#define DOWN 80
#define bk_color BLACK
#define max(a,b) ((a) > (b) ? (a) : (b))
int in=1;


typedef struct player
{
	char name[30];
	int run,wkt,t_match;

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


void instructions();
void start_screen();
void createnewteam();
void league_sum()
{
	char f_name[30];
	team t;
	char  path[80];
	FILE *fp;
	FILE *fp1;
	printf("			    LEAGUE SUMMARY\n ");
	printf("	        	     POINTS TABLE    ");
	gotoxy(1,4);
	printf("+------------------------------+---------------------------------+");
	printf("\n| TEAM NAME                  ");
	gotoxy(22,5);
	printf("|  MATCHES PLAYED                ");
	gotoxy(40,5);
	printf("|   WIN                         ");
	gotoxy(50,5);
	printf("|  LOST                          ");
	gotoxy(60,5);
	printf("|  TIE                            ");

	fp=fopen("C:\\tc\\team\\teaml.dat","rb");
	while(fread(&f_name,sizeof(f_name),1,fp))
	{

	    strcpy(path,"C:\\tc\\team\\");
	    strcat(path,f_name);
	    strcat(path,".dat");
	    fp1=fopen(path,"rb");
	    fread(&t,sizeof(t),1,fp1);
	    fclose(fp1);

	    printf("\n");
	    gotoxy(1,wherey());
	    printf("|%s",t.name);
	    gotoxy(22,wherey());
	    printf("|    %d",t.t_match);
	    gotoxy(40,wherey());
	    printf("|    %d",t.win);
	    gotoxy(50,wherey());
	    printf("|    %d",t.loss);
	    gotoxy(60,wherey());
	    printf("|  %d  |",t.t_match-t.win-t.loss);
	}
	getch();
	start_screen();
}

void game(team_live *, team_live *, int);
void display(team_live *,int , int );
void startmatch()
{
	FILE *fp;
	int i,t,ov;
	int gd=DETECT,gm;
	team team1,team2;
	team_live t1,t2;
	char s[20][30],path[80],bat;
	fp=fopen("c:\\tc\\team\\teaml.dat","r");
	i=0;
	clrscr();
	while(fread(&s[i],sizeof(*s),1,fp))
	{
		printf("\n%d. ",i+1);

		printf("%s",s[i]);
		i++;
	}
	fclose(fp);

	printf("\n\nChoose two teams\n ");

	printf("Team A ?\t ");
	scanf("%d",&t);
	t--;
	strcpy(path,"c:\\tc\\team\\");
	strcat(path,s[t]);
	strcat(path,".dat");
	fp=fopen(path,"r");
	//printf("%s",path);
	fread(&team1,sizeof(team),1,fp);
	fclose(fp);
	printf("\nTeam B ?\t ");
	scanf("%d",&t);
	t--;
	strcpy(path,"c:\\tc\\team\\");
	strcat(path,s[t]);
	strcat(path,".dat");
	//printf("%s",path);
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
		t1.p[i].t_match=0;
		t2.p[i].run_scored=0;
		t2.p[i].ball_played=0;
		t2.p[i].ball_del=0;
		t2.p[i].wkt=0;
		t2.p[i].run_given=0;
		t2.p[i].t_match=0;
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

	if(t1.score>t2.score)
	{
		team1.win++;
		team2.loss++;
	}
	else if(t2.score>t1.score)
	{
		team1.loss++;
		team2.win++;
	}
	team1.t_match++;
	team2.t_match++;
	for(i=0;i<11;i++)
	{
		team1.p[i].run+=t1.p[i].run_scored;
		team1.p[i].wkt+=t1.p[i].wkt;
		team1.p[i].t_match+=t1.p[i].t_match;

		team2.p[i].run+=t2.p[i].run_scored;
		team2.p[i].wkt+=t2.p[i].wkt;
		team2.p[i].t_match+=t2.p[i].t_match;
	}

	strcpy(path,"c:\\tc\\team\\");
	strcat(path,team1.name);
	strcat(path,".dat");
	fp=fopen(path,"w");
	fwrite(&team1,sizeof(team),1,fp);
	fclose(fp);

	strcpy(path,"c:\\tc\\team\\");
	strcat(path,team2.name);
	strcat(path,".dat");
	fp=fopen(path,"w");
	fwrite(&team2,sizeof(team),1,fp);
	fclose(fp);


	initgraph(&gd,&gm,"C:\\TC\\BGI");

	cleardevice();
	setbkcolor(GREEN);
	setcolor(RED);
	settextstyle(10,0,4);
	if(t1.score>t2.score)
	{
		outtextxy(130,100,"Congratulations");
		outtextxy(250,180,team1.name);
	}
	else if(t2.score>t1.score)
	{
		outtextxy(130,100,"Congratulations");
		outtextxy(250,180,team2.name);
	}
	else
	{
		outtextxy(130,100,"DRAW");
	}
	getch();
	closegraph();
	league_sum();


}

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
			if(A->score>B->score && B->score>0)
			{
				return;
			}
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
				if(newball->score==1 || newball->score==3 || newball->score==5)
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
	int sr;
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
		{
			printf("\n%s",A->p[i].name);
			gotoxy(19,wherey());
			printf("|   %d",A->p[i].ball_played);
			gotoxy(33,wherey());
			printf("|   %d",A->p[i].run_scored);
			gotoxy(45,wherey());
			printf("|   -  \n");

		}
		else if(A->p[i].run_scored==0)
		{
			printf("\n%s",A->p[i].name);
			gotoxy(19,wherey());
			printf("|   %d",A->p[i].ball_played);
			gotoxy(33,wherey());
			printf("|   %d",A->p[i].run_scored);
			gotoxy(45,wherey());
			printf("|   0.00%  \n");

		}
		else
		{
			sr=A->p[i].run_scored*100;
			sr/=A->p[i].ball_played;

			printf("\n%s",A->p[i].name);
			gotoxy(19,wherey());
			printf("|   %d",A->p[i].ball_played);
			gotoxy(33,wherey());
			printf("|   %d",A->p[i].run_scored);
			gotoxy(45,wherey());
			printf("|   %d%  \n",sr);

		}
		printf("------------------------------------------------------------\n");

	}

    fflush(stdin);

    ch=getch();
    if(ch==BACKSPACE)
	    return;

    for(;i<11;i++)
    {
	if(A->p[i].ball_played==0 && A->p[i].run_scored==0)
		{
			printf("\n%s",A->p[i].name);
			gotoxy(19,wherey());
			printf("|   %d",A->p[i].ball_played);
			gotoxy(33,wherey());
			printf("|   %d",A->p[i].run_scored);
			gotoxy(45,wherey());
			printf("|   -  \n");

		}
		else if(A->p[i].run_scored==0)
		{
			printf("\n%s",A->p[i].name);
			gotoxy(19,wherey());
			printf("|   %d",A->p[i].ball_played);
			gotoxy(33,wherey());
			printf("|   %d",A->p[i].run_scored);
			gotoxy(45,wherey());
			printf("|   0.00%  \n");

		}
		else
		{
			sr=A->p[i].run_scored*100;
			sr/=A->p[i].ball_played;

			printf("\n%s",A->p[i].name);
			gotoxy(19,wherey());
			printf("|   %d",A->p[i].ball_played);
			gotoxy(33,wherey());
			printf("|   %d",A->p[i].run_scored);
			gotoxy(45,wherey());
			printf("|   %d%  \n",sr);

		}
		printf("------------------------------------------------------------\n");


    }
    ch=getch();
    if(ch==UP)
	goto Display;

	in++;
	getch();
}


void g_init()
{

	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");

}



void start_screen()
{

	int i=1;
	char ch;
	g_init();

	cleardevice();

	setbkcolor(BLACK);
	settextstyle(10,0,5);
	outtextxy(20,30,"CRICKET MANAGER");

	settextstyle(1,0,3);
	setfillstyle(SOLID_FILL,RED);
	setcolor(RED);
	rectangle(180,160,420,190);
	floodfill(190,170,RED);

	setcolor(GREEN);
	outtextxy(190,160,"Start a Match");
	outtextxy(190,200,"Create Team");
	outtextxy(190,240,"League Summary");
	outtextxy(190,280,"About the Software");

	fflush(stdin);

	while(ch!=ENTER)
	{
		if(ch==UP)
		{

			if(i==1)
			{
				i=4;

				setcolor(bk_color);
				rectangle(180,160,420,190);
				setfillstyle(SOLID_FILL,bk_color);
				floodfill(190,170,bk_color);

				setcolor(RED);
				rectangle(180,280,420,310);
				setfillstyle(SOLID_FILL,RED);
				floodfill(190,290,RED);

				setcolor(GREEN);
				outtextxy(190,160,"Start a Match");
				outtextxy(190,280,"About the Software");
			}
			else if(i==2)
			{
				i=1;

				setcolor(bk_color);
				setfillstyle(SOLID_FILL,bk_color);
				rectangle(180,200,420,230);
				floodfill(190,210,bk_color);

				setcolor(RED);
				rectangle(180,160,420,190);
				setfillstyle(SOLID_FILL,RED);
				floodfill(190,170,RED);

				setcolor(GREEN);
				outtextxy(190,160,"Start a Match");
				outtextxy(190,200,"Create Team");
			}
			else if(i==3)
			{
				i=2;

				setcolor(bk_color);
				setfillstyle(SOLID_FILL,bk_color);
				rectangle(180,240,420,270);
				floodfill(190,250,bk_color);

				setcolor(RED);
				rectangle(180,200,420,230);
				setfillstyle(SOLID_FILL,RED);
				floodfill(190,210,RED);

				setcolor(GREEN);
				outtextxy(190,240,"League Summary");
				outtextxy(190,200,"Create Team");
			}
			else if(i==4)
			{
				i=3;

				setcolor(bk_color);
				setfillstyle(SOLID_FILL,bk_color);
				rectangle(180,280,420,310);
				floodfill(190,290,bk_color);

				setcolor(RED);
				rectangle(180,240,420,270);
				setfillstyle(SOLID_FILL,RED);
				floodfill(190,250,RED);

				setcolor(GREEN);
				outtextxy(190,240,"League Summary");
				outtextxy(190,280,"About the Software");
			}

		 }
		 else if(ch==DOWN)
		 {
			if(i==1)
			{
				i=2;

				setcolor(RED);
				rectangle(180,200,420,230);
				setfillstyle(SOLID_FILL,RED);
				floodfill(190,210,RED);

				setcolor(bk_color);
				setfillstyle(SOLID_FILL,bk_color);
				rectangle(180,160,420,190);
				floodfill(190,170,bk_color);

				setcolor(GREEN);
				outtextxy(190,160,"Start a Match");
				outtextxy(190,200,"Create Team");
			}
			else if(i==2)
			{
				i=3;

				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				rectangle(180,240,420,270);
				floodfill(190,250,RED);

				setcolor(bk_color);
				rectangle(180,200,420,230);
				setfillstyle(SOLID_FILL,bk_color);
				floodfill(190,210,bk_color);

				setcolor(GREEN);
				outtextxy(190,240,"League Summary");
				outtextxy(190,200,"Create Team");
			}
			else if(i==3)
			{
				i=4;

				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				rectangle(180,280,420,310);
				floodfill(190,290,RED);

				setcolor(bk_color);
				rectangle(180,240,420,270);
				setfillstyle(SOLID_FILL,bk_color);
				floodfill(190,250,bk_color);

				setcolor(GREEN);
				outtextxy(190,240,"League Summary");
				outtextxy(190,280,"About the Software");
			}
			else if(i==4)
			{
				i=1;

				setcolor(RED);
				setfillstyle(SOLID_FILL,RED);
				rectangle(180,160,420,190);
				floodfill(190,170,RED);

				setcolor(bk_color);
				rectangle(180,280,420,310);
				setfillstyle(SOLID_FILL,bk_color);
				floodfill(190,290,bk_color);

				setcolor(GREEN);
				outtextxy(190,280,"About the Software");
				outtextxy(190,160,"Start a Match");
			}
		 }
		 ch=getch();
		 if(ch==27)
			exit(0);
	}
	switch(i)
	{
		case 1 :closegraph();
			startmatch();
			break;
		case 2 :closegraph();
			createnewteam();
			break;
		case 3 :closegraph();
			league_sum();
			break;
		case 4 :instructions();
			break;
	}
}


void main()
{

	start_screen();

}



void instructions()
{

	char ch;
	int x;

	int gd=DETECT, gm;
	initgraph(&gd, &gm,"c:\\tc\\BGI");
	cleardevice();

	x=getmaxx();
	setbkcolor(0);
	setcolor(3);
	settextstyle(0,0,4);
	outtextxy(x/2-300,30,"ABOUT THE SOFTWARE");

	setcolor(2);
	settextstyle(1,0,2);
	outtextxy(50,100,"Cricket Manager");

	setcolor(15);
	settextstyle(2,0,8);
	outtextxy(175,140,"Version 1.0 : ACPS_B4");

	setcolor(4);
	settextstyle(1,0,2);
	outtextxy(50,200,"Developers");

	setcolor(15);
	settextstyle(3,0,2);
	outtextxy(50,225,"Chanchur Bansal_ 14103134");
	outtextxy(50,250,"Sumit Garg_      14103149");
	outtextxy(50,275,"Priyansh Sharma_ 14103053");
	outtextxy(50,300,"Avruty Agarwal_  14103052");


	setcolor(14);
	settextstyle(1,0,2);
	outtextxy(325,400,"Click Enter for Next Page");
	outtextxy(325,425,"Click Backspace for Main Menu");
	ch=getch();

	if(ch==ENTER)                                 //go to Instructions
	{
		cleardevice();

		setcolor(13);
		settextstyle(9,0,4);
		outtextxy(140,20,"INSTRUCTIONS");

		setcolor(15);
		settextstyle(3,0,3);
		outtextxy(2,100,"1. Choose two teams.");
		outtextxy(2,140,"2. Select the batting team.");
		outtextxy(2,180,"3. Enter the number of overs.");
		outtextxy(2,220,"4. Start the match.");
		outtextxy(2,260,"5. Indicate what happens on each ball.");
		outtextxy(2,300,"6. Summary of first innings is displayed.");
		outtextxy(2,340,"7. Indicate what happens on each ball for the next team.");
		outtextxy(2,380,"8. Game Summary is displayed.");

		setcolor(14);
		settextstyle(1,0,2);
		outtextxy(325,425,"Click Backspace for Last Page");


		ch=getch();
		if(ch==BACKSPACE)
		{
			instructions();
		}

	 }



	 else if(ch==BACKSPACE)
	  {
		start_screen();
	  }



	closegraph();

}



void createnewteam()
{

	int i;
	char f_name[80];
	FILE *f;
	team t;

	printf("-----------------------------------------------\n");

	printf("        Enter the team name    ");
	gets(t.name);
	t.win=t.loss=t.t_match=0;

	for(i=0;i<11;i++)
	{

		printf("-----------------------------------------------\n");
		printf("-----------------------------------------------\n");

		printf("  Player %d     ||     ",i+1);
		scanf("%s",t.p[i].name);

		t.p[i].run=0;
		t.p[i].wkt=0;
		t.p[i].t_match=0;

		printf("\n");

	}
	strcpy(f_name,"c:\\tc\\team\\");
	strcat(f_name,t.name);
	strcat(f_name,".dat");

	f=fopen(f_name,"w");
	fwrite(&t,sizeof(t),1,f);
	fclose(f);

	f=fopen("c:\\tc\\team\\teaml.dat","a");
	fwrite(&(t.name),sizeof(t.name),1,f);
	fclose(f);

	getch();
	start_screen();

}





