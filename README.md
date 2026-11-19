# Biblioteca do algoritmo RSA

É apenas para estudo, não use em produção.

Para gerar os artefatos:

```bash
# Diretorio lib
gcc -c rsa.c -o rsa.o
ar rcs rsalib.a rsa.o
# Diretorio raiz do projeto
gcc main.c -L. -l:lib/rsalib.a -o app
```
