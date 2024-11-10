# Programação Paralela e Distribuída

Este repositório contém exemplos de código para ilustrar conceitos fundamentais de programação paralela e distribuída, incluindo Leitores e Escritores, Barreiras, Sinais e Deadlocks. Cada exemplo foi implementado em C utilizando a biblioteca `pthread`.

## Conteúdo

- [Leitores e Escritores](#leitores-e-escritores)
- [Barreiras](#barreiras)
- [Sinais](#sinais)
- [Deadlocks](#deadlocks)

## Estrutura do Diretório

Cada conceito está implementado em um arquivo separado dentro de sua própria pasta:

```
.
├── Leitores_e_Escritores
│   └── leitores_e_escritores.c
├── Barreiras
│   └── barreiras.c
├── Sinais
│   └── sinais.c
└── Deadlocks
    └── deadlocks.c
```

## Leitores e Escritores

### Descrição

O problema dos leitores e escritores envolve um recurso compartilhado que pode ser lido por múltiplos leitores simultaneamente, mas só pode ser escrito por um único escritor por vez. Este exemplo demonstra como coordenar o acesso de leitores e escritores ao recurso compartilhado utilizando mutexes e variáveis de condição.

### Compilar e Executar

```bash
cd Leitores_e_Escritores
gcc -pthread -o leitores_e_escritores leitores_e_escritores.c
./leitores_e_escritores
```

## Barreiras

### Descrição

Uma barreira é uma técnica de sincronização onde múltiplas threads precisam esperar até que todas tenham alcançado um ponto específico antes de continuar. Este exemplo demonstra a implementação de uma barreira utilizando mutexes e variáveis de condição.


### Compilar e Executar

```bash
cd Barreiras
gcc -pthread -o barreiras barreiras.c
./barreiras
```

## Sinais

### Descrição

Sinais são um método de comunicação entre processos em sistemas Unix-like. Este exemplo demonstra como um processo pai pode enviar um sinal `SIGUSR1` para um processo filho, que captura e trata o sinal com um handler.

```bash
cd Sinais
gcc -o sinais sinais.c
./sinais
```

## Deadlocks

### Descrição

Um deadlock ocorre quando dois ou mais processos ou threads estão esperando indefinidamente por recursos que estão sendo mantidos por si próprios. Este exemplo demonstra um deadlock simples onde duas threads tentam adquirir dois mutexes em ordem inversa, resultando em uma espera circular.

### Compilar e Executar

```bash
cd Deadlocks
gcc -pthread -o deadlocks deadlocks.c
./deadlocks
```

## Referências

- Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts. John Wiley & Sons.
- Tanenbaum, A. S., & Bos, H. (2014). Modern Operating Systems. Pearson.
- Pacheco, P. (2011). An Introduction to Parallel Programming. Morgan Kaufmann.
- Rauber, T., & Rünger, G. (2013). Parallel Programming: For Multicore and Cluster Systems. Springer.
- Kerrisk, M. (2010). The Linux Programming Interface: A Linux and UNIX System Programming Handbook. No Starch Press.
- Stevens, W. R., & Rago, S. A. (2013). Advanced Programming in the UNIX Environment. Addison-Wesley.

Este repositório oferece uma visão prática sobre questões de sincronização e coordenação em ambientes de programação paralela e distribuída.