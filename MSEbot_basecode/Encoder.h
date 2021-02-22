/*
 Western Engineering base code
2021 02 04 E J Porter

 encoder implement
  
 */

 #ifndef ENCODER_H
  #define ENCODER_H 1

//---------------------------------------------------------------------------

void ENC_ClearMotorRunningFlags(void);
void ENC_SetMotorRunningFlags(void);
boolean ENC_ISMotorRunning(void);
void ENC_ClearCheckOdoemterFlags(void);
void ENC_SetCheckOdoemterFlags(void);
boolean ENC_ISCheckingOdometer(void);



#include "Motion.h";
#include "BreakPoint.h"

#define ALPHA 32768
#define ALPHAMIN 2048

 volatile boolean ENC_btLeftEncoderADataFlag;
 volatile boolean ENC_btLeftEncoderBDataFlag;
 volatile boolean ENC_btRightEncoderADataFlag;
 volatile boolean ENC_btRightEncoderBDataFlag;

 volatile boolean ENC_btLeftMotorRunningFlag;
 volatile boolean ENC_btRightMotorRunningFlag;

  volatile boolean ENC_btLeftMotorOdometerCheckFlag;
 volatile boolean ENC_btRightMotorOdometerCheckFlag;

 volatile uint16_t ENC_vui16LeftEncoderAMissed;
 volatile uint16_t ENC_vui16LeftEncoderBMissed;
 volatile uint16_t ENC_vui16RightEncoderAMissed;
 volatile uint16_t ENC_vui16RightEncoderBMissed;

 
 uint16_t ENC_uiAlpha = ALPHA;

 volatile int32_t ENC_vi32LeftEncoderARawTime = 0;
 volatile int32_t ENC_vi32LeftEncoderBRawTime = 0;
 volatile int32_t ENC_vi32RightEncoderARawTime = 0;
 volatile int32_t ENC_vi32RightEncoderBRawTime = 0;


 
 int32_t ENC_ui32LeftEncoderAAveTime = 0;
 int32_t ENC_ui32LeftEncoderBAveTime = 0;
 int32_t ENC_ui32RightEncoderAAveTime = 0;
 int32_t ENC_ui32RightEncoderBAveTime = 0;

 uint32_t ENC_ui32LeftEncoderAveTime = 0;
 uint32_t ENC_ui32RightEncoderAveTime = 0;

 volatile int32_t ENC_vi32LeftOdometer;
 volatile int32_t ENC_vi32RightOdometer;

 volatile int32_t ENC_vi32LeftOdometerCompare;
 volatile int32_t ENC_vi32RightOdometerCompare;

 volatile int32_t ENC_vsi32LastTimeLA;
 volatile int32_t ENC_vsi32ThisTimeLA;


 uint32_t ENC_ui32LeftEncoderAveTimeMaxA = 0;
 uint32_t ENC_ui32RightEncoderAveTimeMaxA =  0;
 uint32_t ENC_ui32LeftEncoderAveTimeMinA = 0xffffffff;
 uint32_t ENC_ui32RightEncoderAveTimeMinA = 0xffffffff;
 uint32_t ENC_ui32LeftEncoderAveTimeMaxB = 0;
 uint32_t ENC_ui32RightEncoderAveTimeMaxB = 0;
 uint32_t ENC_ui32LeftEncoderAveTimeMinB = 0xffffffff;
 uint32_t ENC_ui32RightEncoderAveTimeMinB = 0xfffffff;

 unsigned long ENC_ulMotorTimerNow;
 unsigned long ENC_ulMotorTimerPrevious;
 uint8_t ENC_SpeedTest = 0;
 uint8_t ui8CalIndex = 0;
 bool    btSpeedTestUD = false;


 
