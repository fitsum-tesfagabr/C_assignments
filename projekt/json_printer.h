#ifndef JSON_PRINTER_H
#define JSON_PRINTER_H
#include "./json_data.h"
#include <stdio.h>

/* Prints JsonMember in a json format to a file. */
void json_fprint_member(FILE* f, int indent, JsonMember* m);

/* Prints JsonObject in a json format to a file. */
void json_fprint_object(FILE* f, int indent, JsonObject* o);

/* Prints JsonValue in a json format to a file. */
void json_fprint_value(FILE* f, int indent, JsonValue* v);

#endif // JSON_PRINTER_H
