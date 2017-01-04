#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define ungetchar(c)  ungetc(c, stdin)    // unread char read from stdin

enum {INTE, HEXA, OCTA, BINA};
long convert(char s[], long sign, int method);
int mygetchar(void);

int mygetchar()		// like getchar(), but mygetchar() fetches the next char we "want", ignoring line splices and quotes
{
	int state = 1;	// the 1 state means we ignore and consume ch, 0 means we take the getchar()
	int ch = getchar();

	if (ch == '"'){
		while ((ch = getchar()) != '"' && (ch != EOF)){
			if (ch == '\\'){
				ch = getchar(); // get the thing after the escape character, the next iteration of the loop will consume it
			}
		}
	}

	if (ch == '\\'){	// we ignore all escaped characters
		ch = mygetchar();	//character after the escape is ignored
		ch = mygetchar();
	}

	return ch;
}

long convert(char s[], long sign, int method)
{
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
	char buffer[35]; // We're not gonna exceed 30 digits
	long total = 0;
	sign = 1;
	while ((ch = mygetchar()) != EOF)
 	{
 		if (ch == ' ' || ch == '\n' || ch == '\t' || isspace(ch)) sign = 1;	// ignore whitespace
 		if (ch == '-') sign = -1;	// keep track of the sign

 		else if (ch >= '1' && ch <= '9'){
 			printf("Found int.\n");
 			for (int i = 0; isdigit(ch); ++i){
 				buffer[i] = ch;
 				ch = mygetchar();
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
 			ch = mygetchar();
 			if (ch == 'x' || ch == 'X'){
 				printf("Hexademical found.\n");
 				ch = mygetchar();

 				for (int i = 0; isxdigit(ch); ++i){
 					buffer[i] = ch;
 					ch = mygetchar();
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
 				ch = mygetchar();

 				for (int i = 0; ch == '1' || ch == '0'; ++i){
 					buffer[i] = ch;
 					ch = mygetchar();
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
 					ch = mygetchar();
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
 				fprintf(stderr, "Fatal Error: invalid value entered.\n");
 				ungetchar(ch);
 			}
 		}
	}

	printf("Total: %ld\n", total);
}
