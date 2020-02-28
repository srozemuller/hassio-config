
# Home Automation with Docker and Postgres on RaspberryPI and AzureVM.

In the basics my environment has the following configuration

  

![hassioversion](https://img.shields.io/badge/hassio-0.105.3-blue) ![reposize](https://img.shields.io/github/repo-size/srozemuller/hassio-config) ![lastcommit](https://img.shields.io/github/last-commit/srozemuller/hassio-config)

#### Local:

-  [Raspberry PI 3b+ with 16GB SD](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)

-  [Philips HUE](https://www2.meethue.com/)

-  [Tado Gateway](https://www.tado.com/)

-  [Wireless Zigbee CC2531 Sniffer Bare Board](https://nl.aliexpress.com/item/32950799594.html?spm=a2g0s.9042311.0.0.44264c4dMfEXKg)

-  [FTDI FT232RL USB To TTL Serial IC Adapter Converter Module](https://nl.aliexpress.com/item/32648158894.html?spm=a2g0s.9042311.0.0.27424c4dh5Tr07)

  

##### Devices:

- Philips HUE Lightbulbs

- Tado Thermostat

- Tado Smart Radiator

- IKEA Tradfri Lightbulbs

-  [IKEA Trafri Motion Sensor](https://www.ikea.com/nl/nl/p/tradfri-draadloze-bewegingssensor-wit-70429913/)

-  [XIAOMI Door/ Window Sensor](https://nl.aliexpress.com/item/32991903307.html?spm=a2g0s.9042311.0.0.6afb4c4dopldDg)

-  [NEO Coolcam Smart Plug 16A](https://www.aliexpress.com/snapshot/0.html?spm=a2g0s.9042311.0.0.6afb4c4dopldDg&orderId=8004619814437739&productId=32966183521)

  

##### RPI:

-  [Docker](https://www.docker.com)

-  [Hass.io](https://www.hass.io)

-  [DSMR-Reader](https://github.com/xirixiz/dsmr-reader-docker)

-  [Portainer](https://www.portainer.io/installation/)

-  [Strongswan](https://strongswan.org/)

  

#### [Azure](https://portal.azure.com)

VM: Ubuntu 18.04 size B2s, standard, 2vCPU, 4GB mem

-  [Docker](https://www.docker.com)

-  [Portainer](https://www.portainer.io/installation/)

-  [Postgres](https://hub.docker.com/_/postgres)

-  [PostgresAdmin](https://hub.docker.com/r/dpage/pgadmin4/)

  

##### Setup Azure IPsec

[https://docs.microsoft.com/en-en/azure/vpn-gateway/vpn-gateway-howto-site-to-site-resource-manager-portal](https://docs.microsoft.com/en-en/azure/vpn-gateway/vpn-gateway-howto-site-to-site-resource-manager-portal)

  

For setting up the VPN on the Raspberry I used the following steps:

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

Generate preshared key

```

$ openssl rand -base64 64

```

  

We will setup our VPN Gateway in Site A (Paris), first to setup the `/etc/ipsec.secrets` file:

```

$ cat /etc/ipsec.secrets # source destination [ExternalIP] [RemoteExternalIP] : PSK "xxxxx"

```

Now to setup our VPN configuration in `/etc/ipsec.conf`:

```

cat /etc/ipsec.conf

# basic configuration

config setup charondebug="all"

uniqueids=yes

strictcrlpolicy=no

# connection to azure

conn home-to-azure

authby=secret left=%defaultroute

leftid=ExternalIP

leftsubnet=localsubnet/24

right=azureExternalIP

rightsubnet=azureLocalsubnet/24

ike=aes256-sha2_256-modp1024!

esp=aes256-sha2_256!

keyingtries=0

ikelifetime=1h

lifetime=8h

dpddelay=30

dpdtimeout=120

dpdaction=restart

auto=start

```

Firewall settings

```

sudo iptables -t nat -A POSTROUTING -s AzureLocalSubnet/24 -d localSubnet/24 -j MASQUERADE

```

Start the service (on boot)

```

$ sudo ipsec restart

$ sudo systemctl enable strongswan

```

Status

```

$ sudo ipsec status

```

  
  

#### Used Hass.io components & cards

Cards

- https://github.com/custom-cards/button-card

- https://github.com/kalkih/mini-graph-card

- https://github.com/thomasloven/lovelace-card-mod

- https://github.com/nervetattoo/simple-thermostat

  

Components

- https://github.com/USA-RedDragon/badnest

-  [https://github.com/hassio-addons/addon-node-red](https://github.com/hassio-addons/addon-node-red)

-  [https://github.com/Koenkk/zigbee2mqtt](https://github.com/Koenkk/zigbee2mqtt)

-  [https://www.home-assistant.io/docs/mqtt/broker/](https://www.home-assistant.io/docs/mqtt/broker/)

  

Icons: [http://materialdesignicons.com/](http://materialdesignicons.com/)

  
  

### Roadmap

Environment

- Remove Neo coolcam Smart plugs

- Setup Strongswan on Azure Ubuntu VM, remove Azure VPN Gateway (costs ;))

 
Hass.io

- Scheduled dark-light theme

- Onboarding Spotify

- Onboarding Playstation

 
### Screenshots
![LightTheme](https://github.com/srozemuller/hassio-config/blob/master/screenshots/Image%20798.png)
![LightTheme-SystemInfo](https://github.com/srozemuller/hassio-config/blob/master/screenshots/Image%20799.png)
![DarkTheme](https://github.com/srozemuller/hassio-config/blob/master/screenshots/Image%20794.png)
![DarkTheme-SystemInfo](https://github.com/srozemuller/hassio-config/blob/master/screenshots/Image%20796.png)
![DarkTheme-EnergyInfo](https://github.com/srozemuller/hassio-config/blob/master/screenshots/Image%20797.png)