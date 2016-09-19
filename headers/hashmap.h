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

mapnode new_mapnode(unsigned long , void *, int, void *, int);

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
void add(hashmap, void *, void *);
void * get(hashmap, void *);
void * del_node(hashmap, void *);
void del_hashmap(hashmap);
void print(hashmap);
int has(hashmap, void *);

#endif
