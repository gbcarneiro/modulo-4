#include <iostream>
#include <string>

using namespace std;

// variável que guardará os nomes ea ordem das direções.
char *nomeDirecoes[4] = {(char *) "Direita", (char *) "Esquerda", (char *) "Frente", (char *) "Trás"};

// a partir de uma medida, um valor máximo e minimo a função irá fazer com que o valor se ajuste percentualmente entre essas duas faixas.
int converteSensor(int medida, int minimo, int maximo) {
    medida = (medida - minimo) * 100; 
    int delta = maximo - minimo; 
    int resultado = (medida - minimo) * 100 / (maximo - minimo); 
    cout << resultado;
    
	return (medida - minimo) * 100 / (maximo - minimo);
}

// função que irá verificar se o usuário deseja continuar
int leComando() { 
    char resposta; 
    cout << "Você deseja continuar? (s/n) "; 
    cin >> resposta; 
    if (resposta == 's') {
        return 1;
    } else {
        return 0; 
    }
}

// esta função irá receber um valor a ser inserido em um vetor, e a posição em que ele deseja ser inserido.
// o uso do valorMaximo é uma verificação se a posição desejada é válida no escopo máximo do vetor
int insereValorVetor(int valor, int* vetor, int valorMaximo, int indiceVetor) {
    if (indiceVetor < valorMaximo) {         
		vetor[indiceVetor] = valor;  
		indiceVetor += 1; // após inserir o valor no vetor, atualizamos a posição atual e retornamos ela
	}

    // o intuito de retornar o novo valor da posição é para que na próxima inserção, o indice já esteja na posição correta
	return indiceVetor;
}

int dirige(int *v,int maxv){
    int maxVetor = maxv;
    int *vetorMov = v;

    int posAtualVetor = 0;
    int mapeamento = 1;
    int dirigindo = 1; // variável que guardará a resposta da pergunta "Quer continuar?", enquanto for 1 o loop continuará executando

    while(dirigindo) {
            printf("Mapeamento %d \n", mapeamento);
            
            int medida; // guardará o valor que o usuário digitar 

            // este loop irá coletar as informações para as 4 direções, e guarda-las no vetor passado pelos parâmetros chamando a função insereValorVetor
            for (int i = 0; i < 4; i++) {  
                printf("Digite a distância do robô até o lado %s: ", nomeDirecoes[i]);
                cin >> medida;
                medida = converteSensor(medida, 0, 830);
                posAtualVetor = insereValorVetor(medida, vetorMov, maxVetor, posAtualVetor);
            }

        dirigindo = leComando(); // verifica se o usuário deseja continuar com o mapeamento
        mapeamento += 1; // atualiza o número do mapeamento
    }

    return posAtualVetor;
}

// A função deseja calcular o maior caminho dentre as direções passadas
char* direcaoMaiorCaminho(int* vetor, int* distancia) {
	int index = 0;         
	int maiorValor = vetor[0]; // para guardar o maior valor iremos iniciar essa variável com o primeiro valor do vetor, e mudará de acordo com o loop abaixo

	// Mapeia o vetor, buscando o índice do maior valor dentro do vetor. 
	for (int i = 1; i < 4; i++) {
		if (vetor[i] > maiorValor) {  
			maiorValor = vetor[i];    
			index = i;         
		}
	}

	*distancia = maiorValor; // armazena o maior valor encontrado                                 
	return nomeDirecoes[index]; // irá retornar o nome da direção que apresenta este maior valor
}

// Esta função percorre o vetor maior que contem todas os valores coletados pelo programa e mostra para o usuário qual a direção e o valor da maior distância
void percorre(int *v,int tamPercorrido) {		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char* direcao = direcaoMaiorCaminho(&vetorMov[i], &maiorDir);  // pega a direção do maior valor
        printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}
int main(int argc, char** argv) {
   int maxVetor = 100;
   int vetorMov[maxVetor*4];
   int posAtualVet = 0;

   posAtualVet = dirige(vetorMov,maxVetor);
   percorre(vetorMov,posAtualVet);

   return 0;
}