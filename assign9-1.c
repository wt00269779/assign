#include<stdio.h>
#include<conio.h>
#include<time.h>

int load_data_file_text(char filename[],double *data,int *count){
	FILE *fp;
	double a;
	int success = 0;
	if((fp=fopen(filename,"r"))!=NULL){
		*count = 0;
		while(fscanf(fp,"%lf",&a)==1){
			data[*count]=a;
			*count = *count + 1;
		}
			fclose(fp);
			printf("Load file %s %d records complete\n",filename,*count);
			success = *count;
	}
	else{
		printf("Error can't Load file %s\n",filename);
	}
	return success;
}

int load_data_file_binary(char filename[],int *data,int *count){
	FILE *fp;
	int size;
	fp = fopen(filename,"rb");
	if(fp!=NULL){
		size = 120000;
		*count=fread(data,sizeof(int),size,fp);
		fclose(fp);
		printf("Load file %s %d records complete\n",filename,*count);
	}
	else{
		printf("Error can't Load file %s\n",filename);	
		return 0;
	}
	return *count;
}

void order_data_double(double *data,int count){
	int i,j;
	double buff;
	for(i=0;i<count-1;i++){
		for(j=i+1;j<count;j++){
			if(data[i]>data[j]){
				buff = data[i];
				data[i] = data[j];
				data[j] = buff;
			}
		}
	}
	printf("\nOrder data double success!\n");
}

void quick_sort_d(double arr[],int low,int high){
 int pivot,j,temp,i;
 if(low<high){
  pivot = low;
  i = low;
  j = high;
  while(i<j){
   while((arr[i]<=arr[pivot])&&(i<high)){
    i++;
   }
   while(arr[j]>arr[pivot]){
    j--;
   }
   if(i<j){ 
    temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
   }
  }
  temp=arr[pivot];
  arr[pivot]=arr[j];
  arr[j]=temp;
  quick_sort_d(arr,low,j-1);
  quick_sort_d(arr,j+1,high);
 }
}


void quick_sort_i(int arr[],int low,int high){
 int pivot,j,temp,i;
 if(low<high){
  pivot = low;
  i = low;
  j = high;
  while(i<j){
   while((arr[i]<=arr[pivot])&&(i<high)){
    i++;
   }
   while(arr[j]>arr[pivot]){
    j--;
   }
   if(i<j){ 
    temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
   }
  }
  temp=arr[pivot];
  arr[pivot]=arr[j];
  arr[j]=temp;
  quick_sort_i(arr,low,j-1);
  quick_sort_i(arr,j+1,high);
 }
}

int quick_sr(double *data1,int *data2,int count1,int count2,int *same_num){
	int i=0,j=0;
	int same_count=0;
	*same_num=0;
	while(i<count1&&j<count2){
		if(data1[i]>=data2[j]){
			if(data1[i]==data2[j]){
				same_num[same_count++] = data2[j];
				i++;
			}
			else{ 
				j++;
			}
		}
		else{
			i++;
		}
	}
	return same_count;
}

int main(){
	double data1[120000];
	double start,stop,total;
	int data2[120000];
	int same_data[2000];
	int count_d1,count_d2,same_count,success,i;
	char file1[50] = "txt100000.txt",file2[50] = "bin100000.bin";
	success = load_data_file_text(file1,data1,&count_d1);
	success = load_data_file_binary(file2,data2,&count_d2);
	printf("\nRead text file from %s total %d records\n",file1,count_d1);
	printf("Read binary file frim %s total %d records\n",file2,count_d2);
	printf("Total data = %d records\n",count_d1+count_d2);
	quick_sort_d(data1,0,count_d1);
	quick_sort_i(data2,0,count_d2);
	printf("\nProcess data\n");
	start = clock();
	same_count = quick_sr(data1,data2,count_d1,count_d2,same_data);
	stop = clock();
	for(i=1;i<same_count;i++){
		printf("Found [%d] = %d\n",i,same_data[i]);
	}
	printf("End program\n\n");
	total = (stop-start)/CLK_TCK;
	printf("execution time : %.3lf s",total);
	getch();
}
