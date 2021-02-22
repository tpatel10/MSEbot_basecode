/*
 Western Engineering base code
2020 05 13 E J Porter

 Dual Motor driver controller implement
  
 */

 #ifndef MOTION_H
  #define MOTION_H 1

//---------------------------------------------------------------------------

#include "BreakPoint.h"
#include "Encoder.h"

//#define DEBUGPRINT 1
#define ACCELERATIONRATE 1;



unsigned char ucMotion_Direction;
unsigned char ucMotion_Speed;
unsigned char ucPrevious_Speed;
unsigned char ucNow_Speed;

const uint8_t cui8StartingSpeed = 140;

uint8_t ui8LeftWorkingSpeed = cui8StartingSpeed;
uint8_t ui8RightWorkingSpeed = cui8StartingSpeed;

unsigned char ucMotorState = 0;

double dManualSpeed;
double dForwardSpeed;
double dReverseSpeed;
double dLeftSpeed;
double dRightSpeed;

void setupMotion (void)
{
	
  dManualSpeed = 0;
  dForwardSpeed = 250;  // max 255; min ~150 before motor stall
  dReverseSpeed = 250;
  dLeftSpeed = 170;
  dRightSpeed = 170;
  
  //setup PWM for motors
  ledcAttachPin(ciMotorLeftA, 1); // assign Motors pins to channels
  ledcAttachPin(ciMotorLeftB, 2);
  ledcAttachPin(ciMotorRightA, 3);
  ledcAttachPin(ciMotorRightB, 4);

  // Initialize channels 
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 20000, 8); // 20mS PWM, 8-bit resolution
  ledcSetup(2, 20000, 8);
  ledcSetup(3, 20000, 8);
  ledcSetup(4, 20000, 8);
 	
   ucMotion_Direction = 0;
   ucMotion_Speed = 0;
}


void ResetSpeeds()
{
  ui8LeftWorkingSpeed = cui8StartingSpeed;
  ui8RightWorkingSpeed = cui8StartingSpeed;

  
}

void MoveTo(uint8_t ui8Direction, uint8_t ui8LeftSpeed, uint8_t ui8RightSpeed)
{
    int  iPrintOnce;

    static uint8_t aui8SlowPulsing;  
   
     switch(ui8Direction)
      {
      
      
        //forward
        case 1:
        {
            
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
          
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
          
          break;
        }
        //Left
        case 2:
        {
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(1,0);
          ledcWrite(2,ui8LeftWorkingSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
        
          break;
        }
        //Right
        case 3:
        {
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(3,0);
          ledcWrite(4,ui8RightWorkingSpeed);
       
          break;
        }
        //Reverse
        case 4:
        {
             
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(1,0);
          ledcWrite(2,ui8LeftWorkingSpeed);
          ledcWrite(3,0);
          ledcWrite(4,ui8RightWorkingSpeed);
       
          break;
        }
       //forward slow
        case 5:
        {
           ui8LeftWorkingSpeed = ui8LeftSpeed;
           ui8RightWorkingSpeed = ui8RightSpeed;
           aui8SlowPulsing = aui8SlowPulsing + 1;
           if(aui8SlowPulsing > 5)
           {
            aui8SlowPulsing = 0; 
            ui8LeftWorkingSpeed = 250;
           ui8RightWorkingSpeed = 250;
           }
          
          
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
          
          break;
        }
        
      }
 }

void move(uint8_t ui8Speed)
{
    int  iPrintOnce;

     switch(ucMotorState)
      {
        //Stop, coast mode
        case 0:
        {
          ucPrevious_Speed = ui8Speed;
          ucNow_Speed = 0;
          //if 0 is put in both INs motors will coast stop 
          ledcWrite(2,0);
          ledcWrite(1,0);
          ledcWrite(4,0);
          ledcWrite(3,0);
          ENC_ClearMotorRunningFlags();
          ENC_ClearCheckOdoemterFlags();
        //ucWorkingButtonState = 9;
      #ifdef DEBUGPRINT  
          if(iPrintOnce != 0)
           {
            iPrintOnce = 0;
            Serial.print(F("stop-coasting"));
            Serial.println(ui8Speed);
          }
      #endif    
          break;
        }
      
        //Forward
        case 1:
        {
          //ui8speed = dForwardSpeed;
          ucPrevious_Speed = ucNow_Speed;
          ucNow_Speed = ui8Speed;
          ENC_SetMotorRunningFlags();
          ledcWrite(2,0);
          ledcWrite(1,ui8Speed);
          ledcWrite(4,0);
          ledcWrite(3,ui8Speed);
          
          //ucWorkingButtonState = 9;
        #ifdef DEBUGPRINT  
          if(iPrintOnce != 1)
           {
            iPrintOnce = 1;
            Serial.print(F("Forward "));
            Serial.println(ui8Speed);
           }
         #endif   
          break;
        }
        //Left
        case 2:
        {
          ui8Speed = dLeftSpeed;
          ucPrevious_Speed = ucNow_Speed;
          ucNow_Speed = ui8Speed;        
          ENC_SetMotorRunningFlags();
          ledcWrite(2,0);
          ledcWrite(1,ui8Speed);
          ledcWrite(3,0);
          ledcWrite(4,ui8Speed);
         //ucWorkingButtonState = 9;
         #ifdef DEBUGPRINT  
          if(iPrintOnce != 3)
           {
            iPrintOnce = 3;
            Serial.print(F("Left "));
            Serial.println(ui8Speed);
           }
         #endif 
          break;
        }
        //Right
        case 3:
        {
          ui8Speed = dRightSpeed;
          ucPrevious_Speed = ucNow_Speed;
          ucNow_Speed = ui8Speed;
          ENC_SetMotorRunningFlags();
          ledcWrite(1,0);
          ledcWrite(2,ui8Speed);
          ledcWrite(4,0);
          ledcWrite(3,ui8Speed);
          // ucWorkingButtonState = 9;
          #ifdef DEBUGPRINT  
          if(iPrintOnce != 4)
           {
            iPrintOnce = 4;
            Serial.print(F("Right "));
            Serial.println(ui8Speed);
           }
         #endif   
          break;
        }
        //Reverse
        case 4:
        {
          // ui8speed = dReverseSpeed;
          ucPrevious_Speed = ucNow_Speed;
          ucNow_Speed = ui8Speed;
          ENC_SetMotorRunningFlags();
          ledcWrite(1,0);
          ledcWrite(2,ui8Speed);
          ledcWrite(3,0);
          ledcWrite(4,ui8Speed);
         // ucWorkingButtonState = 9;
         #ifdef DEBUGPRINT  
          if(iPrintOnce != 2)
           {
            iPrintOnce = 2;
            Serial.print(F("Reverse "));
            Serial.println(ui8Speed);
           }
         #endif  
          break;
        }
        //Stop  braking mode
        case 5:
        {
          ucPrevious_Speed = ucNow_Speed;
          ucNow_Speed = 255;
          //if 255 is put in both INs brakes will be applied 
          ledcWrite(2,255);
          ledcWrite(1,255);
          ledcWrite(4,255);
          ledcWrite(3,255);
          ENC_ClearMotorRunningFlags();
          ENC_ClearCheckOdoemterFlags();
        //ucWorkingButtonState = 9;
      #ifdef DEBUGPRINT  
          if(iPrintOnce != 0)
           {
            iPrintOnce = 0;
            Serial.print(F("stop-braking"));
            Serial.println(ui8Speed);
          }
      #endif    
          break;
        }
      }
}


#endif
