SET PATH=D:\ARM\Keil\ARM\ARMCC\bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\Git\cmd;C:\Program Files\MATLAB\R2008a\bin;C:\Program Files\MATLAB\R2008a\bin\win32;C:\Program Files\Microsoft SQL Server\100\Tools\Binn\;C:\Program Files\Microsoft SQL Server\100\DTS\Binn\;C:\Program Files\GnuWin32\bin;C:\Program Files\GNU Tools ARM Embedded\5.4 2016q2\bin;C:\Program Files\PuTTY\;C:\Program Files\Altium Designer 6\System;C:\Program Files\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\TortoiseGit\bin;C:\Program Files\Atmel\sam-ba_2.12\drv\;C:\Program Files\Atmel\sam-ba_2.12;C:\Program Files\Atmel\sam-ba_2.15\drv\;C:\Program Files\Atmel\sam-ba_2.15;C:\Python\Scripts\;C:\Python\;C:\Program Files\GnuWin32\bin;C:\Program Files\GNU Tools ARM Embedded\5.4 2016q2\bin
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\main.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\stm32f10x_it.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\led.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\sys.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmAsm" --Via "..\obj\startup_stm32f10x_hd._ia"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\stm32f10x_gpio.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\misc.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\stm32f10x_rcc.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmCC" --Via "..\obj\appinterface.__i"
"D:\ARM\Keil\ARM\ARMCC\bin\ArmLink" --Via "..\OBJ\LED.lnp"
D:\ARM\Keil\ARM\ARMCC\bin\fromelf.exe "..\OBJ\LED.axf" --i32combined --output "..\OBJ\LED.hex"
"D:\ARM\Keil\UV4\KSPAWN.EXE" D:\ARM\Keil\ARM\ARMCC\bin\fromelf.exe --bin -o ../output/iap.bin ../OBJ/LED.axf
