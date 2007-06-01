#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

int main(int argc, char **argv)
{
  struct json_tokener *tok;
  struct json_object *my_string, *my_int, *my_object, *my_array;
  struct json_object *new_obj;
  int i;

  mc_set_debug(2);

  my_string = json_object_new_string("\t");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  json_object_put(my_string);

  my_string = json_object_new_string("\\");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  json_object_put(my_string);

  my_string = json_object_new_string("foo");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));

  my_int = json_object_new_int(9);
  printf("my_int=%d\n", json_object_get_int(my_int));
  printf("my_int.to_string()=%s\n", json_object_to_json_string(my_int));

  my_array = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(3));
  json_object_array_put_idx(my_array, 4, json_object_new_int(5));
  printf("my_array=\n");
  for(i=0; i < json_object_array_length(my_array); i++) {
    struct json_object *obj = json_object_array_get_idx(my_array, i);
    printf("\t[%d]=%s\n", i, json_object_to_json_string(obj));
  }
  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));    

  my_object = json_object_new_object();
  json_object_object_add(my_object, "abc", json_object_new_int(12));
  json_object_object_add(my_object, "foo", json_object_new_string("bar"));
  json_object_object_add(my_object, "bool0", json_object_new_boolean(0));
  json_object_object_add(my_object, "bool1", json_object_new_boolean(1));
  json_object_object_add(my_object, "baz", json_object_new_string("bang"));
  json_object_object_add(my_object, "baz", json_object_new_string("fark"));
  json_object_object_del(my_object, "baz");
  json_object_object_add(my_object, "arr", my_array);
  printf("my_object=\n");
  /*json_object_object_foreach(my_object, key, val) {
    printf("\t%s: %s\n", key, json_object_to_json_string(val));
  }*/
  printf("my_object.to_string()=%s\n", json_object_to_json_string(my_object));

  new_obj = json_tokener_parse("\"\003\"");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("/* hello */\"foo\"");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("// hello\n\"foo\"");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("\"\\u0041\\u0042\\u0043\"");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("null");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("True");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("12");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("12.3");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("[\"\\n\"]");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("[\"\\nabc\\n\"]");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("[null]");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("[]");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("[false]");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("[\"abc\",null,\"def\",12]");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("{}");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("{ \"foo\": \"bar\" }");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("{ \"foo\": \"bar\", \"baz\": null, \"bool0\": true }");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("{ \"foo\": [null, \"foo\"] }");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("{ \"abc\": 12, \"foo\": \"bar\", \"bool0\": false, \"bool1\": true, \"arr\": [ 1, 2, 3, null, 5 ] }");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);

  new_obj = json_tokener_parse("{ foo }");
  if(is_error(new_obj)) printf("got error as expected\n");

  new_obj = json_tokener_parse("foo");
  if(is_error(new_obj)) printf("got error as expected\n");

  new_obj = json_tokener_parse("{ \"foo");
  if(is_error(new_obj)) printf("got error as expected\n");

  /* test incremental parsing */

printf("Hello\n");
  tok = json_tokener_new();
  new_obj = json_tokener_parse_ex(tok, "{ \"foo", 6);
  if(is_error(new_obj)) printf("got error as expected\n");
  new_obj = json_tokener_parse_ex(tok, "\": {\"bar", 8);
  if(is_error(new_obj)) printf("got error as expected\n");
  new_obj = json_tokener_parse_ex(tok, "\":13}}", 6);
  printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
  json_object_put(new_obj);  
  json_tokener_free(tok);

  json_object_put(my_string);
  json_object_put(my_int);
  json_object_put(my_object);
  /*json_object_put(my_array);*/

	{
	struct json_object *laser = json_object_new_object();
	struct json_object *my_array = json_object_new_array();
	int i; for(i=0;i<20;i++) {
		json_object_array_add(my_array, 
			i%5 > 0 ? json_object_new_double(i) :
				json_tokener_parse("null")
					);
	}
	json_object_object_add(laser, "readings", my_array);

	printf("new_obj.to_string()=%s\n", json_object_to_json_string(laser));
	json_object_put(laser);
}

  return 0;
}
