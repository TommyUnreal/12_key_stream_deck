// key configuration
#define BUTTON_KEY_1  KEY_F13
#define BUTTON_KEY_2  KEY_F14
#define BUTTON_KEY_3  KEY_F15
#define BUTTON_KEY_4  KEY_F16
#define BUTTON_KEY_5  KEY_F17
#define BUTTON_KEY_6  KEY_F18
#define BUTTON_KEY_7  KEY_F19
#define BUTTON_KEY_8  KEY_F20
#define BUTTON_KEY_9  KEY_F21
#define BUTTON_KEY_10 KEY_F22
#define BUTTON_KEY_11 KEY_F23
#define BUTTON_KEY_12 KEY_F24

// pin configuration
#define BUTTON_PIN_1  2
#define BUTTON_PIN_2  3
#define BUTTON_PIN_3  4
#define BUTTON_PIN_4  5
#define BUTTON_PIN_5  6
#define BUTTON_PIN_6  7
#define BUTTON_PIN_7  8
#define BUTTON_PIN_8  9
#define BUTTON_PIN_9  10
#define BUTTON_PIN_10 14
#define BUTTON_PIN_11 15
#define BUTTON_PIN_12 16
// ---------------------------------
 
#include "Keyboard.h"
 
// class to handle press release and debounce time
class button {
  public:
  const char key;
  const uint8_t pin;
 
  button(uint8_t k, uint8_t p) : key(k), pin(p){}

  void press(boolean state){
    if(state == pressed || (millis() - last_pressed  <= debounce_time)){
      return;
    }
 
    last_pressed = millis();
    state ? Keyboard.press(key) : Keyboard.release(key);    
    pressed = state;
  }
 
  void update(){
    press(!digitalRead(pin));
  }
 
  private:
  const unsigned long debounce_time = 10;
  unsigned long last_pressed        = 0;
  boolean pressed                   = 0;
} ;
 
// Button array for 12 keys setup
button buttons[] = {
  {BUTTON_KEY_1,  BUTTON_PIN_1},
  {BUTTON_KEY_2,  BUTTON_PIN_2},
  {BUTTON_KEY_3,  BUTTON_PIN_3},
  {BUTTON_KEY_4,  BUTTON_PIN_4},
  {BUTTON_KEY_5,  BUTTON_PIN_5},
  {BUTTON_KEY_6,  BUTTON_PIN_6},
  {BUTTON_KEY_7,  BUTTON_PIN_7},
  {BUTTON_KEY_8,  BUTTON_PIN_8},
  {BUTTON_KEY_9,  BUTTON_PIN_9},
  {BUTTON_KEY_10, BUTTON_PIN_10},  
  {BUTTON_KEY_11, BUTTON_PIN_11},  
  {BUTTON_KEY_12, BUTTON_PIN_12},
};
const uint8_t num_buttons = sizeof(buttons) / sizeof(button);
 
void setup() { 
  
 // Map pins
  for(int i = 0; i < num_buttons; i++){
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}
 
void loop() {
  for(int i = 0; i < num_buttons; i++){
    buttons[i].update();
  }
}
