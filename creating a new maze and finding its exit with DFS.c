#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 30 
char matris[MAX][MAX];
int i,j,a,n;
int stop;
struct Stack{      //stack i oluþturuyorum
	int a;
	int b;
	struct Stack* next;
};
struct Stack* top=NULL;

void push(int x,int y){       //stack in push fonksiyonu
	if(top==NULL){
		top=(struct Stack*)malloc(sizeof(struct Stack));
		top->next=NULL;
		top->a=x;    //stackteki her bir node iki deðer tutacak, bunlar root hücresinin satýr ve sütun deðerleri olacak
		top->b=y;	
	}
	else{
		struct Stack* tmp=(struct Stack*)malloc(sizeof(struct Stack));
		tmp->a=x;
		tmp->b=y;
		tmp->next=top;
		top=tmp;
	}	
}
int pop(){
	if(top->next==NULL){     //stack in pop fonksiyonu
		return -1;
	}
	else{
	struct Stack* tmp=top;
	top=top->next;
	free(tmp);
		return 1;
	}	
}
void print(int n){              //labirenti yazdýrmak için fonksiyon
	for(i=0 ; i<((2*n)+1); i++){
		for(j=0 ; j < ((2*n)+1); j++){
			printf("%c ",matris[i][j]);
		}
		printf("\n");
	}
}



void dfs(){
		if(stop==0){
	if(matris[(top->a)-2][(top->b)]=='B' && matris[(top->a)-1][(top->b)]==' '){  //yukarý hücre boþ mu ve arada hücre var mý diye kontrol
		matris[(top->a)-2][(top->b)]='I';
		if(((top->a)-2)==((n*2)-1) && (top->b)==((n*2)-1)){
			stop=1;
			printf("YOL BULUNDU!!");
		}
		print(n);
		printf("\n");
		push((top->a)-2,(top->b));
		dfs();
	}
	//print(n);
	}
	if(stop==0){

	if(matris[(top->a)][(top->b)+2]=='B' && matris[(top->a)][(top->b)+1]==' '){
		matris[(top->a)][(top->b)+2]='I';
		if((top->a)==((n*2)-1) && ((top->b)+2)==((n*2)-1)){     //sað hücre boþ mu ve arada duvar var mý diye kontrol ediyoruz
			stop=1;
			printf("YOL BULUNDU!!");
		}
		print(n);
		printf("\n");
		push((top->a),(top->b)+2);
		dfs();
	}
	//print(n);
	}

	if(stop==0){
	if(matris[(top->a)+2][(top->b)]=='B' && matris[(top->a)+1][(top->b)]==' '){ //aþþaðý hücre boþ mu ve arada hücre var mý diye kontrol ediyoruz
		matris[(top->a)+2][(top->b)]='I';
		if(((top->a)+2)==((n*2)-1) && (top->b)==((n*2)-1)){
			stop=1;
			printf("YOL BULUNDU!!");
		}
		print(n);
		printf("\n");
		push((top->a)+2,(top->b));
		dfs();
	}
	//print(n);
	}

	if(stop==0){
	if(matris[(top->a)][(top->b)-2]=='B' && matris[(top->a)][(top->b)-1]==' '){  //sol hücre boþ mu ve arada hücre var mý diye kontrol ediyoruz
		matris[(top->a)][(top->b)-2]='I';
		if((top->a)==((n*2)-1) && ((top->b)-2)==((n*2)-1)){
			stop=1;
			printf("YOL BULUNDU!!");
		}
		print(n);
		printf("\n");
		push((top->a),(top->b)-2);
		dfs();
	}
	//print(n);
	}
	if(stop==0){   
	matris[top->a][top->b]='B';
	a=pop();
	if(a<0){         //durdurmak için stop un 1 olmasý gerekiyor.
		stop=1;
		printf("\nLabirentte uygun yol bulunamadi...");
	}
	}
}

	


void main() {
	
	
	
	printf("n kac olsun?:");
	scanf("%d",&n);
	int random;
	stop=0;
	srand(time(NULL));                    //random labirent oluþturdum.
	for(i=0;i<((2*n)+1);i++){
		for(j=0;j<((2*n)+1);j++){
			if(i%2==1 && j%2==1){
				matris[i][j]='B';
			}
			else if(i%2==0 && j%2==0){
				matris[i][j]='+';
			}
			else if((i==0||i==(2*n)) && j%2==1){
				matris[i][j]='-';
			}
			else if((j==0||j==(2*n)) && i%2==1){
				matris[i][j]='|';
			}
			else if(i%2==1){
				random=rand()%3;
				if(random==1){
					matris[i][j]='|';
				}
				else{
					matris[i][j]=' ';
				}
			}
			else{
				random=rand()%3;
				if(random==1){
					matris[i][j]='-';
				}
				else{
					matris[i][j]=' ';
				}
			}
		}
	}
	/*matris[1][2]=' ';
	matris[1][4]='|';
	matris[1][6]=' ';
	matris[1][8]='|';
	matris[2][1]='-';
	matris[2][3]=' ';
	matris[2][5]=' ';
	matris[2][7]='-';
	matris[2][9]='-';
	matris[3][2]='|';
	matris[3][4]=' ';
	matris[3][6]='|';
	matris[3][8]=' ';
	matris[4][1]=' ';
	matris[4][3]='-';
	matris[4][5]='-';
	matris[4][7]=' ';
	matris[4][9]='-';
	matris[5][2]=' ';
	matris[5][4]='|';
	matris[5][6]=' ';
	matris[5][8]='|';
	matris[6][1]='-';
	matris[6][3]=' ';
	matris[6][5]=' ';
	matris[6][7]='-';
	matris[6][9]=' ';
	matris[7][2]='|';
	matris[7][4]='|';
	matris[7][6]=' ';
	matris[7][8]=' ';
	matris[8][1]=' ';
	matris[8][3]='-';
	matris[8][5]='-';
	matris[8][7]='-';
	matris[8][9]=' ';
	matris[9][2]='|';
	matris[9][4]='|';
	matris[9][6]='|';
	matris[9][8]='|';
*/
	
	
	print(n);
	printf("\n");
	matris[1][1]='I';
	push(1,1);
	dfs();
	matris[1][1]='*';
	matris[2*n-1][2*n-1]='X';
	printf("\n\n");
	print(n);

}
