# ESP32-S3_MLX90640_Thermal

An assembled and tested board is available at Tindie: https://www.tindie.com/products/miker/esp32-s3-mlx90640-thermal-image-board/<br/>

This project has gone through several revisions over several months. This latest uses a pcb track antenna instead of the chip type. Tuning has gone well and it seems to perform well. This version uses an ESP32-S3 processor allowing everything to fit on the backside of a 1.69" screen. An 8-bit bus improves the refresh dramatically over traditional spi displays. It is powered by a USB-C connector or small LiPO battery<br/>
Two right angle pushbuttons are on one side if needed and two small vertical ones needed only when first powering up the board to bring up the com port. The thermal code provided is rough but shows basic functionality. Hopefully it can be of some help allowing you to make improvements. The design files are all available if you would like to assemble your own and change the design yourself. <br/>
<br/>

**Hardware used on this board <br/>**
-Processor (ESP32-S3FN8)<br/>
-1.69" LCD (https://www.buydisplay.com/1-69-inch-color-280x240-round-rectangle-ips-tft-lcd-display-panel-st7789)<br/>
-3.3V LDO (HT7833)<br/>
-LiPo charger (MCP73831T-2ACI)<br/>
-LiPo connector (1.25mm JST type)<br/>
-Thermal Sensor (MLX90640ESF-BAB-000-TU)<br/>
-LiPo battery monitor (MAX17048G+)<br/>
<br/>

**FAQ** <br/> 
**How do I updload my own sketch?<br/>** 
**-Plug the board into your pc. If your com port appears and disappears over and over, hold down the B (Boot button), tap on the R (Reset) button, let go of the Boot button. This should hold the com port<br/>**
**-Install the latest Arduino IDE, install the ESP32 Board libraries, Install the sensor libraries, Install an older TFT_eSPI library 2.5.43 or compile issues may appear, delete the User_Setup.h and User_Setup_Select.h files and replace with mine<br/>**
**-Upload your sketch<br/>**
<br/>
**Where do I get a battery?<br/>**
**-Source a 300mAh to 500mAh LiPo with a 1.25mm battery from Aliexpress. Just make sure the positive and negative wires are in the correct locations as noted on the board. If not, they can be removed by lifting the tab and swapping around<br/>**
<br/>
**Why does my battery never charge?<br/>**
**-The charger cannot power the board and charge the battery at the same time. To properly charge the battery turn the device off and leave the USB-C plugged in. The red light will go off once charged<br/>**
<br/>
**Why is this often out of stock?<br/>**
**Each board is hand assembled using a hot plate and hot air wand. Parts are usually purchased in small quantities in case it does not sell. Proper testing, packaging and hardware debugging takes time<br/>**
<br/>
**Do you offer custom designs?<br/>**
**Yes if time allows. Hardware prototype design is my full time job with hobby projects as a fun evening adventure<br/>**
(https://youtube.com/shorts/amKmFCEE5ls?si=_cqpdNFftW1ooPPc") <br/>
<br/>

![Hand](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/ba3d8526-d287-444c-90c5-280552fa3a73) <br/>
![Back](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/140335cc-d5b3-4149-8417-632e4b00c66d) <br/>
![Rev3_Components](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/7aa49093-eb51-410e-9361-4884b0d71cc6) <br/>
![Size](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/a2fc3894-5fc3-46e2-a023-1946b68b1cbc) <br/>
![Front](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/3b73e65f-1645-44f8-9601-684ffbde1dd9)

