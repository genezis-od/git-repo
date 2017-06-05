/*
http://we.easyelectronics.ru/STM8/8l-kurs-chast-5-taymery-nachalo.html

Код мигалки светодиода на Таймере1

LED - PC3
*/

// work in master branch - оабота в ветве мастер

// add some comment in main.c

// adding some functionality in this code--

// continue coding...

// указание  - првоерить номер порта светодиода


// team lead development process: changing code

// developing mode start // dev 1 // dev 2

// embedded engineer added some more functionality


#include "iostm8l151g4.h"

 #define STRINGVECTOR(x) #x
 #define ISR( a, b )  \
 _Pragma( STRINGVECTOR( vector = (b) ) )        \
 __interrupt void (a)( void )

// Обработчик прерывания по Таймеру1 (совпадение со значением в ARR)   
ISR(TIM1_OVF, TIM1_OVR_UIF_vector)
{
 PC_ODR_bit.ODR3 ^= 1; //Инвертируем пин со светодиодом

 TIM1_SR1_bit.UIF = 0; // Сброс флага прерывания
};

int main( void )
{
  CLK_CKDIVR = 0;       // предделитель частоты 0 - тактирование ядра 16 MHz (HSI)
  CLK_PCKENR2_bit.PCKEN21 = 1; //Включаем тактирование таймера 1

  PC_DDR_bit.DDR3 = 1;  // PD4 mode - OUT
  PC_CR1_bit.C13 = 1;   

  TIM1_PSCRH = (1599) >> 8;     // Записываем в предделитель значение 1600 (Старший байт)
  TIM1_PSCRL = (1599)& 0xFF;    // Записываем в предделитель значение 1600 (младший байт)
  TIM1_ARRH = (10000) >> 8; //Частота переполнений = 16М / 1600 / 10000 = 1 Гц //(10000) приводится к 8бит Счет идет в диаппазоне [0;ARR], т.е. при коэффициенте 10000 будет деление на 10001
  TIM1_ARRL = (10000)& 0xFF;

  TIM1_CR1_bit.URS = 1; //Прерывание только по переполнению счетчика
  TIM1_EGR_bit.UG = 1;  //Вызываем Update Event

  TIM1_IER_bit.UIE = 1; //Разрешаем прерывание
  TIM1_CR1_bit.CEN = 1; //Запускаем таймер

  asm("rim"); // Разрешить глобально прерывания

  while(1); // Пустой цикл
}




