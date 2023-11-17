# This README needs updating!

# plant_watering
The classic automatic watering system, for my ```thirsty``` basil plant.

Can't afford to put images here so this text-art diagram will have to suffice. 
```

              ________+++________
  GP0   [01] <|       +++       |> [40]  VBUS                       ____________________         Power Supply
  GP1   [02] <|LED              |> [39]  VSYS --------------- 5V  <| Adafruit MPM3610  |> VIN ------ 12V
  GND   [03] <|@ GP25           |> [38]  GND  --------------- GND <| 5V Buck Converter |> GND ---|-- 0V
  GP2   [04] <|                 |> [37]  3V3_EN               EN  <|___________________|       | |
  GP3   [05] <|                 |> [36]  3V3(OUT)                                              | |
  GP4   [06] <|                 |> [35]          ADC_VREF                                      | |
  GP5   [07] <|                 |> [34]  GP28    ADC2              _____ IRF520NPbF            | |
  GND   [08] <|                 |> [33]  GND     AGND             |  O  |  MOSFET              | |
  GP6   [09] <|                 |> [32]  GP27    ADC1             |_____|                      | |
  GP7   [10] <|                 |> [31]  GP26    ADC0              | | |                       | |
  GP8   [11] <|                 |> [30]  RUN                       | | |--DRAIN----------------| |
  GP9   [12] <|                 |> [29]  GP22                      | |                           |
  GND   [13] <|                 |> [28]  GND             ----GATE----|                           |
  GP10  [14] <|                 |> [27]  GP21                      |            _______          |
  GP11  [15] <|                 |> [26]  GP20                      |--SOURCE---|       |---------|
  GP12  [16] <|Raspberry        |> [25]  GP19                                  | 12V   |
  GP13  [17] <|Pi Pico          |> [24]  GP18                                  | Fish  |== Water to basil ==>
  GND   [18] <|                 |> [23]  GND                                   | Tank  |
  GP14  [19] <|                 |> [22]  GP17                        \\        | Pump  |       //
  GP15  [20] <|______DEBUG______|> [21]  GP16                         \\       |_______|      //
                     | | |                                             \\====================//

```

Most of the code is adapted from https://github.com/krzmaz/pico-w-webserver-example
lwipopts.h is copied from the above repo, but there are similar files in the 
pico-examples repository.
