// Copyright EMI- 2024

#include <mbed.h>
#include <cstdint>
#include "mux.h"

int main() {
   while (true) {
        
        // Função para varrer/ler os primeiros 6 canais
        SweepChannel (READ_CHANNEL_UNTIL);
        // Função para printar os primeiros 6 canais
        PrintSweep (READ_CHANNEL_UNTIL);
        // Leitura do canal 7 - Output Voltage
        float voltage_total = ReadChannel(READ_CHANNEL_UNTIL + 1);
        // Leitura do canal 8 - Output Current
        float current_total = ReadChannel(READ_CHANNEL_UNTIL + 2);

        printf("Tensão total: %.2f V\n", voltage_total);
        printf("Corrente total: %.2f A\n", current_total);
        
        // Delay de 2 segundo para visualização no serial monitor
         osDelay(2000);
        
    }
} 