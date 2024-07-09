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

void aws_access_key_id_check(char str[]) {
  regex_t regex;
  int return_value = regcomp(&regex, "[ASIA|AKIA|AROA|AIDA][A-Z0-7]{16}", REG_EXTENDED);
  return_value = regexec(&regex, str, 0, NULL, 0);
  if (return_value == 0) {
    print_result(return_value);
  }
  print_result(return_value);
}

int main() {
  //sensitive_data_choice is the type of sensitive data you want to look for.
  char sensitive_data_choice;
  char input_string[80];
  char input_choice;
  FILE* file = fopen("./testfile.txt", "r");
  char line[256];

  printf("How do you want to supply the input?");
  printf("  '1' for File in same directory\n  '2' for stdin input\n");
  scanf("%c", &input_choice);
  printf("What sensitive data type do you want me to look for? Type:\n");
  printf("  '1' for Credit Card Numbers\n  '2' for Social Security Numbers\n");
  printf("  '3' for AWS Access Key IDs\n");
  scanf(" %c", &sensitive_data_choice);
  
  if (input_choice == '1') {
    if (file != NULL) {
      // Read each line from the file and store it in the
      // 'line' buffer.
      while (fgets(line, sizeof(line), file)) {
        // Print each line to the standard output.
        //printf("%s", line);
        credit_card_number_check(line);
      }

      // Close the file stream once all lines have been
      // read.
      fclose(file);
    }
    else {
      // Print an error message to the standard error
      // stream if the file cannot be opened.
      fprintf(stderr, "Unable to open file!\n");
    }

  } else if (input_choice == '2') {
    printf("\nWhat's the text you want me to search through?\n");
    scanf("%s", input_string);
    if (sensitive_data_choice == '1') {
        credit_card_number_check(input_string);
    } else if (sensitive_data_choice == '2') {
        social_security_number_check(input_string);
    } else if (sensitive_data_choice == '3') {
        aws_access_key_id_check(input_string);
    }
  }
  
  return 0;
}