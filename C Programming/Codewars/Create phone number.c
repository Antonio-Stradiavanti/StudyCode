#include <stdio.h>

// ф-ция принимает на вход массив десяти целых чисел и возвращает случайную строчку их них в форме номера телефона 

char *create_phone_number(char phnum[15], const unsigned char nums[10]);

// беззнаковый символьный ➡️ означает что старший бит будет использоваться для записи числа а не для знака +/-, так как для переменной char доступен диапазон значений от -127 до 127, а для переменной unsigned char от 0 до 255 (весь диапазон кодов ascii)

void main()
{

}

char *create_phone_number(char phnum[15], const unsigned char nums[10])
{
    *phnum = '\0';
    return phnum;
}
