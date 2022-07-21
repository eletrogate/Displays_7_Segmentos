// Arduino - Modulo Display TM1637
// baseado no exemplo da biblioteca TM1637
// https://blog.eletrogate.com/guia-completo-dos-displays-de-7-segmentos-arduino/

#include <Arduino.h>               // biblioteca Arduino 
#include <TM1637Display.h>         // biblioteca TM1637

#define CLK 2                      // pino D2 Arduino conectado ao pino CLK do modulo TM1637
#define DIO 3                      // pino D2 Arduino conectado ao pino DIO do modulo TM1637

#define TEST_DELAY   1000          // atraso de tempo entre os testes do display = 1 segundo

const uint8_t SEG_DONE[] =         // matriz com a palavra DONE
{
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

TM1637Display display(CLK, DIO);   // inicializa o objeto

void setup()
{
}

void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };   // matriz todos os bits ON
    
  display.setBrightness(0x0f);                   // controle do brilho 0F = maximo

  display.setSegments(data);                     // teste do display - todos segmentos ativados
  delay(TEST_DELAY);

  data[0] = display.encodeDigit(0);              // display mostrando o numero 0123
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);
  delay(TEST_DELAY);

  display.showNumberDec(321, true);              // Mostra 0301 com zero à esquerda
  delay(TEST_DELAY);
  display.showNumberDec(321, false);             // Mostra _301 sem zero à esquerda
  delay(TEST_DELAY);

  display.showNumberDec(-27, false);             // Mostra -27 sem zero à esquerda
  delay(TEST_DELAY);

  display.setSegments(SEG_DONE);                 // mostra a palavra dOnE
  delay(TEST_DELAY);
}