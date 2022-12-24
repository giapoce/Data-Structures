#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 2

int monoMatrix[2] = {1,2};

int matrix4x4[4][4] = {
        {1,2,3,4},
        {3,4,2,1},
        {5,6,7,8},
        {8,7,6,5}
    };
    
int matrix2x2[2][2] = {
        {1,3},
        {6,4}
    };
        
void trasposeMatrix(int matrix[][COLUMNS],int width,int height) {
    
    int x,y;
    int tmp;
    
    if (width != height) {
        printf("%s\n","Matrix is not squared");
        return;
    }
    
    for (x=0;x<height;x++)
        for (y=x+1;y<width;y++)
            {
                if (y > width) break;
                tmp = matrix[x][y];                
                matrix[x][y] = matrix[y][x];                
                matrix[y][x] = tmp;
                
            }
            
}

void printMatrix(int matrix[][COLUMNS],int width,int height) {
    
    int x,y;
    
        for (x=0;x<height;x++) {
            for (y=0;y<width;y++)
                    printf("%d\t",matrix[x][y]);
                printf("\n");
        }
                
            printf("\n");
    
}

void printMonoMatrix(int matrix[],int size) {
    
        int x;
        
        for (x=0; x< size; x++)             
            printf("%d\t",matrix[x]);
            
            printf("\n");
            
    
}


void changeMonoMatrix(int matrix[],int c,int size) {
    
        int x;
        
        for (x=0; x< size; x++)             
            matrix[x]=c;
            
            printf("\n");
            
    
}

int main() {
    
    
    printMatrix(matrix2x2,2,2);
    trasposeMatrix(matrix2x2,2,2);
    printMatrix(matrix2x2,2,2);
    
    
    system("PAUSE");
   
    return 0;

}
