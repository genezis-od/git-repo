/*
http://we.easyelectronics.ru/STM8/8l-kurs-chast-5-taymery-nachalo.html

��� ������� ���������� �� �������1

LED - PC3
*/

// work in master branch - ������ � ����� ������

// add some comment in main.c

// adding some functionality in this code--

// continue coding...

// ��������  - ��������� ����� ����� ����������


// team lead development process: changing code

// developing mode start // dev 1 // dev 2

// embedded engineer added some more functionality


#include "iostm8l151g4.h"

 #define STRINGVECTOR(x) #x
 #define ISR( a, b )  \
 _Pragma( STRINGVECTOR( vector = (b) ) )        \
 __interrupt void (a)( void )

// ���������� ���������� �� �������1 (���������� �� ��������� � ARR)   
ISR(TIM1_OVF, TIM1_OVR_UIF_vector)
{
 PC_ODR_bit.ODR3 ^= 1; //����������� ��� �� �����������

 TIM1_SR1_bit.UIF = 0; // ����� ����� ����������
};

int main( void )
{
  CLK_CKDIVR = 0;       // ������������ ������� 0 - ������������ ���� 16 MHz (HSI)
  CLK_PCKENR2_bit.PCKEN21 = 1; //�������� ������������ ������� 1

  PC_DDR_bit.DDR3 = 1;  // PD4 mode - OUT
  PC_CR1_bit.C13 = 1;   

  TIM1_PSCRH = (1599) >> 8;     // ���������� � ������������ �������� 1600 (������� ����)
  TIM1_PSCRL = (1599)& 0xFF;    // ���������� � ������������ �������� 1600 (������� ����)
  TIM1_ARRH = (10000) >> 8; //������� ������������ = 16� / 1600 / 10000 = 1 �� //(10000) ���������� � 8��� ���� ���� � ���������� [0;ARR], �.�. ��� ������������ 10000 ����� ������� �� 10001
  TIM1_ARRL = (10000)& 0xFF;

  TIM1_CR1_bit.URS = 1; //���������� ������ �� ������������ ��������
  TIM1_EGR_bit.UG = 1;  //�������� Update Event

  TIM1_IER_bit.UIE = 1; //��������� ����������
  TIM1_CR1_bit.CEN = 1; //��������� ������

  asm("rim"); // ��������� ��������� ����������

  while(1); // ������ ����
}




