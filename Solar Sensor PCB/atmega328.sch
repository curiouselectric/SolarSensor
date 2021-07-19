EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 4900 5900 0    50   ~ 0
DTR
Text Label 4900 5400 0    50   ~ 0
GND
Text Label 4900 5500 0    50   ~ 0
CTS
Text Label 4900 5700 0    50   ~ 0
RXI
Text Label 4900 5800 0    50   ~ 0
TX0
Wire Wire Line
	5150 5900 4900 5900
Wire Wire Line
	4900 5800 5150 5800
Wire Wire Line
	5150 5700 4900 5700
Wire Wire Line
	4650 5450 4650 5400
Wire Wire Line
	4650 5400 4800 5400
Connection ~ 4800 5400
Wire Wire Line
	4800 5500 4800 5400
Wire Wire Line
	4800 5500 5150 5500
Wire Wire Line
	4800 5400 5150 5400
Wire Wire Line
	4650 5600 5150 5600
Text Notes 4600 6100 0    50   ~ 0
FTDI for Normal\nProgramming
Wire Wire Line
	7250 3700 7350 3700
Wire Wire Line
	7050 3300 7050 3700
Wire Wire Line
	6200 3300 7050 3300
Connection ~ 7850 2300
Wire Wire Line
	7850 2100 7750 2100
Wire Wire Line
	7850 2300 7850 2100
Wire Wire Line
	7850 2300 7850 2800
Connection ~ 7250 2300
Wire Wire Line
	7200 2300 7250 2300
Wire Wire Line
	7200 2400 7200 2300
Connection ~ 4400 3950
Wire Wire Line
	4300 3950 4400 3950
Wire Wire Line
	4400 3250 4600 3250
Text Label 8850 2400 2    50   ~ 0
I2C_SDA
Text Label 8850 2300 2    50   ~ 0
I2C_SCL
Connection ~ 8050 2500
Wire Wire Line
	8050 2500 8050 2400
Wire Wire Line
	8050 2500 8200 2500
Connection ~ 5600 4650
Wire Wire Line
	5700 4650 5600 4650
Wire Wire Line
	5700 4500 5700 4650
Wire Wire Line
	5800 4500 5700 4500
Wire Wire Line
	5800 4550 5800 4500
Wire Wire Line
	7250 4350 7250 4300
Text Notes 6650 5350 0    50   ~ 0
ISP for Initial\nProgramming
Wire Wire Line
	5500 4650 5400 4650
Connection ~ 5500 4650
Wire Wire Line
	5500 4500 5500 4650
Wire Wire Line
	5400 4650 5400 4500
Wire Wire Line
	5600 4650 5500 4650
Connection ~ 5600 1350
Wire Wire Line
	5500 1350 5500 1500
Wire Wire Line
	5600 1350 5500 1350
$Comp
L matts_components:ATmega328P-AU-MCU_Microchip_ATmega U?
U 1 1 60FFEE05
P 5600 3000
AR Path="/60FFEE05" Ref="U?"  Part="1" 
AR Path="/60FF06B8/60FFEE05" Ref="U4"  Part="1" 
F 0 "U4" H 5600 4000 50  0000 C CNN
F 1 "ATmega328P-AU" V 5450 3100 50  0000 C CNN
F 2 "REInnovationFootprint:TQFP32-08" H 5600 3000 50  0001 C CIN
F 3 "" H 5600 3000 50  0001 C CNN
F 4 "Farnell" H 5600 3000 50  0001 C CNN "Supplier 1"
F 5 "ATMEL" H 5600 3000 50  0001 C CNN "Manufacturer"
F 6 "ATMEGA328P-AU" H 5600 3000 50  0001 C CNN "Manufacturer Part"
F 7 "C14877" H 5600 3000 50  0001 C CNN "LCSC"
F 8 "Y" H 5600 3000 50  0001 C CNN "JLCPCB Add"
F 9 "1.2649" H 5600 3000 50  0001 C CNN "JLCPCB Cost"
	1    5600 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60FFEE2F
