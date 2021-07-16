EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 4600 7300 0    60   ~ 0
Temperature Measurement\nFor temp. compensation
$Comp
L Connector_Generic:Conn_01x04 P10
U 1 1 58FDD599
P 1050 2150
F 0 "P10" H 1050 2400 50  0000 C CNN
F 1 "SERIAL" V 1150 2150 50  0000 C CNN
F 2 "REInnovationFootprint:SIL-4_Grove_SCREW" H 1050 2150 50  0001 C CNN
F 3 "" H 1050 2150 50  0000 C CNN
	1    1050 2150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 58FDDFBF
P 4350 7200
F 0 "#PWR04" H 4350 6950 50  0001 C CNN
F 1 "GND" H 4350 7050 50  0000 C CNN
F 2 "" H 4350 7200 50  0000 C CNN
F 3 "" H 4350 7200 50  0000 C CNN
	1    4350 7200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 58FDDFE8
P 10350 1900
F 0 "#PWR05" H 10350 1750 50  0001 C CNN
F 1 "+5V" H 10350 2040 50  0000 C CNN
F 2 "" H 10350 1900 50  0000 C CNN
F 3 "" H 10350 1900 50  0000 C CNN
	1    10350 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 1900 10350 2000
Wire Wire Line
	10350 2000 10250 2000
$Comp
L power:+5V #PWR06
U 1 1 58FDE07A
P 4350 5950
F 0 "#PWR06" H 4350 5800 50  0001 C CNN
F 1 "+5V" H 4350 6090 50  0000 C CNN
F 2 "" H 4350 5950 50  0000 C CNN
F 3 "" H 4350 5950 50  0000 C CNN
	1    4350 5950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 58FDE267
P 6750 1400
F 0 "#PWR07" H 6750 1250 50  0001 C CNN
F 1 "+5V" H 6750 1540 50  0000 C CNN
F 2 "" H 6750 1400 50  0000 C CNN
F 3 "" H 6750 1400 50  0000 C CNN
	1    6750 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 58FDE29C
P 10400 2550
F 0 "#PWR08" H 10400 2300 50  0001 C CNN
F 1 "GND" H 10400 2400 50  0000 C CNN
F 2 "" H 10400 2550 50  0000 C CNN
F 3 "" H 10400 2550 50  0000 C CNN
	1    10400 2550
	1    0    0    -1  
$EndComp
$Comp
L SolarSensorPCB-rescue:SW_PUSH-matts_components SW1
U 1 1 58FDF0BF
P 9550 4200
F 0 "SW1" H 9550 4350 50  0000 C CNN
F 1 "UP" H 9550 4100 50  0000 C CNN
F 2 "REInnovationFootprint:SMD_SW_6x3_5" H 9550 4400 50  0001 C CNN
F 3 "" H 9550 4400 50  0000 C CNN
F 4 "C319333" H 9550 4200 50  0001 C CNN "LCSC"
F 5 "Y" H 9550 4200 50  0001 C CNN "JLCPCB Add"
F 6 "0.0391" H 9550 4200 50  0001 C CNN "JLCPCB Cost"
	1    9550 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 58FDF1ED
P 10000 4200
F 0 "#PWR010" H 10000 3950 50  0001 C CNN
F 1 "GND" H 10000 4050 50  0000 C CNN
F 2 "" H 10000 4200 50  0000 C CNN
F 3 "" H 10000 4200 50  0000 C CNN
	1    10000 4200
	1    0    0    -1  
$EndComp
Text HLabel 8950 4200 0    60   Input ~ 0
SW1
$Comp
L power:GND #PWR014
U 1 1 58FE0418
P 5200 3950
F 0 "#PWR014" H 5200 3700 50  0001 C CNN
F 1 "GND" H 5200 3800 50  0000 C CNN
F 2 "" H 5200 3950 50  0000 C CNN
F 3 "" H 5200 3950 50  0000 C CNN
	1    5200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR017
U 1 1 58FE0559
P 6850 4050
F 0 "#PWR017" H 6850 3900 50  0001 C CNN
F 1 "+5V" H 6850 4200 50  0000 C CNN
F 2 "" H 6850 4050 50  0000 C CNN
F 3 "" H 6850 4050 50  0000 C CNN
	1    6850 4050
	1    0    0    -1  
$EndComp
Text HLabel 7150 3650 2    60   Output ~ 0
SCL_I2C
Text HLabel 7150 3800 2    60   Output ~ 0
SDA_I2C
$Comp
L device:R R4
U 1 1 5900CACA
P 2350 3450
F 0 "R4" V 2430 3450 50  0000 C CNN
F 1 "47k" V 2350 3450 50  0000 C CNN
F 2 "REInnovationFootprint:SM0805" V 2280 3450 50  0001 C CNN
F 3 "" H 2350 3450 50  0000 C CNN
F 4 "C17713" H 2350 3450 50  0001 C CNN "LCSC"
F 5 "Y" H 2350 3450 50  0001 C CNN "JLCPCB Add"
F 6 "0.0040" H 2350 3450 50  0001 C CNN "JLCPCB Cost"
	1    2350 3450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5900CAD9
