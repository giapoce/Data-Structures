#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PAVL_H
#define PAVL_H

#define TRUE 1
#define FALSE 0

struct libavl_allocator
{
       void *(*libavl_malloc) (struct libavl_allocator *, size_t libavl_size);
       void (*libavl_free) (struct libavl_allocator *, void *libavl_block);
};

void *tbl_malloc(struct libavl_allocator *alloc, size_t size)
{

     return malloc(size);
}

/* Frees block. */
void tbl_free (struct libavl_allocator *alloc, void *block)
{
     
     free (block);
}

/* Default memory allocator that uses malloc() and free(). */
struct libavl_allocator pavl_allocator_default = {tbl_malloc, tbl_free};

typedef int pavl_comparison_func(const void *pavl_a, const void *pavl_b, void *pavl_param);

struct pavl_node
{
       struct pavl_node *pavl_link[2]; /* Subtrees. */
       struct pavl_node *pavl_parent; /* Parent node. */
       void *pavl_data; /* Pointer to data. */
       signed char pavl_balance; /* Balance factor. */
};

struct pavl_table
{
       struct pavl_node *pavl_root; /* Tree’s root. */
       pavl_comparison_func *pavl_compare; /* Comparison function. */
       void *pavl_param; /* Extra argument to bst compare. */
       struct libavl_allocator *pavl_alloc; /* Memory allocator. */
       size_t pavl_count; /* Number of items in tree. */
};


struct pavl_table *pavl_create (pavl_comparison_func *compare, void *param, struct libavl_allocator *alloc)
{
     struct pavl_table *tree;

     

     if (alloc == NULL)
                alloc = &pavl_allocator_default;

     tree = (struct pavl_table *)alloc->libavl_malloc(alloc, sizeof *tree);

      if (tree == NULL)
          return NULL;

       tree->pavl_root = NULL;
       tree->pavl_compare = compare;
       tree->pavl_param = param;
       tree->pavl_alloc = alloc;
       tree->pavl_count = 0;

       return tree;
}

struct pavl_node *pavl_find (const struct pavl_table *tree, const void *item)
{

     struct pavl_node *p;
     

     for (p = tree->pavl_root; p != NULL;)
         {
           int cmp = tree->pavl_compare (item, p->pavl_data, tree->pavl_param);
               /*if (cmp < 0)
                  p = p->pavl_link[0];
               else if (cmp > 0)
                  p = p->pavl_link[1];
               else
                   return p; */
                   if (cmp == 0)
                     return p;
                   else
                       p = p->pavl_link[(cmp>0)];
               /* cmp == 0 */

          }

    return NULL;
}

