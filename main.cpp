#include <mbed.h>

// Define os pinos de seleção do MUX
DigitalOut S0(p18);
DigitalOut S1(p19);
DigitalOut S2(p20);

// Define o pino de leitura do Mbed LPC1768
AnalogIn AN0(p15);

int main() {
  // Loop infinito
  while (true) {
    // Lê os canais de 0 a 7
    for (int i = 0; i < 8; i++) {
      // Seleciona o canal
      S0 = (i & 0b1) >> 0;
      S1 = (i & 0b10) >> 1;
      S2 = (i & 0b100) >> 2;

      // Lê o valor analógico
      int valor = AN0.read_u16();

      // Converte o valor analógico para digital
      float tensao = valor * (3.3 / 65535.0);

      // Imprime a tensão
      if (i % 2 == 0) {
        printf("Tensão %d: %f V\n", i / 2 + 1, tensao);
      } else {
        // Converte para corrente (assumindo shunt de 0.25 ohm)
        float corrente = tensao / 0.25;
        printf("Corrente %d: %f A\n", i / 2 + 1, corrente);
      }
    }

    // Lê a tensão total (assumindo que está conectada a um canal)
    float tensaoTotal = AN0.read_u16() * (3.3 / 65535.0);

    // Lê a corrente total (assumindo que está conectada a um canal e shunt de 0.25 ohm)
    float correnteTotal = AN0.read_u16() * (3.3 / 65535.0) / 0.25;

    // Imprime a tensão total e a corrente total
    printf("Tensão total: %f V, Corrente total: %f A\n", tensaoTotal, correnteTotal);

    // Delay de 1 segundo
    ThisThread::sleep_for(2000ms);
  }
}
