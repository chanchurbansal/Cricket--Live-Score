#include<stdio.h>
#include<conio.h>
void display1()
{

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
		       }
void display2()
{
char f_name[30];
team t;
char  path[80];
	FILE *fp;
	FILE *fp1;
	fp=fopen("C:\\tc\\team\\teaml.dat","rb");
	while(fread(&f_name,sizeof(f_name),1,fp))
	{
	    strcpy(path,"C:\\tc\\team\\");
	    strcat(path,f_name);
	    strcat(path,".dat");
	    fp1=fopen(path,"rb");
	    fread(&t,sizeof(t),1,fp1);
	    gotoxy(2,6);
	    printf("%s",t.name);
	    gotoxy(23,6);
	    printf("%d",t.t_match);
	    gotoxy(41,5);
	    printf("%d",t.win);
	    gotoxy(51,5);
	    printf("%d",t.loss);

	}


void main()
{

clrscr();
display1();
display2();
getch();
}