void **pavl_insert (struct pavl_table *tree, void *item)
{

       struct pavl_node *y; /* Top node to update balance factor, and parent. */
       struct pavl_node *p, *q; /* Iterator, and parent. */
       struct pavl_node *n; /* Newly inserted node. */
       struct pavl_node *w; /* New root of rebalanced subtree. */
       int dir; /* Direction to descend. */
       

       y = tree->pavl_root;

       for (q = NULL, p = tree->pavl_root; p != NULL; q = p, p = p->pavl_link[dir])
       {
           int cmp = tree->pavl_compare (item, p->pavl_data, tree->pavl_param);

           if (cmp == 0)
              return &p->pavl_data;

           dir = (cmp > 0);

           if (p->pavl_balance != 0)
                  y = p;
      }

n = tree->pavl_alloc->libavl_malloc (tree->pavl_alloc, sizeof *p);

if (n == NULL)
   return NULL;

           tree->pavl_count++;
           n->pavl_link[0] = n->pavl_link[1] = NULL;
           n->pavl_parent = q;
           n->pavl_data = item;

if (q != NULL)
   q->pavl_link[dir] = n;
else
   tree->pavl_root = n;

     n->pavl_balance = 0;
     if (tree->pavl_root == n)
              return &n->pavl_data;

      for (p = n; p != y; p = q)
          {
             q = p->pavl_parent;
             dir = (q->pavl_link[0] != p);
                 if (dir == 0)
                    q->pavl_balance--;
                 else
                    q->pavl_balance++;
          }


          if (y->pavl_balance == -2)
             {

               struct pavl_node *x = y->pavl_link[0];

               if (x->pavl_balance == -1)
                 {

                 /*<Rebalance for - balance factor in PAVL insertion in left subtree>*/

                         w = x;
                         y->pavl_link[0] = x->pavl_link[1];
                         x->pavl_link[1] = y;
                         x->pavl_balance = y->pavl_balance = 0;

                         x->pavl_parent = y->pavl_parent;
                         y->pavl_parent = x;

                         if (y->pavl_link[0] != NULL)
                            y->pavl_link[0]->pavl_parent = y;
                 }
               else
                 {

                 /*<Rebalance for + balance factor in PAVL insertion in left subtree>*/

                

                w = x->pavl_link[1];
                x->pavl_link[1] = w->pavl_link[0];
                w->pavl_link[0] = x;
                y->pavl_link[0] = w->pavl_link[1];
                w->pavl_link[1] = y;

                if (w->pavl_balance == -1)
                     x->pavl_balance = 0, y->pavl_balance = +1;
                else if (w->pavl_balance == 0)
                     x->pavl_balance = y->pavl_balance = 0;
                else
                     x->pavl_balance = -1, y->pavl_balance = 0;

                     w->pavl_balance = 0;

                    w->pavl_parent = y->pavl_parent;
                    x->pavl_parent = y->pavl_parent = w;

                    if (x->pavl_link[1] != NULL)
                       x->pavl_link[1]->pavl_parent = x;

                    if (y->pavl_link[0] != NULL)
                       y->pavl_link[0]->pavl_parent = y;

                 }

                 }
          else if (y->pavl_balance == +2)
                  {

                  /*<Rebalance PAVL tree after insertion in right subtree >*/

                  struct pavl_node *x = y->pavl_link[1];

                  if (x->pavl_balance == +1)
                     {
                            w = x;
                            y->pavl_link[1] = x->pavl_link[0];
                            x->pavl_link[0] = y;
                            x->pavl_balance = y->pavl_balance = 0;
                            x->pavl_parent = y->pavl_parent;
                            y->pavl_parent = x;

                            if (y->pavl_link[1] != NULL)
                               y->pavl_link [1]->pavl_parent = y;

                          /*<Rebalance for + balance factor in PAVL insertion in right subtree>*/

                     }
                      else
                      {
                           /*<Rebalance for - balance factor in PAVL insertion in right subtree>*/
                            

                            w = x->pavl_link[0];

                            x->pavl_link[0] = w->pavl_link [1];
                            w->pavl_link[1] = x;
                            y->pavl_link[1] = w->pavl_link [0];
                            w->pavl_link[0] = y;

                            if (w->pavl_balance == +1)
                               x->pavl_balance = 0, y->pavl_balance = -1;
                            else if (w->pavl_balance == 0)
                                 x->pavl_balance = y->pavl_balance = 0;
                            else
                                 x->pavl_balance = +1, y->pavl_balance = 0;

                                 w->pavl_balance = 0;

                                 w->pavl_parent = y->pavl_parent;
                                 x->pavl_parent = y->pavl_parent = w;

                                if (x->pavl_link[0] != NULL)
                                   x->pavl_link[0]->pavl_parent = x ;
                                if (y->pavl_link[1] != NULL)
                                   y->pavl_link[1]->pavl_parent = y;
                      }

                  }
          else
               return &n->pavl_data;

          if (w->pavl_parent != NULL)
              w->pavl_parent->pavl_link [y != w->pavl_parent->pavl_link[0]] = w;
          else tree->pavl_root = w;

          return &n->pavl_data;
}


