/*Program to input text in graphics at (x,y) */

#include<stdio.h>
#include<conio.h>
#include<graphics.h>

int intextxy(int x,int y, char inbuf[],int max)
{
	char c;
	int color,in_pos=0;
	inbuf[0]='\0';
	while(1)
	{
		outtextxy(x,y,inbuf);
		c=getch();
		switch (c)
		{
			case 8: //backspace
				if(in_pos)
				{
					color=getcolor();
					setcolor(getpixel(x-1,y+1));
					outtextxy(x,y,inbuf);
					setcolor(color);
					in_pos--;
					inbuf[in_pos]='\0';
				}
				break;
			case 13://return
				return 1;
			case 27://Escape = Abort
				inbuf[0]='\0';
				return 0;
			default:
				if(in_pos < max-1 && c>=' ' && c<='~')
				{
					inbuf[in_pos]=c;
					in_pos++;
					inbuf[in_pos]='\0';
				}
		}
	}
}
void main()
{
	int gd=DETECT,gm;
	char s[30];
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	cleardevice();
	setbkcolor(BLUE);

	settextstyle(1,0,3);
	setfillstyle(SOLID_FILL,RED);
	setcolor(RED);
	rectangle(180,160,500,190);
	floodfill(190,170,RED);
	setcolor(GREEN);
	outtextxy(190,160,"Player : ");
	intextxy(300,160,s,30);
	printf("%s",s);
	getch();
}