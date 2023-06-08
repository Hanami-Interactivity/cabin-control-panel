/*
 * Variables.h
 *
 *  Created on: 22 mars 2023
 *      Author: nathan
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <WS2812FX.h>
#include <WS2812b_Effect.h>


#define pin_LED_ACTIVITY				    13
#define pin_ARCADE_BUTTON				    10
#define pin_SLIDER_1_BUTTON					12
#define pin_SLIDER_1					    25
#define pin_SLIDER_2					    27
#define pin_ROTARY_ENCODER_A		    	23
#define pin_ROTARY_ENCODER_B			    22
#define pin_LED_WS2812_CABIN_TOP	    	4
#define pin_LED_WS2812_CONTROL_PANEL		6
#define pin_LED_WS2812_BUTTON			    3
#define pin_LED_WS2812_CABIN_BOTTOM	    	7
#define pin_SELECTOR_1						41
#define pin_SELECTOR_2						40
#define pin_SELECTOR_3						39
#define pin_SELECTOR_4						38
#define pin_SELECTOR_5						37
#define pin_SELECTOR_6						36
#define pin_SELECTOR_7						35
#define pin_SELECTOR_8						34
#define pin_SELECTOR_9						33

#define NB_POSITION_SELECTOR				9

//#define REI_RotaryEncoder_A bitRead(PIND,pin_ROTARY_ENCODER_A)
//#define REI_RotaryEncoder_B bitRead(PIND,pin_ROTARY_ENCODER_B)

#define NB_WS2812_STRIP_CABIN_TOP		    200
#define NB_WS2812_CABIN_TOP_TOTAL			(NB_WS2812_STRIP_CABIN_TOP)

#define NB_WS2812_STRIP_CABIN_BOTTOM		    200
#define NB_WS2812_CABIN_BOTTOM_TOTAL			(NB_WS2812_STRIP_CABIN_BOTTOM)

#define NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1				6
#define NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2				6
#define NB_WS2812_STRIP_CONTROL_PANEL_ENCODER				8
#define NB_WS2812_STRIP_CONTROL_PANEL_SELECTOR				4
#define NB_WS2812_STRIP_CONTROL_PANEL_INDICATOR_SELECTOR	9
#define NB_WS2812_CONTROL_PANEL_TOTAL						(NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1 + NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2 + NB_WS2812_STRIP_CONTROL_PANEL_ENCODER + NB_WS2812_STRIP_CONTROL_PANEL_SELECTOR + NB_WS2812_STRIP_CONTROL_PANEL_INDICATOR_SELECTOR)

#define NB_WS2812_STRIP_BUTTON			  12
#define NB_WS2812_BUTTON_TOTAL			  (NB_WS2812_STRIP_BUTTON)

#define FREQUENCE_TIMER               100                   				// (en Hz) fr�quence du timer principal, les taches sont ensuite effectu� tous les multiples
#define PERIODE_TIMER_PRINCIPAL				(1000 / FREQUENCE_TIMER)	// en ms
#define NB_PERIODE_1S									FREQUENCE_TIMER
#define NB_PERIODE_01S								(NB_PERIODE_1S / 10)

#define COM_END_CHAR                  "W"
#define COM_PERIODE_SEND_ECU_STATUS   (NB_PERIODE_01S)
#define COM_HEADING_ECU_STATUS        "ECU"

#define COM_HEADING_SFX                 "SFX"

//#define COM_SFX_EFFECT_OFF				0x0
//#define COM_SFX_EFFECT_FIXE				0x1
//#define COM_SFX_EFFECT_BREATH			0x2
//#define COM_SFX_EFFECT_WAVE				0x3


//#define COM_SFX_CODE_ALL				0x0
//#define COM_SFX_CODE_BUTTON				0x1
//#define COM_SFX_CODE_SLIDER_1			0x2
//#define COM_SFX_CODE_SLIDER_2			0x3
//#define COM_SFX_CODE_ENCODER			0x4
//#define COM_SFX_CODE_SELECTOR			0x5
//#define COM_SFX_CODE_SELECTOR_INDICATOR	0x6
//#define COM_SFX_CODE_CABIN_ALL			0x7
//#define COM_SFX_CODE_CABIN_TOP			0x8
//#define COM_SFX_CODE_CABIN_BOTTOM		0x9

typedef enum {ObjectWS2812_Button, ObjectWS2812_ControlPanel, ObjectWS2812_CabinTop, ObjectWS2812_CabinBottom}enum_ObjectWS2812;

typedef enum {OffsetButton_Principal, OffsetButton_SIZE}enum_OffsetButton;
typedef enum {OffsetControlPanel_Slider1,
				OffsetControlPanel_Slider2,
				OffsetControlPanel_Encoder,
				OffsetControlPanel_Selector,
				OffsetControlPanel_IndocatorSelector,
				OffsetControlPanel_SIZE}enum_OffsetControlPanel;
typedef enum {OffsetCabinTop_Principal, OffsetCabinTop_SIZE}enum_OffsetCabinTop;
typedef enum {OffsetCabinBottom_Principal, OffsetCabinBottom_SIZE}enum_OffsetCabinBottom;



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
  int16_t i_Speed;
  int16_t i_Speed_Z1;
  boolean b_FlagLoop;			//To know if INT16_MAX or MIN for counter
  void * Interrupt_A = NULL;
  void * Interrupt_B = NULL;
}struct_RotatyEncoderInput;

typedef struct{
	uint8_t ui_NbPosition;
	uint8_t * ui_Pin = NULL;
	boolean * b_State = NULL;
	boolean * b_State_Z1 = NULL;
	uint8_t ui_Position;
	uint8_t ui_Position_Z1;
}struct_DigitalSelectorInput;
/*
typedef struct{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}struct_Color;

typedef struct{
	boolean b_InProcess;
	boolean b_New;							//True when a new effect it's start
	uint8_t ui_EffectIndex;
	uint8_t ui_Speed;
	struct_Color ColorPrincipal;
	struct_Color ColorSecond;
	uint32_t ui_ColorPrincipal;
	uint32_t ui_ColorSecond;
	uint32_t ui_ColorActual;
	int32_t i_Delta;
	uint8_t ui_Luminosity;
}struct_Effect;
*/
typedef struct{
	WS2812FX* Strip;
	const uint16_t* ui_Size = NULL;				//it's array for size of different, the order it's the same of physical strip
	Effects* Effect[15];
}struct_StripLED;

typedef struct{
	struct_StripLED LED_CabinTop;
	struct_StripLED LED_CabinBottom;
	struct_StripLED LED_ControlPanel;
	struct_StripLED LED_Button;
	boolean b_StateActivityLed;
	uint8_t ui_IndexTask;
  String s_BufferIntput;
  boolean b_NewMsgSerial;

  int16_t i_speed;
}struct_Variables;

typedef struct{
	struct_DigitalInput DI_ArcadeButton;
	struct_DigitalInput DI_SLider1Button;
  struct_AnalogInput AI_Slider1;
  struct_AnalogInput AI_Slider2;
  struct_RotatyEncoderInput REI_RotaryEncoder;
  struct_DigitalSelectorInput DSI_Selector;
}struct_IO;






#endif /* VARIABLES_H_ */
