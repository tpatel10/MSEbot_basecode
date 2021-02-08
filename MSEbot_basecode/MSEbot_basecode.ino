
//MSE 2202 
//Western Engineering base code
//2020 05 13 E J Porter


/*
  esp32                                           MSE-DuinoV2
  pins         description                        Brd Jumpers /Labels                                                                  User (Fill in chart with user PIN usage) 
  1             3v3                               PWR 3V3                                                                              3V3
  2             gnd                               GND                                                                                  GND
  3             GPIO15/AD2_3/T3/SD_CMD/           D15 (has connections in both 5V and 3V areas)                    
  4             GPIO2/AD2_2/T2/SD_D0              D2(has connections in both 5V and 3V areas)  /INDICATORLED ( On ESP32 board )        Heartbeat LED
  5             GPIO4/AD2_0/T0/SD_D1              D4(has connections in both 5V and 3V areas)                                          Left Motor, Channel A
  6             GPIO16/RX2                        Slide Switch S1b                                                                     IR Receiver
  7             GPIO17/TX2                        Slide Switch S2b                                                                     Left Encoder, Channel A
  8             GPIO5                             D5 (has connections in both 5V and 3V areas)                                         Left Encoder, Channel B
  9             GPIO18                            D18 (has connections in both 5V and 3V areas)                                        Left Motor, Channel B
  10            GPIO19/CTS0                       D19 (has connections in both 5V and 3V areas)                                        Right Motor, Channel A
  11            GPIO21                            D21/I2C_DA  
  12            GPIO3/RX0                         RX0
  13            GPIO1//TX0                        TX0
  14            GPIO22/RTS1                       D22/I2C_CLK
  15            GPIO23                            D23 (has connections in both 5V and 3V areas)  
  16            EN                                JP4 (Labeled - RST) for reseting ESP32
  17            GPI36/VP/AD1_0                    AD0                   
  18            GPI39/VN/AD1_3/                   AD3
  19            GPI34/AD1_6/                      AD6
  20            GPI35/AD1_7                       Potentiometer R2 / AD7
  21            GPIO32/AD1_4/T9                   Potentiometer R1 / AD4                                                               Pot 1 (R1)
  22            GPIO33/AD1_5/T8                   IMon/D33  monitor board current
  23            GPIO25/AD2_8/DAC1                 SK6812 Smart LEDs / D25                                                              Limit switch
  24            GPIO26/A2_9/DAC2                  Push Button PB2                                                                      PB2
  25            GPIO27/AD2_7/T7                   Push Button PB1                                                                      PB1
  26            GPOP14/AD2_6/T6/SD_CLK            Slide Switch S2a                                                                     Right Encoder, Channel A
  27            GPIO12/AD2_5/T5/SD_D2/            D12(has connections in both 5V and 3V areas)                                         Right Motor, Channel B
  28            GPIO13/AD2_4/T4/SD_D3/            Slide Switch S1a                                                                     Right Encoder, Channel B
  29            GND                               GND                                                                                  GND
  30            VIN                               PWR 5V t 7V                                                                          PWR 5V to 7V
*/


//Pin assignments
const int ciHeartbeatLED = 2;
const int ciPB1 = 27;     
const int ciPB2 = 26;      
const int ciPot1 = A4;    //GPIO 32  - when JP2 has jumper installed Analog pin AD4 is connected to Poteniometer R1
const int ciLimitSwitch = 26;
const int ciIRDetector = 16;
const int ciMotorLeftA = 4;
const int ciMotorLeftB = 18;
const int ciMotorRightA = 19;
const int ciMotorRightB = 12;
const int ciEncoderLeftA = 17;
const int ciEncoderLeftB = 5;
const int ciEncoderRightA = 14;
const int ciEncoderRightB = 13;


#include "0_Core_Zero.h"

#include <esp_task_wdt.h>

#include <Math.h>
#include "Motion.h";
#include "MyWEBserver.h"
#include "BreakPoint.h"
#include "WDT.h";

