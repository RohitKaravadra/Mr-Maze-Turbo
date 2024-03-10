/* please do not try to mess with the code or any file provided
with this program. It can lead to misbehaviour of the program
*/
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>
#include<dos.h>
#include<string.h>

class load
{
	protected:
	void check();
	int level;
	void loadprofile();
	void update();
};

/* Main class containing necessary data and functions */
class game:public load
{
	int x,y,tmplev,steps;
	char maze[10];
	protected:
	void openingbanner();
	void outline();
	void menu();
	void mazeexecuter();
	void levelselector();
	void levelscreen();
	void instructions();
	public:
	void execute();
};

void game::openingbanner()
{
	textbackground(GREEN);
	outline();
	textbackground(BLUE);
	for(int k=2;k<9;k++)
	{
		for(int i=2;i<9;i++)
		{
			gotoxy(29,i);
			if(i==k) textcolor(YELLOW); else textcolor(BLUE);
			cprintf("RBK PRODUCTION presents-");
			_setcursortype(0);
		}
		delay(40);
	}
	for(k=0;k<2;k++)
	{
		if(k==1)
		textbackground(RED);
		else
		textbackground(LIGHTGREEN);
		for(int i=17+k;i<65-k;i++)
		{
			for(int j=9+k;j<19-k;j++)
			{	gotoxy(i,j);
				cprintf(" ");
			}
		}
	}
	delay(400);
	textbackground(LIGHTGREEN);
	ifstream obj("mrmaze.txt");
	if(obj)
	{
		while(!obj.eof())
		{
			obj>>x;
			obj>>y;
			gotoxy(x,y);
			cprintf(" ");
			delay(10);
		}
	}
	else
	{
		gotoxy(4, 21);
		cout<<"[ERROR] : File mrmaze.txt not found"; getche(); exit(0);
	}
	obj.close();
	textbackground(GREEN);
	textcolor(RED);
	gotoxy(35,18);
	cprintf("Mister  Maze");
	delay(800);
	textbackground(BLUE);
	gotoxy(17,22);
	cprintf("Loading...");
	textbackground(CYAN);
	for(k=17;k<65;k++)
	{       if(k==random(47)+17)
		delay(400);
		gotoxy(k,23);
		cprintf(" ");
		delay(100);
	}
	check();
}

void load::check()
{
	system("cls");
	ofstream obj;
	obj.open("profile.txt",ios::app,ios::nocreate);
	if(!obj)
	{ ofstream obj1("profile.txt"); obj1<<1; obj1.close();}
	obj.close();
	obj.open("level.txt",ios::app,ios::nocreate);
	if(!obj)
	{ cout<<"ERROR\nFile level.txt not found"; getche(); exit(0);}
	obj.close();
	obj.open("maze.txt",ios::app,ios::nocreate);
	if(!obj)
	{ cout<<"ERROR\nFile maze.txt not found"; getche(); exit(0);}
	obj.close();
	obj.open("coord.txt",ios::app,ios::nocreate);
	if(!obj)
	{ cout<<"ERROR\nFile coord.txt not found"; getche(); exit(0);}
	obj.close();
	obj.open("instr.txt",ios::app,ios::nocreate);
	if(!obj)
	{ cout<<"ERROR\nFile coord.txt not found"; getche(); exit(0);}
	obj.close();
}

void load::loadprofile()
{
	ifstream obj("profile.txt");
	obj>>level;
	obj.close();
}

void load::update()
{
	ofstream obj("profile.txt");
	obj<<level;
	obj.close();
}
void game::mazeexecuter()
{
	int a,b,xe,ye,ch1,c;
	steps=0;
	_setcursortype(0);
	textbackground(BLUE); textcolor(CYAN); gotoxy(4,3); cprintf("STEPS - ");
	textbackground(MAGENTA);
	ifstream obj("coord.txt");
	for(int i=0;i<tmplev;i++)
	{
		obj>>a;  obj>>b;
		obj>>xe; obj>>ye;
	}
	obj.close();
	int ch=0;
	obj.open("maze.txt");
	while(!obj.eof())
	{
		obj>>x;
		obj>>y;
		if(x==tmplev&&y==0) {ch=1; continue;}
		else if(x==tmplev+1&&y==0) break;
		if(ch==1)
		{
			gotoxy(x,y);
			cprintf(" ");
		}
	}
	obj.close();
	gotoxy(a,b);   textbackground(GREEN);
	cprintf(" ");
	while(1)
	{
		textbackground(BLUE); textcolor(CYAN); gotoxy(12,3); cprintf("%d",steps);
		textbackground(BLUE);
		textcolor(BLUE);
		gotoxy(1,1);
		ch1=getche();
		gotoxy(a,b); cprintf(" ");
		if(ch1==8)
		break;
		gotoxy(a,b);
		cprintf(" ");
		switch(char(ch1))
		{
			case 'H':b--; steps++;
			break;
			case 'K':a--; steps++;
			break;
			case 'M':a++; steps++;
			break;
			case 'P':b++; steps++;
			break;
		}
		c=0;
		obj.open("maze.txt");
		ch=0;
		while(!obj.eof())
		{
			obj>>x;
			obj>>y;
			if(x==tmplev&&y==0) { ch=1; continue;}
			else if(x==tmplev+1&&y==0) ch=0;
			if(ch==1)
			if(x==a&&y==b)
			c++;
		}
		obj.close();
		if(c!=0)
		{
			switch(char(ch1))
			{
				case 'H':b++; steps--;
				break;
				case 'K':a++; steps--;
				break;
				case 'M':a--; steps--;
				break;
				case 'P':b--; steps--;
				break;
			}
		}
		textbackground(CYAN);
		gotoxy(a,b);
		cprintf(" ");
		if(a==xe&&b==ye)
		{
			if(tmplev==level&&tmplev<7)
			level++; lb: textbackground(BLUE); textcolor(random(10)+2);
			gotoxy(37,23); cprintf("YOU WON");
			gotoxy(58,24); cprintf("ENTER to continue:-");
			textcolor(BLUE);
			gotoxy(1,1); ch1=getche();
			if(int(ch1)!=13) goto lb;
			break;
		}
	}
}

