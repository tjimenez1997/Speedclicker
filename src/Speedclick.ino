/*
Speedclick v1 (Beta)
By Thomas Jimenez

Elapsed Project Time: Around 13 Hours

TODO:
Fix Graphical Flashes Properly
Possible bug with Start Button (May have to click twice)
Add EEPROM for Permanent High Score Storage
Method to Soft Reset High Score?
Understand the method of keeping time
Possibly use libraries to simplify redundancy

*/

#include <LiquidCrystal.h>

int switchState1 = 0;
int switchState2 = 0;
int switchState3 = 0;
int switchStatestart = 0;
int buttonPin1 = 0;
int buttonPin2 = 1;
int buttonPin3 = 6;
int startButton = 7;
int screen = 0;
int index = 0;
int highscore;
int interval=1000;
long prevtime=0;
long time;
int unitsoffaketime = 0;
bool userclick = false;
bool gamestart = false;
bool gamecomplete = false;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
	lcd.begin(16, 2);
	pinMode(buttonPin1, INPUT);
	pinMode(buttonPin2, INPUT);
	pinMode(buttonPin3, INPUT);
	pinMode(startButton, INPUT);
	lcd.print("Speed Clicker");
	delay(5000);
	lcd.clear();

	//Check for Stored High Score (If no high score then set to 0)
	if(highscore == NULL) {
		highscore == 0;
	}
}

void loop() {

	//Reads Button States
	switchState1 = digitalRead(buttonPin1);
	switchState2 = digitalRead(buttonPin2);
	switchState3 = digitalRead(buttonPin3);
	switchStatestart = digitalRead(startButton);


    //Loop to Start Game
	if(switchStatestart == HIGH && gamestart == false){
		lcd.clear(); //Removes artifacts from high score > 10? Check for other graphical bugs
      	userclick = true;
		gamestart = true;
	}


	//Default Timeout or Game Over
	if (gamecomplete) {
		screen = 4;
	}

	//Starts time with Game Start
	if (gamestart == true && gamecomplete == false) {
		time = millis();

	//Logic to count seconds
		if ((long)(time - prevtime) >= interval) {
			prevtime = time;
			unitsoffaketime++;
		}

		lcd.setCursor(0,1) ;
		lcd.print("Time:");
		lcd.print((10-(unitsoffaketime)));
		lcd.print("          ");

		if ((10-(unitsoffaketime)) == 0) {
			gamecomplete = true;
		}
	}




	//Loops when Gamestart = True
	if (gamestart == true) {
		//Switches state if clicked and correct screen is pressed
		if((gamestart == true) && ((switchState1 ||switchState2 ||switchState3) == LOW)) {
			if(userclick) {
				screen = random(1,4);
				userclick = false;
			}
		}

		else if (switchState1 == HIGH) {
			if (screen == 1) {
				index = index + 1;
				lcd.clear();
				delay(50);
				screen = random(1,4);
			} else {
				screen=5;
			}
		}

		else if (switchState2 == HIGH) {
			if (screen == 2) {
				index = index + 1;
				lcd.clear();
				delay(50);
				screen = random(1,4);
			} else {
				screen = 5;
			}
		}

		else if (switchState3 == HIGH) {
			if (screen == 3) {
				index = index + 1;
				lcd.clear();
				delay(50);
				screen = random(1,4);
			}
			else {
				screen = 5;
			}
		}
	}
  //Different Screen States
	switch(screen) {
		case 0:
      	lcd.print("High Score: ");
		lcd.print(highscore);
		lcd.setCursor(0,1) ;
		lcd.print("Press Start     ");
		break;

		case 1:
		lcd.setCursor(0,0) ;
		lcd.print("Press 1      ");
		break;

		case 2:
		lcd.setCursor(0,0) ;
		lcd.print("Press 2      ");
		break;

		case 3:
		lcd.setCursor(0,0) ;
		lcd.print("Press 3      ");
		break;

		case 4:
		gamestart = false;
		lcd.clear();
		lcd.print("Game Over");
		lcd.setCursor(0,1) ;
		lcd.print("Your Score:");
		lcd.print(index);
		if(index > highscore) {
			highscore = index;
		}
		delay(3000);
		lcd.clear();
		//Resets Game
		gamecomplete = false;
		gamestart = false;
		unitsoffaketime = 0;
		index = 0;
		screen = 0;
		break;

		case 5:
		lcd.clear();
		lcd.print("You lose");
		delay(3000);
		screen = 4;
		break;

	}
}
