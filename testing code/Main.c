/*
David Szczecina
MTE 121
Main
*/
task main(){

while (true){

		displayString(5,"Manual Mode?");
		displayString(10, "Y/N (Left/Right buttons)");

		while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight)){}
		while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
			{
				if(getButtonPress(buttonLeft))
				{
					manualMode();
				}

		displayString(5,"Colour Mode?");
		displayString(10, "Y/N (Left/Right buttons)");

		while(!getButtonPress(buttonLeft) && !getButtonPress(buttonRight)){}
		while(getButtonPress(buttonLeft) || getButtonPress(buttonRight))
			{
				if(getButtonPress(buttonLeft))
				{
					ColourMode();
				}
			}
	}
}
