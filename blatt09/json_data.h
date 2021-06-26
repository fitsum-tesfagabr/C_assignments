#ifndef JSON_DATA_H_
#define JSON_DATA_H_

#include "./vec.h"

typedef struct JsonObject JsonObject;
typedef struct JsonMember JsonMember;
typedef struct JsonValue JsonValue;

typedef enum JsonValueType {
  JSON_NUMBER,
  JSON_STRING,
  JSON_OBJECT
} JsonValueType;

JsonObject* json_object_new(Vec* ms);
Vec* json_object_members(JsonObject* o);
JsonValue* json_object_find(JsonObject* o, const char* name);
void json_object_free(JsonObject* o);

JsonMember* json_member_new(char* name, JsonValue* value);
char* json_member_name(JsonMember* m);
JsonValue* json_member_value(JsonMember* m);
void json_member_free(JsonMember* m);

JsonValue* json_value_new_string(char* s);
JsonValue* json_value_new_number(int i);
JsonValue* json_value_new_object(JsonObject* o);
void json_value_free(JsonValue* v);
JsonValueType json_value_type(JsonValue* v);
char* json_value_as_string(JsonValue* v);
int json_value_as_number(JsonValue* v);
JsonObject* json_value_as_object(JsonValue* v);

#endif // JSON_DATA_H_
