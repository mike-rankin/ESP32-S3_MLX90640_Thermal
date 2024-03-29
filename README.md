# ESP32-S3_MLX90640_Thermal
ESP32-S3 Thermal Sensor using an 8-bit bus



(https://youtube.com/shorts/amKmFCEE5ls?si=_cqpdNFftW1ooPPc")

This project evolved from a customer project who needed a large 2.4" lcd. I was pretty sure that going with an ESP32-S3 bare chip would allow everything to fit on the backside of a 1.69" screen. Previous revisions used a SPI bus but the refresh rate was far too slow. Changing the 1.69" screen this 8-bit bus type improved the refresh dramatically: https://www.buydisplay.com/1-69-inch-color-280x240-round-rectangle-ips-tft-lcd-display-panel-st7789 <br/>
Going with the 8-bit bus takes up many more gpio but the S3 has plenty left over. Right now the image sensor and LiPo monitor are on the same i2c bus. Two right angle pushbuttons are on one side if needed and two small vertical ones needed when first powering up the board to bring up the com port. When first plugged in the com port will appear and disappear over and over. Holding down the boot button (B) and tapping the reset (R) button once sorts this out. The original sketch here: https://github.com/Uspizig/MLX90640 was very helpful in getting things up and running. It has since been modified to use the TFT_eSPI library needed for the 8-bit bus. <br/>
I hope to continue testing and if all is well, can possibly sell assembled boards on Tindie. It's been years since I've sold projects but this is one of my favourites and something I've always wanted to purchase. <br/>
The design files are all available if you would like to assemble your own of change the design yourself. <br/>

![Hand](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/ba3d8526-d287-444c-90c5-280552fa3a73) <br/>
![Back](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/140335cc-d5b3-4149-8417-632e4b00c66d) <br/>
![Rev2_Components](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/21599616-aa07-453e-aaf3-1c32bfe3a255) <br/>
![Size](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/a2fc3894-5fc3-46e2-a023-1946b68b1cbc) <br/>
![Front](https://github.com/mike-rankin/ESP32-S3_MLX90640_Thermal/assets/4991664/3b73e65f-1645-44f8-9601-684ffbde1dd9)

