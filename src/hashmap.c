#include <stdlib.h>
#include "hashmap.h"
#include "string.h"

#define INITIAL_SIZE 1024

mapnode new_mapnode(unsigned long keyhash, void * key, int keysize, void * data, int datasize){
	//Handling only one case
	mapnode nd = (mapnode)malloc(sizeof(mapnode_t));
	nd->keyhash = keyhash;
	
	nd->key = (unsigned char *)malloc(keysize);
	strcpy(nd->key, key);
	
	//Will have to figure out how to store functions like this
	nd->data = (unsigned char *)malloc(datasize);
	strcpy(nd->data, data);

	return nd;
}

hashmap new_hashmap(hashfunction hash, char * keytype, char * valtype){
	hashmap map = (hashmap)malloc(sizeof(hashmap_t));
	
	//Memory allocation failed
	if (!map) goto err;
	
	map->nd = (mapnode *)calloc(INITIAL_SIZE, sizeof(mapnode));
	if (!map->nd) goto err;

	map->size = INITIAL_SIZE;
	map->keytype = keytype;
	map->valtype = valtype;
	
	return map;

	err:
		if (map)
			del_hashmap(map);
		return NULL;
}

void del_hashmap(hashmap map){

}

unsigned long djb2(void * key){
	//Convert to char
	unsigned char * keystring = (unsigned char *)key;

	//Get hash
	unsigned long hash = 5381;
	int c;

	while (c = *keystring++)
		hash = ((hash << 5) + hash) + c; // hash * 33 + c

	return hash;
}

void add(hashmap map, void * key, void * value){
	//Cast key
	unsigned long hash;
	printf("map keytype: %s\n", map->keytype);
	printf("compare keytypes: %d\n", strcmp(map->keytype, "string") == 0);
	if (strcmp(map->keytype, "string") == 0){
		 hash = djb2(key);
		//Create new mapnode(Ugly hack for sizes)
		hash = hash % 1000; //Have to find the correct method for this
		mapnode nd = new_mapnode(hash, key, 10, value, 20);


		//Insert into map
		map->nd[hash] = nd;
	}
	else {
		printf("Only string keys are implemented\n");
	}
}

void print(hashmap map){
	for (int i=0; i < INITIAL_SIZE; i++){
		if (map->nd[i]){
			printf("%d : [%s -> %s]\n", i, (char *)map->nd[i]->key, (char *)map->nd[i]->data);
		}
		else{
			printf("%d : []\n", i);
		}
		//printf("%s : %s\n", (char *)map->nd[i]->key, (char *)map->nd[i]->data);
	}	
}
