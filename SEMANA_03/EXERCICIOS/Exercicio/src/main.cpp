#include <Arduino.h>
#define botaoSalvar 36
#define botaoLer 39
#define buzzer 41

int vetor[4];
int vetorArmazenado[100]; 
int posAtual = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(botaoSalvar, INPUT_PULLUP);
  pinMode(botaoLer, INPUT_PULLUP);

  pinMode(41, OUTPUT);

  pinMode(14, INPUT);

  pinMode(15, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(10, OUTPUT);
}


void converterBinario(int num) {
  for(int i = 0; i < 4; i++){
    vetor[i] = num % 2;
    num = num / 2; 
  }

}

void ler(int num) {
  converterBinario(num);

  if (vetor[3] == 1) {
    digitalWrite(15, HIGH); 
  } else if (vetor[3] == 0) {
    digitalWrite(15, LOW);
  }

  if (vetor[2] == 1) {
    digitalWrite(17, HIGH); 
  } else if (vetor[2] == 0) {
    digitalWrite(17, LOW);
  }

  if (vetor[1] == 1) {
    digitalWrite(46, HIGH); 
  } else if (vetor[1] == 0) {
    digitalWrite(46, LOW);
  }

  if (vetor[0] == 1) {
    digitalWrite(10, HIGH); 
  } else if (vetor[0] == 0) {
    digitalWrite(10, LOW);
  }
}

void buzz(int num) { 
  for(int i = 1; i < num; num--) {
    tone(41, (100*num), 200);

  }
}

int armazenaVetor(int num, int posicao) {
  vetorArmazenado[posicao] = num;
  Serial.println("Foi");

  ler(num);
  buzz(num);

  return posicao + 1; 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Convertendo o valor para um número entre 0 e 15
  int valorNumero = analogRead(14);
  int valorLDR = (valorNumero / 273);

  Serial.println(valorLDR); 

  if (digitalRead(botaoSalvar) == LOW) { 
    posAtual = armazenaVetor(valorLDR, posAtual);
    Serial.println("Salvando valor");
    while(digitalRead(botaoSalvar) == LOW) {}
  }

  if (digitalRead(botaoLer) == LOW) {
    //posAtual =buzz(vetorArmazenado, posAtual);
    Serial.println("Lendo valor");
    while (digitalRead(botaoLer) == LOW) {}

    for(int i =0; i < posAtual; i++) {
      ler(vetorArmazenado[i]);
      buzz(vetorArmazenado[i]);
      delay(3000);
    }
  }

  delay(3000);
}
 