void ENC_SpeedTesting()
{
  
   
    static uint32_t sui32StoreLeftAverageForward[256];
    static uint32_t sui32StoreRightAverageForward[256];
    static uint32_t sui32StoreLeftAverageBackward[256];
    static uint32_t sui32StoreRightAverageBackward[256];
   // static uint16_t sui16StoreIndex;


    
   ENC_ulMotorTimerNow = millis();
  if(ENC_ulMotorTimerNow - ENC_ulMotorTimerPrevious >= 200)   
  {  
   ENC_ulMotorTimerPrevious = ENC_ulMotorTimerNow;
   switch(ui8CalIndex)
   {
    case 0:
    {
      
      
      
       if(btSpeedTestUD)
      {
        ENC_SpeedTest = ENC_SpeedTest + 1;
      }
      else
      {
        ENC_SpeedTest = ENC_SpeedTest - 1;
      }
      if(ENC_SpeedTest == 0)
      {
        if(btSpeedTestUD)
        {
          btSpeedTestUD = false;
          btRun = false;
          
          for(uint16_t ui16Loop = 0; ui16Loop <= 255;ui16Loop++)
            {
             Serial.print(ui16Loop);
             Serial.print(",");
             Serial.print(sui32StoreLeftAverageForward[ui16Loop]);
             Serial.print(",");
             Serial.print(sui32StoreLeftAverageBackward[ui16Loop]);
             Serial.print(",");
             Serial.print(sui32StoreRightAverageForward[ui16Loop]);
             Serial.print(",");
             Serial.println(sui32StoreRightAverageBackward[ui16Loop]);
             vTaskDelay(1);
             
            }
          
        }
        else
        {
          btSpeedTestUD = true;
        }
         
        
      }

    
      ucMotorState = 1;
      move(ENC_SpeedTest); 
   
      
      ui8CalIndex = 1;
      break;
    }
    case 1:
    {
     
       
        ENC_btLeftMotorRunningFlag = true;
        ENC_btRightMotorRunningFlag = true;
        ENC_ui32LeftEncoderAveTimeMaxA = 0;
        ENC_ui32RightEncoderAveTimeMaxA =  0;
        ENC_ui32LeftEncoderAveTimeMinA = 0xffffffff;
        ENC_ui32RightEncoderAveTimeMinA = 0xffffffff;
        ENC_ui32LeftEncoderAveTimeMaxB = 0;
        ENC_ui32RightEncoderAveTimeMaxB = 0;
        ENC_ui32LeftEncoderAveTimeMinB = 0xffffffff;
        ENC_ui32RightEncoderAveTimeMinB = 0xfffffff;
        ENC_ui32LeftEncoderAAveTime = 0;
        ENC_ui32LeftEncoderBAveTime = 0;
        ENC_ui32RightEncoderAAveTime = 0;
        ENC_ui32RightEncoderBAveTime = 0;
        ENC_ui32LeftEncoderAveTime = 0;
        ENC_ui32RightEncoderAveTime = 0;
   
      ui8CalIndex = 2;
      break;
    }
    case 2:
    {

      ui8CalIndex = 3;
      break;
    }
    case 3:
    {

      ui8CalIndex = 4;
      break;
    }
    case 4:
    {

      ui8CalIndex = 5;
      break;
    }
    case 5:
    {

      ui8CalIndex = 6;
      break;
    }
    case 6:
    {

      ui8CalIndex = 7;
      break;
    }
    case 7:
    {

      ui8CalIndex = 8;
      break;
    }
    case 8:
    {

      ui8CalIndex = 9;
      break;
    }
    case 9:
    {

      ui8CalIndex = 10;
      break;
    }
    case 10:
    {

        if((ENC_ui32LeftEncoderAveTime == 0)  && (ENC_ui32RightEncoderAveTime == 0) && (btSpeedTestUD == 0))
        {
          btSpeedTestUD = true;
        }

 
         if(btSpeedTestUD)
         {
           ENC_ClearMotorRunningFlags();
           sui32StoreLeftAverageBackward[ENC_SpeedTest]  = ENC_ui32LeftEncoderAveTime;
           sui32StoreRightAverageBackward[ENC_SpeedTest]  = ENC_ui32RightEncoderAveTime;
         }
         else
         {
           ENC_ClearMotorRunningFlags();
           sui32StoreLeftAverageForward[ENC_SpeedTest]  = ENC_ui32LeftEncoderAveTime;
           sui32StoreRightAverageForward[ENC_SpeedTest]  = ENC_ui32RightEncoderAveTime;
         }
        // sui16StoreIndex += 1;
        
      
      ui8CalIndex = 0;
      break;
    }
  
  }
 }
}



