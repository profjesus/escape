#include <LiquidCrystal.h>

// Inicializamos la librería al asignar pines de la tarjeta
// a los pines requeridos para la interface con el display LCD
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Definition of RGB LED pins: outputs
#define redPin 11
#define greenPin 10
#define bluePin 9 

//Definition of LED pins: outputs
#define redLedPin 8
#define greenLedPin 7
#define blueLedPin 6

// Defino as cores:
#define NADA -1
#define VERMELLO 0
#define VERDE 1
#define AZUL 2
#define MORADO 3
#define AMARELO 4
#define NEGRO 5
#define BRANCO 6

// Valores RGB para cada cor
int rgbCores[7][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 0, 255}, {200, 100, 0}, { 0, 0, 0}, {255, 255, 255} };

// Valores para os LEDs monocores
int ledCores[3] = {redLedPin, greenLedPin, blueLedPin};

int contador = 0;
int indice = 0;
int indiceLed = 0;

// Secuencia de cores
int secuenciaRgb[10] = { AMARELO, MORADO, AZUL, BRANCO, VERMELLO, AMARELO, NEGRO, BRANCO, VERDE, MORADO };
int secuenciaLed[9] = { AZUL, VERMELLO, NADA, VERMELLO, AZUL, NADA, AZUL, VERDE, VERMELLO };

void setup() {
  //Pin definitions
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  contador=0;
  indice=contador;
  indiceLed=contador;
  //Serial.begin(9600);

  // Inicializamos la pantalla con el número de columnas y renglones
  lcd.begin(16, 2);
}

void loop() {
  // Establecemos el cursor a la columna cero y al renglón 1
  // (nota: el renglón 1 es en realidad en segundo, ya que la cuenta comienza en 0):
  lcd.setCursor(0, 0);
  // Imprimimos los milisegundos transcurridos desde el ultimo reset:
  lcd.print("x=");
  lcd.print(contador+1);
  lcd.setCursor(0, 1);
  // Cambiar cor LEDs
  indice = contador % (sizeof(secuenciaRgb)/sizeof(secuenciaRgb[0]));
  changeRgbColor(secuenciaRgb[indice]);
  if (secuenciaLed[indiceLed] != NADA) {
    digitalWrite(ledCores[secuenciaLed[indiceLed]], LOW);
  }
  indiceLed = contador % (sizeof(secuenciaLed)/sizeof(secuenciaLed[0]));
  if (secuenciaLed[indiceLed] != NADA) {
    digitalWrite(ledCores[secuenciaLed[indiceLed]], HIGH);
  }
  contador++;
  delay(1000);
}

void changeRgbColor(int newColor) {
  analogWrite(redPin, rgbCores[newColor][0]);
  analogWrite(greenPin, rgbCores[newColor][1]);
  analogWrite(bluePin, rgbCores[newColor][2]);
}