#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int vars[50];       //vars[0] means a vars[1] means b ..... I keep values of variables in this array.
char equals[50];	//the variables at left side of equal symbols "="
char string[400]="";  //the string we read.
char postfix[400]=""; //the postfix form string that we transformed from main string.
char aracikti[400]=""; //the string to write stage outputs. 
char forstack[100]=""; //these are for write stack to end from head.
int forstack2[100]; 
int allvariables[50];  //char codes of all variables we use.

struct Stack{      //building stack
	char ch;
	int value;
	struct Stack* next;
};
struct Stack* top=NULL;

void push(char a){       //push function for stack to use in stage of transforming between infix and postfix
	if(top==NULL){
		top=(struct Stack*)malloc(sizeof(struct Stack));
		top->next=NULL;
		top->ch=a;	
	}
	else{
		struct Stack* tmp=(struct Stack*)malloc(sizeof(struct Stack));
		tmp->ch=a;
		tmp->next=top;
		top=tmp;
	}	
}
void push2(int a){       //second push function for stack to use in stage of solving postfix
	if(top==NULL){
		top=(struct Stack*)malloc(sizeof(struct Stack));
		top->next=NULL;
		top->value=a;	
	}
	else{
		struct Stack* tmp=(struct Stack*)malloc(sizeof(struct Stack));
		tmp->value=a;
		tmp->next=top;
		top=tmp;
	}	
}
char pop(){
	if(top==NULL){     //pop function for first stage
		return -1;	
	}
	else{
	char a=top->ch;
	struct Stack* tmp=top;
	top=top->next;
	free(tmp);
		return a;
	}	
}
int pop2(){
	if(top==NULL){     //pop function for second stage
		return -1;
	}
	else{
	int a=top->value;
	struct Stack* tmp=top;
	top=top->next;
	free(tmp);
		return a;
	}	
}
void stackviewer(struct Stack* a){  //viewer for stack
	printf("Stack:");
	int count=0; int i;
	if(a==NULL){
		printf("empty");
	}
	else{
		while(a!=NULL){
			forstack[count]=a->ch;
			a=a->next;
			count++;
		}
		for(i=count-1;i>=0;i--){
			printf("%c",forstack[i]);
		}
		memset(forstack, 0, sizeof(forstack));
	}
}
void stackviewer2(struct Stack* a){ //second viewer for second type stack
	printf("Stack:");
	int count=0; int i;
	if(a==NULL){
		printf("empty");
	}
	else{
		while(a!=NULL){
			forstack2[count]=a->value;
			a=a->next;
			count++;
		}
		for(i=count-1;i>=0;i--){
			printf(" %d ",forstack2[i]);
		}
		memset(forstack2, 0, sizeof(forstack2));
	}
}
int toint(char ch){   //function to transform a variable to its value. example: variable:c then function returns its value ex:7
	int tmp=ch-97;
	return vars[tmp];										
}
//I build a while loop. It is splitting the string with (;).
//There are if conditions in while. The conditions check situations and do their job.
void infixtopostfix(){   //infix to postfix 
	int i=0;    //variables for counting and keeping
	int j=0;
	int k=0;
	int x=0;
	char tmp=' ';
	while( i < (strlen(string)-1) ) {
		equals[x]=string[i];
		x++;
		i=i+4;
		k=0;
		while(string[i]!=';'){
			if(string[i]=='('){ 
				push(string[i]);
				i++;
			}
			else if(string[i]==')'){
				tmp=pop();
				while(tmp!='('){
					postfix[j]=tmp;
					aracikti[k]=tmp;
					k++;
					tmp=pop();
					j++;
				}
			}
			else if(isdigit(string[i])){
				postfix[j]=string[i];
				aracikti[k]=string[i];
				k++;
				j++;
				i++;	
			}
			else if(isalpha(string[i])){
				postfix[j]=string[i];
				aracikti[k]=string[i];
				k++;
				j++;
				i++;
			}
			else if(string[i]=='+' || string[i]=='-'){
				if(top==NULL){
					push(string[i]);
				}
				else  if(top->ch=='+' || top->ch=='-'){
					push(string[i]);
				}
				else{
					while(top->ch=='/' || top->ch=='*'){
						tmp=pop();
						postfix[j]=tmp;
						aracikti[k]=tmp;
						k++;
						j++;
					}
					push(string[i]);
				}
				i++;
			}
			else if(string[i]=='*' || string[i]=='/'){;
				push(string[i]);
				i++;
			}
			i++;
			printf("Postfix:%s ",aracikti);
			stackviewer(top);
			printf("\n");	
		}
		while(top!=NULL){
		tmp=pop();
		postfix[j]=tmp;
		aracikti[k]=tmp;
		k++;
		j++;
		printf("Postfix:%s ",aracikti);
		stackviewer(top);
		printf("\n");
		}
		postfix[j]=';';
		j++;
		i=i+2;
		printf("\nStage output:%s\n\n",aracikti);
	    memset(aracikti, 0, sizeof(aracikti));
	}
}
int numbertrans(char c){  //For using numbers in string. 
	int k=c-48;
	return k;
}
//The solving function. A loop checks if string is over or not. Then there are if conditions 
//Pushing and popping events control what result is.
void solvingpostfix(){
	char knownvars[30];
	int i=0;
	int j=0;
	int k=0;
	int n=0;
	int c;
	int a;
	int b;
	int abc;
	while(i<strlen(postfix)){
		printf("\n%c=",equals[k]);
		n=0;
		while(postfix[j]!=';'){    //this part is defining variables that we know already.
			printf("%c",postfix[j]);
			if(isalpha(postfix[j])){
				knownvars[n]=postfix[j];
				n++;
			}
			j++;
		}
		printf("   ");
		c=0;
		while(c<n){  
			printf(" %c <- %d ",knownvars[c],toint(knownvars[c]));
			c++;
		}
		memset(knownvars, 0, sizeof(knownvars));
		printf("\n");
		while(postfix[i]!=';'){     //In this loop there are if conditions that check does the character equals digit, alpha or operation symbol.
			if(isdigit(postfix[i])){
				push2(numbertrans(postfix[i]));
				stackviewer2(top);
				printf("\n");
			}
			else if(isalpha(postfix[i])){
				push2(toint(postfix[i]));
				stackviewer2(top);
				printf("\n");
			}
			else if(postfix[i]=='+'){
				a=pop2();
				b=pop2();
				b=a+b;
				push2(b);
				stackviewer2(top);
				printf("\n");
			}
			else if(postfix[i]=='-'){
				a=pop2();
				b=pop2();
				b=b-a;
				push2(b);
				stackviewer2(top);
				printf("\n");
			}
			else if(postfix[i]=='*'){
				a=pop2();
				b=pop2();
				b=a*b;
				push2(b);
				stackviewer2(top);
				printf("\n");
			}
			else if(postfix[i]=='/'){
				a=pop2();
				b=pop2();
				b=b/a;
				push2(b);
				stackviewer2(top);
				printf("\n");
			}
			i++;	
		}
		i++;
		j++;
		a=pop2();
		abc=equals[k]-97;
		vars[abc]=a;	
		printf("Result: %d\n",a);
		k++;
	}
	int t,r;
	int flag=0;
	int countt=0;
	for(t=0;t<k;t++){          //This part is for showing values of all variables.
		r=0;
		while(r<t){  
			if(equals[t]==equals[r]){
				flag=1;
			}
			r++;
		}
		if(flag==0){
			printf(" %c=%d ",equals[t],toint(equals[t]));
		}
		flag=0;
	}
}

int main() {
	int i=0;int j=0;
	char str[100];
    char *token;
    
	FILE *fp=fopen("input.txt","r");
	if(fp==NULL){
		printf("WARNING!!");
		exit(0);
	}
	while(!feof(fp)){  //Reading from file..
	fgets(str,100, fp);
	strcat(string,str);	
	}
	fclose(fp);
	printf("File read. 'input.txt'\n\n");
	printf("---INFIX TO POSTFIX---\n\n");
	infixtopostfix();
	for(i=0;i<strlen(postfix);i++){
		if(postfix[i]==';'){
			printf("\n");
		}
		else{
			printf("%c",postfix[i]);
		}
	}
	printf("\n---POSTFIX SOLVING---\n");
	solvingpostfix();
	
	fclose(fp);	
	return 0;
}
