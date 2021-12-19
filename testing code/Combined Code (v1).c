/*
Combined Code v.1
Team 50
*/


// configures the sensors
void configSensors()
{
	SensorType [S1] = sensorEV3_Touch;
	wait1Msec(50);
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


void dealLinear(int numPlayers, int cardsPerPlayer)
{
	const int DIST = 100; // set distance of table

	int totalNumCards = cardsPerPlayer * numPlayers;

	while (totalNumCards > 0)
	{
		for(int count = 0; count > numPlayers; count++)
		{
		dealCard(1);
		totalNumCards--;
		driveDist(DIST/numPlayers);
		}
		driveDist(-DIST);
	}
}


// deals cards radially
void radialDeal(int numPlayers, int numCards, int distance)
{
	int elapsedTime = 0;

	for (int counter = 1; counter <= numPlayers; counter++)
	{
		time1[T1] = 0;
		driveDist(distance);
		elapsedTime = time1[T1];

		dealCard(numCards);

		time1[T1] = 0;
		motor[motorA] = motor[motorD] = 25;

		while (time1[T1] < elapsedTime)
		{}

		motor[motorA] = motor[motorD] = 0;

		rotate(determineAngle(numPlayers));
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

	while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
	{}
	while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
	{
		if(getButtonPress(buttonLeft))
			numCards = 54;
		else
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

		while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
		{}
		while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
		{
			if(getButtonPress(buttonLeft))
				numPlayers--;
			else
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

	bool setCardsPerPlayer = 0;
	while (!setCardsPerPlayer)
	{
		displayString(5, "Cards per player: %d", cardsPerPlayer);
		displayString(10, "Left to decrease");
		displayString(11, "Right to increase");
		displayString(12, "Down to enter");

		while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight) && !getButtonPress(buttonDown))
		{}
		while(getButtonPress(buttonLeft) || getButtonPress(buttonRight) || getButtonPress(buttonDown))
		{
			if(getButtonPress(buttonLeft))
				cardsPerPlayer--;
			else if(getButtonPress(buttonRight))
				cardsPerPlayer++;
			else if((cardsPerPlayer * numPlayers <= numCards) && (cardsPerPlayer > 0))
				setCardsPerPlayer = 1;
			else
				displayString(10, "Invalid number, please change");
		}
	}

	//deal in circle or deal in line
	displayString(5, "Deal in circle (Left)");
	displayString(10, "Deal in line (Right)");

	while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
	{}
	while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
	{
		if(getButtonPress(buttonLeft))
		{
			const int DIST_TO_PLAYER = 100;
			radialDeal(numPlayers, cardsPerPlayer, DIST_TO_PLAYER);
		}
		else
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
		dealCard(1);
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
			dealCard(1);
		}
	}
}





task main()
{
	while (true)
	{
		displayString(5,"Manual Mode?");
		displayString(10, "Y/N (Left/Right buttons)");

		while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
		{}
		while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
		{
			if(getButtonPress(buttonLeft))
			{
				manualMode();
			}

			displayString(5,"Colour Mode?");
			displayString(10, "Y/N (Left/Right buttons)");

			while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight))
			{}
			while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
			{
				if(getButtonPress(buttonLeft))
				{
					ColourMode();
				}
			}
		}
	}
}