void loopWEBServerButtonresponce(void);


const int CR1_ciMainTimer =  1000;
const int CR1_ciHeartbeatInterval = 500;
const int CR1_ciMotorRunTime = 1000;
const long CR1_clDebounceDelay = 50;
const long CR1_clReadTimeout = 480;

unsigned char CR1_ucMainTimerCaseCore1;
 uint8_t CR1_ui8LimitSwitch;

uint8_t CR1_ui8IRDatum;
uint8_t CR1_ui8WheelSpeed;

uint32_t CR1_u32Now;
uint32_t CR1_u32Last;
uint32_t CR1_u32Temp;
uint32_t CR1_u32Avg;

unsigned long CR1_ulLastDebounceTime;

unsigned long CR1_ulMainTimerPrevious;
unsigned long CR1_ulMainTimerNow;

unsigned long CR1_ulMotorTimerPrevious;
unsigned long CR1_ulMotorTimerNow;
unsigned char ucMotorStateIndex = 0;

unsigned long CR1_ulHeartbeatTimerPrevious;
unsigned long CR1_ulHeartbeatTimerNow;

boolean btHeartbeat = true;
boolean btRun = false;
int iButtonState;
int iLastButtonState = HIGH;

void setup() {
   Serial.begin(115200);
    Serial2.begin(2400,SERIAL_8N1, ciIRDetector);

   
   Core_ZEROInit();

   WDT_EnableFastWatchDogCore1();
   WDT_ResetCore1();
   WDT_vfFastWDTWarningCore1[0] = 0;
   WDT_vfFastWDTWarningCore1[1] = 0;
   WDT_vfFastWDTWarningCore1[2] = 0;
   WDT_vfFastWDTWarningCore1[3] = 0;
   WDT_ResetCore1();
   WDT_vfFastWDTWarningCore1[4] = 0;
   WDT_vfFastWDTWarningCore1[5] = 0;
   WDT_vfFastWDTWarningCore1[6] = 0;
   WDT_vfFastWDTWarningCore1[7] = 0;
   WDT_ResetCore1();
   WDT_vfFastWDTWarningCore1[8] = 0;
   WDT_vfFastWDTWarningCore1[9] = 0;
   WDT_ResetCore1(); 

   setupMotion();
   pinMode(ciHeartbeatLED, OUTPUT);
   pinMode(ciPB1, INPUT_PULLUP);
   pinMode(ciLimitSwitch, INPUT_PULLUP);
}
void loop()
{

  //WSVR_BreakPoint(1);
  while (Serial2.available() > 0)
  {
    CR1_ui8IRDatum = Serial2.read();
    //Serial.println(CR1_ui8IRDatum,HEX);
  }
   
  int iButtonValue = digitalRead(ciPB1);       // read value of push button 1
  if (iButtonValue != iLastButtonState) {      // if value has changed
     CR1_ulLastDebounceTime = millis();        // reset the debouncing timer
  }

 if ((millis() - CR1_ulLastDebounceTime) > CR1_clDebounceDelay) {
    if (iButtonValue != iButtonState) {        // if the button state has changed
    iButtonState = iButtonValue;               // update current button state

     // only toggle the run condition if the new button state is LOW
     if (iButtonState == LOW)
     {
       ENC_ClearLeftOdometer();
       ENC_ClearRightOdometer();
       btRun = !btRun;
        Serial.println(btRun);
       // if stopping, reset motor states and stop motors
       if(!btRun)
       {
          ucMotorStateIndex = 0; 
          ucMotorState = 0;
          move(0);
       }
      
     }
   }
 }
 iLastButtonState = iButtonValue;             // store button state

 if(!digitalRead(ciLimitSwitch))
 {
  btRun = 0;//if limit switch is pressed stop bot
  ucMotorStateIndex = 0;
  ucMotorState = 0;
  move(0);
 }
 
 CR1_ulMainTimerNow = micros();
 if(CR1_ulMainTimerNow - CR1_ulMainTimerPrevious >= CR1_ciMainTimer)
 {
   WDT_ResetCore1(); 
   WDT_ucCaseIndexCore0 = CR0_ucMainTimerCaseCore0;
   
   CR1_ulMainTimerPrevious = CR1_ulMainTimerNow;
 
  switch(CR1_ucMainTimerCaseCore1)  //full switch run through is 1mS
  {
    //###############################################################################
    case 0: 
    {
      
      if(btRun)
      {
       CR1_ulMotorTimerNow = millis();
       if(CR1_ulMotorTimerNow - CR1_ulMotorTimerPrevious >= CR1_ciMotorRunTime)   
       {   
         CR1_ulMotorTimerPrevious = CR1_ulMotorTimerNow;
         switch(ucMotorStateIndex)
         {
          case 0:
          {
            ucMotorStateIndex = 1;
            ucMotorState = 0;
            move(0);
            break;
          }
           case 1:
          {
            ucMotorStateIndex = 2;
            ucMotorState = 0;
            move(0);
            break;
          }
           case 2:
          {
            ucMotorStateIndex = 3;
            ucMotorState = 1;   //forward
            move(CR1_ui8WheelSpeed);
            break;
          }
           case 3:
          {
            ucMotorStateIndex = 4;
            ucMotorState = 0;
            move(0);
            break;
          }
           case 4:
          {
            ucMotorStateIndex = 5;
            ucMotorState = 2;  //left
            move(0);
            break;
          }
           case 5:
          {
            ucMotorStateIndex = 6;
            ucMotorState = 0;
            move(0);
            break;
          }
           case 6:
          {
            ucMotorStateIndex = 7;
            ucMotorState = 3;  //right
            move(0);
            break;
          }
           case 7:
          {
            ucMotorStateIndex = 8;
            ucMotorState = 0;
            move(0);
            break;
          }
           case 8:
          {
            ucMotorStateIndex = 0;
            ucMotorState = 4;  //reverse
            move(CR1_ui8WheelSpeed);
            break;
          }
           
         }
        }
      }
      CR1_ucMainTimerCaseCore1 = 1;
      
      break;
    }
    //###############################################################################
    case 1: 
    {
   
      //read pot 1 for motor speeds 
      CR1_ui8WheelSpeed = analogRead(ciPot1) >> 4;
     
      
      CR1_ucMainTimerCaseCore1 = 2;
    
      break;
    }
    //###############################################################################
    case 2: 
    {
      //average the encoder tick times
      ENC_Averaging();

      CR1_ucMainTimerCaseCore1 = 3;
      break;
    }
    //###############################################################################
    case 3: 
    {
      
      
      CR1_ucMainTimerCaseCore1 = 4;
      break;
    }
    //###############################################################################
    case 4:   
    {
    
      CR1_ucMainTimerCaseCore1 = 5;
      break;
    }
    //###############################################################################
    case 5: 
    {
   
      CR1_ucMainTimerCaseCore1 = 6;
      break;
    }
    //###############################################################################
    case 6:
    {
  
    
      CR1_ucMainTimerCaseCore1 = 7;
      break;
    }
    //###############################################################################
    case 7: 
    {
   
      CR1_ucMainTimerCaseCore1 = 8;
      break;
    }
    //###############################################################################
    case 8: 
    {
    
      CR1_ucMainTimerCaseCore1 = 9;
      break;
    }
    //###############################################################################
    case 9: 
    {
  
      CR1_ucMainTimerCaseCore1 = 0;
      break;
    }

  }
 }

 // Heartbeat LED
 CR1_ulHeartbeatTimerNow = millis();
 if(CR1_ulHeartbeatTimerNow - CR1_ulHeartbeatTimerPrevious >= CR1_ciHeartbeatInterval)
 {
    CR1_ulHeartbeatTimerPrevious = CR1_ulHeartbeatTimerNow;
    btHeartbeat = !btHeartbeat;
    digitalWrite(ciHeartbeatLED, btHeartbeat);
 }
}
