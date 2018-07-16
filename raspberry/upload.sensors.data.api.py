#!/usr/bin/python

import os
import urllib2

#password file for api
api_pass_file = '/root/api_pass'
api_pass_file = open(api_pass_file)
api_pass = api_pass_file.readline()
api_pass = api_pass.rstrip()
print api_pass
#api_string = "http://coffee.onmypc.net/meteotemplate/api.php?"
api_string = "https://www.usemy.cloud/meteotemplate/api.php?"

infileInt = "/var/log/mem/sensor.Int.txt"
if os.path.isfile(infileInt):
    sensorInt = open(infileInt)
    sensorInt = sensorInt.readline()
    sensorInt = sensorInt.rstrip()
    sensorInt = api_string + sensorInt + "&PASS=" + api_pass
    print sensorInt
    response = urllib2.urlopen(sensorInt)
    html = response.read()
    print html
    if html == "Success":
        html="success"
        print html
        print 'remove file'
        #os.remove(infileInt)


infileExt1 = '/var/log/mem/sensor.RF.Ext1.txt'
if os.path.isfile(infileExt1):
    sensorExt1 = open(infileExt1)
    sensorExt1 = sensorExt1.readline()
    sensorExt1 = sensorExt1.rstrip()
    sensorExt1 = api_string + sensorExt1 + "&PASS=" + api_pass
    print sensorExt1
    response = urllib2.urlopen(sensorExt1)
    html = response.read()
    print html
    if html == "Success":
        html="success"
        print html
        print 'remove file'
        #os.remove(infileExt1)

infileExt2 = '/var/log/mem/sensor.RF.Ext2.txt'
if os.path.isfile(infileExt2):
    sensorExt2 = open(infileExt2)
    sensorExt2 = sensorExt2.readline()
    sensorExt2 = sensorExt2.rstrip()
    sensorExt2 = api_string + sensorExt2 + "&PASS=" + api_pass
    print sensorExt2
    response = urllib2.urlopen(sensorExt2)
    html = response.read()
    print html
    if html == "Success":
        html="success"
        print html
        print 'remove file'
        #os.remove(infileExt2)

infileExt3 = '/var/log/mem/sensor.RF.Ext3.txt'
if os.path.isfile(infileExt3):
    sensorExt3 = open(infileExt3)
    sensorExt3 = sensorExt3.readline()
    sensorExt3 = sensorExt3.rstrip()
    sensorExt3 = api_string + sensorExt3 + "&PASS=" + api_pass
    print sensorExt3
    response = urllib2.urlopen(sensorExt3)
    html = response.read()
    print html
    if html == "Success":
        html="success"
        print html
        print 'remove file'
<<<<<<< HEAD
        #os.remove(infileExt3)
=======
        os.remove(infileExt3)

infileExt4 = '/var/log/mem/sensor.RF.Ext4.txt'
if os.path.isfile(infileExt4):
    sensorExt4 = open(infileExt4)
    sensorExt4 = sensorExt4.readline()
    sensorExt4 = sensorExt4.rstrip()
    sensorExt4 = api_string + sensorExt4 + "&PASS=" + api_pass
    print sensorExt4
    response = urllib2.urlopen(sensorExt4)
    html = response.read()
    print html
    if html == "Success":
        html="success"
        print html
        print 'remove file'
        os.remove(infileExt4)

>>>>>>> devel_2
