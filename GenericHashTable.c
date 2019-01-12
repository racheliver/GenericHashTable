
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericHashTable.h"







					/************************************************
					*    user name:rachelive                        *
					*    Name & ID:Racheli  Verechzon , 305710071   *
					*  ======================================       *
					*   Ex1 - Hashtable in c Programming            *
					*               12/12/2018                      *
					*  ======================================       *
					************************************************/


			/***************************About this Program*************************************
			* Using Dynamic memory Allocation and Generic Programming                         *
			* implementaion Hash Table data structures that support these three operations:   *
			*   					                            		  *
			*1. Adding an element								  *
			*2. Removing an element								  *
			*3. Searching for an element							  *
			***********************************************************************************/








/*************************createTable*************************************************************
* The function gets the original size and the type of the data in the table elements.            *
* it initializes the Table struct members and in addition                                        *
* memory assignment for a table-type strcak as well as a linked list within it.                  *
* On success, the function returns a pointer to the new created Table, otherwise, it return NULL.*
**************************************************************************************************/

Table *createTable(int size, int dType, int listLength) {
    Table* new_table;
    if (size<1) {
        printf("**invalid size for table**\n"); return NULL;
    } /* invalid size for table */
    if(dType!=1 && dType!=0){
        printf("**invalid dtype for table**\n"); return NULL;
    } /* invalid dtype for table */
    if (listLength<1) {
        printf("**invalid listLength of nodes**\n"); return NULL;
    } /* invalid listLength of nodes */


    /* Attempt to allocate memory for the table structure */
    if ((new_table = malloc(sizeof(Table))) == NULL) {
        return NULL;
    }

    /* Attempt to allocate memory for the table itself */
    if ((new_table->arr = malloc(sizeof(Object *) * size)) == NULL) {
        return NULL;
    }
    /* Initialize the elements of the table */
    for(int i=0; i<size; i++) new_table->arr[i] = NULL;

/* Set the table's details */
    new_table->size = size;
    new_table->d = 1;
    new_table->Ext = 1;
    new_table->dType=dType;
    new_table->listLength=listLength;
    return new_table;

}






/**************************************freeTable**************************************************
* The function release all the allocated members of struct Table.                                *
* We have a private case test where we got a pointer to the NULL table.                          *
* In the event that the table actually points to the data, we use two loops                      *
* when the one passes the size of the current array and the second receives                      *
* the size of the linked lists within the table cells.                                           *
* We will define a pointer named list, with which we will go over the linked list vertebrates,   *
* and we will release one by one using an auxiliary function.                                    *
* And finally releasing the pointer to the table and the table itself                            *
**************************************************************************************************/

void freeTable(Table* table)
{

    int i;
    Object *list, *temp;

    if (table==NULL){
        printf("the table is NULL\n"); return;
    }

    /* Free the memory for every item in the table, including the
     * object themselves.
     */
    for(i=0; i<(table->size)*(table->d); i++) {
        list = table->arr[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;

            freeObject(temp, table->dType);
            temp=NULL;

        }
    }

    /* Free the table itself */
    free(table->arr);
    free(table);

}










/***************add********************************************************************************
* The function accepts two parameters:                                                            *
* 1) Table* table: provides the table struct.                                                     *
* 2) void* data  : the information we want to insert into the table.                              *
* The function adds data to the hashtable (as described in the exe definition)                    *
* On success, the function returns the array index of the added data, otherwise, it return -1.    *
* We distinguish between two cases, one of an integer  as data,                                   *
* and the other a string received as data.                                                        *
* This is because in the string case we use memory allocation for the characters                  *
* We then examine the easiest case in which we insert the linked lists into the first cell,       *
* if its not that case,we determine where the next cell is available.                             *
* This is done by an auxiliary function that clarifythe correct location in the linked list Table *
***************************************************************************************************/

