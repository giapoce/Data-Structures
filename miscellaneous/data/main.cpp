#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    
    unsigned char data[sizeof(int)];
    *(int *)data = 12;
    
    printf("%d\n",*(int *)data);
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