P 2300 4700
F 0 "#PWR018" H 2300 4450 50  0001 C CNN
F 1 "GND" H 2300 4550 50  0000 C CNN
F 2 "" H 2300 4700 50  0000 C CNN
F 3 "" H 2300 4700 50  0000 C CNN
	1    2300 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR019
U 1 1 5900CAE7
P 2300 3850
F 0 "#PWR019" H 2300 3700 50  0001 C CNN
F 1 "+5V" H 2300 3990 50  0000 C CNN
F 2 "" H 2300 3850 50  0000 C CNN
F 3 "" H 2300 3850 50  0000 C CNN
	1    2300 3850
	1    0    0    -1  
$EndComp
Text Notes 2950 3500 0    60   ~ 0
0.1% precision \nresistor
$Comp
L device:D_Photo D2
U 1 1 5900DD96
P 1400 4450
F 0 "D2" H 1250 4550 50  0000 C CNN
F 1 "PHOTO DIODE" H 1500 4350 50  0000 C CNN
F 2 "REInnovationFootprint:TH_LED-5MM_larg_pad" H 1400 4450 50  0001 C CNN
F 3 "" H 1400 4450 50  0000 C CNN
F 4 "~" H 1400 4450 60  0000 C CNN "Notes"
F 5 "~" H 1400 4450 60  0001 C CNN "Description"
F 6 "~" H 1400 4450 60  0001 C CNN "Manufacturer"
F 7 "~" H 1400 4450 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 1400 4450 60  0001 C CNN "Supplier 1"
F 9 "~" H 1400 4450 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 1400 4450 60  0001 C CNN "Supplier 1 Cost"
F 11 "~" H 1400 4450 60  0001 C CNN "Supplier 2"
F 12 "~" H 1400 4450 60  0001 C CNN "Supplier 2 Part No"
F 13 "~" H 1400 4450 60  0001 C CNN "Supplier 2 Cost"
	1    1400 4450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5900FD9D
P 1500 1700
F 0 "#PWR020" H 1500 1450 50  0001 C CNN
F 1 "GND" H 1500 1550 50  0000 C CNN
F 2 "" H 1500 1700 50  0000 C CNN
F 3 "" H 1500 1700 50  0000 C CNN
	1    1500 1700
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 5900FDE7
P 1750 2000
F 0 "#PWR021" H 1750 1850 50  0001 C CNN
F 1 "+5V" H 1750 2140 50  0000 C CNN
F 2 "" H 1750 2000 50  0000 C CNN
F 3 "" H 1750 2000 50  0000 C CNN
	1    1750 2000
	-1   0    0    -1  
$EndComp
Text HLabel 3250 2350 0    60   Input ~ 0
Rx
Text HLabel 3250 2450 0    60   Input ~ 0
Tx
Wire Wire Line
	1750 2000 1750 2050
Wire Wire Line
	1750 2050 1250 2050
Wire Wire Line
	1500 1700 1350 1700
Wire Wire Line
	1350 1700 1350 1950
Wire Wire Line
	1350 1950 1250 1950
Text HLabel 3250 2100 0    60   Input ~ 0
SW1
$Comp
L device:C C1
U 1 1 59012353
P 2350 3150
F 0 "C1" H 2375 3250 50  0000 L CNN
F 1 "10n" H 2375 3050 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 2388 3000 50  0001 C CNN
F 3 "" H 2350 3150 50  0000 C CNN
F 4 "C107135" H 2350 3150 50  0001 C CNN "LCSC"
F 5 "Y" H 2350 3150 50  0001 C CNN "JLCPCB Add"
F 6 "0.0105" H 2350 3150 50  0001 C CNN "JLCPCB Cost"
	1    2350 3150
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P5
U 1 1 59012D3E
P 6650 6750
F 0 "P5" H 6650 6850 50  0000 C CNN
F 1 "LOGO2" V 6750 6750 50  0000 C CNN
F 2 "CuriousElectric3:TCEC_Words_13mm" H 6650 6750 50  0001 C CNN
F 3 "" H 6650 6750 50  0000 C CNN
	1    6650 6750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P6
U 1 1 59012DA7
P 6650 7050
F 0 "P6" H 6650 7150 50  0000 C CNN
F 1 "PCB" V 6750 7050 50  0000 C CNN
F 2 "REInnovationFootprint:PCB_40mm_Round_SolarSensorPCB_design" H 6650 7050 50  0001 C CNN
F 3 "" H 6650 7050 50  0000 C CNN
	1    6650 7050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P7
