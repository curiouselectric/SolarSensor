EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 8200 3550 2    60   Output ~ 0
SCL_I2C
Text HLabel 8200 3650 2    60   Output ~ 0
SDA_I2C
$Comp
L device:R R1
U 1 1 60FA8084
P 3550 3000
F 0 "R1" V 3630 3000 50  0000 C CNN
F 1 "47k" V 3550 3000 50  0000 C CNN
F 2 "REInnovationFootprint:SM0805" V 3480 3000 50  0001 C CNN
F 3 "" H 3550 3000 50  0000 C CNN
F 4 "C17713" H 3550 3000 50  0001 C CNN "LCSC"
F 5 "Y" H 3550 3000 50  0001 C CNN "JLCPCB Add"
F 6 "0.0040" H 3550 3000 50  0001 C CNN "JLCPCB Cost"
	1    3550 3000
	0    1    1    0   
$EndComp
Text Notes 4150 3050 0    60   ~ 0
0.1% precision \nresistor
$Comp
L device:D_Photo D1
U 1 1 60FA80A1
P 2600 4000
F 0 "D1" H 2450 4100 50  0000 C CNN
F 1 "PHOTO DIODE" H 2700 3900 50  0000 C CNN
F 2 "REInnovationFootprint:TH_LED-5MM_larg_pad" H 2600 4000 50  0001 C CNN
F 3 "" H 2600 4000 50  0000 C CNN
F 4 "~" H 2600 4000 60  0000 C CNN "Notes"
F 5 "~" H 2600 4000 60  0001 C CNN "Description"
F 6 "~" H 2600 4000 60  0001 C CNN "Manufacturer"
F 7 "~" H 2600 4000 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 2600 4000 60  0001 C CNN "Supplier 1"
F 9 "~" H 2600 4000 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 2600 4000 60  0001 C CNN "Supplier 1 Cost"
F 11 "~" H 2600 4000 60  0001 C CNN "Supplier 2"
F 12 "~" H 2600 4000 60  0001 C CNN "Supplier 2 Part No"
F 13 "~" H 2600 4000 60  0001 C CNN "Supplier 2 Cost"
	1    2600 4000
	0    1    1    0   
$EndComp
$Comp
L device:C C1
U 1 1 60FA80AA
P 3550 2700
F 0 "C1" H 3575 2800 50  0000 L CNN
F 1 "10n" H 3575 2600 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 3588 2550 50  0001 C CNN
F 3 "" H 3550 2700 50  0000 C CNN
F 4 "C107135" H 3550 2700 50  0001 C CNN "LCSC"
F 5 "Y" H 3550 2700 50  0001 C CNN "JLCPCB Add"
F 6 "0.0105" H 3550 2700 50  0001 C CNN "JLCPCB Cost"
	1    3550 2700
	0    1    1    0   
$EndComp
Text Notes 7800 4250 0    60   ~ 0
16 Bit ADC
$Comp
L device:C C3
U 1 1 60FA80D1
P 5800 3450
F 0 "C3" H 5825 3550 50  0000 L CNN
F 1 "100n" H 5825 3350 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 5838 3300 50  0001 C CNN
F 3 "" H 5800 3450 50  0000 C CNN
F 4 "C49678" H 5800 3450 50  0001 C CNN "LCSC"
F 5 "Y" H 5800 3450 50  0001 C CNN "JLCPCB Add"
F 6 "0.0108" H 5800 3450 50  0001 C CNN "JLCPCB Cost"
	1    5800 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3200 5800 3300
Wire Wire Line
	5800 3600 5800 3750
$Comp
L device:C C2
U 1 1 60FA8102
P 3900 4750
F 0 "C2" H 3925 4850 50  0000 L CNN
F 1 "100n" H 3925 4650 50  0000 L CNN
F 2 "REInnovationFootprint:SM_C_0805" H 3938 4600 50  0001 C CNN
F 3 "" H 3900 4750 50  0000 C CNN
F 4 "C49678" H 3900 4750 50  0001 C CNN "LCSC"
F 5 "Y" H 3900 4750 50  0001 C CNN "JLCPCB Add"
F 6 "0.0108" H 3900 4750 50  0001 C CNN "JLCPCB Cost"
	1    3900 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 4900 3900 5100
Wire Wire Line
	3900 4600 3900 4400
Wire Wire Line
	2600 4100 2600 4300
Wire Wire Line
	2600 4300 2900 4300
Wire Wire Line
	3150 4300 3150 3900
Wire Wire Line
	3150 3900 3300 3900
Wire Wire Line
	2900 4400 2900 4300
Connection ~ 2900 4300
Wire Wire Line
	2900 4300 3150 4300
Wire Wire Line
	2600 3800 2600 3700
Wire Wire Line
	2600 3700 3000 3700
Wire Wire Line
	3000 3700 3000 3000
Wire Wire Line
	3000 3000 3400 3000
Connection ~ 3000 3700
Wire Wire Line
	3000 3700 3300 3700
