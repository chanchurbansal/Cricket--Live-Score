#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#include<string.h>
//#include "c:\\tc\\pro\\txt_grap.c"

typedef struct player
{
	char name[20];
	int run,wkt,t_plays;
	float avg,eco;

}player;

typedef struct team
{
	char name[20];
	int win,loss,t_match;
	player p[11];
}team;
void createnewteam()
{
	int i;
	char f_name[80];
	FILE *f;
	team t;
	printf("enter the team name");
	scanf("%s",t.name);
	t.win=t.loss=t.t_match=0;
	for(i=0;i<11;i++)
	{
		printf("enter the player %d name",i+1);
		scanf("%s",t.p[i].name);
		t.p[i].run=0;
		t.p[i].wkt=0;
		t.p[i].avg=0.0;
		t.p[i].sr=0.0;
		t.p[i].eco=0.0;
	}
	strcpy(f_name,"c:\\tc\\");
	strcat(f_name,t.name);
	strcat(f_name,".dat");
	f=fopen(f_name,"w");
	fwrite(&t,sizeof(t),1,f);
	fclose(f);
	f=fopen("c:\\tc\\teamlist.dat","a+");
	fwrite(&(t.name),sizeof(t.name),1,f);
	fclose(f);
}
void main()
{
	clrscr();
	createnewteam();
	getch();
}





