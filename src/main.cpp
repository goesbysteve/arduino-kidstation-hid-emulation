// KidStation Controller Keybord HID Emulator v 0.1

#include <Arduino.h>
#include <Bounce2.h>
#include <Keyboard.h>

#define NUM_BUTTONS 4

const int RXLED = 17;

struct Key {
  char keycode;
  Bounce* bounce;
};

Key keys[NUM_BUTTONS];

Key key(char keycode, int pin) {
  Key *ret = new Key;
  ret->keycode = keycode;
  ret->bounce = new Bounce();
  // pinMode(pin, INPUT_PULLUP);
  ret->bounce->attach(pin, INPUT_PULLUP);
  ret->bounce->interval(10);
  return *ret;
}

void setupKeys() {
  keys[0] = key('w', 4);
  keys[1] = key('s', 7);
  keys[2] = key('a', 5);
  keys[3] = key('d', 6);
  delay(10); // Allow pullup to settle
}

void setup() {
  setupKeys();
  /* for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i].attach(BUTTON_PINS[i][0], INPUT_PULLUP);
    buttons[i].interval(25);
  } */
  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("KidStation Controller Keybord Emulator v 0.1");
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    keys[i].bounce->update();
    if (keys[i].bounce->fell()) {
      Keyboard.press(keys[i].keycode);
      Serial.println("key pressed");
      digitalWrite(RXLED, LOW);
      delay(100);
      digitalWrite(RXLED, HIGH);
    } else if (keys[i].bounce->rose()) {
      Keyboard.release(keys[i].keycode);
      Serial.println("key released");
    }
  }
  /* for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i].update();
    if (buttons[i].fell()) {
      Keyboard.press(char(BUTTON_PINS[i][1]));
      Serial.println("key pressed");
      digitalWrite(RXLED, LOW);
      delay(100);
      digitalWrite(RXLED, HIGH);
    }
    if (buttons[i].rose()) {
      Keyboard.release(char(BUTTON_PINS[i][1]));
      Serial.println("key released");
    }
  }*/

}
