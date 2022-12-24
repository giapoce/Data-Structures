#include "AVL.h"

pavl_table<int> avt;

void _copyConstructor()
{
    pavl_table<int> _y(avt);

	 
	pavl_table<int> _z;
				   _z.pavl_insert(22);
 
	cout << "copy constructor" << endl;
	_y.pavl_output();

	  
	cout << "assign operator" << endl;
	_z = _y;
	_z.pavl_output();

}

void _insert()
{
     int y;
     printf("Insert a value: \n");
     scanf("%d",&y);
     avt.pavl_insert(y);
     avt.pavl_output();
     printf("\n");      
}

void _delete()
{
     int y;
     printf("Insert a value: \n");
     scanf("%d",&y);
     avt.pavl_delete(y);
     avt.pavl_output();      
     printf("\n");
}

void _getBalance()
{
     int y;
     printf("Insert a value: \n");
     scanf("%d",&y);
     pavl_node<int> *n = avt.pavl_find(y);
     if (n != NULL)
        printf("Balance factor is: %d\n",n->pavl_balance);
     else
         printf("Node not found\n");
}

int main()
{
    
    int choice;
    
    while (true)
    {

          printf("Choice 1: INSERT\nChoice 2: DELETE\nChoice 3: GET BALANCE FACTOR\nChoice 4: COPY CONSTRUCTOR\n\n");
          fflush(stdin);
          int _s = scanf("%d",&choice);
          if (_s != 1) {fflush(stdin); choice = 0;}

          
          switch(choice)
              {
                        case 1:
                             _insert();
                             break;
                        case 2:
                             _delete();
                             break;
                        case 3:
                             _getBalance();
                             break;     
                        case 4:
                             _copyConstructor();
                             break;
              }
    }
    
    system("PAUSE");
    return 0;    
}
