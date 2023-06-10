void DI_ConditionedReading(struct_DigitalInput* DI, boolean b_FastRead = false)
{
  DI->b_State_Z1 = DI->b_State;
  if(b_FastRead == true) {
	  DI->b_State = digitalReadFast(DI->ui_Pin);
  }
  else {
	  DI->b_State = digitalRead(DI->ui_Pin);
  }

}

void AI_ConditionedReading(struct_AnalogInput* AI)
{
  AI->ui_Val_Z1 = AI->ui_Val;
  AI->ui_Val = analogRead(AI->ui_Pin);
  if (AI->ui_Val < AI->ui_Min || AI->ui_Val > AI->ui_Max) {
	  AI->ui_Val = 0;
  }
  double range = AI->ui_Max - AI->ui_Min;
  double normalizedValue = AI->ui_Val - AI->ui_Min;
  AI->ui_Val = (normalizedValue / range) * 1000;
}

void DSI_ConditionedReading(struct_DigitalSelectorInput* DSI)
{
	uint8_t i;
	DSI->ui_Position_Z1 = DSI->ui_Position;
	for(i = 0; i < DSI->ui_NbPosition; i++){
		DSI->b_State_Z1[i] = DSI->b_State[i];
		DSI->b_State[i] = digitalRead(DSI->ui_Pin[i]);
		if(DSI->b_State[i] == false){
			DSI->ui_Position = i;
		}
	}
}

void Interrupt_A_REI_RotaryEncoder() {
	//DI_ConditionedReading(&IO.REI_RotaryEncoder.DI_A, true);
	IO.REI_RotaryEncoder.DI_A.b_State = digitalRead(IO.REI_RotaryEncoder.DI_A.ui_Pin);
	IO.REI_RotaryEncoder.i_Counter_Z1 = IO.REI_RotaryEncoder.i_Counter;
	if(IO.REI_RotaryEncoder.DI_A.b_State == HIGH) {
		if(IO.REI_RotaryEncoder.i_Counter < INT16_MAX){
			IO.REI_RotaryEncoder.i_Counter++;
		} else {
			IO.REI_RotaryEncoder.b_FlagLoop = true;
			IO.REI_RotaryEncoder.i_Counter = INT16_MIN + 1;
			IO.REI_RotaryEncoder.i_Counter_Z1 = INT16_MIN;
		}

	}else{
		if(IO.REI_RotaryEncoder.i_Counter > INT16_MIN){
			IO.REI_RotaryEncoder.i_Counter--;
		} else {
			IO.REI_RotaryEncoder.b_FlagLoop = true;
			IO.REI_RotaryEncoder.i_Counter = INT16_MAX - 1;
			IO.REI_RotaryEncoder.i_Counter_Z1 = INT16_MAX;
		}
	}
}

void Interrupt_B_REI_RotaryEncoder() {
	//DI_ConditionedReading(&IO.REI_RotaryEncoder.DI_B, true);
	IO.REI_RotaryEncoder.DI_B.b_State = digitalRead(IO.REI_RotaryEncoder.DI_B.ui_Pin);
	//IO.REI_RotaryEncoder.i_Counter_Z1 = IO.REI_RotaryEncoder.i_Counter;
	if(IO.REI_RotaryEncoder.DI_B.b_State == HIGH) {
		if(IO.REI_RotaryEncoder.i_Counter > INT16_MIN){
			IO.REI_RotaryEncoder.i_Counter--;
		} else {
			IO.REI_RotaryEncoder.b_FlagLoop = true;
			IO.REI_RotaryEncoder.i_Counter = INT16_MAX - 1;
			IO.REI_RotaryEncoder.i_Counter_Z1 = INT16_MAX;
		}
	}else{
		if(IO.REI_RotaryEncoder.i_Counter < INT16_MAX){
			IO.REI_RotaryEncoder.i_Counter++;
		} else {
			IO.REI_RotaryEncoder.b_FlagLoop = true;
			IO.REI_RotaryEncoder.i_Counter = INT16_MIN + 1;
			IO.REI_RotaryEncoder.i_Counter_Z1 = INT16_MIN;
		}
	}
}

