void Init_IO(){
  IO.DI_ArcadeButton.ui_Pin = pin_ARCADE_BUTTON;
  IO.AI_Slider1.ui_Pin = pin_SLIDER_1;
  IO.AI_Slider2.ui_Pin = pin_SLIDER_2;
  IO.REI_RotaryEncoder.DI_A.ui_Pin = pin_ROTARY_ENCODER_A;
  IO.REI_RotaryEncoder.DI_B.ui_Pin = pin_ROTARY_ENCODER_B;

	pinMode(pin_LED_ACTIVITY, OUTPUT);
	pinMode(IO.DI_ArcadeButton.ui_Pin, INPUT_PULLUP);
	pinMode(IO.AI_Slider1.ui_Pin, INPUT);
	pinMode(IO.AI_Slider2.ui_Pin, INPUT);
	pinMode(IO.REI_RotaryEncoder.DI_A.ui_Pin, INPUT);
	pinMode(IO.REI_RotaryEncoder.DI_B.ui_Pin, INPUT);
}

void Read_INPUTS()
{
  DI_ConditionedReading(&IO.DI_ArcadeButton);
  AI_ConditionedReading(&IO.AI_Slider1);
  AI_ConditionedReading(&IO.AI_Slider2);
  REI_ConditionedReading(&IO.REI_RotaryEncoder);
}

void DI_ConditionedReading(struct_DigitalInput* DI)
{
  DI->b_State_Z1 = DI->b_State;
  DI->b_State = digitalRead(DI->ui_Pin);
}

void AI_ConditionedReading(struct_AnalogInput* AI)
{
  AI->ui_Val_Z1 = AI->ui_Val;
  AI->ui_Val = analogRead(AI->ui_Pin);
}

void REI_ConditionedReading(struct_RotatyEncoderInput* REI)
{
  DI_ConditionedReading(&REI->DI_A);
  DI_ConditionedReading(&REI->DI_B);
  if(REI->DI_A.b_State != REI->DI_A.b_State_Z1) {
    REI->i_Counter_Z1 = REI->i_Counter;
    if(REI->DI_B.b_State != REI->DI_A.b_State)
    {
      REI->i_Counter++;
    } 
    else 
    {
      REI->i_Counter--;
    }
    Serial.print("Counter : ");
    Serial.println(REI->i_Counter);
  }
}