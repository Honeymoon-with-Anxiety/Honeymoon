@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\Users\admin\Documents\AVR - Pechar\USBasp\labels.tmp" -fI -W+ie -C V2 -o "C:\Users\admin\Documents\AVR - Pechar\USBasp\USBasp.hex" -d "C:\Users\admin\Documents\AVR - Pechar\USBasp\USBasp.obj" -e "C:\Users\admin\Documents\AVR - Pechar\USBasp\USBasp.eep" -m "C:\Users\admin\Documents\AVR - Pechar\USBasp\USBasp.map" "C:\Users\admin\Documents\AVR - Pechar\USBasp\USBasp.asm"
