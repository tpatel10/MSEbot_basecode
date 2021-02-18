/*
Western Engineering base code
2020 06 17
  
\Core 0 code


*/

#ifndef CORE_ZERO_H
#define CORE_ZERO_H 1

#include "Encoder.h"
#include "MyWEBserver.h"
#include "BreakPoint.h"
#include "WDT.h";

TaskHandle_t Core_Zero;

const int CR0_ciMainTimer =  1000;

unsigned char CR0_ucMainTimerCaseCore0;

unsigned int uiTestCounter;

uint32_t CR0_u32Now;
uint32_t CR0_u32Last;
uint32_t CR0_u32Temp;
uint32_t CR0_u32Avg;


  uint32_t ui32Countit;

unsigned long CR0_ulPreviousMicrosCore0;
unsigned long CR0_ulCurrentMicrosCore0;

void Core_ZeroCode( void * pvParameters );


void Core_ZEROInit()
{
   xTaskCreatePinnedToCore(
                    Core_ZeroCode,   /* Task function. */
                    "Core_Zero",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Core_Zero,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 
};

void CR0_CheckOperationTime(uint8_t ui8Start);

void Core_ZeroCode( void * pvParameters )
{
  Serial.print("Core - ");
  Serial.print(xPortGetCoreID());
  Serial.println("   running ");


  //Core 0 Setup
  //-------------------------------------------------------------------------------------------
   WSVR_BreakPointInit("DBON","CONT"); //Start contidions "HALT", "CONT", DBON", DBOF" 

   WSVR_setupWEbServer();
  
   delay(1000);

   
   WDT_EnableFastWatchDogCore0();
   
   WDT_ResetCore0();
   WDT_vfFastWDTWarningCore0[0] = 0;
   WDT_vfFastWDTWarningCore0[1] = 0;
   WDT_vfFastWDTWarningCore0[2] = 0;
   WDT_vfFastWDTWarningCore0[3] = 0;
   WDT_ResetCore0();
   WDT_vfFastWDTWarningCore0[4] = 0;
   WDT_vfFastWDTWarningCore0[5] = 0;
   WDT_vfFastWDTWarningCore0[6] = 0;
   WDT_vfFastWDTWarningCore0[7] = 0;
   WDT_ResetCore0();
   WDT_vfFastWDTWarningCore0[8] = 0;
   WDT_vfFastWDTWarningCore0[9] = 0;
   WDT_ResetCore0(); 
   
   ENC_Init();
  //loop function for core 0
  //-------------------------------------------------------------------------------------------
  for(;;)
  {

       
       CR0_ulCurrentMicrosCore0 = micros();
      if ((CR0_ulCurrentMicrosCore0 - CR0_ulPreviousMicrosCore0) >= CR0_ciMainTimer)
      {
        
        WDT_ResetCore0();
        WDT_ucCaseIndexCore0 = CR0_ucMainTimerCaseCore0;
        vTaskDelay(1);

    
        CR0_ulPreviousMicrosCore0 = CR0_ulCurrentMicrosCore0;
        
   
        switch(CR0_ucMainTimerCaseCore0)  //full switch run through is 1mS
        {
          //###############################################################################
          case 0: 
          {
           
            CR0_ucMainTimerCaseCore0 = 1;
            
            break;
          }
          //###############################################################################
          case 1: //
          {
         
           
             
            CR0_ucMainTimerCaseCore0 = 2;
          
            break;
          }
          //###############################################################################
          case 2: //web debugger control
          {
            //don't put anything else in this case, for now
          
            WSVR_Watch();
            webSocket.loop();
         
            CR0_ucMainTimerCaseCore0 = 3;
            break;
          }
          //###############################################################################
          case 3: 
          {
            uiTestCounter = uiTestCounter + 1;  //used as test can be removed
             //new break point function , use this function over the old WSVR_BreakPoint function
              //move it to where ever you need a break point can use 1 to 5 break points
              WSVR_BP(1);

              
            CR0_ucMainTimerCaseCore0 = 4;
            break;
          }
          //###############################################################################
          case 4:   ///warning exceed wdt time
          {
            WDT_CheckOperationTime();
            CR0_ucMainTimerCaseCore0 = 5;
            break;
          }
          //###############################################################################
          case 5: 
          {
         
                  
            CR0_ucMainTimerCaseCore0 = 6;
            break;
          }
          //###############################################################################
          case 6:
          {
            
          
            CR0_ucMainTimerCaseCore0 = 7;
            break;
          }
          //###############################################################################
          case 7: 
          {
            
            CR0_ucMainTimerCaseCore0 = 8;
            break;
          }
          //###############################################################################
          case 8: 
          {
           
            CR0_ucMainTimerCaseCore0 = 9;
            break;
          }
          //###############################################################################
          case 9: 
          {
                       
       
            CR0_ucMainTimerCaseCore0 = 0;
           
            break;
          }
      
        }
        
      }
  }
}




void CR0_CheckOperationTime(uint8_t ui8Start)
{
  //this function can be used to check how much time a fuction, chunk of code or library is using of processor time
  // to use put the CR0_CheckOperationTime(1) before the cod eot check and CR0_CheckOperationTime(0) after
  // it will then print to serial monitor the time between the functions
  // this function uses 63nS of processor time combine for (1) and (0) together
  
  float fTempTime;
  uint32_t ui32TempTime;
  if(ui8Start)
  {
    asm volatile("esync; rsr %0,ccount":"=a" (CR0_u32Last)); // @ 240mHz clock each tick is ~4nS 
  }
  else
  {
    asm volatile("esync; rsr %0,ccount":"=a" (CR0_u32Now));    
    //uses CR0_u32Last and CR0_u32Now and prints time
    ui32TempTime = CR0_u32Now - CR0_u32Last;
    fTempTime = (ui32TempTime * 3)/1000000;
    if(fTempTime != 0)
    {
     Serial.print(fTempTime);
     Serial.println(" mS");
    }
    else
    {
     fTempTime = (ui32TempTime * 3)/1000;
     if(fTempTime != 0)
     {
      Serial.print(fTempTime);
      Serial.println(" uS");
     }
     else
     {    
      fTempTime = ui32TempTime * 3;
      if(fTempTime != 0)
      {
       Serial.print(fTempTime);
       Serial.println(" nS");
      }
     }
    }
  }
}

#endif
