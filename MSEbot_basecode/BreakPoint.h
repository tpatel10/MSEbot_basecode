/*
//Western Engineering base code 
March 21,2020
  
\Break point variable code setup

usage
#define WATCH_VARIABLE_1_NAME "put Variable name here ( in quotes), if charting is wanted then inside quotes put  ;LL1;###;UL1;####"  the ## is the upper and lower variable limits negative values ok 
                                                                                                        //only 6 charting variable allowed, ie LL1, UL1 to LL6, UL6
#define WATCH_VARIABLE_1_TYPE " put variable type ie unsigned int, boolean, float etc
#define WATCH_VARIABLE_1 Variable name , not in quotes, if the variable is not a global ie local a temporary global variable will have to be used and the local variable will have to be passed in code to this 
                                                                                        Temp variable before call to break point function. see under //temporary variable for local variable watching
 

*/

#ifndef BREAKPOINT_H
#define BREAKPOINT_H 1

//-----------------------------------------------------------
//Row 1
 
#define WATCH_VARIABLE_1_NAME "uiTestCounter"
#define WATCH_VARIABLE_1_TYPE unsigned int
#define WATCH_VARIABLE_1 uiTestCounter
// 
#define WATCH_VARIABLE_2_NAME "CR1_ui8WheelSpeed"
#define WATCH_VARIABLE_2_TYPE uint8_t
#define WATCH_VARIABLE_2 CR1_ui8WheelSpeed
////
#define WATCH_VARIABLE_3_NAME "ENC_vi32RightOdometer"
#define WATCH_VARIABLE_3_TYPE volatile int32_t
#define WATCH_VARIABLE_3 ENC_vi32RightOdometer
//
#define WATCH_VARIABLE_4_NAME "ENC_vi32LeftOdometer"
#define WATCH_VARIABLE_4_TYPE volatile int32_t
#define WATCH_VARIABLE_4 ENC_vi32LeftOdometer

////-----------------------------------------------------------
////Row 2

#define WATCH_VARIABLE_5_NAME "ENC_vui16LeftEncoderAMissed"
#define WATCH_VARIABLE_5_TYPE volatile uint16_t
#define WATCH_VARIABLE_5 ENC_vui16LeftEncoderAMissed
 
#define WATCH_VARIABLE_6_NAME "ENC_vui16LeftEncoderBMissed"
#define WATCH_VARIABLE_6_TYPE  volatile uint16_t
#define WATCH_VARIABLE_6 ENC_vui16LeftEncoderBMissed

#define WATCH_VARIABLE_7_NAME "ENC_vui16RightEncoderAMissed"
#define WATCH_VARIABLE_7_TYPE  volatile uint16_t
#define WATCH_VARIABLE_7 ENC_vui16RightEncoderAMissed

#define WATCH_VARIABLE_8_NAME "ENC_vui16RightEncoderBMissed"
#define WATCH_VARIABLE_8_TYPE  volatile uint16_t
#define WATCH_VARIABLE_8 ENC_vui16RightEncoderBMissed

////-----------------------------------------------------------
////Row 3


#define WATCH_VARIABLE_9_NAME "ENC_ui32LeftEncoderAveTime;LL1;8000;UL1;30000" //only 6 charting varable allowed, first number is minimun value ; 2nd is maximum value
#define WATCH_VARIABLE_9_TYPE uint32_t
#define WATCH_VARIABLE_9 ENC_ui32LeftEncoderAveTime
 
#define WATCH_VARIABLE_10_NAME "ENC_SpeedTest"
#define WATCH_VARIABLE_10_TYPE uint8_t
#define WATCH_VARIABLE_10 ENC_SpeedTest

#define WATCH_VARIABLE_11_NAME "ENC_ui32RightEncoderAveTime;LL2;8000;UL2;30000" //only 6 charting varable allowed, first number is minimun value ; 2nd is maximum value
#define WATCH_VARIABLE_11_TYPE uint32_t
#define WATCH_VARIABLE_11 ENC_ui32RightEncoderAveTime
//
#define WATCH_VARIABLE_12_NAME "ENC_SpeedTest"
#define WATCH_VARIABLE_12_TYPE uint8_t
#define WATCH_VARIABLE_12 ENC_SpeedTest

