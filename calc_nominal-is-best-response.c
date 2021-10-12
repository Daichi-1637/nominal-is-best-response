#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"math.h"

#define DATA_LENGTH 10000
#define LOOP_TIME 100

// 昇順ソートができているかどうか簡単に調べる関数
int debug(long int* ary){
	int isUpperSort = 1;
	int i;
	for(i = 1; i < DATA_LENGTH; i++){
		isUpperSort *= ary[i - 1] <= ary[i];
	}
	return isUpperSort;
}

// 配列のコピー
void ary_copy(long int* src, long int* dist){
  int i = 0;
  for(i = 0; i < DATA_LENGTH; i++){
    dist[i] = src[i];
  }
}

// cpuの経過時間を取得する関数
double cpu_time(){
	return (double)clock() / CLOCKS_PER_SEC;
}

int main(){
	int i, j, k;
	int swap;
	long int src_ary[DATA_LENGTH], copyed_ary[DATA_LENGTH];
	double start_time, finish_time, past_time[LOOP_TIME];
  double ave = 0, sum = 0;
  double St = 0, Sm = 0, Se = 0, Ve, fe = LOOP_TIME - 1;
	double eta;
  FILE *fp;

	// ファイルからデータを取得
	fp = fopen("randomNum.csv", "r");
	for(i = 0; i < DATA_LENGTH; i++){
		fscanf(fp, "%ld,", &src_ary[i]);
	}
  fclose(fp);

  for(i = 0; i < LOOP_TIME; i++){
    // 配列の内容をコピー
    ary_copy(src_ary, copyed_ary);

    // 計測開始の時間を記録
	  start_time = cpu_time();

	  // バブルソート
	  for(j = DATA_LENGTH; j > 1; j--){
	  	for(k = 0; k < j; k++){
	  		if(src_ary[j] > src_ary[j + 1]){
	  			swap = src_ary[k];
	  			src_ary[k] = src_ary[k + 1];
	  			src_ary[k + 1] = swap;
	  		}
	  	}
	  }

	  // 計測終了の時間を記録
	  finish_time = cpu_time();

    // 計測時間の計算
	  past_time[i] = finish_time - start_time;

    // 合計の計算
    sum += past_time[i]; 
    
    // 全二乗和の計算
    St += past_time[i] * past_time[i];
  }

  // 平均の計算
  ave = sum / (double)LOOP_TIME;

  Sm = (double)LOOP_TIME * ave * ave;
  // 誤差二乗和の計算
  Se = St - Sm;
  // 誤差分散の計算
  Ve = Se / fe;

	printf("average: %.16f\n", ave);
	printf("St: %.16f\n", St);
	printf("Sm: %.16f\n", Sm);
	printf("Se: %.16f\n", Se);
	printf("Ve: %.16f\n", Ve);

  // 展望特性のSN比
	eta = (double)10 * log10((Sm - Ve) / ((double)LOOP_TIME * Ve));

  printf("%.16f[dB]\n", eta);

  return 0;
}