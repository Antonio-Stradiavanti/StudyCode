#include <stdio.h>

// 1

void main() 
{
    float x = 0.0, y = 0.0, z = 0.0; 
    // рповерка на уникальность введенных значений
    label1:
        printf("Enter unique values for x, y and z:\n"); 
        scanf("%f %f %f", &x, &y, &z);
        printf("\nYour input is: x = %f, y = %f, z = %f\n", x, y, z);

        if ((x != y) && (y != z) && (x != z))
        {
            goto label2;
        }
        else
        {
            goto label1;
        }
    label2:
        if ((x + y + z) < 1)
        {
            if ((x > y) && (x > z))
            {
                x = (x+y)/2;
            }
            else if ((y > x) && (y > z))
            {
                y = (x+z)/2;
            }
            else
            {
                z = (y+x)/2;
            }
        }
        else
        {
            if (y < z)
            {
                y = (z+x);
            }
            else
            {
                z = (y+x);
            }
        }
    printf("New values: x = %f, y = %f, z = %f", x, y, z);

}