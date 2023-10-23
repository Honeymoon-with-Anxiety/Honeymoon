@ECHO OFF
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\adc1.map"
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\labels.tmp" -fI  -o "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\adc1.hex" -d "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\adc1.obj" -e "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\adc1.eep" -m "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~3\adc_la~1\adc1.map" -W+ie   "C:\Documents and Settings\dd\Dokumenty\atmelAVR\Priklady\COMLETED_LAB_PROJECTS\VolumeIV_Interrupts\ADC_lab11\ADC1.asm"
