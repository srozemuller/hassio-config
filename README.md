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
  - DSMR-Reader
  - Portainer
- Strongswan 

Azure Environment
VM: Ubuntu 18.04 size B2s, standard, 2vCPU, 4GB mem
- Docker
  - Portainer
  - Postgres
  - PostgresAdmin
Configured VPN connection to local.


#Used Home Assistant Components
- https://github.com/custom-cards/button-card
- https://github.com/kalkih/mini-graph-card


The environment has three different behaviours.
- full automation
- vacation mode (default mode)
- manual mode


```javascript
{
	position: [0, 0],
	width: 1,
	title: 'Modus',
	classes: [CLASS_BIG],
	type: TYPES.INPUT_BOOLEAN,
	id: 'input_boolean.turn_on_vacationmode',
	icons: {
	  on: 'mdi-caravan',
	  off: 'mdi-home'
	},
	states: {
	  on: "Vakantie",
	  off: "Home"
	},
	customStyles: function (item, entity) {
	        if (entity.state == 'on') {
	            return {
	                'background': '#E3655B',
	                //'filter': 'grayscale()',
	            };
	        }
	         else {
	            return {
	                'background': '#5B8C5A',
	                //'filter': 'grayscale()',
	            };
	        }
	    },
},
```
![Alt text](https://github.com/srozemuller/HomeAssistant/blob/master/www/tileboard/images/screenshots/vacation.png?raw=true "Vacation mode")
![Alt text](https://github.com/srozemuller/HomeAssistant/blob/master/www/tileboard/images/screenshots/home.png?raw=true "Home mode")

