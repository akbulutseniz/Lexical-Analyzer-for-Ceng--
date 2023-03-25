#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) __HadError=true;goto ExitJmp;

int identifierMax=20;
int integerMax=10;

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
        ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
        ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

bool isAlphabet(char ch)
{
	if (ch == 'a' || ch == 'b' || ch == 'c' ||ch == 'd' || ch == 'e' || ch == 'f' ||ch == 'g' 
	|| ch == 'h' || ch == 'i' ||ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' 
	|| ch == 'o' ||ch == 'p' || ch == 'r' || ch == 's' ||ch == 't' || ch == 'u' || ch == 'v' 
	||ch == 'y' || ch == 'z' || ch == 'w' || ch == 'q' || ch == 'x')
		return (true);
	return (false);
}
bool isDigit(char ch){
	if (ch == '0' || ch == '1' || ch == '2' ||ch == '3' || ch == '4' || ch == '5' ||ch == '6' || ch == '7' || ch == '8' ||ch == '9')
		return (true);
	return (false);
}

bool isvalidIdentifier(char* str){
	int i,len = strlen(str);
	if (len==0){ return(false);}
	
	if(len>identifierMax){
		printf("Error : Maximum Identifier size is 20 characters.You have exceeded the identifier max value.");
		exit(0);
	}

	if (isAlphabet(str[0]) == true){
   		for(i=1;i<len;i++){
   			if(isAlphabet(str[i]) && isDigit(str[i]) && str[i]=='_'){
   				return (false);
   				break;
			}	
		}
   }
   return (true);
}

bool isValidInteger(char* str) {
	int i, len = strlen(str);
	if (len == 0)
		return (false);
	else if(str[0]==' '){
		return (false);
	}
	if(len >integerMax){
		printf("Error : Maximum integer size is 10 digits.You have exceeded the integer max value.");
		return(false);
	}
	else
	{
		for (i = 0; i < len; i++) {
			if(str[i] == '-' && i == 0){
				printf("Error : Negative values are not supported.");
				exit(0);
			}
			if(str[i] == '-' && i > 0){
				printf("Error : The '-' character cannot be used in the integer string.");
				exit(0);
			}
			if (isDigit(str[i])==false){
					return (false);
			}
   		}
	}
   return (true);
   
}

bool isValidString(char* str){
	int len=strlen(str);
	if(len==0)
		return (false);
	int i=0;
	for(i=0;i<len;i++){
		if(!isAlphabet(str[i])==true || !isDelimiter(str[i])==true || !isDigit(str[i])==true ){
			printf("Invalid String!");
		}
	}
	return (true);
}


bool isValidOperator(char ch){
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == ':') 
		return (true);
   return (false);
}

bool isValidBracket(char ch) {
   if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
   		return (true);
   return (false);
}

bool isValidKeyword(char* str) 
{
   if (!strcmp(str, "break") || !strcmp(str, "case") || !strcmp(str, "char")
	   || !strcmp(str, "const") || !strcmp(str, "continue") || !strcmp(str, "do") 
	   || !strcmp(str, "else") || !strcmp(str, "enum") || !strcmp(str, "float")
	   || !strcmp(str, "for") || !strcmp(str, "goto") || !strcmp(str, "if") 
	   || !strcmp(str, "int") || !strcmp(str, "long") || !strcmp(str, "record")
	   || !strcmp(str, "return") || !strcmp(str, "static") || !strcmp(str, "while"))
	   return (true);
	return (false);
}
bool isValidComment(char* str){
	int len = strlen(str);
	if(str[0]=='('&& str[1]=='*' && str[len-3]=='*'&& str[len-2]==')'){
		return(true);
	}
	return(false);
}
bool isPreProcessorDirective(char* str){
	if(str[0]=='#')
		return(true);
	return(false);
}
char* subString(char* str, int left, int right) {
   int i;
   char* subStr = (char*)malloc( sizeof(char) * (right - left+2 ));
   for (i = left; i <= right; i++)
      subStr[i - left] = str[i];
   subStr[right - left + 1] = '\0';
   return (subStr);
}

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

void st(char* str,int left,int right){
	char* subStr = subString(str, left, right - 1);	
	remove_spaces(subStr);
	if(subStr[0]=='('){
		if(isValidComment(subStr)==true){
			printf("Comment:%s \n",subStr);	
		}
	}
	else if (isValidKeyword(subStr) == true){
		printf("Keyword(%s)\n",subStr);
	}
	else if (isvalidIdentifier(subStr)==true)
	{
		printf("Identifier(%s)\n",subStr);
	}
	else if (isValidInteger(subStr)==true)
	{
		printf("IntConst(%s)\n",subStr);
	}
	else if(isValidString(subStr)==true){
		printf("String(%s)\n",subStr);
	}
	
	
}

