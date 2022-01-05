# ESP8266 Driven Neopixel Matrix Display

Software to read, display, and upload K20 Co2 sensor data to Google Sheets.

## Expected Hardware

* [K30 Co2 Sensor](https://senseair.com/products/flexibility-counts/k30/)
* [8x32 Neopixel Matrix](https://www.amazon.co.uk/BTF-LIGHTING-Individual-Addressable-Flexible-Controllers/dp/B088K1KDW5?pd_rd_w=uJPyg&pf_rd_p=833f8100-480e-45a7-90a8-1a00dde75c2a&pf_rd_r=9PWB9GCV2NEHNRR5CS2Y&pd_rd_r=300e8ec5-787b-4de6-94ce-19c7651cf541&pd_rd_wg=RjuaW&pd_rd_i=B088K1KDW5&psc=1&ref_=pd_bap_d_rp_1_i)
* [ESP8266 Node MCU](https://www.amazon.co.uk/gp/product/B074Q27ZBQ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* [Print the enclosure](https://www.thingiverse.com/thing:5187606)
## Install

This software was built using the [Vs Code](https://code.visualstudio.com/) extension [PlatformIO](https://platformio.org/). With both installed you should be able to upload it to your ESP8266 fairly easily.

## Uploading data to google sheets.

By default, this software will just display the value of the K30 sensor on the Neopixel matrix, but uploading your data to Google Sheets can be achieved with a little configuration.

* Modify the `ssid` and `password` for your WiFi network in `src/main.cpp`.
* Follow these [setup steps for Google Sheets](https://github.com/StorageB/Google-Sheets-Logging#instructions-for-google-sheets) substituting the google script for the one from this repo (`google-scripts/date-and-value.gs`).
* When you've got your scripts deployment ID you can then paste this into the `scriptId` property in `src/main.cpp`.
* Use the alternative `ledCo2Service` which takes these additional arguments and uploads your data.

(The google script we're using has a small modification to save only one value and adds a timestamp to each entry.)

## Thanks to
* https://github.com/StorageB/Google-Sheets-Logging#instructions-for-google-sheets
* https://github.com/electronicsguy/HTTPSRedirect