P 8200 2750
AR Path="/60FFEE2F" Ref="R?"  Part="1" 
AR Path="/60FF06B8/60FFEE2F" Ref="R7"  Part="1" 
F 0 "R7" V 8200 2650 50  0000 L CNN
F 1 "4k7" V 8150 2500 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 8130 2750 50  0001 C CNN
F 3 "~" H 8200 2750 50  0001 C CNN
F 4 "Farnell" H 8200 2750 50  0001 C CNN "Supplier 1"
F 5 "9334580" H 8200 2750 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/multicomp/mc01w080554k7/res-4k7-5-0-1w-0805-thick-film/dp/9334580?st=0805%20resistor%204k7" H 8200 2750 50  0001 C CNN "Supplier 1 Web"
F 7 "MC01W080554K7" H 8200 2750 50  0001 C CNN "Manufacturer Part"
F 8 "0.01" H 8200 2750 50  0001 C CNN "Supplier 1 Cost"
F 9 "C17673" H 8200 2750 50  0001 C CNN "LCSC"
F 10 "Y" H 8200 2750 50  0001 C CNN "JLCPCB Add"
F 11 "0.0031" H 8200 2750 50  0001 C CNN "JLCPCB Cost"
	1    8200 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60FFEE3D
P 7250 3500
AR Path="/60FFEE3D" Ref="R?"  Part="1" 
AR Path="/60FF06B8/60FFEE3D" Ref="R5"  Part="1" 
F 0 "R5" H 7320 3546 50  0000 L CNN
F 1 "10k" H 7320 3455 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 7180 3500 50  0001 C CNN
F 3 "~" H 7250 3500 50  0001 C CNN
F 4 "Farnell" H 7250 3500 50  0001 C CNN "Supplier 1"
F 5 "2073607" H 7250 3500 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/multicomp/mcmr08x1002ftl/res-10k-1-0-125w-0805-ceramic/dp/2073607?st=0805%20resistor%2010k" H 7250 3500 50  0001 C CNN "Supplier 1 Web"
F 7 "0.02" H 7250 3500 50  0001 C CNN "Supplier 1 Cost"
F 8 "MCMR08X1002FTL" H 7250 3500 50  0001 C CNN "Manufacturer Part"
F 9 "C17414" H 7250 3500 50  0001 C CNN "LCSC"
F 10 "Y" H 7250 3500 50  0001 C CNN "JLCPCB Add"
F 11 "0.0029" H 7250 3500 50  0001 C CNN "JLCPCB Cost"
	1    7250 3500
	1    0    0    -1  
$EndComp
Text Notes 2600 3800 0    50   ~ 0
SENSOR Board ID\n
Wire Wire Line
	3500 4150 3500 4050
Connection ~ 3500 4150
Wire Wire Line
	3400 4150 3500 4150
Connection ~ 3500 4250
Wire Wire Line
	3500 4050 3400 4050
Wire Wire Line
	3500 4250 3500 4150
Wire Wire Line
	3500 4250 3500 4400
Wire Wire Line
	3400 4250 3500 4250
$Comp
L matts_components:ISP_3X2 P?
U 1 1 60FFEE6D
P 3000 4200
AR Path="/60FFEE6D" Ref="P?"  Part="1" 
AR Path="/60FF06B8/60FFEE6D" Ref="P3"  Part="1" 
F 0 "P3" H 3000 4550 50  0000 C CNN
F 1 "ID" H 3000 4466 40  0000 C CNN
F 2 "REInnovationFootprint:SM_6pad_3W_SOLDER" H 3000 4200 60  0001 C CNN
F 3 "" H 3000 4200 60  0000 C CNN
F 4 "Toby Electronics" H 3000 4200 50  0001 C CNN "Supplier 1"
F 5 "THD-03-R" H 3000 4200 50  0001 C CNN "Supplier 1 Code"
F 6 "https://www.toby.co.uk/board-to-board-pcb-connectors/254mm-headers/thd-valcon-2.54mm-pitch-dual-row-pin-header/" H 3000 4200 50  0001 C CNN "Supplier 1 Web"
F 7 "Valcon" H 3000 4200 50  0001 C CNN "Manufacturer"
F 8 "0.05" H 3000 4200 50  0001 C CNN "Supplier 1 Cost"
	1    3000 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4050 2450 4050
Wire Wire Line
	2600 4150 2450 4150
Wire Wire Line
	2600 4250 2450 4250
Text Label 2450 4250 2    50   ~ 0
A2
Text Label 2450 4150 2    50   ~ 0
A1
Text Label 2450 4050 2    50   ~ 0
A0
Wire Wire Line
	2450 2350 2650 2350
