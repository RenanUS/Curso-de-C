#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num1, num2;
    char operador;
    int resultado;
    
    while (1)
    {
        printf("Digite o primeiro número: ");
        scanf("%d", &num1);
        printf("Digite o operador (+, -, x, /): ");
        scanf(" %c", &operador);
        printf("Digite o segundo número: ");
        scanf("%d", &num2);

        if (operador == '+' || operador == '-' || operador == 'x' || operador == '/')
            {
                if (operador == '+')
                {
                    resultado = num1 + num2;
                }
                else if (operador == '-')
                {
                    resultado = num1 - num2;
                }
                else if (operador == 'x')
                {
                    resultado = num1 * num2;
                }
                else if (operador == '/')
                {
                    if(num2 == 0)
                    {
                        printf("Divisão por zero não é permitida.\n");
                        continue;
                    }
                    resultado = num1 / num2;
                }
                printf("Resultado: %d\n", resultado);
            }
            else
            {
                printf("Operador inválido.\n");
                continue;
            }
        
        while (1)
        {
            printf("Digite o operador (+, -, x, /, c): ");
            scanf(" %c", &operador);
            if (operador == 'c')
            {
                break;
            }
            else if (operador == '+' || operador == '-' || operador == 'x' || operador == '/')
            {
                printf("Digite o próximo número: ");
                scanf("%d", &num2);
                if (operador == '+')
                {
                    resultado = resultado + num2;
                }
                else if (operador == '-')
                {
                    resultado = resultado - num2;
                }
                else if (operador == 'x')
                {
                    resultado = resultado * num2;
                }
                else if (operador == '/')
                {
                    if(num2 == 0)
                    {
                        printf("Divisão por zero não é permitida.\n");
                        continue;
                    }
                    resultado = resultado / num2;
                }
                printf("Resultado: %d\n", resultado);
            }
            else
            {
                printf("Operador inválido.\n");
            }
        }
        
    }
}