void detectTokens(char* str) {
	if(isPreProcessorDirective(str)){
   		printf("Pre Processor Directive(%s)",str );
   	}
   	else {
		int left = 0, right = 0;
		int first=0,last=0;
		int length = strlen(str);
		while (right <= length && left <= right) {
			if(str[right]==' '){
				st(str,left,right);
				right++;
				left=right;
			}
			if (isDelimiter(str[right]) == false)
            	right++;
			
			if (isValidOperator(str[right]) == true) {
		       if(str[right]==':' && str[right+1]=='='){
		       		st(str,left,right);
		            printf("Operator(:=)\n" );
		            right++;
		            left=right;
				}
				else if(str[right]=='+' && str[right+1]=='+'){
					st(str,left,right);
					printf("Operator(++)\n");
					right++;
					left=right;
				}
				else if(str[right]=='-' && str[right+1]=='-'){
					st(str,left,right);
					printf("Operator(--)\n");
					right++;
					left=right;
				}
				else if(str[right]=='*'){
					if(str[right-1]!='(' || !str[right+1]!=')'){
						st(str,left,right);
						printf("Operator(%c)\n",str[right]);
						left=right;
					}
					else{
						
					}
						
				}
				else{
					st(str,left,right);
					printf("Operator(%c)\n",str[right]);
				}
				right++;
				left=right;
		        }
			    else if(str[right]==';'){
			    	st(str,left,right);
					printf("EndOfFile\n");
					right++;
					left=right;
				}
				else if(str[right]=='"'){
						int x=right;
						while(!str[x]=='"'){
							x=x+1;
							if(x>length){
								printf("Lexical Error!\n");
								exit(0);
							}
						}
						st(str,left+1,x+1);
						right=right+x;
						left=right;	
				}
				else if(isValidBracket(str[right])==true){
					if(str[right]=='('){
						if(str[right+1]=='*'){
							int x=right;
							while(str[x]!=')'){
								x=x+1;
								if(x>length){
									printf("Lexical Error!\n");
									exit(0);
								}
							}
							st(str,left,x+2);
							right=right+x;
							left=right;	
						}
						else {
							st(str,left,right);
							printf("LeftPar\n");
							right++;
							left=right;	
						}
					}
					else if(str[right]==')'){
						if(str[right+1]=='*'){}
						else{
							st(str,left,right);
							printf("RightPar\n");
							right++;
							left=right;
						}
					}
					else if(str[right]=='{'){
						st(str,left,right);
						printf("LeftCurlyBracket\n");
						right++;
						left=right;
					}
					else if(str[right]=='}'){
						st(str,left,right);
						printf("RightCurlyBracket\n");
						right++;
						left=right;
					}
					else if(str[right]=='['){
						st(str,left,right);
						printf("LeftSquareBracket\n");
						right++;
						left=right;
					}
					else if(str[right]==']'){
						st(str,left,right);
						printf("RightSquareBracket\n");
						right++;
						left=right;
					}     						
				}
	    }
	}
}

int main(int argc, char *argv[]) {
	char a='*',next,file_name[20];
	int line=0,count=0;
	puts("Make sure that the file to be analyzed is in the same location as the source file.\n");
	puts("Analysis begins...\n");
	puts("Enter the file name:");
	scanf("%s",file_name);
	FILE *f;
	f=fopen(file_name,"r");
	if(f==NULL)
	{
		puts("\n\nThe file does not open.");
		getch();
		exit(0);
	}
	else{
		char str[1000] = "";
		puts("\nFile content is being analyzed...");
		while(a!=EOF) //dosyanýn sonuna kadar okuma yap
		{
			count++;
			a=fgetc(f); //karakter oku
			str[count-1]=a;
			if(a=='\n') //alt satýra geçme, satýr sonu karakteri mi?
			{
				line++;
				count--; //alt satýra geçiþ karakteri sayýlmýyor
				//printf("%d.satirda %d karakter var\n",line,count);
				//printf("%s",str);
				puts("\nThe row is being analyzed...\n");
				detectTokens(str);
				int i;
				for(i = 0 ; i<=count;i++)
					str[i] = ' ';
				count=0;
				next=fgetc(f);
			}
			
		}
		// alt satýra geçilmiþ ancak herhangi bir karakter girilmemiþse
		// ya da satýr sonunda alt satýra geçilmeden bitirilmiþse
		if(next!=EOF)
		{
			line++;
			//printf("%d satirda %d karakter var\n",line,count);
			//printf(" %s",str);
			puts("\nThe row is being analyzed...\n");
			detectTokens(str);
			int i;
			for(i = 0 ; i<=count;i++)
				str[i] = ' ';
			count=0;
		}
		exit(0); 
	}
}
	


