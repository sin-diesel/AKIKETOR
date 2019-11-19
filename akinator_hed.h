

#ifndef AK1NATOR_AKINATOR_HED_H
#define AK1NATOR_AKINATOR_HED_H

#define MAX_OBJECT 100
#define MAX_SIGN 100
#define BEG_VAL "Computer Game"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Onegin.h"

typedef char* elem_t;


struct Node {
    elem_t data;
    struct Node* left;
    struct Node* right;
};

struct Node* visitor (struct Node* Tree, elem_t seek_value, int (*func)(struct Node* node, elem_t a));


int seek_Node(struct Node* node, elem_t data);

struct Node* AddNode(struct Node* node, elem_t after_which, int direction);

struct Node* appendNode(struct Node* node, int direction, char* data);


int PrintTree(struct Node* node, elem_t a);

void createNodes(struct string* commands, struct Node* node, int cmd_size);

int TreeDecrypter(struct Node* tree, FILE* outfile);

void strings_reform(struct string* strings, int str_size);

void create_dot(struct Node* tree, char* dot_out);

void operate(struct Node* tree);

void Delete(struct Node* node);

void DeleteNode(struct Node* tree, elem_t value);

#endif //AK1NATOR_AKINATOR_HED_H
