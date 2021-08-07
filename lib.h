/*Bibliotecas*/
#include <string.h>
#include <memory.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/*tipos pre-definidos */
typedef struct
{
	char 	entidade				[120+1];
	char    cnpj					[14+1];
	char    email                   [100+1];
	char    fone					[11+1];
    char    comunidade				[30+1];
    char    enderdoar				[150+1];
    char    tipoassentamento		[50+1];
    char    subprefeitura			[50+1];
    int		qtdcestas;
}
registro_osc;

typedef struct
{
	char	nomecompleto			[120+1];
	char	datanasc				[10+1];
	char	cpf						[11+1];
	char	municipio				[100+1];
	char	logradouro 				[150+1];
	char	nro						[7+1];
	char	complemento				[10+1];
	char	bairro					[150+1];
	char	celular					[11+1];
	char	possuipet				[1+1];

}
registro_ass;

/*variaveis globais*/
long int 	TAMANHO_VETOR;
int			gerenciaOSC;

/*Funções*/

int validaTipoAssentamento(char *tipo){
	char	tiposValidos[15][30] =
	{
	"Favela",
	"Cortiço",
	"Ocupação",
	"Loteamento",
	"Comunidade indígena",
	"Grupo de mulheres",
	"Imigrantes ou Refugiados",
	"Criança e adolescente",
	"Idosos",
	"Minorias étnico-raciais",
	"LGBTI",
	"Pessoas em situação de rua",
	"Egresso do sistema prisional",
	"Pessoa com deficiência",
	"Outros"
	};
	int i, achou = 0;
	for(i=0; i<15; i++)
		if(strcmp(tipo,tiposValidos[i])==0)
		{
			achou = 1;
			break;
		}
	return(achou);
}

int validaSubprefeitura(char * subprefeitura)
{
	char subprefeiturasValidas[32][30] = {
	"Aricanduva",
	"Butantã",
	"Campo Limpo",
	"Capela do Socorro",
	"Casa Verde",
	"Cidade Ademar",
	"Cidade Tiradentes",
	"Ermelino Matarazzo",
	"Freguesia do Ó",
	"Guaianases",
	"Ipiranga",
	"Itaim Paulista",
	"Itaquera",
	"Jabaquara",
	"Jaçanã Tremembé",
	"Lapa",
	"M'Boi Mirim",
	"Mooca",
	"Parelheiros",
	"Penha",
	"Perus",
	"Pinheiros",
	"Pirituba Jaraguá",
	"Santana Tucuruvi",
	"Santo Amaro",
	"São Mateus",
	"São Miguel Paulista",
	"Sapopemba",
	"Sé",
	"Vila Maria Vila Guilherme",
	"Vila Mariana",
	"Vila Prudente",
	};
	int i, achou = 0;
	for (i=0; i<32; i++)
		if(strcmp(subprefeitura,subprefeiturasValidas[i])==0);
		{
			achou =1;

		}

	return(achou);
}

int validaCNPJ(char* cnpj)
{
	int i;
	if(strlen(cnpj)!=14)
		return(0);
	for(i=0; cnpj[i]!='\0'; i++)
		if(cnpj[i]<'0' || cnpj[i]>'9')
			return(0);
	return(1);
}


