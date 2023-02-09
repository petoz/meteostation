import smbus2
import bmp280

port = 1
address = 0x76
bus = smbus2.SMBus(port)

bmp280_sensor = bmp280.BMP280(i2c_dev=bus)

temperature = bmp280_sensor.get_temperature()
pressure = bmp280_sensor.get_pressure()


print("teplota{:.2f}C".format(temperature))