Text Label 2450 2350 0    50   ~ 0
D8
Wire Wire Line
	2650 3150 2650 2950
$Comp
L matts_components:SW_PUSH SW?
U 1 1 60FFEE95
P 2650 2650
AR Path="/60FFEE95" Ref="SW?"  Part="1" 
AR Path="/60FF06B8/60FFEE95" Ref="SW1"  Part="1" 
F 0 "SW1" V 2604 2767 50  0000 L CNN
F 1 "SWA" V 2695 2767 50  0000 L CNN
F 2 "REInnovationFootprint:SMD_SW_6x3_5" H 2650 2650 60  0001 C CNN
F 3 "" H 2650 2650 60  0000 C CNN
F 4 "https://uk.farnell.com/alcoswitch-te-connectivity/147873-1/tactile-switch-spst-0-05a-24v/dp/2610942" H 2650 2650 50  0001 C CNN "Supplier 1 Web"
F 5 "Farnell" H 2650 2650 50  0001 C CNN "Supplier 1"
F 6 "2610942" H 2650 2650 50  0001 C CNN "Supplier 1 Code"
F 7 "147873-1" H 2650 2650 50  0001 C CNN "Manufacturer Part"
F 8 "0.236" H 2650 2650 50  0001 C CNN "Supplier 1 Cost"
F 9 "C412368" H 2650 2650 50  0001 C CNN "LCSC"
F 10 "Y" H 2650 2650 50  0001 C CNN "JLCPCB Add"
F 11 "0.0194" H 2650 2650 50  0001 C CNN "JLCPCB Cost"
	1    2650 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	7250 2300 7400 2300
$Comp
L Device:Crystal Y?
U 1 1 60FFEEA6
P 7250 2550
AR Path="/60FFEEA6" Ref="Y?"  Part="1" 
AR Path="/60FF06B8/60FFEEA6" Ref="Y1"  Part="1" 
F 0 "Y1" V 7250 2700 50  0000 L CNN
F 1 "8MHz_XTAL" V 7350 2700 50  0000 L CNN
F 2 "REInnovationFootprint:SM-crystal-HC49UP" H 7250 2550 50  0001 C CNN
F 3 "~" H 7250 2550 50  0001 C CNN
F 4 "Farnell" H 7250 2550 50  0001 C CNN "Supplier 1"
F 5 "2832071" H 7250 2550 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/iqd-frequency-products/lfxtal058154/crystal-8mhz-18pf-11-4mm-x-4-9mm/dp/2832071?st=hc49%208mhz" H 7250 2550 50  0001 C CNN "Supplier 1 Web"
F 7 "LFXTAL058154" H 7250 2550 50  0001 C CNN "Manufacturer Part"
F 8 "0.5952" H 7250 2550 50  0001 C CNN "Supplier 1 Cost"
F 9 "C12674" H 7250 2550 50  0001 C CNN "LCSC"
F 10 "Y" H 7250 2550 50  0001 C CNN "JLCPCB Add"
F 11 "0.0425" H 7250 2550 50  0001 C CNN "JLCPCB Cost"
	1    7250 2550
	0    1    1    0   
$EndComp
$Comp
L Device:LED D?
U 1 1 60FFEEC0
P 1800 3300
AR Path="/60FFEEC0" Ref="D?"  Part="1" 
AR Path="/60FF06B8/60FFEEC0" Ref="D2"  Part="1" 
F 0 "D2" V 1900 3300 50  0000 R CNN
F 1 "LED0" V 1550 3300 50  0000 R CNN
F 2 "REInnovationFootprint:SM0805_LED" H 1800 3300 50  0001 C CNN
F 3 "~" H 1800 3300 50  0001 C CNN
F 4 "Farnell" H 1800 3300 50  0001 C CNN "Supplier 1"
F 5 "3015159" H 1800 3300 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/multicomp-pro/mc011368/led-orange-red-150mcd-620nm-0805/dp/3015159" H 1800 3300 50  0001 C CNN "Supplier 1 Web"
F 7 "MC011368" H 1800 3300 50  0001 C CNN "Manufacturer Part"
F 8 "0.0834" H 1800 3300 50  0001 C CNN "Supplier 1 Cost"
F 9 "C2296" H 1800 3300 50  0001 C CNN "LCSC"
F 10 "Y" H 1800 3300 50  0001 C CNN "JLCPCB Add"
F 11 "0.0102" H 1800 3300 50  0001 C CNN "JLCPCB Cost"
	1    1800 3300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60FFEECE
