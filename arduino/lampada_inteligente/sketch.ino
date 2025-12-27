#define RELE 10
#define RELE_INPUT 8
#define COMUM A0


void setup()
{
  // configurações iniciais
  pinMode(RELE, OUTPUT);
  pinMode(RELE_INPUT, INPUT);
  Serial.begin(9600);
  digitalWrite(RELE, LOW);
  Serial.print("INICIADO O TERMINAL!\n");
  Serial.print("COMANDOS:\nl - LIGAR\nd - DESLIGAR\nc - CHECAR ESTADO\n");
}

String leStringSerial()
{
  //verifica se há comando no monitor serial
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
  Serial.print("");

// recebe informações pra saber se a lampada está ligada ou não
  if (Serial.available() > 0) {
    // leitura dos pinos
    int b = digitalRead(RELE_INPUT);
    float c = analogRead(COMUM);
    int estado = (int)(c/10);
    String recebido = leStringSerial();

// lógica pra ligar a lâmpada 
    if (recebido == "l") {
      
      if(estado == 0) {
        Serial.print("Ja esta ligado!\n");
      } else {
        digitalWrite(RELE, !b);
        Serial.print("Ligada!\n");
      }
    }
//lógica pra desligar a lâmpada 
    if (recebido == "d") {

      if(estado == 0) {
        digitalWrite(RELE, !b);
        Serial.print("Desligada!\n");
      } else {
        Serial.print("Ja esta desligado!\n");
      }
    }
// lógica de verificação de estado para obtenção de informações para a montagem de lógica
    if (recebido == "c") {
      Serial.print("Estado bobina: ");
      Serial.println(b);
      Serial.print("Estado comum: ");
      Serial.println(c);
    }
  }
  delay(100);
}