void ENC_ClearMotorRunningFlags()
{
  ENC_btLeftMotorRunningFlag = false;
  ENC_btRightMotorRunningFlag = false;
}

void ENC_SetMotorRunningFlags()
{
  ENC_btLeftMotorRunningFlag = true;
  ENC_btRightMotorRunningFlag = true;
}


boolean ENC_ISMotorRunning()
{
  if((ENC_btLeftMotorRunningFlag) && (ENC_btRightMotorRunningFlag))
  {
    return(1);
  }
  else
  {
     return(0);
  }
}

void ENC_ClearCheckOdoemterFlags()
{
  ENC_btLeftMotorOdometerCheckFlag = false;
  ENC_btRightMotorOdometerCheckFlag = false;
}

void ENC_SetCheckOdoemterFlags()
{
  ENC_btLeftMotorOdometerCheckFlag = true;
  ENC_btRightMotorOdometerCheckFlag = true;
}

boolean ENC_ISCheckingOdometer()
{
  if((ENC_btLeftMotorOdometerCheckFlag) && (ENC_btRightMotorOdometerCheckFlag))
  {
    return(1);
  }
  else
  {
     return(0);
  }
}



void ENC_SetDistance(int32_t i32LeftDistance, int32_t i32RightDistance)
{
  
   ENC_vi32LeftOdometerCompare = ENC_vi32LeftOdometer + i32LeftDistance;
   ENC_vi32RightOdometerCompare = ENC_vi32RightOdometer + i32RightDistance;
   ENC_btLeftMotorRunningFlag = true;
   ENC_btRightMotorRunningFlag = true;
   ENC_btRightMotorOdometerCheckFlag = true;
   ENC_btLeftMotorOdometerCheckFlag = true;
   ui8LeftWorkingSpeed = cui8StartingSpeed;
   ui8RightWorkingSpeed = cui8StartingSpeed;

}

//Encoder interrupt service routines - entered every change in in encoder pin H-> L and L ->H
//---------------------------------------------------------------------------------------------
void IRAM_ATTR ENC_isrLeftA()
{
   volatile static int32_t ENC_vsi32LastTime;
   volatile static int32_t ENC_vsi32ThisTime;
  
 
   // if the last interrupts data wasn't collected, count the miss
  if(ENC_btLeftEncoderADataFlag)
  {
    ENC_vui16LeftEncoderAMissed += 1;
    
  }
 
  //how much time elapsed since last interrupt
  
  asm volatile("esync; rsr %0,ccount":"=a" (ENC_vsi32ThisTime )); // @ 240mHz clock each tick is ~4nS 
  ENC_vi32LeftEncoderARawTime = ENC_vsi32ThisTime - ENC_vsi32LastTime;
  ENC_vsi32LastTime = ENC_vsi32ThisTime;
  ENC_btLeftEncoderADataFlag = true;

  //if both pins are high or low then count down otherwise wheel is going backwards count up
  //odometer reading
  if((digitalRead(ciEncoderLeftA) && digitalRead(ciEncoderLeftB)) || ((digitalRead(ciEncoderLeftA) == 0 && digitalRead(ciEncoderLeftB) == 0)))
  {
    ENC_vi32LeftOdometer -= 1;
  }
  else
  {
    ENC_vi32LeftOdometer += 1;
  }

  
  if(ENC_btLeftMotorRunningFlag)
  {
    if(ENC_btLeftMotorOdometerCheckFlag)
    {
      if(ENC_vi32LeftOdometer >= ENC_vi32LeftOdometerCompare)
      {
        ENC_btLeftMotorRunningFlag = false;
        ENC_btRightMotorRunningFlag = false;
        ENC_btRightMotorOdometerCheckFlag = false;
        ENC_btLeftMotorOdometerCheckFlag = false;
        digitalWrite(ciMotorLeftA,HIGH);
        digitalWrite(ciMotorLeftB,HIGH);
        digitalWrite(ciMotorRightA,HIGH);
        digitalWrite(ciMotorRightB,HIGH);
        ledcWrite(2,255);
        ledcWrite(1,255);  //stop with braking Left motor 
        ledcWrite(3,255);
        ledcWrite(4,255);  //stop with braking Right motor 
      }
    }
  }
  
}