P 1800 2850
AR Path="/60FFEECE" Ref="R?"  Part="1" 
AR Path="/60FF06B8/60FFEECE" Ref="R4"  Part="1" 
F 0 "R4" H 1870 2896 50  0000 L CNN
F 1 "470" H 1870 2805 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 1730 2850 50  0001 C CNN
F 3 "~" H 1800 2850 50  0001 C CNN
F 4 "Farnell" H 1800 2850 50  0001 C CNN "Supplier 1"
F 5 "2447662" H 1800 2850 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/multicomp/mcwr08x4700ftl/res-470r-1-0-125w-thick-film/dp/2447662?st=470r%200805" H 1800 2850 50  0001 C CNN "Supplier 1 Web"
F 7 "MCWR08X4700FTL" H 1800 2850 50  0001 C CNN "Manufacturer Part"
F 8 "0.0077" H 1800 2850 50  0001 C CNN "Supplier 1 Cost"
F 9 "C17710" H 1800 2850 50  0001 C CNN "LCSC"
F 10 "Y" H 1800 2850 50  0001 C CNN "JLCPCB Add"
F 11 "0.0030" H 1800 2850 50  0001 C CNN "JLCPCB Cost"
	1    1800 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 5600 5850 5600
Wire Wire Line
	5850 5700 6100 5700
Wire Wire Line
	6100 5800 5850 5800
Wire Wire Line
	6900 5800 7050 5800
Wire Wire Line
	7050 5700 6900 5700
Wire Wire Line
	6900 5600 7050 5600
Text Label 7050 5700 0    50   ~ 0
MOSI
Text Label 6650 3300 0    50   ~ 0
RESET
Text Label 5850 5800 0    50   ~ 0
RESET
Text Label 5850 5700 0    50   ~ 0
SCLK
Text Label 5850 5600 0    50   ~ 0
MISO
Text Label 6350 4200 0    50   ~ 0
D7
Text Label 6350 4100 0    50   ~ 0
D6
Text Label 6350 4000 0    50   ~ 0
D5
Text Label 6350 3900 0    50   ~ 0
D4
Text Label 6350 3800 0    50   ~ 0
D3
Text Label 6350 3700 0    50   ~ 0
D2
Text Label 6350 3600 0    50   ~ 0
TX0
Text Label 6350 3500 0    50   ~ 0
RXI
Text Label 7900 3700 0    50   ~ 0
DTR
Wire Wire Line
	7250 3350 7250 3300
Wire Wire Line
	7250 3700 7050 3700
Wire Wire Line
	7250 3700 7250 3650
Connection ~ 7250 3700
$Comp
L matts_components:SW_PUSH SW?
U 1 1 60FFEF00
P 7250 4000
AR Path="/60FFEF00" Ref="SW?"  Part="1" 
AR Path="/60FF06B8/60FFEF00" Ref="SW2"  Part="1" 
F 0 "SW2" V 7204 4117 50  0000 L CNN
F 1 "RST" V 7295 4117 50  0000 L CNN
F 2 "REInnovationFootprint:SMD_SW_6x3_5" H 7250 4000 60  0001 C CNN
F 3 "" H 7250 4000 60  0000 C CNN
F 4 "Farnell" H 7250 4000 50  0001 C CNN "Supplier 1"
F 5 "2610942" H 7250 4000 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/alcoswitch-te-connectivity/147873-1/tactile-switch-spst-0-05a-24v/dp/2610942" H 7250 4000 50  0001 C CNN "Supplier 1 Web"
F 7 "147873-1" H 7250 4000 50  0001 C CNN "Manufacturer Part"
F 8 "0.236" H 7250 4000 50  0001 C CNN "Supplier 1 Cost"
F 9 "C412368" H 7250 4000 50  0001 C CNN "LCSC"
F 10 "Y" H 7250 4000 50  0001 C CNN "JLCPCB Add"
F 11 "0.0194" H 7250 4000 50  0001 C CNN "JLCPCB Cost"
	1    7250 4000
	0    1    1    0   
$EndComp
Text Label 7000 3100 0    50   ~ 0
I2C_SDA
Text Label 7000 3200 0    50   ~ 0
I2C_SCL
Wire Wire Line
	8200 3200 8200 2900
