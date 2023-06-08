#include "Arduino.h"
#include "Variables.h"
#include <elapsedMillis.h>

elapsedMillis Timer;
struct_Variables Variables;
struct_IO IO;

const uint8_t ui_PinsSelector[NB_POSITION_SELECTOR] = {pin_SELECTOR_1, pin_SELECTOR_2, pin_SELECTOR_3, pin_SELECTOR_4, pin_SELECTOR_5,
													pin_SELECTOR_6, pin_SELECTOR_7, pin_SELECTOR_8, pin_SELECTOR_9};

const uint16_t ui_SizeStripCabinTop[OffsetCabinTop_SIZE] = {NB_WS2812_STRIP_CABIN_TOP};
const uint16_t ui_SizeStripCabinBottom[OffsetCabinBottom_SIZE] = {NB_WS2812_STRIP_CABIN_BOTTOM};
const uint16_t ui_SizeStripControlPanel[OffsetControlPanel_SIZE] = {NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1,
											NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2,
											NB_WS2812_STRIP_CONTROL_PANEL_ENCODER,
											NB_WS2812_STRIP_CONTROL_PANEL_SELECTOR,
											NB_WS2812_STRIP_CONTROL_PANEL_INDICATOR_SELECTOR};
const uint16_t ui_SizeStripButton[OffsetButton_SIZE] = {NB_WS2812_STRIP_BUTTON};


//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(152000);
	delay(500);
	Init_IO();
	Init_SFX();

	Timer = 0;
}

// The loop function is called in an endless loop
void loop()
{
	uint8_t i, j, ui_IndexTemp;

	if (Timer >= PERIODE_TIMER_PRINCIPAL)			// toutes les 5ms
	{
		Timer = Timer - (PERIODE_TIMER_PRINCIPAL);
		//--------------------INPUT
		Read_INPUTS();
		ProcessingNewMsgSerial();

  		//--------------------LOOP

		//
		UpdateSFX();
		if((Variables.ui_IndexTask % ROTARY_ENCODER_PERIODE_UPDATE_SPEED) == 0){
			REI_Update(&IO.REI_RotaryEncoder);
		}

		//--------------------OUTPUT


		if((Variables.ui_IndexTask % COM_PERIODE_SEND_ECU_STATUS) == 0){
			COM_PackagingAndWritingStatus();
			//Serial.println(IO.REI_RotaryEncoder.i_Counter);
		}

//		Variables.LED_CabinTop.Strip->service();
//		Variables.LED_CabinBottom.Strip->service();
//		Variables.LED_ControlPanel.Strip->service();
//		Variables.LED_Button.Strip->service();



		if ((Variables.ui_IndexTask % 8)== 0){
			Variables.LED_CabinTop.Strip->show();
		}
		if ((Variables.ui_IndexTask % 8)== 2){
			Variables.LED_CabinBottom.Strip->show();
		}
		if ((Variables.ui_IndexTask % 8)== 4){
			Variables.LED_ControlPanel.Strip->show();
		}
		if ((Variables.ui_IndexTask % 8)== 6){
			Variables.LED_Button.Strip->show();
		}

		/*Variables.LED_CabinTop.Strip->show();
		Variables.LED_CabinBottom.Strip->show();
		Variables.LED_ControlPanel.Strip->show();
		Variables.LED_Button.Strip->show();*/

		Variables.ui_IndexTask = Variables.ui_IndexTask + 1;
		if (Variables.ui_IndexTask >= FREQUENCE_TIMER)
		{	Variables.ui_IndexTask = 0; }
		if ((Variables.ui_IndexTask % 20) == 0)
		{	Variables.b_StateActivityLed = !Variables.b_StateActivityLed;	}
		digitalWriteFast(pin_LED_ACTIVITY, (char)Variables.b_StateActivityLed);
	}




}
