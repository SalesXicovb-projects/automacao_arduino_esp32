// Projeto: Lâmpada Inteligente com ESP32

#define RELE 4
#define RELE_INPUT 5
#define COMUM 2

void setup()
{
    // Configurações iniciais
  pinMode(RELE, OUTPUT);
  pinMode(RELE_INPUT, INPUT_PULLUP);
  Serial.begin(115200);
  digitalWrite(RELE, LOW);

  Serial.print("INICIADO O TERMINAL!\n");
  Serial.print("COMANDOS:\nl - LIGAR\nd - DESLIGAR\nc - CHECAR ESTADO\n");
}

String leStringSerial()
{
  String conteudo = "";
  char estado;
  while (Serial.available() > 0) {
    estado = Serial.read();
    if (estado != '\n') {
      conteudo.concat(estado);
    }
    delay(100);
  }
  Serial.print("Recebi: ");
  Serial.println(conteudo);

  return conteudo;
}

void loop() {

  if (Serial.available() > 0) {
    // Capturando as leituras dos pinos
    int b = digitalRead(RELE_INPUT);
    float c = analogRead(COMUM);
    int estado = (int)(c/10);

    // Lendo o comando recebido via serial
    String recebido = leStringSerial();

    // Lógica para ligar/desligar/checar o estado da lâmpada
    if (recebido == "l") {
      if(estado == 0) {
        Serial.print("Ja esta ligado!\n");
      } else {
        digitalWrite(RELE, !b);
      }
    }
    if (recebido == "d") {
      if(estado == 0) {
        digitalWrite(RELE, !b);
      } else {
        Serial.print("Ja esta desligado!\n");
      }
    }

    // Lógica para testes e verificação do estado
    if (recebido == "c") {
      Serial.print("Estado comum: ");
      Serial.println(estado);
      Serial.print("Estado bobina: ");
      Serial.println(b);
    }
  }
  delay(100);
}

