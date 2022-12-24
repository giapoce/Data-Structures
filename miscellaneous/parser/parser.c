#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1024


/*
  Copyright - Gianmarco Iapoce 2007 Vodafone Italy (Milan)

*/



char stack[STACK_SIZE];
 
int sp = 0;
 

int isEmpty()
{
 return (sp == 0);
}

char top()
{

     return stack[sp-1];
 
}


void pop()
{
     if (sp>0)
        sp--;
     else
         {
             printf("STACK UNDERFLOW\n");
             exit(1);    
         }
      
}


void push(char ch)
{
     if (sp < STACK_SIZE)
          {
              stack[sp] = ch; 
              sp++;
          }
     else
         {
           printf("STACK OVERFLOW\n");
           exit(1);
         }
}


 


void clearStack()
{
     memset(stack,0,STACK_SIZE);
     sp = 0;
}


long _stack[STACK_SIZE];
 
int _sp = 0;
 

int _isEmpty()
{
 return (_sp == 0);
}

long _top()
{
    
     return _stack[_sp-1];
 
}


void _pop()
{
     if (_sp>0)
        _sp--;
     else
         {
             printf("STACK UNDERFLOW\n");
             exit(1);    
         }
      
}


void _push(long num)
{
     if (_sp < STACK_SIZE)
          {
              _stack[_sp] = num; 
              _sp++;
          }
     else
         {
           printf("STACK OVERFLOW\n");
           exit(1);
         }
}

void printStack()
{
 
 int i;
 
 printf("\n");
 
     for (i=_sp-1; i>=0; i--) 
           printf("\t%d\t",_stack[i]);
             
         
 printf("\n");
 
}
 
void _printStack()
{
 
 int i;
 
 printf("\n");
 
     for (i=sp-1; i>=0; i--) 
           printf("\t%c\t",stack[i]);
             
         
 printf("\n");
 
}

void _clearStack()
{
     memset(_stack,0,STACK_SIZE);
     _sp = 0;
}


int isGreater(char a, char b)
{
    return  (((a=='*') && (b== '/' || b=='+' || b=='-'))  ||  ((a == '/') && (b=='+' || b=='-')) ||  (a=='+'  && (b=='-'))); 
    
}


int isOperator(char a)
{
  return (a=='+' || a=='-' || a=='*' || a=='/' || a=='%' || a=='^');    
}

 
int isUnary(char a, char *s)
{
    
    /*
 
 To be implemented
 
 if Position = 1 then
 return True;
 end if;

 Prev_Index:= Position-1;
 while Prev_Index >=1 and Infix(Prev_Index) /= '(' loop
 if Infix(Prev_Index) = ' ' then
 Prev_Index := Prev_Index -1;
 elsif Isoperator(Infix(Prev_Index)) then
 return True;
 else
 return False;
	end if;
 end loop;


return True; 
 
    */
    
}

void convInfixToPostfix(char *i,char *p)
{

 //Simple syntax check
 //unary operator not managed 
 
 int p_cn = 0;
 int pt=0;
 char prev='\0';
 char prev_d;
 
 while (*i)
  {
        
       if (isspace(*i))      
          i++;
       else if (isdigit(*i))
            {
                   
                                     
               while (isdigit(*i))
                       { *p++=*i++; pt++; }
                       
                      
                       *p++='\t';
                       
            }
       else if (*i == '(')
            { push(*i++); p_cn++; pt++;}
       else if (isOperator(*i))
            {
                               
                if (isOperator(prev))
                   {
                         
                                   
                              printf("Syntax error: two consecutives operators\n");
                              system("PAUSE");
                              exit(1);
                            
                        
                   }
                       
        		
                	while( !isEmpty() && top()!='(' )
    			         {
    				
                           if ( isGreater(top(), *i) )
    				          {
                                          
                  				    	  *p++=top();
    			                           pop();
             	             }
                           else break;
                         }
                      
                push(*i++);
                prev=*i;
                
            }
       else if (*i == ')')
            {
                      
                      p_cn--;
                      
                       while (!isEmpty()  && top() != '(')
                            {
                                                 
                                                *p++=top();
                                                pop();
                                                                                  
                                         if (!isEmpty()) pop();
                            
                            }                   
                       i++;
            }
            
           
  }      
  
  if (p_cn)
     {
           printf("Syntax error: unbalanced parenthesis\n");
           system("PAUSE");
           exit(1);
     }
           
  while (!isEmpty())
  {
        
        *p++=top();
        pop();      
  }
  
   *p='\0';
   
}

void evaluatePostfix(char *s)
{
    
    
  char b[STACK_SIZE];     
  char *p=b; 
  int c = 0;
  long value = 0;
    
    while (*s != '\0')
    {
          
          if (*s == '\t')
             s++;
             
             
          if (isdigit(*s))
             {
                          
                            
                          while(isdigit(*s) && c < STACK_SIZE) {*p++ = *s++; c++;}
                           
                          _push(atol(b));
                          p = b;
                          c = 0;
                          memset(b,0,STACK_SIZE);
                          
             }
             
              
             if (isOperator(*s))
                {
                            
                              
                                long op2 = _top();
                                _pop();
                                 
                                
                                long op1 = _top();
                                _pop();
                                 
                                
                                long res;
                                
                                switch(*s)
                                  {
                                          case '/':
                                               
                                               res = op1/op2;
                                               _push(res);
                                               
                                          break;
                                               
                                          case '*':
                                               
                                               res = op1 * op2;
                                               _push(res);
                                               
                                          break;
                                          
                                          case '+':
                                                
                                               res = op1 + op2;
                                               _push(res);
                                                
                                          break;
                                          
                                          case '-':
                                                
                                                res = op1 - op2;
                                               _push(res);
                                               
                                          break;
                                  
                                  }
                 
                                  
                }
              
             
              
            s++;
                    
    }
    
      
     
}


int main(int argc, char *argv[])
{

    char infix_array[100];
    char postfix_array[100];
    int i;
       
    strcpy(infix_array," (4+8)*(6-5)/((3-2)*(2+2))");

    convInfixToPostfix(infix_array,postfix_array);
    printf("%s\n",postfix_array);
 
    
    evaluatePostfix(postfix_array);
    
    printf("%d\n",_top());
    
    
    
      system("PAUSE");	
      return 0;


}
