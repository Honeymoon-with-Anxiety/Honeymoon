@ECHO OFF
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\keybintdisp.map"
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\labels.tmp" -fI  -o "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\keybintdisp.hex" -d "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\keybintdisp.obj" -e "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\keybintdisp.eep" -m "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\keybin~1\keybintdisp.map" -W+ie   "F:\AVR\asm\KeyboardScanning\KeybIntDisp\KeybIntDisp.asm"
