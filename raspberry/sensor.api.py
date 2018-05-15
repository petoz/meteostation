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

infileInt = '/var/log/mem/sensor.Int.txt'
if os.path.isfile(infileInt):
    infileInt = open(infileInt)
    print "file exist"
    #line1 = infile.readline()
    #line1 = line1.rstrip()
    sensorInt = infileInt.readline()
    sensorInt = sensorInt.rstrip()

#print line1o


infile = '/var/log/mem/sensor.RF.Ext1.txt'
infile = open(infile)
line1 = infile.readline()
line1 = line1.rstrip()
print line1

infile2 = '/var/log/mem/sensor.RF.Ext2.txt'
infile2 = open(infile2)
line2 = infile2.readline()
line2 = line2.rstrip()
print line2

infile3 = '/var/log/mem/sensor.RF.Ext3.txt'
infile3 = open(infile3)
line3 = infile3.readline()
line3 = line3.rstrip()
print line3

casi = int(time.time())
cass = str(casi)
api_string = "http://coffee.onmypc.net/meteotemplate/api.php?"
#full = api_string + line1 + "&TIN=" + str("%.2f" %cTemp) + "&P=" + str("%.2f" %pressure) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&T1=" + str("%.2f" %temp) + "&PASS=" + api_pass
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&T1=" + str("%.2f" %temp) + "&T2=" + str("%.2f" %read_temp()) + "&PASS=" + api_pass
# 9.6.2017 add parameter W,G,B,R,RR,S to disable PHP Notice in page error.log
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&BAT=91.2" + "&TBAT=92.8" + "&T2BAT=95.5" + "&T1=" + str("%.2f" %temp) + "&T2=" + str("%.2f" %read_temp()) + "&PASS=" + api_pass
#sensorRFInt = api_string + cass + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %tempds) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
sensorInt = api_string + sensorInt + "&PASS=" + api_pass
sensorRFExt1 = api_string + line1 + "&PASS=" + api_pass
sensorRFExt2 = api_string + line2 + "&PASS=" + api_pass
sensorRFExt3 = api_string + line3 + "&PASS=" + api_pass
#full = api_string + line1 + line2 + line3 + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %tempds) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
print sensorInt
print sensorRFExt1
print sensorRFExt2
#print sensorRFExt3

response = urllib2.urlopen(sensorInt)
html = response.read()
print html

response = urllib2.urlopen(sensorRFExt1)
html = response.read()
print html

response = urllib2.urlopen(sensorRFExt2)
html = response.read()
print html

#response = urllib2.urlopen(sensorRFExt3)
#html = response.read()
#print html
