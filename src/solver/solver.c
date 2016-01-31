#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

struct expr_unit {
    int sign;          /* Sign of the coeficient (-)7/9x^1 */
    long nom;           /* Nominator of the coeficient fraction +(5)/7x^0 */
    long denom;         /* Denominator of the coeficient fraction -2/(3)x^2 */
    char unknown;      /* The unknown character e.g. X, Y or Z +2/3(x)^2*/
    int unknown_pow;   /* Power of the unknown -4/5x^(2) */
};

#define ALLOWED_CHARS "=+-*/^xyz0123456789"
#define INFNAME "input.txt"
#define OUTFNAME "output.txt"

struct expr_unit sideA[500], sideB[500];

/*
    @e: -24x^2, +0, -0*x^1, +13
    @res: structure expr_unit    
*/
struct expr_unit ExprParser( const char *e ) {
    struct expr_unit res;
    const char *pe = &e[0];
    long num;
    int flag;
    
    /*
    printf("\n[Processing: '%s']\n", e);
    assert( '-' == *pe || '+' == *pe);
    */    
    if ( '-' == *pe ) {
        res.sign = -1;
        pe++;
    } else if ( '+' == *pe ) {
        res.sign = 1;
        pe++;
    } else { 
        /* No sign treat as PLUS (+) but do not advance the expression pointer */
        res.sign = 1;
    }
    
    /* printf("\n[%c]\n", *pe); */
    num  = 0;
    flag = 1;
    while ( *pe >= '0' && *pe <= '9' ) {
        /*
        printf("\n>[%d = %d *10 + (%d - %d)]\n", num, num, *pe, '0');
        printf("\n>>[%d = %d *10 + (%d)]\n", num, num, *pe - '0');
        */
        num = num * 10 + (*pe - '0');
        pe++;
        flag = 0;
    }
    res.nom = ( 0 == num && flag ) ? (1) : (num);
    
    res.denom = 1;
    if ( '/' == *pe ) {
        pe++;
        num  = 0;
        while ( *pe >= '0' && *pe <= '9' ) {
            num = num * 10 + (*(pe++) - '0');
        }
        res.denom = num;
    }
    
    /* There could be STAR sign used for multiplication */
    if ( '*' == *pe ) {
        pe++;
    }
   
    res.unknown_pow = 0;
    res.unknown = 'x';
    /* Chaeck if there is an unknown in the expression */
    if ( 'x' == *pe || 'y' == *pe || 'z' == *pe ) {
        res.unknown = *pe;
        /* In case there is no ^ sign after the unknown */
        res.unknown_pow = 1;
        pe++;
    }
    
    /* printf("\n[%d]\n", *pe); */
    if ( '^' == *pe ) {
        pe++;
        assert( *pe >= '0' && *pe <= '2' );
        res.unknown_pow = (*pe - '0');
    } 
    /*
    printf("\n[Processed res.sign='%c' res.nom=%d res.denom=%d res.unknown='%c' res.unknown_pow=%d]\n", 
        ((-1 == res.sign)?('-'):('+')), res.nom, res.denom, res.unknown, res.unknown_pow);    
    */
    return res;
}

void PrintExpr( const struct expr_unit e ) {
    printf(" ");
    if ( 1 == abs(e.nom * e.denom) && abs(e.nom) == abs(e.denom) && e.unknown_pow > 0) {
        printf("%c", (e.sign < 0)?'-':'+');
    } else {
        printf("%c%ld", (e.sign < 0)?'-':'+', e.nom);
    }
    if ( e.denom > 1 ) {
        printf("/%ld", e.denom); 
    }
    switch ( e.unknown_pow ) {
        case 0:
            break;
        case 1:
            printf("%c", e.unknown);
            break;
        case 2:
            printf("%c^%d", e.unknown, e.unknown_pow);
            break;
        default:
            printf("\nPOWER HIGHER THAN 2 IS NOT ALLOWED\n");
            exit(-1);
    }
}

/*
    x^2 +14x^1 -22 = 2x+   22
*/
void ReadInputFile(const char fname[]) {
    FILE *inf = fopen(fname, "r");
    char ch, *p; 
    char expr[20] = "";
    struct expr_unit etmp;
    
    if ( !inf ) {
        printf("Unable to read from file: %s\n", fname);
        exit(-1);
    }
    /* Initially set the poiner */
    p = &expr[0];
    while ( ch = fgetc(inf), ch != EOF ) {   
        switch ( (int) ch ) {
            /* 
            32 => SPACE 
            13 => CARRIAGE RETURN (ONLY WINDOWS)
            */
            case 32:
            case 13:
                continue; 
                break;
            /*
            10 => NEW LINE
            43 => PLUS SIGN (+)
            45 => MINUS SIGN (-)
            61 => EQUAL SIGN (=)            
            */                
            case 10:
            case 43:
            case 45:
            case 61:
                if ( 61 == expr[0] ) {
                    printf(" =");
                    p = &expr[0];
                }
                /* Terminate the expr_unit word with end-of-word charecter */
                *p = '\0';
                /* Print only if the expr variable contains something meaningful */
                if ( 43 == expr[0] || 45 == expr[0] ) {
                    etmp = ExprParser(expr);
                    PrintExpr(etmp);
                }
                /* Restart the pointer */
                p = &expr[0];
                if ( 10 == ch ) {
                    printf("\n");
                    /* Reset both side arrays */
                    continue;
                }
                break;
            /* EVERYHTING ELESE */
            default:
                ;;
        }       
        /* We do not allow foreign characters to the approved expressions */
        if ( strchr(ALLOWED_CHARS, ch) ) {
            *(p++) = ch;
        }
        else {
            printf("\nILLEGAL CHARACTER ASCII(%d)\n", ch);
            exit(-1);
        }
    }
    
    fclose(inf);
}

/*************
 * M A I N
 *************/

int main(const int argc, const char **argv) {
    char fname[20] = INFNAME;
    if (argc == 2 && strlen(argv[1]) > 0) strcpy(fname, argv[1]);
    printf("Reading from: %s\n", fname);
    /* printf("%d\n", (long)strchr(fname, '.') - (long)&fname); */
    ReadInputFile(fname);

    return 0;
}
