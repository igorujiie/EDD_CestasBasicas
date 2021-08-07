/*
  Programa: Cidade Solidária
  Data....: 31/05/2021
*/

/*Bibliotecas*/
#include <string.h>
#include <memory.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
     
/*Protótipos*/
int MenuEntidades (void);
void ordenaCNPJDAT(void);
long int findSize(char file_name[]) ;
int quickSort(registro_osc *vetorRegistro, int start, int end); 
int partition(registro_osc *vetorRegistro, int start, int pivot) ;
void mostraCNPJ (registro_osc  *v, int tam);

/* Variáveis globais */
registro_osc 	informacao;
FILE      		*CSV;
FILE      		*DAT;
int       		i, cont=0;

/* Funções */
/* Função erro ao ler arquivo DAT */
void errogravarDAT1 (void)
{
	system ("cls");
	printf ("\nERRO AO GRAVAR NO ARQUIVO .DAT");
	getch();
	exit(0);
}

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


int partition(registro_osc *vetorRegistro, int start, int pivot) 
{
	registro_osc aux;
	int i; 
	int bigger = start;
	
	for (i = start; i < pivot; i++) {
		if ( atoll(vetorRegistro[i].cnpj) < atoll(vetorRegistro[pivot].cnpj) )  {
			aux = vetorRegistro[bigger];
			vetorRegistro[bigger] = vetorRegistro[i];
			vetorRegistro[i] = aux;
			bigger++;
		}
	}
	aux = vetorRegistro[bigger];
	vetorRegistro[bigger] = vetorRegistro[pivot];
	vetorRegistro[pivot] = aux;
	return bigger;
}
/* Função para ordenar o arquivo DAT */
int quickSort(registro_osc *vetorRegistro, int start, int end) 
{
	int pivot;
	if (start < end) {
		pivot = partition(vetorRegistro, start, end);
		quickSort(vetorRegistro, start, pivot-1);
		quickSort(vetorRegistro, pivot+1, end);
	}
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
/* Função para ordenar arquivo DAT */
void OrdenaCNPJDAT(void)
{
   FILE * ArqDAT;
   registro_osc  *vet;   
   int   ind=0, indOrd;
   int   qtdRegistros;
   //int   linha=1;
   /* Alocar dinamicamente a memória para o vetor (vet) de registros (registro_osc)*/
   vet = (registro_osc  *) malloc (findSize("OSC.DAT"));
   if ( vet==NULL )
   {
   	  //system ("cls");
   	  printf ("\nNão foi possível alocar %ld bytes em memória", findSize("OSC.DAT") );
   	  getch();
   	  exit(0);
   }
   //debug
   system("cls");
   printf ("\nOSC.DAT tem %ld bytes", findSize("OSC.DAT") );    
   //getch();

   /* Copiar o conteúdo do OSC.DAT para a memória alocada*/   
   /* abre o arquivo OSC.DAT para leitura (e depois transportá-lo para memória) */
   ArqDAT = fopen("OSC.DAT", "r");	
   if (  ArqDAT==NULL )
   {
      printf ("\nErro o ler OSC.DAT!");
	  getch();
	  exit(0);		
   }
   while (!feof(ArqDAT)) /*Lê do arquivo para o vetor até o fim do arquivo*/
   {
   	 fread (&vet[ind], sizeof(registro_osc), 1, ArqDAT);
   	 if (!feof(ArqDAT))
   	    ind++; /* Contabiliza um registro lido do OSC.DAT */
   }
   fclose(ArqDAT);
   //debug
   printf ("\nExistem %i registros no arquivo 'OSC.DAT'", ind ); 
   //getch();
   
   /*Ordena o vetor pelo CNPJ*/
   quickSort(vet, 0, ind-1) ;
   

	/* Transfere o vetor ordenado para o OSC.DAT */
	ArqDAT = fopen("OSC.DAT", "w");	
	if (  ArqDAT==NULL )
	{
      printf ("\nErro o ler OSC.DAT!");
	  getch();
	  exit(0);		
	}

	/*Grava no DAT */
	/* Percorrer o vetor (vet) ordenado e gravar no .DAT */
    for ( indOrd=0; indOrd<ind; indOrd++ )
    {
    	fwrite ( &vet[indOrd], sizeof(vet[indOrd]), 1, ArqDAT);
    	if ( ferror(ArqDAT) )
    	   errogravarDAT1();
	}
	fclose(ArqDAT);
	printf ("\n[%i] registro(s) ordenados(s) com sucesso!!", ind); 
	getch();
	 	   
	/* Mostra os CNPJs ordenados*/
	mostraCNPJ(vet, ind);
	
	/* Libera a memória alocada por malloc */
	free(vet);
}
/*Função mostrar CNPJs ordenados*/
void mostraCNPJ (registro_osc  *v, int tam)
{
    int i;
	system ("cls"); 
	
	FILE * REL;
    REL = fopen ("OSCORGANIZADO.TXT", "w"); /*Cria arquivo de relatório TXT*/
    if (REL == NULL)
    {
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO OSCORGANIZADO.TXT");
		getch();
		exit(0);
	}
	for (i=0; i<tam; i++)
		{
		printf ("\n%s;%s;%s;%s;%s;%s;%s;%s;%d\n",v[i].entidade, v[i].cnpj,v[i].email,v[i].fone,v[i].comunidade,v[i].enderdoar,v[i].tipoassentamento,v[i].subprefeitura,v[i].qtdcestas);
	    fprintf (REL,"\n%s;%s;%s;%s;%s;%s;%s;%s;%d\n\n",v[i].entidade, v[i].cnpj,v[i].email,v[i].fone,v[i].comunidade,v[i].enderdoar,v[i].tipoassentamento,v[i].subprefeitura,v[i].qtdcestas);
	    //fprintf (REL,"\n%s",v[i].cnpj);
		}
	
	fclose (REL);
	getch();
}

			/*----- CONVERSÃO DE CSV PARA DAT ------*/
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
        //debug
        //printf ("\nEntidade: %s", informacao.entidade);
        
        /*trata o cnpj*/
        i=0;
		do
		{
		  informacao.cnpj[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.cnpj[i++] != ';' );
	    informacao.cnpj[--i] = '\0';
        //debug
        //printf ("\ncnpj: %s", informacao.cnpj); 

		/*trata o email*/
		i=0;
      	do
		{
		  informacao.email[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.email[i++] != ';' );
	    informacao.email[--i] = '\0';
        //debug
        //printf ("\ne-mail: %s", informacao.email); 

		/* trata o telefone*/
		i=0;
        do
		{
		  informacao.fone[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.fone[i++] != ';' );
	    informacao.fone[--i] = '\0';
        //debug
        //printf ("\ntelefone: %s", informacao.fone); 

		/* trata a comunidade*/
		i=0;
    	do
		{
		  informacao.comunidade[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.comunidade[i++] != ';');
	    informacao.comunidade[--i] = '\0';
        //debug
        //printf ("\ncomunidade: %s", informacao.comunidade); 
        
        /* trata o endereço doação*/
        i=0; 
        do
		{
		  informacao.enderdoar[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.enderdoar[i++] != ';');
	    informacao.enderdoar[--i] = '\0';
        //debug
        //printf ("\nenderdoar: %s", informacao.enderdoar); 

		/* trata o tipo assentameto*/
	    i=0;		 
        do
		{
		  informacao.tipoassentamento[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.tipoassentamento[i++] != ';');
	    informacao.tipoassentamento[--i] = '\0';
        //debug
        //printf ("\ntipoassentamento: %s", informacao.tipoassentamento);

		/*trata a subprefeitura*/
		i=0;
    	do
		{
		  informacao.subprefeitura[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.subprefeitura[i++] != ';');
	    informacao.subprefeitura[--i] = '\0';
        //debug
        //printf ("\nsubprefeitura: %s", informacao.subprefeitura); 

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
        //debug
        //printf ("\nqtdcestas: %i", informacao.qtdcestas); 

		/* Contabiliza um registro convertido */
		qtdRegistros++; 

		/*Grava registro montado no DAT*/
        if (fwrite (&informacao, sizeof(informacao), 1, DAT) != 1 )
	   	   errogravarDAT();
	    linha++;
	    
		printf ("\n[%i] registro(s) convertido(s) com sucesso!!", qtdRegistros);
		system ("cls");
		 
		//getch();
			
	}
	
	
	fclose (CSV);
	fclose (DAT);
}

/*Funcão para mostrar conteúdo do arquivo DAT*/
void MostraDAT (void)
{
    FILE * REL;
    REL = fopen ("RELOSC.TXT", "w"); /*Cria arquivo de relatório TXT*/
    if (REL == NULL)
    {
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO RELOSC.TXT");
		getch();
		exit(0);
	}
	DAT = fopen ("OSC.DAT", "r"); /*Ler conteúdo do arquivo DAT*/
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO OSC.DAT  ");
		getch();
		exit(0);
	}
	/*Mostra conteúdo do arquivo DAT*/
	printf ("\n----- CONTEÚDO DE OSC.DAT ------");
	printf ("\nENTIDADE		CNPJ		E-MAIL		TELEFONE		COMUNIDADE		ENDEREÇO DOAÇÃO		TIPO ASSENTAMENTO		SUBPREFEITURA		QTD CESTAS");
	printf ("\n-------------------------------------");
	/*Escreve conteúdo do arquivo DAT no arquivo TXT*/
	fprintf (REL, "\n----- CONTEÚDO DE OSC.DAT ------");
	fprintf (REL, "\nENTIDADE		CNPJ		E-MAIL		TELEFONE		COMUNIDADE		ENDEREÇO DOAÇÃO		TIPO ASSENTAMENTO		SUBPREFEITURA		QTD CESTAS");
	fprintf (REL, "\n-------------------------------------");
	
	while ( !feof(DAT) ) /* lê o DAT até o fim do arquivo */
	{
		
		fread (&informacao, sizeof(informacao), 1, DAT);		
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO .DAT  ");
			getch();
			exit(0);
		}
		if (!feof(DAT)) 	/* Mostra registro lido */
		{
			printf  ("\n%s;%s;%s;%s;%s;%s;%s;%s;%d\n\n", informacao.entidade, informacao.cnpj,informacao.email,informacao.fone,informacao.comunidade,informacao.enderdoar,informacao.tipoassentamento,informacao.subprefeitura,informacao.qtdcestas);		
			fprintf (REL,"\n%s;%s;%s;%s;%s;%s;%s;%s;%d\n\n", informacao.entidade, informacao.cnpj,informacao.email,informacao.fone,informacao.comunidade,informacao.enderdoar,informacao.tipoassentamento,informacao.subprefeitura,informacao.qtdcestas);		
		}
		//getch();
	}
	fclose (DAT);
	fclose (REL);
	getch();
	system ("notepad RELOSC.TXT ");
}

/*Função CadEntidades*/
int CadEntidades (void){ 

    /*variáveis*/
    int linha=0;
    
    /*Add acentos e Ç ao texto gravado na variável*/
	setlocale(LC_ALL, "Portuguese_Brasil.1252");  
    
    FILE * CadEnt; 

	//system("cls"); 
	printf ("\nENTRE COM OS DADOS DA NOVA ENTIDADE:\n\n"); 
    printf ("Nome da Entidade...........: ");
	gets   (informacao.entidade);
    printf ("CNPJ.....                  : "); 
    gets   (informacao.cnpj);
    printf ("E-mail.....................: "); 
    gets   (informacao.email); 
    printf ("Telefone...................: "); 
    gets   (informacao.fone);
    printf ("Comunidade Beneficiada.....: ");
    gets   (informacao.comunidade);
    printf ("Endereço...................: ");
    gets   (informacao.enderdoar);
    printf ("Tipo de Assentamento.......: ");
    gets   (informacao.tipoassentamento);
    printf ("Subprefeitura..............: ");
    gets   (informacao.subprefeitura);
    printf ("Quantidades de Cestas:.....: ");
    scanf  ("%d", &informacao.qtdcestas); 
    linha++;

    /*Abrir o arquivo 'OSC.DAT'*/ 
	if ((CadEnt=fopen("OSC.DAT","a+"))==NULL) 
    { 
    	system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO 'OSC.DAT'.  ");
		getch();
		exit(0); 
    }
    /*Grava os dados no DAT*/ 
	if (fwrite (&informacao, sizeof(informacao), 1, CadEnt) != 1 )
		errogravarDAT();
	linha++;

    /*Fecha arquivo*/ 
    fclose(CadEnt);
    system ("cls");
    printf ("\nORDENANDO ARQUIVO 'OSC.DAT'. :\n\n");
    OrdenaCNPJDAT();
      
}

/*Função MenuEntidades*/
int MenuEntidades (void){ 
	/*cores
	0 - Preto
	1 - Azul	2 - Verde	3 - Verde-água	4 - Vermelho	5 - Roxo	6 - Amarelo
	7 - Branco	8 - Cinza	9 - Azul claro	A - Verde Claro	B - Verde-água claro
	C - Vermelho Claro	D - Lilás	E - Amarelo Claro	F - Branco Brilhante*/
	
	/*cores do fundo e texto*/
    system("color 0B");
    
	/* Declaração de variáveis*/
    int opc;
	
    printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("      << CADASTRO DE ENTIDADES DA SOCIEDADE CIVIL >>\n\n"); 
    printf ("      1 - Cadastro de nova entidade\n"); 
    printf ("      2 - Consulta entidades cadastradas\n");
	printf ("      3 - Converter CSV para DAT\n");
    printf ("      4 - Ordenar OSC.DAT\n"); 
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); 
    printf ("----------------------------------------------------------\n");
    printf ("Digite a opção desejada e tecle [Enter]: ");
    scanf ("%d", &opc); 
    printf ("----------------------------------------------------------\n");
    getchar(); 

	return opc; 
}

/*Programa principal*/
int main(){ 
	/*Declaração de variáveis*/
    int opcao; 

    /*Add acentos e Ç*/
	setlocale (LC_ALL, ""); 
	/*Tamanho da Janela*/
	//system("mode con:cols=75 lines=30");
	
	/*Captura de opção no MenuEntidades*/
    do{ 
        system ("cls"); 
        opcao = MenuEntidades(); 

            switch (opcao) { 
                case 1: 
					CadEntidades();
                break; 
                case 2: 
                    MostraDAT(); 
                break; 
                case 3: 
                    ConverteCSVDAT();
				break; 
				case 4: 
                    OrdenaCNPJDAT(); 
                break;  
           		case 0:  exit(0); 
				break;
                
				default: 
                    /*cores do fundo e texto*/
					system("color C0");
					/*system("cls");*/ 
					printf ("\n\t\tOPÇÃO INVÁLIDA!!!\n\n"); 
                    printf ("Tecle [Enter] para continuar..."); 
                    getch();
                } 
    }while( opcao != 0 ); 
	return 0; 
}
