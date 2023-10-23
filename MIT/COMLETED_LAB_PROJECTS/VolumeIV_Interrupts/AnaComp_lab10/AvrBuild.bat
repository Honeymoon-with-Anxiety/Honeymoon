@ECHO OFF
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\anacomp.map"
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\labels.tmp" -fI  -o "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\anacomp.hex" -d "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\anacomp.obj" -e "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\anacomp.eep" -m "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\anacom~1\anacomp.map" -W+ie   "C:\Documents and Settings\dd\Dokumenty\atmelAVR\Priklady\MB_ATmega_16\AnaComp\AnaComp.asm"
