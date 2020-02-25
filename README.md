# Home Automation with Docker and Postgres on RaspberryPI and AzureVM.
In the basics my environment has the following configuration:

Local environment:
Hardware:
- Raspberry PI 3b+ with 16GB SD
- Philips HUE Gateway
- Tado Gateway
- Wireless Zigbee CC2531 Sniffer Bare Board
- FTDI FT232RL USB To TTL Serial IC Adapter Converter Module 

Devices: 
- Philips HUE Lightbulbs
- Tado Thermostat
- Tado Smart Radiator
- IKEA Tradfri Lightbulbs
- IKEA Tradfri Motion Sensor
- Xiaomi Aqara Door Window / Door Sensor Zigbee 
- NEO Coolcam Smart Plug WiFi Socket 3680W 16A (deprecated)

RPI:
- Docker
  - Home Assistant (Hass.io)
  - DSMR-Reader ([Docker install](https://github.com/xirixiz/dsmr-reader-docker))
  - Portainer ([Installation](https://www.portainer.io/installation/))
- Strongswan ([Website](https://strongswan.org/))

Azure Environment
VM: Ubuntu 18.04 size B2s, standard, 2vCPU, 4GB mem
- Docker
  - Portainer
  - Postgres
  - PostgresAdmin

For setting up the VPN i used the following steps:
Update first
```
$ apt update && sudo apt upgrade -y 
$ apt install strongswan -y
```
Set kernel parameters
```
$ cat >> /etc/sysctl.conf << EOF 
net.ipv4.ip_forward = 1 
net.ipv4.conf.all.accept_redirects = 0 
net.ipv4.conf.all.send_redirects = 0 EOF 
$ sysctl -p /etc/sysctl.conf
```
# Used Home Assistant Components
- https://github.com/custom-cards/button-card
- https://github.com/kalkih/mini-graph-card
- https://github.com/thomasloven/lovelace-card-mod
- https://github.com/nervetattoo/simple-thermostat
- https://github.com/USA-RedDragon/badnest

Icons: [http://materialdesignicons.com/](http://materialdesignicons.com/)

