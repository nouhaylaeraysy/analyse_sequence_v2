#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../lib/constants.h"
#include "translation.h"

int main(int argc, char *argv[]) {
    char *protein;
    char *filePath;
    char *rna_sequence;
    char  message[60];

    sprintf(message, "%sPlease entre a valid RNA sequence : %s", BLU, RESET);

    get_path_from_user(&filePath, message);

    extract_sequence(filePath, &rna_sequence);

    while (valid_rna_sequence(rna_sequence) == 0) {
        printf("\n%sInvalid sequence rna. Please enter a valid rna sequence: %s", RED, RESET);
        get_path_from_user(&filePath, "");
        extract_sequence(filePath, &rna_sequence);
    }

    char file_name_protein[200];
    sprintf(file_name_protein, PROTEIN_SEQUENCE_FILE, timeInMilliseconds());

    removeAllSpaceAndReturnAline(&rna_sequence);

    translateRnaToProtein(rna_sequence, &protein);

    int is_saved = save_sequence(rna_sequence, file_name_protein, MAX_LINE_LENGTH);
    if (is_saved == 1) {
        printf("%sFile is saved in %s %s", GRN, file_name_protein, RESET);
    }

    return 1;
}
