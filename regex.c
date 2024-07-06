#include<stdio.h>
// Importing the POSIX regex library
#include <regex.h> 
void print_result(int return_value) {
  if (return_value == 0){
    printf("Pattern found.\n");
  }
  else if (return_value == REG_NOMATCH){
    printf("Pattern not found.\n");
  }
  else {
    printf("An error occured.\n");
  }
}

int social_security_number_check(char str[]) {
  regex_t regex;
  int return_value = regcomp(&regex,"[0-9]{3}-[0-9]{2}-[0-9]{4}", REG_EXTENDED);
  return_value = regexec(&regex, str, 0, NULL, 0);

  if (return_value == 0) {
    print_result(return_value);
    return 0;
  }

  return_value = regcomp(&regex,"([0-9]){9}", REG_EXTENDED);
  return_value = regexec(&regex, str, 0, NULL, 0);
  if (return_value == 0) {
    print_result(return_value);
    return 0;
  }
  
  print_result(return_value);
  return 0;
}

int credit_card_number_check(char str[]) {
  regex_t regex;
  int return_value = regcomp(&regex, "[0-9]{4}-[0-9]{4}-[0-9]{4}-[0-9]{4}", REG_EXTENDED);
  return_value = regexec(&regex, str, 0, NULL, 0);

  if (return_value == 0) {
    print_result(return_value);
    return 0;
  }

  return_value = regcomp(&regex, "[0-9]{16}", REG_EXTENDED);
  return_value = regexec(&regex, str, 0, NULL, 0);
  if (return_value == 0) {
    print_result(return_value);
    return 0;
  }
  print_result(return_value);
  return 0;
}

int aws_access_key_id_check(char str[]) {
  regex_t regex;
  int return_value = regcomp(&regex, "[ASIA|AKIA|AROA|AIDA][A-Z0-7]{16}", REG_EXTENDED);
  return_value = regexec(&regex, str, 0, NULL, 0);
  if (return_value == 0) {
    print_result(return_value);
    return 0;
  }
  print_result(return_value);
  return 0;
}

int main() {
  char choice;
  char input_string[80];
  printf("What sensitive data type do you want me to look for? Type:\n");
  printf("  '1' for Credit Card Numbers\n  '2' for Social Security Numbers\n");
  printf("  '3' for AWS Access Key IDs\n");
  scanf("%c", &choice);
  printf("\nWhat's the text you want me to search through?\n");
  scanf("%s", input_string);
  if (choice == '1') {
    credit_card_number_check(input_string);
  } else if (choice == '2') {
    social_security_number_check(input_string);
  } else if (choice == '3') {
    aws_access_key_id_check(input_string);
  }
  
  return 0;
}