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

infileInt = '/var/log/mem/sensor.Int.txt'
tmpfileInt = '/var/log/mem/sensor.Int.tmp.txt'
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
        os.rename(infileInt,tmpfileInt)

infileExt1 = '/var/log/mem/sensor.RF.Ext1.txt'
tmpfileExt1 = '/var/log/mem/sensor.RF.Ext1.tmp.txt'
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
        os.rename(infileExt1,tmpfileExt1)

infileExt2 = '/var/log/mem/sensor.RF.Ext2.txt'
tmpfileExt2 = '/var/log/mem/sensor.RF.Ext2.tmp.txt'
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
        os.rename(infileExt2,tmpfileExt2)

infileExt3 = '/var/log/mem/sensor.RF.Ext3.txt'
tmpfileExt3 = '/var/log/mem/sensor.RF.Ext3.tmp.txt'
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
        os.rename(infileExt3,tmpfileExt3)

infileExt4 = '/var/log/mem/sensor.RF.Ext4.txt'
tmpfileExt4 = '/var/log/mem/sensor.RF.Ext4.tmp.txt'
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
        os.rename(infileExt4,tmpfileExt4)

infileExt5 = '/var/log/mem/sensor.RF.Ext5.txt'
tmpfileExt5 = '/var/log/mem/sensor.RF.Ext5.tmp.txt'
if os.path.isfile(infileExt5):
    sensorExt5 = open(infileExt5)
    sensorExt5 = sensorExt5.readline()
    sensorExt5 = sensorExt5.rstrip()
    sensorExt5 = api_string + sensorExt5 + "&PASS=" + api_pass
    print sensorExt5
    response = urllib2.urlopen(sensorExt5)
    html = response.read()
    print html
    if html == "Success":
        html="success"
        print html
        print 'remove file'
        os.rename(infileExt5,tmpfileExt5)