void IRAM_ATTR ENC_isrLeftB()
{
  volatile static int32_t ENC_vsi32LastTime;
  volatile static int32_t ENC_vsi32ThisTime;
  
   // if the last interrupts data wasn't collected, count the miss
  if(ENC_btLeftEncoderBDataFlag)
  {
    ENC_vui16LeftEncoderBMissed += 1;
  }
  //how much time elapsed since last interrupt
  ENC_vsi32LastTime = ENC_vsi32ThisTime;
  asm volatile("esync; rsr %0,ccount":"=a" (ENC_vsi32ThisTime)); // @ 240mHz clock each tick is ~4nS 
  ENC_vi32LeftEncoderBRawTime = ENC_vsi32ThisTime - ENC_vsi32LastTime;
  ENC_btLeftEncoderBDataFlag = true;

  //Left Encoder B is opposite of A so if  both pins are high or low then count up otherwise wheel is going forwards count down
  //odometer reading
  if((digitalRead(ciEncoderLeftA) && digitalRead(ciEncoderLeftB)) || ((digitalRead(ciEncoderLeftA) == 0 && digitalRead(ciEncoderLeftB) == 0)))
  {
    ENC_vi32LeftOdometer += 1;
  }
  else
  {
    ENC_vi32LeftOdometer -= 1;
  }
  if(ENC_btLeftMotorRunningFlag)
  {
    if(ENC_btLeftMotorOdometerCheckFlag)
    {
      if(ENC_vi32LeftOdometer >= ENC_vi32LeftOdometerCompare)
      {
        ENC_btLeftMotorRunningFlag = false;
        ENC_btRightMotorRunningFlag = false;
        ENC_btRightMotorOdometerCheckFlag = false;
        ENC_btLeftMotorOdometerCheckFlag = false;
        digitalWrite(ciMotorLeftA,HIGH);
        digitalWrite(ciMotorLeftB,HIGH);
        digitalWrite(ciMotorRightA,HIGH);
        digitalWrite(ciMotorRightB,HIGH);
        ledcWrite(2,255);
        ledcWrite(1,255);  //stop with braking Left motor 
        ledcWrite(3,255);
        ledcWrite(4,255);  //stop with braking Right motor 
      }
    }
  }
}

