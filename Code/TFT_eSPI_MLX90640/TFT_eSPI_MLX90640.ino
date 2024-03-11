/*

 Has to be an older Boards, ESP32 Rev 2.0.11
 Has to be Library, TFT_eSPI Rev 2.5.34
 The latest does not work

*/

#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Wire.h>
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

#define TA_SHIFT 8 //Default shift for MLX90640 in open air

const byte MLX90640_address = 0x33;
static float mlx90640To[768];
paramsMLX90640 mlx90640;

int xPos, yPos;                                // Abtastposition
int R_colour, G_colour, B_colour;              // RGB-Farbwert
int i, j;                                      // Zählvariable
float T_max, T_min;                            // maximale bzw. minimale gemessene Temperatur
float T_center;   

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

void setup(void)
 {
  Serial.begin(115200);
  Wire.begin(18,17); //S3 Parallel
  delay(1000);
  Wire.setClock(800000); //Increase I2C clock speed to 800kHz

  //while (!Serial); //Wait for user to open terminal  //Plug into pc or charger issue fixed by commenting out

  Serial.println("MLX90640 IR Array Example");
  
  if (isConnected() == false)
  {
   Serial.println("MLX90640 not detected at default I2C address. Please check wiring. Freezing.");
   while (1);
  } 
    
  Serial.println("MLX90640 online!");
  //Get device parameters - We only have to do this once
  int status;
  uint16_t eeMLX90640[832];
    
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);
  if (status != 0)
       Serial.println("Failed to load system parameters");

  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
  if (status != 0)
  {
   Serial.println("Parameter extraction failed");
   Serial.print(" status = ");
   Serial.println(status);
  }
  //Once params are extracted, we can release eeMLX90640 array
   MLX90640_I2CWrite(0x33, 0x800D, 6401);    // writes the value 1901 (HEX) = 6401 (DEC) in the register at position 0x800D to enable reading out the temperatures!!!
  // ===============================================================================================================================================================
  //MLX90640_SetRefreshRate(MLX90640_address, 0x00); //Set rate to 0.25Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x01); //Set rate to 0.5Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x02); //Set rate to 1Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x03); //Set rate to 2Hz effective - Works
  //MLX90640_SetRefreshRate(MLX90640_address, 0x04); //Set rate to 4Hz effective - Works
  MLX90640_SetRefreshRate(MLX90640_address, 0x05); //Set rate to 8Hz effective - Works at 800kHz
  //MLX90640_SetRefreshRate(MLX90640_address, 0x06); //Set rate to 16Hz effective - fails
  //MLX90640_SetRefreshRate(MLX90640_address, 0x07); //Set rate to 32Hz effective - fails


  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  //tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour

  
  // draw the colour-scale
  for (i = 0; i < 181; i++)
  {
   getColour(i);
   //tft.drawLine(250, 210 - i, 260, 210 - i, tft.color565(R_colour, G_colour, B_colour)); 
   tft.drawLine(250, 215 - i, 260, 215 - i, tft.color565(R_colour, G_colour, B_colour)); //Over
  } 
  
}

