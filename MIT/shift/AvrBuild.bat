@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "D:\E3A\MIT\shift\labels.tmp" -fI -W+ie -C V2E -o "D:\E3A\MIT\shift\shift.hex" -d "D:\E3A\MIT\shift\shift.obj" -e "D:\E3A\MIT\shift\shift.eep" -m "D:\E3A\MIT\shift\shift.map" "D:\E3A\MIT\shift\shift.asm"
