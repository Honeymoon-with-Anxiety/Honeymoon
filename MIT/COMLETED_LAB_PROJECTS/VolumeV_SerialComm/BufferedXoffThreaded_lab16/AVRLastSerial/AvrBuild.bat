@ECHO OFF
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\lastserial.map"
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\labels.tmp" -fI  -o "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\lastserial.hex" -d "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\lastserial.obj" -e "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\lastserial.eep" -m "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\voa9b6~1\buffer~1\avrlas~1\lastserial.map" -W+ie   "C:\Documents and Settings\dd\Dokumenty\atmelAVR\Priklady\COMLETED_LAB_PROJECTS\VolumeV_SerialComm\BufferedXoffThreaded\AVRLastSerial\LastSerial.asm"