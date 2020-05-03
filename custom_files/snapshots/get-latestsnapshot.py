import os
import time
from datetime import datetime
#directory = '/usr/share/hassio/backup/'
path = '/usr/share/hassio/backup/'

name_list = os.listdir(path)
full_list = [os.path.join(path,i) for i in name_list]
time_sorted_list = sorted(full_list, key=os.path.getmtime)
latest_file = max(full_list, key=os.path.getctime)

#print time_sorted_list
for filename in time_sorted_list:
    today = datetime.today()
    #print(filename)
    creation_date =time.ctime(os.path.getctime(filename))
    file_date = datetime.strptime(creation_date,'%a %b %d %H:%M:%S %Y')
    diff = today - file_date
    if diff.days > 2:
        print "File: " ,filename , "created at: " , creation_date, "thats " , diff.days,  "days ago and needs to be deleted"  
        os.remove(filename)

    #print "File: " ,filename , "created at: " , creation_date, "thats " , diff.days,  "days ago"  

writeToFile = open("last_snapshotfilename.txt","w") 
writeToFile.write(latest_file) 
writeToFile.close()
writeToFile = open("last_snapshotfiledate.txt","w") 
writeToFile.write(str(file_date)) 
writeToFile.close()

writeToFile = open("last_snapshot.txt","w") 
writeToFile.write(str(diff.days)) 
writeToFile.close()