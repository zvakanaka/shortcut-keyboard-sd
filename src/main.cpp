/*
 * Original author of Duckduino: Seytonic
 *        https://twitter.com/seytonic
 *        https://www.youtube.com/seytonic
 *        https://github.com/Seytonic/Duckduino-microSD
 *
 * DuckyScript documentation:
 *        https://docs.hak5.org/hc/en-us/articles/360047381354-QUACK-and-Ducky-Script-2-0
 *
 * Pro Micro pinout:
 *        https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/all#hardware-overview-pro-micro
 */

#include <Arduino.h>
#include <HID-Project.h>
#include <SD.h>
#include <SPI.h>
#include <string.h>

#define DEBUG
// #define WAIT_FOR_SERIAL

File fileHandler;
// sets keys to 1,2,3,4,5,6,7,8 if SD fails
boolean factoryTestMode = false;  // NOTE: if SD fails, this is set to true

/*
  SD board
  VCC -> VCC
  D15 -> SCK
  D14 -> MISO
  D16 -> MOSI
  GND -> GND
  D4  -> CS
*/

// 2 and 3 are reserved for i2c, but would work for buttons if needed
#define KEY1 18  // (A0)
#define KEY2 19  // (A1)
#define KEY3 5   // (5)
#define KEY4 6   // (6)
#define KEY5 7   // (7)
#define KEY6 8   // 8
#define KEY7 9   // 9
#define KEY8 10  // 10

#define KEY_DELAY 150

void executeScript(String scriptFileName);
void Line(String l);
void Press(String b);

void setup() {
  Serial.begin(9600);
#ifdef SCREEN_KEY
  u8x8.begin();
#endif
  delay(200);
#ifdef WAIT_FOR_SERIAL
  while (!Serial) {
    ;  // wait for serial port to connect
  }
#endif
  Serial.println("STARTUP");

  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  pinMode(KEY4, INPUT_PULLUP);
  pinMode(KEY5, INPUT_PULLUP);
  pinMode(KEY6, INPUT_PULLUP);
  pinMode(KEY7, INPUT_PULLUP);
  pinMode(KEY8, INPUT_PULLUP);

  if (!SD.begin(4)) {
    Serial.println("SD FAILURE");
    Serial.println("Falling back to factory test mode (1,2,3,4,5,6,7,8)");
    factoryTestMode = true;
  }
}

void executeScript(String scriptFileName) {
  char buf[30];
  scriptFileName.toCharArray(buf, scriptFileName.length() + 1);
  #ifdef DEBUG
    Serial.print("LOOKING FOR FILE ");
    Serial.println(buf);
  #endif
  fileHandler = SD.open(buf);
  if (fileHandler) {
    #ifdef DEBUG
      Serial.println("FOUND FILE " + scriptFileName);
    #endif
    Keyboard.begin();
    Consumer.begin(); // Initializes the media keyboard

    String line = "";

    while (fileHandler.available()) {
      char m = fileHandler.read();
      if (m == '\n') {
        #ifdef DEBUG
          Serial.println("   " + line);
        #endif
        Line(line);
        line = "";
      } else if ((int)m != 13) {
        line += m;
      }
    }
    Line(line);

    fileHandler.close();
  } else {
    Serial.println("FILE NOT FOUND " + scriptFileName);
  }

  Keyboard.end();
}

void Line(String l) {
  int space_1 = l.indexOf(" ");
  if (space_1 == -1) {
    Press(l);
  } else if (l.substring(0, space_1) == "STRING") {
    Keyboard.print(l.substring(space_1 + 1));
  } else if (l.substring(0, space_1) == "DELAY") {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  } else if (l.substring(0, space_1) == "REM") {
  } else {
    String remain = l;

    while (remain.length() > 0) {
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1) {
        Press(remain);
        remain = "";
      } else {
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
    }
  }

  Keyboard.releaseAll();
}

