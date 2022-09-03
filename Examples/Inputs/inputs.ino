#include <P1AM.h>
#include <P1_HSC.h>

/******************************************************************************************
 * Automationdirect.com
 * This version of ProductivityBlocks supports P1AM-100 Library V1.0.3
 * To download this library, please visit https://github.com/facts-engineering/P1AM
 * For information on the P1AM-100 hardware, please visit https://www.automationdirect.com
 ******************************************************************************************/

void __proBlocksDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

bool _PBVAR_1_Input_1= false ;
bool _PBVAR_2_Input_16= false ;
boolean __proBlocksDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


unsigned long _PBVAR_3_Slot_1_Inputs = 0UL ;

void setup()
{
  while(!P1.init())
  {
  }

  Serial.begin(115200, SERIAL_8N1);
  P1.writeDiscrete(0, 2, 0);
  __proBlocksDigitalWrite(32, LOW);
  _PBVAR_1_Input_1 = LOW ;
  _PBVAR_2_Input_16 = LOW ;

}

void loop()
{
  if (__proBlocksDigitalRead(31))
  {

    //Store the Status of the Inputs into a Variable
    _PBVAR_3_Slot_1_Inputs = P1.readDiscrete(1, 0) ;

    //Test to see if Input 1 was on at the start of the scan and only execute command once
    if (( ( ( (_PBVAR_3_Slot_1_Inputs & 0x01UL) ) > ( 0 ) ) && _PBVAR_1_Input_1 ))
    {
      Serial.println("Input 1 is On");
      _PBVAR_1_Input_1 = LOW ;
    }
    if (( ( ( (_PBVAR_3_Slot_1_Inputs & 0x01UL) ) == ( 0 ) ) && !( _PBVAR_1_Input_1 ) ))
    {
      Serial.println("Input 1 is Off");
      _PBVAR_1_Input_1 = HIGH ;
    }

    //Test to see if Input 16 was on at the start of the scan and only execute command once
    if (( ( ( (_PBVAR_3_Slot_1_Inputs & 0x8000UL) ) > ( 0 ) ) && _PBVAR_2_Input_16 ))
    {
      Serial.println("Input 16 is On");
      _PBVAR_2_Input_16 = LOW ;
    }
    if (( ( ( (_PBVAR_3_Slot_1_Inputs & 0x8000UL) ) == ( 0 ) ) && !( _PBVAR_2_Input_16 ) ))
    {
      Serial.println("Input 16 is Off");
      _PBVAR_2_Input_16 = HIGH ;
    }
  }
}
