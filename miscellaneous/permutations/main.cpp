#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100

//
//  A single call to permut(k, n) will produce (n - k + 1)!
//  permutations consisting of the integers:
//
//               r[1] ... r[k-1] ... r[k] ... r[n]
//  
//  In the output, the first r[1]...r[k-1] numbers will not
//  change.  The r[k]...r[n] numbers will be permiated.  An
//  initial call of permut(1, n) will produce the full n!
//  permutations of these n numbers.
//
//

void permut(int k, int n, int *nums)
{

  int i, j, tmp;
	
  /* when k > n we are done and should print */
  if (k <= n) 
  {

  
    for (i = k; i <= n; i++) 
		{

		    /** 
			*  each element i is promoted to the kth place while the rest
			*  of the items from k to i-1 are shifted to make room with
			*  a ripple-shift operation.
			*
			**/

		  tmp = nums[i];
		   
		  for (j = i; j > k; j--) 
				nums[j] = nums[j-1];
      
				nums[k] = tmp;

		  /* recurse on k+1 to n */

		  permut(k + 1, n, nums);
			
		  for (j = k; j < i; j++) 
				nums[j] = nums[j+1];
      
				nums[i] = tmp;
		}
  } 
  else 
  {
    for (i = 1; i <= n; i++) 
      printf("%d ", nums[i]);
    
    printf("\n");
  }

}

int main(void) 
{

  int iCount = 0;
  int rgNums[MAX_NUM];
  int i = 0;

  while (true)
	{
		  
		  fflush(stdin);
	      printf("Enter n: ");
		  int r = scanf("%d", &iCount);
		
		  if (r != 1) fflush(stdin);

		  /* create a workspace of numbers in their respective places */
		  for (i = 1; i <= iCount; i++)
				rgNums[i] = i;
		  

		  printf("Permutations:\n\n");
		  permut(1, iCount, rgNums);
		  printf("\n");
	}

  return 0;

}


