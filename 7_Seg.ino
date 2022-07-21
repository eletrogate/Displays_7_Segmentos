// Arduino - Display 7 Segmentos com PCF8574
// https://blog.eletrogate.com/guia-completo-dos-displays-de-7-segmentos-arduino
// Interface Arduino I2C > SDA = A4   SCL = A5  Resistor 4K7 pullup
// baseado em https://www.instructables.com/id/Arduino-and-PCF8574-IO-Expander-Binary-Counter-and
// baseado em http://forum.arduino.cc/index.php?topic=307479.15

#include <Wire.h>                             // biblioteca wire 

#define digito_1 0x20                         // endereço do display digito 1 - lado direito
#define digito_2 0x21                         // endereço do display digito 2 - lado esquerdo

int addressDisplay;                           // variável do endereço do display
int dataDisplay;                              // variável do dado do display
int atraso = 300;                             // atraso de 300 milisegundos

int n;                                        // variável numero de dígitos
int digits[2];                                // matriz com dois algarismos
long value;                                   // variável do numero
long divider;                                 // variável do divisor

void setup()
{
  Wire.begin();                               // inicializa a interface I2C
}

void pcf8574Write(byte address, byte data )   // envia dado para PCF8574 - interface I2C
{
  Wire.beginTransmission(address);            // envia o endereço do PCF8574
  Wire.write(data);                           // envia o dado para o PCF8574
  Wire.endTransmission();                     // termina transmissão
}

void displayNumber ()
{
  if (digits[n] == 0) dataDisplay = 0x81 ;     // mostra número 0
  if (digits[n] == 1) dataDisplay = 0xCF ;     // mostra número 1
  if (digits[n] == 2) dataDisplay = 0x92 ;     // mostra número 2
  if (digits[n] == 3) dataDisplay = 0x86 ;     // mostra número 3
  if (digits[n] == 4) dataDisplay = 0xCC ;     // mostra número 4
  if (digits[n] == 5) dataDisplay = 0xA4 ;     // mostra número 5
  if (digits[n] == 6) dataDisplay = 0xA0 ;     // mostra número 6
  if (digits[n] == 7) dataDisplay = 0x8F ;     // mostra número 7
  if (digits[n] == 8) dataDisplay = 0x80 ;     // mostra número 8
  if (digits[n] == 9) dataDisplay = 0x8C ;     // mostra número 9
}

void printDisplay ()                                 // mostra algarismos em 2 displays
{
  for (int i = 0; i < 100; i++)                      // contagem de 0 a 99
  {
    n = 2;                                           // número de casas decimais 
    value = i ;                                      // número a ser desmembrado em digitos
    divider = 10;                                    // divisor por 10
    while (n--)                                      // contagem regressiva dos dígitos
    {
      digits[n] = (value / divider);                 // carrega matriz com a divisão
      value = value - (digits[n] * divider);         // equação 
      divider = divider/10;                          // divisor dividido por 10
    }

    n = 2;                                           // número de casas decimais
    while (n--)                                      // contagem regressiva dos dígitos
    {
      if (n == 0)                                    // se for o primeiro dígito - lado direito 
      {
        addressDisplay = digito_1 ;                  // endereça o PCF8574
        displayNumber ();                            // mostra o número 
      }
   
      if (n == 1)                                    // se for o segundo dígito - lado esquerdo
      {
        addressDisplay = digito_2 ;                  // endereça o PCF8574
        displayNumber ();                            // mostra o número
      }
      
      pcf8574Write(addressDisplay, dataDisplay);     // envia dado para PCF8574 endereçado
    }
    delay (atraso);                                  // atraso de tempo
  }
}

void loop()
{
  printDisplay ();                                  // mostra a contagem nos displays
}

// Para mostrar carater A = 0x88
// Para mostrar carater B = 0xE0
// Para mostrar carater C = 0xB1
// Para mostrar carater D = 0xC2
// Para mostrar carater E = 0xB0
// Para mostrar carater F = 0xB8
// Para mostrar todos segmentos ligados = 0x00<code>
</code>