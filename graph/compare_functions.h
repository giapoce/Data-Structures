#ifndef COMP_FUNCTION
#define COMP_FUNCTION

enum CMP {EQUAL = 2, GREATER = 3, LOWER = 4};

template<class K>
	CMP compare(const K &A, const K &B)
		{
				if (A>B)
					return GREATER;
				if (A<B)
					return LOWER;
				if (A == B)
					return EQUAL;
		}

CMP compare(char *A, char *B)
		{
			
			
					int i = strcmp(A,B);

						if (i>0)
							return GREATER;
						if (i<0)
							return LOWER;
						if (i==0)
							return EQUAL;
			 
			
				
		}


 

#endif
