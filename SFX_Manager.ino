#include <WS2812b_Effect.h>

unsigned int CharHexaToInt(String s_Data, uint8_t ui_Size = 0, uint8_t ui_StartIndex = 0);			//Here for compilation

void Init_SFX(){
	Init_StipLED(&Variables.LED_CabinTop, pin_LED_WS2812_CABIN_TOP, NB_WS2812_CABIN_TOP_TOTAL, ui_SizeStripCabinTop, OffsetCabinTop_SIZE);
	Init_StipLED(&Variables.LED_CabinBottom, pin_LED_WS2812_CABIN_BOTTOM, NB_WS2812_CABIN_BOTTOM_TOTAL, ui_SizeStripCabinBottom, OffsetCabinBottom_SIZE);
	Init_StipLED(&Variables.LED_ControlPanel, pin_LED_WS2812_CONTROL_PANEL, NB_WS2812_CONTROL_PANEL_TOTAL, ui_SizeStripControlPanel, OffsetControlPanel_SIZE);
	Init_StipLED(&Variables.LED_Button, pin_LED_WS2812_BUTTON, NB_WS2812_BUTTON_TOTAL, ui_SizeStripButton, OffsetButton_SIZE);
}

void Init_StipLED(struct_StripLED* StripLED, uint8_t ui_Pin, uint16_t ui_NbLed, const uint16_t* ui_SegmentsSize, uint8_t ui_NbSegment){
	uint8_t i, ui_StartTemp;
	StripLED->Strip = new WS2812FX(ui_NbLed, ui_Pin, NEO_GRB + NEO_KHZ800);
	StripLED->Strip->init();
	StripLED->ui_Size = ui_SegmentsSize;
	for(i = 0; i < ui_NbSegment; i++){
		StripLED->Effect[i] = new Effects(StripLED->Strip, i);
		if(i == 0){
			ui_StartTemp = 0;
		}
		else {
			ui_StartTemp += ui_SegmentsSize[i-1];
		}
		StripLED->Strip->setSegment(i, ui_StartTemp, ui_StartTemp + ui_SegmentsSize[i]);
	}
	StripLED->Strip->setColor(BLACK);
	StripLED->Strip->setBrightness(100);
	//StripLED->Strip->start();
}

void NewRequestSFX(uint8_t ui_Code, uint8_t ui_SousCode, uint8_t ui_Effect, String s_Data){
	struct_Var EffectTemp;
	EffectTemp.b_New = true;
	EffectTemp.ui_EffectIndex = ui_Effect;
	EffectTemp.ui_Speed = CharHexaToInt(s_Data, 2, 0) * NB_PERIODE_01S;
	EffectTemp.ColorPrincipal.H = CharHexaToInt(s_Data, 3, 2);
	EffectTemp.ColorPrincipal.S = CharHexaToInt(s_Data, 2, 5);
	EffectTemp.ColorPrincipal.L = CharHexaToInt(s_Data, 2, 7);
	EffectTemp.ColorSecond.H = CharHexaToInt(s_Data, 3, 9);
	EffectTemp.ColorSecond.S = CharHexaToInt(s_Data, 2, 12);
	EffectTemp.ColorSecond.L = CharHexaToInt(s_Data, 2, 14);

	Serial.println(EffectTemp.ColorPrincipal.H);
	Serial.println(EffectTemp.ColorPrincipal.S);
	Serial.println(EffectTemp.ColorPrincipal.L);
	Serial.println(EffectTemp.ColorSecond.H);
	Serial.println(EffectTemp.ColorSecond.S);
	Serial.println(EffectTemp.ColorSecond.L);

	//EffectTemp.ui_Luminosity = CharHexaToInt(s_Data, 2, 16);

	switch (ui_Code) {
	case ObjectWS2812_Button:
		if(ui_SousCode < OffsetButton_SIZE) {
			Variables.LED_Button.Effect[ui_SousCode]->VAR = EffectTemp;
		}
		break;
	case ObjectWS2812_ControlPanel:
		if(ui_SousCode < OffsetControlPanel_SIZE) {
			Variables.LED_ControlPanel.Effect[ui_SousCode]->VAR = EffectTemp;
		}
		break;
	case ObjectWS2812_CabinTop:
		if(ui_SousCode < OffsetCabinTop_SIZE) {
			Variables.LED_CabinTop.Effect[ui_SousCode]->VAR = EffectTemp;
		}
		break;
	case ObjectWS2812_CabinBottom:
		if(ui_SousCode < OffsetCabinBottom_SIZE) {
			Variables.LED_CabinBottom.Effect[ui_SousCode]->VAR = EffectTemp;
		}
		break;
	default:
		break;
	}

}

double calculatePercentageIntensity(double value, double min, double max, double intensityMax = 50) {
    if (value < min || value > max) {
        return 0.0;
    }

    double range = max - min;
    double normalizedValue = value - min;

    return (normalizedValue / range) * intensityMax;
}

