#include <stdio.h>
#include <time.h>
#include <stdlib.h>


char verificar(char armario, char pos);

int main() {
   unsigned char x, y;
   unsigned char feito = 1;
   unsigned char armarios = 0;
   while (1) {
      for (unsigned char i = 0; i < 8; i++) {
         if (verificar(armarios, i))
            printf("Armário %hhu está ocupado\n", i);
         else
            printf("Armário %hhu está desocupado\n", i);
      }
      puts("Você tem 3 opções: \n 1. Ocupar um armário aleatório\n 2. Liberar um armário a sua escolha\n 3. Sair");
      scanf("%hhu", &x);
      if (x == 3)
         break;
      if ((x < 1) || (x > 3)) {
         puts("Essa opção não é válida, tente novamente");
      }
      if (x == 1) {
         srand(time(NULL));
         y = rand() % 8;
         printf("%hhu", y);
         if (!verificar(armarios, y))
            armarios = armarios ^ 1 << y;
      }
      if (x == 2) {
         puts("Escolha um armário para liberar: ");
         scanf("%hhu", &y);
         if (verificar(armarios, y))
            armarios = armarios ^ 1 << y;
      }
   }
}


char verificar(char armario, char pos) {
   return ((armario >> pos) & 1);
}
