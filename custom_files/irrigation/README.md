#### Arduino Water Flow Sensor with MQTT and HomeAssistant

For controlling my irrigation system i've started building a sensor which is capturing the consumed liters. 
##### Components i've used:

- [Water Flow Sensor DN25   YF-G1](https://nl.aliexpress.com/item/32605385176.html?spm=a2g0s.9042311.0.0.3baf4c4deSDh9x)
- [Wemos D1 Mini   Pro](https://nl.aliexpress.com/item/32845084675.html?spm=a2g0o.productlist.0.0.447c2a6c9p3L8q&algo_pvid=0a8d7fc9-790a-437a-96c6-850c4fab697b&algo_expid=0a8d7fc9-790a-437a-96c6-850c4fab697b-1&btsid=0b0a187b15889643446401239e643b&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
- [Case](https://nl.aliexpress.com/item/32898023600.html?spm=a2g0s.9042311.0.0.27424c4dCWlSoI)
- [PCB Solder board](https://nl.aliexpress.com/item/32902801591.html?spm=a2g0o.productlist.0.0.77673622KI40vP&algo_pvid=fdf9053c-e135-4342-87d9-c516c5c7fbc1&algo_expid=fdf9053c-e135-4342-87d9-c516c5c7fbc1-11&btsid=0b0a187b15889646114502037e643b&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)

The Arduino [flowsensor.ino](https://github.com/srozemuller/hassio-config/blob/master/custom_files/irrigation/flowsensor.ino) file is in this repo folder
See the [garden.yaml](https://github.com/srozemuller/hassio-config/blob/master/sensors/garden.yaml) file for the [HomeAssistant](https://www.home-assistant.io/) code i've used.

#### Home-Assistant card example
![home-assistant cards](https://user-images.githubusercontent.com/43162899/81440894-12257c80-9171-11ea-9ab5-f24d38ab28b5.png)

#### Home-Assistant view
```yaml
  - badges: []
    cards:
      - entities:
          - entities:
              - sensor.total_liters
              - sensor.current_liters
              - sensor.irrigation_last_run
              - sensor.irrigation_last_contact
            entity: sensor.pump_status
            icon: 'mdi:water-pump'
            name: Irrigatie
            state_header: Status
            type: 'custom:multiple-entity-row'
        type: entities
      - cards:
          - entities:
              - entity: sensor.flow_rate
                index: 0
            font_size: 75
            hours_to_show: 3
            icon: 'mdi:pinwheel-outline'
            line_color: var(--accent-color)
            line_width: 8
            points_per_hour: 60
            type: 'custom:mini-graph-card'
          - entities:
              - entity: sensor.current_liters
                index: 0
            font_size: 75
            hours_to_show: 3
            icon: 'mdi:water-outline'
            line_color: var(--accent-color)
            line_width: 8
            points_per_hour: 60
            type: 'custom:mini-graph-card'
        type: horizontal-stack
      - entities:
          - entity: sensor.total_liters
            index: 0
        font_size: 75
        group_by: date
        hours_to_show: 168
        icon: 'mdi:pinwheel-outline'
        show:
          graph: bar
        type: 'custom:mini-graph-card'
      - type: entity
        entity: sensor.saved_water_costs
        icon: 'mdi:dollar'
    icon: 'mdi:flower-tulip'
    path: garden
    title: Garden

#### Hardware
![The wemos and case](https://user-images.githubusercontent.com/43162899/81441039-54e75480-9171-11ea-816f-c6af2805db82.jpeg)

![Flow sensor YF-G1](https://user-images.githubusercontent.com/43162899/81441118-78aa9a80-9171-11ea-89ef-a1511bff1da7.jpeg)
