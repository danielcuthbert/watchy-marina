/***************************************************
 Watch face for a Watchy Open Source E-Paper Watch
 V0.1
 Daniel Cuthbert 2021
 ****************************************************/

#include <Watchy.h> //include the Watchy library
#include "marina_opentype12pt7b.h"
#include "marina_opentype50pt7b.h" // 50pt works but maybe smaller will be better
				

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //where the main look of the watch face goes
      
      int16_t  x1, y1; // Display is a 200x200 GDEH0154D67
      uint16_t w, h;
      String textstring;
   
      // We don't want the activity sensor to roll over, so reset it at 00:00
      if(currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
      }
      
      // Make the main watch face black 
      // This is where the hour/day will be shown in 50pt
      display.fillScreen(GxEPD_BLACK);
      display.setTextColor(GxEPD_WHITE);
      display.setTextWrap(false);
      display.setFont(&marina_opentype_bigfontsite_com50pt7b);
     
      //Hour of Day
      textstring = currentTime.Hour;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(185-w, 85-5);
      display.print(textstring);
      
      //Minutes
      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(185-w, 90-5+h);
      display.print(textstring);

      // Battery Level
      display.drawRect(8, 16, 34, 12, GxEPD_WHITE); //the box
      display.drawRect(44, 19, 3, 6, GxEPD_WHITE); // the postive terminal
      float batt = (getBatteryVoltage() - 3.3) / 0.9;
      if (batt > 0) {
       display.fillRect(12,20,21*batt,4,GxEPD_WHITE); //the status charge
      }									

      // Second part of the display
      // This is where the date/month and step counter is shown
      // We need a smaller font
      display.setFont(&marina_opentype_bigfontsite_com12pt7b);

      //Our Step Counter
      textstring = sensor.getCounter();
      textstring += " Steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(8, 181);
      display.print(textstring);
      
      // The Day
      textstring = dayStr(currentTime.Wday);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(8, 130);
      display.print(textstring);
            
      // The Month
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(8, 100);
      display.print(textstring);
 
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
