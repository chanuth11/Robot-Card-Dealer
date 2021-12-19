/*
	Combined Code v.1
	Team 50
*/


// configures the sensors
void configSensors()
{
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType [S4] = sensorEV3_Gyro;
	wait1Msec (50);
	nMotorEncoder[motorA] = 0;
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}


// determines the maximum number of cards per player
int maxCardsPerPlayer(int numPlayers, int numCards)
{
	int maxNumCards = 0;
	maxNumCards = (numCards / numPlayers);
	return maxNumCards;
}


// determines the turn angle when dealing radially
float determineAngle(int numPlayers)
{
	return 360 / numPlayers;
}


// deal cards
void dealCards(int numCards)
{
	const int MED_SPEED = 10;
	const float CARD_LENGTH = 1.55;
	int card = numCards;
	int enc_limit = (card * CARD_LENGTH) * 180 / PI * 2.75;

	motor[motorB] = MED_SPEED;
	while (nMotorEncoder[motorB] < enc_limit)
	{}
}


// Drive distance in metre
int driveDist(float dist_cm)
{
	const int MOTOR_POWER = 25;
	int enc_limit = dist_cm * 180 / (PI * 2.75);

	time1[T1] = 0;
	nMotorEncoder[motorA] = 0;

	motor[motorA] = motor[motorD] = MOTOR_POWER;
	while (nMotorEncoder[motorA] < enc_limit)
  {}
	motor[motorA] = motor[motorD] = 0;

	return time1[T1];
}


// Rotate Gyro
void rotateRobot(int angle)
{
	int motorPower = 25;
	tSensors gyroPort = S4;
	resetGyro(gyroPort);

	if (angle > 0)
	{
		motor[motorA] = -motorPower;
		motor[motorD] = motorPower;
	}
	else
	{
		motor[motorA] = motorPower;
		motor[motorD] = -motorPower;
	}

	angle = abs(angle);
	while (abs(getGyroDegrees(gyroPort)) < angle)
	{}
	motor[motorA] = motor[motorD] = 0;
}


// deals cards in a line
void dealLinear(int numPlayers, int cardsPerPlayer)
{
	const int DIST = 100; // set distance of table

	int totalNumCards = cardsPerPlayer * numPlayers;

	while (totalNumCards > 0)
	{
		for(int count = 0; count > numPlayers; count++)
		{
		dealCards(1);
		totalNumCards--;
		driveDist(DIST/numPlayers);
		}
		driveDist(-DIST);
	}
}


// deals cards in a circle
void radialDeal(int numPlayers, int numCards, int distance)
{
	int elapsedTime = 0;

	for (int counter = 1; counter <= numPlayers; counter++)
	{
		time1[T1] = 0;
		driveDist(distance);
		elapsedTime = time1[T1];

		dealCards(numCards);

		time1[T1] = 0;
		motor[motorA] = motor[motorD] = 25;

		while (time1[T1] < elapsedTime)
		{}

		motor[motorA] = motor[motorD] = 0;

		rotateRobot(determineAngle(numPlayers));
	}
}


