#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

int rowa,rowb,cola,colb;
char array[22][22],last;
int round;
int flag=0,y=55;
void take_time(int tk);


void main()
{
   char ch;
   int i;
   void getout();
   void help();
   void play();
   void high();

   for(i=1;i<=5;i++)
   { clrscr();
     textcolor(RED);
     textbackground(BLUE);
     gotoxy(25,15);
     cprintf("WELCOME TO TRACK GAME ");
     gotoxy(32,18);
     textcolor(GREEN);
     cprintf("A.Play");
     gotoxy(32,20);
     cprintf("D.Instructions ");
     gotoxy(32,22);
     cprintf("S.High Scores");
     gotoxy(32,24);
     cprintf("W.Exit");
     textcolor(RED);
     ch=getch();

     switch(ch)
     {  case 'A':  play();break;

	case 'D':  help();break;

	case 'S':  high();break;

	case 'W':  getout();break;

	default : return;
     }
   }
}

void high()
{  FILE *fi;
   int i=1;
   char scorer[10];
   char back;
   clrscr();
   fi=fopen("score.txt","r");
   gotoxy(28,15);
   textcolor(RED);
   cprintf("THE HIGHEST SCORERS ");
   textcolor(GREEN);

   while(fscanf(fi,"%s",&scorer) !=EOF || i>10)
   {  i++;
      gotoxy(33,15+2*i);
      cprintf("%d.%s",i-1,scorer);
   }

   if(i==1)
   {  gotoxy(31,25);
      cprintf("No High Scorers");
   }

   fclose(fi);
   gotoxy(60,40);
   textcolor(RED);
   cprintf("BACK : B");
   back=getch();
   if(back=='B')
	   return;
   else exit(0);
}


void getout()
{  char ch;
   clrscr();
   sleep(1);
   gotoxy(45,35);
   cputs("DO YOU WANT TO EXIT : Y/N ");
   ch=getch();
   if(ch=='N') return;
   exit(0);
}

void play()
{  int stop=0,score=0,i;
   int ind=0;
   int ti,tj,tk=500;
   int lvl=0,sl=50,count=0;
   char track[]="TRACK";
   char cur=track[lvl];
   void draw();
   void defl(char cur);
   void level(int lvl);
   int check(int count);
   int update(char cur);
   void record(int score);
   clrscr();
   defl(cur);
   randomize();

   for(;;)
   {  clrscr();
      ind=0;
      textcolor(LIGHTGREEN);
      cprintf("\n\n\n");
      for(i=1;i<14;i++)   cprintf(" ");
      cprintf("   TRACK\n\n\n\r");
      for(i=1;i<14;i++)   cprintf(" ");
      cprintf("   YOUR SCORE\n\n\r");
      for(i=1;i<14;i++)   cprintf(" ");
      cprintf("%d",score);
      textcolor(RED);
      stop=update(cur);
      if(stop==2)
      {  score+=sl;
	 while(1)
	 {  ti=random(22);
	    tj=random(22);
	    if(ti==0) ti=10;
	    if(tj==0) tj=10;
	    if(array[ti][tj]==' ')
	    {  array[ti][tj]=cur;
	       count++;
	       if(count>6)
		 stop=check(count);
	       if(count==10)
	       {  lvl++;
		  cur=track[lvl];
		  if(lvl==5)
		   {  stop=1;
		      break;
		   }
		   sl+=50;
		   count=0;
		   tk-=75;
		   level(lvl);
		   defl(cur);
		   ind=1;
	       }
	       break;
	     }
	   }
	}

	if(rowa==0 || rowa==21 || cola==0 || cola==21)  stop=1;

	if(stop==0  && ind==0 )   draw();

	take_time(tk);

	if(stop==1)
	{  clrscr();
	   if(lvl!=5)
	   {  for(i=1;i<=2;i++)  printf("\n\n\n\n");
	      printf("\t\t\tGAME OVER ");
	      sleep(1);
	      printf("\n\n\n\n");
	      printf("\t\tYOUR SCORE : %d",score);
	      sleep(3);
	      return;
	   }
	   else
	   {  textcolor(CYAN);
	      for(i=1;i<=5;i++)  cprintf("\n\n\n");
	      cprintf("      ");
	      cprintf("CONGRATULATIONS ");
	      sleep(5);
	      record(score);
	   }
	}
    }
}



void help()
{  int i,back;
   clrscr();
   for(i=1;i<10;i++)  printf("\n");
   printf("  INSTRUCTIONS : \n\n\n");
   textcolor(LIGHTGREEN);
   cprintf("\n\n");
   for(i=1;i<20;i++)  cprintf(" ");
   cprintf(" 1.You can change the direction of the TRAIN only when\n\n");
   for(i=1;i<=27;i++)  cprintf(" ");
   cprintf(" it is straight\n");
   cprintf("\n\n\n\r");
   for(i=1;i<20;i++)  cprintf(" ");
   cprintf("2. Throughout the game keep the CAPS LOCK on ");
   cprintf("\n\n\n\n\r");
   for(i=1;i<20;i++)  cprintf(" ");
   cprintf(" 3. The Game has been built to use the \n\n\n\r");
   for(i=1;i<25;i++)  cprintf(" ");
   cprintf("Standard Direction Letters \n\n\r");
   for(i=1;i<=33;i++)  cprintf(" ");
   cprintf("A.Left\n\n\r");
   for(i=1;i<=33;i++)  cprintf(" ");
   cprintf("D.Right\n\n\r");
   for(i=1;i<=33;i++)  cprintf(" ");
   cprintf("W.Up\n\n\n\r");
   for(i=1;i<=33;i++)  cprintf(" ");
   cprintf("S.Down\n\n\r");
   for(i=1;i<=20;i++) cprintf(" ");
   cprintf("4. Don't Collide against the walls ");
   cprintf("\n\n\n\r");
   textcolor(LIGHTRED);
   for(i=1;i<60;i++) cprintf(" ");
   cprintf(" BACK : B");

   while(1)
   {  back=getch();
      if(back=='B') break;
   }
}


