
            /************************************************
			*    user name:rachelive                        *
            *    Name & ID:Racheli  Verechzon , 305710071   *
            *  ======================================       *
            *   Ex1 - Hashtable in c Programming            *
            *               12/12/2018                      *
            *  ======================================       *
            *************************************************/
			*** Please open this document using Notepad++ ***
			*************************************************


			
***********what this program do************************
Using Dynamic memory Allocation and Generic Programming
we build a Hash Tables data structures that support these three operations: 
 
1. Adding an element
2. Removing an element
3. Searching for an element
  
the size of the array is dynamic, i.e. the size of the array can grow.
Mapping of an object to the appropriate location in this array is accomplished using a hash function:  
i=d*H(k,m)  
 
**********Description of the function*******************

	createTable - create the table and set the attributes.
	freeTable - free the table.
	add - add data to the ltable.
	removeObj - remove objects from the table.
	search - search data from the table.
	printTable - print the table.
	createObject - create objects and set the attributes.
	freeObject - free the object and the data.
	isEqual - check equality of two objects.
	intHashFun - calculate a hash table of integers.
	strHashFun - calculate a hash table of strings.

********** How to Compile this program*************

write  : "make"                   

***********How to run this program***********

write: ./ex1

**********Description of program files*************


#GenericHashTable.c	- c file.
#GenericHashTable.h	- header file.
#makefile		    - Make file.
#README 			- this file.

**********Description What input we needed*************
The user will create a main program And in it a table Type Table*
in which can send it to the functions listed above.

***********An explanation of the output we get************

output:	print the tables, pointer to search data , location of add object & remove object