void UpdateSFX(){
	uint32_t ui_ColorTemp;
	uint8_t i, j, ui_IndexTemp, ui_LumTemp = 0, ui_DeltaTemp, ui_PixelTemp = 0;
	ui_IndexTemp = 0;
	for(i = 0; i < OffsetButton_SIZE; i++){
		Variables.LED_Button.Effect[i]->update();
		if(i == 0){
			ui_IndexTemp = 0;
		} else {
			ui_IndexTemp = ui_SizeStripButton[i - 1];
		}
		for(j = 0; j < ui_SizeStripButton[i]; j++){
			Variables.LED_Button.Strip->setPixelColor(ui_IndexTemp + j, Variables.LED_Button.Effect[i]->VAR.ui_ColorActual);
		}
	}
	ui_IndexTemp = 0;
	for(uint8_t i = 0; i < OffsetControlPanel_SIZE; i++){
		Variables.LED_ControlPanel.Effect[i]->update();
		if(i == 0){
			ui_IndexTemp = 0;
		} else {
			ui_IndexTemp += ui_SizeStripControlPanel[i - 1];
		}
		for(j = 0; j < ui_SizeStripControlPanel[i]; j++){
			boolean b_Test = false;
			uint8_t ui_Temp, ui_IntensityTemp;
			uint32_t ui_ColorTemp = BLACK;
			switch (i) {					//for specifics conditions (indicator selector for example)
				case OffsetControlPanel_Slider1:
					ui_Temp = oppositeInRange((IO.AI_Slider1.ui_Val / (IO.AI_Slider1.ui_Max/NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1)), 0, NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1) - 1;
					ui_IntensityTemp = calculatePercentageIntensity(IO.AI_Slider1.ui_Val % (IO.AI_Slider1.ui_Max/NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1), 0, IO.AI_Slider1.ui_Max/NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.L);
					if(j < NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1 / 2){
						if(j < ui_Temp){
							ui_ColorTemp = BLACK;
						}
						else if(j == ui_Temp){
							ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->makeColor(Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.H, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.S, ui_IntensityTemp);
						}
						else{
							ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->VAR.ui_ColorActual;
						}
					}
					else {
						ui_IntensityTemp = oppositeInRange(ui_IntensityTemp, 0, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.L);
						if(j < ui_Temp){
							ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->VAR.ui_ColorActual;
						}
						else if(j == ui_Temp){
							ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->makeColor(Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.H, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.S, ui_IntensityTemp);
						}
						else{
							ui_ColorTemp = BLACK;
						}
					}

					if(((ui_Temp == NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1 / 2) || (ui_Temp == (NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_1 / 2) - 1)) && j == ui_Temp && ui_IntensityTemp <= 5){
						ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->makeColor(0, 0, 5);
					}

					break;
				case OffsetControlPanel_Slider2:
					ui_IntensityTemp = oppositeInRange(calculatePercentageIntensity(IO.AI_Slider2.ui_Val % (IO.AI_Slider2.ui_Max/NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2), 0, IO.AI_Slider2.ui_Max/NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.L), 0, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.L);
					ui_Temp = oppositeInRange((IO.AI_Slider2.ui_Val / (IO.AI_Slider2.ui_Max/NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2)), 0, NB_WS2812_STRIP_CONTROL_PANEL_SLIDER_2) - 1;
					if(j < ui_Temp){
						ui_ColorTemp =  Variables.LED_ControlPanel.Effect[i]->VAR.ui_ColorActual;
					}
					else if(j == ui_Temp) {
						ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->makeColor(Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.H, Variables.LED_ControlPanel.Effect[i]->VAR.ColorActual.S, ui_IntensityTemp);
					}
					else {
						ui_ColorTemp = BLACK;
					}
				break;

				case OffsetControlPanel_IndocatorSelector:
					if(j == IO.DSI_Selector.ui_Position){
						ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->VAR.ui_ColorActual;
					} else {
						ui_ColorTemp = BLACK;
					}
					break;
				default:
					ui_ColorTemp = Variables.LED_ControlPanel.Effect[i]->VAR.ui_ColorActual;
					break;
			}
			Variables.LED_ControlPanel.Strip->setPixelColor(ui_IndexTemp + j, ui_ColorTemp);
		}
	}
	ui_IndexTemp = 0;
	for(i = 0; i < OffsetCabinTop_SIZE; i++){
		Variables.LED_CabinTop.Effect[i]->update();
		if(i == 0){
			ui_IndexTemp = 0;
		} else {
			ui_IndexTemp = ui_SizeStripCabinTop[i - 1];
		}
		for(j = 0; j < ui_SizeStripCabinTop[i]; j++){
			Variables.LED_CabinTop.Strip->setPixelColor(ui_IndexTemp + j, Variables.LED_CabinTop.Effect[i]->VAR.ui_ColorActual);
		}
		//UpdateEffect(&Variables.LED_CabinTop.Effect[i]);
	}
	ui_IndexTemp = 0;
	for(i = 0; i < OffsetCabinBottom_SIZE; i++){
		Variables.LED_CabinBottom.Effect[i]->update();
		if(i == 0){
			ui_IndexTemp = 0;
		} else {
			ui_IndexTemp = ui_SizeStripCabinBottom[i - 1];
		}
		for(j = 0; j < ui_SizeStripCabinBottom[i]; j++){
			Variables.LED_CabinBottom.Strip->setPixelColor(ui_IndexTemp + j, Variables.LED_CabinBottom.Effect[i]->VAR.ui_ColorActual);
		}
		//UpdateEffect(&Variables.LED_CabinBottom.Effect[i]);
	}
}

int oppositeInRange(int number, int lowerBound, int upperBound) {
    if (number >= lowerBound && number <= upperBound) {
        int range = upperBound - lowerBound;
        return upperBound - number + lowerBound;
    }
    return number;
}
