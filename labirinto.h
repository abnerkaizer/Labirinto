#include <stdbool.h>

typedef struct labirinto {
	// ’i’=inicio, ’0’=livre, ’1’=parede, ’Q’=queijo, ’S’=saida
	char **mapa;
	int colunas; /* mapa[colunas*x + y] */
	int linhas;
}Labirinto;

typedef struct posicao {
	int x;
	int y;
}Posicao;

char** alocarMatriz(int Linhas,int Colunas);

Labirinto * carrega_labirinto();

Posicao * coordenada_inicial(Labirinto *lab);

bool acha_saida(Labirinto*lab,int x,int y);

void imprime_labirinto(Labirinto* lab,FILE*file);

void percurso(Labirinto*lab,int linhas, int colunas,FILE*file);

void libera_labirinto(Labirinto *lab);
