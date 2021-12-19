/*
David Szczecina
MTE 121
Main
*/
void main(){}

void manualMode(){

	int numCards = 0;
	int numPlayers = 0;
	int cardsPerPlayer = 0;


	//are there jokers in the deck
	//one if statement
	displayString(10, "Y/N (Left/Right buttons)");

		while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight)){}
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
				displayString(5, "%d", numPlayers);
				displayString(10, "Left to decrease");
				displayString(11, "right to increase");
				displayString(12, "down to enter");

				while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight)){}
				while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
				{
					if(getButtonPress(buttonLeft))
						numPlayers--;
					else
						numPlayers++;
				}
			}

			//set cardsPerPlayer
			//left to decrease, right to increase
			// in a loop so that the display is always updated
			// down button sets value and exits loop if value satisfies conditions
			//checks if cardsPerPlayer*numPlayers >= numCards & cardsPerPlayer >0

			bool setCardsPerPlayer = 0;
			while (!setCardsPerPlayer)
			{
				displayString(5, "%d", setCardsPerPlayer);
				displayString(10, "Left to decrease");
				displayString(11, "right to increase");
				displayString(12, "down to enter");

				while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight) && !getButtonPress(buttonDown)){}
				while(getButtonPress(buttonLeft) || getButtonPress(buttonRight) || getButtonPress(buttonDown))
				{
					if(getButtonPress(buttonLeft))
						cardsPerPlayer--;
					else if(getButtonPress(buttonRight))
						cardsPerPlayer++;
					else
						if((cardsPerPlayer * numPlayers >= numCards) && (cardsPerPlayer > 0))
							setCardsPerPlayer = 1;
						else
							displayString(10, "Invalid number, please change");
				}
			}

			//deal in circle or deal in line
			displayString(5, "deal in circle (Left)");
			displayString(10, "deal in line (Right)");

			while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight)){}
			while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
			{
				if(getButtonPress(buttonLeft))
					dealInCircle();
				else
					dealInLine();
			}
}
