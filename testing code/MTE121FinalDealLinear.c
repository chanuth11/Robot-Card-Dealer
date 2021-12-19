


dealLinear(int numPlayers, int numCards)
{
	CONST int DIST = 50; // set distance of table

	while (numCards > 0)
	{
			for(int count = 0; count > numPlayers; count++)
			{
			quickDeal();
			numCards--;
			driveDist(DIST/numPlayers);
			}
			driveDist(-numPlayers);
		}
}
