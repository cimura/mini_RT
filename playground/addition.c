#include <stdio.h> 

int main(void)
{

	int n ;
	float d, ans ;
	double	answer, f;

	d = 0.0001 ;
	f = 0.0001;

	ans = 0;
	answer = 0;
	for( n = 1 ; n <= 10000 ; n++ ){
		ans += d ;
		answer += f;
	}
	printf("double result: %f\n", answer);
	if( ans == 1. ){
		printf("\n0.0001を，10000回足し算すると，1になります。\n") ;
	}
	else{
		printf("\n0.0001を，10000回足し算すると，1にはなりません。\n") ;
		printf("答えは，%f\n", ans) ;
	}
}