////-----------------------------------------------------------
////Row 4
#define WATCH_VARIABLE_13_NAME "ENC_uiAlpha"
#define WATCH_VARIABLE_13_TYPE uint16_t
#define WATCH_VARIABLE_13 ENC_uiAlpha
////
//
#define WATCH_VARIABLE_14_NAME "i32AverageDifference;LL3;-5000;UL3;5000" 
#define WATCH_VARIABLE_14_TYPE  int32_t
#define WATCH_VARIABLE_14 i32AverageDifference

#define WATCH_VARIABLE_15_NAME "ui8LeftWorkingSpeed"
#define WATCH_VARIABLE_15_TYPE uint8_t
#define WATCH_VARIABLE_15 ui8LeftWorkingSpeed
//

#define WATCH_VARIABLE_16_NAME "ui8RightWorkingSpeed"
#define WATCH_VARIABLE_16_TYPE uint8_t
#define WATCH_VARIABLE_16 ui8RightWorkingSpeed
// 
////-----------------------------------------------------------
////Row 5
//#define WATCH_VARIABLE_17_NAME ""
//#define WATCH_VARIABLE_17_TYPE unsigned int
//#define WATCH_VARIABLE_17 
//
//#define WATCH_VARIABLE_18_NAME ""
//#define WATCH_VARIABLE_18_TYPE unsigned int
//#define WATCH_VARIABLE_18 
//
//#define WATCH_VARIABLE_19_NAME ""
//#define WATCH_VARIABLE_19_TYPE unsigned int
//#define WATCH_VARIABLE_19 
//
//#define WATCH_VARIABLE_20_NAME "fTestCounter;LL2;-500;UL2;500"
//#define WATCH_VARIABLE_20_TYPE float
//#define WATCH_VARIABLE_20 fTestCounter


#include "MyWEBserver.h"

//temporary variable for local variable watching
 unsigned int BP_uiTempVariable1; 

 //extern variable you what to watch except locals 
#ifdef  WATCH_VARIABLE_1
extern WATCH_VARIABLE_1_TYPE WATCH_VARIABLE_1;
#endif
#ifdef  WATCH_VARIABLE_2
extern WATCH_VARIABLE_2_TYPE WATCH_VARIABLE_2;
#endif
#ifdef  WATCH_VARIABLE_3
extern WATCH_VARIABLE_3_TYPE WATCH_VARIABLE_3;
#endif
#ifdef  WATCH_VARIABLE_4
extern WATCH_VARIABLE_4_TYPE WATCH_VARIABLE_4;
#endif
#ifdef  WATCH_VARIABLE_5
extern WATCH_VARIABLE_5_TYPE WATCH_VARIABLE_5;
#endif
#ifdef  WATCH_VARIABLE_6
extern WATCH_VARIABLE_6_TYPE WATCH_VARIABLE_6;
#endif
#ifdef  WATCH_VARIABLE_7
extern WATCH_VARIABLE_7_TYPE WATCH_VARIABLE_7;
#endif
#ifdef  WATCH_VARIABLE_8
extern WATCH_VARIABLE_8_TYPE WATCH_VARIABLE_8;
#endif
#ifdef  WATCH_VARIABLE_9
extern WATCH_VARIABLE_9_TYPE WATCH_VARIABLE_9;
#endif
#ifdef  WATCH_VARIABLE_10
extern WATCH_VARIABLE_10_TYPE WATCH_VARIABLE_10;
#endif
#ifdef  WATCH_VARIABLE_11
extern WATCH_VARIABLE_11_TYPE WATCH_VARIABLE_11;
#endif
#ifdef  WATCH_VARIABLE_12
extern WATCH_VARIABLE_12_TYPE WATCH_VARIABLE_12;
#endif
#ifdef  WATCH_VARIABLE_13
extern WATCH_VARIABLE_13_TYPE WATCH_VARIABLE_13;
#endif
#ifdef  WATCH_VARIABLE_14
extern WATCH_VARIABLE_14_TYPE WATCH_VARIABLE_14;
#endif
#ifdef  WATCH_VARIABLE_15
extern WATCH_VARIABLE_15_TYPE WATCH_VARIABLE_15;
#endif
#ifdef  WATCH_VARIABLE_16
extern WATCH_VARIABLE_16_TYPE WATCH_VARIABLE_16;
#endif
#ifdef  WATCH_VARIABLE_17
extern WATCH_VARIABLE_17_TYPE WATCH_VARIABLE_17;
#endif
#ifdef  WATCH_VARIABLE_18
extern WATCH_VARIABLE_18_TYPE WATCH_VARIABLE_18;
#endif
#ifdef  WATCH_VARIABLE_19
extern WATCH_VARIABLE_19_TYPE WATCH_VARIABLE_19;
#endif
#ifdef  WATCH_VARIABLE_20
extern WATCH_VARIABLE_20_TYPE WATCH_VARIABLE_20;
#endif
  

