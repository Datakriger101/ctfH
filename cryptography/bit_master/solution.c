#include <stdio.h>

int main(int argc, char *argv[]){

	//the flag : CTFkom{f3W_p30pL3_cAn_$h1Ft}
	int new_flag[40] = {1072, 1344, 1120, 1712, 1776, 1744, 1968, 1632, 816, 1392, 1520, 1792, 816, 768, 1792, 1216, 816, 1520, 1584, 1040, 1760, 1520, 576, 1664, 784, 1120, 1856, 2000};

	//Soulution THAT IS SUPPOSED TO WORK. Maybe a little unclear

	//for(int i = 1; i < 10; i++){		I want to decide numbers of bit shift with a variable i, but it wont let me. 
	//									The soulution is therefor to change the (number of bits) variable until it shows
	//									a flag. In this case it is 4.
		for(int i = 0; i < 28; i++){
			printf("%c", new_flag[i] >> 4 /* <-- variable i*/);	
		}
		printf("\n");
	//}


	return 0;
}	

	//Creation

	//char flag[40] = {'C', 'T', 'F', 'k', 'o', 'm', '{', 'f', '3', 'W','_', 'p', '3', '0', 'p', 'L', '3', '_', 'c', 'A', 'n', '_', '$', 'h', '1', 'F', 't', '}'};
	
	/*
	for(int i = 0; i < 28; i++){
		printf("%i, ", flag[i] << 4);	
	}
	*/



	//Solution
/*
	for(int i = 0; i < 28; i++){
		printf("%c", new_flag[i] >> 4);
	}
*/