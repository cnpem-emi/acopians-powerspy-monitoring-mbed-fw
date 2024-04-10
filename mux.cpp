// Copyright EMI- 2024

#include "mux.h"
#include <cmath>
#include <cstdint>

float SWEEP_RESULTS[READ_CHANNEL_UNTIL];  

// Pinos de seleção do MUX
DigitalOut DIGITAL_PINS[CHANNEL_CONFIG_LENGTH] = { DigitalOut(S0PIN),
                                                   DigitalOut(S1PIN),
                                                   DigitalOut(S2PIN)
                                                 };

// Pino ADC do uC
AnalogIn   AN0  (AN0PIN);

// Função para selecionar cada canal de acordo com S0,S1 E S2
void SetChannelToRead (int channel){

    // Seleciona o canal de acordo com a configuração de S0,S1 e S2
    for (int i = 0; i < CHANNEL_CONFIG_LENGTH; i++)
    {   
        DIGITAL_PINS[i] =  ((channel) >> i) & 0b1;
    }    
}

// Função para calcular a média
float CalculateAverage(AnalogIn analog_pin, int NUM_MEDIDAS)
{
    // Array para armazenar as medidas
    float medidas[NUM_MEDIDAS]; 
    // Variável para somar as medidas
    float soma = 0; 
  
    for (int i = 0; i < NUM_MEDIDAS; i++) {

        // Converte o valor analógico em digital
        float voltage_analog_pin = analog_pin.read_u16();
        float voltage = (voltage_analog_pin/pow(2, 16)) * 3.3;
   
        // Armazena a medida atual no array
        medidas[i] = voltage;
    
        // Soma a medida atual à variável de soma
        soma += voltage;
    }

    // Calcula a média das medidas
    float media = soma / NUM_MEDIDAS;
  
    return media;
}

// Função para ler canal
float ReadChannel(  int channel,
                    float alpha,
                    int beta, 
                    AnalogIn analog_pin,
                    int NUM_MEDIDAS,
                    int DELAY) 
{
    //Função para selecionar cada canal do MUX
    SetChannelToRead(channel);

    // Tempo para garantir configuração do MUX e estabilização da medida e ainda assegurar taxa de aquisição de 10Hz
    // No pior cenário o MUX pode demorar 520ns para acionar cada canal
    // 10us = 10000ns
     wait_us(10);
    
    
    float value = CalculateAverage(analog_pin, NUM_MEDIDAS) * alpha + beta;

    return value;
}

// Função para varrer os canais
void SweepChannel(uint8_t read_channel_until) {
    // Lê os canais de 0 a 6 do MUX
       for (int i = 0; i < read_channel_until; i++) {
           SWEEP_RESULTS[i] = ReadChannel(i);
            
        }
}

// Função para printar as medidas no serial monitor
void PrintSweep(uint8_t print_channel_until) {
    // Printa os Canais do Mux
       for (int i = 0; i < print_channel_until; i++) {
            
           if (i % 2 == 0) {
               // Tensão
               printf("Tensão (Vmon) S%d: %.2f V\n", i/ 2 + 1, SWEEP_RESULTS[i]);
            } else {
                   // Corrente
                printf("Corrente (Imon) S%d: %.2f A\n", i / 2 + 1, SWEEP_RESULTS[i]);
            }
            
        } 
}