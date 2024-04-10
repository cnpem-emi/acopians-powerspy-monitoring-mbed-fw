// Copyright EMI- 2024

#ifndef INCLUDE_MUX_H_
#define INCLUDE_MUX_H_

#include <mbed.h>

#define S0PIN p18 
#define S1PIN p19
#define S2PIN p20
#define AN0PIN p15

#define READ_CHANNEL_UNTIL 6
#define CHANNEL_CONFIG_LENGTH 3

//Função para calcular a média das leituras
float CalculateAverage( AnalogIn analog_pin,
                        int NUM_MEDIDAS = 10);

// Função para ler os canais do MUX
float ReadChannel(  int channel,
                    float alpha = 1,
                    int beta = 0, 
                    AnalogIn analog_pin = AnalogIn(AN0PIN),
                    int NUM_MEDIDAS = 10,
                    int DELAY = 10); 


void SweepChannel(uint8_t read_channel_until);
void PrintSweep(uint8_t print_channel_until);



#endif // INCLUDE_MUX_H_