#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 500

int matris[50][50];
typedef struct Edge{  //kenarlar için veri yapısı
	int a,b,w;
}edge;
typedef struct EdgeList{//kenarların listesi için veri yapısı
	edge data[MAX];
	int n;
}edgelist;
edgelist elist;

void sort(){ //kenarları sıralayan fonksiyon
	int i,j;
    edge temp;
     
    for(i=1;i<elist.n;i++){
	
        for(j=0;j<((elist.n)-1);j++)
		{
            if(elist.data[j].w > elist.data[j+1].w)
            {
                temp=elist.data[j];
                elist.data[j]=elist.data[j+1];
                elist.data[j+1]=temp;
            }
 	    }
	}
}

void clustering(int nesneler[],int n,int k){	//ana işlemi yapan fonksiyon
	int i=0,j=0;
	elist.n=0;
	
	for(i=1;i<n;i++){  //kenar uzunluklarını kenar listesine aktaran for döngüleri
        for(j=0;j<i;j++)
        {
            if(matris[i][j]!=0)
            {
                elist.data[elist.n].a=i;
                elist.data[elist.n].b=j;
                elist.data[elist.n].w=matris[i][j];
                elist.n++;
            }
        }
	}
	
	sort();
	
	int kumesayisi=n;
	int count=0;
	int kumenumarasi=1;
	int tmp=0;
	while(kumesayisi!=k && count!=elist.n){ //n-k kere dönerek nesneleri koşullarına göre kümeleyen fonksiyon
		
		if(nesneler[elist.data[count].a]!=nesneler[elist.data[count].b]){
			
			if(nesneler[elist.data[count].a]==0){
				nesneler[elist.data[count].a]=nesneler[elist.data[count].b];	//printf("11111\n");			
			}
			else if(nesneler[elist.data[count].b]==0){							//printf("22222\n");
				nesneler[elist.data[count].b]=nesneler[elist.data[count].a];
			}
			else{
				if(nesneler[elist.data[count].a]>nesneler[elist.data[count].b]){// printf("33333\n");
					tmp=nesneler[elist.data[count].a];
					for(i=0;i<n;i++){
						if(nesneler[i]==tmp){	
							nesneler[i]=nesneler[elist.data[count].b];
						}
					}
				}
				if(nesneler[elist.data[count].b]>nesneler[elist.data[count].a]){// printf("444444\n");
				    tmp=nesneler[elist.data[count].b];
					for(i=0;i<n;i++){
						if(nesneler[i]==tmp){	
							nesneler[i]=nesneler[elist.data[count].a];
						}
					}
				}
			}
			kumesayisi--;	
		}
		if(nesneler[elist.data[count].a]==0 && nesneler[elist.data[count].b]==0){ //printf("555555");
			nesneler[elist.data[count].a]=kumenumarasi;
			nesneler[elist.data[count].b]=kumenumarasi;
			kumenumarasi++;
			kumesayisi--;
		}
		count++;
	}

	int yenikumenumarasi=kumenumarasi;
	for(i=0;i<n;i++){    
		if(nesneler[i]==0){ //printf("66666");
			nesneler[i]=yenikumenumarasi;
			yenikumenumarasi++;
		}
	}
	
}
	

void print(int nesneler[],int n){//kümeleri yazdırmak için fonksiyon
	int i,j;
	for(i=1;i<(n+1);i++){
		printf("%d. grup: ",i);
		for(j=0;j<n;j++){
			if(nesneler[j]==i){
				printf("%d-",j+1);
			}
		}
		printf("\n");
	}
}
int enYakinBulma(int a,int b,int nesneler[],int n){  //kümeler arasındaki en yakın değerleri bulma için fonksiyon
	int dizi1[30];
	int dizi2[30];
	int count=0;
	int count2=0;
	int i,j;
	for(i=0;i<n;i++){
		if(nesneler[i]==a){
			dizi1[count]=i;
			count++;
		}
		if(nesneler[i]==b){
			dizi2[count2]=i;
			count2++;
		}
	}
	int min=100;
	for(i=0;i<count;i++){
		for(j=0;j<count2;j++){
			if(matris[dizi1[i]][dizi2[j]]!=0){
				if(matris[dizi1[i]][dizi2[j]]<min){
					min=matris[dizi1[i]][dizi2[j]];
				}
			}		
		}
	}
	return min;
}


int main(){    
/*	int i=0,j=0,n,k;
	printf("Kac nesne var?:");
    scanf("%d",&n);
    
	//a = 3 ;b = 2 ;c = a + b * 4 ;b = c + b * 2 ;d = a * ( b - c ) / 2 ;
	char str[100];
    char *token;
    
	FILE *fp=fopen("dataLab.txt","r");
	
	if(fp==NULL){
		printf("WARNING!!");
		exit(0);
	}
	
	while(!feof(fp)){  //dosyadan okudum burada
	fgets(str,100, fp);
	
	token = strtok(str, ",");
	matris[i][j]=atoi(token);
	j++;
	
	while (token = strtok(NULL, ",")){
		matris[i][j] = atoi(token);
		j++;
	}
	i++;
	j=0;	
    }
    
	int nesneler[n];  //nesneler diye dizi tanımlayıp içine tamamen 0 koydum.
	for(i=0;i<n;i++){
		nesneler[i]=0;
	}
	printf("\nk kac?:");
	scanf("%d",&k);
	clustering(nesneler,n,k);
	
	printf("\n");
	print(nesneler,n);
	printf("\nIki kume arasindaki en yakin mesafeyi bulmak ister misiniz?(1/0):");
	int secenek,a,b,min;
	scanf("%d",&a);
	while(a==1){
		printf("\nhangi kumeler:");
		scanf("%d",&a);
		scanf("%d",&b);
		min=enYakinBulma(a,b,nesneler,n);
		printf("%d",min);
		printf("\nagain?:");
		scanf("%d",&a);
	}
	
	fclose(fp);*/
	
	int a='a';
	printf("%d",a);
	
	
	return 0;
}
	
