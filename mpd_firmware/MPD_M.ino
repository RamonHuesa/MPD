
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

//    The acelerometre part based on MPU-6050 Short Example Sketch By Arduino User JohnChi

#include <SoftwareSerial.h>     //library needed to use SoftwareSeral funtion
#include<Wire.h>      //library needed to use Wire funtion to configure MPU
SoftwareSerial xbee(9,8); //xbee pins      //set pins 10 and 9 as serial comunication pins Tx and Rx
const int MPU_addr=0x68;      // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;      //Inicialize ·variable for the Accelerometer axes and another 3 for the Gyro
int stepCount=0;
int last_t=millis(), sPeed;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);     //Access PWR_MGMT_1 register
  Wire.write(0);      // set to zero desable sleep mode (wakes up the MPU-6050)
  Wire.endTransmission(true);
  xbee.begin(9600);     //9600 bps serial comunication with the Xbee
}
void loop(){
  Wire.beginTransmission(MPU_addr);     //ENTIENDO QUE ACCEDE A UN REGUISTRO LO GUARDA Y SE MUEVE
  Wire.write(0x3D);  // starting with register 0x3D (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers  
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)

  sPeed = millis()-last_t;
  if (AcY>18000)  {
        stepCount=stepCount+1;
        last_t=millis();
        
        xbee.print(" "); xbee.print(stepCount);
        xbee.print(" "); xbee.print(sPeed);
        xbee.print(" "); xbee.print(AcY);
        xbee.print("\n");        
        delay(350);      //Delay to help the communication to be read correctly 
  }

}
