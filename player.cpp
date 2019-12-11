#include "player.h"
#include "globals.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

player::player() {//constructor
	//position of player
	xPos = 100;
	yPos = SCREEN_H - 50;

	//player velocity
	xVel = 0;
	yVel = 0;

	isOnGround = false;
	CanJump = false;
	ID = PLAYER;

}

void player::moveLeft() { xVel--; }
void player::moveRight() { xVel++; }
void player::Jump() { 
	if (CanJump)
		yVel = -10;

}
void player::draw() { 
	al_draw_filled_rectangle(xPos, yPos, xPos + 30, yPos + 30, al_map_rgb(50, 120, 10));
}
void player::move(vector<gameObject*>stuff) {
	//deal wth platform collision

	vector < gameObject*> ::iterator iter;
	int x;
	int y;
	for (iter = stuff.begin(); iter != stuff.end(); iter++) {
		if ((*iter)->getID()==PLATFORM) {  //only worry about platforms
			x = (*iter)->getX();
			y = (*iter)->getY();
		
			if (VerticalCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), PLATFORM_WIDTH, PLATFORM_HEIGHT, yVel) == 2) {
				yVel = -1.0;
				isOnGround = true;
			}//if
			if (VerticalCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), PLATFORM_WIDTH, PLATFORM_HEIGHT, yVel) == 1) {
				yVel = 0.0;
				isOnGround = true;
			}//if

		}//platform
	}//forloop platform

	//update player position by adding velocity
	xPos += xVel;
	yPos += yVel;

	//friction
	xVel *= .7;

	//gravity
	if (isOnGround == false) {
		yVel += .4;//falling speed
			CanJump = false;//turn off flying
	}

	else {
	
		yVel = 0;//stop downward movement if on ground
		CanJump = true;
	}
	if (yPos + 30 > SCREEN_H)
		isOnGround = true;
	else
		isOnGround = false;

	//set terminal velocity
	if (yVel > 5)
		yVel = 5;
		
		//bounds checking
	if (xPos < 0)
		xPos = 0;
	if (xPos + 32 > SCREEN_W)
		xPos = SCREEN_W - 32;


}//voiid Player

//Collision Funtion that difffers based on how close your fwwt are yo the ground and allowing you to walk stairs
int player::VerticalCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int ydir) {
	if ((ydir >= 0) &&
		(x1 + w1 > x2) &&
		(x1 < x2 + w2) &&
		(y1 + h1 + 4 > y2) &&
		(y1 < y2)) {
		//
		return 2;
	}
	else if ((ydir >= 0) &&
		(x1 + w1 > x2) &&
		(x1 < x2 + w2) &&
		(y1 + h1 + 6 > y2) &&
		(y1 < y2)) {
		//
		return 1;
	}//intplayer collision
	else
		return false;
}

