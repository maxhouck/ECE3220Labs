#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
	char s[100]; //switch this to an array
	char *dyn_s;
//	int ln;
	printf("Enter the input string\n");
	fflush(stdout); //add fflush so the text displays properly
	scanf("%s",s);
//	ln = strlen(s);
	*dyn_s = (char*)malloc(strlen(s)+1);
	dyn_s = s;
	dyn_s[strlen(s)]='\0';
	printf(dyn_s);
	return 0;
}
