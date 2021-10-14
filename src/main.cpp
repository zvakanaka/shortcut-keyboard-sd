/*
 * Original author of Duckduino: Seytonic
 *        https://twitter.com/seytonic
 *        https://www.youtube.com/seytonic
 * GIT:
 *        https://github.com/Seytonic/Duckduino-microSD
 * 
 * DuckyScript documentation:
 *        https://docs.hak5.org/hc/en-us/articles/360047381354-QUACK-and-Ducky-Script-2-0
 */

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <string.h>
#include "Keyboard.h"

#define NUM_KEYS 8

File fileHandler;

/*
  SD board
  VCC -> VCC
  D15 -> SCK
  D14 -> MISO
  D16 -> MOSI
  GND -> GND
  D4  -> CS
*/

#define KEY1 2
#define KEY2 3
#define KEY3 5
#define KEY4 6
#define KEY5 7
#define KEY6 8
#define KEY7 9
#define KEY8 10
// #define KEY9 16 // CANNOT USE (SD uses it)
// #define KEY10 4 // CANNOT USE (SD uses it)

#define KEY_DELAY 200

void executeScript(String scriptFileName);
void Line(String l);
void Press(String b);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("STARTUP");

  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);
  pinMode(KEY4, INPUT_PULLUP);
  pinMode(KEY5, INPUT_PULLUP);
  pinMode(KEY6, INPUT_PULLUP);
  pinMode(KEY7, INPUT_PULLUP);
  pinMode(KEY8, INPUT_PULLUP);
  if (NUM_KEYS == 10) {
  // pinMode(KEY9, INPUT_PULLUP);
  // pinMode(KEY10, INPUT_PULLUP);
  }

  if (!SD.begin(4)) {
    Serial.println("SD FAILURE");
    return;
  }
}

void executeScript(String scriptFileName) {
  char buf[30];
  scriptFileName.toCharArray(buf, scriptFileName.length() + 1);
  Serial.print("LOOKING FOR FILE ");
  Serial.println(buf);
  fileHandler = SD.open(buf);
  if (fileHandler) {
    Serial.println("FOUND FILE " + scriptFileName);
    Keyboard.begin();

    String line = "";
    while (fileHandler.available()) {
      char m = fileHandler.read();
      if (m == '\n') {
        Serial.println("   " + line);
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

void Press(String b) {
  if (b.length() == 1) {
    char c = b[0];
    Keyboard.press(c);
  } else if (b.equals("ENTER")) {
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
  }
}

void checkKey(unsigned int key, unsigned int textFileNumber) {
  if (digitalRead(key) == LOW) {
    // Serial.print(key);
    // Serial.println(" pressed");
    String fileName = String(textFileNumber) + ".txt";
    executeScript(fileName);
  
    delay(KEY_DELAY); // prevent double-press
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
  if (NUM_KEYS == 10) {
    // checkKey(KEY9, 9);
    // checkKey(KEY10, 10);
  }
}
