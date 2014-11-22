#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define STAR_MULT_ALLOW (1)
#define FRAC_ALLOW      (1)
#define MAX_FRAC_DENOM  (10)
#define MAX_POW         (1 + 1)
#define MIN_SIDE_EXPR   (2)
#define MAX_SIDE_EXPR   (10 + 1)
#define MAX_NUMBER      (20 + 1)
#define MAX_SPACE       (0 + 1)
#define MIN_ROWS        (5)
#define MAX_ROWS        (10 + 1)

int main(const int argc, const char *argv[]) {
    FILE *fp = fopen("input_auto.txt", "w");
    int i, j, p;
    char space[4][MAX_SPACE];
    char denom[10] = "";
    const char sign[2] = "+-";
    int rows;
    int side_flag;
    
    /* Make sure non of the parameters are zero */
    assert(MAX_POW > 0);
    assert(MAX_SIDE_EXPR > 0);
    assert(MIN_SIDE_EXPR > 0);
    assert(MAX_SIDE_EXPR > MIN_SIDE_EXPR);
    assert(MAX_NUMBER > 0);
    assert(MAX_SPACE > 0);
    assert(MAX_ROWS > 0);
    assert(MIN_ROWS > 0);
    assert(MIN_ROWS < MAX_ROWS);
    
    srand( (unsigned int) time(NULL) );
    
    rows = MIN_ROWS + rand() % (MAX_ROWS - MIN_ROWS);
    while (rows--) {
        side_flag = 2;
        while (side_flag--) {
            for (i = 0; i < MIN_SIDE_EXPR + rand() % (MAX_SIDE_EXPR - MIN_SIDE_EXPR); i++) {
                /* Generate space variables */
                for (j = 0; j < 4; j++) {
                    strcpy(space[j], "");
                    for (p = 0; p < rand() % MAX_SPACE; p++) strcat(space[j], " ");
                }
                strcpy(denom, "");
                /* Randomly decide if you are going to have a denominator generated*/
                if ( (rand() % MAX_NUMBER) < (rand() % MAX_NUMBER) && FRAC_ALLOW ) {
                    sprintf( denom, "%s/%d", space[rand() % 4], 1 + (rand() % MAX_FRAC_DENOM) );
                }
                
                /* Nasty random bug does not allow then next fprintf() so we do not use this fprintf() now
                fprintf(fp, space[0]);
                */
                fprintf(fp, "%c", sign[rand() % 2]); 
                fprintf(fp, space[1]);
                fprintf(fp, "%d", (rand() % MAX_NUMBER) ); 
                fprintf(fp, denom);
                fprintf(fp, space[2]);
                if ( (rand() % MAX_NUMBER) < (rand() % MAX_NUMBER) ) {
                    if ( STAR_MULT_ALLOW ) fprintf(fp, "*");
                    if ( (rand() % MAX_NUMBER) > (rand() % MAX_NUMBER) ) fprintf(fp, "x");
                    else fprintf(fp, "x^%d", rand() % MAX_POW);
                } 
                fprintf(fp, space[3]);
            }
            if (side_flag) fprintf(fp, "=");
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    
    return 0;
}
