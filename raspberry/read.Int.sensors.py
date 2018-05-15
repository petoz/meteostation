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

outfile = '/var/log/mem/sensor.RF.Int.txt'
outfile = open(outfile,'w')
#line1 = infile.readline()
#line1 = line1.rstrip()
#print line1

casi = int(time.time())
cass = str(casi)
api_string = "http://coffee.onmypc.net/meteotemplate/api.php?"
#full = api_string + line1 + "&TIN=" + str("%.2f" %cTemp) + "&P=" + str("%.2f" %pressure) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&T1=" + str("%.2f" %temp) + "&PASS=" + api_pass
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&T1=" + str("%.2f" %temp) + "&T2=" + str("%.2f" %read_temp()) + "&PASS=" + api_pass
# 9.6.2017 add parameter W,G,B,R,RR,S to disable PHP Notice in page error.log
#full = api_string + line1 + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %cTemp) + "&HIN=" + str("%.2f" %hum) + "&BAT=91.2" + "&TBAT=92.8" + "&T2BAT=95.5" + "&T1=" + str("%.2f" %temp) + "&T2=" + str("%.2f" %read_temp()) + "&PASS=" + api_pass
#sensorRFInt = api_string + "U=" + cass + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %tempds) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
sensorRFInt = "U=" + cass + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %tempds) + "&HIN=" + str("%.2f" %hum)
#full = api_string + line1 + line2 + line3 + "&P=" + str("%.2f" %pressure) + "&W=0.0&G=0.0&B=0&R=0.0&RR=0.0&S=0.0" + "&TIN=" + str("%.2f" %tempds) + "&HIN=" + str("%.2f" %hum) + "&PASS=" + api_pass
#dd
print sensorRFInt
#print (sensorRFInt,outfile)
outfile.write(sensorRFInt)
outfile.close()
#response = urllib2.urlopen(sensorRFInt)
#html = response.read()
#print html
#if html == "Success":
#  html="success"
#  print 'remove file'
#  outfile.close()
#  os.remove("/var/log/mem/sensor.RF.Int.txt")
#print "end"
