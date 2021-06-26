#ifndef JSON_PRINTER_H
#define JSON_PRINTER_H
#include "./json_data.h"
#include <stdio.h>

void json_fprint_member(FILE* f, int indent, JsonMember* m);
void json_fprint_object(FILE* f, int indent, JsonObject* o);
void json_fprint_value(FILE* f, int indent, JsonValue* v);

#endif // JSON_PRINTER_H