void IRAM_ATTR ENC_isrRightA()
{
  volatile static int32_t ENC_vsi32LastTime;
  volatile static int32_t ENC_vsi32ThisTime;

   // if the last interrupts data wasn't collected, count the miss
  if(ENC_btRightEncoderADataFlag)
  {
    ENC_vui16RightEncoderAMissed += 1;
  }
  //how much time elapsed since last interrupt
  ENC_vsi32LastTime = ENC_vsi32ThisTime;
  asm volatile("esync; rsr %0,ccount":"=a" (ENC_vsi32ThisTime)); // @ 240mHz clock each tick is ~4nS 
  ENC_vi32RightEncoderARawTime = ENC_vsi32ThisTime - ENC_vsi32LastTime;
  ENC_btRightEncoderADataFlag = true;

  //Right Encoder A -  if both pins are high or low then count down otherwise wheel is going forwards count up
  //odometer reading
  if((digitalRead(ciEncoderRightA) && digitalRead(ciEncoderRightB)) || ((digitalRead(ciEncoderRightA) == 0 && digitalRead(ciEncoderRightB) == 0)))
  {
    ENC_vi32RightOdometer -= 1;
  }
  else
  {
    ENC_vi32RightOdometer += 1;
  }
  if(ENC_btRightMotorRunningFlag)
  {
    if(ENC_btRightMotorOdometerCheckFlag)
    {
      if(ENC_vi32RightOdometer >= ENC_vi32RightOdometerCompare)
      {
        ENC_btLeftMotorRunningFlag = false;
        ENC_btRightMotorRunningFlag = false;
        ENC_btRightMotorOdometerCheckFlag = false;
        ENC_btLeftMotorOdometerCheckFlag = false;
        digitalWrite(ciMotorLeftA,HIGH);
        digitalWrite(ciMotorLeftB,HIGH);
        digitalWrite(ciMotorRightA,HIGH);
        digitalWrite(ciMotorRightB,HIGH);
        ledcWrite(2,255);
        ledcWrite(1,255);  //stop with braking Left motor 
        ledcWrite(3,255);
        ledcWrite(4,255);  //stop with braking Right motor 
      }
    }
  }
}

void IRAM_ATTR ENC_isrRightB()
{
  volatile static int32_t ENC_vsi32LastTime;
  volatile static int32_t ENC_vsi32ThisTime;

  
  // if the last interrupts data wasn't collected, count the miss
  if(ENC_btRightEncoderBDataFlag)
  {
    ENC_vui16RightEncoderBMissed += 1;
  }
  //how much time elapsed since last interrupt
  ENC_vsi32LastTime = ENC_vsi32ThisTime;
  asm volatile("esync; rsr %0,ccount":"=a" (ENC_vsi32ThisTime)); // @ 240mHz clock each tick is ~4nS 
  ENC_vi32RightEncoderBRawTime = ENC_vsi32ThisTime - ENC_vsi32LastTime;
  ENC_btRightEncoderBDataFlag = true;

  //Right Encoder B is opposite of A so if both pins are high or low then count up otherwise wheel is going forwards count down
  //odometer reading
  if((digitalRead(ciEncoderRightA) && digitalRead(ciEncoderRightB)) || ((digitalRead(ciEncoderRightA) == 0 && digitalRead(ciEncoderRightB) == 0)))
  {
    ENC_vi32RightOdometer += 1;
  }
  else
  {
    ENC_vi32RightOdometer -= 1;
  }
  if(ENC_btRightMotorRunningFlag)
  {
    if(ENC_btRightMotorOdometerCheckFlag)
    {
      if(ENC_vi32RightOdometer >= ENC_vi32RightOdometerCompare)
      {
        ENC_btLeftMotorRunningFlag = false;
        ENC_btRightMotorRunningFlag = false;
        ENC_btRightMotorOdometerCheckFlag = false;
        ENC_btLeftMotorOdometerCheckFlag = false;
        digitalWrite(ciMotorLeftA,HIGH);
        digitalWrite(ciMotorLeftB,HIGH);
        digitalWrite(ciMotorRightA,HIGH);
        digitalWrite(ciMotorRightB,HIGH);
        ledcWrite(2,255);
        ledcWrite(1,255);  //stop with braking Left motor 
        ledcWrite(3,255);
        ledcWrite(4,255);  //stop with braking Right motor 
      }
    }
  }
}
//---------------------------------------------------------------------------------------------

