#include "hashmap.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char * st = "gaurav";
	hashmap map = new_hashmap(&djb2, "string", "string");
	printf("key: gaurav \nhashed key: %ld\n", djb2("annie"));
	
	char * key, *value;
	key = "gaurav";
	value = "gautam";
	hashmap_add(map, (void *)key, (void *)value);

	key = "chakravarthy";
	value = "gopi";
	hashmap_add(map, (void *)key, (void *)value);

	key = "annie";
	value = "cherkaev";
	hashmap_add(map, (void *)key, (void *)value);

	print(map);
	
	printf("annie -> %s\n", (char *)hashmap_get(map, (void *)key));
	key = "gaurav";
	printf("gaurav -> %s\n", (char *)hashmap_get(map, (void *)key));
	key = "chakravarthy";
	printf("chakravarthy -> %s\n", (char *)hashmap_get(map, (void *)key));
	return 0;
}
