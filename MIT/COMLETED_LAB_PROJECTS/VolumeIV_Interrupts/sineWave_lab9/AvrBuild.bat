@ECHO OFF
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\sinewave.map"
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\labels.tmp" -fI  -o "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\sinewave.hex" -d "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\sinewave.obj" -e "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\sinewave.eep" -m "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\sinewa~1\sinewave.map" -W+ie   "C:\Documents and Settings\dd\Dokumenty\atmelAVR\Priklady\COMLETED_LAB_PROJECTS\VolumeIV_Interrupts\sineWave_lab9\sineWave.asm"