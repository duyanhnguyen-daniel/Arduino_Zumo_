
// Syntax:     g,0,1,300,200,300,-1.2,-4.1,0.1,90
  //           go, Force, command, p,i,d,x,y,z,rotation
  //  
  //  
  //
  //
  //
  




#include <Wire.h>
#include <ZumoShield.h>


ZumoMotors motors;
int readByte = 0;
int defaulSpeed = 0;
String force = "";
String runFlag = "";
//double kp = 45, ki = 40, kd = 0;
float kp = 0, ki = 0, kd = 0;

float x_robot = 0, y_robot =0, z_robot=0, Rotation_robot = 0;
double PID_p = 0, PID_i = 0, PID_d = 0;
double PID_value ;
double PID_error;
double PID_errorTotal = 0 ;
double PID_errorTotal2 = 0;
int wL=0;
int wR=0;
int wL_new=0;
int wR_new=0;
double norm_v;
double angle;
double theta;
double theta_back;
double omega;
double currentForce;
double setOri;
double previousPID_error;
double previousPID_error2;
double PID_x_value;
double PID_y_value;

float currentTime ;
float previousTime ;
double correction;
String command = "";
float setForce = 1.8;
float elapsedTime = 0;
String p_parameter = "";
String i_parameter = "";
String d_parameter = "";
String x_parameter = "";
String y_parameter = "";
String z_parameter = "";
String Rotation_parameter = "";
String left = "";
String right="";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.flush();
   elapsedTime = 0.02;
  delay(6000);
 
}

void loop()
{
  char buf[100] = {'\0'};
  char* pos = NULL;
  if (Serial.available() > 0)
  {
    readByte = Serial.readBytesUntil('\n', buf, 100);
    String myString = String(buf);
    int firstDelimiter = myString.indexOf(",");
    runFlag = myString.substring(0, firstDelimiter);

    
  
    
    
  Serial.flush();
  if (runFlag == "g" )
  {
    int secondDelimiter = myString.indexOf(",", firstDelimiter + 1);
    left = myString.substring(firstDelimiter + 1, secondDelimiter);
    wL=atof( left.c_str());
    int thirdDelimiter = myString.indexOf(",", secondDelimiter + 1);
    right = myString.substring(secondDelimiter + 1, thirdDelimiter);
     wR=atof( right.c_str());
     int offset=65;
   if(wL >= 0) wL_new = wL + offset;
   else wL_new = wL - offset;
   if(wR >= 0) wR_new = wR +offset ;
   else wR_new = wR - offset;
    delay(2);
//wL_new= 100;
//wR_new=-100;
    
 motors.setLeftSpeed(wL_new);
  delay(2);
  motors.setRightSpeed(wR_new);  
  } else if (runFlag == "s")
    {
      stopMotor();
    }
    
    }
     delay(50);

  //----------------------------------------------------------------------------------
// g,0,1,5,0,0,-1,0,0,0


}
int stepp =5;
void stopMotor()
{
  while((wL!=0)&&(wR!=0))
  {
  if (abs(wL)>stepp) 
  {if (wL>0) wL=wL-stepp;
  else  wL=wL+stepp;
  }
  else wL=0;
  if (abs(wR)>stepp)
  {if (wR>0) wR=wR-stepp;
  else  wR=wR+stepp;
  }
  else wR=0;
 motors.setLeftSpeed(wL);
  delay(2);
  motors.setRightSpeed(wR);
  delay (150);
  }
  
}


void rorateLeft(int correction, float error)
{
  motors.setLeftSpeed(-190);
  motors.setRightSpeed(190);
  delay(2);
}


void rorateRight(int correction)
{
  motors.setLeftSpeed(190);
  motors.setRightSpeed(-190);
  delay(2);
}
