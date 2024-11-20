#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int nivel_bateria = 100;
int timer = 0;
String modos[] = {"Fritar", "Cozinhar a Vapor", "Assar"};
String modo_selecionado = "";
bool executando = true;

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Painel SolarCooker");
  delay(2000);
}

void loop() {
  showMenu();
  handleUserInput();
}

void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--- Painel SolarCooker ---");
  lcd.setCursor(0, 1);
  lcd.print("1. Verificar Bateria");
  lcd.setCursor(0, 2);
  lcd.print("2. Configurar Timer");
  lcd.setCursor(0, 3);
  lcd.print("3. Selecionar Modo");
  Serial.println("Escolha uma opcao (1, 2, 3):");
}

void handleUserInput() {
  while (Serial.available() == 0) {}

  char escolha = Serial.read();
  switch (escolha) {
    case '1':
      verificarBateria();
      break;
    case '2':
      configurarTimer();
      break;
    case '3':
      selecionarModo();
      break;
    default:
      Serial.println("Opção inválida. Tente novamente.");
      break;
  }
}

void verificarBateria() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nivel de Bateria: ");
  lcd.setCursor(0, 1);
  lcd.print(nivel_bateria);
  lcd.print("%");
  Serial.print("Nível de Bateria: ");
  Serial.println(nivel_bateria);
  delay(2000);
}

void configurarTimer() {
  int tempo_input = 0;
  bool entrada_valida = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Defina o tempo (max 99)");

  while (!entrada_valida) {
    Serial.println("Defina o tempo de preparo (em minutos, max 99): ");
    while (Serial.available() == 0) {}
    tempo_input = Serial.parseInt();
    if (tempo_input > 0 && tempo_input <= 99) {
      timer = tempo_input;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Timer configurado:");
      lcd.setCursor(0, 1);
      lcd.print(timer);
      lcd.print(" minutos.");
      Serial.print("Timer configurado para ");
      Serial.print(timer);
      Serial.println(" minutos.");
      entrada_valida = true;
      delay(3000);
    } else {
      Serial.println("Por favor, insira um numero valido entre 1 e 99.");
    }
  }
}

void selecionarModo() {
  int escolha = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Modos disponiveis:");
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, 1 + i);
    lcd.print(i + 1);
    lcd.print(". ");
    lcd.print(modos[i]);
  }

  delay(4000);

  Serial.println("Escolha um modo de preparo (1, 2 ou 3):");
  while (Serial.available() == 0) {}
  escolha = Serial.parseInt();

  if (escolha >= 1 && escolha <= 3) {
    modo_selecionado = modos[escolha - 1];
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Modo selecionado: ");
    lcd.setCursor(0, 1);
    lcd.print(modo_selecionado);
    Serial.print("Modo selecionado: ");
    Serial.println(modo_selecionado);
    delay(2000);
  } else {
    Serial.println("Opção inválida. Tente novamente.");
  }
}