void WSVR_BreakPointInit(String strDebug_OnOff, String strHaltContinous)
{
 // break point initialze variabel names
 // "BPN#;NN;variable name1;...variable name 5;  # is 1 to 5, string these togather to populate all 25 variable names. 
 //BNP numbers don't need to be in order but the names between the BNPs will fill the teh column right below this BNP number
 //initialize chart names and data scope size
 //BPCN;NN;LL1;variable 1 lower limit,UU1; variable 1 upper limit;LL2;variable 2 lower limit,UU2; variable 2 upper limit;+
 //LL3;variable 3 lower limit,UU3; variable 3 upper limit;LL4;variable 4 lower limit,UU4; variable 4 upper limit;LL5;variable 5 lower limit,UU5; variable 5 upper limit;+
 //variable name1;...variable name 6;

  
  if(strDebug_OnOff.equals("DBON"))
  {
     bWSVR_DebugOfOff = true;
  }
  else
  {
     bWSVR_DebugOfOff = false;
  }
 
  if(strHaltContinous.equals("HALT"))
  {
     bWSVR_HaltContinuous = false;
  }
  else
  {
     bWSVR_HaltContinuous = true;
  } 
  
 strWSVR_VariableNames = String(String("N#^") + ";" + strDebug_OnOff) + ";" + String(strHaltContinous) + ";" + String("BPN") + ";" + String("CC") + ";"

#ifdef WATCH_VARIABLE_1_NAME
                       + String("WV01") + ";" + String(WATCH_VARIABLE_1_NAME) + ";" 
#endif 
#ifdef WATCH_VARIABLE_2_NAME
                       + String("WV02") + ";" + String(WATCH_VARIABLE_2_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_3_NAME
                       + String("WV03") + ";" + String(WATCH_VARIABLE_3_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_4_NAME
                       + String("WV04") + ";" + String(WATCH_VARIABLE_4_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_5_NAME
                       + String("WV05") + ";" + String(WATCH_VARIABLE_5_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_6_NAME
                       + String("WV06") + ";" + String(WATCH_VARIABLE_6_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_7_NAME
                       + String("WV07") + ";" + String(WATCH_VARIABLE_7_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_8_NAME
                       + String("WV08") + ";" + String(WATCH_VARIABLE_8_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_9_NAME
                       + String("WV09") + ";" + String(WATCH_VARIABLE_9_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_10_NAME
                       + String("WV10") + ";" + String(WATCH_VARIABLE_10_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_11_NAME
                       + String("WV11") + ";" + String(WATCH_VARIABLE_11_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_12_NAME
                       + String("WV12") + ";" + String(WATCH_VARIABLE_12_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_13_NAME
                       + String("WV13") + ";" + String(WATCH_VARIABLE_13_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_14_NAME
                       + String("WV14") + ";" + String(WATCH_VARIABLE_14_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_15_NAME
                       + String("WV15") + ";" + String(WATCH_VARIABLE_15_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_16_NAME
                       + String("WV16") + ";" + String(WATCH_VARIABLE_16_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_17_NAME
                       + String("WV17") + ";" + String(WATCH_VARIABLE_17_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_18_NAME
                       + String("WV18") + ";" + String(WATCH_VARIABLE_18_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_19_NAME
                       + String("WV19") + ";" + String(WATCH_VARIABLE_19_NAME) + ";" 
#endif
#ifdef WATCH_VARIABLE_20_NAME
                       + String("WV20") + ";" + String(WATCH_VARIABLE_20_NAME) + ";" 
#endif                      
                       + String("END"); 

}        

void WSVR_BreakPoint(unsigned char ucBPindex)
{
  
  if(bWSVR_DebugOfOff)
  {
    
 strWSVR_VariableData = String("V#^") + ";" + String("CC") + ";"

#ifdef WATCH_VARIABLE_1_NAME
                       + String(WATCH_VARIABLE_1) + ";" 
#endif 
#ifdef WATCH_VARIABLE_2_NAME
                       + String(WATCH_VARIABLE_2) + ";" 
#endif
#ifdef WATCH_VARIABLE_3_NAME
                       + String(WATCH_VARIABLE_3) + ";" 
#endif
#ifdef WATCH_VARIABLE_4_NAME
                       + String(WATCH_VARIABLE_4) + ";" 
#endif
#ifdef WATCH_VARIABLE_5_NAME
                       + String(WATCH_VARIABLE_5) + ";" 
#endif
#ifdef WATCH_VARIABLE_6_NAME
                       + String(WATCH_VARIABLE_6) + ";" 
#endif
#ifdef WATCH_VARIABLE_7_NAME
                       + String(WATCH_VARIABLE_7) + ";" 
#endif
#ifdef WATCH_VARIABLE_8_NAME
                       + String(WATCH_VARIABLE_8) + ";" 
#endif
#ifdef WATCH_VARIABLE_9_NAME
                       + String(WATCH_VARIABLE_9) + ";" 
#endif
#ifdef WATCH_VARIABLE_10_NAME
                       + String(WATCH_VARIABLE_10) + ";" 
#endif
#ifdef WATCH_VARIABLE_11_NAME
                       + String(WATCH_VARIABLE_11) + ";" 
#endif
#ifdef WATCH_VARIABLE_12_NAME
                       + String(WATCH_VARIABLE_12) + ";" 
#endif
#ifdef WATCH_VARIABLE_13_NAME
                       + String(WATCH_VARIABLE_13) + ";" 
#endif
#ifdef WATCH_VARIABLE_14_NAME
                       + String(WATCH_VARIABLE_14) + ";" 
#endif
#ifdef WATCH_VARIABLE_15_NAME
                       + String(WATCH_VARIABLE_15) + ";" 
#endif
#ifdef WATCH_VARIABLE_16_NAME
                       + String(WATCH_VARIABLE_16) + ";" 
#endif
#ifdef WATCH_VARIABLE_17_NAME
                       + String(WATCH_VARIABLE_17) + ";" 
#endif
#ifdef WATCH_VARIABLE_18_NAME
                       + String(WATCH_VARIABLE_18) + ";" 
#endif
#ifdef WATCH_VARIABLE_19_NAME
                       + String(WATCH_VARIABLE_19) + ";" 
#endif
#ifdef WATCH_VARIABLE_20_NAME
                       + String(WATCH_VARIABLE_20) + ";" 
#endif                      
                       + String("END"); 
    
    if(bWSVR_HaltContinuous == false)
    {
     bWSVR_Halted = true;
       
     if((ucBPindex != 0)  && (ucBPindex < 5))
     { 
       strWSVR_VariableData.setCharAt(4,'H'); 
       strWSVR_VariableData.setCharAt(5,(0x30 + ucBPindex));
       while(bWSVR_Halted)
       {
         WSVR_SendMsg(strWSVR_VariableData);
         webSocket.loop();
        // WSVR_ButtonResponse();
         vTaskDelay(1);
         if((bWSVR_DebugOfOff == false) || (bWSVR_HaltContinuous))
         {
          break;
         }
       }
     }
            
     
     strWSVR_VariableData.setCharAt(4,'C');       
     strWSVR_VariableData.setCharAt(5,'C'); 
     
    }
    else
    {
      WSVR_SendMsg(strWSVR_VariableData);
     
    }
    
   
   }
  
}

void WSVR_BP(unsigned char ucBPindex)
{
  
  if(bWSVR_DebugOfOff)
  {
    
    if(bWSVR_HaltContinuous == false)
    {
     bWSVR_Halted = true;
       
     if((ucBPindex > 0)  && (ucBPindex <= 5))
     {
       strWSVR_VariableData  = String("B#^;6");
       strWSVR_VariableData.setCharAt(4,(0x30 + ucBPindex));
       WSVR_SendMsg(strWSVR_VariableData);
       while(bWSVR_Halted)
       {
         webSocket.loop();
       
         vTaskDelay(1);
         if((bWSVR_DebugOfOff == false) || (bWSVR_HaltContinuous))
         {
          break;
         }
       }
     }

    }
  
   }
  
}

void WSVR_Watch()
{
  bool btSendData = false;
  volatile static uint8_t vsui8WSVR_WatchIndex;
  
  if(bWSVR_DebugOfOff)
  {
     
   strWSVR_VariableData = String("W#^;");
   switch(vsui8WSVR_WatchIndex)
   {
    case 0:
    {
      vsui8WSVR_WatchIndex = 1;
      #ifdef WATCH_VARIABLE_1_NAME
        strWSVR_VariableData += ("0;" + String(WATCH_VARIABLE_1) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 1:
    {
      vsui8WSVR_WatchIndex = 2;
      #ifdef WATCH_VARIABLE_2_NAME
        strWSVR_VariableData +=  ("1;" + String(WATCH_VARIABLE_2) + ";");
        btSendData = true;
        break;
      #endif  
      
    }
    case 2:
    {
      vsui8WSVR_WatchIndex = 3;
      #ifdef WATCH_VARIABLE_3_NAME
        strWSVR_VariableData +=  ("2;" + String(WATCH_VARIABLE_3) + ";");
        btSendData = true;
        break;
      #endif  
      
    }
    case 3:
    {
      vsui8WSVR_WatchIndex = 4;
      #ifdef WATCH_VARIABLE_4_NAME
        strWSVR_VariableData += ("3;" + String(WATCH_VARIABLE_4) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 4:
    {
      vsui8WSVR_WatchIndex = 5;
      #ifdef WATCH_VARIABLE_5_NAME
        strWSVR_VariableData += ("4;" + String(WATCH_VARIABLE_5) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 5:
    {
      vsui8WSVR_WatchIndex  = 6;
      #ifdef WATCH_VARIABLE_6_NAME
        strWSVR_VariableData += ("5;" + String(WATCH_VARIABLE_6) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 6:
    {
      vsui8WSVR_WatchIndex = 7;
      #ifdef WATCH_VARIABLE_7_NAME
        strWSVR_VariableData += ("6;" + String(WATCH_VARIABLE_7) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 7:
    {
      vsui8WSVR_WatchIndex = 8;
      #ifdef WATCH_VARIABLE_8_NAME
        strWSVR_VariableData += ("7;" + String(WATCH_VARIABLE_8) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 8:
    {
      vsui8WSVR_WatchIndex = 9;
      #ifdef WATCH_VARIABLE_9_NAME
        strWSVR_VariableData += ("8;" + String(WATCH_VARIABLE_9) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 9:
    {
      vsui8WSVR_WatchIndex  = 10;
      #ifdef WATCH_VARIABLE_10_NAME
        strWSVR_VariableData += ("9;" + String(WATCH_VARIABLE_10) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 10:
    {
      vsui8WSVR_WatchIndex = 11;
      #ifdef WATCH_VARIABLE_11_NAME
        strWSVR_VariableData += ("10;" + String(WATCH_VARIABLE_11) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 11:
    {
      vsui8WSVR_WatchIndex = 12;
      #ifdef WATCH_VARIABLE_12_NAME
        strWSVR_VariableData += ("11;" +  String(WATCH_VARIABLE_12) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 12:
    {
      vsui8WSVR_WatchIndex = 13;
      #ifdef WATCH_VARIABLE_13_NAME
        strWSVR_VariableData += ("12;" + String(WATCH_VARIABLE_13) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 13:
    {
      vsui8WSVR_WatchIndex = 14;
      #ifdef WATCH_VARIABLE_14_NAME
        strWSVR_VariableData += ("13;" + String(WATCH_VARIABLE_14) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 14:
    {
      vsui8WSVR_WatchIndex = 15;
      #ifdef WATCH_VARIABLE_15_NAME
        strWSVR_VariableData += ("14;" + String(WATCH_VARIABLE_15) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 15:
    {
      vsui8WSVR_WatchIndex = 16;
      #ifdef WATCH_VARIABLE_16_NAME
        strWSVR_VariableData += ("15;" + String(WATCH_VARIABLE_16) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 16:
    {
      vsui8WSVR_WatchIndex = 17;
      #ifdef WATCH_VARIABLE_17_NAME
        strWSVR_VariableData += ("16;" + String(WATCH_VARIABLE_17) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 17:
    {
      vsui8WSVR_WatchIndex = 18;
      #ifdef WATCH_VARIABLE_18_NAME
        strWSVR_VariableData += ("17;" + String(WATCH_VARIABLE_18) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 18:
    {
      vsui8WSVR_WatchIndex = 19;
      #ifdef WATCH_VARIABLE_19_NAME
        strWSVR_VariableData += ("18;" + String(WATCH_VARIABLE_19) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    case 19:
    {
      vsui8WSVR_WatchIndex = 0;
      #ifdef WATCH_VARIABLE_20_NAME
        strWSVR_VariableData += ("19;" + String(WATCH_VARIABLE_20) + ";"); 
        btSendData = true;
        break;
      #endif  
      
    }
    default:
    {
      vsui8WSVR_WatchIndex = 0;
      btSendData = false;
      break;
    }
   }
   if(btSendData)
   {
    WSVR_SendMsg(strWSVR_VariableData);
   }
  }
 }








#endif
