@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "D:\E3A\MIT\cocacola_espuma\labels.tmp" -fI -W+ie -C V2E -o "D:\E3A\MIT\cocacola_espuma\cocacola_espuma.hex" -d "D:\E3A\MIT\cocacola_espuma\cocacola_espuma.obj" -e "D:\E3A\MIT\cocacola_espuma\cocacola_espuma.eep" -m "D:\E3A\MIT\cocacola_espuma\cocacola_espuma.map" "D:\E3A\MIT\cocacola_espuma\cocacola_espuma.asm"
