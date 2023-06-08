/^(\.text|\.text\.progmem|\.text\.itcm|\.data|\.text\.csf)/ {arduino_size += $2 }
/^(\.usbdescriptortable|\.dmabuffers|\.usbbuffers|\.data|\.bss|\.noinit|\.text\.itcm|\.text\.itcm\.padding)/ {arduino_data += $2 }
/^(\.eeprom)/ {arduino_eeprom += $2 }
END { print "\nSketch uses " arduino_size " bytes (" int(arduino_size/10000*100+0.5)  "%)  of program storage space. Maximum is " 10000 " bytes.\nGlobal variables use "arduino_data" bytes ("int(arduino_data/10000*100+0.5)"%) of dynamic memory, leaving "10000-arduino_data" bytes for local variables. Maximum is "10000" bytes.\n"}