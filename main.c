#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include "lib/rsa.h"

/*
p = primeiro numero primo
q = segundo numero primo
n = calculo do produto dos numeros primos
qe = quociente de euler (phi)
d = necessario para criar a chave privada
*/
u64 p,
    q,
    n,
    qe,
    e,
    d;

// Gera os calculos iniciais, necessarios, para a criacao das chaves
void auxCalc(u64 np1, u64 np2) {
  p = np1;
  q = np2;
  n = (p * q);
  qe = ((p - 1) * (q - 1));

  e = 65537;
  while (mdc(e, qe) != 1)
  {
    e += 2;
  }
    
  d = inverso_mod(e, qe);
}

int main(void)
{
  srand((unsigned)time(NULL));

  u64 p, q;

  do
  {
    p = primo_aleatorio(1000, 5000);
    q = primo_aleatorio(1000, 5000);
  } while (p == q);

  auxCalc(p, q);

  printf("Primos..............: p = %llu, q = %llu\n", p, q);
  printf("Modulo n............: %llu\n", n);
  printf("Totiente phi(n).....: %llu\n", qe);
  printf("Chave publica.......: (e = %llu, n = %llu)\n", e, n);
  printf("Chave privada.......: (d = %llu, n = %llu)\n\n", d, n);

  const char *msg = "Ola mundo!";
  size_t len = strlen(msg);

  u64 cifrado[256];
  char decifrado[257];

  if (len > 256)
  {
    len = 256;
  }
  
  printf("Mensagem original...: \"%s\"\n", msg);

  printf("Bytes cifrados......: ");
  for (size_t i = 0; i < len; i++)
  {
    cifrado[i] = pot_mod((unsigned char)msg[i], e, n);
    printf("%llx", cifrado[i]);
  }
  
  printf("\n");

  for (size_t i = 0; i < len; i++)
  {
    decifrado[i] = (char)pot_mod(cifrado[i], d, n);
  }

  decifrado[len] = '\0';

  printf("Mensagem decifrada..: \"%s\"\n", decifrado);
  printf("Verificacao.........: %s\n", strcmp(msg, decifrado) == 0 ? "Ok, mensagem recuperada!" : "Erro na decifragem!");
  

  return 0;
}