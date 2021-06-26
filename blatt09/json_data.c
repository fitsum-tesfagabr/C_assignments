// Copyright 2019 University of Freiburg
// Author: Peter Thiemann <thiemann@informatik.uni-freiburg.de>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./json_data.h"
#include "./memtools.h"

// Data Structures /////////////////////////////////////////////////////////////

struct JsonObject {
  Vec* members;
};

struct JsonMember {
  char* name;
  JsonValue* value;
};

struct JsonValue {
  JsonValueType type;
  union {
    int as_number;
    char* as_string;
    JsonObject* as_object;
  } value;
};

// JsonObject //////////////////////////////////////////////////////////////////

JsonObject* json_object_new(Vec* members) {
  JsonObject* o = malloc_or_exit(sizeof(JsonObject));
  o->members = members;
  return o;
}

Vec* json_object_members(JsonObject* o) {
  return o->members;
}

JsonValue* json_object_find(JsonObject* o, const char* name) {
  for (size_t i = 0; i < vec_length(o->members); ++i) {
    JsonMember* member = *vec_at(o->members, i);
    if (strcmp(name, member->name) == 0) {
      return member->value;
    }
  }
  return NULL;
}

void json_object_free(JsonObject* o) {
  for (size_t i = 0; i < vec_length(o->members); ++i) {
    JsonMember* member = *vec_at(o->members, i);
    json_member_free(member);
  }
  vec_free(o->members);
  free(o);
}

// JsonMember //////////////////////////////////////////////////////////////////

// assume that name and value are safe to share
JsonMember* json_member_new(char* name, JsonValue* value) {
  JsonMember* m = malloc_or_exit(sizeof(JsonMember));
  m->name = name;
  m->value = value;
  return m;
}

char* json_member_name(JsonMember* m) {
  return m->name;
}

JsonValue* json_member_value(JsonMember* m) {
  return m->value;
}

void json_member_free(JsonMember* m) {
  free(m->name);
  json_value_free(m->value);
  free(m);
}

// JsonValue ///////////////////////////////////////////////////////////////////

JsonValue* json_value_new_string(char* s) {
  JsonValue* v = malloc_or_exit(sizeof(JsonValue));
  v->type = JSON_STRING;
  v->value.as_string = s;
  return v;
}

JsonValue* json_value_new_number(int i) {
  JsonValue* v = malloc_or_exit(sizeof(JsonValue));
  v->type = JSON_NUMBER;
  v->value.as_number = i;
  return v;
}

JsonValue* json_value_new_object(JsonObject* o) {
  JsonValue* v = malloc_or_exit(sizeof(JsonValue));
  v->type = JSON_OBJECT;
  v->value.as_object = o;
  return v;
}

void json_value_free(JsonValue* v) {
  switch (v->type) {
  case JSON_NUMBER:
    break;
  case JSON_STRING:
    free(v->value.as_string);
    break;
  case JSON_OBJECT:
    json_object_free(v->value.as_object);
    break;
  }
  free(v);
}

JsonValueType json_value_type(JsonValue* v) {
  return v->type;
}

char* json_value_as_string(JsonValue* v) {
  return v->value.as_string;
}

int json_value_as_number(JsonValue* v) {
  return v->value.as_number;
}

JsonObject* json_value_as_object(JsonValue* v) {
  return v->value.as_object;
}
