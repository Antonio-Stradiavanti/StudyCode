#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#define size 50

/* 
Спецификация

Написать программу, реализующую в виде отдельных функций языка Си следующий набор операций над элементами массива структур.

1. --Ввод элементов массива структур (одного или нескольких).--
2. --Вывод одного элемента массива структур или диапазона элементов.--
3. Установка/получение (две разные функции) значений полей элемента массива структур по заданному индексу в массиве.
4. Поиск элемента массива структур, в котором значение выбранного поля совпадает со значением поля, введенным пользователем.
5. Обмен значений соответствующих полей двух заданных элементов массива структур.
6. Упорядочение элементов массива структур по возрастанию/убыванию значений заданного поля (по желанию).

Программа должна работать в консольном режиме и выдавать информацию о дисциплине, группе, авторе, преподавателе («титульный лист»), затем предлагать нумерованное меню, включающее список перечисленных операций, и при выборе номера пункта меню переходить к соответствующей операции. Следует предусмотреть возможность многократного выполнения операций, т.е. после выполнения операции программа должна ожидать нажатия клавиши и повторно выдавать главное меню. В меню должен быть предусмотрен пункт «выход» из программы.

Домашнее животное	
    Тип (перечисляемый), кличка (массив char), количество наград (unsigned)
    Сортировка по возрастанию.	
*/

static int i, j;

typedef struct pet
{
	enum pet_types { mammal = 1, reptile = 2, bird = 3, fish = 4 } pet_type;
	char nick[size];
	unsigned rewards;
} pets;

unsigned chose_pet_type()
{
	int flag = 0;
	unsigned container;
	printf("\nEnter your pet new type: 1 - mammal, 2 - reptile, 3 - bird, 4 - fish: ");
	scanf("%d", &flag);
		switch (flag)
		{
		case 1:
			container = mammal;
			break;
		case 2:
			container = reptile;
			break;
		case 3:
			container = bird;
			break;
		case 4:
			container = fish;
			break;
		default:
			printf("\nThis type of pet does not exist !!!\n");
			break;
		}
	return container;
}

void struct_gen(struct pet *structus, int n)
{
    int flag = 0; 
	label:
	for (i = 0; i < n; i++)
	{

		structus[i].pet_type = chose_pet_type();

		printf("Enter your pet {%d} nickname: ", i+1); 
		scanf("%s", &structus[i].nick);

		printf("Enter the number of rewards for your {%d} pet: ", i+1);
		scanf("%u", &structus[i].rewards);
	}
}

void struct_print(struct pet *structus, int n)
{
	for (i = 0; i < n; i++)
	{
		printf("\n"); printf("Your number pet {%d} type is %u", i + 1, structus[i].pet_type);
		printf("\n"); printf("Nickname {%d} is: %s", i + 1, structus[i].nick);
		printf("\n"); printf("Number of rewards is: %u\n", structus[i].rewards);
	}
}

void struct_get(struct pet *structus, int index, int count)
{
	switch(count)
	{
		case 1:
			printf("\nYour number pet type is %u\n", structus[index].pet_type);
			break;
		case 2:
			printf("\nYour number pet type is %u\n", structus[index].pet_type);
			printf("Nickname is: %s\n", structus[index].nick);
			break;
		default:
			printf("\nYour number pet type is %u\n", structus[index].pet_type);
			printf("Nickname is: %s\n", structus[index].nick);
			printf("Number of rewards is: %u\n", structus[index].rewards);
			break;
	}
}

void struct_edit(struct pet *structus, int index, int flag2)
{

	pets stick;
	printf("\nEnter new values: ");

	// ввод и вывод новых значений.
	
	switch (flag2)
	{
		case 1:

			stick.pet_type = chose_pet_type();

			printf("\nYour new number pet {%d} type is %u\n", index, stick.pet_type);
			structus[index].pet_type = stick.pet_type;
			
			break;
		case 2:

			stick.pet_type = chose_pet_type();
	
			printf("Enter new nick: "); scanf("%s", stick.nick);

			printf("\nYour new number pet {%d} type is %u\n", index, stick.pet_type);
			printf("New nickname {%d} is: %s\n", index, stick.nick);

			structus[index].pet_type = stick.pet_type;
			strcpy(structus[index].nick, stick.nick);
			
			break;
		default:
			
			stick.pet_type = chose_pet_type();;

			printf("Enter new nick: "); scanf("%s", stick.nick);
			printf("Enter new n of rewards: "); scanf("%u", &stick.rewards);

			printf("\nYour new number pet {%d} type is %u\n", index, stick.pet_type);
			printf("New nickname {%d} is: %s\n", index, stick.nick);
			printf("New number of rewards is: %u\n", stick.rewards);
	
			structus[index].pet_type = stick.pet_type;
			strcpy(structus[index].nick, stick.nick);
			structus[index].rewards = stick.rewards;
			
			break;
	}

}

