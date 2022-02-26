#include "arquivos.h"
/*                      Parametros
        f_endereco_ptr: Endereço digitado do arquivo.
        f_ptr: Arquivo de endereço f_endereco_ptr.
        tam_f: Tamanho do arquivo f_ptr.
        f_vetor_p_ptr: Vetor que armazena uma palavra do arquivo f_ptr.
*/
//Criar vetor de palavras do arquivo sem as pontuações
char *vetor_do_arquivo(FILE *f_ptr, long int tam_f){
    //Declarações
    char *vetor_ptr = calloc(tam_f, sizeof(char));
    char *vetor_final = calloc(tam_f, sizeof(char));
    long int i, j;
    //Instruções
    i = 0;
    j = 0;
    //Mover o ponteiro em uma unidade a partir do inicio
    fseek(f_ptr, 1, SEEK_SET);
    //Posicionar na posicao inicial
    rewind(f_ptr);
    //1)Remover as pontuações
    //Enquanto não chegar no fim do arquivo
    while( !feof(f_ptr) ){
        //Enquanto não chegar no tamanho do vetor
        for(i = 0; i <= tam_f; i++){
            vetor_ptr[i] = fgetc(f_ptr);
            //Se pontuações ou numerais na tabela ASCII
            if(((vetor_ptr[i] >= 33)&&(vetor_ptr[i] <= 47)) ||
               ((vetor_ptr[i] >= 48)&&(vetor_ptr[i] <= 57)) ||
               ((vetor_ptr[i] >= 58)&&(vetor_ptr[i] <= 64)) ||
               ((vetor_ptr[i] >= 91)&&(vetor_ptr[i] <= 96)) ||
               ((vetor_ptr[i] >= 123)&&(vetor_ptr[i]<=126))){
                //Substituir por caractere nulo
                vetor_ptr[i] = '\0';
            }
        }
    }
    //2)Remover espaços
    //Enquanto não chegar no tamanho do vetor
    for(i = 0; i <= tam_f; i++){
        //Se espaço na tabela ASCII
        if(((vetor_ptr[i] >=  7)&&(vetor_ptr[i] <=  9)) ||
           ((vetor_ptr[i] >= 11)&&(vetor_ptr[i] <= 15)) ||
            (vetor_ptr[i] == 32)||(vetor_ptr[i] == EOF)){
            //Substituir por caractere quebra de linha
            vetor_ptr[i] = '\n';
        }
    }
    //3)Remover quebra de linha em excesso
    for(i = 0; i <= tam_f; i++){
        //Se quebra de linha na tabela ASCII
        if((vetor_ptr[i] == 10)&&(vetor_ptr[i+1] == 10)){
            //Substituir por caractere nulo
            vetor_ptr[i] = '\0';
        }
    }
    //4)Remover caracteres nulos
    for(i = 0; i <= tam_f; i++){
        //Se caractere nulo
        if(vetor_ptr[i] == '\0'){
                ;
        }else{
            vetor_final[j] = vetor_ptr[i];
            j++;
        }
    }
    vetor_final[tam_f] = EOF;
    return vetor_final;
}
//Recriar vetor eliminando palavras com menos de três caracteres
char *vetor_menos_palavras(char *vetor_ptr, long int tam_f){
    //Declarações
    char *vetor_final = calloc(tam_f, sizeof(char));
    int i, j;
    //Instruções
    i = 0;
    j = 0;
    //1) Remover palavras com menos de 3 caracteres
    for(i = 0; i <= tam_f; i++){
        //Se palavra separada por '\n' tiver 3 caracteres ou dois caracteres
        if((vetor_ptr[i]==10)&&(vetor_ptr[i+4]==10)){
            //Substituir por caractere nulo
            vetor_ptr[i+1] = '\0';
            vetor_ptr[i+2] = '\0';
            vetor_ptr[i+3] = '\0';
        }else if((vetor_ptr[i]==10)&&(vetor_ptr[i+3]==10)){
            //Substituir por caractere nulo
            vetor_ptr[i+1] = '\0';
            vetor_ptr[i+2] = '\0';
        }
    }
    //3)Remover quebra de linha em excesso
    for(i = 0; i <= tam_f; i++){
        //Se quebra de linha na tabela ASCII
        if(((vetor_ptr[i] == 10)&&(vetor_ptr[i+4] == 10)) ||
           ((vetor_ptr[i] == 10)&&(vetor_ptr[i+3] == 10)) ||
           ((vetor_ptr[i] == 10)&&(vetor_ptr[i+2] == 10)) ||
           ((vetor_ptr[i] == 10)&&(vetor_ptr[i+1] == 10))){
            //Substituir por caractere nulo
            vetor_ptr[i] = '\0';
        }
    }
    //2) Remover caracteres nulos
    for(i = 0; i <= tam_f; i++){
        //Se caractere nulo
        if(vetor_ptr[i] == '\0'){
                ;
        }else{
            vetor_final[j] = vetor_ptr[i];
            j++;
        }
    }
    vetor_final[tam_f] = EOF;
    return vetor_final;
}
//Abrir arquivo existente para leiturua.
FILE *abrir_arquivo_leitura(char *f_endereco_ptr){
    //Retornar arquivo existente aberto para leitura
    return fopen(f_endereco_ptr, "r");
}
//Abrir novo arquivo para escrita
FILE *abrir_arquivo_escrita(char *f_endereco_ptr){
    //Retorna o arquivo aberto para escrita
    return fopen(f_endereco_ptr, "w");
}
//Calcular palavras de um vetor dividido por quebra de linhas
int numero_de_palavras(char *vetor_ptr, long int tam_f){
    //Declarações
    int contador;
    int i;
    //Instruções
    contador = 0;
    i = 0;
    //Comparar enquanto não chegar no fim do arquivo
    for(i = 0; i < tam_f; i++){
        //Se encontrou quebra de linha ou fim do arquivo e não é um numero
        if((vetor_ptr[i] == '\n')&&(vetor_ptr[i-1] < 48 || vetor_ptr[i-1] > 57)){
            contador++;
        }
    }
    return contador;
}
//Criar arquivos txt com as avaliacoes por notas
int separar_por_notas(FILE *f_ptr){
    //Declarações
    char vetor_aux[20000];
    char c;
    FILE *f_n1 = NULL;//Arquivo com as avaliações de nota 1
    FILE *f_n2 = NULL;//" " nota 2
    FILE *f_n3 = NULL;//" " nota 3
    FILE *f_n4 = NULL;//" " nota 4
    FILE *f_n5 = NULL;//" " nota 5
    int i;
    //Instruções
    f_n1 = fopen("nota1.txt", "a+");
    f_n2 = fopen("nota2.txt", "a+");
    f_n3 = fopen("nota3.txt", "a+");
    f_n4 = fopen("nota4.txt", "a+");
    f_n5 = fopen("nota5.txt", "a+");
    c = fgetc(f_ptr);
    while (c != EOF) {
        if(c == '"') {
            memset(vetor_aux, 0, 20000);
            c = fgetc(f_ptr);
            i = 0;
            while (c != '"'){
                vetor_aux[i] = c;
                c = fgetc(f_ptr);
                i++;
            }
            vetor_aux[i] = '\n';
        }
        switch(c){
            case '1':
                fputs(vetor_aux, f_n1);
                break;
            case '2':
                fputs(vetor_aux, f_n2);
                break;
            case '3':
                fputs(vetor_aux, f_n3);
                break;
            case '4':
                fputs(vetor_aux, f_n4);
                break;
            case '5':
                fputs(vetor_aux, f_n5);
                break;
            default:
                break;
        }
        c = fgetc(f_ptr);
    }
    memset(vetor_aux, 0, 20000);
    fclose(f_n1);
    fclose(f_n2);
    fclose(f_n3);
    fclose(f_n4);
    fclose(f_n5);
    return 1;
}
//Gerar tamanho de um arquivo
long int tamanho_do_arquivo(FILE *f_ptr){
    //Instruções
    //Posicionar o indicador no fim do arquivo
    fseek(f_ptr, 0, SEEK_END);
    //Retornar tamanho do arquivo
    return ftell(f_ptr);
}
//Limpar tela
void clearf(){
    system("cls || clear");
}
//Ler cada caractere de arquivo e imprimir na tela
void mostrar_arquivo(FILE *f_ptr){
    //Declarações
    int caractere;
    //Instruções
    //Enquanto não chegar no fim do arquivo
    while(!feof(f_ptr)){
        //Ler cada caractere por posição
        caractere = fgetc(f_ptr);
        //Exibir cada caracter, exceto o último
        if(caractere != EOF){
            //Exibir caracter
            printf("%c", (char)caractere);
        }
        //putchar(ch);//Printar cada caractere
    }
}
//Mostrar o vetor um arquivo
void mostrar_vetor(char *vetor_ptr, long int tam_f){
    //Declarações
    long int i;
    //Instruções
    for(i = 0; i < tam_f; i++){
        printf("%c", vetor_ptr[i]);
    }
}
//Sair do programa:
void sair(){
    printf("\n ----- Encerrado com sucesso ----- \n");
    getch();
    clearf();
}
/*
//Prototipo de uma potencial função
char *procurar_frase(char *vetor_ptr, long int i){
    //Declarações
    char vetor_auxiliar[1024];
    int pos_i;
    int pos_f;
    long int j;
    //Instruções
    j = 0;
    //A posicao inicial
    pos_i = 0;
    //A posição quando encontra número
    pos_f = 0;
    //flag1 = 1;
    //A posição final em que o número foi achado
    pos_f = i;
    //Para a posição inicial até a posição do número achado
    for(pos_i = pos_i; pos_i < pos_f; pos_i++){
        //O vetor_avaliacao recebe a avaliação
        vetor_auxiliar[j++] = vetor_ptr[pos_i];
    }
    memset(vetor_auxiliar, 0, 1024);
    j = 0;
    //Nova posição inicial da procura
    pos_i = pos_f;
    return vetor_auxiliar;
}
*/
