#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define MAX_EQ_SIDE 500
#define EPS 0.000001
#define MAX_DIFFICULTY_LEVEL 10
/* Change the level of difficulty here */
#define DIFFICULTY_LEVEL 10 /* FROM 1 UP TO 10 */
#define MIN_EQ_LEN DIFFICULTY_LEVEL * 2 + 10 - DIFFICULTY_LEVEL
/* Simple fraction
#define MIN_EQ_LEN DIFFICULTY_LEVEL * 2 + 10 - DIFFICULTY_LEVEL
*/

/* The STEP is calculated automatically */
#define DIFFICULTY_STEP (MAX_DIFFICULTY_LEVEL / 5)

#define INFNAME "input.txt"
#define OUTFNAME "output.txt"

struct eq_unit {
    int sign;          /* Sign of the coeficient (-)7/9x^1 */
    int nom;          /* Nominator of the coeficient fraction +(5)/7x^0 */
    int denom;        /* Denominator of the coeficient fraction -2/(3)x^2 */
    char unknown;      /* The unknown character e.g. X, Y or Z +2/3(x)^2*/
    int unknown_pow;   /* Power of the unknown -4/5x^(2) */
};

struct frac {
    int nom;
    int denom;
};

struct eq_unit sideA[MAX_EQ_SIDE], sideB[MAX_EQ_SIDE];

