unsigned int CharHexaToInt(String s_Data, uint8_t ui_Size = 0, uint8_t ui_StartIndex = 0);			//Here for compilation

//ECU:BBB,CCC,DDD,AW
//BBB : Valeur sélecteur 1 (0 à 255)
//CCC : Valeur sélecteur 2 (0 à 255)
//DDD : Valeur codeur (-125 à 125)
//A : Etat bouton arcade (0 ou 1)
//E : Etat bouton slider
//W : caractère de fin

void COM_PackagingAndWritingStatus() {
  String s_Buffer = String(COM_HEADING_ECU_STATUS) + ":";
  s_Buffer += String(IO.AI_Slider1.ui_Val) + ",";
  s_Buffer += String(IO.AI_Slider2.ui_Val) + ",";
  s_Buffer += String(IO.DSI_Selector.ui_Position) + ",";
  s_Buffer += String(IO.REI_RotaryEncoder.i_Speed) + ",";
  s_Buffer += String(IO.DI_ArcadeButton.b_State) + ",";
  s_Buffer += String(IO.DI_SLider1Button.b_State) + String(COM_END_CHAR);
	#ifdef SEND_ECU_STATUS
  Serial.println(s_Buffer);
	#endif
}

//SFX:A,E,B…BW
//A : Numéro de commande (cf. tableau commande)
//E : Numéro effet (cf. tableau effet)
//B…B : data, peut être vide
//W : caractère de fin

void ProcessingNewMsgSerial(){
  if(Variables.b_NewMsgSerial == true)
  {
    String s_Heading, s_Code, s_SousCode, s_Effect, s_Data;
    unsigned int ui_Code, ui_SousCode, ui_Effect;
    uint8_t ui_Index;
    if(Variables.s_BufferIntput.indexOf(COM_END_CHAR) != -1) {
      ui_Index = 0;
      s_Heading = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(":"));
      ui_Index += s_Heading.length() + 1;
      s_Code = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(",", ui_Index));
      ui_Code = CharHexaToInt(s_Code);
      ui_Index += s_Code.length() + 1;
      s_SousCode = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(",", ui_Index));
      ui_SousCode = CharHexaToInt(s_SousCode);
      ui_Index += s_SousCode.length() + 1;
      s_Effect = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(",", ui_Index));
      ui_Effect = CharHexaToInt(s_Effect);
      ui_Index += s_Effect.length() + 1;
      s_Data = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(COM_END_CHAR));
      if(s_Heading == COM_HEADING_SFX){
    	  NewRequestSFX(ui_Code, ui_SousCode, ui_Effect, s_Data);
      }
    }
    Variables.s_BufferIntput = "";
    Variables.b_NewMsgSerial = false;
  }

}

void serialEvent() {
  Variables.s_BufferIntput = "";
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    Variables.s_BufferIntput += inChar;
  }
  Variables.b_NewMsgSerial = true;
  Serial.print("New MSG : ");
  Serial.println(Variables.s_BufferIntput);
}

unsigned int CharHexaToInt(String s_Data, uint8_t ui_Size = 0, uint8_t ui_StartIndex = 0){
	int result = 0;
	uint8_t i;
	char c_Temp;

	if(ui_Size > 0){
		s_Data = s_Data.substring(ui_StartIndex, ui_StartIndex + ui_Size);
	}

	char * p;
	result = strtol( s_Data.c_str(), & p, 16 );
	return (unsigned int)result;
}
