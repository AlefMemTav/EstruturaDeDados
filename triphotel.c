/*
    Objetivo: Abrir arquivo com um texto
    e gerar vetor de vocabulario e cinco arquivos
    e cinco vetores e calcular TF-IDF

    Entrada: Endereço do arquivo

    Saída: TF-IDF
*/
#include "arquivos.h"
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMITE 1024
#define TAM_P 35
//Estrutura de dados csv:
struct vocabulario{
    char palavra[TAM_P];
};
//Menu de opções obs: Declarada aqui por causa do setlocale
void mensagem_menu(){
    printf("        Trip advisor hotel avaliações      \n");
    printf("1 - Abrir arquivo de avaliações.\n");
    printf("2 - Gerar vocabulário.\n");
    printf("3 - Exibir TF-IDF.\n");
    printf("4 - Exibir TF-IDF de uma nota.\n");
    printf("5 - Sair.\n");
    printf("Digite uma opção: \n");
}
int main(){
    //Declarações
    char endereco_arquivo[30];//Ponteiro para endereço do arquivo
    char *nome_ptr_1;// Ponteiro para armazenar nome de arquivo digitado
    char *vetor_palavras_csv = NULL;//Vetor de palavras sem as pontuações
    char *vetor_palavras_csv_s3c = NULL;//" " e sem três caracteres
    char *vetor_ptr_2;
    char *vetor_auxiliar = NULL;
    char *vetor_auxiliar_2 = NULL;
    char *parte = NULL;
    char *vetor_avaliacao;
    FILE *arquivo_csv = NULL;//Arquivo principal csv no qual se buscará os simbolos especificos
    FILE *arquivo_nota1 = NULL;//Arquivo com as avaliações de nota 1
    FILE *arquivo_nota2 = NULL;//" " nota 2
    FILE *arquivo_nota3 = NULL;//" " nota 3
    FILE *arquivo_nota4 = NULL;//" " nota 4
    FILE *arquivo_nota5 = NULL;//" " nota 5
    FILE *arquivo_vocabulario = NULL;
    int opcao;
    int i, j;
    int pos_i;
    int pos_f;
    int num_palavras;//Número de palavras totais
    int caractere;
    int bandeira_1, bandeira_2, bandeira_3, bandeira_4 = 0;
    int tam_caracteres;
    long int tam_csv;//Tamanho do arquivo_csv
    long int tam_n1;//" " nota1
    long int tam_n2;//" " nota2
    long int tam_n3;//" " nota3
    long int tam_n4;//" " nota4
    long int tam_n5;//" " nota5
    struct vocabulario *palavras_arquivo;
    //Instruções
    i = 0;
    j = 0;
    //Inicializar tamanho do arquivo csv
    tam_csv = 0;
    //Adaptar idioma de localidade
    setlocale(LC_ALL,"");
    //Sinal onde deve retornar
    sinal:
    //Limpar a tela após retorno
    if(opcao != 0 && opcao != 6){
        getch();
        clearf();
    }
    //Chamar menu de escolhas
    mensagem_menu();
    //Ler escolha do usuário
    scanf("%d", &opcao);
    //Limpar a tela
    clearf();
    switch(opcao){
        //Abrir arquivo csv para leitura
        case 1:
            /*          Etapas
                      1) Abrir arquivo csv FEITO
                      2) Separar avaliacao por notas em cinco arquivos FEITO
                      3) Calcular tam_csv FEITO
                      4) Gerar vetor_ptr_csv_s3c FEITO
            */
            printf("Digite o endereço do arquivo a ser aberto:\n");
            //Ler dados
            scanf("%s", endereco_arquivo);//A string do tipo palavra.csv
            arquivo_csv = abrir_arquivo_leitura(endereco_arquivo);
            if(arquivo_csv == NULL){
                //Não aberto
                printf("Erro! Arquivo %s não pode ser aberto.\n", endereco_arquivo);
            }else{
                //Verdadeiro
                bandeira_1 = 1;
                //Aberto
                printf("Arquivo %s aberto com sucesso.\n", endereco_arquivo);
                //Nome do arquivo digitado
                nome_ptr_1 = endereco_arquivo;
                //Cincos arquivos com texto separado por notas
                separar_por_notas(arquivo_csv);
                //Tamanho do arquivo
                tam_csv = tamanho_do_arquivo(arquivo_csv);
                printf("Tamanho do arquivo: %d", tam_csv);
                vetor_palavras_csv = calloc(tam_csv, sizeof(char));
                //Vetor de palavras sem pontuações
                vetor_palavras_csv = vetor_do_arquivo(arquivo_csv, tam_csv);
                //Fechar arquivo
                fclose(arquivo_csv);
                vetor_palavras_csv_s3c = calloc(tam_csv, sizeof(char));
                //Vetor sem palavras iguais ou menores que 3 caracteres
                vetor_palavras_csv_s3c = vetor_menos_palavras(vetor_palavras_csv, tam_csv);
                //Liberar vetor antigo
                free(vetor_palavras_csv);
            }
            goto sinal;
            break;
        //Gerar vetor de vocabularios
        case 2:
            /*          Etapas
                      1) Gerar vetor vocabulario FEITO
                      2) Eliminar palavras com menos de três caracteres FEITO
                      3) Calcular numero de palavras total do arquivo FEITO
                      4) Eliminar palavras repetidas do vetor FALTA
            */
            if(bandeira_1 = 1){
                vetor_auxiliar = calloc(35, sizeof(char));
                //mostrar_vetor(vetor_palavras_csv_s3c, tam_csv);
                i = 0;
                //Armazenar vetor em arquivo
                arquivo_vocabulario = fopen("vocabulario.txt", "a");
                fputs(vetor_palavras_csv_s3c, arquivo_vocabulario);
                fclose(arquivo_vocabulario);
                //Quantidade total de palavras do arquivo csv
                num_palavras = numero_de_palavras(vetor_palavras_csv_s3c, tam_csv);
                //Ver
                printf("Numero total de palavras: %d\n", num_palavras);
                palavras_arquivo = calloc(num_palavras, sizeof(struct vocabulario));
                /*
                abrir_arquivo_leitura("vocabulario.txt");
                //A PARTIR DAQUI É PRECISO GERAR VETOR COM PALAVRAS NÃO-REPETIDAS
                while(!feof(arquivo_vocabulario)){
                    //Pegar uma string do arquivo
                    fgets(vetor_auxiliar, TAM_P, arquivo_vocabulario);
                    //Substituir o \n por \0 no vetor_palavra
                    //vetor_auxiliar[strcspn(vetor_auxiliar, "\n")] = '\0';
                    printf("Do arquivo: %s\n", vetor_auxiliar);
                    //Procurar entre vetor do arquivo e vetor palavra
                    if(strstr(vetor_auxiliar, vetor_palavras_csv_s3c[i]) == 0){
                        //Ver
                        printf("Do vetor: %s\n", vetor_palavras_csv_s3c[i]);
                    }else{
                        //printf("Não encontrado. \n");
                    }
                }
                close(arquivo_vocabulario);
                */
                /*
                i = 0;
                //A posicao inicial
                pos_i = 0;
                //A posição quando encontra número
                pos_f = 0;
                while(!feof(arquivo_vocabulario)){
                    //Pegar uma string do arquivo
                    fgets(vetor_auxiliar, TAM_P, arquivo_vocabulario);
                    printf("Do arquivo: %s\n", vetor_auxiliar);
                    i = pos_i;
                    //Procurar nova linha
                    while((vetor_palavras_csv_s3c[i++] != '\n')){
                        //Se encontrar uma palavra
                        if(vetor_palavras_csv_s3c[i] == '\n'){
                            //A posição em que '\n' foi achado
                            pos_f = i;
                        }
                    }
                    //Armazenar palavra encontrada
                    for(pos_i = pos_i; pos_i < pos_f; pos_i++){
                        vetor_auxiliar_2[j++] = vetor_palavras_csv_s3c[pos_i];
                    }
                    //CONFERIR
                    printf("Palavra aux: %s Ln: %d Sz: %d\n", vetor_auxiliar_2, strlen(vetor_auxiliar));
                    //Se as duas palavras forem iguais
                    if(strcmp(vetor_auxiliar, vetor_auxiliar_2) == 0){
                        //Achou
                        printf("Palavra %s achada", vetor_auxiliar_2);
                    }
                    //Limpar vetor
                    //Zerar contador
                    j = 0;
                    //Nova posição inicial da procura
                    pos_i = pos_f;
                }
                */
                /*
                parte = strtok(vetor_ptr, "\n");
                do{
                    j++;
                    //Se encontrar uma quebra de linha
                    if(vetor_ptr[j] == '\n'){
                        //Armazenar
                        //for(i = 0; i <= j; i++){
                            //vetor_copia[i] = vetor_ptr[i];
                        //}
                        //Se as palavras forem iguais
                        if(strcmp("Jose", parte) == 0){
                            printf("Achou");
                            break;
                        }
                    }
                    j++;
                    parte = strtok(NULL, "\n");
                }while((vetor_ptr[i] != EOF) && (parte != EOF));
                */
                //Quando tiver resolvido isso, publicar:
                printf("Vetor vocabulário e arquivo vocabulário gerado com sucesso.\n ");
                printf("Deseja vizualizar o vetor? (1 para sim 2 para não).\n");
                scanf("%d", &opcao);
                if(opcao == 1){
                    mostrar_vetor(vetor_palavras_csv_s3c, tam_csv);
                }
                free(vetor_palavras_csv_s3c);
            }else{
                printf("Não foi possivel encontrar vetor vocabulário.\n ");
            }
            goto sinal;
            break;
        //Substituir palavras
        case 3:
            /*          Etapas
                      1) Calcular TF-IDF
            */
            goto sinal;
            break;
        //Mostrar arquivo principal se já fora aberto
        case 4:
            /*          Etapas
                      1) Exibir TF-IDF para uma nota
            */
            goto sinal;
            break;
        case 5:
            sair();
            if(bandeira_1 == 1){
                //fclose(arquivo_nota1);
                //fclose(arquivo_nota2);
                //fclose(arquivo_nota3);
                //fclose(arquivo_nota4);
                //fclose(arquivo_nota5);
            }
            break;
        default:
            break;
    }
    return 0;
}
