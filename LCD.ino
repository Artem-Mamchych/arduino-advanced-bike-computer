void clearLCD() {
  tft.fillRect(34, 0, 130, 95, ST7735_BLACK);
}

void drawAlertMessage(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void tftPrintPlot() {
  tft.drawLine(graph_pos-1, (prev_accel+512)>>3, graph_pos, (accel+512)>>3, ST7735_YELLOW);
  tft.drawLine(graph_pos-1, prev_speed_value, graph_pos, speed_value, ST7735_WHITE);

  tft.drawPixel(graph_pos, (x+512)>>3, ST7735_BLUE);
  tft.drawPixel(graph_pos, (y+512)>>3, ST7735_RED);   
  ++graph_pos;
}

void tftCleanText() {
  tft.setCursor(0, 0);
  if (graph_pos >= width) { //If at the edge of the window, go back to the beginning:
    tft.fillScreen(ST7735_BLACK);
    graph_pos = 1;
  } else {
    tft.setTextColor(ST7735_BLACK);

    tftPrintSpeed(false);
    tftPrintAccelerometerXYZ(false);
  }
}

void tftPrintValues() {
  tft.setCursor(0, 0);
//  tft.fillRect(34, 0, 130, 95, ST7735_BLACK);

  tftPrintSpeed(true);
  tftPrintAccelerometerXYZ(true);
}

inline void tftPrintSpeed(boolean useColor) { //useColor = false used only in clean LCD function
  if (useColor) {
    prev_speed_value = speed_value;
    prev_mileage = mileage; 
  }

  if (useColor) tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.print(prev_speed_value); tft.print("/"); tft.println(prev_mileage); 
}

inline void tftPrintAccelerometerXYZ(boolean useColor) { //useColor = false used only in clean LCD function
  tft.setTextSize(2);

  if (useColor) {
    prev_x = x;
    prev_y = y;
    prev_z = z;  
    prev_accel = accel;
  }

  if (useColor) tft.setTextColor(ST7735_BLUE);
  tft.print("X"); tft.print(prev_x);
  if (useColor) tft.setTextColor(ST7735_RED);
  tft.print(" Z"); tft.println(prev_z);

  if (useColor) tft.setTextColor(ST7735_GREEN);
  tft.print("Y");   tft.print(prev_y);
  if (useColor) tft.setTextColor(ST7735_YELLOW);
  tft.print(" A"); tft.println(prev_accel);  
}
