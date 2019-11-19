#include <stdio.h>
#include <stdlib.h>
#include "Onegin.h"
#include "akinator_hed.h"

#define MAX_OBJECT 100
#define MAX_SIGN 100
#define BEG_VAL "Computer Game"


int main (int argc, char** argv) {

    if (argc < 4) {
        return -1;
    }

    struct input data = acquire_input(argv);

    char* buffer = create_buffer(data.name_in);

    int size = count_file(data.name_in);

    int str_size = count_str(buffer, size);

    struct string* strings = calloc(str_size, sizeof(struct string));

    get_str(buffer, strings);


    struct Node* mytree = (struct Node*) calloc(1, sizeof(struct Node*));
    mytree ->left = (struct Node*) calloc(1, sizeof(struct Node*));
    mytree ->right = (struct Node*) calloc(1, sizeof(struct Node*));


    createNodes(strings, mytree, str_size);

    mytree->data = BEG_VAL;

    operate(mytree);

    create_dot(mytree, "dot_out.dot");

    FILE* outfile = fopen(data.name_out, data.type_out);

    TreeDecrypter(mytree, outfile);

    Delete(mytree);

    fclose(outfile);

    return 0;
}