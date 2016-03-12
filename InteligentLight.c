/*David Hatch and Christopher Harte:

	Intelligent Lighting Embedded System-
		-System will turn LED on and off automatically
			-LED will be on when environment is dark
			-LED will be off when environment is light
		-System will have a manual override initaied via push button
			-When pushed LED will toggle states
				-On to off
				-Off to on
		-Program will keep track of timing
			-Program will track exact time and date LED is on and off
			-Program will print to command line date and time light changes state
			-Program will output how long the LED was in the previous state
			
	NOTE: 
		-Sensor in on pin P9_39
		-Button in on pin P9_11
		-LED out on pin P9_12
		
*/


//////////////////////////////////////////////////
//Preprocessor directives
//////////////////////////////////////////////////
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//////////////////////////////////////////////////
//Global Variables
//////////////////////////////////////////////////


//Variables for Light Sensor
int Ain = 0;
int AinComp = 1000;
int SensorTrig = 0:
FILE *Ain0;
	
//Variables for Button Push
int Oldstate = 0;
int Newstate = 0;
int Buttonpress = 0;
FILE *Button;

//Variables for LED access
//
//LED state variable
// 1 = on
// 0 = off
int LED = 0; 
FILE* LEDfile;

//Timing Variables
// for time and date
clock_t StarttimeNew, StarttimeOld, Stoptime, Statetime;
time_t date;


//////////////////////////////////////////////////
//Funtions
//////////////////////////////////////////////////

//
//Toggle LED
//
int TLED(){
//Toggle LED
LEDfile = fopen("/sys/class/gpio/gpio49/value","r");
fscanf(LEDfile, "%d", &LED);
//Close file
fclose(LEDfile);

//if LED is on, turn off
if(LED == 1){
	LEDoff();
}
//else turn LED on
else{
	LEDon();
}

//Call Ptime to print the time
Ptime();

return 0;
}

//
//Turn LED ON*************************************************************
//
int LEDon(){
//Turns LED on

//Open LED file
LEDfile = fopen("/sys/class/gpio/gpio49/value","w");

//Set LED variable to on
LED = 1;

//Write to LED file
fprintf(LEDfile, "%d", LED);

//Close LED file
fclose(LEDfile);

//Call Ptime to print the time
Ptime();

return 0;	
}

//
//Turn LED OFF*************************************************************
//
int LEDoff(){
//Turns LED off

//Open LED file
LEDfile = fopen("/sys/class/gpio/gpio49/value","w");

//Set LED variable to on
LED = 0;

//Write to LED file
fprintf(LEDfile, "%d", LED);

//Close LED file
fclose(LEDfile);

//Call Ptime to print the time
Ptime();

return 0;
}

//
//Print Timing
//
int Ptime(){
//	prints time and date and keeps track 
//		of start and stop times for LED

//Set stop time and start time new to current time
Stoptime = clock();
StarttimeNew = Stoptime;

//determine time LED was in current state
//   state time = stop time - start time
Statetime = (double)(Stoptime - StarttimeOld)/CLOCKS_PER_SEC;

//Print date to command line
printf("The state of the LED changed on: ", ctime(&date);
//Print to command line the time LED was in Previous State
printf("The LED remained in its previous state for %d seconds", %Statetime);

//Set start time old to start time new
StarttimeOld = StarttimeNew;

return 0;
}

//////////////////////////////////////////////////
//Main 
//////////////////////////////////////////////////
int main()
{	
	//While loop to run program indefinately
	while(1){
		
		
		
		
//LIGHT SENSOR HANDLING/////////////////////////////
		//Open file and read Sensor Signal
		Ain0 = fopen("/sys/bus/iio/devices/iio:device0/in_voltage0_raw","r");
		fscanf(Ain0,"%d",&Ain);
		
		//Check if Sensor has switched states
		if(((AinComp-Ain)<-500)|(AinComp-Ain)>500)){
			SensorTrig = 1;
		}
		
		
		//Check if light is ON or OFF
		if(SensorTrig==1){
			
			//Determine if HIGH or LOW
			//	NOTE: Light off when value below 500
			
			//check if light is on
			if(Ain > 500){
				printf("Light was turned on.\n");
				LEDoff();
				AinComp=Ain;
				SensorTrig=0;
			}
			//If light is not on it is OFF
			else{
				printf("Light was turned off.\n");
				LEDon();
				AinComp=Ain;
				SensorTrig=0;
			}
		}	
		fclose(Ain0);
		
//BUTTON PRESS HANDLING/////////////////////////////
		//Open file to check newstate of button
		Button = fopen("/sys/class/gpio/gpio115/value","r");
		fscanf(Button,"%d",&Newstate);
		
		//Check if button is pressed
		if((Oldstate==0)&(Newstate==1){
			Buttonpress = 1;
		}
		
		//Reset Oldsate variable to Newstate
		Oldstate = Newstate;
		
		//If button is pressed call toggle LED
		if(Buttonpress==1){
			//Call toggle LED
			TLED();
			
			//Reset Buttonpress variable
			Buttonpress = 0;
		}
		
		//Close file for Button
		fclose(Button);
	}

	return 0;
}