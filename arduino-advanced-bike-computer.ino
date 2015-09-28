#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

//#define SERIAL_DEBUG
//#define SERIAL_DEBUG_TFT

//LCD definitions
//LCD pin cs   10
//LCD pin dc   9
//LCD pin rst  8
//Using hardware SPI pins for max speed
Adafruit_ST7735 tft = Adafruit_ST7735(); //Library was optimized for max speed, sources available here: https://github.com/Artem-Mamchych/Adafruit-ST7735-Library
#define MIN_LCD_FEFRESH_DELAY 60 //Reduce this for faster LCD refresh rate. TODO: find best value
unsigned long currentFrameMillis, previousFrameMillis = 0;

int16_t width, height;
int graph_pos = 0;
unsigned long lcdCleanTime, lcdFillTime;
//LCD definitions END

//MMA7361 definitions
#define PIN_X     A0
#define PIN_Y     A1
#define PIN_Z     A2
#define PIN_SLEEP A3
//#define PIN_FREEFALL_DETECT 12

#define FREEFALL_EVENT   HIGH
#define SLEEP_MODE_ON    LOW
#define SLEEP_MODE_OFF   HIGH
//For lower power consumption, it is recommended to set g-Select to 1.5g mode.

//#define PIN_SENSITIVITY_MODE 11 //Not used
//g-Range Sensitivity:
#define MODE_1.5G LOW  //+- 1.5g 800 mV/g
#define MODE_6G   HIGH //+- 6g 206 mV/g

//This calibration coefficients is specific for each MMA7361 chip
#define CALIB_VAL_X 407
#define CALIB_VAL_Y 427
#define CALIB_VAL_Z 565

int x, y, z, accel;
int prev_x, prev_y, prev_z, prev_accel;
//MMA7361 definitions END

//BICYCLE SPEED SENSOR definitions
#define TYRE_CIRCUMFERENCE 2074 //mm
#define DEBOUNCE_DELAY 15 //Debouncing Time in Milliseconds

volatile unsigned long time = 0;
volatile unsigned long speed_value = 0, prev_speed_value = 0;
volatile unsigned long mileage = 0, prev_mileage = 0;

//Interrupt handler for reed switch on pin 2
void speedReedSwInterrupt() {
  if((long)(millis() - time) >= DEBOUNCE_DELAY) {
    speed_value = TYRE_CIRCUMFERENCE/(millis() - time);
    mileage += TYRE_CIRCUMFERENCE/1000;
    if(speed_value > 99) speed_value = 99;
    
    time = millis();
  }
}

inline void setupSpeedSensorInterrupt() {
  attachInterrupt(0, speedReedSwInterrupt, RISING);
  speed_value = 0;
}
//BICYCLE SPEED SENSOR definitions END

void setup(void) {
  pinMode(PIN_SLEEP, OUTPUT);
//  pinMode(PIN_FREEFALL_DETECT, INPUT);
  digitalWrite(PIN_SLEEP, SLEEP_MODE_OFF);
#if  defined (SERIAL_DEBUG) || defined (SERIAL_DEBUG_TFT)  
  Serial.begin(9600);
#endif
  
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, LCD controller
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
  width = tft.width();
  height = tft.height();
  
  setupSpeedSensorInterrupt(); 
}

void loop() {
  currentFrameMillis = millis();
  if (currentFrameMillis - previousFrameMillis > MIN_LCD_FEFRESH_DELAY) {
    previousFrameMillis = currentFrameMillis; 
    
    //LCD thread

    //uartPrintValues()
#ifdef SERIAL_DEBUG_TFT
     lcdCleanTime = millis();
#endif
    tftCleanText();
#ifdef SERIAL_DEBUG_TFT 
    lcdFillTime = millis();
#endif
    tftPrintValues();
//    tftPrintPlot();

#ifdef SERIAL_DEBUG_TFT
    Serial.print(millis() - lcdFillTime); //draw time, ms  
    Serial.print("/");
    Serial.println(lcdFillTime - lcdCleanTime); //clean time, ms
#endif
  } else {
#ifdef SERIAL_DEBUG_TFT
    Serial.print(":");
    Serial.print(millis() - currentFrameMillis);
#endif
    getAccelValues(); //Add filtering
    delay(10);
  }
//  delay(80); //Refresh Rate
}


//void uartPrintValues() {
//  Serial.print(" X: ");
//  Serial.print(x);
//  Serial.print(" Y: ");
//  Serial.print(y);
//  Serial.print(" Z: ");
//  Serial.println(z);
//}


