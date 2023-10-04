#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char** letterCombinations(char* digits, int* returnSize) {
    int len  = strlen(digits);
    if ( !digits || !len ) {
        *returnSize = 0;
        return NULL;
    }
    char* array[9] = {"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int size = 1, cnt = 0, cur_size = 0, rest_size = 0;
    for (int i = 0; i < len; i++) {
        size *= strlen(array[digits[i] - '1']);
    }
    *returnSize = rest_size = size;
    char** ret = (char**) malloc(sizeof(char*) * (*returnSize));
    for (int i = 0; i < size; i++) {
        ret[i] = (char*) malloc (sizeof(char) * (len+1));
    }
    for (int i = 0; i < len+1; i++) {
        if (i < len) {
            cur_size = strlen(array[digits[i] - '1']);
            rest_size /= cur_size;
        }
        for (int j = 0; j < size; j++) {
            if (i == len) {
                ret[j][cnt] = '\0'; 
            } else {
                // every character need rest_size times -> j/rest_size%cur_size
                ret[j][cnt] = array[digits[i] - '1'][j/rest_size%cur_size];
            }
        } 
        cnt++;
    }
    return ret;
}