int add(Table *table, void *data) {
    if(table==NULL || data==NULL){
        printf("the table/data is NULL return value -1\n"); return ERROR;
    }
    Object* object ;
    int position;
    int resultMod;
    int thePotision;
    if(table->dType==INT_TYPE){
        resultMod=intHashFun((int*)data,table->size);
        object =createObject(data);
    }
    else {
        char *stringObj = (char *)malloc(strlen((char *)data) * sizeof(char) + 1);
        if(stringObj == NULL)return ERROR;
        strcpy(stringObj, (char *)data);
        object = createObject((char *)stringObj);
        resultMod = strHashFun((char *) data, table->size);
    }

    position = resultMod*(table->d);
    if(table->arr[position]==NULL) {
        table->arr[position] = object;
        return position;
    }
    else {
        thePotision=clarifyLoc(&table,position,&object);
        if(thePotision!=ERROR)
        {
            return thePotision;//not need multi
        }
        else{
            newPower2table(table);
            position = resultMod*(table->d);
            thePotision=clarifyLoc(&table,position,&object);
            return thePotision;
        }

    }

}





/**************************removeObj*********************************************************
* The function removes the Object which its data equals to data, if there are more than one,*
* it removes the first one.                                                                 *
* On success, the function returns the array index of the removed data,                     *
* otherwise, it returns -1. -1 is also returned in the case where there is no such object.  *
* First, we will refer to individual cases in which NULL values ​​are sent to the function.   *
* We will then identify the position at the beginning of the table to the resulting data.   *
* Then we move through two loops as the outer layer is at the top of the first cell of the  *
* position we received and ends in the last cell in the table (in the case of expansion     *
* we will need to go through more than one cell to confirm an object adjustment.            *
* In the second loop we will go over the size of the linked lists and compare               *
* with an auxiliary function whether the two objects we found are equal.                    *
* If we find the object, we will release it                                                 *
*********************************************************************************************/

int removeObj(Table *table, void *data)
{
    if(data==NULL || table==NULL){
        printf("**Error the data/table is NULL**\n");return ERROR;
    }

    int potision;
    if (table->dType == INT_TYPE)
        potision = (table->d)*intHashFun((int*)data, table->size);
    else
        potision = (table->d)*strHashFun((char*)data, table->size);

    for (int i = potision; i < potision + table->d; i++)
    {
        Object *pointer = table->arr[i], *prev = NULL; int index=table->listLength;
        while (pointer != NULL && index>0)
        {
            if (isEqual(table->dType, pointer->data, data) == 0)
            {

                if (prev == NULL)
                    table->arr[i] = pointer->next;
                else
                    prev->next = pointer->next;
                freeObject(pointer, table->dType);

                return i;
            }
            index--;
            prev = pointer;
            pointer = pointer->next;
        }
    }
    return ERROR;
}






/***************************************search**************************************************************
* The function search for an object that its data is equal to data and returns a pointer to that object.   *
* If there is no such object or in a case of an error, NULL is returned.                                   *
* First we will examine cases in which we have null values ​​for a function.                                 *
* Then we will check the exact position of the object at the beginning of the table                        *
* and then we will loop through the linked list and use the auxiliary function                             *
* to determine that we have indeed reached Ubiquit and return a pointer                                    *
************************************************************************************************************/

Object* search(Table* table, void* data){
    if(data==NULL || table == NULL){
        printf("**Error NULL**\n");return NULL;
    }
    Object *pointer; int potision;int d=table->d;

    if (table->dType == INT_TYPE)
        potision = (table->d)*intHashFun((int*)data, table->size);
    else
        potision = (table->d)*strHashFun((char*)data, table->size);

    for(int j = potision ; j < (potision + d);j++){
        pointer = table->arr[j];
        while(pointer != NULL){
            if(isEqual(table->dType, data, pointer->data) == 0)
                return pointer;
            pointer = pointer->next;
        }
    }
    free(pointer);
    return NULL;
}




/************************printTable**********************************
* The function print the table (the format is in the exe definition)*
*********************************************************************/

void printTable(Table *table) {
    if(table==NULL){
        printf("**Error NULL**\n");return;
    }
    int i;Object* object;

    printf("\n");
    for (i = 0; i <table->size*table->d ; i++) {
        printf("[%d]",i);

        object=table->arr[i];
        while (object != NULL) {
            if(table->dType==STR_TYPE)
                printf("\t%s\t-->\t", (char *) object->data);
            else {
                int x=*(int*) (object->data);
                printf("\t%d\t-->\t", (int) x);
            }
            object = object->next;
        }

        printf("\n");
    }
}






