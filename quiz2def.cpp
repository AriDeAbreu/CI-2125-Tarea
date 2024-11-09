#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un polinomio
typedef struct {
    int grado;
    int *coef;
} Polinomio;

// Función para crear un nuevo polinomio
Polinomio crearPolinomio(int grado) {
    Polinomio p;
    p.grado = grado;
    p.coef = (int *)malloc((grado + 1) * sizeof(int));
    return p;
}

// Función para leer los coeficientes de un polinomio
void leerPolinomio(Polinomio *p) {
    printf("Introduce los coeficientes del polinomio de grado %d:\n", p->grado);
    for (int i = 0; i <= p->grado; i++) {
        printf("Coeficiente de x^%d: ", i);
        scanf("%d", &(p->coef[i]));
    }
}

// Función para imprimir un polinomio
void imprimirPolinomio(Polinomio p) {
    for (int i = p.grado; i >= 0; i--) {
        printf("%d", p.coef[i]);
        if (i > 0)
            printf("x^%d + ", i);
    }
    printf("\n");
}

// Función para sumar dos polinomios
Polinomio sumarPolinomios(Polinomio p1, Polinomio p2) {
    int maxGrado = p1.grado > p2.grado ? p1.grado : p2.grado;
    Polinomio suma = crearPolinomio(maxGrado);

    for (int i = 0; i <= maxGrado; i++) {
        int coef1 = (i <= p1.grado) ? p1.coef[i] : 0;
        int coef2 = (i <= p2.grado) ? p2.coef[i] : 0;
        suma.coef[i] = coef1 + coef2;
    }
    return suma;
}

int main() {
    int n, maxGrado;

    printf("Introduce el numero de polinomios a sumar: ");
    scanf("%d", &n);

    printf("Introduce el mayor grado que puedan tener los polinomios: ");
    scanf("%d", &maxGrado);

    Polinomio *polinomios = (Polinomio *)malloc(n * sizeof(Polinomio));

    for (int i = 0; i < n; i++) {
        int grado;
        do {
            printf("Introduce el grado del polinomio %d (maximo %d): ", i + 1, maxGrado);
            scanf("%d", &grado);
            if (grado > maxGrado) {
                printf("El grado introducido supera el maximo permitido (%d). Intentalo de nuevo.\n", maxGrado);
            }
        } while (grado > maxGrado);
        polinomios[i] = crearPolinomio(grado);
        leerPolinomio(&polinomios[i]);
    }

    Polinomio resultado = polinomios[0];
    for (int i = 1; i < n; i++) {
        resultado = sumarPolinomios(resultado, polinomios[i]);
    }

    printf("La suma de los polinomios es: ");
    imprimirPolinomio(resultado);

   
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)calloc(maxGrado + 1, sizeof(int));
        for (int j = 0; j <= polinomios[i].grado; j++) {
            matriz[i][j] = polinomios[i].coef[j];
        }
    }

    
    printf("Matriz de coeficientes:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= maxGrado; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < n; i++) {
        free(polinomios[i].coef);
        free(matriz[i]);
    }
    free(polinomios);
    free(matriz);
    free(resultado.coef);

    system("pause");

    return 0;
}
