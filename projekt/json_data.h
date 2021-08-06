#ifndef JSON_DATA_H_
#define JSON_DATA_H_

#include "./vec.h"

typedef struct JsonObject JsonObject;
typedef struct JsonMember JsonMember;
typedef struct JsonValue JsonValue;

/* JsonValue Datastructure */
typedef enum JsonValueType {
  JSON_NUMBER,
  JSON_STRING,
  JSON_OBJECT
} JsonValueType;

/* Create Json object from a vector of memebers. */
JsonObject* json_object_new(Vec* ms);

/* Returns the Members of JsonObject */
Vec* json_object_members(JsonObject* o);

/* Find the value of a member in a given object */
JsonValue* json_object_find(JsonObject* o, const char* name);

/* Deallocate JsonObject. */
void json_object_free(JsonObject* o);

/* Create new Json Member with name and value. */
JsonMember* json_member_new(char* name, JsonValue* value);

/* Return the name of the memeber. */
char* json_member_name(JsonMember* m);

/* Return the value of a memeber. */
JsonValue* json_member_value(JsonMember* m);

/* Deallocate JsonMember. */
void json_member_free(JsonMember* m);

/* Create Json value if the value is a string. */
JsonValue* json_value_new_string(char* s);

/* Create Json value if the value is a number.
 * It accepts a double value so that it can store any number.. */
JsonValue* json_value_new_number(double i);

/* Create Json value if the value is a JsonObject. */
JsonValue* json_value_new_object(JsonObject* o);

/* Deallocate Json Value. */
void json_value_free(JsonValue* v);

/* Returns the type of the JsonValue. It can be either a strign, a number, or an
 * objcet. */
JsonValueType json_value_type(JsonValue* v);

/* Returns a string, if the type of the JsonValue is a string. */
char* json_value_as_string(JsonValue* v);

/* Returns a number, if the type of the JsonValue is a number. */
double json_value_as_number(JsonValue* v);

/* Returns a JsonObject, if the type of the JsonValue is a JsonObject. */
JsonObject* json_value_as_object(JsonValue* v);

#endif // JSON_DATA_H_
