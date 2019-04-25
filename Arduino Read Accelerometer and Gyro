// The acelerometre part based on MPU-6050 Short Example Sketch By Arduino User JohnChi
#include <SoftwareSerial.h>     //library needed to use SoftwareSeral funtion
#include<Wire.h>      //library needed to use Wire funtion to configure MPU
SoftwareSerial xbee(10,9); //xbee pins      //set pins 10 and 9 as serial comunication pins Tx and Rx
const int MPU_addr=0x68;      // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;      //Inicialize ·variable for the Accelerometer axes and another 3 for the Gyro
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);     //Access PWR_MGMT_1 register
  Wire.write(0);      // set to zero desable sleep mode (wakes up the MPU-6050)
  Wire.endTransmission(true);
  xbee.begin(9600);     //9600 bps serial comunication with the Xbee
}
void loop(){
  Wire.beginTransmission(MPU_addr);     //REALMETE NO SE QUE HACE MUY BIEN ESTA PARTE (es copiapega de la pagina de arduino sobre el MPU). ENTIENDO QUE ACCEDE A UN REGUISTRO LO GUARDA Y SE MUEVE
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)     //yo este no lo voy a usar pero no se borrarlo y hacer que salte de Az a Gx
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  xbee.print(" "); xbee.print(AcX);     //Transmiting the values to the serial communication with the Xbee
  xbee.print(" "); xbee.print(AcY);
  xbee.print(" "); xbee.print(AcZ);
  xbee.print(" "); xbee.print(GyX);
  xbee.print(" "); xbee.print(GyY);
  xbee.print(" "); xbee.println(GyZ); xbee.print("\n");

  delay(10);      //Delay to help the communication to be read correctly
}