void *pavl_delete (struct pavl_table *tree, const void *item)
{

     struct pavl_node *p; /* Traverses tree to find node to delete. */
     struct pavl_node *q; /* Parent of p. */
     int dir;      /* Side of q on which p is linked. */

    

    if (tree->pavl_root == 0)
       return NULL;

    p = tree->pavl_root;

    for (;;)
        {
             int cmp = tree->pavl_compare (item, p->pavl_data, tree->pavl_param);

             if (cmp == 0)
                break;

             dir = (cmp > 0);

             p = p->pavl_link[dir];

             if (p == NULL)
                return NULL;
         }

item = p->pavl_data;

q = p->pavl_parent;

if (q == NULL)
 {
      q = (struct pavl_node *) &tree->pavl_root;
      dir = 0;
 }

    if (p->pavl_link[1] == NULL)
        {

          q->pavl_link[dir] = p->pavl_link[0];

          if (q->pavl_link[dir] != NULL)
             q->pavl_link[dir]->pavl_parent = p->pavl_parent;

        }
         else
         {
             struct pavl_node *r = p->pavl_link[1];

             if (r->pavl_link[0] == NULL)
                {

                  /*<Case 2 in PAVL deletion>*/

                    r->pavl_link[0] = p->pavl_link[0];
                    q->pavl_link[dir] = r;
                    r->pavl_parent = p->pavl_parent;

                    if (r->pavl_link[0] != NULL)
                       r->pavl_link[0]->pavl_parent = r;

                    r->pavl_balance = p->pavl_balance;
                    q = r;
                    dir = 1;
                }
             else
                {

                  /*<Case 3 in PAVL deletion>*/

                  struct pavl_node *s = r->pavl_link[0];

                    while (s->pavl_link[0] != NULL)
                          s = s->pavl_link[0];

                          r = s->pavl_parent;

                    r->pavl_link[0] = s->pavl_link[1];
                    s->pavl_link[0] = p->pavl_link[0];
                    s->pavl_link[1] = p->pavl_link[1];
                    q->pavl_link[dir] = s;

                    if (s->pavl_link[0] != NULL)
                       s->pavl_link[0]->pavl_parent = s;

                       s->pavl_link[1]->pavl_parent = s;
                       s->pavl_parent = p->pavl_parent;

                    if (r->pavl_link[0] != NULL)
                       r->pavl_link[0]->pavl_parent = r;

                    s->pavl_balance = p->pavl_balance;
                    q = r;
                    dir = 0;
                }
         }

     tree->pavl_alloc->libavl_free(tree->pavl_alloc, p);

    /*<Steps 3 and 4: Update balance factors and rebalance after PAVL deletion>*/

while (q != (struct pavl_node *) &tree->pavl_root)
    {
                struct pavl_node *y = q;

                if (y->pavl_parent != NULL)
                    q = y->pavl_parent;
                else
                     q = (struct pavl_node *) &tree->pavl_root;

        if (dir == 0)
           {

                dir = (q->pavl_link[0] != y);

                y->pavl_balance++;

                if (y->pavl_balance == +1)
                   break;
                else if (y->pavl_balance == +2)
                     {
                       /*<Step 4: Rebalance after PAVL deletion>*/

                          struct pavl_node *x = y->pavl_link[1];

                          if (x->pavl_balance == -1)
                          {

                          /*<Left-side rebalancing case 1 in PAVL deletion>*/

                           

                            struct pavl_node *w;

                            w = x->pavl_link[0];

                            x->pavl_link[0] = w->pavl_link[1];
                            w->pavl_link[1] = x;
                            y->pavl_link[1] = w->pavl_link[0];
                            w->pavl_link[0] = y;

                            if (w->pavl_balance == +1)
                               x->pavl_balance = 0, y->pavl_balance = -1;
                            else if (w->pavl_balance == 0)
                                 x->pavl_balance = y->pavl_balance = 0;
                            else
                                 x->pavl_balance = +1, y->pavl_balance = 0;

                                 w->pavl_balance = 0;

                                 w->pavl_parent = y->pavl_parent;
                                 x->pavl_parent = y->pavl_parent = w;

                                if (x->pavl_link[0] != NULL)
                                   x->pavl_link[0]->pavl_parent = x;

                                if (y->pavl_link[1] != NULL)
                                   y->pavl_link[1]->pavl_parent = y;

                                q->pavl_link[dir] = w;

                                    }
                               else {

                                    /*<Left-side rebalancing case 2 in PAVL deletion>*/

                                            y->pavl_link[1] = x->pavl_link[0];
                                            x->pavl_link[0] = y;
                                            x->pavl_parent = y->pavl_parent;
                                            y->pavl_parent = x;

                                            if (y->pavl_link[1] != NULL)
                                               y->pavl_link[1]->pavl_parent = y;

                                               q->pavl_link[dir] = x;

                                            if (x->pavl_balance == 0)
                                               {
                                                       x->pavl_balance = -1;
                                                       y->pavl_balance = +1;
                                                       break;
                                               }
                                            else
                                               {
                                                       x->pavl_balance = y->pavl_balance = 0;
                                                       y = x;
                                               }
                                    }
                       }
           }
           else
               {
                    /*<Steps 3 and 4: Symmetric case in PAVL deletion>*/

                    dir = (q->pavl_link[0] != y);
                    y->pavl_balance--;

                    if (y->pavl_balance == -1)
                         break;
                    else if (y->pavl_balance == -2)
                         {
                            struct pavl_node *x = y->pavl_link[0];
                                if (x->pavl_balance == +1)
                                   {

                                       /*<Right-side rebalancing case 1 in PAVL deletion>*/

                                       
                                        struct pavl_node *w;
                                        w = x->pavl_link[1];

                                        x->pavl_link[1] = w->pavl_link[0];
                                        w->pavl_link[0] = x;
                                        y->pavl_link[0] = w->pavl_link[1];
                                        w->pavl_link[1] = y;

                                        if (w->pavl_balance == -1)
                                             x->pavl_balance = 0, y->pavl_balance = +1;
                                        else if (w->pavl_balance == 0)
                                             x->pavl_balance = y->pavl_balance = 0;
                                        else
                                             x->pavl_balance = -1, y->pavl_balance = 0;

                                            w->pavl_balance = 0;

                                            w->pavl_parent = y->pavl_parent;
                                            x->pavl_parent = y->pavl_parent = w;

                                            if (x->pavl_link[1] != NULL)
                                               x->pavl_link[1]->pavl_parent = x;

                                            if (y->pavl_link[0] != NULL)
                                               y->pavl_link[0]->pavl_parent = y;

                                            q->pavl_link[dir] = w;
                                   }
                                else
                                   {
                                           /*<Right-side rebalancing case 2 in PAVL deletion>*/

                                           y->pavl_link[0] = x->pavl_link[1];

                                            x->pavl_link[1] = y;
                                            x->pavl_parent = y->pavl_parent;
                                            y->pavl_parent = x;

                                            if (y->pavl_link[0] != NULL)
                                               y->pavl_link[0]->pavl_parent = y;

                                            q->pavl_link[dir] = x;

                                            if (x->pavl_balance == 0)
                                               {
                                                        x->pavl_balance = +1;
                                                        y->pavl_balance = -1;
                                                        break;
                                               }

                                            else
                                               {
                                                        x->pavl_balance = y->pavl_balance = 0;
                                                        y = x;
                                               }
                                   }

                       }
               }
        }

        tree->pavl_count--;
        return (void *) item;

}

