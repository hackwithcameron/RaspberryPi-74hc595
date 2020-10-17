/*
 * blankWiringPi.cxx
 * 
 * Copyright 2020  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
 #define DS 0
 #define STCP 1
 #define SHCP 2


#include <iostream>
#include <wiringPi.h>



void pinHigh(int pin)
{
	digitalWrite(pin, 1);
}

void pinLow(int pin)
{
	digitalWrite(pin, 0);
}

void pulse(int pin)
{
	digitalWrite(pin, 0);
	digitalWrite(pin, 1);
}

int init()
{
	if(wiringPiSetup() == -1)
	{
		printf("Initialization failed!!");
		return 1;
	}
	
	pinMode(DS, OUTPUT);
	pinMode(STCP, OUTPUT);
	pinMode(SHCP, OUTPUT);
	
	digitalWrite(DS, 0);
	digitalWrite(STCP, 0);
	digitalWrite(SHCP, 0);
	return 0;
}

void clear()
{
	digitalWrite(DS, 0);
	digitalWrite(STCP, 0);
	digitalWrite(SHCP, 0);
	for(int i = 0; i < 8; i++)
	{
		pulse(SHCP);
	}
	pulse(STCP);
}

void automate(int arry[][8], int speed, int range)
{
	for(int i=0; i < range; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(arry[i][j])
			{
				pinHigh(DS);
				pulse(SHCP);
			}
			else
			{
				pinLow(DS);
				pulse(SHCP);
			}
		}
		pulse(STCP);
		delay(speed);
		clear();
	}
	// pulse(STCP);
	// delay(500);
}

int main(void)
{
	
	
	int bounce[][8] = {
		{1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0},
		{1,1,1,0,0,0,0,0},
		{1,1,1,1,0,0,0,0},
		{1,1,1,1,1,0,0,0},
		{1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,0,0},
		{1,1,1,1,1,0,0,0},
		{1,1,1,1,0,0,0,0},
		{1,1,1,0,0,0,0,0},
		{1,1,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0},
	};
			
	int dance[][8] = {
		{1,0,1,0,1,0,1,0},
		{0,1,0,1,0,1,0,1}
	};
	
	
	
	init();
	clear();
	for(int i = 0; i < 10; i++)
	{
		automate(dance, 250, 2);
	}

	for(int i = 0; i < 5; i++)
	{
		automate(bounce, 25, 14);
	}
	
	clear();
	
	

	return 0;
}

