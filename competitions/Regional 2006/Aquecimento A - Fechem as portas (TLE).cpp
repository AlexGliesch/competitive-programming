#include <stdio.h>
#include <string.h>
#define MAX 25000000

int num_factors[MAX+10],num_div[MAX+10];

int main(){
	int i, j;
	memset(num_factors,0,sizeof(num_factors));
	for (i = 2; i <= MAX; ++i) {
		if (num_factors[i]==0){
			for (j = i; j <= MAX; j += i){
				++num_factors[j];
				int x=j;
				num_div[j]=0;
				while(x > 0 && x % i == 0) { ++num_div[j]; x /= i; }
			}
		}
	}


	int N;
	while(scanf("%d",&N), N){
		int first=1;
		if (N==0){
			printf("\n");
		}
		/*for(int i=0;i<=10;++i){
			cout << "num_div["<<i<<"]="<<num_div[i]<<endl;
		}*/

		for (i=1;i<=N;++i){

			if (num_div[i]%2==0){
				if (!first){
					printf(" ");
				}
				first=0;
				printf("%d",i);
			}
		}
		printf("\n");

	}
}