void p_output(struct pavl_node *,int);

void pavl_output(struct pavl_table *t)
{
	p_output(t->pavl_root,0);
}


void p_output(struct pavl_node *_x,int _off)
{
	if (!_x)
		return;

	p_output(_x->pavl_link[1],_off + 5);
    int j;

		for (j=0; j<_off; j++)
            printf(" ");

			printf("%d",_x->pavl_data);
            printf("\n");

	p_output(_x->pavl_link[0],_off + 5);
}


int pavl_compare(const void *pavl_a, const void *pavl_b, void *pavl_param)
{
               if (pavl_a > pavl_b)
                  return 1;
               if (pavl_b > pavl_a)
                  return -1;
               if (pavl_a == pavl_b)
                  return 0;
}

void _insert(struct pavl_table *x)
{
     int y;
     printf("Insert a value: \n\n");
     scanf("%d",&y);
     pavl_insert(x,(void *)y);
     printf("\n");
     pavl_output(x);
     printf("\n");
}

void _delete(struct pavl_table *x)
{
     int y;
     printf("Insert a value: \n\n");
     scanf("%d",&y);
     pavl_delete(x,(void *)y);
     printf("\n");
     pavl_output(x);
     printf("\n");
}

void _getBalance(struct pavl_table *x)
{
     int y;
     printf("Insert a value: \n");
     scanf("%d",&y);
     struct pavl_node *n = pavl_find(x,(void *)y);
     if (n != NULL)
        printf("Balance factor is: %d\n\n",n->pavl_balance);
     else
         printf("Node not found\n\n");
}

int main()
{

    struct pavl_table *t = pavl_create (pavl_compare, 0, &pavl_allocator_default);

    int choice;

    while (TRUE)
    {
          printf("1: INSERT\n2: DELETE\n3: GET BALANCE FACTOR\n\n");
          fflush(stdin);
          int _s = scanf("%d",&choice);
          if (_s != 1) {fflush(stdin); choice = 0;}


          switch(choice)
              {
                        case 1:
                             _insert(t);
                             break;
                        case 2:
                             _delete(t);
                             break;
                        case 3:
                             _getBalance(t);
                             break;
              }
    }
    
    system("PAUSE");
    return 0;    
}

#endif