/**************************createObject*********************************************************
* This function creates an object and return the pointer to it or NULL if there is some error. *
************************************************************************************************/

Object* createObject(void* data) {

    struct Object* object = (struct Object*)malloc(sizeof(struct Object));
    if(object==NULL)return NULL;
    object->data=data;
    object->next=NULL;
    return object;
}




/****************************************freeObject****************************
* This function frees an object,  note the in the case of STR_TYPE, the data  *
* of the object should also be freed.                                         *
*******************************************************************************/

void freeObject(Object *obj, int type)
{
    if (type == STR_TYPE)
    {
        free(obj->data);
        free(obj);
    }
    else
        free(obj);
}




/*****************************************isEqual*****************************************************************
* check the equality of the data of two objects. The implementation is different depending the type of the data. *
* the function returns 0 if they are equal or some other value if they are not equal.                            *
******************************************************************************************************************/

int isEqual(int type, void* data1, void* data2){
    if(type == INT_TYPE)
        if(*(int*)data1 == *(int*)data2)
            return 0;

    if(type == STR_TYPE)
        if(strcmp((char*)data1, (char*)data2 ) == 0)
            return 0;

    return ERROR;
}







/***********************strHashFun*************************************
* The function gets 2 parameters:                                     *
*1)key Which is the data  and also the a key in the hash table.       *
*2)the origSize represent The original size of the table.             *
* The function returns:                                   	      *
* the hash value of an string, which is sum mod origSize,             *
* where sum is the sum of the ascii value of all the character in key.*
* I used the function strlen from <string.h> directory to determine   *
* the length of the received character string                         *
* Character after character in the loopI summed up the amount         *
**********************************************************************/

int strHashFun(char *key, int origSize) {
    int count = 0;int i;
    for (i=0; i<(strlen(key)); i++)
    {
        count+=key[i];
    }
    return (count%origSize);
}






/**************************intHashFun*****************************
* returns the hash value of an integer, which is key mod origSize*
******************************************************************/

int intHashFun(int *key, int origSize) {

    return ((*key) % origSize);
}










/******************************************************private function********************************************************/


/******************************************clarifyLoc***********************************************************************
* A private function that tells you the exact location of the next empty object in the table.                              *
* The function accepts three parameters:                                                                                   *
* 1) points to the table                                                                                                   *
* 2) The cell at the beginning of the linked lists that we want to examine                                                 *
* 3) Pointing to the object you want to insert.                                                                            *
* The function is used in two loops. One is the size of the linked list and the second checks for the next free cell.      *
* When we find the empty space we will place the object in it.                                                             *
* And finally return the position in the table we found.                                                                   *
****************************************************************************************************************************/

int clarifyLoc(Table** table,int position,Object** object)
{
    int index=0;int needToExt;
    Object** objectPointer;
    for (needToExt = position;needToExt <position+(*table)->d ;needToExt++) {
        objectPointer=&((*table)->arr[needToExt]);
        index=0;
        while (index < (*table)->listLength && (*objectPointer) != NULL) {
            objectPointer = &((*objectPointer)->next);
            index++;
        }

        if((*objectPointer) == NULL && index < (*table)->listLength) {
            (*objectPointer) = *object;
            return position;
        }
    }


    return ERROR;
}





/*********************************newPower2table*******************************************************
* The size of an array is generally smaller than the number of possible keys given.                   *
* Thus, more than one key can be mapped by a specific hash function to a single location in the array *
* which forms the hash table. we Choose that way to deal with this issue:                             *
* All existed entries of the table 0-(n-1) will be mapped to the respective even entries              *
* in the new table (this is accomplished by multiplying the original index by 2).                     *
* If an additional expansion of this table is required, this process is repeated.                     *
* In this manner the distance between entries of the original table are always a power oם two.        *
 ******************************************************************************************************/

Table* newPower2table(Table* table){

    Table* new_table; table->d *=2; int d=table->d;

    new_table= createTable(table->size*d,table->dType,table->listLength);

    for(int i = 0; i < table->size*d; i++){
        if(i%2 == 0)
            new_table->arr[i] = table->arr[i/2];
    }
    free(table->arr);
    table->arr = new_table->arr;
    free(new_table);
    return table;
}