void loop() 
{
  //tft.setTextColor(TFT_GREEN, TFT_BLACK);
  //tft.setCursor (8, 52);
  //tft.print("Test"); // This uses the standard ADAFruit small font

   for (byte x = 0 ; x < 2 ; x++) //Read both subpages
       {
        uint16_t mlx90640Frame[834];
        int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);
    
        if (status < 0)
           {
            Serial.print("GetFrame Error: ");
            Serial.println(status);
           }

        float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
        float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

        float tr = Ta - TA_SHIFT; //Reflected temperature based on the sensor ambient temperature
        float emissivity = 0.95;

        MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
       }

       
    // determine T_min and T_max and eliminate error pixels
    // ====================================================

    mlx90640To[1*32 + 21] = 0.5 * (mlx90640To[1*32 + 20] + mlx90640To[1*32 + 22]);    // eliminate the error-pixels
    mlx90640To[4*32 + 30] = 0.5 * (mlx90640To[4*32 + 29] + mlx90640To[4*32 + 31]);    // eliminate the error-pixels
    
    T_min = mlx90640To[0];
    T_max = mlx90640To[0];

    for (i = 1; i < 768; i++)
       {
        if((mlx90640To[i] > -41) && (mlx90640To[i] < 301))
           {
            if(mlx90640To[i] < T_min)
               {
                T_min = mlx90640To[i];
               }

            if(mlx90640To[i] > T_max)
               {
                T_max = mlx90640To[i];
               }
           }
        else if(i > 0)   // temperature out of range
           {
            mlx90640To[i] = mlx90640To[i-1];
           }
        else
           {
            mlx90640To[i] = mlx90640To[i+1];
           }
       }


    // determine T_center
    // ==================

    T_center = mlx90640To[11* 32 + 15];    

    // drawing the picture
    // ===================

    for (i = 0 ; i < 24 ; i++)
       {
        for (j = 0; j < 32; j++)
           {
            mlx90640To[i*32 + j] = 180.0 * (mlx90640To[i*32 + j] - T_min) / (T_max - T_min);
                       
            getColour(mlx90640To[i*32 + j]);
            
            //tft.fillRect(217 - j * 7, 35 + i * 7, 7, 7, tft.color565(R_colour, G_colour, B_colour));
            tft.fillRect(235 - j * 7, 35 + i * 7, 7, 7, tft.color565(R_colour, G_colour, B_colour));  //On the S3 board
            //tft.fillRect(297 - j * 7, 35 + i * 7, 7, 7, tft.color565(R_colour, G_colour, B_colour));//großes Bild
            //tft.fillRect(267 - j * 7, 35 + i * 7, 7, 7, tft.color565(R_colour, G_colour, B_colour));//großes Bild
            //tft.fillRect(300 - j * 7, 35 + i * 7, 7, 7, tft.color565(R_colour, G_colour, B_colour));//großes Bild
           }
       }

    //Fadenkreuz
    tft.drawLine(235 - 15*7 + 3.5 - 5, 11*7 + 35 + 3.5, 235 - 15*7 + 3.5 + 5, 11*7 + 35 + 3.5, tft.color565(255, 255, 255));
    tft.drawLine(235 - 15*7 + 3.5, 11*7 + 35 + 3.5 - 5, 235 - 15*7 + 3.5, 11*7 + 35 + 3.5 + 5,  tft.color565(255, 255, 255));
    //tft.drawLine(287 - 15*7 + 3.5 - 5, 11*7 + 35 + 3.5, 287 - 15*7 + 3.5 + 5, 11*7 + 35 + 3.5, tft.color565(255, 255, 255));
    //tft.drawLine(287 - 15*7 + 3.5, 11*7 + 35 + 3.5 - 5, 287 - 15*7 + 3.5, 11*7 + 35 + 3.5 + 5,  tft.color565(255, 255, 255));
 
    //tft.fillRect(260, 25, 37, 10, tft.color565(0, 0, 0));
    //tft.fillRect(260, 205, 37, 10, tft.color565(0, 0, 0));    
    //tft.fillRect(115, 220, 37, 10, tft.color565(0, 0, 0));    

    //tft.setTextColor(TFT_WHITE, tft.color565(0, 0, 0));
    //tft.setCursor(265, 25);//tft.setCursor(265, 25);
    //tft.print(T_max, 1);
    //tft.setCursor(265, 205);//tft.setCursor(265, 205);
    //tft.print(T_min, 1);
    tft.setCursor(120, 220);
    tft.print(T_center, 1);

    //tft.setCursor(300, 25);//tft.setCursor(300, 25);//T Max Oben
    //tft.print("C");
    //tft.setCursor(300, 205);//tft.setCursor(300, 205); //TMin unten
    //tft.print("C");
    tft.setCursor(155, 220);//TFadenkreuz
    tft.print("C");

    //Skala rechts
    /*tft.setCursor(300, 55);//tft.setCursor(300, 25);
    tft.print("300");
    tft.setCursor(300, 85);//tft.setCursor(300, 25);
    tft.print("200");
    tft.setCursor(300, 115);//tft.setCursor(300, 25);
    tft.print("150");
    tft.setCursor(300, 145);//tft.setCursor(300, 25);
    tft.print("100");
    tft.setCursor(300, 175);//tft.setCursor(300, 25);
    tft.print("50");
    */
    tft.setCursor(80, 210);//warum sooo weit links
    tft.print("ESP32-S3 Parallel Bus");
    
    delay(20);
}


// ===============================
// ===== determine the colour ====
// ===============================

void getColour(int j)
   {
    if (j >= 0 && j < 30)
       {
        R_colour = 0;
        G_colour = 0;
        B_colour = 20 + (120.0/30.0) * j;
       }
    
    if (j >= 30 && j < 60)
       {
        R_colour = (120.0 / 30) * (j - 30.0);
        G_colour = 0;
        B_colour = 140 - (60.0/30.0) * (j - 30.0);
       }

    if (j >= 60 && j < 90)
       {
        R_colour = 120 + (135.0/30.0) * (j - 60.0);
        G_colour = 0;
        B_colour = 80 - (70.0/30.0) * (j - 60.0);
       }

    if (j >= 90 && j < 120)
       {
        R_colour = 255;
        G_colour = 0 + (60.0/30.0) * (j - 90.0);
        B_colour = 10 - (10.0/30.0) * (j - 90.0);
       }

    if (j >= 120 && j < 150)
       {
        R_colour = 255;
        G_colour = 60 + (175.0/30.0) * (j - 120.0);
        B_colour = 0;
       }

    if (j >= 150 && j <= 180)
       {
        R_colour = 255;
        G_colour = 235 + (20.0/30.0) * (j - 150.0);
        B_colour = 0 + 255.0/30.0 * (j - 150.0);
       }

   }
   



//Returns true if the MLX90640 is detected on the I2C bus
boolean isConnected()
   {
    Wire.beginTransmission((uint8_t)MLX90640_address);
  
    if (Wire.endTransmission() != 0)
       return (false); //Sensor did not ACK
    
    return (true);
   }   
   