Wire Wire Line
	8050 3100 8050 2900
Wire Wire Line
	8200 2500 8200 2600
Wire Wire Line
	8050 2600 8050 2500
Text Label 6350 3200 0    50   ~ 0
A5_SCL
Text Label 6350 3100 0    50   ~ 0
A4_SDA
Text Label 6350 3000 0    50   ~ 0
A3
Text Label 6350 2900 0    50   ~ 0
A2
Text Label 6350 2800 0    50   ~ 0
A1
Text Label 6350 2700 0    50   ~ 0
A0
Text Label 4850 2100 0    50   ~ 0
A7
Text Label 4850 2000 0    50   ~ 0
A6
Wire Wire Line
	7250 2800 7250 2700
Wire Wire Line
	7250 2300 7250 2400
Text Label 6350 2300 0    50   ~ 0
SCLK
Text Label 6350 2200 0    50   ~ 0
MISO
Text Label 6350 2100 0    50   ~ 0
MOSI
Text Label 6350 2000 0    50   ~ 0
D10
Text Label 6350 1900 0    50   ~ 0
D9
Text Label 6350 1800 0    50   ~ 0
D8
$Comp
L Device:R R?
U 1 1 60FFEF2E
P 8050 2750
AR Path="/60FFEF2E" Ref="R?"  Part="1" 
AR Path="/60FF06B8/60FFEF2E" Ref="R6"  Part="1" 
F 0 "R6" V 8050 2650 50  0000 L CNN
F 1 "4k7" V 8000 2500 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 7980 2750 50  0001 C CNN
F 3 "~" H 8050 2750 50  0001 C CNN
F 4 "Farnell" H 8050 2750 50  0001 C CNN "Supplier 1"
F 5 "9334580" H 8050 2750 50  0001 C CNN "Supplier 1 Code"
F 6 "https://uk.farnell.com/multicomp/mc01w080554k7/res-4k7-5-0-1w-0805-thick-film/dp/9334580?st=0805%20resistor%204k7" H 8050 2750 50  0001 C CNN "Supplier 1 Web"
F 7 "MC01W080554K7" H 8050 2750 50  0001 C CNN "Manufacturer Part"
F 8 "0.01" H 8050 2750 50  0001 C CNN "Supplier 1 Cost"
F 9 "C17673" H 8050 2750 50  0001 C CNN "LCSC"
F 10 "Y" H 8050 2750 50  0001 C CNN "JLCPCB Add"
F 11 "0.0031" H 8050 2750 50  0001 C CNN "JLCPCB Cost"
	1    8050 2750
	1    0    0    -1  
$EndComp
$Comp
L matts_components:ISP_3X2 P?
U 1 1 60FFEF34
P 6500 5750
AR Path="/60FFEF34" Ref="P?"  Part="1" 
AR Path="/60FF06B8/60FFEF34" Ref="P4"  Part="1" 
F 0 "P4" H 6500 6100 50  0000 C CNN
F 1 "ISP" H 6500 6016 40  0000 C CNN
F 2 "REInnovationFootprint:ISP_3x2" H 6500 5750 60  0001 C CNN
F 3 "" H 6500 5750 60  0000 C CNN
	1    6500 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4500 5600 4650
Connection ~ 5700 1350
Wire Wire Line
	5700 1350 5700 1250
Wire Wire Line
	5700 1350 5700 1500
Wire Wire Line
	5600 1350 5700 1350
Wire Wire Line
	5600 1500 5600 1350
Connection ~ 4400 3250
Wire Wire Line
	4400 3100 4400 3250
Wire Wire Line
	4400 3950 4600 3950
Wire Wire Line
	4400 4100 4400 3950
Wire Wire Line
	4600 3250 4600 3400
Wire Wire Line
	4300 3250 4400 3250
Wire Wire Line
	4300 3400 4300 3250
