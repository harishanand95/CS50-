//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(int argc,char* argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

	float xvel = 1.0 ;
	
	float yvel = 1.0 ;
	
	// keep playing until game over
    while (lives > 0 && bricks > 0)
    {
      	if(lives != 3)
		ball = initBall(window);
		waitForClick();
		while(true)
		{
			move(ball,xvel,yvel);
			if(argc == 2 && !strcmp(argv[1],"GOD"))
 		    {
				
					double x = getX(ball);
			    	if(x > getWidth(window) - 60)
						x = getWidth(window) - 60;
					if(x < 0)
						x = 0;
        	    	setLocation(paddle, x,550);
				
			}
			else
			{
				GEvent event = getNextEvent(MOUSE_EVENT);
				if(!(event == NULL ))
				{
					if(getEventType(event) == MOUSE_MOVED)
					{
						double x = getX(event);
						if(x > getWidth(window) - 60)
							x = getWidth(window) - 60;
						if(x < 0)
							x = 0;
        	        	setLocation(paddle, x,550);
					}
				}
			}	
			if(getWidth(ball) + getX(ball) >= getWidth(window))
				xvel = -xvel;
			else if (getWidth(ball) + getY(ball) >= getHeight(window))
       		   	break;
			else if (getX(ball) <= 0)      		
				xvel = -xvel;
			else if (getY(ball) <= 0)
				yvel = -yvel;
			else if ( getX(ball)+ getY(ball) == 0 )
			{	yvel = -yvel;
				xvel = -xvel;
			}
			else if( getY(ball) == 0 && getX(ball) + getWidth(ball) == getWidth(window))
			{
				yvel = -yvel;
				xvel = -xvel;		
			}
			else if ( getX(ball) == 0 && getY(ball) + getWidth(ball) == getHeight(window) )
			{	yvel = -yvel;
				xvel = -xvel;
			}
			else if ( getX(ball) + getWidth(ball) == getWidth(window) && +  getY(ball) + getWidth(ball) == getHeight(window) )
			{	yvel = -yvel;
				xvel = -xvel;
			}
			pause(10);
			GObject object = detectCollision(window,ball);
			if(object == paddle)
			{
					yvel = -yvel;	
			}			
			GObject brick = detectCollision(window,ball);
			if(brick == NULL)
			{
				continue;
			}
			if(getY(brick) == 120 || getY(brick) == 105 || getY(brick) == 90 || getY(brick) == 75 || getY(brick) == 60  )
			{
					bricks--;
					points++;
					updateScoreboard(window,label,points);
					removeGWindow(window,object);
					yvel = -1*yvel + 0.1;
					if(xvel>0)
						xvel = xvel + 0.1;
					else
						xvel = xvel - 0.1;
			}
			if(bricks == 0)
			 break;
		}
		removeGWindow(window,ball);			
		lives = lives - 1;	

	}
    // wait for click before exiting
    waitForClick();
	waitForClick();
    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
	char strary[5][10] = { "RED","ORANGE","YELLOW","GREEN","CYAN" };
	
	for(int i = 0 , flag2 = 60; i < ROWS; flag2 += 15 )
	{
		for(int j = 0, flag1 = 2;j < COLS;  flag1 += 40)
		{
			GRoundRect rect = newGRoundRect(flag1 , flag2 , 35, 10 ,1);
			setColor(rect, strary[i]);
			setFilled(rect, true);
			setRaised(rect, true);			
			add(window, rect);
			j++;
	    }
		i++;
	}
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
	int x = getWidth(window);
	int y = getHeight(window); 
	GOval ball = newGOval(x/2 - 10,y/2 - 10,20,20);
	setFilled(ball,true);
	setColor(ball,"BLACK");
	add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    //TODO
	int x = getWidth(window);
	GRoundRect pad = newGRoundRect(x/2 - 32 ,550,60,10,1);
	setFilled(pad,true);
	setColor(pad,"BLUE");
	add(window,pad);
    return pad;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
	GLabel label = newGLabel("");
    setFont(label, "SansSerif-56");
	setColor(label,"GREY");
    add(window, label);
	char s[3] ;
	
	sprintf(s, "%i", 0);    
	// update label
    setLabel(label, s);

    // center label
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
	return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
	if(points == 50)
    {
		  GLabel label1 = newGLabel("WON");
      	  setFont(label1, "SansSerif-56");
		  setColor(label1,"RED");
     	  double x = (getWidth(window) - getWidth(label1)) / 2 - 5;
    	  double y = (getHeight(window) + getFontAscent(label1)) / 2;
    	  setLocation(label1, x, y);
    	  add(window, label1);
	}
	else
	{
		char s[12];
		sprintf(s, "%i", points);
    	setLabel(label, s);

    	// center label in window
    	double x = (getWidth(window) - getWidth(label)) / 2;
    	double y = (getHeight(window) - getHeight(label)) / 2;
    	setLocation(label, x, y);
	}
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
