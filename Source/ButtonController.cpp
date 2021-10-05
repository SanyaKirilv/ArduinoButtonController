#include "ButtonController.h"
#include <Arduino.h>

ButtonController::ButtonController(byte pin, byte mode)
{
  _pin = pin;
  setMode(mode);
}

void ButtonController::getButtonState()
{
  bool flag = getButtonFlag();
  unsigned long thisMls = millis();
  if (flag == _flag)
  {
    if (!_deb)
    {
      if (!flag)
      {
        buttonState = button_RELEASED;
        if (millis() - double_timer > _doubleclick)
        {
          _clickcount = 0;
        }
      }
      else if (millis() - button_timer < _timeout)
      {
        buttonState = button_PRESSED;
      }
      else
      {
        buttonState = button_HOLDED;
      }
    }
  }
  else
  {
    if (_debounce > 0)
    {
      if (!_deb)
      {
        debounce_timer = thisMls;
        _deb = true;
      } 
      else if (millis() - debounce_timer >= _debounce)
      {
        setButtonUpClick(flag, thisMls);
      }
    }
    else
    {
      setButtonUpClick(flag, thisMls);
    }
  }
}

void ButtonController::setMode(byte mode)
{
  _mode = mode;
  switch (mode)
  {
  case PULL_UP:
    pinMode(_pin, INPUT_PULLUP);
    break;
  default:
    pinMode(_pin, INPUT);
    break;
  }
}

void ButtonController::setDebounce(word debounce)
{
  _debounce = debounce;
}

void ButtonController::setTimeout(word new_timeout)
{
  _timeout = new_timeout;
}

void ButtonController::setDoubleClickTimeout(word new_timeout)
{
  _doubleclick = new_timeout;
}

bool ButtonController::getButtonFlag()
{
  bool val = digitalRead(_pin);
  if (_mode == PULL_UP)
  {
    val = !val;
  }
  return val;
}

void ButtonController::setButtonUpClick(bool flag, unsigned long thisMls)
{
  _deb = false;
  _flag = flag;

  if (flag)
  {
    button_timer = thisMls;
    if (_clickcount == 0)
    {
      buttonState = BUTTON_CLICK;
      _clickcount++;
      double_timer = thisMls;
    }
    else if (millis() - double_timer <= _doubleclick)
    { 
      buttonState = button_DOUBLECLICK;
      _clickcount = 0;
    }
  }
  else
  {
    buttonState = button_UP;
  }
}
