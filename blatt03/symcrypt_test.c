#include "../unity/unity.h"
#include "../unity/unity_internals.h"
#include "./symcrypt_lib.h"
#include <string.h>

void setUp(void) {}

void tearDown(void) {}

void test_encrypt_char_1(void) {
  TEST_ASSERT_EQUAL('O', encrypt_char('e', 'i'));
}

void test_encrypt_char_2(void) {
  TEST_ASSERT_EQUAL('f', encrypt_char('s', 'r'));
}

void test_encrypt_char_3(void) {
  TEST_ASSERT_EQUAL('e', encrypt_char('e', ' '));
}

void test_decrypt_char_1(void) {
  TEST_ASSERT_EQUAL('I', decrypt_char('3', 'i'));
}

void test_decrypt_char_2(void) {
  TEST_ASSERT_EQUAL('s', decrypt_char('f', 'r'));
}

void test_decrypt_char_3(void) {
  TEST_ASSERT_EQUAL('e', decrypt_char('e', ' '));
}

void test_encrypt_1(void) {
  char encrypted[5000];
  encrypt("I am scared of broccoli!", "ilikecats", encrypted);
  TEST_ASSERT_EQUAL(0, strcmp(encrypted, "3lKYeWEVfOQi[LcDgcMPYXOd"));
}
void test_decrypt_1(void) {
  char decrypted[5000];
  decrypt("3lKYeWEVfOQi[LcDgcMPYXOd", "ilikecats", decrypted);
  TEST_ASSERT_EQUAL(0, strcmp(decrypted, "I am scared of broccoli!"));
}

void test_encrypt_2(void) {
  char encrypted[5000];
  encrypt("I want to save my secret", "I am student", encrypted);
  TEST_ASSERT_EQUAL(0, strcmp(encrypted, "r YOnhtjTebV@ea[ysh[HXTi"));
}

void test_decrypt_2(void) {
  char decrypted[5000];
  decrypt("r YOnhtjTebV@ea[ysh[HXTi", "I am student", decrypted);
  TEST_ASSERT_EQUAL(0, strcmp(decrypted, "I want to save my secret"));
}

int main(int argc, char *argv[]) {

  UNITY_BEGIN();
  // Test for encrypt char
  RUN_TEST(test_encrypt_char_1);
  RUN_TEST(test_encrypt_char_2);
  RUN_TEST(test_encrypt_char_3);
  // Test for decrypt char
  RUN_TEST(test_decrypt_char_1);
  RUN_TEST(test_decrypt_char_2);
  RUN_TEST(test_decrypt_char_3);
  // Unit Test for encrypt
  RUN_TEST(test_encrypt_1);
  RUN_TEST(test_decrypt_1);
  RUN_TEST(test_encrypt_2);
  RUN_TEST(test_decrypt_2);
  return UNITY_END();
}
