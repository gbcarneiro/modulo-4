#define LIGHT_SENSOR_PIN 14
#define botaoSalvar 33
#define botaoLer 32
#define buzzer 5

int vetor[4]; //Vetor que armazenará o valor convertido para binário 
int vetorArmazenado[100]; // Vetor que guardará o histórico dos valores
int posAtual = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(botaoSalvar, INPUT_PULLUP);

  pinMode(botaoLer, INPUT_PULLUP);

  pinMode(14, INPUT);

  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
}


// A função recebe um valor inteiro, e converte ele para binário realizando o módulo do número por 2, e realizando uma divisão inteira por 2
void converterBinario(int num) {
  for(int i = 0; i < 4; i++){
    vetor[i] = num % 2;
    num = num / 2; 
  }

}


// A função liga os leds de acordo com o valor que é encontrado no vetor, caso 1 o led corresponde acenderá, caso 0 irá ficar apagado
void ler(int num) {
  converterBinario(num);

  if (vetor[3] == 1) {
    digitalWrite(12, HIGH); 
  } else if (vetor[3] == 0) {
    digitalWrite(12, LOW);
  }

  if (vetor[2] == 1) {
    digitalWrite(27, HIGH); 
  } else if (vetor[2] == 0) {
    digitalWrite(27, LOW);
  }

  if (vetor[1] == 1) {
    digitalWrite(26, HIGH); 
  } else if (vetor[1] == 0) {
    digitalWrite(26, LOW);
  }

  if (vetor[0] == 1) {
    digitalWrite(25, HIGH); 
  } else if (vetor[0] == 0) {
    digitalWrite(25, LOW);
  }
}

// Armazena o valor de 0 a 15 do ldr, a fim de ser acessado posteriomente pelo botão de leitura
int armazenaVetor(int num, int posicao) {
  vetorArmazenado[posicao] = num;

  ler(num);
  buzz(num);

  return posicao + 1; 
}

// Utiliza o número do LDR convertido de 0 a 15 para tocar uma determinada frequência a partir deste número
void buzz(int num) { 
  for(int i = 1; i < num; num--) {
    tone(5, (100*num), 200);

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Convertendo o valor para um número entre 0 e 15
  int valorNumero = analogRead(14);
  int valorLDR = 15 - (valorNumero / 273);

  //Caso o botão verde seja pressionado, o valor será armazenado no vetor
  if (digitalRead(botaoSalvar) == LOW) { 
    posAtual = armazenaVetor(valorLDR, posAtual);
    Serial.println("Salvando valor");
    while(digitalRead(botaoSalvar) == LOW) {}
  }


  //Caso o botão azul seja pressionado, o vetor será percorrido e seus valores lidos
  if (digitalRead(botaoLer) == LOW) {
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
 