void game::outline()
{
	textbackground(BLUE);
	clrscr();
	textbackground(LIGHTGREEN);
	for(int i=2;i<80;i++)
	{
		gotoxy(i,1);
		cprintf(" ");
		gotoxy(i,25);
		cprintf(" ");
		if(i<25)
		{
			gotoxy(1,i);
			cprintf("  ");
			gotoxy(79,i);
			cprintf("  ");
		}
		_setcursortype(0);
	}
}

void game::menu()
{
	x=0,y=10;
	while(1)
	{
		textbackground(GREEN);
		loadprofile();
		outline();
		textcolor(RED);
		gotoxy(30,5); cprintf("WELCOME TO MR. MAZE");
		textbackground(BLUE);
		textcolor(YELLOW);
		gotoxy(32,10); cprintf("    Cotinue");
		gotoxy(32,12);cprintf("    New Game");
		gotoxy(32,14);cprintf("  Instructions");
		gotoxy(32,16);cprintf("      Exit");
		do
		{
			for(int i=10;i<17;i++)
			{
				if(i==y)
				textcolor(YELLOW);
				else
				textcolor(BLUE);
				gotoxy(32,i);   cprintf("->");
				gotoxy(46,i);   cprintf("<-");
				textcolor(BLUE);
			}
			x=getche();
			if(x==13)
			{
				if(y==16)
				exit(0);
				else if(y==12)
				{
					level=1;
					update();
					levelscreen();
				}
				else if(y==10)
				levelscreen();
				else if(y==14)
				instructions();
				y=10; x=13;
			}
			switch(char(x))
			{
				case 'P':if(y!=16) y=y+2; else y=10;
				break;
				case 'H':if(y!=10) y=y-2;  else y=16;
				break;
			}
		}while(x!=13);
	}
}

void game::instructions()
{
	textbackground(GREEN);
	outline();
	textbackground(BLUE);
	char str[70];
	y=3;
	ifstream obj("INSTR.TXT");
	while(!obj.eof())
	{
		textcolor(y+1);
		gotoxy(3,y++);
		obj.getline(str,70);
		cprintf(str);
	}
	obj.close();
	getche();
	_setcursortype(0);
}

void game::levelscreen()
{
	tmplev=level; y=7+level;
	while(1)
	{
		textbackground(GREEN);
		outline();
		textbackground(BLUE);
		for(int i=1;i<12;i++)
		{
			if(i<=level) textcolor(YELLOW);
			else textcolor(RED);
			gotoxy(36,7+i);
			switch(i)
			{
				case 1:cprintf("Level 1");
				break;
				case 2:cprintf("Level 2");
				break;
				case 3:cprintf("Level 3");
				break;
				case 4:cprintf("Level 4");
				break;
				case 5:cprintf("Level 5");
				break;
				case 6:cprintf("Level 6");
				break;
				case 7:cprintf("Level 7");
				break;
				case 8:cprintf("Level 8");
				break;
				case 9:cprintf("Level 9");
				break;
				case 10:cprintf("Level 10");
				break;
				case 11:cprintf("Level 11");
				break;
			}
		}
		do
		{
			for(int i=8;i<19;i++)
			{
				if(y==i)
				textcolor(YELLOW);
				else
				textcolor(BLUE);
				gotoxy(33,i); cprintf("->");
				gotoxy(44,i); cprintf("<-");
				textcolor(BLUE);
				gotoxy(1,1);
			}
			_setcursortype(0);
			x=getche();
			if(x==13)
			{
				levelselector();
				mazeexecuter();
				if(tmplev==level-1)
				update();
				y=7+level;
				tmplev=level;
				x=13;
			}
			else
			{
				switch(char(x))
				{
					case 'P':if(level>tmplev) { y++; tmplev++; }
					break;
					case 'H':if(tmplev!=1) { y--; tmplev--; }
					break;
				}
			}
		}while(x!=13&&x!=8);
		if(x==8) break;
	}
}
void game::levelselector()
{
	outline();
	delay(500);
	textbackground(CYAN);
	ifstream obj("level.txt");
	int c=0;
	while(!obj.eof())
	{
		obj>>x;
		obj>>y;
		if(x==tmplev&&y==0) { c=1; continue;}
		else if(x==tmplev+1&&y==0) break;
		if(c==1)
		{
			gotoxy(x,y);
			cprintf(" ");
			delay(10);
		}
	}
	obj.close();
	delay(500);
	outline();
}

void game::execute()
{
	openingbanner();
	menu();
}

void main()
{
	system("cls");
	game g;
	g.execute();
	getch();
}