void record(int score)
{  int i;
   char name[10];
   FILE *fi;
   void what_is_y();
   fi=fopen("score.txt","a");
   clrscr();
   for(i=1;i<=40;i++) cprintf("\n");
   printf("\tENTER YOUR NAME : ");
   scanf("%d",&name);
   fprintf(fi,"\n\n%s",name);
   fclose(fi);
   clrscr();
   gotoxy(32,25);
   cprintf("\n\n\n\nYOUR SCORE IS THE HIGHEST : %d",score);
   sleep(5);
   while(round!=6)
   {  gotoxy(35,15);
      textbackground(BLACK);
      textcolor(GREEN+BLINK);
      cprintf("TRACKER");
      gotoxy(y,24);
      textcolor(RED);
      cputs(name);
      what_is_y();
      take_time(600);
      clrscr();
   }
   exit(0);
}

void what_is_y()
{   if(y==15)
     {   flag=0;
	 round++;
     }
     if(y==55) flag=1;
     if(flag==0) y++;
     else y--;
     return;
}

void draw()
{  int i,j;
   printf("\n\n\n\n");
   for(i=0;i<22;i++)
   {   for(j=0;j<22;j++)
	  putchar(array[i][j]);
	  printf("\n");
   }
   return;
}


void take_time(int tk)
{  int i,k,j;
   for(i=1;i<=1000;i++)
   {  for(j=1;j<=400;j++)
	 for(k=1;k<=tk;k++)
	    ;
   }

   return;
}


int check(int count)
{  int i,j;
   int star;
    for(i=1;i<22;i++)
    {  for(j=1;j<22;j++)
	  if(array[i][j]=='*')  star++;
    }

    if(star>count+1)  return 1;

    else return 0;
}


void defl(char cur)
{     int i,j,k;
      for(i=0;i<=21;i++)  array[0][i]='-';

      for(i=1;i<=20;i++)
      {  array[i][0]='!';
	 for(j=1;j<=20;j++)  array[i][j]=' ';
	 array[i][j]='!';
      }

      for(i=0;i<=21;i++)  array[21][i]='-';

      array[5][10]='#';
      array[5][11]='*';
      array[8][5]=cur;

      rowa=5;
      rowb=5;
      cola=10;
      colb=11;

      return;
}


void level(int lvl)
{
    clrscr();
    gotoxy(32,20);
    textcolor(LIGHTGREEN);
    cprintf("LEVEL: %d",lvl+1);
    last='M';
    sleep(3);
    clrscr();
    textcolor(RED);
    return;
}

int update(char cur)
{
     char choice;
     int decider=0;
     if(kbhit())
     {  choice=getch();
	last=choice;
     }
     else choice=last;

     switch(choice)
     {    case 'W': if(array[rowa-1][cola]=='*')
		    {  decider=1;
		       break;
		    }
		    if(array[rowa-1][cola]!=cur)
		    {   array[rowa][cola]='*';
			array[--rowa][cola]='#';
			if(cola==colb)
			    array[rowb--][colb]=' ';
			else  {  if(cola>colb)
					array[rowb][colb++]=' ';
				  else array[rowb][colb--]=' ';
			      }
		    }
		    else
		    {   decider=2;
			array[rowa][cola]='*';
			array[--rowa][cola]='#';
		    }

		    break;

     case 'S' :  if(array[rowa+1][cola]=='*')
		 {  decider=1;
		    break;
		 }

		 if(array[rowa+1][cola]!=cur)
		 {  array[rowa][cola]='*';
		    array[++rowa][cola]='#';

		    if(cola==colb)   array[rowb++][colb]=' ';
		    else  {  if(cola>colb)
				  array[rowb][colb++]=' ';
			     else array[rowb][colb--]=' ';
			  }
		}

		else
		{   decider=2;
		    array[rowa][cola]='*';
		    array[++rowa][cola]='#';
		}

		break;

  case 'A' : if(array[rowa][cola-1] == '*')
	     {  decider=1;
		break;
	     }

	     if(array[rowa][cola-1]!=cur)
	     {   array[rowa][cola]='*';
		 array[rowa][--cola]='#';
		 if(rowa==rowb)  array[rowb][colb--]=' ';
		 else
		 {  if(rowa>rowb)  array[rowb++][colb]=' ';
		    else array[rowb--][colb]=' ';
		 }
	    }

	    else
	    { decider=2;
	      array[rowa][cola]='*';
	      array[rowa][--cola]='#';
	    }

	    break;


   case 'D' : if(array[rowa][cola+1]=='*')
	      {  decider=1;
		 break;
	      }

	      if(array[rowa][cola+1]!=cur)
	      {   array[rowa][cola]='*';
		  array[rowa][++cola]='#';

		  if(rowa==rowb)  array[rowb][colb++]=' ';
		  else
		  {  if(rowa>rowb)  array[rowb++][colb]=' ';
		     else  array[rowb--][colb]=' ';
		  }
	       }

	       else
	       {  decider=2;
		  array[rowa][cola]='*';
		  array[rowa][++cola]='#';
	       }

	       break;


      default : decider=0;
      }

   return decider;
}




