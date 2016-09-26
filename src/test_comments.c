#include "hashmap.h"

#include "minunit.h" // <------- this is the very tiny testing framework

#include <stdio.h>
#include <string.h>



 int tests_run = 0;


 static char * test_hash() {
     mu_assert("error, gaurav didn't hash correctly!", djb2("gaurav") == 3457928); //or whatever actual number
     mu_assert("error, empty string didn't hash correctly!", djb2("") == 0); //think about edgecases!
     return 0;
 }


 static char * test_add_get_has() {
     hashmap map = new_hashmap(&djb2, "string", "string");
     //edge cases! know what you expect to happen for empty maps!
     mu_assert("error, empty hashmap, has failed!", !hashmap_has("gaurav"));
     mu_assert("error, empty hashmap, get failed!", hashmap_get("gaurav")==NULL);

     char * key, *value;
     key = "gaurav";
     value = "gautam";
     hashmap_add(map, (void *)key, (void *)value);
     mu_assert("error, hashmap didn't add, key: gaurav, value: gautam, correctly!", hashmap_has("gaurav"));
     mu_assert("error, hashmap didn't add, key: gaurav, value: gautam, correctly!", hashmap_get("gaurav") == "gautam");

     key = "chakravarthy";
     value = "gopi";
     hashmap_add(map, (void *)key, (void *)value);
     mu_assert("error, hashmap didn't add, key: chakravarthy, value: gopi, correctly!", hashmap_has("chakravarthy"));
     mu_assert("error, hashmap didn't add, key: chakravarthy, value: gopi, correctly!", hashmap_get("chakravarthy") == "gopi");

     key = "annie";
     value = "cherkaev";
     hashmap_add(map, (void *)key, (void *)value);
     mu_assert("error, hashmap didn't add, key: annie, value: cherkaev, correctly!", hashmap_has("annie"));
     mu_assert("error, hashmap didn't add, key: annie, value: cherkaev, correctly!", hashmap_get("annie") == "cherkaev");

     //check keys we didn't add
     key = "peter";
     value = "norvig"; // no add!
     mu_assert("error, hashmap didn't add, key: annie, value: cherkaev, correctly!", !hashmap_has("peter"));
     mu_assert("error, hashmap didn't add, key: annie, value: cherkaev, correctly!", hashmap_get("peter") == NULL);

     return 0;
 }



 static char * all_tests() {
     mu_run_test(test_hash);
     mu_run_test(test_add_get_has);
     return 0;
 }

 int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);

     return result != 0;
 }