/* Standard C Function: Greatest Common Divisor */
int gcd( int a, int b )
{
    int c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

struct eq_unit* FindQuadraticABC1(double *x1, double *x2) {
    struct frac coef[3];
    double D;
    static struct eq_unit ans[MAX_EQ_SIDE];
    unsigned long i, j;

    for ( i = 0;; ) {
        for (j = 0; j < 3; j++) {
            coef[j].nom = 1 + (rand() % (DIFFICULTY_LEVEL * 10));
            coef[j].denom = 1 + (rand() % (DIFFICULTY_LEVEL * 10));
            if (DIFFICULTY_LEVEL >= 5) {
                coef[j].nom *= 1 + (rand() % 10);
                coef[j].denom *= 1 + (rand() % 10);
            }
            coef[j].denom = (rand() % 10 > 5) ? 1 : coef[j].denom;
            coef[j].nom *= (rand() % 10 > 5) ? (-1) : (1);
        }
        D = (coef[1].nom * coef[1].nom)/(double)(coef[1].denom * coef[1].denom) -
            ( 4.0 * (coef[0].nom * coef[2].nom)/(double)(coef[0].denom * coef[2].denom) );
        /*
        printf("DEBUG: %ld\n", i);
        printf("DEBUG: A=%d/%d\tB=%d/%d\tC=%d/%d\n", coef[0].nom, coef[0].denom,
        	coef[1].nom, coef[1].denom, coef[2].nom, coef[2].denom);
        */
        i++;
        if ( D < 0.0 ) continue;

        *x1 = ( -(coef[1].nom/(double)coef[1].denom) + sqrt(D) ) / (2.0 * coef[0].nom / (double)coef[0].denom);
        *x2 = ( -(coef[1].nom/(double)coef[1].denom) - sqrt(D) ) / (2.0 * coef[0].nom / (double)coef[0].denom);

        if ( fabs( fabs( *x1 * 100.0 ) - fabs( floor(*x1 * 100.0) ) )  < EPS &&
                fabs( fabs( *x2 * 100.0 ) - fabs( floor(*x2 * 100.0) ) ) < EPS )
        {
            /*
            printf("DEBUG: A=%d/%d\tB=%d/%d\tC=%d/%d\n", coef[0].nom, coef[0].denom,
            coef[1].nom, coef[1].denom, coef[2].nom, coef[2].denom);
            */
            for (j = 0; j < 3; j++) {
                ans[j].sign = (coef[j].nom < 0) ? (-1) : (1);
                ans[j].nom = abs( coef[j].nom / gcd(coef[j].nom, coef[j].denom) );
                ans[j].denom = abs( coef[j].denom / gcd(coef[j].nom, coef[j].denom) );
                ans[j].unknown = 'x';
                ans[j].unknown_pow = 2 - j;
            }
            break;
        }
    }
    return ans;
}

/*
	This function uses Vieta's formulas in order to generate the quadratic equation.
	It takes X1 and X2 solution roots and generates the quadratic equation itself.
*/
char* FindQuadraticABC2(const double x1, const double x2) {
    static char res[500] = "";
    double a, b, c, red;

    a = 1.0;
    b = -(x1 + x2);
    c = x1*x2;

    while ( ( a - floor(a) ) >= EPS || ( b - floor(b) ) >= EPS ||
            ( c - floor(c) ) >= EPS )
    {
        a *= 10.0;
        b *= 10.0;
        c *= 10.0;
    }
    red = 10.0;
    while ( red > 0.0 ) {
        /* printf("%f (%f - %f)\n", red, a, red*floor(a/red)); */
        if ( fabs( a - red * floor(a / red) ) < EPS &&
                fabs( b - red * floor(b / red) ) < EPS &&
                fabs( c - red * floor(c / red) ) < EPS ) {

            a /= red;
            b /= red;
            c /= red;
        }
        red -= 1.0;
    }
    sprintf(res, "%+.0fx^2%+.0fx%+.0f=0", a, b, c);

    /*printf("DEBUG: %s\n", res);*/
    return res;
}

double GenRandomRoot(void) {
    double x;

    x = (double) ( rand() % (5 + rand() % MAX_DIFFICULTY_LEVEL) );
    x += (double) (rand() % DIFFICULTY_LEVEL) * 0.05;
    x += (rand() % 2) ? 0.05 : 0.0;
    /* x += (DIFFICULTY_LEVEL > MAX_DIFFICULTY_LEVEL / 2) ? 0.05 : 0.0; */
    x = (rand() % 2) ? (-x) : (x);

    return x;
}

char* FilterEquation(double *x1, double *x2) {
    static char ans[500] = "";

    do {
        *x1 = GenRandomRoot();
        *x2 = GenRandomRoot();

        /* printf("x1= %+.4f\tx2= %+.4f\n", *x1, *x2); */
        strcpy( ans, FindQuadraticABC2(*x1, *x2) );
        /* printf("%d '%s'\n", strlen(ans), ans); */
    } while ( fabs(*x1 + *x2) - fabs(*x1 - *x2) < EPS ||
              strlen(ans) < 1 || strlen(ans) > MIN_EQ_LEN + (DIFFICULTY_LEVEL / DIFFICULTY_STEP)
            );

    return ans;
}

char* EquationToString(const struct eq_unit eq[], const int mode) {
    static char res[MAX_EQ_SIDE] = "";
    char tmp[20];
    unsigned int i;
    double tmp_f;

    strcpy(res, "");
    for (i = 0; i < 3; i++) {
        strcat(res, (eq[i].sign <  0) ? "-" : "+");
        if ( 1 || mode ) {
            sprintf(tmp, "%d", eq[i].nom);
            strcat( res,  tmp);
            if ( eq[i].denom > 1 ) {
                strcat(res, "/");
                sprintf(tmp, "%d", eq[i].denom);
                strcat( res,  tmp);
            }
        }
        else {
            strcpy(tmp, "$.$$");
            tmp_f = eq[i].nom / (double)eq[i].denom;
            if ( fabs(tmp_f - floor(tmp_f)) < EPS )
                sprintf(tmp, "%0.0f", tmp_f);
            else if ( fabs(tmp_f * 10.0 - floor(tmp_f * 10.0)) < EPS )
                sprintf(tmp, "%0.1f", tmp_f);
            else  /*( fabs(tmp_f * 100.0 - floor(tmp_f * 100.0)) < EPS )*/
                sprintf(tmp, "%0.2f", tmp_f);
            strcat(res, tmp);
        }
        switch ( eq[i].unknown_pow ) {
        case 0:
            break;
        case 1:
            sprintf(tmp, "%c", eq[i].unknown);
            strcat(res, tmp);
            break;
        case 2:
            sprintf(tmp, "%c", eq[i].unknown);
            strcat(res, tmp);
            strcat(res, "^");
            sprintf(tmp, "%d", eq[i].unknown_pow);
            strcat(res, tmp);
            break;
        default:
            printf("Power grater than 2 not implemented!\n");
            exit(-1);
        }
    }
    return res;
}

/***************
 **  M A I N  **
 ***************/

int main(const int argc, const char *argv[]) {
    char fname[50] = "Random engine";
    char ans[MAX_EQ_SIDE];
    double x1, x2;
    int cnt;

    if (argc == 2 && strlen(argv[1]) > 0) strcpy(fname, argv[1]);
    printf("Using input: %s\n", fname);

    srand( (unsigned) time(NULL) );
    assert( DIFFICULTY_LEVEL > 0 && DIFFICULTY_LEVEL <= MAX_DIFFICULTY_LEVEL );
    /*
    printf("%s => %s\n", "1.00x^2+3.04x+23.20=0", EliminateTrailingZeros("1.00x^2+3.04x+23.20=0"));
    printf("%s => %s\n", "1.00x^2+3.00x+0.00=0", EliminateTrailingZeros("1.00x^2+3.00x+0.00=0"));
    */
    for (cnt = 0; cnt < 10;) {
        /* IF clause looks OK */
        if ( 0 && rand() % 2 == 0 ) strcpy( ans, FilterEquation(&x1, &x2) );
        strcpy( ans, EquationToString(FindQuadraticABC1(&x1, &x2), 0) );
        if ( strlen(ans) < MIN_EQ_LEN ) continue;
        printf( "%s=0\n",  ans);
        printf("x1= %+.2f\tx2= %+.2f\n", x1, x2);
        cnt++;
    }

    return 0;
}
