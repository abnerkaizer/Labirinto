#include <stdio.h>
#include <stdlib.h>
#include "labirinto.h"


Labirinto* carrega_labirinto(){
	char nmArq[20]="labirinto.txt";
	int linhas, colunas;
	FILE* file = fopen(nmArq,"r");
	fscanf(file,"%d %d\n",&linhas,&colunas);
	Labirinto* lab = (Labirinto*)malloc(sizeof(Labirinto));
	lab->colunas = colunas;
	lab->linhas = linhas;
	lab->mapa = alocarMatriz(linhas,colunas);
	for(size_t i = 0; i < linhas; i++){
    	char buffer;// para armezenar o caracter para teste futuro
      	for(size_t j = 0; j < colunas; j++){
           	fscanf(file, "%c ", &buffer);
           	if ( buffer != '\n')//testa para não colocar na matriz a quebra de linha
                lab->mapa[i][j] = buffer;
      }
	}
	fclose(file);
	return lab;
}
char** alocarMatriz(int Linhas,int Colunas){ //Recebe a quantidade de Linhas e Colunas como Parâmetro
	char **m = (char**)malloc(Linhas * sizeof(char*)); //Aloca um Vetor de Ponteiros	 
  	for (int i = 0; i < Linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
       m[i] = (char*) malloc(Colunas*sizeof(char)); //Aloca um Vetor de char para cada posição do Vetor de Ponteiros.
   	}
	return m; //Retorna o Ponteiro para a Matriz Alocada
}

void imprime_labirinto(Labirinto* lab,FILE* file){
	char** mat = lab->mapa;
	int linhas = lab->linhas;
	int colunas = lab->colunas;

	for (int i = 0; i < linhas; ++i)
	{
		for (int j = 0; j < colunas; ++j)
		{
			fprintf(file,"%c ",mat[i][j]);
		}
		fprintf(file,"\n");
	}
	
}

Posicao * coordenada_inicial(Labirinto *lab){
	int linhas = lab->linhas;
	int colunas = lab->colunas;
	Posicao* pos= (Posicao*)malloc(sizeof(Posicao));
	for (int i = 0; i < linhas; ++i)
	{
		for (int j = 0; j < colunas; ++j)
		{
			if (lab->mapa[i][j]=='i')
			{
				pos->x = i;
				pos->y = j;
				break;
			}
		}
	}
	return pos;
}

void percurso(Labirinto*lab,int linhas, int colunas,FILE*file){
	int passos=0,queijos=0,caminho=0;
	char**mapa = lab->mapa;

	fprintf(file,"\n");
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			fprintf(file,"%c ",mapa[i][j]);
			if (mapa[i][j]=='2'||mapa[i][j]=='3'||mapa[i][j]=='4')
			{
				passos++;//calcula os passos totais
			}
			if (mapa[i][j]=='2'||mapa[i][j]=='4')
			{
				caminho++;//calcula o tamanho do caminho
			}
			
			if (mapa[i][j]=='4')
			{
				queijos++;//calcula quantidade de queijos
			}
			
		}
		fprintf(file,"\n");
	}
	fprintf(file,"Passos: %d\n",passos);
	fprintf(file,"Caminho: %d\n",caminho);
	fprintf(file,"Queijos: %d\n",queijos);
}

bool acha_saida(Labirinto* lab, int x, int y) {
		char**mapa = lab->mapa;
		int linhas = lab->linhas;
		int colunas = lab->colunas;
		//verifica se está dentro do labirinto
        if ((x < 0 || x >= linhas) || (y < 0 || y >= colunas)) {
			printf("Limite\n");
            return false;
        }
		//verifica se é a posição final
        if (mapa[x][y] == 'S') {
			printf("Terminou\n");
            return true;
        }
		//delimita as paredes
        if (mapa[x][y] == '1') {
            return false;
        }
		//volta se encontra novamente um caminho sem saida ou que ja tenha passado
        if (mapa[x][y]=='3'||mapa[x][y]=='2'||mapa[x][y]=='4') {
            return false;
        }
		//marca as posições que passou
        if(mapa[x][y]=='i'||mapa[x][y]=='0'||mapa[x][y]=='Q'){
			if (mapa[x][y]=='Q')
			{
				mapa[x][y] = '4';// marca onde comeu queijo
			}else
				mapa[x][y] = '2';//marca por onde passou
        }
		//navega em x para a esquerda.
        if (acha_saida(lab, x, (y - 1)) == true) {
            return true;
        }
		//navega em y para baixo
        if (acha_saida(lab, (x + 1), y) == true) {
            return true;
        }
		//navega em x para direita
        if (acha_saida(lab, x, (y + 1)) == true) {
            return true;
        }
		//navega em y para cima
        if (acha_saida(lab, (x - 1), y) == true) {
            return true;
        }
		//marca as posições que não tem saida
        mapa[x][y] = '3';
        return false;
    }
//libera a matriz dentro do registro e o registro Labirinto
void libera_labirinto(Labirinto *lab){
	for (int i = 0; i < lab->linhas; i++)
	{
		free(lab->mapa[i]);
	}
	free(lab->mapa);
	free(lab);
}

int main(int argc, char const *argv[])
{
	Labirinto* lab = carrega_labirinto();
	Posicao* init = coordenada_inicial(lab);
	FILE*file = fopen("saida.txt","w");
	imprime_labirinto(lab,file);
	acha_saida(lab,init->x,init->y);
	percurso(lab,lab->linhas,lab->colunas,file);
	fclose(file);
	free(init);
	libera_labirinto(lab);
	return 0;
}
