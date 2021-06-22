#include <stdio.h>
#include "./json_printer.h"

void fprint_indent(FILE* f, int indent) {
  for (int i = 0; i < indent; ++i) {
    fprintf(f, " ");
  }
}

void json_fprint_member(FILE* f, int indent, JsonMember* m) {
  fprint_indent(f, indent);
  fprintf(f, "\"%s\": ", json_member_name(m));
  json_fprint_value(f, indent, json_member_value(m));
}

void json_fprint_members(FILE* f, int indent, Vec* ms) {
  for (size_t i = 0; i < vec_length(ms); ++i) {
    JsonMember* m = *vec_at(ms, i);
    json_fprint_member(f, indent, m);
    if (i < vec_length(ms) - 1) {
      fprintf(f, ",\n");
    }
  }
}

void json_fprint_object(FILE* f, int indent, JsonObject* o) {
  fprintf(f, "{\n");
  json_fprint_members(f, indent + 2, json_object_members(o));
  fprintf(f, "\n");
  fprint_indent(f, indent);
  fprintf(f, "}");
}

void json_fprint_value(FILE* f, int indent, JsonValue* v) {
  switch (json_value_type(v)) {
    case JSON_NUMBER:
      fprintf(f, "%d", json_value_as_number(v));
      break;
    case JSON_STRING:
      fprintf(f, "\"%s\"", json_value_as_string(v));
      break;
    case JSON_OBJECT:
      json_fprint_object(f, indent, json_value_as_object(v));
      break;
  }
}
