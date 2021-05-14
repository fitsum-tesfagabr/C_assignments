
#include "../unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

int fib_fast(int n) {
  /* The end result will be stored in a local
   * variable sothat the cache canbe freed
   * */

  if (n == 0 || n == 1) {
    return n;
  }

  int result = 0; /*fib(n) will be stored in local variable */

  /* Fibonacci series are indexed from 0, therefore,
   * n + 1 memory addresses are required to execute
   * the function.
   * */
  int *cache = malloc((n + 1) * sizeof(int));

  *cache = 0;
  *(cache + 1) = 1;

  for (int i = 2; i <= n; ++i) {
    cache[i] = cache[i - 1] + cache[i - 2];
  }

  result = cache[n];
  free(cache); /* deallocate the dynamically allocated memory space */

  return result;
}

char *repeat(size_t n, char *s) {

  size_t buff_size = n * strlen(s) + 1;

  /* The required memory size will be dynamically allocated */
  char *buffer = (char *)malloc(buff_size * sizeof(char));

  unsigned int s_position = 0; /* index of the current character in "s" */

  for (int i = 0; i < buff_size - 1; i++) {
    buffer[i] = s[s_position];
    ++s_position;
    if (s_position == strlen(s)) {
      /* the index of s will be set to first character so that it
       * can repeatedly be read from start
       * */
      int *cache = malloc((n) * sizeof(int));
      s_position = 0;
    }
  }
  /* 0 is added at the end of the string to indicate end of string*/
  buffer[buff_size - 1] = 0;
  return buffer;
}

/* This fuction uses strcat funktion from string.h to concatinate the strings*/
char *join(char **strings, size_t num_strings, char *separator) {
  /* num_concatenated_chars is initialized to one
   * because one space is required at the end of
   * any string to indicate end of string.
   */
  unsigned int num_concatenated_chars = 1;

  for (int i = 0; i < num_strings; i++) {
    num_concatenated_chars += strlen(strings[i]);
  }

  /*
   * '(num_strings - 1)*strlen(separator)' additional
   * spaces for the separator.
   */
  num_concatenated_chars += (num_strings - 1) * strlen(separator);

  char *buffer = malloc(num_concatenated_chars * sizeof(char));
  for (int i = 0; i < num_strings; i++) {
    strcat(buffer, strings[i]);
    if (i == num_strings - 1) {
      break;
    }
    strcat(buffer, separator);
  }
  buffer[num_concatenated_chars - 1] = 0;
  return buffer;
}

/* Where as this function concatenates the strings explicitly */
char *join_alternative(char **strings, size_t num_strings, char *separator) {
  /* num_concatenated_chars is initialized to one
   * because one space is required at the end of
   * any string to indicate end of string.
   */
  unsigned int num_concatenated_chars = 1;

  for (int i = 0; i < num_strings; i++) {
    num_concatenated_chars += strlen(strings[i]);
  }

  /*
   * '(num_strings - 1)*strlen(separator)' additional
   * spaces for the separator.
   */
  num_concatenated_chars += (num_strings - 1) * strlen(separator);

  char *buffer = malloc(num_concatenated_chars * sizeof(char));

  buffer[0] = 0; /* the aim is to set the length of buffer to 0 temporarily */

  /*
   * i - strings index to read each string everytime
   * j - buffer index, usefull when concatinating
   * k - string index from the strings array
   * x - separator index*
   */
  for (int i = 0; i < num_strings; i++) {
    char *s = strings[i];

    /* Since the strings are concatenated buff_length musst be initialized to
     * the next free space.
     */
    int j = strlen(buffer);

    /* k is used to index the string to be concatenated. Therefore, new string
     * is indexed starting from 0
     */
    int k = 0;

    /*string after string are concatenated to buffer*/
    for (j, k; k < strlen(s); j++, k++) {
      buffer[j] = s[k];
    }
    int x = 0;

    /* the separator will be concatenated after the string is added to buffer */
    for (x; x < strlen(separator); x++) {
      if (i < num_strings - 1) {
        buffer[j + x] = separator[x];
      }
    }

    /* It addes 0 everitime we iterate through the strings and conatenate
     * them with the separator.
     *
     * if but the last string is concatenated the end of string indicator,
     * 0 must be placed after the last string is concatenated
     */
    if (i < num_strings - 1) {
      buffer[j + x] = 0; /* end of string indicator */
    } else {
      buffer[j] = 0;
    }
  }

  return buffer;
}

