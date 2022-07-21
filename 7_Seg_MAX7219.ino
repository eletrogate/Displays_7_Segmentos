// Arduino - Módulo Display 4 dígitos com MAX7219
// baseado no exemplo da biblioteca LedMatrixDriver
// https://blog.eletrogate.com/guia-completo-dos-displays-de-7-segmentos-arduino/
// SPI Interface MOSI(D11)= DIN , SCK(D13)= CLK
// Sequencia dos digitos invertida - Digito 0 é o mais da esquerda

#include <LEDMatrixDriver.hpp>

const int LEDMATRIX_CS_PIN = 6;                       // MAX7219 Load/CS(pin 12) = Arduino D6
const int NO_OF_DRIVERS = 1;                          // numero de chips MAX7219

int n;                                                // variável numero de digitos
int digits[4];                                        // matriz com 4 algarismos
long value;                                           // variável do valor
long divider;                                         // variável do divisor

int digito;                                           // variável do digito
int numero;                                           // variável do valor do digito
int atraso = 200;                                     // atraso de 200 milisegundos

LEDMatrixDriver lmd(NO_OF_DRIVERS, LEDMATRIX_CS_PIN); // inicializando a instância

void setup()
{
  lmd.setEnabled(true);                               // ativa configuração
  lmd.setIntensity(15);                               // configura brilho 0 = min, 15 = max
  lmd.setScanLimit(3);                                // 0-7: mostra 4 digitos n+1
  lmd.setDecode(0xFF);                                // ativa "BCD tipo B"
}

void loop()
{
  for (int i = 0; i < 10000; i++)                     // contagem de 0 a 9999
  {
    n = 4;                                            // numero de casas decimais
    value = i ;                                       // numero a ser desmembrado em digitos
    divider = 1000;                                   // divisor por 1000
    while (n--)                                       // contagem regressiva dos dígitos
    {
      digits[n] = (value / divider);                  // carrega matriz com a divisão
      value = value - (digits[n] * divider);          // equação
      divider = divider / 10;                         // divisor dividido por 10
    }

    n = 4;                                            // numero de casas decimais
    while (n--)                                       // contagem regressiva do dígitos
    {
      if (n == 0) digito = 0;                         // endereça o digito 4
      if (n == 1) digito = 1;                         // endereça o digito 3        
      if (n == 2) digito = 2;                         // endereça o digito 2 
      if (n == 3) digito = 3;                         // endereça o digito 1 
      
      numero = digits[n];                             // numero a ser mostrado 
      lmd.setDigit(digito, numero, false);            // setDigit (digito, valor, bool ponto decimal)
      lmd.display();                                  // mostra no display
    }
    delay (atraso);                                   // atraso de tempo
  }

  lmd.setDigit(3, LEDMatrixDriver::BCD_H);           // mostra a palavra HELP por um segundo
  lmd.setDigit(2, LEDMatrixDriver::BCD_E);
  lmd.setDigit(1, LEDMatrixDriver::BCD_L);
  lmd.setDigit(0, LEDMatrixDriver::BCD_P);
  lmd.display();                                     // mostra no display
  delay(1000);                                       // atraso de 1 segundo
}