#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *vetor_do_arquivo(FILE *f_ptr, long int tam_f);
char *vetor_menos_palavras(char *vetor_ptr, long int tam_f);
FILE *abrir_arquivo_leitura(char *f_endereco_ptr);
FILE *abrir_arquivo_escrita(char *f_endereco_ptr);
int numero_de_palavras(char *vetor_ptr, long int tam_f);
int separar_por_notas(FILE *f_ptr);
long int tamanho_do_arquivo(FILE *f_ptr);
void sair();
void clearf();
void mostrar_arquivo(FILE *f_ptr);
void mostrar_vetor(char *vetor_ptr, long int tam_f);

#endif // ARQUIVOS_H_INCLUDED
