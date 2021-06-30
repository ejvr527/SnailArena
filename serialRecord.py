import serial
import numpy as np
import time
import datetime;
import sys

uno='/dev/ttyACM0'
pico='/dev/ttyACM0'
nano='/dev/ttyUSB0'
ser = serial.Serial(
    port=nano,
    baudrate=115200,
    timeout=1
)

fname = sys.argv[1]
hold = []
i=0;
while True:
    line = ser.readline()
    line=line.decode("utf8",errors='ignore').rstrip("\n\r")
    print(line)
    if line!="" and line!=" ":
        process=line.split(",")
        a=[]
        for i in range(len(process)):
            a.append(float(process[i]))
        print("a:",a)
        hold.append(a);
        i=i+1;
    # if line.strip():
    #     try:
            
    #         i=i+1
    # #         if line!='':
    # #             hold.append(float(line))
    # #             # print(len(hold))
    # #     # except ValueError:
    # #     #     print("value error")
    if i>=1:
        f=open(fname+'.txt','ab')
        np.savetxt(f,hold)
        f.close()