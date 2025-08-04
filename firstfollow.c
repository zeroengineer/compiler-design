#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 10
int n;
char productions[MAX][MAX];
char result[MAX];
int resultIndex = 0;
void first(char c);
void follow(char c);
void addToResult(char c);
int main() 
{
	int i, repeat;
	char target, dummy;
	printf("Enter the number of productions:\n");
	scanf("%d", &n);
	getchar();
    	printf("Enter the productions (e.g., E=TR):\n");
   	for (i = 0; i < n; i++) 
   	{
        	fgets(productions[i], MAX, stdin);
        	productions[i][strcspn(productions[i], "\n")] = '\0';
    	}
    	do 
    	{
        	resultIndex = 0;
        	memset(result, 0, sizeof(result));
       	printf("\nEnter the non-terminal to find FIRST and FOLLOW: ");
        	scanf(" %c", &target);
        	first(target);
        	printf("First(%c) = { ", target);
        	for (i = 0; i < resultIndex; i++) 
        	{
            		printf("%c ", result[i]);
        	}
        	printf("}\n");
        	resultIndex = 0;
        	memset(result, 0, sizeof(result));
        	follow(target);
        	printf("Follow(%c) = { ", target);
        	for (i = 0; i < resultIndex; i++) 
        	{
            		printf("%c ", result[i]);
        	}
        	printf("}\n");

        	printf("Continue? (1 = Yes / 0 = No): ");
       	scanf("%d", &repeat);
    	} 
    	while (repeat == 1);
    	return 0;
}
void addToResult(char c) 
{
	for (int i = 0; i < resultIndex; i++) 
  	{
    		if (result[i] == c)
            	return;
    	}
    	result[resultIndex++] = c;
}
void first(char c) 
{
    	if (!isupper(c)) 
    	{
        	addToResult(c);
        	return;
    	}
    	for (int k = 0; k < n; k++) 
    	{
        	if (productions[k][0] == c) 
        	{
            		if (productions[k][2] == '$') 
            		{
                		follow(productions[k][0]);
            		} 
            		else if (islower(productions[k][2])) 
            		{
                		addToResult(productions[k][2]);
            		} 
            		else 
            		{
                		first(productions[k][2]);
            		}
        	}
    	}
}
void follow(char c) {
    if (productions[0][0] == c) {
        addToResult('$'); 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(productions[i]); j++) {
            if (productions[i][j] == c) {
                if (productions[i][j + 1] != '\0') {
                    first(productions[i][j + 1]);
                } else if (productions[i][j + 1] == '\0' && c != productions[i][0]) {
                    follow(productions[i][0]);
                }
            }
        }
    }
}
