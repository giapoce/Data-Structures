#include <bitset>
#include <cmath>

using namespace std;

int main()
{

	const int N = 4024;
	int k,j,m,counter,finalBit; 

	bitset<N> a;
	a.flip();

	finalBit = sqrt(a.size()) + 1;
		
	for (k = 2; k < finalBit; k++)
		if (a.test(k))	
			for (j = 2*k; j < N; j+=k)
					a.reset(j);

	for (m = 2,counter = 0; m< N; m++)
		{
	
			if (a.test(m))
				{
					printf("%d\t",m);

					if (++counter % 10 == 0)
						printf("\n");
				}
	
		}

	printf("\n");
    system("PAUSE");
	return 0;
}
