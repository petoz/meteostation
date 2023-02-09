import os
import urllib2

with open("/root/api_pass_dev") as f:
    api_pass = f.readline().rstrip()
api_string = "https://meteo.usemy.cloud/api.php?"

def process_file(file_path, tmp_file_path):
    if os.path.isfile(file_path):
        with open(file_path) as f:
            sensor_data = f.readline().rstrip()
            sensor_data = api_string + sensor_data + "&PASS=" + api_pass
            response = urllib2.urlopen(sensor_data)
            html = response.read()
            if html == "Success":
		print html
		print sensor_data
                os.rename(file_path, tmp_file_path)

process_file("/var/log/mem/sensor.Int.txt", "/var/log/mem/sensor.Int.tmp.txt")
process_file("/var/log/mem/sensor.RF.Ext1.txt", "/var/log/mem/sensor.RF.Ext1.tmp.txt")
process_file("/var/log/mem/sensor.RF.Ext2.txt", "/var/log/mem/sensor.RF.Ext2.tmp.txt")
process_file("/var/log/mem/sensor.RF.Ext3.txt", "/var/log/mem/sensor.RF.Ext3.tmp.txt")
process_file("/var/log/mem/sensor.RF.Ext4.txt", "/var/log/mem/sensor.RF.Ext4.tmp.txt")