U 1 1 59012E13
P 6650 7400
F 0 "P7" H 6650 7500 50  0000 C CNN
F 1 "ENC" V 6750 7400 50  0000 C CNN
F 2 "" H 6650 7400 50  0001 C CNN
F 3 "https://www.rapidonline.com/pdf/30-3800e.pdf" H 6650 7400 50  0001 C CNN
F 4 "~" H 6650 7400 60  0000 C CNN "Notes"
F 5 "~" H 6650 7400 60  0001 C CNN "Description"
F 6 "~" H 6650 7400 60  0001 C CNN "Manufacturer"
F 7 "~" H 6650 7400 60  0001 C CNN "Manufacturer Part No"
F 8 "Rapid" H 6650 7400 60  0001 C CNN "Supplier 1"
F 9 "30-3804" H 6650 7400 60  0001 C CNN "Supplier 1 Part No"
F 10 "4.37" H 6650 7400 60  0001 C CNN "Supplier 1 Cost"
F 11 "~" H 6650 7400 60  0001 C CNN "Supplier 2"
F 12 "~" H 6650 7400 60  0001 C CNN "Supplier 2 Part No"
F 13 "~" H 6650 7400 60  0001 C CNN "Supplier 2 Cost"
	1    6650 7400
	1    0    0    -1  
$EndComp
NoConn ~ 6450 6750
NoConn ~ 6450 7050
NoConn ~ 6450 7400
Text Notes 5500 4550 0    60   ~ 0
16 Bit ADC
$Comp
L device:CP1 C5
U 1 1 60CD624D
P 10250 2250
F 0 "C5" H 10275 2350 50  0000 L CNN
F 1 "100u" H 10275 2150 50  0000 L CNN
F 2 "REInnovationFootprint:SM_4x5.3" H 10250 2250 50  0001 C CNN
F 3 "" H 10250 2250 50  0000 C CNN
F 4 "C134722" H 10250 2250 50  0001 C CNN "LCSC"
F 5 "Y" H 10250 2250 50  0001 C CNN "JLCPCB Add"
F 6 "0.0566" H 10250 2250 50  0001 C CNN "JLCPCB Cost"
	1    10250 2250
	1    0    0    -1  
$EndComp
$Comp
L device:C C6
U 1 1 60CD67EE
P 10550 2250
F 0 "C6" H 10575 2350 50  0000 L CNN
F 1 "100n" H 10575 2150 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 10588 2100 50  0001 C CNN
F 3 "" H 10550 2250 50  0000 C CNN
F 4 "C49678" H 10550 2250 50  0001 C CNN "LCSC"
F 5 "Y" H 10550 2250 50  0001 C CNN "JLCPCB Add"
F 6 "0.0108" H 10550 2250 50  0001 C CNN "JLCPCB Cost"
	1    10550 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 2000 10550 2000
Wire Wire Line
	10550 2000 10550 2100
Connection ~ 10350 2000
Connection ~ 10250 2000
Wire Wire Line
	10250 2450 10400 2450
Wire Wire Line
	10250 2100 10250 2000
Wire Wire Line
	10250 2400 10250 2450
Wire Wire Line
	10550 2400 10550 2450
Wire Wire Line
	9850 4200 10000 4200
$Comp
L SolarSensorPCB-rescue:ADS1115-matts_components U3
U 1 1 60D28746
P 5750 3800
F 0 "U3" H 5800 4287 60  0000 C CNN
F 1 "ADS1115" H 5800 4181 60  0000 C CNN
F 2 "REInnovationFootprint:SM_MSOP10-0.5" H 5950 3700 60  0001 C CNN
F 3 "" H 5950 3700 60  0000 C CNN
F 4 "C37593" H 5750 3800 50  0001 C CNN "LCSC"
F 5 "Y" H 5750 3800 50  0001 C CNN "JLCPCB Add"
F 6 "4.7766" H 5750 3800 50  0001 C CNN "JLCPCB Cost"
	1    5750 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3950 5400 3950
$Comp
L device:R R3
U 1 1 60D4783F
P 4900 3550
F 0 "R3" H 4970 3596 50  0000 L CNN
F 1 "10k" H 4970 3505 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 4830 3550 50  0001 C CNN
F 3 "~" H 4900 3550 50  0001 C CNN
F 4 "C17414" H 4900 3550 50  0001 C CNN "LCSC"
F 5 "Y" H 4900 3550 50  0001 C CNN "JLCPCB Add"
F 6 "0.0040" H 4900 3550 50  0001 C CNN "JLCPCB Cost"
	1    4900 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3650 5200 3650
Wire Wire Line
	5400 3800 4900 3800
Wire Wire Line
	4900 3800 4900 3700