char *find_quoted(char *s) {

  unsigned int num_quotes = 0;
  /* stores the first and second appearances of a quote*/
  int quote_index[2] = {0};

  for (int i = 0; i < strlen(s); i++) {
    // Check for first appearance of quote
    if (s[i] == 34 && num_quotes == 0) { /* 34 is ASCII equivalent of \" */
      quote_index[0] = i;
      num_quotes++;
    }
    // Check for the second appearance of quote, if true break loop
    else if (s[i] == 34) {
      quote_index[1] = i;
      num_quotes++;
      break;
    }
  }

  // return the quoted string if found any
  if (num_quotes == 2) {

    size_t buff_size = quote_index[1] - quote_index[0];
    char *buffer = malloc(buff_size * sizeof(char));

    /*Temporary identifiers.*/
    int i, j;
    for (i = quote_index[0], j = 0; i < quote_index[1] - 1; i++, j++) {
      buffer[j] = s[i + 1];
    }

    buffer[buff_size] = 0;
    return buffer;
  }
  // return NULL if ther is no string found bounded by double quotes
  else {
    return NULL;
  }
}

void test_fib_fast_0(void) { TEST_ASSERT_EQUAL_INT(0, fib_fast(0)); }

void test_fib_fast_1(void) { TEST_ASSERT_EQUAL_INT(1, fib_fast(1)); }

void test_fib_fast_15(void) { TEST_ASSERT_EQUAL_INT(610, fib_fast(15)); }

void test_repeat_foo_3_times(void) {
  char *s = "fool";
  char *result = repeat(3, s);
  TEST_ASSERT_EQUAL_INT(0, strcmp("foolfoolfool", result));
  free(result); /* Freed the allocated memory in function repeat*/
}

void test_repeat_cpp_5_times(void) {
  char *s = "cpp";
  char *result = repeat(5, s);
  TEST_ASSERT_EQUAL_STRING("cppcppcppcppcpp", result);
  free(result); /* Freed the allocated memory in function repeat*/
}

void test_join_1(void) {
  char *strings[] = {"Help!", "I'm split into", "multiple", "strings!"};
  char *result = join(strings, 4, " * ");
  TEST_ASSERT_EQUAL(
      0, strcmp("Help! * I'm split into * multiple * strings!", result));
  free(result); /* Freed the allocated memory in function join*/
}

void test_join_alternative_1(void) {
  char *strings[] = {"Welcome", "to", "C", "Programming", "2021!"};
  char *result = join_alternative(strings, 5, " - ");
  TEST_ASSERT_EQUAL_STRING("Welcome - to - C - Programming - 2021!", result);
  free(result); /* Freed the allocated memory in function join_alternative*/
}

void test_join_2(void) {
  char *strings[] = {"Welcome", "to", "C", "Programming", "2021!"};
  char *result = join(strings, 4, " ");
  TEST_ASSERT_EQUAL_STRING("Welcome to C Programming", result);
  free(result); /* Freed the allocated memory in function join*/
}
void test_join_3(void) {
	  char *strings[] = {"Help!", "I'm split into", "multiple", "strings!"};
	    char *result = join(strings, 4, " * ");
	      TEST_ASSERT_EQUAL(
			            0, strcmp("Help! * I'm split into * multiple * strings!", result));
	        free(result); /* Freed the allocated memory in function join*/
}

void test_find_quoted_1(void) {
  char *s1 = find_quoted("foo \"bar baz \" \"boo");
  TEST_ASSERT_EQUAL_STRING("bar baz ", s1);
  free(s1); /* Freed the allocated memory in function find_quoted */
}

void test_find_quoted_2(void) {
  char *s2 = find_quoted("foo \"bar baz boo");
  TEST_ASSERT_EQUAL(NULL, s2);
  free(s2); /* Freed the allocated memory in function find_quoted */
}

void test_find_quoted_3(void) {
  char *s3 = find_quoted("foo \"bar baz boo");
  TEST_ASSERT_EQUAL(NULL, s3);
  free(s3); /* Freed the allocated memory in function find_quoted */
}

int main(void) {

  UNITY_BEGIN();

  RUN_TEST(test_fib_fast_0);
  RUN_TEST(test_fib_fast_1);
  RUN_TEST(test_fib_fast_15);

  RUN_TEST(test_repeat_foo_3_times);
  RUN_TEST(test_repeat_cpp_5_times);
  RUN_TEST(test_join_1);
  RUN_TEST(test_join_alternative_1);
  RUN_TEST(test_join_2);
  RUN_TEST(test_join_3);

  RUN_TEST(test_find_quoted_1);
  RUN_TEST(test_find_quoted_2);
  RUN_TEST(test_find_quoted_3);
  return UNITY_END();
}
