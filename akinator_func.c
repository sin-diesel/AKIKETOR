#include "akinator_hed.h"
#define MAX_OBJECT 100
#define MAX_SIGN 100
#define BEG_VAL "Computer Game"


struct Node* res = NULL;

struct Node* visitor (struct Node* Tree, elem_t seek_value, int (*func)(struct Node* node, elem_t a)) {

    int state = 0;
    state = func(Tree, seek_value);


    if (state != 0) {
        if (Tree->left) {
            visitor(Tree->left, seek_value, func);
        }
    }
    if (state == 0) {
        if (res == NULL)
            res = Tree;
    }
    if (state != 0) {
        if (Tree->right) {
            visitor(Tree->right, seek_value, func);
        }
    }
    return res;
}

int seek_Node(struct Node* node, elem_t data) {
    if (strcmp(node->data, data) == 0) {
        return 0;
    } else {
        return 1;
    }
}

struct Node* AddNode(struct Node* node, elem_t after_which, int direction) {

    struct Node* which = visitor(node, after_which, seek_Node);

    struct Node* prev_left = which->left;
    struct Node* prev_right = which->right;

    if (direction == 0) {

        which->left = (struct Node *) calloc(1, sizeof(struct Node));
        //which->left->data = "1";

        (which->left)->left = prev_left;
        return which->left;
//TODO
    } else {

        which->right = (struct Node *) calloc(1, sizeof(struct Node));
        //which->right->data = "1";

        (which->right)->right = prev_right;
        //(which->left)->right = NULL;

        return which->right;

    }
}

struct Node* appendNode(struct Node* node, int direction, char* data) {

    if (direction == 0) {

        node->left = (struct Node *) calloc(1, sizeof(struct Node));
        node->left->data = data;

        (node->left)->left = NULL;
        (node->left)->right = NULL;

        return node->left;
    } else {

        node->right = (struct Node *) calloc(1, sizeof(struct Node));
        node->right->data = data;

        (node->right)->left = NULL;
        (node->right)->right = NULL;

        return node->right;

    }
}

int PrintTree(struct Node* node, elem_t a) {
    printf("%s ", node->data);
    return 1;
}

void createNodes(struct string* commands, struct Node* node, int cmd_size) {
    static int i = 0;

    int value = 0;

    if (i == cmd_size) {
        return;
    }

    if (strcmp(commands[i].str, "{l") == 0) {

        node->left = (struct Node *) calloc(1, sizeof(struct Node));
        ++i;
        createNodes(commands, node->left, cmd_size);

    } else if (strcmp(commands[i].str, "{r") == 0) {

        node->right = (struct Node*) calloc(1, sizeof(struct Node));
        ++i;
        createNodes(commands, node->right, cmd_size);

    } else if (strcmp(commands[i].str, "}") == 0) {
        ++i;
        return;
    } else {
        node->data = commands[i].str;
        ++i;
    }
    createNodes(commands, node, cmd_size);
    return;

}

void create_tree(struct Node* tree, FILE* dot_out) {

    if (tree->left != NULL) {
        fprintf (dot_out, "\n\t\t\"%s\"[shape = \"ellipse\", color=\"#900000\", style=\"filled\", fillcolor = \"#D0FDFF\"];\n"
                          "\t\t\"%s\"->\"%s\"[label = \"YES\"];\n", tree->data, tree->data, (tree->left)->data);

        create_tree (tree->left, dot_out);
    }

    if (tree->right != NULL) {
        fprintf(dot_out,
                "\n\t\t\"%s\"[shape = \"egg\", color=\"#900000\", style=\"filled\", fillcolor = \"#D0FDFF\"];\n"
                "\t\t\"%s\"->\"%s\"[label = \"NO\"];\n", tree->data, tree->data, (tree->right)->data);

        create_tree(tree->right, dot_out);
    }
}

int TreeDecrypter(struct Node* tree, FILE* outfile) {

    fprintf(outfile, "%s\n", tree->data);

    if (tree->left != NULL) {
        fprintf(outfile, "{l\n");
        TreeDecrypter(tree->left, outfile);
    }
    if (tree->right != NULL) {
        fprintf(outfile, "{r\n");
        TreeDecrypter(tree->right, outfile);

    }

    if (strcmp(tree->data, BEG_VAL) != 0) {
        fprintf(outfile, "}\n");
    }
    return 0;
}

void strings_reform(struct string* strings, int str_size) {

    for (int i = 0; i < str_size; ++i) {
        char *p = strings[i].str;
        while (*p != '\0') {
            ++p;
        }
        *p = '\n';
    }

}

void create_dot(struct Node* tree, char* dot_out) {
    FILE *file_dot = fopen(dot_out, "wb");

    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[shape = \"cube\", color = \"#800000\", fontsize = 15, style = \"filled\", fillcolor = \"#88CEFA\"];\n"
                      "\tedge[color = \"#190970\", fontsize = 11];\n");


    create_tree (tree, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

}

void operate(struct Node* tree) {

    unsigned long maxobj = 100;
    unsigned long maxsign = 100;

    char* answer = (char*) calloc(3, sizeof(char));
    char* object = (char*) calloc(MAX_OBJECT, sizeof(char));
    char* sign = (char*) calloc(MAX_SIGN, sizeof(char));


    int yes_ans = 0;
    int no_ans = 0;

    if (tree->left != NULL || tree->right != NULL) {
        printf("%s?\n", tree->data);
        scanf("%s", answer);
    }

    if (strcmp(answer, "Yes") == 0) {
        if (tree->left != NULL) {
            operate(tree->left);
        }
        yes_ans = 1;

    }

    if (strcmp(answer, "No") == 0) {
        if (tree->right != NULL) {
            operate(tree->right);
        }
        no_ans = 1;
    }

    if (yes_ans == 0 && no_ans == 0 && (tree->left != NULL || tree->right != NULL)) {
        operate(tree);
    }

    if (tree->left == NULL && tree->right == NULL) {

        printf("The answer is %s?\n", tree->data);
        scanf("%s", answer);

        if (strcmp(answer, "Yes") == 0) {
            printf("Ak1nator has found the answer!\n");
            yes_ans = 1;
        }

        if (strcmp(answer, "No") == 0) {

            printf("Whoa, then who is it you meant?\n");

            scanf("\n%[^\n]", object);
            //printf("%s", object);

            printf("What is the difference from the suggested object?\n");
            scanf("\n%[^\n]", sign);

            appendNode(tree, 1, tree->data);
            appendNode(tree, 0, object);

            tree->data = sign;
            no_ans = 1;
        }

    }

    return;

}

void Delete(struct Node* node) {
    if (node->left) {
        Delete(node->left);
    }

    if (node->right) {
        Delete(node->right);
    }
    free(node);
    node = NULL;
}

void DeleteNode(struct Node* tree, elem_t value) {

    struct Node* node = visitor(tree, value, seek_Node);

    if (node == NULL) {
        return;
    }

    Delete(node);

}