void ENC_Init()
{
   //set pin modes
  pinMode(ciEncoderLeftA, INPUT_PULLUP);
  pinMode(ciEncoderLeftB, INPUT_PULLUP);
  pinMode(ciEncoderRightA, INPUT_PULLUP);
  pinMode(ciEncoderRightB, INPUT_PULLUP);

   // enable GPIO interrupt on change
  attachInterrupt(ciEncoderLeftA, ENC_isrLeftA, CHANGE);
  attachInterrupt(ciEncoderLeftB, ENC_isrLeftB, CHANGE);
  attachInterrupt(ciEncoderRightA, ENC_isrRightA, CHANGE);
  attachInterrupt(ciEncoderRightB, ENC_isrRightB, CHANGE);

  ENC_btLeftMotorRunningFlag = false;
  ENC_btRightMotorRunningFlag = false;
  ENC_btLeftMotorOdometerCheckFlag = false;
  ENC_btRightMotorOdometerCheckFlag = false;


  //check to see if calibration is in eeprom and retreive
  
  
}

void ENC_Disable()
{
   
   // disable GPIO interrupt on change
  detachInterrupt(ciEncoderLeftA);
  detachInterrupt(ciEncoderLeftB);
  detachInterrupt(ciEncoderRightA);
  detachInterrupt(ciEncoderRightB);
  
}

