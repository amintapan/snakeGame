#include <iostream>
#include<graphics.h>
#include<stdio.h>
#include<pthread.h>
#include<dos.h>
#define MAX 10000
int queue[MAX],front=-1,rear=-1;
int nextDirection=1;
int direction=1;
int snakeInitPointX;
int snakeInitPointY;
int snakeEndX;
int snakeEndY;
int eggEaten=1;
int eggX;
int eggY;
int score;
using namespace std;

void insert_element(int num)// QUEUE is used for corners
{
  //printf("\n Enter the number to be inserted: ");
  //scanf("%d",&num);
  if(front==0 && rear==MAX-1)
    printf("\n Queue OverFlow Occured");
  else if(front==-1&&rear==-1)
  {
      front=rear=0;
      queue[rear]=num;

  }
  else if(rear==MAX-1 && front!=0)
  {
    rear=0;
    queue[rear]=num;
  }
  else
  {
      rear++;
      queue[rear]=num;
  }
}
void delete_element()
{
  int element;
  if(front==-1)
  {
      //printf("\n Underflow");
  }
  element=queue[front];
  if(front==rear)
     front=rear=-1;
  else
  {
    if(front==MAX-1)
      front=0;
    else
      front++;
    //printf("\n The deleted element is: %d",element);
  }

}
/*
void display_queue()
{
    int i;
    if(front==-1)
      //printf("\n No elements to display");
    else
    {
      //printf("\n The queue elements are:\n ");
      for(i=front;i<=rear;i++)
      {
          printf("\t %d",queue[i]);
      }
    }
}
*/
void* thread_func(void* parameter)  //This thread is for continous scanning of DIRECTIONS.
{
    printf("thread_func started\n");
    int i;
    int eggX;
    int eggY;
    printf("Enter Direction");
    while(1)
    {
        scanf("%d",&nextDirection);
        if(nextDirection==7)
        {
            direction=nextDirection;
            return NULL;
        }
        if(nextDirection==1 && direction!=3)
        {
            if(nextDirection!=direction)
                insert_element((snakeInitPointY*1080)+snakeInitPointX);
            direction=nextDirection;
        }
        if(nextDirection==2 && direction!=5)
        {
            if(nextDirection!=direction)
                insert_element((snakeInitPointY*1080)+snakeInitPointX);
            direction=nextDirection;
        }
        if(nextDirection==5 && direction!=2)
        {
            if(nextDirection!=direction)
                insert_element((snakeInitPointY*1080)+snakeInitPointX);
            direction=nextDirection;
        }
        if(nextDirection==3 && direction!=1)
        {
            if(nextDirection!=direction)
                insert_element((snakeInitPointY*1080)+snakeInitPointX);
            direction=nextDirection;
        }
    }
return 0;
}
void* goRight(void* parameter)  //this THREAD is for moving snake
{
    char msg[128];
    eggEaten=0;
    printf("goRight started\n");
    while(1)
    {
        if(direction==3)
        {
            if(getpixel(snakeInitPointX+1,snakeInitPointY)==1||getpixel(snakeInitPointX+1,snakeInitPointY)==15)
            {
                //If snake touches the border or itself then game over
                Beep(999,1000);
                sprintf(msg, "SCORE : %d", score-1);
                outtextxy(505,300,msg);
                outtextxy(500,350, "GAME OVER");
                printf("Game Over\n");
                return 0;
            }
            else if(getpixel(snakeInitPointX+1,snakeInitPointY)==4)
            {
                //If snake touches the egg
                score++;
                Beep(523,50);
                eggEaten=1;
                //return 0;
            }
            snakeInitPointX++;
            putpixel(snakeInitPointX,snakeInitPointY,1);
        }
        else if(direction==1)
        {
            if(getpixel(snakeInitPointX-1,snakeInitPointY)==1||getpixel(snakeInitPointX-1,snakeInitPointY)==15)
            {
                Beep(999,1000);
                sprintf(msg, "SCORE : %d", score-1);
                outtextxy(505,300,msg);
                outtextxy(500,350, "GAME OVER");
                printf("Game Over\n");
                return 0;
            }
            else if(getpixel(snakeInitPointX-1,snakeInitPointY)==4)
            {
                score++;
                Beep(523,50);
                eggEaten=1;
                //return 0;
            }
            snakeInitPointX--;
            putpixel(snakeInitPointX,snakeInitPointY,1);
        }
        else if(direction==2)
        {
            if(getpixel(snakeInitPointX,snakeInitPointY+1)==1||getpixel(snakeInitPointX,snakeInitPointY+1)==15)
            {
                Beep(999,1000);
                sprintf(msg, "SCORE : %d", score-1);
                outtextxy(505,300,msg);
                outtextxy(500,350, "GAME OVER");
                printf("Game Over\n");
                return 0;
            }
            else if(getpixel(snakeInitPointX,snakeInitPointY+1)==4)
            {
                score++;
                Beep(523,50);
                eggEaten=1;
                //return 0;
            }
            snakeInitPointY++;
            putpixel(snakeInitPointX,snakeInitPointY,1);
        }
        else if(direction==5)
        {
            if(getpixel(snakeInitPointX,snakeInitPointY-1)==1||getpixel(snakeInitPointX,snakeInitPointY-1)==15)
            {
                Beep(999,1000);
                sprintf(msg, "SCORE : %d", score-1);
                outtextxy(505,300,msg);
                printf("Game Over\n");
                outtextxy(500,350, "GAME OVER");
                return 0;
            }
            else if(getpixel(snakeInitPointX,snakeInitPointY-1)==4)
            {
                score++;
                Beep(523,50);
                eggEaten=1;
                //return 0;
            }
            snakeInitPointY--;
            putpixel(snakeInitPointX,snakeInitPointY,1);
        }
        else if(direction==7)
        {
            //7 is to quit the game
            sprintf(msg, "SCORE : %d", score-1);
            outtextxy(505,300,msg);
            outtextxy(500,350, "GAME OVER");
            outtextxy(450,400, "Game Was Stopped By User\n");
            printf("scorw : %d",score);
            //display_queue();
            return NULL;
        }
        //eggEaten condition goes here........
        if(eggEaten==0)
        {
            //If egg is not eaten
            if(front!=-1) //If there is a corner
            {
                int lastCorner=queue[front];
                int lastCornerX=lastCorner%1080;
                int lastCornerY=lastCorner/1080;
                //printf("%d \t%d\t %d\t %d\n",lastCornerX,lastCornerY,snakeEndX,snakeEndY);
                if(lastCornerX==snakeEndX && lastCornerY==snakeEndY)        //If end is on Corner
                {
                    delete_element();   //delete last corner from QUEUE.
                    printf("arrived at corner %d\n",front);
                    if(front!=-1)       //If any other corners exist.
                    {
                        int templastCorner=queue[front];
                        int templastCornerX=templastCorner%1080;
                        int templastCornerY=templastCorner/1080;
                        if(snakeEndX>templastCornerX && templastCornerY==snakeEndY) //end is on right side of lastcorner
                        {
                            snakeEndX--;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                        if(snakeEndX<templastCornerX && templastCornerY==snakeEndY) //end is on left side of lastcorner
                        {
                            snakeEndX++;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                        if(snakeEndX==templastCornerX && templastCornerY>snakeEndY) //end is on upper side of lastcorner
                        {
                            snakeEndY++;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                        if(snakeEndX==templastCornerX && templastCornerY<snakeEndY) //end is on bottom side of lastcorner
                        {
                            snakeEndY--;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                    }
                    else    //if end is on corner but no other corners then follow snake.
                    {
                        if(direction==3)
                        {
                            snakeEndX++;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                        else if(direction==1)
                        {
                            snakeEndX--;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                        else if(direction==2)
                        {
                            snakeEndY++;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                        else if(direction==5)
                        {
                            snakeEndY--;
                            putpixel(snakeEndX,snakeEndY,0);
                        }
                    }
                }
                else    //If end is not on corner
                {
                    if(snakeEndX>lastCornerX && lastCornerY==snakeEndY) //end is on right side of lastcorner
                    {
                        snakeEndX--;
                        putpixel(snakeEndX,snakeEndY,0);
                    }
                    if(snakeEndX<lastCornerX && lastCornerY==snakeEndY) //end is on left side of lastcorner
                    {
                        snakeEndX++;
                        putpixel(snakeEndX,snakeEndY,0);
                    }
                    if(snakeEndX==lastCornerX && lastCornerY>snakeEndY) //end is on upper side of lastcorner
                    {
                        snakeEndY++;
                        putpixel(snakeEndX,snakeEndY,0);
                    }
                    if(snakeEndX==lastCornerX && lastCornerY<snakeEndY) //end is on bottom side of lastcorner
                    {
                        snakeEndY--;
                        putpixel(snakeEndX,snakeEndY,0);
                    }
                }
            }
            else               //If No corner then follow the snake's direction.
            {
                if(direction==3)
                {
                        snakeEndX++;
                        putpixel(snakeEndX,snakeEndY,0);
                }
                else if(direction==1)
                {
                    snakeEndX--;
                    putpixel(snakeEndX,snakeEndY,0);
                }
                else if(direction==2)
                {
                    snakeEndY++;
                    putpixel(snakeEndX,snakeEndY,0);
                }
                else if(direction==5)
                {
                    snakeEndY--;
                    putpixel(snakeEndX,snakeEndY,0);
                }
            }
            delay(10);
        }
        else
        {
            //If EGG is eaten
            int i,j;
            //The below for loop is for removing the egg which is eaten
            for(i=0; i<10; i++)
            {
                for(j=0; j<10; j++)
                {
                    putpixel(eggX+i,eggY+j,0);
                }
            }
            printf("Egg is Eaten");
            eggEaten=0;
            int eggOnSnake=0;
            eggX=rand()%(980+1-100)+100;    //rand() % (max_number + 1 - minimum_number)) + minimum_number
            eggY=rand()%(580+1-70)+70;
            //Produce the new EGG
            for(i=0; i<10; i++)
            {
                for(j=0; j<10; j++)
                {
                    if(getpixel(eggX+i,eggY+j)==4)  //If the new egg is on the snake's body then produce another egg
                    {
                        eggOnSnake=1;
                        //printf("egg on the snake\n");
                        eggEaten=1;
                        break;
                    }
                    else
                    {
                        putpixel(eggX+i,eggY+j,4);
                        //delay(20);
                    }
                }
            }
            if(eggOnSnake==1)
            {
                for(i=0; i<10; i++)
                {
                    for(j=0; j<10; j++)
                    {
                        putpixel(eggX+i,eggY+j,0);
                    }
                }
            }
            //delay(10);
        }
    }
}
void snakeInitialize();
void goRight(int snakeInitPointX, int snakeInitPointY, int snakeEndX, int snakeEndY);
void goLeft(int snakeInitPointX, int snakeInitPointY, int snakeEndX, int snakeEndY);
int main()
{
    int gd=DETECT;
    int gm;
    int startVar;
    int length,width;
   // initgraph(&gd,&gm,"C:\\TC\\BGI");
    initwindow(1080,640);
    outtextxy(30,30,"Press 1 for left     2 for Down     3 for Right     5 for Up");
    outtextxy(5,5,"Snake Game : Made By Tapan Amin");
    //Set the window for the game
    rectangle(80,50,1000,600);
    rectangle(81,51,999,599);
    rectangle(82,52,998,598);
    printf("Enter 1 to start the Game :");
    scanf("%d",&startVar);
    if(startVar==1)
    {
        score=0;
        //snake's length and width
        //snakeInitPointX and Y ------> where the snake starts from
        //putPixelX and Y is addition of the above 2
        //int length,width,snakeInitPointX,snakeInitPointY,snakeEndX,snakeEndY;
        int lastDirection, forLength, forWidth;
        snakeInitPointX=500;
        snakeInitPointY=200;
        length=400;
        width=0;
        snakeEndY=snakeInitPointY;
        //snake Initialization
        for(forLength=0; forLength<=length; forLength++)
        {
                snakeEndX=snakeInitPointX+forLength;
                //putPixelY=snakeInitPointY+forWidth;
                putpixel(snakeEndX,snakeEndY,1);
                //putpixel(snakeEndX,snakeEndY+1,1);
        }
        putpixel(snakeEndX,snakeEndY,0);
        printf("Egg is produced");
        eggX=rand()%(980+1-100)+100;//rand() % (max_number + 1 - minimum_number)) + minimum_number
        eggY=rand()%(580+1-70)+70;
        //First egg
        for(int i=0; i<10; i++)
        {
            for(int j=0; j<10; j++)
            {
                putpixel(eggX+i,eggY+j,4);
            }
        }
        pthread_t thread_handle;
        int ret = pthread_create(&thread_handle,0,thread_func,0);
        int ret1 = pthread_create(&thread_handle,0,goRight,0);
        if(ret!=0)
        {
            printf("error in thread");
        }
    }
    getch();
    closegraph();
}
