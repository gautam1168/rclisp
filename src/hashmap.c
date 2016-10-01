#include <stdlib.h>
#include "hashmap.h"
#include "string.h"

#define INITIAL_SIZE 1009

//Limit scope of this function to this file
bucket_t find_bucket(hashmap map, void * key, int starting_index){
	mapnode curr;
	int mapsize = map->size;
	mapnode * nodes = map->nd;
	//Set required bucket to starting_index of search
	int reqd_bucket = starting_index, buckets_traversed=0;
	//Loop for the entire mapnode array
	while (buckets_traversed < mapsize){
		curr = nodes[reqd_bucket];

		//If bucket is not empty
		if (curr){
			if (strcmp(curr->key, (char *)key) == 0){
			bucket_t bucket = {reqd_bucket, curr};
				return bucket;
			}
			else{
				reqd_bucket += 1;
				buckets_traversed += 1;
				//Go to start of array if end is reached
				if (reqd_bucket == mapsize-1)
					reqd_bucket = 0;
			}
		}
		//If empty bucket is found then key is not in map
		else{
			bucket_t bucket = {reqd_bucket, NULL};
			return bucket;
		}
	}
	//Reached when the map is full but doesn't contain the required key
	bucket_t bucket = {-1, NULL};
	return bucket;
}

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
	if (!map){
		exit(1);
	}
	else{
		map->nd = (mapnode *)calloc(INITIAL_SIZE, sizeof(mapnode));
		if (!map->nd){
				del_hashmap(map);
				exit(1);
			}
	}

	map->size = INITIAL_SIZE;
	map->keytype = keytype;
	map->valtype = valtype;

	return map;
}

void del_hashmap(hashmap map){}

void hashmap_delete(hashmap map, void * key){}

bool hashmap_has(hashmap map, void * key){
	char * strkey = (char *)key;
	//Find hash of key
	unsigned long hash = djb2(key) % map->size;
	//Find actual key of node in map
	bucket_t bucket = find_bucket(map, key, hash);
	if (bucket.index != -1 && bucket.nd != NULL){
		return true;
	}
	return false;
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
	if (strcmp(map->keytype, "string") == 0){
		hash = djb2(key) % map->size; //Have to find the correct method for this
		mapnode nd = new_mapnode(hash, key, value);

		//Probe the hasmap to find empty slot
		bucket_t bucket = find_bucket(map, key, hash);
		if (bucket.nd != NULL){
			printf("Error: hashmap is full. Cannot insert key %s\n",
					(char *)key);
		}
		else{
			//Insert into map
			map->nd[bucket.index] = nd;
		}
	}
	else {
		printf("Only string keys are implemented\n");
	}
}

bucket_t hashmap_get(hashmap map, void * key){
	//Cast key
	char * strkey = (char *)key;

	//Calculate hash of key
	unsigned long hash = djb2(key) % map->size;

	bucket_t bucket = find_bucket(map, key, hash);

	//Get value from map
	return bucket;
}

void print(hashmap map){
	printf("Hashmap:\nsize:%d\n", map->size);
	for (int i=0; i < map->size; i++){
		if (map->nd[i]){
			printf("%d : [%s -> %s]\n", i, (char *)map->nd[i]->key, (char *)map->nd[i]->data);
		}
	}
}
