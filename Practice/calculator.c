#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 5

// Estructura para la pila
typedef struct
{
    int top;
    float items[MAX_SIZE];
} Stack;

// Inicializa la pila con ceros
void initStack(Stack *s)
{
    s->top = -1;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        s->items[i] = 0.0f;
    }
}

// Verifica si la pila está vacía
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// Verifica si la pila está llena
int isFull(Stack *s)
{
    return s->top == MAX_SIZE - 1;
}

// Añade un número a la pila
void push(Stack *s, float num)
{
    if (isFull(s))
    {
        // Desplazar los elementos hacia abajo
        for (int i = 0; i < MAX_SIZE - 1; i++)
        {
            s->items[i] = s->items[i + 1];
        }
        s->items[MAX_SIZE - 1] = num; // Añadir el nuevo número al final
    }
    else
    {
        s->items[++(s->top)] = num;
    }
}

// Elimina el último número de la pila
void pop(Stack *s)
{
    if (!isEmpty(s))
    {
        s->top--;
    }
    else
    {
        printf("La pila está vacía, no hay nada que eliminar.\n");
    }
}

// Limpiar pila
void clear(Stack *s)
{
    s->top = -1;
}

// Imprimir pila en orden inverso
void printStack(Stack *s)
{
    printf("");
    printf("Sus números:\n");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%0.2f\n", s->items[i]);
    }
}

// Submenú de operaciones
void mathMenu()
{
    printf("\nOperaciones Matemáticas:\n");
    printf("1. Suma (+)\n");
    printf("2. Resta (-)\n");
    printf("3. Multiplicación (*)\n");
    printf("4. División (/)\n");
    printf("5. Seno (sin)\n");
    printf("6. Coseno (cos)\n");
    printf("7. Tangente (tan)\n");
    printf("8. Raíz cuadrada (sqrt)\n");
    printf("9. Potencia (^)\n");
    printf("10. Módulo (%%)\n");
    printf("Seleccione una operación: ");
}

void performOperation(Stack *s, int operation)
{
    if (s->top < 1)
    {
        printf("\nNo hay suficientes números en la pila para realizar la operación.\n");
        return;
    }

    // Los dos últimos números ingresados en la pila
    float b = s->items[s->top];
    float a = s->items[s->top - 1];
    float result = 0.0f;

    switch (operation)
    {
    case 1:
        result = a + b;
        break;
    case 2:
        result = a - b;
        break;
    case 3:
        result = a * b;
        break;
    case 4:
        if (b != 0)
        {
            result = a / b;
        }
        else
        {
            printf("\nError: División por cero.\n");
            return;
        }
        break;
    case 5:
        result = sin(a);
        break;
    case 6:
        result = cos(a);
        break;
    case 7:
        if (fmod(a, 3.14159265358979323846) == 3.14159265358979323846 / 2 || fmod(a, 3.14159265358979323846) == -3.14159265358979323846 / 2)
        {
            printf("\nError: La tangente de 90 grados (o múltiplos) tiende al infinito.\n");
            return;
        }
        result = tan(a);
        break;
    case 8:
        if (a < 0)
        {
            printf("\nError: No se puede calcular la raíz cuadrada de un número negativo.\n");
            return;
        }
        result = sqrt(a);
        break;
    case 9:
        result = 1;
        for (int i = 0; i < (int)b; i++)
            result *= a;
        break;
    case 10:
        if ((int)b != 0)
        {
            result = (int)a % (int)b;
        }
        else
        {
            printf("\nError: División por cero.\n");
            return;
        }
        break;
    default:
        printf("\nOperación no válida.\n");
        return;
    }

    // Almacena el resultado en la posición del penúltimo número y elimina el último
    s->items[s->top - 1] = result;
    pop(s); // Elimina el último número usado en la operación
}

// Menú principal
void menu()
{
    printf("\nMenú:\n");
    printf("1. Añadir un número\n");
    printf("2. Limpiar el último número ingresado\n");
    printf("3. Limpiar todos los números\n");
    printf("4. Realizar una operación matemática\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

int main()
{
    Stack stack;
    int option, operation;
    float num;

    initStack(&stack);

    do
    {
        menu();
        if (scanf("%d", &option) != 1)
        {
            printf("Entrada inválida. Intente nuevamente.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (option)
        {
        case 1:
            printf("Ingrese un número: ");
            scanf("%f", &num);
            push(&stack, num);
            break;
        case 2:
            pop(&stack);
            break;
        case 3:
            clear(&stack);
            break;
        case 4:
            mathMenu();
            scanf("%d", &operation);
            performOperation(&stack, operation);
            break;
        case 5:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opción no válida, intente nuevamente.\n");
        }

        printf("");
        printStack(&stack);

    } while (option != 5);

    return 0;
}
