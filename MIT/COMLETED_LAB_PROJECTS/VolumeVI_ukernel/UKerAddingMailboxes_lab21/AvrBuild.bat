@ECHO OFF
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\tokenring.map"
del "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\labels.tmp" -fI  -o "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\tokenring.hex" -d "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\tokenring.obj" -e "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\tokenring.eep" -m "c:\docume~1\dd\dokume~1\atmelavr\priklady\comlet~1\volume~4\ukerad~1\tokenring.map" -W+ie   "C:\Documents and Settings\dd\Dokumenty\atmelAVR\Priklady\COMLETED_LAB_PROJECTS\VolumeVI_ukernel\UKerAddingMailboxes_lab21\TokenRing.asm"