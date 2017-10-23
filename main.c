#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct usuarios_infos{
char usuario[100];
char senha[100];
};
void main(){
	struct usuarios_infos contas_tmp,conta_definida;
	char * lista_de_contas,usuario[20]="\0",senha[20]="\0";
	int ponteiro_contas=0,total_de_contas=0,total_de_bytes=0;
	printf("****** Systema de Login ****** \n");
	printf("Usuario: ");
	scanf("%s",usuario);
	printf("Senha: ");
	scanf("%s",senha);
	// coloca nossos dados dentro de conta_definida
	memset(&conta_definida,0,sizeof(struct usuarios_infos));
	memcpy(&conta_definida.usuario,&usuario,strlen(usuario));
	memcpy(&conta_definida.senha,&senha,strlen(senha));
	// --------------------------------------------
	FILE * file_contas;
	file_contas = fopen("usuarios.db","rb");
	if(file_contas == NULL){
		printf("[F] Falha ao carregar o arquivo de dados. \n");
		return;
	}else{
		// codigo para pegar o tamanho do arquivo
		fseek(file_contas,0,SEEK_END);
		total_de_bytes = ftell(file_contas);
		rewind(file_contas);
			// cria um array no ponteiro lista_de_contas exatamente com tamanho do arquivo
			lista_de_contas = malloc(total_de_bytes);
			if(lista_de_contas == NULL){
				printf("[F] Não foi possivel liberar espaço. \n");
				return;
			}
			// ---------------------------------------------------------------------------
		// --------------------------------------
		//printf("[Ok] Arquivo carregado bytes: %d \n",total_de_bytes);
	}
	// Carrega todas as contas dentro do arquivo
	if(fread(lista_de_contas,1,total_de_bytes,file_contas) == 0){
		printf("[F] Falha na leitura das contas. \n");
		return;
	}else{
		total_de_contas = total_de_bytes / sizeof(struct usuarios_infos);
		//printf("[Ok] Todas as %d contas foram carregadas. \n",total_de_contas);
	}
	// -----------------------------------------
	// Compara a conta inserida no programa com todas presentes dentro do arquivo usuarios.db
	while(1){
		memset(&contas_tmp,0,sizeof(struct usuarios_infos));
		memcpy(&contas_tmp,&lista_de_contas[ponteiro_contas],sizeof(struct usuarios_infos));
		if(memcmp(&conta_definida,&contas_tmp,sizeof(struct usuarios_infos))==0){
			// coloque uma função abaixo caso usuario longado
			printf("Bem - Vindo: %s \n",contas_tmp.usuario);
			// ---------------------------------------------
			break;
		}else{
			//printf("Conta %d \nUsuario:%s\nSenha:%s \n",ponteiro_contas/sizeof(struct usuarios_infos),contas_tmp.usuario,contas_tmp.senha);
		}
		if(ponteiro_contas/sizeof(struct usuarios_infos) == total_de_contas-1){
			printf("Usuario ou Senha Incorreto. \n");
			break;
		}
		ponteiro_contas = ponteiro_contas + sizeof(struct usuarios_infos);
	}
	// --------------------------------------------------------------------------------------
	fclose(file_contas);
	free(lista_de_contas);
}
