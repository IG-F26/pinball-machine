#include <LiquidCrystal.h>
//#include <Servo>

int score = 0;
int highScore = 500;
bool highscoreReached = false;
int ballsLeft = 5; //sensor each time ball goes back into machine

//????? get the game to start again
//once a ball runs over the sensor in the resevoir decrement the count by 1
bool gameoverTriggered = false; 
int gameoverPin = __; //once ran over by all five balls game stops >> connect to sensor
//code the holes
//code doors

//spiral ramp logic
bool rampTriggered = false;
const int RAMP_PIN = __;
const int DOOR_PIN = __;
int rampPoints = __;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(gameoverPin, INPUT);
  pinMode(scorePin, INPUT);
}

void loop() 
{
  //pin inputs
  int gameoverState = digitalRead(gameoverPin);
  int scoreState = digitalRead(scorePin);
  // ramp logic
  while(gameoverTriggered)
  {
    int rampState = digitalRead(RAMP_PIN);
    int doorState = digitalRead(DOOR_PIN);
    {
      if(rampState and !rampTriggered)
      {
      score+= rampPoints;
      rampTriggered = true;
      }
    }
  }
}
