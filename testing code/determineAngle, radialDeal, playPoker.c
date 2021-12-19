/*
	Determine Angle Function
	Radial Deal Function
	Play Poker Function

	Marko Vehauc
 */


// determines the turn angle when dealing radially
float determineAngle(int numPlayers)
{
	return 360 / numPlayers;
}


// deals cards radially
void radialDeal(int numPlayers, int numCards, int distance)
{
	for (int counter = 1; counter <= numPlayers; counter++)
	{
		time1[T1] = 0;
		driveDist(distance);
		int elapsedTime = time1[T1];

		dealCard(numCards);

		time1[T1] = 0;
		motor[motorA] = motor[motorD] = 25;

		while (time1[T1] < elapsedTime)
		{}

		motor[motorA] = motor[motorD] = 0;

		rotate(determineAngle(numPlayers));
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
	int cardsPerRound[3] = {3, 1, 1};
	string roundName[3] = {"flop", "turn", "river"};

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

	// clear display
	displayString(0, "");
	displayString(1, "");
	displayString(3, "");

	// deal 2 cards to each player
	radialDeal(numPlayers, NUM_CARDS, DIST_TO_PLAYER);

	// deal the community cards
	for (int dealRound = 0; dealRound < 3; dealRound++)
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
		displayString(0, "");

		for (int cardsDealt = 1; cardsDealt <= cardsPerRound[dealRound];
				 cardsDealt++)
		{
			driveDist(DIST_BW_CARDS);
			distToDiscard += DIST_BW_CARDS;
			dealCard(1);
		}
	}
}
