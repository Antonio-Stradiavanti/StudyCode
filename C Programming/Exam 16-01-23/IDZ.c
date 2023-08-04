#include<stdio.h>
#include<math.h>

void main() {

    float i = 0.0, j = 0.0;
	float a, b, c, x, x_min, x_max, d, e;

    printf("Enter some values, coefficient: a, b, c; x min and x max; step, epsilon:\n");
	scanf("%f %f %f %f %f %f %f", &a, &b, &c,&x_min,&x_max,&d,&e);

	for ( i = x_min; i <= x_max; i += d ) 
    {
		for ( j = x_min; j <= x_max; j += d ) 
        {
			if (fabs((j*i)-(c/a))<=e && fabs((i+j)+( b / a))<=e && i!=0 && j!=0) 
            {
				printf("x_min = %f, x_max= %f\n", i, j);
			}
		}
	}
}
