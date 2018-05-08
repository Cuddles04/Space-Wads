#include <Arduboy2.h>
#include "Integers.h"
#include "Bitmaps.h"
Arduboy2 arduboy;

void setup()
{
  //Start The Arduboy
  arduboy.begin();
  //Make Random
  arduboy.initRandomSeed();
  //SetFrames
  arduboy.setFrameRate(15);
  //Fix Player Position
  player.x = 60;
  player.y = 32;
  player.lives = 3;

}

void loop()
{

  //Frame Fix
  if(!arduboy.nextFrame()) return;
  arduboy.clear(); 
  arduboy.pollButtons();

  switch( gamestate ){
      
    case 0:    
    
      // Start
      arduboy.setTextSize(2);
      arduboy.setCursor(5,20);
      arduboy.print("Space Wads");
      arduboy.setTextSize(0);
      arduboy.setCursor(45,55);
      arduboy.print("Press A");
      if (arduboy.justPressed(A_BUTTON)) { gamestate = 1; }
      break;

    case 1:  
    
      // DrawPlayer
      arduboy.drawBitmap(player.x,player.y,Player,8,7); 
      arduboy.setCursor(0,0);
      arduboy.print(player.lives);

      
      // Movement      
      if (arduboy.pressed(RIGHT_BUTTON))     { player.x+=2; }
      if (arduboy.pressed(LEFT_BUTTON))      { player.x-=2; }
      if (arduboy.pressed(UP_BUTTON))        { player.y-=2; }
      if (arduboy.pressed(DOWN_BUTTON))      { player.y+=2; }
      if (arduboy.pressed(B_BUTTON))         { gamestate = 2; }


      // Check limits      
      if (player.x > 120)   player.x = 120;
      if (player.x < 1)     player.x = 1;
      if (player.y > 57)    player.y = 57;
      if (player.y < 1)     player.y = 1;

      
      // Draw Stars      
      for (uint8_t i = 0; i < 25; ++i) {
        
        if (!star[i].active) {
          
          star[i].active = true;
          star[i].x = random(0,128);
          star[i].y = 0;
          star[i].inc = random(2, 5);
          
        }
        
        if (star[i].randomize == true) {
          star[i].y = random(0,64);
          star[i].randomize = false;
        }
        
        if (star[i].active) {
          
          arduboy.drawRect(star[i].x,star[i].y,1,1);
          star[i].y = star[i].y + star[i].inc;
          
          if(star[i].y >= 64) {
            star[i].active = false;
          }
          
        }
      }

      
      //Draw Asteroids
      for (uint8_t i2 = 0;i2 < 10;++i2) {
        
        if (!asteroid[i2].active) {
          asteroid[i2].active = true;
          asteroid[i2].x = random(0,124);
          asteroid[i2].y = 0;
          asteroid[i2].inc = random(2, 4);
        }
        
        if (asteroid[i2].randomize == true) {
          asteroid[i2].y = random(0,32);
          asteroid[i2].randomize = false;
        }
        
        if (asteroid[i2].active) {
           //Set Up Collison Boxes
           Rect rectB{asteroid[i2].x,asteroid[i2].y,6,6};
           Rect rectA{player.x,player.y,8,7};
           
           //Collision Checking
           
           if(arduboy.collide(rectA,rectB)) {
             player.lives-=1;
             asteroid[i2].active = false;
           }
            
          if(player.lives == 0)
          {
            player.lives = 3;
            gamestate = 3;
          }
          arduboy.drawBitmap(asteroid[i2].x,asteroid[i2].y,Asteroid,6,6);
          asteroid[i2].y = asteroid[i2].y + asteroid[i2].inc;
          
          if(asteroid[i2].y >= 64) {
            asteroid[i2].active = false;
          }
        }
      }
      break;

    case 2:
      arduboy.setCursor(48,30);
      arduboy.print("Paused");
      arduboy.setCursor(45,40);
      arduboy.print("Press A");
      if(arduboy.justPressed(A_BUTTON)) { gamestate = 1; }
      break;
      
    case 3:
      arduboy.setCursor(38,30);
      arduboy.print("Game Over");
      if(arduboy.justPressed(B_BUTTON)) { gamestate = 0; }
      
  }

  arduboy.display();

}