$Comp
L power:+5V #PWR015
U 1 1 60D51C08
P 4900 3250
F 0 "#PWR015" H 4900 3100 50  0001 C CNN
F 1 "+5V" H 4900 3390 50  0000 C CNN
F 2 "" H 4900 3250 50  0000 C CNN
F 3 "" H 4900 3250 50  0000 C CNN
	1    4900 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3400 4900 3250
$Comp
L device:C C3
U 1 1 60D575A1
P 4600 3900
F 0 "C3" H 4625 4000 50  0000 L CNN
F 1 "100n" H 4625 3800 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 4638 3750 50  0001 C CNN
F 3 "" H 4600 3900 50  0000 C CNN
F 4 "C49678" H 4600 3900 50  0001 C CNN "LCSC"
F 5 "Y" H 4600 3900 50  0001 C CNN "JLCPCB Add"
F 6 "0.0108" H 4600 3900 50  0001 C CNN "JLCPCB Cost"
	1    4600 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 60D57AC4
P 4600 4200
F 0 "#PWR013" H 4600 3950 50  0001 C CNN
F 1 "GND" H 4600 4050 50  0000 C CNN
F 2 "" H 4600 4200 50  0000 C CNN
F 3 "" H 4600 4200 50  0000 C CNN
	1    4600 4200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 60D57D7F
P 4600 3650
F 0 "#PWR012" H 4600 3500 50  0001 C CNN
F 1 "+5V" H 4600 3790 50  0000 C CNN
F 2 "" H 4600 3650 50  0000 C CNN
F 3 "" H 4600 3650 50  0000 C CNN
	1    4600 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3650 4600 3750
Wire Wire Line
	4600 4050 4600 4200
$Comp
L device:R R1
U 1 1 60D72265
P 3750 1700
F 0 "R1" H 3820 1746 50  0000 L CNN
F 1 "10k" H 3820 1655 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 3680 1700 50  0001 C CNN
F 3 "~" H 3750 1700 50  0001 C CNN
F 4 "C38522" H 3750 1700 50  0001 C CNN "LCSC"
F 5 "Y" H 3750 1700 50  0001 C CNN "JLCPCB Add"
F 6 "0.0045" H 3750 1700 50  0001 C CNN "JLCPCB Cost"
	1    3750 1700
	1    0    0    -1  
$EndComp
$Comp
L device:R R2
U 1 1 60D728FF
P 4050 1700
F 0 "R2" H 4120 1746 50  0000 L CNN
F 1 "10k" H 4120 1655 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 3980 1700 50  0001 C CNN
F 3 "~" H 4050 1700 50  0001 C CNN
F 4 "C17414" H 4050 1700 50  0001 C CNN "LCSC"
F 5 "Y" H 4050 1700 50  0001 C CNN "JLCPCB Add"
F 6 "0.0045" H 4050 1700 50  0001 C CNN "JLCPCB Cost"
	1    4050 1700
	1    0    0    -1  
$EndComp
$Comp
L device:R R5
U 1 1 60D72B52
P 5200 3450
F 0 "R5" H 5270 3496 50  0000 L CNN
F 1 "10k" H 5270 3405 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 5130 3450 50  0001 C CNN
F 3 "~" H 5200 3450 50  0001 C CNN
F 4 "C38522" H 5200 3450 50  0001 C CNN "LCSC"
F 5 "Y" H 5200 3450 50  0001 C CNN "JLCPCB Add"
F 6 "0.0040" H 5200 3450 50  0001 C CNN "JLCPCB Cost"
	1    5200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3950 6600 3950
Wire Wire Line
	6600 3950 6600 4050
Wire Wire Line
	6600 4050 6850 4050
$Comp
L power:+5V #PWR011
U 1 1 60D8BC9A
P 3900 1400
F 0 "#PWR011" H 3900 1250 50  0001 C CNN
F 1 "+5V" H 3900 1550 50  0000 C CNN
F 2 "" H 3900 1400 50  0000 C CNN
F 3 "" H 3900 1400 50  0000 C CNN
	1    3900 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1550 3750 1500
Wire Wire Line
	3750 1500 3900 1500
Wire Wire Line
	4050 1500 4050 1550
Wire Wire Line
	3900 1400 3900 1500
Connection ~ 3900 1500
Wire Wire Line
	3900 1500 4050 1500
Wire Wire Line
	3750 1850 3750 2000
$Comp
L power:GND #PWR024
U 1 1 60DA2F37
P 5400 3150
F 0 "#PWR024" H 5400 2900 50  0001 C CNN
F 1 "GND" H 5400 3000 50  0000 C CNN
F 2 "" H 5400 3150 50  0000 C CNN
F 3 "" H 5400 3150 50  0000 C CNN
	1    5400 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3650 5200 3600
Wire Wire Line
	5200 3300 5200 3100
Wire Wire Line
	5200 3100 5400 3100
Wire Wire Line
	5400 3100 5400 3150
