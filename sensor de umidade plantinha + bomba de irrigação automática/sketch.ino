#include <LiquidCrystal.h> // biblioteca para o lcd funcionar

// define onde estão conectados os pinos do LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 14, 27, 26, 25, 33);

#define SENSOR_PIN 34       // define onde está conectado o pino do sensor de umidade
#define LED_VERDE 15        // define onde está conectado o pino do LED verde
#define LED_AMARELO 2       // define onde está conectado o pino do LED amarelo
#define LED_VERMELHO 4      // define onde está conectado o pino do LED vermelho
#define RELAY_PIN 13        // define onde está conectado o pino do relay (IN), responsável pela bomba de irrigação

void setup() {
Serial.begin(115200); // inicializa a comunicação serial do esp32 e o computador em uma taxa de transmissão de 115200 bits por segundo

pinMode(LED_VERDE, OUTPUT);
pinMode(LED_AMARELO, OUTPUT);
pinMode(LED_VERMELHO, OUTPUT);
pinMode(RELAY_PIN, OUTPUT);  // configura o pino do relay como saída

lcd.begin(16, 2); // inicializa o LCD com 16 colunas e 2 linhas
lcd.print("Iniciando...");
delay(2000);
lcd.clear();
}

void loop() {
int leitura = analogRead(SENSOR_PIN); // lê o valor do sensor de umidade (0–4095)
float umidade = map(leitura, 0, 4095, 100, 0); // mapeia para 0–100%

Serial.print("Umidade: ");
Serial.println(umidade);

// atualiza os valores no LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Umidade: ");
lcd.print(umidade, 1);
lcd.print("%");

lcd.setCursor(0, 1); // segunda linha

// Lógica de controle dos LEDs
if (umidade >= 60) {  // Umidade muito alta
digitalWrite(LED_VERDE, LOW);    // Desliga o LED verde
digitalWrite(LED_AMARELO, LOW);  // Desliga o LED amarelo
digitalWrite(LED_VERMELHO, HIGH); // liga o LED vermelho
digitalWrite(RELAY_PIN, LOW);     // desliga o LED azul
lcd.print("Status: Alta");
}
else if (umidade >= 20 && umidade < 60) {  // Umidade boa
digitalWrite(LED_VERDE, HIGH);   // Liga o LED verde
digitalWrite(LED_AMARELO, LOW);  // Desliga o LED amarelo
digitalWrite(LED_VERMELHO, LOW); // Desliga o LED vermelho
digitalWrite(RELAY_PIN, LOW);      // Desliga o LED azul
lcd.print("Status: Boa");
}
else {  // Umidade baixa
digitalWrite(LED_VERDE, LOW);    // Desliga o LED verde
digitalWrite(LED_AMARELO, HIGH); // Liga o LED amarelo
digitalWrite(LED_VERMELHO, LOW); // Desliga o LED vermelho
digitalWrite(RELAY_PIN, HIGH); 
lcd.print("Status: Baixa");
}

delay(2000); // espera 2 segundos antes de realizar a próxima leitura
}