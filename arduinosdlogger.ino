#include <SD.h>
#include <SPI.h>

int CS_pin = 10; // Pin 10 on Arduino Uno

File sdcard_file;

#define BUFF_MAX 700

void setup() {
  Serial.begin(115200);
  pinMode(CS_pin, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin(CS_pin))
    {
    Serial.println("\n SD card is ready to use.");
    } 
  else
    {
    Serial.println("\n SD card initialization failed");
    return;
    }
 sdcard_file = SD.open("data.txt", FILE_WRITE);
  if(sdcard_file)
    {
        Serial.println("Successfully opened data.txt");
        sdcard_file.close(); // close the file
    }
    else
    {
      Serial.println("error opening data.txt");
    }  
   
}

void loop() {
    char inBuffer[BUFF_MAX];
    memset(inBuffer, 0, sizeof(inBuffer));
  
    while(Serial.available()>0)
    {
      int len = Serial.readBytes(inBuffer,BUFF_MAX);
      Serial.flush();
      Serial.write(inBuffer,sizeof(inBuffer));
      delay(10);
      
      sdcard_file= SD.open("data.txt",FILE_WRITE);
      if(sdcard_file)
      {
        sdcard_file.println(inBuffer);
        sdcard_file.close();  
      }
       else
       {
        Serial.println("\nerror opening data.txt");
        }
    }
     Serial.flush();
}