Wire Wire Line
	5300 4700 5300 4100
Wire Wire Line
	5300 4100 5400 4100
Wire Wire Line
	5400 4250 5350 4250
Wire Wire Line
	5350 4250 5350 4850
$Comp
L device:C C2
U 1 1 60DF05EA
P 2700 5200
F 0 "C2" H 2725 5300 50  0000 L CNN
F 1 "100n" H 2725 5100 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 2738 5050 50  0001 C CNN
F 3 "" H 2700 5200 50  0000 C CNN
F 4 "C49678" H 2700 5200 50  0001 C CNN "LCSC"
F 5 "Y" H 2700 5200 50  0001 C CNN "JLCPCB Add"
F 6 "0.0108" H 2700 5200 50  0001 C CNN "JLCPCB Cost"
	1    2700 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2700 5350 2700 5550
Wire Wire Line
	2700 5050 2700 4850
$Comp
L power:GND #PWR01
U 1 1 60E08C58
P 1700 4850
F 0 "#PWR01" H 1700 4600 50  0001 C CNN
F 1 "GND" H 1700 4700 50  0000 C CNN
F 2 "" H 1700 4850 50  0000 C CNN
F 3 "" H 1700 4850 50  0000 C CNN
	1    1700 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4550 1400 4750
Wire Wire Line
	1400 4750 1700 4750
Wire Wire Line
	1950 4750 1950 4350
Wire Wire Line
	1950 4350 2100 4350
Wire Wire Line
	1700 4850 1700 4750
Connection ~ 1700 4750
Wire Wire Line
	1700 4750 1950 4750
Wire Wire Line
	1400 4250 1400 4150
Wire Wire Line
	1400 4150 1800 4150
Wire Wire Line
	1800 4150 1800 3450
Wire Wire Line
	1800 3450 2200 3450
Connection ~ 1800 4150
Wire Wire Line
	1800 4150 2100 4150
Wire Wire Line
	2500 3450 2850 3450
Wire Wire Line
	2850 3450 2850 4250
Wire Wire Line
	2850 4250 2700 4250
Wire Wire Line
	2200 3150 1800 3150
Wire Wire Line
	1800 3150 1800 3450
Connection ~ 1800 3450
Wire Wire Line
	2500 3150 2850 3150
Wire Wire Line
	2850 3150 2850 3450
Connection ~ 2850 3450
$Comp
L power:GND #PWR09
U 1 1 60E3C134
P 3500 4850
F 0 "#PWR09" H 3500 4600 50  0001 C CNN
F 1 "GND" H 3500 4700 50  0000 C CNN
F 2 "" H 3500 4850 50  0000 C CNN
F 3 "" H 3500 4850 50  0000 C CNN
	1    3500 4850
	1    0    0    -1  
$EndComp
Connection ~ 2850 4250
$Comp
L matts_components:ATTINY85-P IC1
U 1 1 60D4B24E
P 7550 1900
F 0 "IC1" H 8700 2087 60  0000 C CNN
F 1 "ATTINY85-P" H 8700 1981 60  0000 C CNN
F 2 "REInnovationFootprint:SM_SOIC_8" H 7650 1150 60  0001 C CNN
F 3 "" H 7550 1900 60  0000 C CNN
	1    7550 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J1
U 1 1 60D4C8E9
P 6300 1550
F 0 "J1" H 6350 1867 50  0000 C CNN
F 1 "ISP" H 6350 1776 50  0000 C CNN
F 2 "REInnovationFootprint:ISP_3x2" H 6300 1550 50  0001 C CNN
F 3 "~" H 6300 1550 50  0001 C CNN
	1    6300 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 2000 10250 2000
Wire Wire Line
	10050 2500 10400 2500
Wire Wire Line
	10400 2500 10400 2450
Connection ~ 10400 2450
Wire Wire Line
	10400 2450 10550 2450
Wire Wire Line
	10400 2550 10400 2500
Connection ~ 10400 2500
$Comp
L power:GND #PWR027
U 1 1 60D7C31D
P 6750 1650
F 0 "#PWR027" H 6750 1400 50  0001 C CNN
F 1 "GND" H 6750 1500 50  0000 C CNN
F 2 "" H 6750 1650 50  0000 C CNN
F 3 "" H 6750 1650 50  0000 C CNN
	1    6750 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 2000 6950 2000
Wire Wire Line
	6950 2000 6950 1550
Wire Wire Line
	6950 1550 6600 1550
Wire Wire Line
	7350 2100 5900 2100
Wire Wire Line
	5900 2100 5900 1450
Wire Wire Line
	5900 1450 6100 1450
Wire Wire Line
	7350 2200 5950 2200
Wire Wire Line
	5950 2200 5950 1550
Wire Wire Line
	5950 1550 6100 1550
