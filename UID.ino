//  <OLED display. Display data received from the MPU via Xbee.>
//    Copyright (C) <2019>  <Ramón Huesa Amat>
//
//    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, see http://www.gnu.org/licenses
//    or write to the Free Software Foundation,Inc., 51 Franklin Street,
//    Fifth Floor, Boston, MA 02110-1301  USA


#include <Wire.h>       // libraries needed to use OLED
#include <Adafruit_SSD1306.h>    
#include <Adafruit_GFX.h>

#include <SoftwareSerial.h>     // library needed to use Xbee

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_ADDR   0x3D     // Address 0x3D for 128x64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

 SoftwareSerial xbee(10,9);      // set pins 10 and 9 as serial comunication pins Tx and Rx

  int iniMPDTime, sesionAverage, stoppedTime,currentMillis, MPDTime;
  int stepCount = 0;
  int t = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); // initialize and clear display
  display.clearDisplay();
  display.display();
     
  xbee.begin(9600);     //9600 bps serial comunication with the Xbee

// display inicializatin text
  display.setTextSize(1);    // Normal 1:1 pixel scale
  display.setTextColor(WHITE);    // Draw white text
  display.setCursor(0,20);    // Start at 20 pixels from the top and left
  display.print("Welcome to MPD prototype");
  display.setCursor(0,40);        // Start at 40 pixels from the top and left
  display.print("by Ramon Huesa Amat");

  display.display();    // update display with all of the above graphics
}

void loop() {
  
stepCount = xbee.read();
t = xbee.read();

if ((stepCount==0)&&(t==0)) {
iniMPDTime=t;
}

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("Step Count");
  display.setCursor(0,40);
  display.print(stepCount);


  // update display with all of the above graphics
  display.display();

// Extra usefull data for the user (not displayed yet)
currentMillis=millis();
MPDTime = currentMillis+iniMPDTime;
sesionAverage = 1000*stepCount/currentMillis;
stoppedTime= MPDTime-t;

}