void REI_ConditionedReading(struct_RotatyEncoderInput* REI)
{
	REI->i_Speed_Z1 = REI->i_Speed;
	if(REI->b_FlagLoop == true){
		REI->b_FlagLoop = false;
		if(REI->i_Counter_Z1 < REI->i_Counter){
			REI->i_Speed = (INT16_MIN - REI->i_Counter_Z1) - (INT16_MAX - REI->i_Counter) - 1;
		}
		else if(REI->i_Counter_Z1 > REI->i_Counter){
			REI->i_Speed = (REI->i_Counter - INT16_MIN) + (INT16_MAX - REI->i_Counter_Z1) + 1;
		}
	}
	else{
		REI->i_Speed = REI->i_Counter - REI->i_Counter_Z1;
	}
	REI->i_Counter_Z1 = REI->i_Counter;
}

void REI_Init(struct_RotatyEncoderInput* REI){
	attachInterrupt(REI->DI_B.ui_Pin, (void (*)())REI->Interrupt_A, RISING);					//Inversion de l'attache pour utilisé seulement 2 pins et pas une autre pour l'interupt
	attachInterrupt(REI->DI_A.ui_Pin, (void (*)())REI->Interrupt_B, RISING);
}

void REI_Update(struct_RotatyEncoderInput* REI){
	//todo check les calculs
	int32_t i_Temp = REI->i_Counter;
	if(REI->b_FlagLoop == true){
		REI->b_FlagLoop = false;
		if(i_Temp < 0){
			i_Temp += INT16_MAX;
		} else {
			i_Temp -= INT16_MAX;
		}
	}
	REI->i_Speed_Z1 = REI->i_Speed;
	REI->i_Speed = i_Temp - REI->i_Speed;
}

void DSI_Init(struct_DigitalSelectorInput* DSI, uint8_t ui_NbPosition, const uint8_t* ui_Pins, uint8_t ui_Type = INPUT){
	uint8_t i;
	DSI->ui_Pin = new uint8_t[ui_NbPosition];
	for(i = 0; i < ui_NbPosition; i++){
		DSI->ui_Pin[i] = ui_Pins[i];
		pinMode(DSI->ui_Pin[i], ui_Type);
	}
	DSI->b_State = new boolean[ui_NbPosition];
	DSI->b_State_Z1 = new boolean[ui_NbPosition];
	DSI->ui_Position = 0;
	DSI->ui_Position_Z1 = 0;
}

void Init_IO(){

	IO.DI_ArcadeButton.ui_Pin = pin_ARCADE_BUTTON;
	IO.DI_SLider1Button.ui_Pin = pin_SLIDER_1_BUTTON;
	IO.AI_Slider1.ui_Pin = pin_SLIDER_1;
	IO.AI_Slider2.ui_Pin = pin_SLIDER_2;
	IO.REI_RotaryEncoder.DI_A.ui_Pin = pin_ROTARY_ENCODER_A;
	IO.REI_RotaryEncoder.DI_B.ui_Pin = pin_ROTARY_ENCODER_B;
	IO.REI_RotaryEncoder.Interrupt_A = (void*)Interrupt_A_REI_RotaryEncoder;
	IO.REI_RotaryEncoder.Interrupt_B = (void*)Interrupt_B_REI_RotaryEncoder;
	IO.DSI_Selector.ui_NbPosition = NB_POSITION_SELECTOR;

	pinMode(pin_LED_ACTIVITY, OUTPUT);
	pinMode(IO.DI_ArcadeButton.ui_Pin, INPUT_PULLUP);
	pinMode(IO.DI_SLider1Button.ui_Pin, INPUT_PULLUP);
	pinMode(IO.AI_Slider1.ui_Pin, INPUT);
	pinMode(IO.AI_Slider2.ui_Pin, INPUT);
	pinMode(IO.REI_RotaryEncoder.DI_A.ui_Pin, INPUT_PULLUP);
	pinMode(IO.REI_RotaryEncoder.DI_B.ui_Pin, INPUT_PULLUP);
	REI_Init(&IO.REI_RotaryEncoder);
	DSI_Init(&IO.DSI_Selector, NB_POSITION_SELECTOR, ui_PinsSelector, INPUT_PULLUP);

}

void Read_INPUTS()
{
	DI_ConditionedReading(&IO.DI_ArcadeButton);
	DI_ConditionedReading(&IO.DI_SLider1Button);
	AI_ConditionedReading(&IO.AI_Slider1);
	AI_ConditionedReading(&IO.AI_Slider2);
	REI_ConditionedReading(&IO.REI_RotaryEncoder);
	DSI_ConditionedReading(&IO.DSI_Selector);
}


