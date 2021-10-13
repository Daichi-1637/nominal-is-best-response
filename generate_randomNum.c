#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DATA_LENGTH 10000

int main(){
  int i;
  FILE* fp;

  fp = fopen("randomNum.csv", "w");
  
  srand((unsigned int)time(NULL));

  for(i = 0; i < DATA_LENGTH; i++){
    fprintf(fp, "%d, ", rand());
  }

  fclose(fp);

  return 1;
}