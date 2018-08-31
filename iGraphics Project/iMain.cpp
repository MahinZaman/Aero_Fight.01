#include "iGraphics.h"
#include "bitmap_loader.h"
#include "stdlib.h"
#include "string.h"


/*
 function iDraw() is called again and again by the system.

 */
int xcord = 10;
int ycord = 500;
int BulletCount = 0;
int BulletTimer = 0;
int button = 0;
int page = 1;
int enemyX = 1000,enemyY = 600,enemy_Speed = 10;
int dx1 = -10;
int dy1 = -40;
int dx2= 40,dy2 = 40;
int x1 ;
//int y1;
int x2;
int y2;
int flag = 0;
int playerLife=1;

int point = 0;
char string[10] ;


void show()
{
	iSetColor(10,121,23);
	iFilledCircle(188,200,300);
}




void mainPage()
{
	iShowBMP(0,0,"mainpage.bmp");
	iShowBMP(200,500,"StartGame1.bmp");
	iShowBMP2(200,450,"HowToPlay.bmp",255);
	iShowBMP2(200,400,"Highest.bmp",255);
	if(button == 1)
	{
		iShowBMP(200,500,"StartGame2.bmp");
	}
	if(button == 2)
	{
		iShowBMP2(200,450,"HowtoPlay2.bmp",255);
	}
	if(button == 3)
	{
		iShowBMP2(200,400,"Highest2.bmp",255);
	}


}
struct Bullet{
	int x,y;
	bool  hasShot;

}bullet[100];


struct Enemy{
	int x,y;
	bool active;

}enemy[6];

int arry[100];
int temp;


void Enemy()
{

	for (int i = 0,x1=100 ; i < 6 ; i++,x1+=100)
	{enemy[i].x -= 20;
		if(enemy[i].x<0 )
		{	enemy[i].x =enemyX + x1;
			enemy[i].y = (enemyY-100)- rand() % 250;
			enemy[i].active = true;
		}
	}
}


void writeHighScore(int n)
{
    FILE *fp = fopen("D:\\hhh.txt", "a");

    if(fp != NULL)
    {
        fprintf(fp, "%d\n", n);
    }

    fclose(fp);

}
char str[100][10];
int s = 0;
void readHighScore()
{
	printf("Running");
    FILE *fp = fopen("D:\\hhh.txt", "r");


    if (fp != NULL)
    {
        while (fgets(str[s++], 15, fp) != NULL)
        {
            puts(str[s-1]);
        }
    }
}

