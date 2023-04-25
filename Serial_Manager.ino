
//ECU:BBBB,CCCC,(-)DDDD,AW
//BBBB : selector 1 (0 to 1024)
//CCCC : selector 1 (0 to 1024)
//DDDD : rotaty encoder counter (0 to 1024)
//A : stat arcade button (0 or 1)
//W : end char

void COM_PackagingAndWritingStatus() {
  String s_Buffer = String(COM_HEADING_ECU_STATUS) + ":";
  s_Buffer += String(IO.AI_Slider1.ui_Val) + ",";
  s_Buffer += String(IO.AI_Slider2.ui_Val) + ",";
  s_Buffer += String(IO.REI_RotaryEncoder.i_Counter) + ",";
  s_Buffer += String(IO.DI_ArcadeButton.b_State) + String(COM_END_CHAR);
  //Serial.println(s_Buffer);     //todo pour test
}

void ProcessingNewMsgSerial(){
  if(Variables.b_NewMsgSerial == true)
  {
    String s_Heading, s_Int, s_Cmd, s_Data;
    uint8_t ui_Index;
    if(Variables.s_BufferIntput.indexOf(COM_END_CHAR) != -1) {
      ui_Index = 0;
      s_Heading = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(":"));
      ui_Index += s_Heading.length() + 1;
      s_Int = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(",", ui_Index));
      ui_Index += s_Int.length() + 1;
      s_Cmd = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(",", ui_Index));
      ui_Index += s_Cmd.length() + 1;
      s_Data = Variables.s_BufferIntput.substring(ui_Index, Variables.s_BufferIntput.indexOf(COM_END_CHAR));
      switch (s_Heading) {
        case COM_HEADING_SFX :
          NewRequestSFX(s_Int, s_Cmd, s_Data);          
        break;
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
    Serial.print(inChar);
    // add it to the inputString:
    Variables.s_BufferIntput += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      Variables.b_NewMsgSerial = true;
    }
    
  }
}