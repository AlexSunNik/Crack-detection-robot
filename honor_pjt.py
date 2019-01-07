import serial
import numpy as np
from matplotlib import pyplot as plt

def reject_outliers(data, m = 2.):
    d = np.abs(data - np.median(data))
    mdev = np.median(d)
    s = d/mdev if mdev else 0.
    return data[s<m]

"""def reject_outliers(data, m=2):
    return data[abs(data - np.mean(data)) < m * np.std(data)]"""



def data_conv(cur_data):
    cur_int=""
    for i in range(len(cur_data)):
        if cur_data[i].isnumeric():
            cur_int=cur_int+str(cur_data[i])
    return int(cur_int)



ser=serial.Serial('/dev/tty.usbserial-DN041W3Q',9600)

sense1=np.zeros(shape=(90,3))
sense2=np.zeros(shape=(90,3))
sense3=np.zeros(shape=(90,3))
sense4=np.zeros(shape=(90,3))
senseOne=[0]*90;
senseTwo=[0]*90;
senseThree=[0]*90;
senseFour=[0]*90;

oneData=[0]*3;


for i in range(360):
    for j in range(3):
        cur_data=str(ser.readline())
        cur_int=data_conv(cur_data)
        oneData[j]=cur_int
        if j==2:
            if i<=89:
                sense1[i]=np.array(oneData)
            elif i<=179:
                sense2[i-90]=np.array(oneData)
            elif i<=269:
                sense3[i-180]=np.array(oneData)
            else:
                sense4[i-270]=np.array(oneData)
                
"""         
print(sense1)
print(sense2)
print(sense3)
print(sense4)

print(sense1.shape)
print(sense2.shape)
print(sense3.shape)
print(sense4.shape)
"""

for i in range(90):
    senseOne[i]=np.mean(reject_outliers(sense1[i], m = 2.))
    senseTwo[i]=np.mean(reject_outliers(sense2[i], m = 2.))
    senseThree[i]=np.mean(reject_outliers(sense3[i], m = 2.))
    senseFour[i]=np.mean(reject_outliers(sense4[i], m = 2.))
    

print(senseOne)  
print(senseTwo)
print(senseThree)
print(senseFour)

theta=range(360)
r=senseOne+senseTwo+senseThree+senseFour
r=[x+2 for x in r]

plt.figure()
plt.polar(theta,r)
plt.ion()
plt.title('Graph shown in polar coordinate axes')