// allows for user input
void manualMode()
{
	int numCards = 0;
	int numPlayers = 0;
	int cardsPerPlayer = 0;


	//are there jokers in the deck
	//one if statement
	displayString(5, "Are there jokers in the deck?");
	displayString(10, "Y/N (Left/Right buttons)");

	while (!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
	{}
	if (getButtonPress(buttonLeft))
	{
		while (getButtonPress(buttonLeft))
		{}
		numCards = 54;
	}
	if (getButtonPress(buttonRight))
	{
		while (getButtonPress(buttonRight))
		{}
		numCards = 52;
	}


	//set num players
	//left to decrease, right to increase
	// down button sets value and exits loop
	// in a loop so that the display is always updated
	while (!getButtonPress(buttonDown))
	{
		displayString(5, "Number of players: %d", numPlayers);
		displayString(10, "Left to decrease");
		displayString(11, "Right to increase");
		displayString(12, "Down to enter");

		while (!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
		{}
		if (getButtonPress(buttonLeft) && numPlayers > 0)
		{
			while (getButtonPress(buttonLeft))
			{}
			numPlayers--;
		}
		if (getButtonPress(buttonRight))
		{
			while (getButtonPress(buttonRight))
			{}
			numPlayers++;
		}
	}

	while (getButtonPress(buttonDown))
	{}

	//set cardsPerPlayer
	//left to decrease, right to increase
	// in a loop so that the display is always updated
	// down button sets value and exits loop if value satisfies conditions
	//checks if cardsPerPlayer*numPlayers >= numCards & cardsPerPlayer >0

	while (!getButtonPress(buttonDown))
	{
		displayString(5, "Cards per player: %d", cardsPerPlayer);
		displayString(10, "Left to decrease");
		displayString(11, "Right to increase");
		displayString(12, "Down to enter");

		while (!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
		{}

		if (getButtonPress(buttonLeft) && cardsPerPlayer > 0)
		{
			while (getButtonPress(buttonLeft))
			{}
			cardsPerPlayer--;
		}

		if (getButtonPress(buttonRight) && cardsPerPlayer <= maxCardsPerPlayer(numPlayers, numCards))
		{
			while (getButtonPress(buttonRight))
			{}
			cardsPerPlayer++;
		}
	}

	//deal in circle or deal in line
	displayString(5, "Deal in circle (Left)");
	displayString(10, "Deal in line (Right)");

	while (!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
	{}

	if (getButtonPress(buttonLeft))
	{
		while (getButtonPress(buttonLeft))
		{}
		const int DIST_TO_PLAYER = 100;
		radialDeal(numPlayers, cardsPerPlayer, DIST_TO_PLAYER);
	}
	else
	{
		while (getButtonPress(buttonRight))
		{}
		dealLinear(numPlayers, cardsPerPlayer);
	}
}


void playPoker()
{
	// declaring constants and ints
	int numPlayers = 4;
	const int MAX_PLAYERS = 10;
	const int MIN_PLAYERS = 2;

	const int NUM_CARDS = 2;
	const int DIST_TO_PLAYER = 100;

	int distToDiscard = 20;
	const int DIST_BW_CARDS = 10;

	const int NUM_ROUNDS = 3;
	int cardsPerRound[NUM_ROUNDS] = {3, 1, 1};
	string roundName[NUM_ROUNDS] = {"flop", "turn", "river"};

	displayString(0, "Select the number of players");
	displayString(1, "(Press the enter button to confirm)");

	// user input for number of players
	while (!getButtonPress(buttonEnter))
	{
		displayString(3, "%d", numPlayers);

		if (getButtonPress(buttonUp) && numPlayers < MAX_PLAYERS)
		{
			while (getButtonPress(buttonUp))
			{}
			numPlayers++;
		}

		if (getButtonPress(buttonDown) && numPlayers > MIN_PLAYERS)
		{
			while (getButtonPress(buttonDown))
			{}
			numPlayers--;
		}
	}

	eraseDisplay();

	// deal 2 cards to each player
	radialDeal(numPlayers, NUM_CARDS, DIST_TO_PLAYER);

	// deal the community cards
	for (int dealRound = 0; dealRound < NUM_ROUNDS; dealRound++)
	{
		// discard 1 card
		driveDist(-distToDiscard);
		dealCards(1);
		driveDist(distToDiscard);

		// prompt for user input
		displayString(0, "Press the enter button to deal the %s",
		roundName[dealRound]);

		// wait for user input
		while (!getButtonPress(buttonEnter))
		{}
		while (getButtonPress(buttonEnter))
		{}

		// clear display
		eraseDisplay();

		for (int cardsDealt = 1; cardsDealt <= cardsPerRound[dealRound];
		cardsDealt++)
		{
			driveDist(DIST_BW_CARDS);
			distToDiscard += DIST_BW_CARDS;
			dealCards(1);
		}
	}
}


void playPresident()
{
	int numPlayers = 4;
	const int MAX_PLAYERS = 7;
	const int MIN_PLAYERS = 3;
	const int ONE_CARD = 1;
	const int DIST_TO_PLAYER = 100;

	displayString(0, "Select the number of players");
	displayString(1, "(Press the enter button to confirm)");

	// user input for number of players
	while (!getButtonPress(buttonEnter))
	{
		displayString(3, "%d", numPlayers);

		if (getButtonPress(buttonUp) && numPlayers < MAX_PLAYERS)
		{
			while (getButtonPress(buttonUp))
			{}
			numPlayers++;
		}

		if (getButtonPress(buttonDown) && numPlayers > MIN_PLAYERS)
		{
			while (getButtonPress(buttonDown))
			{}
			numPlayers--;
		}
	}

	eraseDisplay();

	radialDeal(numPlayers, ONE_CARD, DIST_TO_PLAYER);
}


void playGoFish()
{
  int numPlayers = 0;
	const int MAX_PLAYERS = 7;
	const int MIN_PLAYERS = 2;
	const int ONE_CARD = 1;


	// user input for number of players
	while (!getButtonPress(buttonEnter))
	{
		displayString(3, "%d", numPlayers);

		if (getButtonPress(buttonUp) && numPlayers < MAX_PLAYERS)
		{
			while (getButtonPress(buttonUp))
			{}
			numPlayers++;
		}

		if (getButtonPress(buttonDown) && numPlayers > MIN_PLAYERS)
		{
			while (getButtonPress(buttonDown))
			{}
			numPlayers--;
		}
	}

	eraseDisplay();


  if (numPlayers > 3)
  {
  	dealLinear(numPlayers, 5); // deal 5 cards per player
  }
  else if (numPlayers <= 3)
  {
  	dealLinear(numPlayers, 7); // deal 7 cards per player
  }


  bool gameActive = true;

  while (gameActive)
  {
  	displayString(8, "game has begun, press the enter button to deal a card");
  	displayString(10, "press the down button to end the game");

  	while (!getButtonPress(buttonEnter) && !getButtonPress(buttonDown))
  	{}

 		if (getButtonPress(buttonEnter))
 		{
 			while(getButtonPress(buttonEnter))
 			{}
 			dealCards(ONE_CARD);
 		}
 		if (getButtonPress(buttonDown))
 		{
 			while(getButtonPress(buttonDown))
 		  {}
 			gameActive = false;
 		}
  }
}


// selects a game
void colourMode()
{
	if (SensorValue[S3] == (int)colorGreen)
	{
	   displayString(1, "green");
	   playPoker();
	}
	else if (SensorValue[S3] == (int)colorBlue)
	{
	   displayString(1, "blue");
	   playGoFish ();
	}
	else if (SensorValue[S3] == (int)colorRed)
	{
	   displayString(1, "red");
	   playPresident();
	}
	else if (SensorValue[S3] == (int)colorYellow)
	{
	   displayString(1, "yellow");
	   dealCards(1);
	}
}


task main()
{
	configSensors();

	while (true)
	{
		displayString(5, "Manual Mode (Left) or Colour Mode (Right)?");

		while (!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
		{}

		if (getButtonPress(buttonLeft))
		{
			while (getButtonPress(buttonLeft))
			{}
			manualMode();
		}

		if (getButtonPress(buttonRight))
		{
			while (getButtonPress(buttonRight))
			{}
			colourMode();
		}
	}
}
