#include <stdlib.h>
#include "hashmap.h"
#include "string.h"

#define INITIAL_SIZE 1009

mapnode new_mapnode(unsigned long keyhash, void * key, void * data){
	//Handling only one case
	mapnode nd = (mapnode)malloc(sizeof(mapnode_t));
	nd->keyhash = keyhash;
	
	nd->key = key;

	nd->data = data;
	
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

void del_hashmap(hashmap map){}

void hashmap_delete(hashmap map, void * key){}

int hashmap_has(hashmap map, void * key){
	char * strkey = (char *)key;
	//Find hash of key
	unsigned long hash = djb2(key) % INITIAL_SIZE;

	int reqd_bucket = hash, buckets_traversed = 0;
	mapnode curr;
	while (buckets_traversed < INITIAL_SIZE){
		curr = map->nd[reqd_bucket];
		if (curr){
			if (strcmp(curr->key, strkey) == 0){
				return 1;
			}
			else{
				reqd_bucket += 1;
				buckets_traversed += 1;
			}
		}
		else{
			reqd_bucket += 1;
			buckets_traversed += 1;

			if (reqd_bucket == INITIAL_SIZE -1){
				reqd_bucket = 0;
			}
		}
	}

	if (buckets_traversed == INITIAL_SIZE){
		return 0;
	}
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

void hashmap_add(hashmap map, void * key, void * value){
	//Cast key
	unsigned long hash;
	printf("map keytype: %s\n", map->keytype);
	printf("compare keytypes: %d\n", strcmp(map->keytype, "string") == 0);
	if (strcmp(map->keytype, "string") == 0){
		hash = djb2(key) % INITIAL_SIZE; //Have to find the correct method for this
		mapnode nd = new_mapnode(hash, key, value);
	
		//Probe the hasmap to find empty slot
		int empty_bucket = hash, buckets_traversed = 0;
		while (buckets_traversed < INITIAL_SIZE){
			//If current bucket is full check next one
			if (map->nd[empty_bucket]){
				empty_bucket += 1;
				buckets_traversed += 1;
		
				//If current bucket is last one set next to first one
				if (empty_bucket == INITIAL_SIZE -1){
					empty_bucket = 0;
				}
			}
			else{
				break;
			}
		}
		if (buckets_traversed == INITIAL_SIZE){
			printf("Error: hashmap is full. Cannot insert key %s\n", 
					(char *)key);
		}
		else{
			//Insert into map
			map->nd[empty_bucket] = nd;
		}
	}
	else {
		printf("Only string keys are implemented\n");
	}
}

void * hashmap_get(hashmap map, void * key){
	//Cast key
	char * strkey = (char *)key;
	
	//Calculate hash of key
	unsigned long hash = djb2(key) % INITIAL_SIZE;

	int reqd_bucket = hash, buckets_traversed = 0;
	mapnode curr;
	while (buckets_traversed < INITIAL_SIZE){
		curr = map->nd[reqd_bucket];
		if (curr){
			if (strcmp(curr->key, strkey) == 0){
				break;
			}
			else{
				reqd_bucket += 1;
				buckets_traversed += 1;
			}
		}
		else{
			reqd_bucket += 1;
			buckets_traversed += 1;

			if (reqd_bucket == INITIAL_SIZE -1){
				reqd_bucket = 0;
			}
		}
	}

	if (buckets_traversed == INITIAL_SIZE){
		printf("WARNING: Key %s not found in map\n", (char *)key);
		return NULL;
	}

	//Get value from map
	return map->nd[reqd_bucket]->data;
}

void print(hashmap map){
	for (int i=0; i < INITIAL_SIZE; i++){
		if (map->nd[i]){
			printf("%d : [%s -> %s]\n", i, (char *)map->nd[i]->key, (char *)map->nd[i]->data);
		}
		//printf("%s : %s\n", (char *)map->nd[i]->key, (char *)map->nd[i]->data);
	}	
}
