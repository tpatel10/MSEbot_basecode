/*
 Western Engineering base code
2020 05 13 E J Porter

 Dual Motor driver controller implement
  
 */

 #ifndef MOTION_H
  #define MOTION_H 1

//---------------------------------------------------------------------------

unsigned char ucMotion_Direction;
unsigned char ucMotion_Speed;


unsigned char ucMotorState = 0;

double dManualSpeed;
double dForwardSpeed;
double dReverseSpeed;
double dLeftSpeed;
double dRightSpeed;




void setupMotion (void)
{
	
  dManualSpeed = 0;
  dForwardSpeed = 255;
  dReverseSpeed = 250;
  dLeftSpeed = 200;
  dRightSpeed = 200
  ;
  
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
  //uiMotorSpeedLeft = uiStop;
  //uiMotorSpeedRight = uiStop;
  //uiMotorCommandLeft = uiStop;
  //uiMotorCommandRight = uiStop;

  
	
   ucMotion_Direction = 0;
   ucMotion_Speed = 0;

	
}


void move(uint8_t ui8speed)
{
    int  iPrintOnce;
      
   
     switch(ucMotorState)
      {
        //Stop
        case 0:
        {
          ledcWrite(2,0);
          ledcWrite(1,0);
          ledcWrite(4,0);
          ledcWrite(3,0);
        //ucWorkingButtonState = 9;
          if(iPrintOnce != 0)
           {
            iPrintOnce = 0;
            Serial.print(F("stop "));
            Serial.println(ui8speed);
          }
          break;
        }
      
        //forwards
        case 1:
        {
          //ui8speed = dForwardSpeed;
          ledcWrite(2,0);
          ledcWrite(1,ui8speed);
          ledcWrite(4,0);
          ledcWrite(3,ui8speed);
          //ucWorkingButtonState = 9;
          if(iPrintOnce != 1)
           {
            iPrintOnce = 1;
            Serial.print(F("Forward "));
            Serial.println(ui8speed);
           }
          break;
        }
        //Left
        case 2:
        {
          ui8speed = dLeftSpeed;
          ledcWrite(2,0);
          ledcWrite(1,ui8speed);
          ledcWrite(3,0);
          ledcWrite(4,ui8speed);
         //ucWorkingButtonState = 9;
          if(iPrintOnce != 3)
           {
            iPrintOnce = 3;
            Serial.print(F("Left "));
            Serial.println(ui8speed);
           }
        
          break;
        }
        //Right
        case 3:
        {
          ui8speed = dRightSpeed;
          ledcWrite(1,0);
          ledcWrite(2,ui8speed);
          ledcWrite(4,0);
          ledcWrite(3,ui8speed);
          // ucWorkingButtonState = 9;
          if(iPrintOnce != 4)
           {
            iPrintOnce = 4;
            Serial.print(F("Right "));
            Serial.println(ui8speed);
           }
          break;
        }
        //Reverse
        case 4:
        {
          // ui8speed = dReverseSpeed;
          ledcWrite(1,0);
          ledcWrite(2,ui8speed);
          ledcWrite(3,0);
          ledcWrite(4,ui8speed);
         // ucWorkingButtonState = 9;
          if(iPrintOnce != 2)
           {
            iPrintOnce = 2;
            Serial.print(F("Reverse "));
            Serial.println(ui8speed);
           }
          break;
        }
        
      }
       
       
        
   
 
}


#endif
