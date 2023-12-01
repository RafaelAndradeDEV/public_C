#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20
#define INI 1

struct Memoria {
   char classe;
   int index;
   int espacoOcupado;
   struct Memoria* proximo;
};

char escolherAleatorio(char opcao1, char opcao2);
void criarMemoria(struct Memoria*, int*);
void imprimirMemoria(struct Memoria*);
void criarNo(struct Memoria*, int*);

int main() {
   srand(time(NULL));
   struct Memoria space;
   int total = 0;

   criarMemoria(&space, &total);
   imprimirMemoria(&space);

   char opcao;
   do {
      criarNo(&space, &total);
      imprimirMemoria(&space);

      printf("Deseja adicionar mais um espaço? (s para sim, p para parar): ");
      scanf(" %c", &opcao);
   } while (opcao != 'p');

   return 0;
}

void criarMemoria(struct Memoria* p, int* total) {
   int quantTotal = 0;
   for (int i = 0; quantTotal < MAX; i++) {
      p->proximo = malloc(sizeof(struct Memoria));
      p->classe = escolherAleatorio('P', 'H');
      p->index = quantTotal;

      p->espacoOcupado = INI + rand() % 4;
      if (quantTotal + p->espacoOcupado > MAX) {
         p->espacoOcupado = MAX - quantTotal;
      }

      quantTotal += p->espacoOcupado;
      if (quantTotal < MAX) {
         p = p->proximo;
      }
      *total += 1;
   }
   p->proximo = NULL;
}

void imprimirMemoria(struct Memoria* p) {
   while (p != NULL) {
      if (p->espacoOcupado > 0) {  // Verifica se a quantidade é maior que zero antes de imprimir
         printf("Classe: %c, Index: %d, Quantidade: %d\n", p->classe, p->index, p->espacoOcupado);
      }
      p = p->proximo;
   }
   printf("------\n");
}

void criarNo(struct Memoria* p, int* total) {
   printf("Digite o tamanho do novo espaço (quantidade): ");
   int novoEspaco;
   scanf("%d", &novoEspaco);

   while (p->proximo != NULL) {
      if (p->classe == 'H' && p->espacoOcupado == novoEspaco) {
         // Substitui a classe apenas se a quantidade for igual
         p->classe = 'P';

         *total += 1;
         printf("Classe do espaço atualizada com sucesso!\n");

         break;;
      }
      else if (p->classe == 'H' && p->espacoOcupado > novoEspaco) {
         // Encontrou um espaço adequado, cria o novo espaço antes do espaço livre
         p->classe = 'P';


         struct Memoria* novoEspacoMem = malloc(sizeof(struct Memoria));
         novoEspacoMem->classe = 'H';
         novoEspacoMem->espacoOcupado = p->espacoOcupado - novoEspaco;
         p->espacoOcupado = novoEspaco;
         novoEspacoMem->index = p->index + p->espacoOcupado;
         novoEspacoMem->proximo = p->proximo;
         p->proximo = novoEspacoMem;



         *total += 2;
         printf("Novo espaço adicionado com sucesso!\n");
         break;
      }
      p = p->proximo;
   }

   printf("Não foi possível adicionar ou atualizar o espaço. Espaço insuficiente ou tamanho incompatível.\n");
}


char escolherAleatorio(char opcao1, char opcao2) {
   // Gera um número aleatório entre 0 e 1 (inclusive)
   int randomNum = rand() % 2;

   char escolha = (randomNum == 0) ? opcao1 : opcao2;
   return escolha;
}
