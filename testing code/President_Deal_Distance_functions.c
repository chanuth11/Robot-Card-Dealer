/*
Chanuth Weeraratna
*/
//deal cards
void dealCards(int numCards){
	const int MED_SPEED = 10;
	const double CARD_LENGTH = 1.55;
	int card = numCards;
	int enc_limit = (card * CARD_LENGTH) * 180 / PI * 2.75;
	motor[motorB] = MED_SPEED;
	while (nMotorEncoder[motorB] < enc_limit)
		{}
 }
//Drive distance in metre
 float driveDist(float dist_m, int motorPower)
 {
   time1[T1] = 0;
   nMotorEncoder[motorA] = 0;
   motor[motorA] = motor[motorD] = motorPower;
   int enc_limit = dist_m * 180 / (PI * 0.00275);
   while (nMotorEncoder[motorA] < enc_limit)
     {}
   motor[motorA] = motor[motorD] = 0;
   return time1[T1] / 1000.0;
 }
//president
void President()
{
	int num_players = 4;
	const int MAX_PLAYERS = 7
	const int MIN_PLAYERS = 3;
	const int ONE_CARD;
	const int DIST_TO_PLAYER = 100;

	dealCards(ONE_CARD); // deal 1 card per player
	displayString(0, "Select the number of players");
 	while (!getButtonPress(buttonEnter))
 		{
 			displayString(3, "%d", numPlayers);
 			if (getButtonPress(buttonUp) && num_players)
 			{
 					while (getButtonPress(buttonUP)){}
 					num_players++;
 			}
 			if (getButtonPress(buttonDown) && num_players > )
 			{
 				while (getButtonPress(buttonDown) && num_players > MIN_PLAYERS){}
 				num_players--;
 			}
		}
		radialDeal(num_players, ONE_CARD, DIST_TO_PLAYER);
}
