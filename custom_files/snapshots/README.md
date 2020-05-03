#### Auto create snapshots in HomeAssistant with Node-Red

In HomeAsisstant there is service called **hassio.snapshot_full** and **hassio.snapshot_partial** I assume you know the difference about full vs partial By calling one of the services HomeAssistant will create a snapshot.

Because im doing all the automation things in Node-Red i've also created an automation flow for creating snapshots. 
At this moment, because im still developing every day in HomeAssistant, i've set the automation on every day at 11PM.

![nodered-snapshot-automation](https://user-images.githubusercontent.com/43162899/80915707-5ae5cb80-8d54-11ea-8515-5266d110def7.png)

Node-Red code. Just import this code and you have been set.

    [{"id":"b7aabdac.7c19c","type":"api-call-service","z":"2c3d28e1.93a558","name":"create snapshot full","server":"26a3f650.f38c3a","version":1,"debugenabled":true,"service_domain":"hassio","service":"snapshot_full","entityId":"","data":"","dataType":"json","mergecontext":"","output_location":"","output_location_type":"none","mustacheAltTags":false,"x":410,"y":540,"wires":[["200a1b07.9d7204"]]},{"id":"200a1b07.9d7204","type":"debug","z":"2c3d28e1.93a558","name":"","active":true,"tosidebar":true,"console":false,"tostatus":false,"complete":"false","x":610,"y":540,"wires":[]},{"id":"30357cb7.744fb4","type":"inject","z":"2c3d28e1.93a558","name":"Start at 23:00 every day","topic":"","payload":"It is 23:00, starting full snapshot","payloadType":"str","repeat":"","crontab":"00 23 * * *","once":false,"onceDelay":0.1,"x":150,"y":540,"wires":[["b7aabdac.7c19c"]]},{"id":"26a3f650.f38c3a","type":"server","z":"","name":"Home Assistant","legacy":false,"addon":true,"rejectUnauthorizedCerts":true,"ha_boolean":"y|yes|true|on|home|open","connectionDelay":true,"cacheJson":true}]


#### Auto remove old snapshots in HomeAssistant
Because of missing a HomeAssistant service which is removing snapshots i've created a Python script (see custom_files folder get-latestsnapshot.py) which is removing "old" snapshots (older than 2 days).
The Python is script is listing the backup directory and removes the files. 

I've choosed running the script at 23:30 PM. 
#### Verify if snapshot is created in HomeAssistant
![snapshot-sensor](https://user-images.githubusercontent.com/43162899/80915180-e5c4c700-8d50-11ea-8088-766de2ead586.png)

The Python script also puts some output into textfiles for picking up by HomeAssistant. In these text files the filename and creation date is posted. By picking up these file by HomeAssistant I can use these input as a sensor. See folder Sensors->system.yaml for the whole config. 

```yaml
#Latest snapshot 
- platform: command_line
  name: Latest HA Snapshot date
  command: 'cat /config/custom_files/snapshots/last_snapshotfiledate.txt'

- platform: command_line
  name: Latest HA Snapshot file
  command: 'cat /config/custom_files/snapshots/last_snapshotfilename.txt |  sed "s:.*/::"'

