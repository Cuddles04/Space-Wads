#pragma once
//Integers and Bools ect.
uint8_t gamestate = 0;
uint8_t i = 0;
uint8_t i2 = 0;
//Player
class Player
{
  public:
    uint8_t x = 0;
    uint8_t y = 0;
    bool pause = false;
    uint8_t lives = 3;
};
Player player = player;
//Star                                                                                                                                                     
 struct Star
{
  public:
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t inc = 0;
    bool active;
    bool randomize = true;
};
  Star star[25];

//Asteroid
struct Asteroid
{
  public:
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t inc = 0;
    bool active;
    bool randomize = true;
};
  Asteroid asteroid[10];
  


