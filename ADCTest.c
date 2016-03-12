

#include <stdio.h>
#include <stdlib.h>

int volt = 0;

int main(){

//char* file="/sys/bus/iio/devices/iio:device0/in_voltage0_raw";
FILE* infile;

infile = fopen("/sys/bus/iio/devices/iio:device0/in_voltage0_raw","r");
printf("First step Worked\n");

fscanf(infile, "%d", &volt);

system("cat /sys/bus/iio/devices/iio:device0/in_voltage0_raw");

printf("Voltage in is : %d \n",volt);

fclose(infile);
return 0;
}
