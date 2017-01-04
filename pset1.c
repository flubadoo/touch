#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define ungetchar(c)  ungetc(c, stdin)    // unread char read from stdin
#define IN 1
#define OUT 0
enum {INTE, HEXA, OCTA, BINA};
long convert(char s[], long sign, int method);

long convert(char s[], long sign, int method){
	if (method == INTE)
		return sign*strtol(s, NULL, 10);
	else if (method == HEXA)
		return sign*strtol(s, NULL, 16);
	else if (method == OCTA)
		return sign*strtol(s, NULL, 8);
	else
		return sign*strtol(s, NULL, 2);
}

int main(void) {
	int ch, state, nn, sign;
	char prefix[2];
	char buffer[35]; //We're not gonna exceed 30 digits
	long total = 0;
	sign = 1;
	while ((ch = getchar()) != EOF)
 	{
 		if (ch == ' ' || ch == '\n' || ch == '\t' || isspace(ch)) sign = 1;
 		if (ch == '-') sign = -1;

 		else if (ch >= '1' && ch <= '9'){
 			printf("Found int.\n");
 			for (int i = 0; isdigit(ch); ++i){
 				buffer[i] = ch;
 				ch = getchar();
 				if (isdigit(ch) == 0){
 					ungetchar(ch);
 					printf("Finished reading int.\n");
 					total += convert(buffer, sign, INTE);
 					memset(buffer, ' ', sizeof(buffer));
 					printf("%ld\n", total);
 					break;
 				}
 			}

 		} else if (ch == '0') {
 			ch = getchar();
 			if (ch == 'x' || ch == 'X'){
 				printf("Hexademical found.\n");
 				ch = getchar();

 				for (int i = 0; isxdigit(ch); ++i){
 					buffer[i] = ch;
 					ch = getchar();
 					if (isxdigit(ch) == 0){
 						ungetchar(ch);
 						printf("Finished reading hex.\n");
 						total += convert(buffer, sign, HEXA);
 						memset(buffer, ' ', sizeof(buffer));
 						printf("%ld\n", total);
 						break;
 					}
 				}

 			} else if (ch == 'B' || ch == 'b'){
 				printf("Binary found.\n");
 				ch = getchar();

 				for (int i = 0; ch == '1' || ch == '0'; ++i){
 					buffer[i] = ch;
 					ch = getchar();
 					if (isdigit(ch) == 0){
 						ungetchar(ch);
 						printf("Finished reading binary.\n");
 						total += convert(buffer, sign, BINA);
 						memset(buffer, ' ', sizeof(buffer));
 						printf("%ld\n", total);
 						break;
 					}
 				}

 			} else if (ch >= '1' || ch <= '9'){
 				printf("Octal found.\n");

 				for (int i = 0; isxdigit(ch); ++i){
 					buffer[i] = ch;
 					ch = getchar();
 					if (isdigit(ch) == 0){
 						ungetchar(ch);
 						printf("Finished reading octal.\n");
 						total += convert(buffer, sign, OCTA);
 						memset(buffer, ' ', sizeof(buffer));
 						printf("%ld\n", total);
 						break;
 					}
 					
 				}

 			} else {
 				ungetchar(ch);
 			}
 		}
	}

	printf("Total: %ld\n", total);
}