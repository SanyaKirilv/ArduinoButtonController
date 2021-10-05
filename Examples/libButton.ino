#include "ButtonController.h"

ButtonController button(13, PULL_UP);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  static int8_t bt = -1;
  button.getButtonState();
  if (bt != button.buttonState)
  {
    bt = button.buttonState;
    switch (bt)
    {
      case BUTTON_RELEASED:
        //Serial.println("Button is released");
        break;
      case button_UP:
        Serial.println("Button up");
        break;
      case button_PRESSED:
        //Serial.println("Button is pressed");
        break;
      case button_HOLDED:
        Serial.println("Button is holded");
        break;
      case button_CLICK:
        Serial.println("Button click");
        break;
      case button_DOUBLECLICK:
        Serial.println("Button double click");
        break;
    }
  }
}
