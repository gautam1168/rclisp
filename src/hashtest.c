#include "hashmap.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char * st = "gaurav";
	hashmap map = new_hashmap(&djb2, "string", "string");
	printf("key: gaurav \nhashed key: %ld\n", djb2("gaurav"));
	
	char * key, *value;
	key = "gaurav";
	value = "gautam";
	add(map, (void *)key, (void *)value);

	key = "chakravarthy";
	value = "gopi";
	add(map, (void *)key, (void *)value);

	key = "annie";
	value = "cherkaev";
	add(map, (void *)key, (void *)value);

	print(map);
	return 0;
}