Wire Wire Line
	7350 2500 6000 2500
Wire Wire Line
	6000 2500 6000 1650
Wire Wire Line
	6000 1650 6100 1650
Wire Wire Line
	6600 1650 6750 1650
Wire Wire Line
	6600 1450 6750 1450
Wire Wire Line
	6750 1450 6750 1400
Text Notes 7150 1600 0    60   ~ 0
ISP Connections:\n1 - MISO\n2 - Vcc\n3 - SCLK\n4 - MOSI\n5 - Reset\n6 - GND
Text Notes 4350 1700 0    60   ~ 0
ATTiny85 Arduino Pins:\nIC Pin:      Arduino Ref\n1                 5/A0/RST\n2                 3/A3\n3                 4/A2\n4                 GND\n5                 0 - PWM\n6                 1 - PWM\n7                 2/A1\n8                +ve supply
Text HLabel 5600 1950 0    60   Input ~ 0
D0
Text HLabel 5600 2050 0    60   Input ~ 0
D1
Text HLabel 5600 2150 0    60   Input ~ 0
D2
Text HLabel 5600 2250 0    60   Input ~ 0
D3
Text HLabel 5600 2350 0    60   Input ~ 0
D4
Wire Wire Line
	7350 2400 5600 2400
Wire Wire Line
	7350 2300 5600 2300
Wire Wire Line
	5600 2200 5950 2200
Connection ~ 5950 2200
Wire Wire Line
	5600 2100 5900 2100
Connection ~ 5900 2100
Wire Wire Line
	5600 2000 6950 2000
Connection ~ 6950 2000
Text HLabel 3250 2200 0    60   Input ~ 0
SCL_I2C
Text HLabel 3250 2000 0    60   Input ~ 0
SDA_I2C
$Comp
L device:R R6
U 1 1 60DB1C59
P 9200 3400
F 0 "R6" H 9270 3446 50  0000 L CNN
F 1 "330R" H 9270 3355 50  0000 L CNN
F 2 "REInnovationFootprint:SM0805" V 9130 3400 50  0001 C CNN
F 3 "~" H 9200 3400 50  0001 C CNN
F 4 "C237764" H 9200 3400 50  0001 C CNN "LCSC"
F 5 "Y" H 9200 3400 50  0001 C CNN "JLCPCB Add"
F 6 "0.0050" H 9200 3400 50  0001 C CNN "JLCPCB Cost"
	1    9200 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR028
U 1 1 60DB5DD2
P 9200 3100
F 0 "#PWR028" H 9200 2950 50  0001 C CNN
F 1 "+5V" H 9200 3250 50  0000 C CNN
F 2 "" H 9200 3100 50  0000 C CNN
F 3 "" H 9200 3100 50  0000 C CNN
	1    9200 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 3250 9200 3100
Wire Wire Line
	8950 4200 9200 4200
$Comp
L device:LED D1
U 1 1 60DD4F75
P 9200 3800
F 0 "D1" V 9239 3682 50  0000 R CNN
F 1 "LED" V 9148 3682 50  0000 R CNN
F 2 "REInnovationFootprint:SM0805_LED" H 9200 3800 50  0001 C CNN
F 3 "~" H 9200 3800 50  0001 C CNN
F 4 "C2293" H 9200 3800 50  0001 C CNN "LCSC"
F 5 "Y" H 9200 3800 50  0001 C CNN "JLCPCB Add"
F 6 "0.0135" H 9200 3800 50  0001 C CNN "JLCPCB Cost"
	1    9200 3800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9200 4200 9200 3950
Connection ~ 9200 4200
Wire Wire Line
	9200 4200 9250 4200
Wire Wire Line
	9200 3650 9200 3550
Wire Wire Line
	5600 2350 5600 2400
Wire Wire Line
	5600 2250 5600 2300
Wire Wire Line
	5600 2150 5600 2200
Wire Wire Line
	5600 2050 5600 2100
Wire Wire Line
	5600 1950 5600 2000
$Comp
L Amplifier_Operational:TSV911xxLx U1
U 1 1 60E18C60
P 2400 4250
F 0 "U1" H 2744 4296 50  0000 L CNN
F 1 "TSV911xxLx" H 2500 4100 50  0000 L CNN
F 2 "REInnovationFootprint:SM_SOT-23-5" H 2300 4050 50  0001 L CNN
F 3 "www.st.com/resource/en/datasheet/tsv911.pdf" H 2400 4450 50  0001 C CNN
F 4 "C361052" H 2400 4250 50  0001 C CNN "LCSC"
F 5 "Y" H 2400 4250 50  0001 C CNN "JLCPCB Add"
F 6 "0.4576" H 2400 4250 50  0001 C CNN "JLCPCB Cost"
	1    2400 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4700 2300 4550
Wire Wire Line
	2300 3950 2300 3850
