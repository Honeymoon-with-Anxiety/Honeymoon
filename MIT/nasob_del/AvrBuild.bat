@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "D:\E3A\MIT\nasob_del\labels.tmp" -fI -W+ie -C V2E -o "D:\E3A\MIT\nasob_del\nasob_del.hex" -d "D:\E3A\MIT\nasob_del\nasob_del.obj" -e "D:\E3A\MIT\nasob_del\nasob_del.eep" -m "D:\E3A\MIT\nasob_del\nasob_del.map" "D:\E3A\MIT\nasob_del\nasob_del.asm"