Text Notes 6150 1300 0    50   ~ 0
Use SMD IC for Product\n3.3V= 8MHz max.\n5V  = 16MHz max.
Text HLabel 7050 5600 2    60   Input ~ 0
Vcc
Text HLabel 1800 3700 3    60   Input ~ 0
GND
Text HLabel 7250 4350 2    60   Input ~ 0
GND
Text HLabel 5800 4550 2    60   Input ~ 0
GND
Text HLabel 4400 4100 2    60   Input ~ 0
GND
Text HLabel 7050 5800 2    60   Input ~ 0
GND
Text HLabel 4650 5600 0    60   Input ~ 0
Vcc
Text HLabel 4650 5450 0    60   Input ~ 0
GND
Text HLabel 2650 3150 3    60   Input ~ 0
GND
Text HLabel 3500 4400 3    60   Input ~ 0
GND
Text HLabel 4400 3100 0    60   Input ~ 0
Vcc
Text HLabel 5700 1250 2    60   Input ~ 0
Vcc
Text HLabel 8050 2400 1    60   Input ~ 0
Vcc
Text Label 1800 2600 0    50   ~ 0
D7
Wire Wire Line
	1800 3000 1800 3150
Wire Wire Line
	1800 2700 1800 2600
Wire Wire Line
	1800 3450 1800 3700
Text HLabel 7250 3300 2    60   Input ~ 0
Vcc
Text HLabel 7750 2100 0    60   Input ~ 0
GND
$Comp
L device:C C10
U 1 1 6105B9E6
P 7550 2800
F 0 "C10" V 7700 2850 50  0000 C CNN
F 1 "22pf" V 7700 2700 50  0000 C CNN
F 2 "REInnovationFootprint:SM_C_0805" H 7588 2650 50  0001 C CNN
F 3 "~" H 7550 2800 50  0001 C CNN
	1    7550 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	7250 2800 7400 2800
$Comp
L device:C C9
U 1 1 6105C39C
P 7550 2300
F 0 "C9" V 7700 2350 50  0000 C CNN
F 1 "22pf" V 7700 2200 50  0000 C CNN
F 2 "REInnovationFootprint:SM_C_0805" H 7588 2150 50  0001 C CNN
F 3 "~" H 7550 2300 50  0001 C CNN
	1    7550 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 2300 7850 2300
Wire Wire Line
	7700 2800 7850 2800
$Comp
L device:C C8
U 1 1 61064A37
P 7500 3700
F 0 "C8" V 7650 3800 50  0000 C CNN
F 1 "100nf" V 7350 3800 50  0000 C CNN
F 2 "REInnovationFootprint:SM_C_0805" H 7538 3550 50  0001 C CNN
F 3 "~" H 7500 3700 50  0001 C CNN
	1    7500 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 3700 7900 3700
Text HLabel 8850 2600 0    60   Input ~ 0
GND
Text HLabel 8850 2500 0    60   Input ~ 0
Vcc
$Comp
L Connector_Generic:Conn_01x04 P10
U 1 1 61070D8C
P 9550 2400
F 0 "P10" H 9630 2392 50  0000 L CNN
F 1 "I2C" H 9630 2301 50  0000 L CNN
F 2 "REInnovationFootprint:SIL-4_Grove_Not_Labelled" H 9550 2400 50  0001 C CNN
F 3 "~" H 9550 2400 50  0001 C CNN
	1    9550 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 2600 9350 2600
Wire Wire Line
	8850 2500 9350 2500
Wire Wire Line
	8850 2400 8900 2400
Wire Wire Line
	8850 2300 8900 2300
$Comp
L device:C C7
U 1 1 610811F3
P 4600 3550
F 0 "C7" H 4650 3450 50  0000 C CNN
F 1 "100nf" V 4500 3750 50  0000 C CNN
F 2 "REInnovationFootprint:SM_C_0805" H 4638 3400 50  0001 C CNN
F 3 "~" H 4600 3550 50  0001 C CNN
	1    4600 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C6
U 1 1 610819A4
P 4300 3550
F 0 "C6" H 4100 3650 50  0000 L CNN
F 1 "100uf" V 4150 3350 50  0000 L CNN
F 2 "REInnovationFootprint:SM_6.3x7.7" H 4338 3400 50  0001 C CNN
F 3 "~" H 4300 3550 50  0001 C CNN
	1    4300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3700 4300 3950
Wire Wire Line
	4600 3700 4600 3950
Text HLabel 8950 2250 2    60   Output ~ 0
I2C_SCL
Text HLabel 8950 2350 2    60   Output ~ 0
I2C_SDA
Wire Wire Line
	8950 2350 8900 2350
Wire Wire Line
	8900 2350 8900 2400
Connection ~ 8900 2400
Wire Wire Line
	8900 2400 9350 2400