// add support for keys from here as needed https://github.com/NicoHood/HID/blob/master/src/HID-APIs/ConsumerAPI.h
void Press(String b) {
  if (b.length() == 1) {
    char c = b[0];
    Keyboard.press(c);
  } else if (b.equals("MEDIA_PAUSE")) {
    Consumer.write(MEDIA_PAUSE);
  } else if (b.equals("MEDIA_VOLUME_MUTE")) {
    Consumer.write(MEDIA_VOLUME_MUTE);
  } else if (b.equals("MEDIA_VOL_MUTE")) {
    Consumer.write(MEDIA_VOL_MUTE);
  } else if (b.equals("MEDIA_VOLUME_UP")) {
    Consumer.write(MEDIA_VOLUME_UP);
  } else if (b.equals("MEDIA_VOL_UP")) {
    Consumer.write(MEDIA_VOL_UP);
  } else if (b.equals("MEDIA_VOLUME_DOWN")) {
    Consumer.write(MEDIA_VOLUME_DOWN);
  } else if (b.equals("MEDIA_VOL_DOWN")) {
    Consumer.write(MEDIA_VOL_DOWN);
  } else if (b.equals("CONSUMER_BRIGHTNESS_UP")) {
    Consumer.write(CONSUMER_BRIGHTNESS_UP);
  } else if (b.equals("CONSUMER_BRIGHTNESS_DOWN")) {
    Consumer.write(CONSUMER_BRIGHTNESS_DOWN);
  } else if (b.equals("CONSUMER_SCREENSAVER")) {
    Consumer.write(CONSUMER_SCREENSAVER);
  } else if (b.equals("MEDIA_PLAY_PAUSE")) {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }  else if (b.equals("ENTER")) {
    Keyboard.press(KEY_RETURN);
  } else if (b.equals("CTRL")) {
    Keyboard.press(KEY_LEFT_CTRL);
  } else if (b.equals("SHIFT")) {
    Keyboard.press(KEY_LEFT_SHIFT);
  } else if (b.equals("ALT")) {
    Keyboard.press(KEY_LEFT_ALT);
  } else if (b.equals("GUI")) {
    Keyboard.press(KEY_LEFT_GUI);
  } else if (b.equals("UP") || b.equals("UPARROW")) {
    Keyboard.press(KEY_UP_ARROW);
  } else if (b.equals("DOWN") || b.equals("DOWNARROW")) {
    Keyboard.press(KEY_DOWN_ARROW);
  } else if (b.equals("LEFT") || b.equals("LEFTARROW")) {
    Keyboard.press(KEY_LEFT_ARROW);
  } else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) {
    Keyboard.press(KEY_RIGHT_ARROW);
  } else if (b.equals("DELETE")) {
    Keyboard.press(KEY_DELETE);
  } else if (b.equals("PAGEUP")) {
    Keyboard.press(KEY_PAGE_UP);
  } else if (b.equals("PAGEDOWN")) {
    Keyboard.press(KEY_PAGE_DOWN);
  } else if (b.equals("HOME")) {
    Keyboard.press(KEY_HOME);
  } else if (b.equals("ESC")) {
    Keyboard.press(KEY_ESC);
  } else if (b.equals("INSERT")) {
    Keyboard.press(KEY_INSERT);
  } else if (b.equals("TAB")) {
    Keyboard.press(KEY_TAB);
  } else if (b.equals("END")) {
    Keyboard.press(KEY_END);
  } else if (b.equals("CAPSLOCK")) {
    Keyboard.press(KEY_CAPS_LOCK);
  } else if (b.equals("F1")) {
    Keyboard.press(KEY_F1);
  } else if (b.equals("F2")) {
    Keyboard.press(KEY_F2);
  } else if (b.equals("F3")) {
    Keyboard.press(KEY_F3);
  } else if (b.equals("F4")) {
    Keyboard.press(KEY_F4);
  } else if (b.equals("F5")) {
    Keyboard.press(KEY_F5);
  } else if (b.equals("F6")) {
    Keyboard.press(KEY_F6);
  } else if (b.equals("F7")) {
    Keyboard.press(KEY_F7);
  } else if (b.equals("F8")) {
    Keyboard.press(KEY_F8);
  } else if (b.equals("F9")) {
    Keyboard.press(KEY_F9);
  } else if (b.equals("F10")) {
    Keyboard.press(KEY_F10);
  } else if (b.equals("F11")) {
    Keyboard.press(KEY_F11);
  } else if (b.equals("F12")) {
    Keyboard.press(KEY_F12);
  } else if (b.equals("SPACE")) {
    Keyboard.press(' ');
  } else if (b.startsWith("0x")) {  
    // convert hex strings to integers (integers are the same as raw hex to HID-Project)
    // possibilities:
    //   https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h
    //   https://github.com/NicoHood/HID/blob/master/src/HID-APIs/ConsumerAPI.h
    //   http://www.freebsddiary.org/APC/usb_hid_usages.php
    // https://github.com/NicoHood/HID/blob/4bf6cd6167b1152a292bbc62793a85ab69070895/examples/Keyboard/ImprovedKeyboard/ImprovedKeyboard.ino#L43
    Keyboard.write(KeyboardKeycode((int)strtol(b.c_str(), 0, 16)));
  }
}

void checkKey(unsigned int key, unsigned int keyNumber) {
  if (digitalRead(key) == LOW) {
#ifdef SCREEN_KEY
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    char text[1];
    text[0] = keyNumber + '0';
    text[1] = '\0';
    u8x8.drawString(0, 1, text);
#endif SCREEN_KEY
#ifdef DEBUG
    Serial.print(keyNumber);
    Serial.println(" pressed");
#endif
    if (factoryTestMode) {
      Keyboard.press(keyNumber + '0');
    } else {
      String fileName = String(keyNumber) + ".txt";
      executeScript(fileName);
    }

    delay(KEY_DELAY);  // prevent double-press
  }
  if (digitalRead(key) == HIGH) {
    Keyboard.releaseAll();
  }
}

void loop() {
  checkKey(KEY1, 1);
  checkKey(KEY2, 2);
  checkKey(KEY3, 3);
  checkKey(KEY4, 4);
  checkKey(KEY5, 5);
  checkKey(KEY6, 6);
  checkKey(KEY7, 7);
  checkKey(KEY8, 8);
}
