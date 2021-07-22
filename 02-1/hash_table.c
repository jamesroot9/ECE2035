//=================================================================
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*
 Student Name: James Root
 Date: 10/30/2020

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
	e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
	e.g. "_HashTable", "_HashTableEntry"

	Recall that in C, we have to type "struct" together with the name of the struct
	in order to initialize a new variable. To avoid this, in hash_table.h
	we use typedef to provide new "nicknames" for "struct _HashTable" and
	"struct _HashTableEntry". As a result, we can create new struct variables
	by just using:
		- "HashTable myNewTable;"
		 or
		- "HashTableEntry myNewHashTableEntry;"

	The preceding underscore "_" simply provides a distinction between the names
	of the actual struct defition and the "nicknames" that we use to initialize
	new structs.
	[See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
	the first letter is lower-case.
	e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
			 It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
	as a distinction between function local variables and struct members.
	e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
	/** The array of pointers to the head of a singly linked list, whose nodes
			are HashTableEntry objects */
	HashTableEntry** buckets;

	/** The hash function pointer */
	HashFunction hash;

	/** The number of buckets in the hash table */
	unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
	/** The key for the hash table entry */
	unsigned int key;

	/** The value associated with this hash table entry */
	void* value;

	/**
	* A pointer pointing to the next hash table entry
	* NULL means there is no next entry (i.e. this is the tail)
	*/
	HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
	//allocate memory for HashTableEntry on heap
	HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry));

	//initialize componets of new HashTableEntry struct
	newEntry->key = key;
	newEntry->value = value;
	newEntry->next = NULL;

	//return pointer
	return newEntry;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
	//calculate index of buckets that the value is stored at
	int buck = hashTable->hash(key);

	//create pointer to first entry at index
	HashTableEntry* ptr = hashTable->buckets[buck];

	//iterate as long as pointer is not NULL
	while (ptr) {
		//if the pointer has the specified key, return that pointer
		if (ptr->key == key) {
			return ptr;
		}
		//move the pointer to the next value
		ptr = ptr->next;
	}

	//loop exited, value not found, return NULL
	return NULL;
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
	// The hash table has to contain at least one bucket. Exit gracefully if
	// this condition is not met.
	if (numBuckets==0) {
		printf("Hash table has to contain at least 1 bucket...\n");
		exit(1);
	}

	// Allocate memory for the new HashTable struct on heap.
	HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

	// Initialize the components of the new HashTable struct.
	newTable->hash = hashFunction;
	newTable->num_buckets = numBuckets;
	newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

	// As the new buckets contain indeterminant values, init each bucket as NULL.
	unsigned int i;
	for (i=0; i<numBuckets; ++i) {
		newTable->buckets[i] = NULL;
	}

	// Return the new HashTable struct.
	return newTable;
}

void destroyHashTable(HashTable* hashTable) {
	// Free every value in buckets
	unsigned int i;
	for (i = 0; i < hashTable->num_buckets; i++) {
		//set pointer to head of linked list
		HashTableEntry* ptr = hashTable->buckets[i];
		//while the ptr is not null, iterate
		while (ptr) {
			//declare another pointer to 
			HashTableEntry* temp = ptr;
			ptr = ptr->next;
			free(temp->value);
			free(temp);
		}
		free(ptr);
	}

	free(hashTable->buckets);
	// Free actual HashTable
	free(hashTable);
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
	// use findItem method to see if the key already exists in the hashtable
	HashTableEntry* finder = findItem(hashTable, key);
	if (finder) {
		//save old value to return, replace with new value
		void* result = finder->value;
		finder->value = value;
		return result;
	}

	//calculate index at which the key will be stored in buckets
	int buck = hashTable->hash(key);

	//create pointer to first entry at that index
	finder = hashTable->buckets[buck];

	//create new node to be inserted
	HashTableEntry* newNode = createHashTableEntry(key, value);
	if (finder) {
		//if the first entry at index is not null, iterate to the last entry in the list
		//and add the entry there
		while (finder->next != NULL) {
			finder = finder->next;
		}
		finder->next = newNode;
	} else {
		//if the first entry is null, place entry in first position
		hashTable->buckets[buck] = newNode;
	}
	return NULL;
}

void* getItem(HashTable* hashTable, unsigned int key) {
	//Use findItem helper to locate the node where key is stored
	HashTableEntry* ptr = findItem(hashTable, key);
	if (ptr != NULL) {
		//if the ptr exists, return the value stored there
		return ptr->value;
	}
	//if rge ptr doesnt exist, return NULL
	return NULL;
}

void* removeItem(HashTable* hashTable, unsigned int key) {
	//calculate index at which the key will be stored in buckets
	int buck = hashTable->hash(key);
	//create pointer to first entry at that index
	HashTableEntry* ptr = hashTable->buckets[buck];
	if (ptr == NULL) {
		//if the ptr is NULL, return NULL (key not found)
		return NULL;
	}
	if (ptr->key == key) {
		//if the key is at the first entry, set first value to be the next value
		//and return original value stored
		HashTableEntry* result = ptr->value;
		hashTable->buckets[buck] = ptr->next;
		free(ptr);
		return result;
	}
	//iterate the next values of ptr to find the node before the key node is found
	while (ptr && ptr->next != NULL && ptr->next->key != key) {
		ptr = ptr->next;
		if (ptr->next == NULL) {
			//if the value next to ptr is NULL, return NULL (key not found)
			return NULL;
		}
	}
	//once node before is found, delete the entry storing the key 
	//and return the value stored there
	HashTableEntry* node = ptr->next;
	void* result = node->value;
	ptr->next = node->next;
	free(node);
	return result;
}

void deleteItem(HashTable* hashTable, unsigned int key) {
	//call remove item and free the data that is returned.
	free(removeItem(hashTable, key));
}
