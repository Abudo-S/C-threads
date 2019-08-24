/*
 * A simple matrix multiplication program
 * (Matrix_A  X  Matrix_B) => Matrix_C
 */
#include <pthread.h>
#include <stdio.h>
#define ARRAY_SIZE 5

typedef int matrix_t[ARRAY_SIZE][ARRAY_SIZE];
matrix_t MA,MB,MC;
//int row,column;
/*
* Routine to multiply a row by a column and place element in
* resulting matrix.
*/
void *perform(void * value){
    int *p; 
     p = (int *) value;
    mult(ARRAY_SIZE,p[0],p[1],MA,MB,MC);
    free(value);
}

void mult(int size,
	  int row,
	  int column,
	  matrix_t MA,
	  matrix_t MB,
	  matrix_t MC)
{
  int position;

  MC[row][column] = 0;
  for(position = 0; position < size; position++) {
    MC[row][column] = MC[row][column] +
      ( MA[row][position]  *  MB[position][column] ) ;
  }
  printf("calc...row&col:%d-%d ",row,column);
  pthread_exit(NULL);
}


/*
 * Main: allocates matrix, assigns values, computes the results
 */
int main(void)
{
  int size,row,column,i;
  size = ARRAY_SIZE;
  int max=size * size;
 pthread_t threads[max]; //array of threads
 int value[2];
 printf("Enter %d * %d matrices\n",size,size);
  printf("MATRIX: The A array is;\n");
  for(row=0;row<size;row++){ //get MA
      for(column=0;column<size;column++){
          scanf("%d",&MA[row][column]);
      }
  }


  printf("MATRIX: The B array is;\n");
  for(row=0;row<size;row++){ //get MB
      for(column=0;column<size;column++){
          scanf("%d",&MB[row][column]);
      }
  }
  i=0;
    
     for(row=0;row<size;row++){
         for(column=0;column<size;column++){ //creating a thread for each element in matrix "MC" (each iteration)
             value[0]=row;
             value[1]=column;
           pthread_create(&threads[i], NULL, perform, (void *) value);     
           i++;
         }
     }
  row=0;
     column=-1;
     /* for(i=0;i<max;i++){   //creating a thread for each element in matrix "MC" //another solution
          
          if(column==ARRAY_SIZE-1){
              row++;
              column=0;
          }else{
            column++; 
          }
          value[0]=row;
          value[1]=column;
          pthread_create(&threads[i], NULL, perform,(void *) value);    
       }*/
      value[0]=0;
      value[1]=0;
       pthread_t thread0;
      pthread_create(&thread0, NULL, perform,(void *) value); 
      for (i=0;i<ARRAY_SIZE*ARRAY_SIZE;i++){
         pthread_join(threads[i],NULL);
       }
      
      printf("\n");
  printf("MATRIX: The resulting matrix C is;\n");
    for(row=0;row<size;row++){   // printing "MC"
        for(column=0;column<size;column++){
           printf("%d\t",MC[row][column]);
        }
        printf("\n");
    }

  return 0;
}

