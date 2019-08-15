#define RELE 8
#define LDR A5

const String ESTEIRA = "\"ESTEIRA\":";
const String ITENS = "\"ITENS\":";
const String RESET = "\"RESET\":";

void alternaRele(String comando);
String JSON_ESTEIRA();
int intervalo = 0;
int itens = 0;
int item_ant = 0;
bool anterior = false ;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    String comando = Serial.readString();
    alternaRele(comando);
  }
  
  if(digitalRead(RELE) == LOW){
    if(analogRead(LDR) < 90 &&
    millis()-intervalo >= 1000 &&
    anterior == false){
      itens++;
      anterior = true;
      intervalo = millis();
    }else if(analogRead(LDR) > 90 &&
    anterior == true){
      anterior = false;
      intervalo = millis();
    }
  }
//  Serial.println(analogRead(LDR));
  if(itens-item_ant > 1){
    itens -= (itens - item_ant - 1);
  }
  item_ant = itens;
  Serial.print(JSON_ESTEIRA());
  delay(100);
}

void alternaRele(String comando){
  if(comando.startsWith("{") && comando.endsWith("}")){

    if(comando.indexOf(ESTEIRA + "0") > 0){
      digitalWrite(RELE, HIGH);
      
    }else if(comando.indexOf(ESTEIRA + "1") > 0){
      digitalWrite(RELE, LOW);
    }

    if(comando.indexOf(RESET + "1") > 0){
      itens = 0;
    }
  }
}

String JSON_ESTEIRA(){
  int est = digitalRead(RELE);
  return "{" +
            ESTEIRA + String(est) + "," +
            ITENS + String(itens) +
         "}";
} 