void showScore ()
{
	char st[100];
	for (int i = 0, y = 0; i < 5; i++, y+= 50)
	{
		itoa(arry[i], st, 10);
		iText(500,500 - y,st,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}


void showEnemy()
{
	for (int i = 0 ; i < 6 ; i++)
		{
			if (enemy[i].active)
				{
					iShowBMP2(enemy[i].x,enemy[i].y,"mahin.bmp",255);
				}
		}
}
void Short();
void killEnemy()
{
	for (int i = 0; i < BulletCount ; i++)
		{
			for (int j = 0 ; j < 6 ; j++)
				{
					if( enemy[j].active && bullet[i].hasShot == true)
						{
							if (bullet[i].x+55 >= enemy[j].x && bullet[i].x+55 <= enemy[j].x +150)
								{
									if (bullet[i].y+19 >= enemy[j].y && bullet[i].y+19 <= enemy[j].y + 80)
											{
												enemy[j].active = false;
												bullet[i].hasShot = false;
												if(enemy[j].active==false)
												{
													point++;
												}

											}
								}
						}
				}
		}

}





void bulletShow()//call from doWork function which Call from iDraw function for Show the Bullet
{
	for(int i = 0; i < BulletCount ; i++)
		{
			if(bullet[i].hasShot== true )
				{
					iShowBMP2(bullet[i].x,bullet[i].y,"bullet.BMP",255);
				}
		}
}






void score()
{

	itoa(point, string,10);
	iSetColor(255,0,0);
	//iFilledRectangle(20,200,100,200);
	iText(150,650,string,GLUT_BITMAP_TIMES_ROMAN_24);
	printf("%d\n",point);


}

void GameOver(){
	for(int i=0;i < 6 ; i++)
	{
		if (enemy[i].active == true)
		{
			if (enemy[i].x <= xcord + 150)
			{
				if (enemy[i].y + 80 >= ycord && enemy[i].y <= ycord)
				{
					//iShowBMP(0,0,"game_over.bmp");
					iText(100,300,"Your Score :",GLUT_BITMAP_TIMES_ROMAN_24);
					iText(250,300,string,GLUT_BITMAP_TIMES_ROMAN_24);
					//writeHighScore(point);
					//readHighScore();
					writeHighScore(point);
					readHighScore();
					Short();
					page = 10;
				}
			}
		}
	}

}


void Short()
{

	for(int i=0;i<s-1;i++)
	{
		arry[i]=atoi(str[i]);
	}

	for(int i=0; i<s-1;i++)
	{
		for(int j=0;j<s;j++)
		{
			if(arry[j]<arry[j+1])
			{
				temp = arry[j];
				arry[j] = arry[j+1];
				arry[j+1] = temp;

			}
		}
	}

}



void ShowHighScore()
{
	iSetColor(128, 0,128);
	iFilledCircle(0,0, 200);
	iShowBMP(0,0,"score.bmp");
}

void iDraw()
{
	//place your drawing codes here
	iClear();
	if(page == 1)
	{
		mainPage();
	}
	if(page == 2)
	{
		iShowBMP2(0,0,"background.bmp",255);

		iShowBMP2(xcord,ycord,"plane.bmp",255);
		showEnemy();
		bulletShow();
		killEnemy();
		score();
		GameOver();
		//


	}
	if(page == 3)
	{
		//iShowBMP2(0,0,"background.bmp",255);
		iShowBMP(0,0,"bb.bmp");
	}
	if(page==4)
	{
		ShowHighScore();
		showScore();

	}
	if (page == 10)
	{
		iShowBMP(0,0,"game_over.bmp");
		showScore();
	}
	//readHighScore();


}





void BulletShoot()
{
	for(int i = 0 ; i < BulletCount ; i++)
	{

		if(bullet[i].hasShot)
			bullet[i].x += 20;

		if(bullet[i].x > 1370)
			bullet[i].hasShot = false;

	}
}

/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	//place your codes here
}

/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(BulletCount<100)
			BulletCount++;
		else if(BulletCount==100)
			BulletCount=0;

		bullet[BulletCount-1].hasShot=true;
		bullet[BulletCount-1].x=xcord+170;
		bullet[BulletCount-1].y=ycord+36;


	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here

	}
}


/*
 function iKeyboard() is called whenever the user hits a key in keyboard.
 key- holds the ASCII value of the key pressed.
 */
void iKeyboard(unsigned char key)
{
	if(page==1)
	{
		if(button == 1)
		{
			if(key== '\r')
			{
				page = 2;
			}
		}
		if(button ==2)
		{
			if(key=='\r')
			{
				page = 3;

			}
		}
		if(button==3)
		{
			if(key=='\r')
			{
				page=4;
				readHighScore();
				Short();
			}
		}
	}
	if (key == 'q')
	{
		exit(0);
	}
	if(key == 'c')
	{
		BulletCount++;
	}
	if(page==2)
	{
	if(key == 'w')
	{
		if(BulletCount<100)
			BulletCount++;
		else if(BulletCount==100)
			BulletCount=0;

		bullet[BulletCount-1].hasShot=true;
		bullet[BulletCount-1].x=xcord+170;
		bullet[BulletCount-1].y=ycord+36;
	}
	}

	//place your codes for other keys here
}

/*
 function iSpecialKeyboard() is called whenver user hits special keys like-
 function keys, home, end, pg up, pg down, arraows etc. you have to use
 appropriate constants to detect them. A list is:
 GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
 GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
 GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
 GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
 */
void iSpecialKeyboard(unsigned char key)
{


	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
			if(key == GLUT_KEY_RIGHT)
	{
		xcord+=20;

	}
	if(key == GLUT_KEY_LEFT)
	{
		xcord-=20;

	}
	if(key == GLUT_KEY_UP)
	{

		button--;
		//page = 2;

	}
	if(key == GLUT_KEY_DOWN)
	{

		button++;
		if(button > 4)
		{
			button =0;
		}
		//page = 2;
	}

	if(key == GLUT_KEY_UP)
	{



		ycord+=20;
	}
	if(key == GLUT_KEY_DOWN)
	{
		ycord-=20;


	}
	if(key==GLUT_KEY_F3)
	{
		if(page==3)
		{
			page=1;
		}
	}
	if(key==GLUT_KEY_F3)
	{
		if(page==2)
		{
			page=1;
		}
	}
	//place your codes for other keys here
}



int timer;



int main()
{
	//place your own initialization codes here.
	printf("this");
	BulletTimer = iSetTimer(100,BulletShoot);
	iSetTimer(300,Enemy);
	iInitialize(1370, 720, "Last Man Survive");

	return 0;
}
