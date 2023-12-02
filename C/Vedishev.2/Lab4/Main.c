#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define KEY_LEN 32
#define FILE_NAME_LEN 1024
typedef struct 
{
    char C;
    char key[KEY_LEN];
    float A[3];
} Data;
typedef struct
{
    int cap; // Максимальное количество элементов в таблице
    int size; // Фактическое количество элементов в ней.
    // указывает что позиция удаленного элемента свободна и на нее можно вставить новый элемент
    Data* vacated;
    Data** table;
} chtb;
// (Сумма всех  кодов символов s, поразрядно сдвинутых влево на четверть своего кода соответственно) % максимальная длина таблицы V
int h(char* key, int cap)
{
    int i, res = 0;
    for (i = 0; i < strlen(key); i++)
        res += key[i] << key[i]/4;
    return (res % cap);
}
int linProbing(char* key, int i, int cap)
{
    return ((h(key, cap) + i) % cap); 
}
// Закрытое хеширование -> хеш таблица - просто массив структур(open addresing)
/* 
    Ф-ции:
    int chtbInit() -> инициализация
    void chtbDestroy() -> уничтожение
    int chtbInsert(, Data* data) -> вставка
    int chtbRemove(, Data* data) -> удаление элемента по 
    адресу
    int chtbLookup(, Data* data) -> поиск элемента по адресу
    match() -> определение совпадения двух ключей
    Комментарии:
    Хеш-таблица - просто массив структур типа Data
    Незанятая позиция имеет значение NULL
*/
int chtbInit(chtb* HT, Data* vac, int cap)
{
    // Возвращает 0 если успех, 1 если неудача
    int i;
    if ((HT->table = (Data**)malloc(cap * sizeof(Data*))) == NULL) 
    {
        printf("[chtbInit] : Error : Can't allocate memory.\n");
        return -1;
    }
    HT->cap = cap;
    // NULL -> флаг пустой ячейки хеш-таблицы
    for (i = 0; i < cap; i++)
        HT->table[i] = NULL;
    // Флаг удаленной записи, указывающий ф-циям что на эту позицию можно добавлять новые записи
    HT->vacated = vac;
    printf("[chtbInit] : Success : The hash table was successfully initialized.\n"); return 0;
}
// V
void chtbDestroy(chtb* HT)
{
    if (HT->table == NULL)
    {
        printf("[chtbDestroy] : Operation canceled : The hash table is empty.\n");
        return;
    }
    for (int i = 0; i < HT->cap; i++)
    {
        if (HT->table[i] != NULL || HT->table[i] != HT->vacated)
        {
			free(HT->table[i]);
        }
    }
    free(HT->table);
    HT->table = NULL;
	HT->vacated = NULL;
    HT->size = 0;
    HT->cap = 0;
    printf("[chtbDestroy] : Success : The hash table was successfully destroyed.\n");
}
// Генерация, вставка, поиск, удаление
/* 
    Если сразу находят искомый элемент, то зондирование не требуется.
	    - Для удаления или поиска таблицу зондируют (прощупывают) пока не наткнутся на искомый элемент или не будет найдена незанятая ячейка. Если найдена незанятая ячейка перед целевым элементом, или если завершен обход всех позиций, то элемента нет в таблице (выводится соответствующее сообщение).
*/
int chtbLookup(chtb* HT, char* key, Data** store)
{   
    // Передаю в ф-цию двойной указатель, так как элементы массива это указатели на адреса младших байтов выделенных под структуры типа Data областей памяти.
    int i, j, cap;
    if (HT->table == NULL)
    {
        printf("[chtbLookup] : Operation canceled : The hash table is empty.\n");
        return -1;
    }
    for (i = 0; i < HT->cap; i++) 
    {
        cap = abs(linProbing(key, i, HT->cap));
        // С помощью хеш-ф-ции смотрим индекс указанного элемента по ключу, если в массиве адрес переданного элемента совпадает с указанным, выводим его, иначе выполняем линейное зондирование.
        if (HT->table[cap] == NULL) return -1;
        else if (strcmp(HT->table[cap]->key, key) == 0) 
        {
            if(store != NULL) *store = HT->table[cap];
            return 0;
        }
    }
    printf("[chtbLookup] : Failure1 : specified data not found.\n");
    return -1;
}
int chtbInsert(chtb* HT, Data* newData)
{
    // Отладить
    if (HT->table == NULL)
    {
        printf("[chtbInsert] : Operation canceled : The hash table is empty.\n");
        return -1;
    }
    if (newData == NULL) 
    {
        printf("[chtbInsert] : Failure : newData is empty.\n"); 
        return 1;   
    }
    if (HT->size == HT->cap) return -1;
    int i, cap = 0;
    for (i = 0; i < HT->cap; i++)
    {
        cap = abs(((h(newData->key, HT->cap) + i) % HT->cap));
        if (HT->table[cap] == NULL || HT->table[cap] == HT->vacated)
        {
            // Получается отрицательное число, не работает для нулевых и конечных позиций.
            HT->table[cap] = (Data*)malloc(sizeof(Data));
            for (int j = 0; j < 3; j++)
				HT->table[cap]->A[j] = newData->A[j]; 
			strcpy(HT->table[cap]->key, newData->key);
			HT->table[cap]->C = newData->C;
            HT->size++;
            printf("[chtbInsert] : Success : entry inserted at the %d position.\n", cap);
            return 0;
        }
    }
    printf("[chtbInsert] : There were some errors. Data not inserted.\n");
    return -1;
}
int chtbRemove(chtb* HT, char* key)
{
    if (HT->table == NULL)
    {
        printf("[chtbRemove] : Operation canceled : The hash table is empty.\n");
        return -1;
    }
    int i, cap;
    Data* tmp;
    if (chtbLookup(HT, key, NULL) == -1) 
    {
        printf("[chtbRemove] : Failure : No data with the specified key was found.\n");
        return -1;
    }
    for (i = 0; i < HT->cap; i++)
    {
        cap = abs((h(key, HT->cap) + i) % HT->cap);
        if (HT->table[cap] == NULL)
        {
            return -1;
        }
        else if (HT->table[cap] == HT->vacated)
        {
            continue;
        }
        else if (strcmp(HT->table[cap]->key, key) == 0)
        {
            tmp = HT->table[cap];
            HT->table[cap] = HT->vacated;
            free(tmp); HT->size--; return 0;
        }
    }
    return -1;
}
// Работает V
void genHashKey(char* key, int len)
{
    char rCh[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
    int i, chL = strlen(rCh);
    for (i = 0; i < len; i++)
    {
        key[i] = rCh[rand() % chL];
    }
    key[i] = 0;
}

int chtbGen(chtb* HT, int N)
{
    if (HT->table == NULL)
    {
        printf("[chtbGen] : Operation canceled : The hash table is empty.\n"); return -1;
    }
    if (N > HT->cap)
    {
        printf("[chtbGen] : Failure : The entered size exceeds the size of the hash table.\n"); return -1;
    }
    if (HT->size != 0)
    {
        printf("[chtbGen] : Failure : The hash table already generated.\n"); return -1;
    }
    int i; float a = 100.0;
    Data* tmp;
    for (i = 0; i < N; i++)
    {
        if ((tmp = (Data*)malloc(sizeof(Data))) == NULL) return -1;
        genHashKey(tmp->key, KEY_LEN);
        tmp->C = rand() % 26 + 65;
        for (int j = 0; j < 3; j++)
            tmp->A[j] = (float)rand()/(float)RAND_MAX * a;
        // Отладить
        if (chtbInsert(HT, tmp) == -1) 
        {
            printf("[chtbGen] : Failure : Unable to insert entry.\n");
            free(tmp);
            return -1;
        }
        free(tmp); 
    }
    printf("[chtbGen] : Success : The hash table was successfully generated and now contains %d elements.\n", HT->size); return 0;
}
// Замена «старого» значения заданного поля записи на заданное новое (поиск по ключу).
int chtbUpdate(chtb* HT, char* key, int n)
{
    Data* tmp; float tmpF;
    char newC;
    if (HT->table == NULL)
    {
        printf("[chtbUpdate] : Operation canceled : The hash table is empty.\n");
        return -1;
    }
    if (chtbLookup(HT, key, &tmp) == -1) 
    {
        printf("[chtbUpdate] : Failure : No entry with the specified key was found.\n");
        return -1;
    }
    if (n == 1)
    {
        printf("[chtbUpdate] : Enter new character : ");
        fflush(stdin); scanf(" %c", &newC);
        tmp->C = newC;
        printf("[chtbUpdate] : Success : The char entry field has been updated.\n");
        return 0;
    }
    else if (n == 2)
    {
        printf("[chtbUpdate] : Fill mini-array.\n");
        for (int j = 0; j < 3; j++)
        {
            printf("> "); fflush(stdin); scanf("%f", &tmpF);
            tmp->A[j] = tmpF; 
        }
        printf("[chtbUpdate] : Success : The float[3] entry field has been updated.\n");
        return 0;
    }
    else
    {
        printf("[chtbUpdate] : Operation canceled : There is no such field.\n");
    }
    return -1;
}
void chtbDisplay(chtb* HT)
{
    int i;
    if (HT->table == NULL)
    {
        printf("[chtbDisplay] : Operation canceled : The hash table is empty.\n"); return;
    }
    for (i = 0; i < HT->cap; i++)
    {
        if (HT->table[i] == NULL || HT->table[i] == HT->vacated)
        {
            printf("HT [%d] : NULL\n", i);
        }
        else
        {
            printf("HT [%d] : [\n\tKey : %s\n\tData :\n\t\tC = %c\n\t\tA = [ %.3f, %.3f, %.3f ]\n]\n", i, HT->table[i]->key, HT->table[i]->C, HT->table[i]->A[0], HT->table[i]->A[1], HT->table[i]->A[2]);
        }
    }
}
void help(){
    printf(
        "*** MENU ***\n"
        "0 - Exit\n"
        "1 - Init hash table\n"
        "2 - Destroy hash table\n"
        "3 - Gen hash table\n"
        "4 - Insert some data from the file\n"
        "5 - Move hash table to the file\n"
        "6 - Insert the entry into the hash table from the keyboard\n"
        "7 - Remove the entry from the hash table\n"
        "8 - Look up for the specified data in the hash table\n"
        "9 - Replacing the old value of a given record field with a given new value (key search)\n"
        "10 - Is hash table empty?\n"
        "11 - Display hash table\n"
        "12 - Help\n"
    );
}
// Работает V
Data* genData()
{
    Data* tmp = (Data*)malloc(sizeof(Data));
    char tmpS[KEY_LEN];
    printf("[genData] : Enter key : ");
    fflush(stdin); 
    scanf("%s", tmpS);
    strcpy(tmp->key, tmpS);
    printf("[genData] : Enter char : ");
    fflush(stdin); scanf(" %c", &tmp->C);
    fflush(stdin); printf("Fill in the mini-array\n");
    scanf(" %f %f %f", &tmp->A[0], &tmp->A[1], &tmp->A[2]);
    return tmp;
}
int WritingToFile(chtb* HT, char* FullFilename)
{
    if (HT->table == NULL || HT->size == 0)
    {
        printf("[WritingToFile] : Operation canceled : The hash table is empty.\n"); return -1;
    }
    FILE* f; int i, elC = 0;
    if ((f = fopen(FullFilename, "wb")) == NULL)
    {
        printf("[WritingToFile] : Failure : Unable to create file.\n"); return -1;
    }
    // Записать количество ненулевых элементов в файл
    for (i = 0; i < HT->cap; i++)
    {
        if (HT->table[i] != NULL) elC++;
    }
    printf("[WritingToFile] : There are %d non-zero entries.\n", elC); 
    if (fwrite(&elC, sizeof(int), 1, f) != 1)
    {
        printf("Can't write size to the file.\n"); return -1;
    }
	for (i = 0; i < HT->cap; i++)
	{
		if (HT->table[i] != NULL)
		{
			if(fwrite(HT->table[i], sizeof(Data), 1, f) != 1)
            {
                printf("[WritingToFile] : Failure : Can't write %d entry to the file.\n", i); return -1;
            }
		}
	}
    if (fclose(f) == EOF) 
    {
        printf("[WritingToFile] : Failure : Error closing bin file.\n") ; return 1;
    }
    printf("[WritingToFile] : Success : The hash table was successfully written to the bin file.\n");
    return 0;
}
int ReadingFromFile(chtb* HT, char* FullFilename)
{
	FILE* f; int i, elC = 0; 
	Data* tmp; if ((tmp = (Data*)malloc(sizeof(Data))) == NULL) return -1;
    if (HT->table == NULL)
    {
        printf("[ReadingFromFile] : Operation canceled : The hash table is empty.\n"); free(tmp) ; return -1;
    }
    if ((f = fopen(FullFilename, "rb")) == NULL)
    {
        printf("[ReadingFromFile] : Failure : The specified file does not exist.\n"); free(tmp) ; return -1;
    }
    if (fread(&elC, sizeof(int), 1, f) != 1)
    {
        printf("[ReadingFromFile] : Failure : Unable to read the number of entries in the file.\n");
        free(tmp); return 1;
    }
    printf("[ReadingFromFile] : Number of entries : %d.\n", elC);
    if (elC > (HT->cap - HT->size))
    {
        printf("[ReadingFromFile] : Operation canceled : There is not enough free space in the hash table.\n") ; free(tmp) ; return 2;
    }
    for (i = 0; i < HT->cap; i++)
    {
        if (fread(tmp, sizeof(Data), 1, f) != 1)
        {
            free(tmp) ; return -1;
        }
        chtbInsert(HT, tmp);
        fseek(f, sizeof(Data) * i + sizeof(int), SEEK_SET);
    }
    if (fclose(f) == EOF)
    {
        printf("[ReadingFromFile] : Failure : Error closing file.\n") ; free(tmp) ; return 1;
    }
	printf("[ReadingFromFile] : Success : All data from the file successfully read.\n");
    free(tmp); return 0;
}
void menu(chtb* HT, Data* vac)
{
    int command, N = 0, field = 0, cap = 0;
    Data* tmp; char tmpS[KEY_LEN] = "", fileName[FILE_NAME_LEN] = "";
    help();
    while (1)
    {
        printf("> ");
        fflush(stdin);
        scanf("%d", &command);
        switch (command)
        {
            case 0:
                printf("[menu->case0] : Goodbye)\n");
				return;
            break;
            case 1:
                printf("[menu->case1] : Init hash table.\nEnter the max number of entries\n> ");
                fflush(stdin); scanf("%d", &cap);
                chtbInit(HT, vac, cap); 
            break;
            case 2:
                printf("[menu->case2] : Destroy hash table.\n");
                chtbDestroy(HT); 
            break;
            case 3:
                printf("[menu->case3] : Gen hash table\nEnter the desired number of elements in the hash table. [Note] : N must be less then %d\n> ", HT->cap);
                fflush(stdin); scanf("%d", &N);
                chtbGen(HT, N);
            break;  
            case 4:
                // Загрузка из файла
				printf("[menu->case4] : Get data from the file.\nEnter file name : ");
				scanf(" %[^\n]%*c", fileName);
				ReadingFromFile(HT, fileName);
				strcpy(fileName, "");
            break;  
            case 5:
                // Выгрузка в файл 
				printf("[menu->case5] : Write data to the file.\nEnter file name : ");
				scanf(" %[^\n]%*c", fileName);
				WritingToFile(HT, fileName);
				strcpy(fileName, "");
            break;
            case 6:
                printf("[menu->case6] : Insert entry\n");
                tmp = genData(tmp);
                if(chtbInsert(HT, tmp) == -1) 
                {
                    free(tmp);
                }
            break;
            case 7:
                printf("[menu->case7] : Remove the entry\nEnter key : "); scanf("%s", tmpS);
                chtbRemove(HT, tmpS); 
                strcpy(tmpS, "");
            break;
            case 8:
                printf("[menu->case8] : Look up specified entry\nEnter key : ");
                fflush(stdin); scanf("%s", tmpS);
                if (chtbLookup(HT, tmpS, &tmp) == 0) printf("HT (founded) : [\n\tKey : %s\n\tData :\n\t\tC = %c\n\t\tA = [ %.3f, %.3f, %.3f ]\n]\n", tmp->key, tmp->C, tmp->A[0], tmp->A[1], tmp->A[2]);
                strcpy(tmpS, "");
            break;
            case 9:                
                printf("[menu->case9] : Update specified entry\nEnter key : ");
                fflush(stdin); scanf("%s", tmpS);
                printf("[menu->case9] : Which field do you want to update? [ 1 -> char, 2 -> float[3] ]\n> "); fflush(stdin);
                scanf("%d", &field);
                chtbUpdate(HT, tmpS, field);
                strcpy(tmpS, "");
            break;
            case 10:
                printf("[menu->case10] : Is has table empty?\n");
                if (HT->table == NULL) printf("[menu->case10] : Yes.\n");
                else printf("[menu->case10] : No.\n");
            break;
            case 11:
                printf("[menu->case11] : Display hash table\n");
                chtbDisplay(HT);
            break;
            case 12:
                printf("[menu->case12] : Print help.\n");
                help();
            break;
            default:
                printf("[menu->default] : The menu does not contain this command.\n");
                break;
        }
    }
}
int main()
{
    srand(time(NULL));
    chtb* HT = (chtb*)malloc(sizeof(chtb));
    Data* vac = (Data*)malloc(sizeof(Data));
    HT->table = NULL; HT->size = 0; HT->cap = 0;
    menu(HT, vac);
    //Data* tmp;
    //chtbInit(HT, vac, 3);
    // Работает
    //chtbGen(HT, 3);
    //free(tmp);
    //chtbDisplay(HT);
    //char key[KEY_LEN]; scanf("%s", key);
    //chtbRemove(HT, key);
    //chtbDisplay(HT);
    //printf("- HT generated : [\n\tKey : %s\n\tData :\n\t\tC = %c\n\t\tA = [ %.3f, %.3f, %.3f ]\n]\n", HT->table[0]->key, HT->table[0]->C, HT->table[0]->A[0], HT->table[0]->A[1], HT->table[0]->A[2]);
    chtbDestroy(HT) ; getc(stdin) ; free(HT) ; return 0;
}