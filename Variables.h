/*
 * Variables.h
 *
 *  Created on: 22 mars 2023
 *      Author: nathan
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <WS2812FX.h>


#define pin_LED_ACTIVITY				    13
#define pin_ARCADE_BUTTON				    7
#define pin_SLIDER_1					    A0
#define pin_SLIDER_2					    A1
#define pin_ROTARY_ENCODER_A		    	2
#define pin_ROTARY_ENCODER_B			    3
#define pin_LED_WS2812_CABIN		    	9
#define pin_LED_WS2812_CONTROL_PANEL		10
#define pin_LED_WS2812_BUTTON			    11

#define NB_WS2812_STRIP_CABIN			    200
#define NB_STRIP_CABIN					    4
#define NB_WS2812_CABIN_TOTAL			    (NB_WS2812_STRIP_CABIN * NB_STRIP_CABIN)

#define NB_WS2812_STRIP_CONTROL_PANEL	200
#define NB_STRIP_CONTROL_PANEL			  1
#define NB_WS2812_CONTROL_PANEL_TOTAL	(NB_WS2812_STRIP_CONTROL_PANEL * NB_STRIP_CONTROL_PANEL)

#define NB_WS2812_STRIP_BUTTON			  12
#define NB_STRIP_BUTTON					    1
#define NB_WS2812_BUTTON_TOTAL			  (NB_WS2812_STRIP_BUTTON * NB_STRIP_BUTTON)

#define FREQUENCE_TIMER               100                   				// (en Hz) fr�quence du timer principal, les taches sont ensuite effectu� tous les multiples
#define PERIODE_TIMER_PRINCIPAL				(1000 / FREQUENCE_TIMER)	// en ms
#define NB_PERIODE_1S									FREQUENCE_TIMER
#define NB_PERIODE_01S								(NB_PERIODE_1S / 10)

#define COM_END_CHAR                  "W"
#define COM_PERIODE_SEND_ECU_STATUS   (NB_PERIODE_01S)
#define COM_HEADING_ECU_STATUS        "ECU"

#define COM_HEADING_SFX                 "SFX"
#define COM_SFX_INST_STOP_NOW           "0"
#define COM_SFX_INST_STOP_FADE          "1"
#define COM_SFX_INST_START_OUNCE        "2"
#define COM_SFX_INST_START_LOOP         "3"

#define COM_SFX_CMD_CABINE_FIXE         "00"
#define COM_SFX_CMD_CABINE_CHENILLARD   "01"
#define COM_SFX_CMD_CABINE_BREATH       "02"

#define COM_SFX_CMD_BUTTON_FIXE         "10"
#define COM_SFX_CMD_BUTTON_CHENILLARD   "11"
#define COM_SFX_CMD_BUTTON_BREATH       "12"

typedef struct{
	uint8_t ui_Pin;
  boolean b_State;
  boolean b_State_Z1;  
}struct_DigitalInput;

typedef struct{
	uint8_t ui_Pin;
  uint16_t ui_Val;
  uint16_t ui_Val_Z1;
}struct_AnalogInput;

typedef struct{
  struct_DigitalInput DI_A;
  struct_DigitalInput DI_B;
  int16_t i_Counter;
  int16_t i_Counter_Z1;
}struct_RotatyEncoderInput;

typedef struct{
	WS2812FX* LED_Cabin;
	WS2812FX* LED_ControlPanel;
	WS2812FX* LED_Button;
	boolean b_StateActivityLed;
	uint8_t ui_IndexTask;
  String s_BufferIntput;
  boolean b_NewMsgSerial;
}struct_Variables;

typedef struct{
	struct_DigitalInput DI_ArcadeButton;
  struct_AnalogInput AI_Slider1;
  struct_AnalogInput AI_Slider2;
  struct_RotatyEncoderInput REI_RotaryEncoder;
}struct_IO;




#endif /* VARIABLES_H_ */
