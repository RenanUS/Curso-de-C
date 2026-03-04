#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Endereço comum no Tinkercad é 0x27 ou 0x20
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 7;
const int motorPin = 8;

const float distanciaAtiva = 20.0;   // Ativa abaixo de 20cm
const float distanciaReset = 35.0;   // Só rearma acima de 35cm
const unsigned long tempoAtivo = 10000; // 10 segundos

unsigned long tempoLigado = 0;
unsigned long ultimoCheckLcd = 0;

enum Estado {
  ESPERANDO,
  ATIVO,
  AGUARDANDO_SAIDA // Novo estado para a histerese funcionar
};

Estado estadoAtual = ESPERANDO;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW);

  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
}

void loop() {
  float distancia = medirDistancia();

  switch (estadoAtual) {
    case ESPERANDO:
      // Atualiza o LCD sem usar delay() fixo
      if (millis() - ultimoCheckLcd >= 300) {
        mostrarDistancia(distancia);
        ultimoCheckLcd = millis();
      }

      if (distancia > 0 && distancia < distanciaAtiva) {
        ativarSistema();
        estadoAtual = ATIVO;
      }
      break;

    case ATIVO:
      atualizarContagem();

      if (millis() - tempoLigado >= tempoAtivo) {
        desativarSistema();
        estadoAtual = AGUARDANDO_SAIDA; 
      }
      break;

    case AGUARDANDO_SAIDA:
      // Mostra mensagem pedindo para afastar
      lcd.setCursor(0, 0);
      lcd.print("Saida liberada ");
      lcd.setCursor(0, 1);
      lcd.print("Afaste-se...   ");

      // Só volta a esperar quando a distância for maior que o reset
      if (distancia > distanciaReset || distancia == -1) {
        lcd.clear();
        estadoAtual = ESPERANDO;
      }
      break;
  }
}

float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 30000);
  if (duracao == 0) return -1;
  return duracao * 0.034 / 2.0;
}

void ativarSistema() {
  tempoLigado = millis();
  digitalWrite(ledPin, HIGH);
  digitalWrite(motorPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bem Vindo!");
}

void desativarSistema() {
  digitalWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW);
  lcd.clear();
}

void mostrarDistancia(float d) {
  lcd.setCursor(0, 0);
  lcd.print("Aguardando...  ");
  lcd.setCursor(0, 1);
  if (d > 0) {
    lcd.print("Dist: ");
    lcd.print(d, 1);
    lcd.print(" cm    ");
  } else {
    lcd.print("Sem leitura    ");
  }
}

void atualizarContagem() {
  unsigned long decorrido = millis() - tempoLigado;
  // Evita que o tempo restante fique negativo antes da transição de estado
  long tempoRestante = (long(tempoAtivo) - long(decorrido)) / 1000;
  if (tempoRestante < 0) tempoRestante = 0;

  lcd.setCursor(0, 1);
  lcd.print("Desliga em ");
  lcd.print(tempoRestante);
  lcd.print("s   ");
}