#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct usuarios_infos{
	char usuario[100];
	char senha[100];
};

void main(){
	struct usuarios_infos contas;
	FILE * wFile;
	wFile = fopen("usuarios.db","ab");
	if(wFile == NULL){
		printf("[F] Falha em abrir o arquivo. \n");
		return;	
	}
	memset(&contas,0,sizeof(struct usuarios_infos));
	printf("**** Inserir novos usuarios **** \n");
	printf("Usuario: ");
	scanf("%s",contas.usuario);
	printf("Senha: ");
	scanf("%s",contas.senha);
	int bytes = fwrite(&contas,1,sizeof(struct usuarios_infos),wFile);
	if(bytes == 0){
		printf("[F] Falha em escrever os dados. \n");
		return;	
	}else{
		printf("[Ok] Usuario gravado com sucesso. \n");	
		fclose(wFile);
	}
}