$Comp
L power:+5V #PWR02
U 1 1 60E286E2
P 2700 4850
F 0 "#PWR02" H 2700 4700 50  0001 C CNN
F 1 "+5V" H 2700 4990 50  0000 C CNN
F 2 "" H 2700 4850 50  0000 C CNN
F 3 "" H 2700 4850 50  0000 C CNN
	1    2700 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 60E28B67
P 2700 5550
F 0 "#PWR03" H 2700 5300 50  0001 C CNN
F 1 "GND" H 2700 5400 50  0000 C CNN
F 2 "" H 2700 5550 50  0000 C CNN
F 3 "" H 2700 5550 50  0000 C CNN
	1    2700 5550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 60E3FE6C
P 6950 4700
F 0 "J2" H 7030 4692 50  0000 L CNN
F 1 "ADC" H 7030 4601 50  0000 L CNN
F 2 "REInnovationFootprint:SIL-4_large_pad" H 6950 4700 50  0001 C CNN
F 3 "~" H 6950 4700 50  0001 C CNN
	1    6950 4700
	1    0    0    1   
$EndComp
$Comp
L power:+5V #PWR025
U 1 1 60E40773
P 6200 4650
F 0 "#PWR025" H 6200 4500 50  0001 C CNN
F 1 "+5V" H 6200 4800 50  0000 C CNN
F 2 "" H 6200 4650 50  0000 C CNN
F 3 "" H 6200 4650 50  0000 C CNN
	1    6200 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 60E40BB0
P 6550 4850
F 0 "#PWR026" H 6550 4600 50  0001 C CNN
F 1 "GND" H 6550 4700 50  0000 C CNN
F 2 "" H 6550 4850 50  0000 C CNN
F 3 "" H 6550 4850 50  0000 C CNN
	1    6550 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4800 6550 4850
Wire Wire Line
	6200 4650 6200 4700
Wire Wire Line
	6650 4500 6400 4500
Wire Wire Line
	6400 4500 6400 4100
Wire Wire Line
	6400 4100 6200 4100
Wire Wire Line
	6200 4250 6300 4250
Wire Wire Line
	6300 4250 6300 4600
$Comp
L Sensor_Temperature:LM75B U2
U 1 1 60E52C75
P 4350 6600
F 0 "U2" H 4500 7200 50  0000 C CNN
F 1 "LM75B" H 4550 7100 50  0000 C CNN
F 2 "REInnovationFootprint:SM_SOIC_8" H 4350 6600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm75b.pdf" H 4350 6600 50  0001 C CNN
F 4 "C34565" H 4350 6600 50  0001 C CNN "LCSC"
F 5 "Y" H 4350 6600 50  0001 C CNN "JLCPCB Add"
F 6 "0.3457" H 4350 6600 50  0001 C CNN "JLCPCB Cost"
	1    4350 6600
	1    0    0    -1  
$EndComp
Text HLabel 3650 6600 0    60   Output ~ 0
SCL_I2C
Text HLabel 3650 6500 0    60   Output ~ 0
SDA_I2C
Wire Wire Line
	4350 6100 4350 5950
Wire Wire Line
	4350 7200 4350 7100
Wire Wire Line
	3650 6500 3950 6500
Wire Wire Line
	3650 6600 3950 6600
$Comp
L power:GND #PWR016
U 1 1 60E723D1
P 4900 6750
F 0 "#PWR016" H 4900 6500 50  0001 C CNN
F 1 "GND" H 4900 6600 50  0000 C CNN
F 2 "" H 4900 6750 50  0000 C CNN
F 3 "" H 4900 6750 50  0000 C CNN
	1    4900 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 6700 4900 6700
Wire Wire Line
	4900 6700 4900 6750
Wire Wire Line
	4750 6500 4900 6500
Wire Wire Line
	4900 6500 4900 6600
Connection ~ 4900 6700
Wire Wire Line
	4750 6600 4900 6600
Connection ~ 4900 6600
Wire Wire Line
	4900 6600 4900 6700
Wire Wire Line
	6200 3800 7150 3800
Wire Wire Line
	6200 3650 7150 3650
Text Notes 3100 1700 0    60   ~ 0
I2C Pull Up
Wire Wire Line
	3250 2000 3750 2000
Wire Wire Line
	3750 2000 5600 2000
Connection ~ 3750 2000
Connection ~ 5600 2000
Wire Wire Line
	5600 2200 4050 2200
Connection ~ 5600 2200
Wire Wire Line
	4050 1850 4050 2200
Connection ~ 4050 2200
Wire Wire Line
	4050 2200 3250 2200
