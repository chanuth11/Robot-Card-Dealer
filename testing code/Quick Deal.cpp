void quickDeal ()
{
while(!getButtonPress (buttonAny))
{}
while(getButtonPress (buttonAny))
{
	dealCards ();
	displayString (5, "press any button to deal a card");

}

