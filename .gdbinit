target remote localhost:1234
set architecture i8086
break *0x7c00
break *0xc000
continue
display/3i $pc