$Comp
L device:C C4
U 1 1 60EA4E96
P 5300 6550
F 0 "C4" H 5325 6650 50  0000 L CNN
F 1 "100n" H 5325 6450 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 5338 6400 50  0001 C CNN
F 3 "" H 5300 6550 50  0000 C CNN
F 4 "C49678" H 5300 6550 50  0001 C CNN "LCSC"
F 5 "Y" H 5300 6550 50  0001 C CNN "JLCPCB Add"
F 6 "0.0108" H 5300 6550 50  0001 C CNN "JLCPCB Cost"
	1    5300 6550
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR022
U 1 1 60EA551F
P 5300 6300
F 0 "#PWR022" H 5300 6150 50  0001 C CNN
F 1 "+5V" H 5300 6440 50  0000 C CNN
F 2 "" H 5300 6300 50  0000 C CNN
F 3 "" H 5300 6300 50  0000 C CNN
	1    5300 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 60EA5825
P 5300 6800
F 0 "#PWR023" H 5300 6550 50  0001 C CNN
F 1 "GND" H 5300 6650 50  0000 C CNN
F 2 "" H 5300 6800 50  0000 C CNN
F 3 "" H 5300 6800 50  0000 C CNN
	1    5300 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 6800 5300 6700
Wire Wire Line
	5300 6400 5300 6300
NoConn ~ 3950 6700
$Comp
L Connector_Generic:Conn_01x04 P1
U 1 1 60EBFB0A
P 10050 5550
F 0 "P1" H 10050 5800 50  0000 C CNN
F 1 "I2C_OLED" V 10150 5550 50  0000 C CNN
F 2 "REInnovationFootprint:SIL-4_large_pad" H 10050 5550 50  0001 C CNN
F 3 "" H 10050 5550 50  0000 C CNN
	1    10050 5550
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR030
U 1 1 60EBFB10
P 9550 5700
F 0 "#PWR030" H 9550 5450 50  0001 C CNN
F 1 "GND" H 9550 5550 50  0000 C CNN
F 2 "" H 9550 5700 50  0000 C CNN
F 3 "" H 9550 5700 50  0000 C CNN
	1    9550 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR029
U 1 1 60EBFB16
P 9300 5650
F 0 "#PWR029" H 9300 5500 50  0001 C CNN
F 1 "+5V" H 9300 5790 50  0000 C CNN
F 2 "" H 9300 5650 50  0000 C CNN
F 3 "" H 9300 5650 50  0000 C CNN
	1    9300 5650
	1    0    0    -1  
$EndComp
Text HLabel 9150 5450 0    60   Input ~ 0
SCL_I2C
Text HLabel 9150 5350 0    60   Input ~ 0
SDA_I2C
Wire Wire Line
	9300 5650 9450 5650
Wire Wire Line
	9450 5650 9450 5550
Wire Wire Line
	9450 5550 9850 5550
Wire Wire Line
	9550 5650 9550 5700
Wire Wire Line
	9550 5650 9850 5650
Wire Wire Line
	9150 5450 9850 5450
Wire Wire Line
	9150 5350 9850 5350
Connection ~ 5600 2400
Connection ~ 5600 2300
Wire Wire Line
	3250 2100 5600 2100
Connection ~ 5600 2100
Text Notes 1000 5550 0    60   ~ 0
Irradiance sensor + amplifier
Text Notes 8550 6100 0    60   ~ 0
Potential OLED output for a little display?
Text Notes 8800 4650 0    60   ~ 0
Switch/LED combo for \ndata display and user input
Text Notes 6100 5450 0    60   ~ 0
We can measure two more \nanalog pins here, if needed.
Wire Wire Line
	2250 2150 2250 2400
Wire Wire Line
	1250 2150 2250 2150
Wire Wire Line
	2250 2400 3300 2400
Wire Wire Line
	1450 2300 1450 2250
Wire Wire Line
	1450 2300 3300 2300
Wire Wire Line
	1450 2250 1250 2250
Wire Wire Line
	3250 2350 3300 2350
Wire Wire Line
	3300 2350 3300 2300
Connection ~ 3300 2300
Wire Wire Line
	3300 2300 5600 2300
Wire Wire Line
	3250 2450 3300 2450
Wire Wire Line
	3300 2450 3300 2400
Connection ~ 3300 2400
Wire Wire Line
	3300 2400 5600 2400
Wire Wire Line
	3500 4850 5350 4850
Wire Wire Line
	3850 4250 3850 4700
Wire Wire Line
	3850 4700 5300 4700
Wire Wire Line
	2850 4250 3850 4250
Wire Wire Line
	6700 4600 6700 4500
Wire Wire Line
	6700 4500 6750 4500
Wire Wire Line
	6300 4600 6700 4600
Wire Wire Line
	6650 4500 6650 4550
Wire Wire Line
	6650 4550 6750 4550
Wire Wire Line
	6750 4550 6750 4600
Wire Wire Line
	6200 4700 6750 4700
Wire Wire Line
	6550 4800 6750 4800
$EndSCHEMATC
