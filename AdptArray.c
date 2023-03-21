#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"


//Definition of the struct
typedef struct AdptArray_
{
    int size;
    PElement* elemarr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray , *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc){
    PAdptArray array = (PAdptArray)malloc(sizeof(AdptArray));
    if (array == NULL){             //Checking if allocation was successful
        return NULL;
    }
    //initialize the variables
    array->size=0;
    array->elemarr = NULL;
    array->copyFunc = copyFunc;
    array->delFunc = delFunc;
    array->printFunc = printFunc;
    return array;
}

void DeleteAdptArray(PAdptArray array){
    if(array == NULL){
        return;
    }
    for (int i = 0 ; i < array->size ; i++){  //Going over all the values in the array and deleting them
        if(array->elemarr[i]!=NULL) {
            array->delFunc((array->elemarr)[i]);
        }
    }
    array->copyFunc = NULL;
    array->delFunc = NULL;
    array->printFunc = NULL;
    free(array->elemarr);       //free the variables that created with allocation
    free(array);
    array = NULL;
}

Result SetAdptArrayAt(PAdptArray array, int index, PElement element){
    if(array == NULL || index <= 0){
        return FAIL;
    }else if(index >= array->size){     //Checking if we got an index larger than the size of the array
        array->elemarr = (PElement) realloc(array->elemarr , (index+1)*sizeof(PElement)); //Increasing the size of the array according to the index we received
        if(array->elemarr == NULL){
            return FAIL;
        }
        //Initialization of all new cells in the array to NULL
        for (int i = array->size ; i<index+1;i++){
            array->elemarr[i] = NULL;
        }
        array->size=index+1;
    }
    //If the cell is not empty, delete the value in the cell
    if(array->elemarr[index]!= NULL){
        array->delFunc((array->elemarr)[index]);
        array->elemarr[index]=NULL;
    }
    array->elemarr[index] = array->copyFunc(element); //Initialize the cell with a copy of the new value
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int index){

    //Checking that the values we received are correct
    if(array == NULL || index >= array->size || index < 0 || array->elemarr[index] == NULL){
        return NULL;
    } else{
        return array->copyFunc((array->elemarr)[index]);
    }
}

int GetAdptArraySize(PAdptArray array) {
    if(array == NULL){
        return -1;
    }
    return array->size;
}

void PrintDB(PAdptArray array){
    if(array == NULL){
        return;
    }

    //Printing all the values in the array using the print function pointer
    for (int i = 0 ; i < array->size ; i++){
        if(array->elemarr[i]!= NULL) {
            array->printFunc((array->elemarr)[i]);
        }
    }
}