Wire Wire Line
	8950 2250 8900 2250
Wire Wire Line
	8900 2250 8900 2300
Connection ~ 8900 2300
Wire Wire Line
	8900 2300 9350 2300
Text HLabel 6600 3500 2    60   Input ~ 0
RXI
Text HLabel 6600 3600 2    60   Output ~ 0
TXO
Text HLabel 6600 3700 2    60   Output ~ 0
D2
Text HLabel 6600 3800 2    60   Output ~ 0
D3
Text HLabel 6600 3900 2    60   Output ~ 0
D4
Text HLabel 6600 4000 2    60   Output ~ 0
D5
Text HLabel 6600 4100 2    60   Output ~ 0
D6
Text HLabel 6600 4200 2    60   Output ~ 0
D7_LED0
Wire Wire Line
	6200 4200 6600 4200
Wire Wire Line
	6200 3500 6600 3500
Wire Wire Line
	6200 3600 6600 3600
Wire Wire Line
	6200 3700 6600 3700
Wire Wire Line
	6200 3800 6600 3800
Wire Wire Line
	6200 3900 6600 3900
Wire Wire Line
	6200 4000 6600 4000
Wire Wire Line
	6200 4100 6600 4100
Wire Wire Line
	6200 3100 8050 3100
Wire Wire Line
	6200 3200 8200 3200
Wire Wire Line
	6200 2400 7200 2400
Wire Wire Line
	7250 2800 7100 2800
Wire Wire Line
	7100 2800 7100 2500
Wire Wire Line
	6200 2500 7100 2500
Connection ~ 7250 2800
Text HLabel 6700 2700 2    60   Output ~ 0
A0
Text HLabel 6700 2800 2    60   Output ~ 0
A1
Text HLabel 6700 2900 2    60   Output ~ 0
A2
Text HLabel 6700 3000 2    60   Output ~ 0
A3
Text HLabel 4700 2000 0    60   Output ~ 0
A6
Text HLabel 4700 2100 0    60   Output ~ 0
A7
Wire Wire Line
	4700 2000 5000 2000
Wire Wire Line
	4700 2100 5000 2100
Wire Wire Line
	6200 3000 6700 3000
Wire Wire Line
	6200 2900 6700 2900
Wire Wire Line
	6200 2800 6700 2800
Wire Wire Line
	6200 2700 6700 2700
Text HLabel 6700 1800 2    60   Output ~ 0
D8_SWA
Text HLabel 6700 1900 2    60   Output ~ 0
D9
Text HLabel 6700 2000 2    60   Output ~ 0
D10
Text HLabel 6700 2100 2    60   Output ~ 0
MOSI
Text HLabel 6700 2200 2    60   Output ~ 0
MISO
Text HLabel 6700 2300 2    60   Output ~ 0
SCLK
Wire Wire Line
	6200 1800 6700 1800
Wire Wire Line
	6200 1900 6700 1900
Wire Wire Line
	6200 2000 6700 2000
Wire Wire Line
	6200 2100 6700 2100
Wire Wire Line
	6200 2200 6700 2200
Wire Wire Line
	6200 2300 6700 2300
$Comp
L device:C C5
U 1 1 60F36418
P 4200 2050
F 0 "C5" H 4250 1950 50  0000 C CNN
F 1 "100nf" V 4100 2250 50  0000 C CNN
F 2 "REInnovationFootprint:SM_C_0805" H 4238 1900 50  0001 C CNN
F 3 "~" H 4200 2050 50  0001 C CNN
	1    4200 2050
	-1   0    0    1   
$EndComp
Text HLabel 4200 2400 3    60   Input ~ 0
GND
Wire Wire Line
	4200 1800 4200 1900
Wire Wire Line
	4200 1800 5000 1800
Wire Wire Line
	4200 2200 4200 2400
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 60FFEDA9
P 5350 5600
AR Path="/60FFEDA9" Ref="J?"  Part="1" 
AR Path="/60FF06B8/60FFEDA9" Ref="P9"  Part="1" 
F 0 "P9" H 5430 5592 50  0000 L CNN
F 1 "PROG" H 5430 5501 50  0000 L CNN
F 2 "REInnovationFootprint:TH_6x1_FTDI" H 5350 5600 50  0001 C CNN
F 3 "~" H 5350 5600 50  0001 C CNN
	1    5350 5600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
