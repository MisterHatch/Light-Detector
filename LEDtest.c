#include <stdio.h>
#include <stdlib.h>

int LED

int main(){

FILE* LEDfile;

LEDfile = fopen("/sys/class/gpio/gpio49/value","rw");
printf("First step Worked\n");

system("cat /sys/class/gpio/gpio49/value");

fscanf(LEDfile, "%d", &LED);

printf("Current value is : %d", LED);

LED = 1;

fprintf(LEDfile, "%d", LED);

system("cat /sys/class/gpio/gpio49/value");

delay(3000)

LED = 0;

fprintf(LEDfile, "%d", LED);

system("cat /sys/class/gpio/gpio49/value");

//fprintf(NameOfFilePointer, "%d", myIntegerVariableName);

fclose(LEDfile);
return 0;
}