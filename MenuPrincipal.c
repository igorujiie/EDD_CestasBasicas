/*
  Programa: Cidade Solidária
  Data....: 31/05/2021
*/

/*Bibliotecas*/
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

/*Protótipos*/
int  MenuPrincipal (void);
void Sobre (void);

/* Variáveis globais */
registro_osc 	informacao;
FILE      		*CSV;
FILE      		*DAT;
int       		i, cont=0;

/* Função erro ao ler arquivo DAT */
void errogravarDAT (void)
{
	system ("cls");
	printf ("\n  ERRO AO GRAVAR NO ARQUIVO .DAT  ");
	getch();
	exit(0);
}

/* Função erro ao ler arquivo CSV */
void  errolerCSV (void)
{
	system ("cls");
	printf ("\n  ERRO AO LER ARQUIVO .CSV  ");
	getch();
	exit(0);
}

/* Função para converter CSV para DAT */
void  ConverteCSVDAT (void)
{
	char  cestasaux [10];
	int   linha=1;
	int   qtdRegistros;
	char  ch;
	CSV = fopen ("OSC.CSV", "r");
	if (CSV==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO 'OSC.CSV'.  ");
		getch();
		exit(0);
	}

	DAT = fopen ("OSC.DAT", "w");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO 'OSC.DAT'.  ");
		getch();
		exit(0);
	}

	qtdRegistros=0;

	while ( !feof(CSV) ) /* lê o CSV até o fim do arquivo*/
	{
		if(linha ==1)   /*pular primeira linha (tira cabeçalho)*/
		{
			do
			{
				ch = fgetc(CSV);
			}
			while(ch != '\n');
		}

		/* trata o nome da entidade*/
        i=0;
        do
		{
		  informacao.entidade[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.entidade[i++] != ';' );
	    informacao.entidade[--i] = '\0';

        /*trata o cnpj*/
        i=0;
		do
		{
		  informacao.cnpj[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.cnpj[i++] != ';' );
	    informacao.cnpj[--i] = '\0';

		/*trata o email*/
		i=0;
      	do
		{
		  informacao.email[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.email[i++] != ';' );
	    informacao.email[--i] = '\0';

		/* trata o telefone*/
		i=0;
        do
		{
		  informacao.fone[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.fone[i++] != ';' );
	    informacao.fone[--i] = '\0';

		/* trata a comunidade*/
		i=0;
    	do
		{
		  informacao.comunidade[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.comunidade[i++] != ';');
	    informacao.comunidade[--i] = '\0';

        /* trata o endereço doação*/
        i=0;
        do
		{
		  informacao.enderdoar[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.enderdoar[i++] != ';');
	    informacao.enderdoar[--i] = '\0';

		/* trata o tipo assentameto*/
	    i=0;
        do
		{
		  informacao.tipoassentamento[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.tipoassentamento[i++] != ';');
	    informacao.tipoassentamento[--i] = '\0';

		/*trata a subprefeitura*/
		i=0;
    	do
		{
		  informacao.subprefeitura[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.subprefeitura[i++] != ';');
	    informacao.subprefeitura[--i] = '\0';

		/* trata qtd de cestas*/
		i=0;
        do
		{
		   ch = fgetc(CSV);
	   	   if ( ch != '\n' && ch != EOF)
	    	cestasaux[i++] = ch;
		   else break;
        }
	    while ( ch != '\n' || ch != EOF );
	    cestasaux[i] = '\0';
	    informacao.qtdcestas = atoi(cestasaux);

	    /* Contabiliza um registro convertido */
		qtdRegistros++;

		/*Grava registro montado no DAT*/
        if (fwrite (&informacao, sizeof(informacao), 1, DAT) != 1 )
	   	   errogravarDAT();

		linha++;
		printf ("\nArquivo 'OSC.CSV' convertido com sucesso!!");
	    //Login ();  /*Função Login*/

		/*system ("cls");*/
		/*getch();*/


	}
	Login ();  /*Função Login*/
	fclose (CSV);
	fclose (DAT);

}


/* Função para encontar tamanho do arquivo DAT */
long int findSize(char file_name[])
{
    long int res;
    /*Abre o arquivo para leitura*/
    FILE* fp = fopen(file_name, "r");
    /*Verifica se o arquivo existe*/
    if (fp == NULL) {
        printf("Arquivo não encontrado!\n");
        return -1;
    }
    /*"Salta" para o fim do arquivo */
    fseek(fp, 0L, SEEK_END);
    /*Calcula o tamanho do arquivo*/
    res = ftell(fp);
    /*Fecha o arquivo*/
    fclose(fp);
    return res;
}

/*Função BuscaBinaria*/
int BuscaBinaria(registro_osc * v, char * cnpj, char * email, int ini, int fim){
	int novoIni = ini;
	int novoFim = fim;
	int meio;

	meio = (ini + fim)/2;
	if (atoll(v[meio].cnpj) == atoll(cnpj)){
		if (strcmp(v[meio].email, email) == 0) {
			return 1;
		}
		return 0;
	}

	if (atoll(v[meio].cnpj) > atoll(cnpj))
		novoFim = meio - 1;
	if (atoll(v[meio].cnpj) < atoll(cnpj))
		novoIni = meio + 1;
	if (ini > fim)
		return 0;

	BuscaBinaria(v, cnpj, email, novoIni, novoFim);
}

/*Função Login*/
int Login (void)
{
	FILE * ArqDAT;
	registro_osc * vet;
	char * cnpj;
	char * email;
	int ind=0;
	int sucessoLogin = 0;

	cnpj = (char *) malloc(sizeof(char) * 15);
	email = (char *) malloc(sizeof(char) * 101);

	/* Alocar dinamicamente a memória para o vetor (vet) de registros (registro_osc)*/
	vet = (registro_osc *) malloc (findSize("OSC.DAT"));
	if ( vet==NULL )
	{
		printf ("\nNão foi possível alocar %ld bytes em memória", findSize("OSC.DAT") );
		getch();
		exit(0);
	}

	/* Copiar o conteúdo do OSC.DAT para a memória alocada*/
   	/* abre o arquivo OSC.DAT para leitura (e depois transportá-lo para memória) */
	ArqDAT = fopen("OSC.DAT", "r");
	if ( ArqDAT==NULL )
	{
		printf ("\nErro o ler OSC.DAT!");
		getch();
		exit(0);
	}

	while (!feof(ArqDAT))	/*Lê do arquivo para o vetor até o fim do arquivo*/
	{
		fread (&vet[ind], sizeof(registro_osc), 1, ArqDAT);
		if (!feof(ArqDAT))
		ind++;		/* Contabiliza um registro lido do OSC.DAT */
	}
	fclose(ArqDAT);

	system("cls");
	do {
		system("color E0");
		printf ("----------------------------------------------------------\n");
    	printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n");
    	printf ("----------------------------------------------------------\n\n");
    	printf ("             << LOGIN DE ACESSO O SISTEMA >>              \n\n");
		printf("-----------------------------------------------------------\n\n");
		printf("\nInforme E-mail e tecle [Enter]: ");
		scanf("%s", email);
		printf("Informe e tecle [Enter]: ");
		scanf("%s", cnpj);

		sucessoLogin = BuscaBinaria(vet, cnpj, email, 0, ind);

		if (!sucessoLogin)
		{
			system("cls");
			printf("FALHA AO REALIZAR LOGIN, INFORMAÇÕES INCORRETAS\n\n");
		}
	}while (!sucessoLogin);
}

/*Função MenuPrincipal*/
int MenuPrincipal (void){

	/*cores
	0 - Preto
	1 - Azul	2 - Verde	3 - Verde-água	4 - Vermelho	5 - Roxo	6 - Amarelo
	7 - Branco	8 - Cinza	9 - Azul claro	A - Verde Claro	B - Verde-água claro
	C - Vermelho Claro	D - Lilás	E - Amarelo Claro	F - Branco Brilhante*/

	/*cores do fundo e texto*/
    system("color B0");

	/* Declaração de variáveis*/
    int opc;

    printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n");
    printf ("----------------------------------------------------------\n\n");
    printf ("                   << MENU PRINCIPAL >>\n\n");
    printf ("      1 - Cadastro de entidades da sociedade civil\n");
    printf ("      2 - Cadastro de assistidos\n");
    printf ("      3 - Cadastro de donativos\n");
    printf ("      4 - Atendimento\n");
    printf ("      5 - Sobre este sistema\n");
    printf ("      0 - Sair do Programa\n\n");
    printf ("----------------------------------------------------------\n");
    printf ("Digite a opção desejada e tecle [Enter]: ");
    scanf ("%d", &opc);
    printf ("----------------------------------------------------------\n");
    getchar();

return opc;
}

/* Função Sobre Sistema */
void Sobre (void){

    /*cores do fundo e texto*/
    system("color A0");

	system ("cls");
    printf ("---------------------------------------------------------------------------\n");
	printf ("			        SOBRE O SISTEMA   \n");
	printf ("---------------------------------------------------------------------------\n\n");
	printf ("  IFSP - INSTITUTO FEDERAL DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA DE SÃO PAULO\n\n");
	printf ("     TECNOLOGIA EM ANÁLISE E DESENVOLVIMENTO DE SISTEMAS - 2º SEMESTRE\n\n\n\n");
    printf ("PROJETO DA DISCIPLINA ESTRUTURA DE DADOS: Ação Social Cidade Solidária\n\n");
	printf ("PROFESSORA: Eurides Balbino\n\n");
	printf ("EQUIPE DE DESENVOLVIMENTO:\n");
    printf ("Igor Kazuhiko       Matr.: 3061973\n");
	printf ("Rivaildo Ferreira   Matr.: 3063968\n\n");
	printf ("---------------------------------------------------------------------------\n\n");
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
    getchar();

}

/*Programa principal*/
int main(){

    /*Add acentos e Ç*/
	setlocale (LC_ALL, "");
	/*Tamanho da Janela*/
	/*system("mode con:cols=75 lines=30");*/

	/*Declaração de variáveis*/
    int opcao;

	ConverteCSVDAT (); /* Função para converter CSV para DAT */
	Login ();  /*Função Login*/

	/*Captura de opção no MenuPrincipal*/
	do{
        system ("cls");
        opcao = MenuPrincipal();

            switch (opcao) {
                case 1: /*MenuEntidades*/
					system ("cls");
                    system ("MenuEntidades");
                break;
                case 2: /*MenuAssistidos*/
                    system ("cls");
                    system ("MenuAssistidos");
                break;
                case 3: /*MenuDonativos*/
                   	system ("cls");
                    system ("MenuDonativos");
				break;
				case 4: /*MenuAtendimento*/
                    system ("cls");
                    system ("MenuAtendimento");
                break;
                case 5: /* Sobre o sistema*/
                    Sobre();
                break;
           		case 0:
                    printf ("Saindo....\n");
					exit(0);
                default:

                    /*cores do fundo e texto*/
					system("color 0C");
					/*system("cls");*/
					printf ("\n\t\tOPÇÃO INVÁLIDA!!!\n\n");
                    printf ("Tecle [Enter] para continuar...");
                    getchar();
                }
    }while(1);

return 0;
}
