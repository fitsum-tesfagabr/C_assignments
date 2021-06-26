#ifndef JSON_READER_H_
#define JSON_READER_H_

#include "json_data.h"
#include "stdbool.h"
#include "stdlib.h"

typedef struct reader reader;

reader* make_reader(const char* stuff);

JsonValue* parse_json(reader* input);
JsonValue* parse_element(reader* input);
JsonValue* parse_value(reader* input);
JsonValue* parse_object(reader* input);
JsonMember* parse_member(reader* input);
JsonValue* parse_string(reader* input);
JsonValue* parse_number(reader* input, int sign);
JsonValue* parse_array(reader* input);
JsonValue* parse_token(reader* input);

#endif
