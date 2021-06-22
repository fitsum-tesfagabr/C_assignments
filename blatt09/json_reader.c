#include "ctype.h"
#include "json_reader.h"
#include "memtools.h"
#include "string.h"
#include "stdio.h"
#include "json_data.h"
#include "vec.h"

#define malloc_or_die malloc_or_exit

typedef struct reader {
  const char *p;
} reader;

reader *make_reader(const char *stuff) {
  reader *input = malloc_or_die(sizeof(struct reader));
  input->p = stuff;
  return input;
}

/* advance input */
reader *next(reader *input) {
  input->p++;
  return input;
}

#define peek(input) (*(input)->p)

void skipws(reader *input) {
  while (isspace(peek(input))) {
    next(input);
  }
}

/* check for character and advance if found */
bool expect(reader *input, char c) {
  if (peek(input) == c) {
    next(input);
    return true;
  } else {
    return false;
  }
}

JsonValue *parse_array(reader *input) {
  return NULL;
}

JsonValue *parse_token(reader *input) {
  while (isalpha(peek(input))) {
    next(input);
  }
  return NULL;
}

JsonValue *parse_number(reader *input, int sign) {
  const char *start = input->p;
  while (isdigit(peek(input))) {
    next(input);
  }
  int r;
  sscanf(start, "%d", &r);
  return json_value_new_number(r * sign);
}

JsonValue *parse_string(reader *input)  {
  expect(input, '"');
  const char *start = input->p;
  while (peek(input) != '"') {
    next(input);
  }
  const char *stop = input->p;
  size_t len = stop - start;
  char *r_string = malloc_or_die(len+1);
  memcpy(r_string, start, len);
  r_string[len] = 0;
  expect(input, '"');
  return json_value_new_string(r_string);
}

JsonMember *parse_member(reader *input) {
  skipws(input);
  JsonValue *key = parse_string(input);
  if (key == NULL) {return NULL;}
  skipws(input);
  if (!expect(input, ':')) { return NULL; }
  JsonValue *value = parse_element(input);
  JsonMember *r = json_member_new(json_value_as_string(key), value);
  free(key);
  return r;
}

JsonValue *parse_object(reader *input) {
  Vec *ms = vec_new();
  skipws(input);
  if (expect(input, '}')) {
    return json_value_new_object(json_object_new(ms)); /* empty object found */
  }
  do {
    JsonMember *m = parse_member(input);
    if (m == NULL) {
      /* nasty free vector elements */
      for (size_t i=0; i < vec_length(ms); i++) {
        json_member_free(*vec_at(ms, i));
      }
      vec_free(ms);
      return NULL;
    }
    vec_push(ms, m);
  } while (expect(input, ','));
  expect(input, '}');
  return json_value_new_object(json_object_new(ms));
}

JsonValue *parse_value(reader *input) {
  if (expect(input, '{')) {
    return parse_object(input);
  } else if (expect(input, '[')) {
    return parse_array(input);
  } else if (peek(input) == '"') {
    return parse_string(input);
  } else if (expect(input, '-')) {
    return parse_number(input, -1);
  } else if (isdigit(peek(input))) {
    return parse_number(input, 1);
  } else if (isalpha(peek(input))) {
    return parse_token(input);
  } else {            /* nothing fits */
    return NULL;        /* syntax error */
  }
}

JsonValue *parse_element(reader *input) {
  skipws(input);
  JsonValue *r = parse_value(input);
  skipws(input);
  return r;
}

JsonValue *parse_json(reader *input) {
  JsonValue *r = parse_element(input);
  if (r == NULL || peek(input)) {
    if (r == NULL) {
      json_value_free(r);
    }
    return NULL;
  }
  return r;
}
