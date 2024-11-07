import serial
import time
import pandas as pd
import urllib3

apiRequest="https://api.thingspeak.com/update?api_key=7UOUM1MEV2C3ZBGT&field1="

# define serial object
node=serial.Serial("/dev/ttyACM0",9600,timeout=0.5)
dataset=[] # global list
count=0 # check the batch size
while True:
    try:
        if(node.inWaiting()>0):
            data=node.readline() # reading line of data from nodata=data.decode('utf-8') # it will convert bytes data into str
            #print(data)
            data=data.decode('utf-8')
            data=data.split(",") # split the data with seperator
            h=float(data[1]) # data[1] is humidity
            t=float(data[2]) # data[2] is temp
            m=int(data[3]) # data[3] is moisture
            n=int(data[4]) # data[4] is nitrogen
            p=int(data[5]) # data[5] is p value
            k=int(data[6]) # data[6] is k value
            http=urllib3.PoolManager()
            response=http.request('GET',apiRequest+str(h)+'&field2='+str(t)+'&field3='+str(m)+'&field4='+str(n)+'&field5='+str(p)+'&field6='+str(k))
            print(response.text)
            time.sleep(15)
            dummy=[h,t,m,n,p,k] # store 6 values in the list
            count+=1
            dataset.append(dummy) # [[]]
            print(dataset)
            if(count==10):
                df=pd.DataFrame(dataset)
                df.to_csv('sensoryfeed.csv')
                count=0
    except:
        continue
