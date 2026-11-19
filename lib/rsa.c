#include<stdlib.h>
#include "rsa.h"
#define TRUE 1
#define FALSE 0

typedef unsigned long long u64;

// Funcao retorna o valor do MDC que no caso do algoritmo RSA sempre sera 1
u64 mdc(u64 num1, u64 num2)
{
  while (num2 != 0)
  {
    u64 resto = num1 % num2;
    num1 = num2;
    num2 = resto;
  }

  return num1;
}

// Funcao que verifica se o numero eh primo. Retornando TRUE para sim e FALSE para nao. (TRUE = 1 e FALSE = 0)
int primo(u64 n)
{
  if (n < 2)
  {
    return FALSE;      
  }

  // O unico numero par primo eh 2
  if (n % 2 == 0)
  {
    return n == 2;
  }

  for (u64 i = 3; i * i <= n; i +=2)
  {
    if (n % i == 0)
    {
      return FALSE;
    }
  }
  
  return TRUE;
}

// Calcula pelo metodo Russo (dobra e soma)
u64 mult_mod(u64 msg, u64 base, u64 mod)
{
  u64 resultado = 0;
  msg %= mod;

  while (base > 0)
  {
    if (base & 1)
    {
      resultado = (resultado + msg) % mod;
    }

    msg = (msg * 2) % mod;
    base >>= 1;
    
  }

  return resultado;
}


// Exponenciacao modular (base ^ exp) % mod
// Usa metodo de quadrar e multiplicar
u64 pot_mod(u64 base, u64 exp, u64 mod)
{
  u64 resultado = 1;
  base %= mod;

  while (exp > 0)
  {
    if (exp & 1)
    {
      resultado = mult_mod(resultado, base, mod);
    }
    
    base = mult_mod(base, base, mod);
    exp >>= 1;
  }
  
  return resultado;
}

// Usa algoritmo Euclides Estendido
u64 inverso_mod(u64 a, u64 m)
{
  long long coeficiente = 0, 
            novo_coeficiente = 1,
            resto = (long long) m,
            novo_resto = (long long)(a % m);

  while (novo_resto != 0)
  {
    long long q = resto / novo_resto;
    long long tmp;

    tmp = coeficiente - q * novo_coeficiente;
    coeficiente = novo_coeficiente;
    novo_coeficiente = tmp;
    
    tmp = resto - q * novo_resto;
    resto = novo_resto;
    novo_resto = tmp;
  }
    
  // mdc(a,m) != 1 -> nao ha inverso
  if (resto != 1)
  {
    return FALSE;
  }
  
  // normaliza para o intervalo [0,m]
  if (coeficiente < 0)
  {
    coeficiente += (long long)m;
  }
  return (u64)coeficiente;
}

u64 primo_aleatorio(u64 min, u64 max)
{
  u64 candidato;

  do
  {
    candidato = min + (u64)(rand()) % (max - min +1);

    if (candidato % 2 == 0)
    {
      candidato++;
    }
    
  } while (candidato < min || candidato > max || !primo(candidato));
  
  return candidato;
}
