/***************************************************
 Bauhaus Watch Face for SQFMI Watchy
 V0.3 - Daniel Cuthbert 2026
 ****************************************************/

#include <Watchy.h>
#include "Baloo2_Regular12pt7b.h"
#include "Baloo2_Regular50pt7b.h"

class WatchFace : public Watchy {
  public:
    void drawWatchFace() {
      int16_t  x1, y1;
      uint16_t w, h;
      String textstring;

      WiFi.mode(WIFI_OFF);
      btStop();

      if (currentTime.Hour == 0 && currentTime.Minute == 0) {
        sensor.resetStepCounter();
      }

      display.setTextWrap(false);

      // Wanted a super clean, grid-based layout with a Bauhaus vibe, so I went with a custom design instead of using the built-in watch face templates. 
      // The layout is fixed and doesn't change based on the time or date, but it shows the time, date, battery level, and step count in a clear and visually appealing way.
    
      // White base
      display.fillScreen(GxEPD_WHITE);

      // Black sections
      display.fillRect(103, 0,   97,  120, GxEPD_BLACK); // minutes (top-right)
      display.fillRect(103, 123, 97,  37,  GxEPD_BLACK); // battery (mid-right)
      display.fillRect(0,   163, 200, 37,  GxEPD_BLACK); // steps   (bottom strip)

      // Grid lines (3px thick)
      display.fillRect(100, 0,   3, 163, GxEPD_BLACK);   // vertical
      display.fillRect(0,   120, 200, 3,  GxEPD_BLACK);  // horizontal mid
      display.fillRect(0,   160, 200, 3,  GxEPD_BLACK);  // horizontal bottom

      // ── HOUR (top-left · white bg · black text) ──────
      display.setFont(&Baloo2_Regular50pt7b);
      display.setTextColor(GxEPD_BLACK);
      textstring = String(currentTime.Hour);
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor((100 - w) / 2 - x1, (120 - h) / 2 - y1);
      display.print(textstring);

      // ── MINUTES (top-right · black bg · white text) ──
      display.setTextColor(GxEPD_WHITE);
      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(103 + (97 - w) / 2 - x1, (120 - h) / 2 - y1);
      display.print(textstring);

      // ── DATE (mid-left · white bg · black text) ──────
      display.setFont(&Baloo2_Regular12pt7b);
      display.setTextColor(GxEPD_BLACK);
      textstring = dayShortStr(currentTime.Wday);
      display.setCursor(8, 140);
      display.print(textstring);
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      display.setCursor(8, 156);
      display.print(textstring);

      // ── BATTERY (mid-right · black bg · white bar) ───
      float batt = (getBatteryVoltage() - 3.3) / 0.9;
      if (batt > 1.0) batt = 1.0;
      if (batt < 0.0) batt = 0.0;
      display.drawRect(113, 134, 77, 14, GxEPD_WHITE);   // outline
      int fillW = (int)(73.0 * batt);
      if (fillW > 0) {
        display.fillRect(115, 136, fillW, 10, GxEPD_WHITE); // fill
      }

      // ── STEPS (bottom strip · black bg · white text) ─
      display.setTextColor(GxEPD_WHITE);
      textstring = String(sensor.getCounter());
      textstring += " steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor((200 - w) / 2 - x1, 163 + (37 - h) / 2 - y1);
      display.print(textstring);
    }
};

WatchFace m;

void setup() {
  m.init();
}

void loop() {
  // Watchy deep sleeps after init()
}