Wire Wire Line
	3700 3000 4050 3000
Wire Wire Line
	4050 3000 4050 3800
Wire Wire Line
	4050 3800 3900 3800
Wire Wire Line
	3400 2700 3000 2700
Wire Wire Line
	3000 2700 3000 3000
Connection ~ 3000 3000
Wire Wire Line
	3700 2700 4050 2700
Wire Wire Line
	4050 2700 4050 3000
Connection ~ 4050 3000
Connection ~ 4050 3800
$Comp
L Amplifier_Operational:TSV911xxLx U1
U 1 1 60FA8130
P 3600 3800
AR Path="/60FA8130" Ref="U1"  Part="1" 
AR Path="/60F87947/60FA8130" Ref="U1"  Part="1" 
F 0 "U1" H 3944 3846 50  0000 L CNN
F 1 "TSV911xxLx" H 3700 3650 50  0000 L CNN
F 2 "REInnovationFootprint:SM_SOT-23-5" H 3500 3600 50  0001 L CNN
F 3 "www.st.com/resource/en/datasheet/tsv911.pdf" H 3600 4000 50  0001 C CNN
F 4 "C361052" H 3600 3800 50  0001 C CNN "LCSC"
F 5 "Y" H 3600 3800 50  0001 C CNN "JLCPCB Add"
F 6 "0.4576" H 3600 3800 50  0001 C CNN "JLCPCB Cost"
	1    3600 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4250 3500 4100
Wire Wire Line
	3500 3500 3500 3400
$Comp
L Connector_Generic:Conn_01x04 P8
U 1 1 60FA8144
P 7450 5250
F 0 "P8" H 7530 5242 50  0000 L CNN
F 1 "ADC" H 7530 5151 50  0000 L CNN
F 2 "REInnovationFootprint:SIL-4_large_pad" H 7450 5250 50  0001 C CNN
F 3 "~" H 7450 5250 50  0001 C CNN
	1    7450 5250
	1    0    0    1   
$EndComp
Wire Wire Line
	7050 5350 7050 5400
Wire Wire Line
	7150 5050 6900 5050
Text Notes 2200 5100 0    60   ~ 0
Irradiance sensor + amplifier
Text Notes 7800 5250 0    60   ~ 0
We can measure one more \nanalog diff input here, if needed.
Wire Wire Line
	4700 4400 6550 4400
Wire Wire Line
	5050 3800 5050 4250
Wire Wire Line
	5050 4250 6500 4250
Wire Wire Line
	4050 3800 5050 3800
Wire Wire Line
	7200 5150 7200 5050
Wire Wire Line
	7200 5050 7250 5050
Wire Wire Line
	6800 5150 7200 5150
Wire Wire Line
	7150 5050 7150 5100
Wire Wire Line
	7150 5100 7250 5100
Wire Wire Line
	7250 5100 7250 5150
Wire Wire Line
	6700 5250 7250 5250
Wire Wire Line
	7050 5350 7250 5350
Text HLabel 3900 4400 2    60   Input ~ 0
Vcc
Text HLabel 3900 5100 2    60   Input ~ 0
GND
Text HLabel 3500 4250 2    60   Input ~ 0
GND
Text HLabel 2900 4400 2    60   Input ~ 0
GND
Text HLabel 7500 4300 3    60   Input ~ 0
GND
Text HLabel 4700 4400 0    60   Input ~ 0
GND
Text HLabel 7050 5400 0    60   Input ~ 0
GND
Text HLabel 5800 3750 0    60   Input ~ 0
GND
Text HLabel 3500 3400 2    60   Input ~ 0
Vcc
Text HLabel 5800 3200 0    60   Input ~ 0
Vcc
Text HLabel 6700 5250 0    60   Input ~ 0
Vcc
$Comp
L Analog_ADC:MCP3426-xSN U2
U 1 1 60F55AC8
P 7500 3750
F 0 "U2" H 7200 4350 50  0000 C CNN
F 1 "MCP3426-xSN" H 7100 4250 50  0000 C CNN
F 2 "REInnovationFootprint:SM_SOIC_8" H 7500 3750 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22226a.pdf" H 7500 3750 50  0001 C CNN
	1    7500 3750
	1    0    0    -1  
$EndComp
Text HLabel 7500 3150 1    60   Input ~ 0
Vcc
Wire Wire Line
	7100 3550 6500 3550
Wire Wire Line
	6500 3550 6500 4250
Wire Wire Line
	7100 3650 6550 3650
Wire Wire Line
	6550 3650 6550 4400
Wire Wire Line
	7100 3850 6900 3850
Wire Wire Line
	6900 3850 6900 5050
Wire Wire Line
	7100 3750 6800 3750
Wire Wire Line
	6800 3750 6800 5150
Wire Wire Line
	7500 3350 7500 3150
Wire Wire Line
	7500 4300 7500 4050
Wire Wire Line
	7900 3550 8200 3550
Wire Wire Line
	7900 3650 8200 3650
$EndSCHEMATC
