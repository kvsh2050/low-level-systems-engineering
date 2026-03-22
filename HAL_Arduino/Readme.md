## Programming 

1. For blinking led in the arduino 



## For Compilation 
1. avr compiler to convert the .c to .hex or .bin 
```
avr 
```

## For serial monitor 
In linux(ubuntu) check these:
1. Find the port name on which the Arduino is connected to 
```
lsusb 
```
2. Find the port in the /dev/* and check for the port on it
```
ls /dev/ttyACM0
```
3. Connect to arduino using picocom 
```
picocom /dev/ttyACM0 -b 115200
```
4. The picocom prints serial messages 

## For Flashing
```
avrdude -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:blink.hex:i
```

