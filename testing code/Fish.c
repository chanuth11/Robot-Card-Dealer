
void playGoFish()
{
  int num_players = 0;
	const int MAX_PLAYERS = 7; 
	const int MIN_PLAYERS = 1;
	const int ONE_CARD;
	const int DIST_TO_PLAYER = 100;
  if (numPlayers > 3)
  {
  	linearDeal(numPlayers, 5); // deal 5 cards per player
  }
  else if (numPlayers <= 3 && numPlayers > 1)
  {
  	linearDeal(numPlayers, 7); // deal 7 cards per player
  }

  while(!getButtonPress(buttonEnter))
  {}
  while(getButtonPress (buttonEnter))
  {
  	displayString (8, "game has begun, press right button to deal a card");
  }
  while(!getButtonPress (buttonDown))
  {}
  while(getButtonPress (buttonDown))
  {
  	displayString (5, "is game finished");
  	displayString (10, "Y/N (Left/Right Buttons)");
  }
  while (!getButtonPress (buttonLeft) && getButtonPress(buttonRight))
  {}
  while (getButtonPress (buttonLeft) && !getButtonPress(buttonRight))
  {
  	displayString (12, "game over");
  	wait1Msec (5000);
  	eraseDisplay();
  	motor[motorA] = motor[motorD] = 0;
  }
}