int32_t ENC_Averaging()
{
  static uint8_t sui8AlphaDelay;  
  int64_t vi64CalutatedAverageTime;
  
   //yn=yn−1⋅(1−α)+xn⋅α  exponentially weighted moving average IIR Filter 65535 = 1

   if(ENC_ISMotorRunning())
    {
      sui8AlphaDelay = sui8AlphaDelay + 1;
      if(sui8AlphaDelay > 3)
      {
        sui8AlphaDelay = 0;
        ENC_uiAlpha = ENC_uiAlpha >> 1;
      }
      
      if(ENC_uiAlpha < ALPHAMIN)
      {
        ENC_uiAlpha = ALPHAMIN;
      }
    }
    else
    {
      
      ENC_uiAlpha = ALPHA;
    }

   //Left Enoder A
   
  if(ENC_btLeftEncoderADataFlag)
   {
       
    ENC_btLeftEncoderADataFlag = false;

    if(ENC_ui32LeftEncoderAveTimeMaxA < ENC_vi32LeftEncoderARawTime)
    {
      ENC_ui32LeftEncoderAveTimeMaxA = ENC_vi32LeftEncoderARawTime;
    }
    if(ENC_ui32LeftEncoderAveTimeMinA > ENC_vi32LeftEncoderARawTime)
    {
      ENC_ui32LeftEncoderAveTimeMinA = ENC_vi32LeftEncoderARawTime;
    }
    
    if (ENC_uiAlpha == 65535 )
    {
      ENC_ui32LeftEncoderAAveTime = ENC_vi32LeftEncoderARawTime;
    }
    else
    {
      vi64CalutatedAverageTime = (int64_t)ENC_ui32LeftEncoderAAveTime * (65535 - ENC_uiAlpha) + ((int64_t)ENC_vi32LeftEncoderARawTime * ENC_uiAlpha);
      ENC_ui32LeftEncoderAAveTime = (int32_t)((vi64CalutatedAverageTime + 32768) / 65536);
   
    }
    if(ENC_ISMotorRunning())
      {
               
        ENC_ui32LeftEncoderAveTime = ((ENC_ui32LeftEncoderAAveTime + ENC_ui32LeftEncoderBAveTime) * 3)/1000;
       
      }
  }

     //Left Enoder B
  if(ENC_btLeftEncoderBDataFlag)
   {
    ENC_btLeftEncoderBDataFlag = false;

    if(ENC_ui32LeftEncoderAveTimeMaxB < ENC_vi32LeftEncoderBRawTime)
    {
      ENC_ui32LeftEncoderAveTimeMaxB = ENC_vi32LeftEncoderBRawTime;
    }
    if(ENC_ui32LeftEncoderAveTimeMinB > ENC_vi32LeftEncoderBRawTime)
    {
      ENC_ui32LeftEncoderAveTimeMinB = ENC_vi32LeftEncoderBRawTime;
    }
    
    if (ENC_uiAlpha == 65535 )
    {
      ENC_ui32LeftEncoderBAveTime = ENC_vi32LeftEncoderBRawTime;
    }
    else
    {
      vi64CalutatedAverageTime = (int64_t)ENC_ui32LeftEncoderBAveTime * (65535 - ENC_uiAlpha) + ((int64_t)ENC_vi32LeftEncoderBRawTime * ENC_uiAlpha);
      ENC_ui32LeftEncoderBAveTime = (int32_t)((vi64CalutatedAverageTime + 32768) / 65536);
      
    }
    if(ENC_ISMotorRunning())
      {
       
        ENC_ui32LeftEncoderAveTime = ((ENC_ui32LeftEncoderAAveTime + ENC_ui32LeftEncoderBAveTime) * 3)/1000;
        
      }
     
  }

  
    //Right Enoder A
  if(ENC_btRightEncoderADataFlag)
   {
    ENC_btRightEncoderADataFlag = false;
    if(ENC_ui32RightEncoderAveTimeMaxA < ENC_vi32RightEncoderARawTime)
    {
      ENC_ui32RightEncoderAveTimeMaxA = ENC_vi32RightEncoderARawTime;
    }
    if(ENC_ui32RightEncoderAveTimeMinA > ENC_vi32RightEncoderARawTime)
    {
      ENC_ui32RightEncoderAveTimeMinA = ENC_vi32RightEncoderARawTime;
    }
    
    if (ENC_uiAlpha == 65535 )
    {
      ENC_ui32RightEncoderAAveTime = ENC_vi32RightEncoderARawTime;
    }
    else
    {
      vi64CalutatedAverageTime = (int64_t)ENC_ui32RightEncoderAAveTime * (65535 - ENC_uiAlpha) + ((int64_t)ENC_vi32RightEncoderARawTime * ENC_uiAlpha);
      ENC_ui32RightEncoderAAveTime = (int32_t)((vi64CalutatedAverageTime + 32768) / 65536);
      
    }
    if(ENC_ISMotorRunning())
      {
        ENC_ui32RightEncoderAveTime = ((ENC_ui32RightEncoderAAveTime + ENC_ui32RightEncoderBAveTime) * 3)/1000;
      }
  }

     //Right Enoder B
  if(ENC_btRightEncoderBDataFlag)
   {
    ENC_btRightEncoderBDataFlag = false;
    if(ENC_ui32RightEncoderAveTimeMaxB < ENC_vi32RightEncoderBRawTime)
    {
      ENC_ui32RightEncoderAveTimeMaxB = ENC_vi32RightEncoderBRawTime;
    }
    if(ENC_ui32RightEncoderAveTimeMinB > ENC_vi32RightEncoderBRawTime)
    {
      ENC_ui32RightEncoderAveTimeMinB = ENC_vi32RightEncoderBRawTime;
    }
    
    if (ENC_uiAlpha == 65535 )
    {
      ENC_ui32RightEncoderBAveTime = ENC_vi32RightEncoderBRawTime;
    }
    else
    {
      vi64CalutatedAverageTime = (int64_t)ENC_ui32RightEncoderBAveTime * (65535 - ENC_uiAlpha) + ((int64_t)ENC_vi32RightEncoderBRawTime * ENC_uiAlpha);
      ENC_ui32RightEncoderBAveTime = (int32_t)((vi64CalutatedAverageTime + 32768) / 65536);
      
    }
    if(ENC_ISMotorRunning())
      {
        ENC_ui32RightEncoderAveTime = ((ENC_ui32RightEncoderAAveTime + ENC_ui32RightEncoderBAveTime) * 3)/1000;
      }
  }

  
}


void ENC_ClearLeftOdometer()
{
  ENC_vi32LeftOdometer = 0;
 
}


void ENC_ClearRightOdometer()
{
  ENC_vi32RightOdometer = 0;
}




#endif
