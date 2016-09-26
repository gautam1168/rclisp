#include <stdlib.h>
#include "hashmap.h"
#include "string.h"

#define INITIAL_SIZE 1009 //this should probably be in the header

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
	if (!map) exit(1);//goto err; -> exit with error code

	map->nd = (mapnode *)calloc(INITIAL_SIZE, sizeof(mapnode));
	if (!map->nd)
    {
        del_hashmap(map);
        exit(1);
    }//goto err;

	map->size = INITIAL_SIZE;
	map->keytype = keytype;
	map->valtype = valtype;

	return map;

//	err:              -> goto's have wierd scope implications, better to avoid them
//		if (map)
//			del_hashmap(map);
//		return NULL;
}

void del_hashmap(hashmap map){}

void hashmap_delete(hashmap map, void * key){}
//bool!
bool hashmap_has(hashmap map, void * key){
    if(hashmap_get(map, key) != NULL)
        return true;
    return false;

	// char * strkey = (char *)key;
	// //Find hash of key
	// unsigned long hash = djb2(key) % map->size; //instead of INITIAL_SIZE
	// int reqd_bucket = hash, buckets_traversed = 0;
	// mapnode curr;
	// while (buckets_traversed < INITIAL_SIZE){
	// 	curr = map->nd[reqd_bucket];
	// 	if (curr){
	// 		if (strcmp(curr->key, strkey) == 0){
	// 			return 1;
	// 		}
	// 		else{
	// 			reqd_bucket += 1;
	// 			buckets_traversed += 1;
	// 		}
	// 	}
	// 	else{
	// 		reqd_bucket += 1;
	// 		buckets_traversed += 1;
    //
	// 		if (reqd_bucket == INITIAL_SIZE -1){
	// 			reqd_bucket = 0;
	// 		}
	// 	}
	// }
    //
	// if (buckets_traversed == INITIAL_SIZE){
	// 	return 0;
	// }
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
//	printf("map keytype: %s\n", map->keytype);
//	printf("compare keytypes: %d\n", strcmp(map->keytype, "string") == 0);
//	if (strcmp(map->keytype, "string") == 0){
		hash = djb2(key) % INITIAL_SIZE; //Have to find the correct method for this
		mapnode nd = new_mapnode(hash, key, value);

        map->nd[find_bucket(NULL, hash)] = value;
        //handle case: map is full (maybe grow the hashmap)
        //if you want to throw error probably exit(1) instead of printing

		//Probe the hasmap to find empty slot
		// int empty_bucket = hash, buckets_traversed = 0;
		// while (buckets_traversed < map->size){    //not INITIAL_SIZE right?
		// 	//If current bucket is full check next one
		// 	if (map->nd[empty_bucket]){
		// 		empty_bucket += 1;
		// 		buckets_traversed += 1;
        //
		// 		//If current bucket is last one set next to first one
		// 		if (empty_bucket == INITIAL_SIZE -1){
		// 			empty_bucket = 0;
		// 		}
		// 	}
		// 	else{
		// 		break;
		// 	}
		// }
		// if (buckets_traversed == map->size){  //not INITIAL_SIZE right?
		// 	printf("Error: hashmap is full. Cannot insert key %s\n",
		// 			(char *)key);
		// }
		//else{
			//Insert into map
		//	map->nd[empty_bucket] = nd;
	//	}
	//}
	//else {
//		printf("Only string keys are implemented\n");
//	}
}

//void*
char * hashmap_get(hashmap map, char * key){
	//Cast key
	char * strkey = (char *)key;

	//Calculate hash of key
	unsigned long hash = djb2(key) % INITIAL_SIZE;

    curr = map->nd[find_bucket(key, hash)];

	// int reqd_bucket = hash, buckets_traversed = 0;
	// mapnode curr;
	// while (buckets_traversed < INITIAL_SIZE){
	// 	curr = map->nd[reqd_bucket];
	// 	if (curr){
	// 		if (strcmp(curr->key, strkey) == 0){
	// 			break;
	// 		}
	// 		else{
	// 			reqd_bucket += 1;
	// 			buckets_traversed += 1;
	// 		}
	// 	}
	// 	else{
	// 		reqd_bucket += 1;
	// 		buckets_traversed += 1;
    //
	// 		if (reqd_bucket == INITIAL_SIZE -1){
	// 			reqd_bucket = 0;
	// 		}
	// 	}
	// }
    // // should this be in the while loop? vvvvvvv
	// if (buckets_traversed == INITIAL_SIZE){
	// 	printf("WARNING: Key %s not found in map\n", (char *)key);
	// 	return NULL;
	// }

	// //Get value from map
	// return map->nd[reqd_bucket]->data;
}


//this is just a sketch, this probably isn't quite right
int find_bucket(start_here, thing_to_find){
    int buckets_traversed = 0;
    mapnode curr;

    while (buckets_traversed < map->size){    //not INITIAL_SIZE right?
        curr = map->nd[reqd_bucket];
        if (curr != thing_to_find){ //or something sort of like this, think about NULL case
            //empty_bucket += 1;    //this is really minor, but you can get by with
            buckets_traversed += 1; // just keep track of how many you've traversed

            //If current bucket is last one set next to first one
            if ((start_here + buckets_traversed) == INITIAL_SIZE -1){
                start_here = 0;
            }
        }
        else{ //found it!
            return (start_here + buckets_traversed); //index!
        }
    }
    return -1;
//    if (buckets_traversed == map->size){  //not INITIAL_SIZE right?
//        printf("Error: hashmap is full. Cannot insert key %s\n",
//                (char *)key);
//    }
}





void print(hashmap map){
	for (int i=0; i < INITIAL_SIZE; i++){
		if (map->nd[i]){
			printf("%d : [%s -> %s]\n", i, (char *)map->nd[i]->key, (char *)map->nd[i]->data);
		}
		//printf("%s : %s\n", (char *)map->nd[i]->key, (char *)map->nd[i]->data);
	}
}
