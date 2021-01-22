#ifndef __DICT_H
#define __DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
	char* key; 
	char* value;
	struct node* next;
} Node;

typedef Node* Dict; // Dict == Node*

/* CONSTRUCTORS */
Dict dict(); // creates an empty dictionary
Node* createNode(char*, char*); // creates a Node with the given args, next points to NULL
void addNode(Dict*, char*, char*); // create a Node and add it at the end of a dictionary

/* SETTERS */
void setValue(Dict, char*, char*); // change the value from a given key

/* GETTERS */
char* getValue(Dict, char*); // get the value from a given key
char** getKeys(Dict); // get every keys of a dict in an array --REMEMBER TO DESTROY IT--
char** getValues(Dict); // get every values of a dict in an array --REMEMBER TO DESTROY IT--
int getLen(Dict); // get the length of the dictionary

/* DESTROYERS */
void destroyDict(Dict); // destroy the whole dictionary 
void destroyKeysArray(char**); // destroy the array given by the getKeys() function
void destroyValuesArray(char**); // destroy the array given by the getValues() function
void destroyNode(Node*); // Destroy a single Node

/* OTHER */
bool hasKey(Dict, char*); // true if there is the key, false otherwise
void printNode(Node* n); // print a single node
void printDict(Dict); // print the whole dictionary
void error(char*, int); // print an error and exit with code given


Dict dict() {
	return NULL;
}

Node* createNode(char* key, char* value) {
	if (!key) error("key cannot be NULL", -3);
	if (!value) error("value cannot be NULL", -3);
	Node* node = malloc(sizeof(Node));
	node -> key = strdup(key);
	node -> value = strdup(value);
	node -> next = NULL;
	return node;
} 

void addNode(Dict* d, char* key, char* value) {
	Node* tmp = createNode(key, value);
	while (*d) {
		if (!strcmp((*d)->key, key)) error("key already exists", -1);
		d = &(*d)->next;
	}
	tmp -> next = *d;
	*d = tmp;
}

void setValue(Dict d, char* key, char* value) {
 	char *p = getValue(d, key);
 	free(p);
 	p = strdup(value);
}

char* getValue(Dict d, char *key) {
	while (d) {
		if (!strcmp(key, d->key)) return d->value;
		d = d->next;
	}
	error("key doesn't exists", -2);
}

char** getKeys(Dict d) {
	int len = getLen(d);
	
	char** ret = calloc(len+1, sizeof(char*));
	int i;
	for (i = 0; i < len; i++, d = d->next) {
		ret[i] = strdup(d->key);
	}	
	ret[i] = NULL;
	return ret;
}

char** getValues(Dict d) {
	int len = getLen(d);
	
	char** ret = calloc(len+1, sizeof(char*));
	int i;
	for (i = 0; i < len; i++, d = d->next) {
		ret[i] = strdup(d->value);
	}	
	ret[i] = NULL;
	return ret;
}

int getLen(Dict d) {
	int i;
	for (i = 0; d; i++, d = d->next);
	return i;
}

void destroyDict(Dict d) {
	if (d) {
		destroyDict(d->next);
		destroyNode(d);
	} else free(d);
}

void destroyKeysArray(char** keys) {
	for (int i = 0; keys[i]; i++) {
		free(keys[i]);
	}
	free(keys);
}

void destroyValuesArray(char** values) {
	destroyKeysArray(values);
}


void destroyNode(Node* d) {
	free(d->key);
	free(d->value);
	free(d);
}

bool hasKey(Dict d, char *key) {
	while (d) {
		if (!strcmp(key, d->key)) return true;
		d = d->next;
	}
	return false;
}

void printNode(Node* n) {
	printf("%s: %s", n->key, n->value);
}

void printDict(Dict d) {
	printf("{");
	while (d) {
		printNode(d);
		if (d->next) printf(", ");
		d = d->next;
	}
	printf("}\n");
}

void error(char* err, int code){
	printf("ERROR: %s\n", err);
    printf("Exiting with %d code\n", code);
    exit(code);
}

#endif