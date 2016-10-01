#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdbool.h>

//Pointer to hash function candidate
typedef unsigned long (*hashfunction)(void *);
unsigned long djb2(void *);

//A node in hashmap
struct mapnode_struct{
	unsigned long keyhash;
	void * key, * data;
};

typedef struct mapnode_struct mapnode_t;
typedef mapnode_t * mapnode;

mapnode new_mapnode(unsigned long keyhash, void * key, void * data);

//Struct packaging a node and its bucket index in a hashmap
struct bucket_struct{
	int index;
	mapnode nd;
};
typedef struct bucket_struct bucket_t;
typedef bucket_t * bucket;

//Hashmap
struct hashmap_struct{
	hashfunction hash;
	mapnode * nd;
	char * keytype, * valtype;
	int size;
};

typedef struct hashmap_struct hashmap_t;
typedef hashmap_t * hashmap;

//constructor
hashmap new_hashmap(hashfunction hash, char * keytype, char * valtype);
void del_hashmap(hashmap map);

//Add values to map
void hashmap_add(hashmap map, void * key, void * value);
bucket_t hashmap_get(hashmap map, void * key);
bool hashmap_has(hashmap map, void * key);
void hashmap_delete(hashmap map, void * key);
void print(hashmap map);

/*
 * Arguments:
 * 			map			 				- map to search
 *			key							- of the node being searched
 *			starting_index	- place to start searching in array
 *
 * Return:
 *			-1 									- if node not present in array
 *			index of node 			- if present
 **/
bucket_t find_bucket(hashmap map, void * key, int starting_index);

#endif
