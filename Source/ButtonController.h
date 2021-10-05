#pragma once
#include <Arduino.h>

// типы подключения кнопки
#define PULL_UP 0                                           // кнопка подтянута к VCC
#define PULL_DOWN 1                                         // кнопка подтянута к GND
// состояние кнопки
#define button_RELEASED 0                                   // кнопка отпущена
#define button_UP 1                                         // кнопка только что отпущена
#define button_PRESSED 2                                    // кнопка нажата, но время удержания не вышло
#define button_HOLDED 3                                     // кнопка удерживается нажатой дольше времени удержания
#define button_CLICK 4                                      // кнопка только что нажата
#define button_DOUBLECLICK 5                                // двойной клик

class ButtonController
{
    public:
                                                            // Варианты инициализации:
                                                            // ButtonController button(пин);   - с привязкой к пину и без указания типа (по умолч. PULL_UP)
                                                            // ButtonController button(пин, тип подключ.); - с привязкой к пину и указанием типа подключения (PULL_UP / PULL_DOWN)
      ButtonController(byte pin, byte mode = PULL_UP);
      void getButtonState();                                // получение состояния кнопки - отпущена/нажата/удерживается
      void setDebounce(word debounce);                      // установка времени антидребезга (по умолчанию 50 мс)
      void setTimeout(word new_timeout);                    // установка таймаута удержания (по умолчанию 500 мс)
      void setDoubleClickTimeout(word new_timeout);            // установка интервала двойного клика
      void setType(byte type);                              // установка типа кнопки (PULL_UP - подтянута к VCC, PULL_DOWN - к GND)
      byte buttonState = BUTTON_RELEASED;                         // текущее состояние кнопки
    private:
      byte _pin = 0;                                        // Пин, на который посажена кнопка
      word _debounce = 50;                                  // Интервал подавления дребезга контактов
      word _timeout = 500;                                  // Интервал удержания кнопки нажатой
      word _doubleclick = 300;                               // Интервал двойного клика
      byte _clickcount = 0;                                 // Счетчик кликов
      byte _type = PULL_UP;                                 // Тип подключения
      bool _flag = false;                                   // Сохраненное состояние кнопки - нажата/не нажата
      bool _deb = false;                                    // Флаг включения подавления дребезга - пока включено, изменения состояния не принимаются
      unsigned long button_timer = 0;                       // Таймер удержания кнопки нажатой
      unsigned long debounce_timer = 0;                     // Таймер подавления дребезга контактов
      unsigned long double_timer = 0;                       // Таймер двойного клика
      bool getButtonFlag();                                 // Получение мгновенного состояния кнопки - нажата/не нажата с учетом типа подключения и без учета дребезга контактов
      void setButtonUpClick(bool flag, unsigned long thisMls);  // Установка кнопке состояния "только что нажата" или "только что отпущена"
};
