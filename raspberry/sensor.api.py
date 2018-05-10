#!/usr/bin/python

import Adafruit_DHT
import time
import smbus
import os
import urllib2
import math

#password file for api
api_pass_file = '/root/api_pass'
api_pass_file = open(api_pass_file)
api_pass = api_pass_file.readline()
api_pass = api_pass.rstrip()
print api_pass

#infile = '/home/pi/outtemp.txt'
infile = '/var/log/mem/sensor.RF.Ext1.txt'
infile = open(infile)
line1 = infile.readline()
line1 = line1.rstrip()
print line1

infile2 = '/var/log/mem/sensrf2.txt'
infile2 = open(infile2)
line2 = infile2.readline()
line2 = line2.rstrip()
print line2

infile3 = '/var/log/mem/sensrf3.txt'
infile3 = open(infile3)
line3 = infile3.readline()
line3 = line3.rstrip()
print line3

device_file = '/sys/bus/w1/devices/28-0516b36044ff/w1_slave'  #konkretny subor kde je teplota z ds18b20

hum,temp = Adafruit_DHT.read_retry(22, 17)
print "Teplota:",("%0.2f" %temp)
print "Vlhkost:",("%0.2f" %hum)


# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# BMP280
# This code is designed to work with the BMP280_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Barometer?sku=BMP280_I2CSs#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# BMP280 address, 0x76(118)
# Read data back from 0x88(136), 24 bytes
b1 = bus.read_i2c_block_data(0x76, 0x88, 24)

# Convert the data
# Temp coefficents
dig_T1 = b1[1] * 256 + b1[0]
dig_T2 = b1[3] * 256 + b1[2]
if dig_T2 > 32767 :
    dig_T2 -= 65536
dig_T3 = b1[5] * 256 + b1[4]
if dig_T3 > 32767 :
    dig_T3 -= 65536

# Pressure coefficents
dig_P1 = b1[7] * 256 + b1[6]
dig_P2 = b1[9] * 256 + b1[8]
if dig_P2 > 32767 :
    dig_P2 -= 65536
dig_P3 = b1[11] * 256 + b1[10]
if dig_P3 > 32767 :
    dig_P3 -= 65536
dig_P4 = b1[13] * 256 + b1[12]
if dig_P4 > 32767 :
    dig_P4 -= 65536
dig_P5 = b1[15] * 256 + b1[14]
if dig_P5 > 32767 :
    dig_P5 -= 65536
dig_P6 = b1[17] * 256 + b1[16]
if dig_P6 > 32767 :
    dig_P6 -= 65536
dig_P7 = b1[19] * 256 + b1[18]
if dig_P7 > 32767 :
    dig_P7 -= 65536
dig_P8 = b1[21] * 256 + b1[20]
if dig_P8 > 32767 :
    dig_P8 -= 65536
dig_P9 = b1[23] * 256 + b1[22]
if dig_P9 > 32767 :
    dig_P9 -= 65536

# BMP280 address, 0x76(118)
# Select Control measurement register, 0xF4(244)
#               0x27(39)        Pressure and Temperature Oversampling rate = 1
#                                       Normal mode
bus.write_byte_data(0x76, 0xF4, 0x27)
# BMP280 address, 0x76(118)
# Select Configuration register, 0xF5(245)
#               0xA0(00)        Stand_by time = 1000 ms
bus.write_byte_data(0x76, 0xF5, 0xA0)

time.sleep(0.5)

# BMP280 address, 0x76(118)
# Read data back from 0xF7(247), 8 bytes
# Pressure MSB, Pressure LSB, Pressure xLSB, Temperature MSB, Temperature LSB
# Temperature xLSB, Humidity MSB, Humidity LSB
data = bus.read_i2c_block_data(0x76, 0xF7, 8)

# Convert pressure and temperature data to 19-bits
adc_p = ((data[0] * 65536) + (data[1] * 256) + (data[2] & 0xF0)) / 16
adc_t = ((data[3] * 65536) + (data[4] * 256) + (data[5] & 0xF0)) / 16

# Temperature offset calculations
var1 = ((adc_t) / 16384.0 - (dig_T1) / 1024.0) * (dig_T2)
var2 = (((adc_t) / 131072.0 - (dig_T1) / 8192.0) * ((adc_t)/131072.0 - (dig_T1)/8192.0)) * (dig_T3)
t_fine = (var1 + var2)
cTemp = (var1 + var2) / 5120.0
fTemp = cTemp * 1.8 + 32

# Pressure offset calculations
var1 = (t_fine / 2.0) - 64000.0
var2 = var1 * var1 * (dig_P6) / 32768.0
var2 = var2 + var1 * (dig_P5) * 2.0

var2 = (var2 / 4.0) + ((dig_P4) * 65536.0)
var1 = ((dig_P3) * var1 * var1 / 524288.0 + ( dig_P2) * var1) / 524288.0
var1 = (1.0 + var1 / 32768.0) * (dig_P1)
p = 1048576.0 - adc_p
p = (p - (var2 / 4096.0)) * 6250.0 / var1
var1 = (dig_P9) * p * p / 2147483648.0
var2 = p * (dig_P8) / 32768.0
pressure = (p + (var1 + var2 + (dig_P7)) / 16.0) / 100

#citanie teploty z ds18b20
def read_temp_raw():
 f = open(device_file, 'r')
 lines = f.readlines()
 f.close()
 return lines

def read_temp():
 lines = read_temp_raw()
 while lines[0].strip()[-3:] != 'YES':
  time.sleep(0.2)
  lines = read_temp_raw()
 equals_pos = lines[1].find('t=')
 if equals_pos != -1:
  temp_string = lines[1][equals_pos+2:]
  temp_c = float(temp_string) / 1000.0
  return temp_c

tempds = read_temp()
print "dstemp=" + str(tempds)
print "ds18b20=" + str(read_temp())
tempds = read_temp()
print "dstemp=" + str(tempds)


# Output data to screen
print "Temperature in Celsius : %.2f C" %cTemp
#print "Temperature in Fahrenheit : %.2f F" %fTemp
print "Pressure : %.2f hPa " %pressure

#pressure = pressure + 355/9.2	//aproximate
h=355
g=9.80665
M=0.0289644
R=8.31447
#TK=cTemp+273.15-17
TK=288.15
gmh=g*M*h

print "gmh=",gmh
RTK=R*TK
print "RTK=",RTK
gmhrtk=gmh/RTK
print "gmh/rtk=",gmhrtk
pressure = pressure * math.exp(gmhrtk)

casi = int(time.time())
cass = str(casi)
api_string = "http://coffee.onmypc.net/meteotemplate/api.php?"
#full = api_string + line1 + "&TIN=" + str("%.2f" %cTemp) + "&P=" + str("%.2f" %pressure) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&T1=" + str("%.2f" %temp) + "&PASS=" + api_pass
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&T1=" + str("%.2f" %temp) + "&T2=" + str("%.2f" %read_temp()) + "&PASS=" + api_pass
# 9.6.2017 add parameter W,G,B,R,RR,S to disable PHP Notice in page error.log
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&BAT=91.2" + "&TBAT=92.8" + "&T2BAT=95.5" + "&T1=" + str("%.2f" %temp) + "&T2=" + str("%.2f" %read_temp()) + "&PASS=" + api_pass
#full = api_string + line1 + line2 + line3 + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %tempds) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
sensorRFExt1 = api_string + line1
print sensorRFExt1
response = urllib2.urlopen(sensorRFExt1)
html = response.read()
print html
#
