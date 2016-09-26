#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>

//Pointer to hash function candidate
typedef unsigned long (*hashfunction)(void *);
unsigned long djb2(void *);

//The hashmap datastructure
struct mapnode_struct{
	unsigned long keyhash;
	void * key, * data;
};

typedef struct mapnode_struct mapnode_t;
typedef mapnode_t * mapnode;

mapnode new_mapnode(unsigned long , void *, void *);

struct hashmap_struct{
	hashfunction hash;
	mapnode * nd;
	char * keytype, * valtype;
	int size;
};

typedef struct hashmap_struct hashmap_t;
typedef hashmap_t * hashmap;

//constructor 
hashmap new_hashmap(hashfunction, char *, char *);
void del_hashmap(hashmap);

//Add values to map
void hashmap_add(hashmap, void *, void *);
void * hashmap_get(hashmap, void *);
void hashmap_delete(hashmap, void *);
void print(hashmap);
int hashmap_has(hashmap, void *);

#endif
