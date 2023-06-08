#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2023-06-08 23:09:41

#include "Arduino.h"
#include <WS2812b_Effect.h>
#include "Arduino.h"
#include "Variables.h"
#include <elapsedMillis.h>

void AI_ConditionedReading(struct_AnalogInput* AI) ;
void DSI_ConditionedReading(struct_DigitalSelectorInput* DSI) ;
void Interrupt_A_REI_RotaryEncoder() ;
void Interrupt_B_REI_RotaryEncoder() ;
void REI_ConditionedReading(struct_RotatyEncoderInput* REI) ;
void REI_Init(struct_RotatyEncoderInput* REI);
void Init_IO();
void Read_INPUTS() ;
void Init_SFX();
void Init_StipLED(struct_StripLED* StripLED, uint8_t ui_Pin, uint16_t ui_NbLed, const uint16_t* ui_SegmentsSize, uint8_t ui_NbSegment);
void NewRequestSFX(uint8_t ui_Code, uint8_t ui_SousCode, uint8_t ui_Effect, String s_Data);
void UpdateSFX();
void COM_PackagingAndWritingStatus() ;
void ProcessingNewMsgSerial();
void serialEvent() ;
void setup() ;
void loop() ;

#include "cabin_control_panel.ino"

#include "IO_Manager.ino"
#include "SFX_Manager.ino"
#include "Serial_Manager.ino"

#endif