void struct_search(struct pet *structus, int structus_size)
{
	int flag4 = 0, finder_count;
	unsigned temp_type, temp_r; char temp_nick[size];
	printf("\nwhich value of which field do you want to find? 1 - pet_type, 2 - nick, 3 - reward: "); scanf("%d", &flag4);
	switch (flag4)
	{
		case 1: 
			finder_count = 0;
			printf("Enter the desired unsigned value, 1 - mammal, 2 - reptile, 3 - bird, 4 - fish: "); scanf("%u", &temp_type);
			for (i = 0; i < structus_size; i++)
			{
				if (structus[i].pet_type == temp_type)
				{ 
					finder_count += 1;
					printf("Match in %d structure\n", i);
				}
			}
			if (finder_count > 0)
			{
				printf("Total found: %d\n", finder_count);
			}
			else
			{
				printf("No matches :(");
			}
			break;
		case 2:
			finder_count = 0;
			printf("Enter the desired char value: "); scanf("%s", &temp_nick);	
			for (i = 0; i < structus_size; i++)
			{
				if (strcmp(structus[i].nick, temp_nick) == 0 )
				{ 
					finder_count += 1;
					printf("Match in %d structure!\n", i);
				}
			}
			if (finder_count > 0)
			{
				printf("Total found: %d\n", finder_count);
			}
			else
			{
				printf("No matches :(");
			}
			break;
		default:
			finder_count = 0;
			printf("Enter the desired unsigned value: "); scanf("%u", &temp_r);	
			for (i = 0; i < structus_size; i++)
			{
				if (structus[i].rewards == temp_r)
				{ 
					finder_count += 1;
					printf("Match in %d structure\n", i);
				}
			}
			if (finder_count > 0)
			{
				printf("Total found: %d\n", finder_count);
			}
			else
			{
				printf("No matches :(");
			}
			break;

	}
}

void struct_swap(struct pet *structus)
{
	unsigned holder1 = 0, holder3 = 0; char holder2[size];
	int first_ind = 0, second_ind = 0, mode = 0;
	printf("Enter the code of the fields you want to swap, 1 - pet_type, 2 - nick, 3 - rewards: "); scanf("%d", &mode);
				printf("\nEnter first and second index:\n"); scanf("%d\n%d", &first_ind, &second_ind);
	switch (mode)
	{
	case 1:  
		holder1 = structus[second_ind].pet_type;
		structus[second_ind].pet_type = structus[first_ind].pet_type;
		structus[first_ind].pet_type = holder1;
	case 2:
		strcpy(holder2, structus[second_ind].nick); // скопировал строку, чтобы не потерять
		strcpy(structus[second_ind].nick, structus[first_ind].nick);
		strcpy(structus[first_ind].nick, holder2);
	default:
		holder3 = structus[second_ind].rewards;
		structus[second_ind].rewards = structus[first_ind].rewards;
		structus[first_ind].rewards = holder3;
		break;
	}
}

void struct_sort_by_rewards(struct pet *structus, int structus_size)
{
	// selection sort алгоритм
	pets temp;
	for (i = 0; i < structus_size-1; i++)
	{
		for (j = i + 1; j < structus_size; j++)
		{
			if(structus[i].rewards > structus[j].rewards)
			{
				temp.rewards = structus[i].rewards; temp.pet_type = structus[i].pet_type; strcpy(temp.nick, structus[i].nick);

				structus[i].rewards = structus[j].rewards; structus[i].pet_type = structus[j].pet_type; strcpy(structus[i].nick, structus[j].nick);

				structus[j].rewards = temp.rewards; structus[j].pet_type = temp.pet_type; strcpy(structus[j].nick, temp.nick); 
			}
		}
	}
	struct_print(structus, structus_size);
}

void main()
{
	int n = 0, flag = 0; 
	int index, flag2, mode = 0;

	// создаю массив структур
	printf("Enter the number of your pets: "); scanf("%d", &n);
	pets *my_pets = (struct pet *)malloc(n * sizeof(pets));
	
    do
    {
        printf("\n1. Struct array generation\n");
        printf("2. Outputing some elements of an array\n");
        printf("3. Setting/getting/changing field values\n");
        printf("4. Find values\n");
		printf("5. Swap values\n");
        printf("6. Sort Asc\n");
        printf("7. Info\n");
        printf("8. Exit\n");

        printf("\nSelect one of the menu items: ");
        scanf("%d", &flag);

        switch(flag)
        {
            case 1:
                // вызов ф-ции генерации структуры
                struct_gen(my_pets, n);
                break;
            case 2:
                // вызов ф-ции вывода структуры
                struct_print(my_pets, n);
                break;
            case 3:
				
                // вызов ф-ции изменения значения поля
				printf("\nTell me what you want to do: 1 - edit, 2 - get, 0 - exit: "); scanf("%d", &mode);
				switch (mode) 
				{
					case 1:
						printf("Enter the index: "); scanf("%d", &index);
						printf("Enter the number of fields whose values you want to edit or get: "); scanf("%d", &flag2);
						struct_edit(my_pets, index, flag2);
						break;
					case 2:
						printf("Enter the index: "); scanf("%d", &index);
						printf("Enter the number of fields whose values you want to edit or get: "); scanf("%d", &flag2);
						struct_edit(my_pets, index, flag2);
						struct_get(my_pets, index, flag2);
						break;
					default:
						printf("Goodbye ))\n");
						break;
				}
				mode = 0;
				break;
            case 4:
                struct_search(my_pets, n);
                break;
            case 5:
                // Обмен значений соответствующих полей двух заданных элементов массива структур.
				struct_swap(my_pets);
                break;
			case 6:
				// Сортировка
				struct_sort_by_rewards(my_pets, n);
				break;
            case 7: 
                // Вывод информации о создателе программы
                printf("\nUniversity: Lipetsk State Technical University\nDepartment: Automated control systems\nStudent: Manannikov Anton\nCroup: Software Engineering, SE-22-2\nLeader, professor: Vedishev Vitaly Viktorovich\n");
                break;
            default:
                printf("Goodbye :)");
                break;
        }

    } while (flag != 8); 
    free(my_pets);
	//getchar();

}