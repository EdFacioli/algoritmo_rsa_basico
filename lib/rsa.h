#ifndef RSA_H
#define RSA_H
#define TRUE 1
#define FALSE 0

typedef unsigned long long u64;

// Funcao retorna o valor do MDC que no caso do algoritmo RSA sempre sera 1
u64 mdc(u64 num1, u64 num2);

// Funcao que verifica se o numero eh primo. Retornando TRUE para sim e FALSE para nao. TRUE = 1 e FALSE = 0
int primo(u64 n);

// Calcula pelo metodo Russo (dobra e soma)
u64 mult_mod(u64 msg, u64 base, u64 mod);

// Exponenciacao modular (base ^ exp) % mod
// Usa metodo de quadrar e multiplicar
u64 pot_mod(u64 base, u64 exp, u64 mod);

// Usa algoritmo Euclides Estendido
u64 inverso_mod(u64 a, u64 m);

u64 primo_aleatorio(u64 min, u64 max);

#endif