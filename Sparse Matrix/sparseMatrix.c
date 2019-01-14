#include <stdio.h>
void printHeadingValue(int val);
void main()
{
	int rows,cols,i,j,size=0,k=0;	
	float mat[100][100];
	do{
		printf("Please enter the no of rows less than 6:\n");
		scanf("%d",&rows);
	}while(rows>5);

	do{
		printf("Enter the no of columns less than 11:\n");
		scanf("%d",&cols);
	}while(cols>10);

	printf("Enter matrix values\n");
	
	for(i=0;i<rows;i++)
	{
 	 for(j=0;j<cols;j++)
 	 {
  	  scanf("%f",&mat[i][j]);
	 }
        }
	
  	printf("\n\nThe elements in the matrix are: \n\n") ;
	for(i = 0 ; i < rows; i++)
	{
         for(j = 0 ; j < cols; j++)
         {
          printf("%1.2f", mat[i][j]) ;
          printf("\t");
         }
        printf("\n");
       }
	printf("\n");

      for(i=0;i<rows;i++)
      {
       for(j=0;j<cols;j++)
       {
        if(mat[i][j]!=0)
        {
         size++;
	}
       }
      }

	
	if(size==0){
		printf("You have entered all zeroes, Bad luck!! No Sparse Matrix!!\n");
	}else{
		float sparsemat[3][size];
		for(i=0;i<=rows;i++)
			for(j=0;j<=cols;j++)
			{
				if(mat[i][j]!=0)
				{
					sparsemat[0][k]=i;
					sparsemat[1][k]=j;
					sparsemat[2][k]=mat[i][j];
					
					k++;
				}
			}
	
	printf("\n\nThe elements in the matrix are: \n\n") ;
	for(i = 0 ; i < 3; i++)
	{
         for(j = 0 ; j < size; j++)
         {
          printf("%1.2f", sparsemat[i][j]) ;
          printf("\t");
         }
        printf("\n");
       }


		printf("terms\t");
		for(int p=1;p<=size;p++)
		{
			printf("%d\t",p);
		}
		printf("\n");
		for(i=0;i<3;i++){
			printHeadingValue(i);
			/*for(j=0;j<size;j++){
				//if(i!=2)
					printf("%d\t",sparsemat[i][j]);
				//else
					//printf("%1.2f\t",sparsemat[i][j]);
			}*/
			for(j = 0 ; j < size; j++)
			 {
				if(i<2)
					printf("%1.0f\t",sparsemat[i][j]);
				else	
			  		printf("%1.2f\t", sparsemat[i][j]) ;
			 
			 }
			printf("\n");
		}
	}
	
}      
void printHeadingValue(int val){
	switch(val){
		case 0:printf("%s\t","rows");break;
		case 1:printf("%s\t","columns");break;
		case 2:printf("%s\t","values");break;
	}
}