#include "hashmap.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char * st = "gaurav";
	printf("Create a new hashmap instance\n");
	hashmap map = new_hashmap(&djb2, "string", "string");

	printf("\nCheck hashing function output\n");
	printf("key: gaurav \nhashed key: %ld\n", djb2("gaurav"));
	
	char * key, *value;
	printf("\nInserting values into hashmap\n");
	key = "gaurav";
	value = "gautam";
	hashmap_add(map, (void *)key, (void *)value);

	key = "chakravarthy";
	value = "gopi";
	hashmap_add(map, (void *)key, (void *)value);

	key = "annie";
	value = "cherkaev";
	hashmap_add(map, (void *)key, (void *)value);

	printf("\nPrinting the hashmap\n");
	print(map);

	printf("\nChecking that the get function works on the hashmap\n");	
	printf("annie -> %s\n", (char *)hashmap_get(map, (void *)key));
	key = "gaurav";
	printf("gaurav -> %s\n", (char *)hashmap_get(map, (void *)key));
	key = "chakravarthy";
	printf("chakravarthy -> %s\n", (char *)hashmap_get(map, (void *)key));

	printf("\nChecking that the has function works on the hashmap\n");
	printf("Map has key- chakravarthy: %d\n", hashmap_has(map, (void *)key));
	key = "lakshit";
	printf("Map has key- lakshit: %d\n", hashmap_has(map, (void *)key));
	return 0;
}
