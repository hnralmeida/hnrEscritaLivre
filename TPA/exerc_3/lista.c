/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: TÃ³picos de ProgramaÃ§Ã£o AvanÃ§ada

Implementacao de sentinelaSimples.h
=========================================================================================
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/*
=========================================================================================
			Implementacao de sentinelaSimples.h
*/


// inicializa lista com ponteiros nulos
void initializeList(Tlist *list){
	list->first=NULL;
	list->last=NULL;
	list->total=0;
}

// subfuncao de addElement
void addIn(Tlist * list, unsigned long long int  reg, string name){

	Tnode *newNode = (Tnode *)malloc(sizeof(Tnode));
	int flag=1;
	newNode->reg = reg;
	newNode->next = NULL;
	strcpy(newNode->name, name);	
	if(list->first == NULL){
		//Lista VAZIA: inserir o primeiro N?.
		list->first = newNode;
		list->last = newNode;
	} else {
		//Lista possui pelo menos um N?: Inserir dados em
		//ordem crescente.
		Tnode *actual = list->first;
		Tnode *previous = NULL;
		
		while(actual != NULL && (newNode->reg >= actual->reg) ){
			previous = actual;
			actual = actual->next;
		}	
		
		if (actual == NULL && (previous!= list->first) ){
			previous->next = newNode;
			list->last = newNode;
		}else if (actual == list->first){
			newNode->next = actual; 
			list->first = newNode;
		}else{
			newNode->next = actual;
			previous->next = newNode;
		}


	}//if ... else
	
	list->total++;
}

// adiciona curso passada como parÃ¢metro na lista 
void addElement(Tlist *list){
	unsigned long long int reg;
	string name;
	
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");
	printf("Informe valor: ");
	scanf("%llu", &reg);

	printf("\nInforme nome do aluno: ");
	scanf("%s", &name);
	
	addIn(list, reg, name);
}

// imprimir valores na lista
void printList(Tlist *list){
	int i=0;
	Tnode *cell = list->first;
	
	if(cell == NULL) printf(" -");
	
	while (cell!=NULL){
		printf(" -> %llu", cell->reg);
		cell = cell->next;
	}
}

// subfuncao de removeElement
void removeIn(Tlist * list, unsigned long long int reg){

	Tnode *actual = list->first, *prev = NULL;
	string removed_name;
	unsigned long long int removed_reg;
	int removed = 0;

	if(actual == NULL)
		printf("\nNao ha nada para remover na lista");
	else{
		while(actual != NULL && (actual->reg != reg)){
			prev = actual;
			actual = actual->next;
		}//while

		if(actual!=NULL){
			strcpy(removed_name, actual->name);
			removed_reg = actual->reg;
			removed = 1;
			list->total--;
		}
		else {
			printf("Esse elemento nao existe");
			return;
		}
		
		if(actual->next == list->last){ //verificar se remover o ultimo
			prev->next = NULL;
			list->last = prev;
			free(actual);
		}else if(prev == NULL){ // verificar se remover o primeiro;
			prev = actual->next;
			list->first = prev;
			free(actual);
		}else{ // caso remover algum do meio qualquer
			prev->next = actual->next;
			free(actual);
		}//if
	}
	
	if(removed){
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("\tAVISO:\n");
		printf("\n\t%s\n", removed_name);
		printf("\t%llu\n", removed_reg);
		printf("\n\tREMOVIDO com SUCESSO !!!\t\n");
		printf("+--------------------------------------+\n\n\n");
		
	} else {
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("|  ALERTA:                             |\n");
		printf("|                                      |\n");
		printf("|  No NAO ENCONTRADO e nem REMOVIDO!!! |\n");
		printf("|                                      |\n");
		printf("+--------------------------------------+\n\n\n");

	}
}

// remover valores da lista
void removeElement(Tlist *list){

	unsigned long long int reg;
	
	printf("\n\n\t=====| REMOVER No |=====\n\n");
	printf("\tInforme VALOR a ser REMOVIDO: ");
	scanf("%llu", &reg);

	removeIn(list, reg);
}
