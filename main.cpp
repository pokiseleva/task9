#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

struct tree
{
    char data;
    tree *left;
    tree *right;
};
struct st
{
    char c;
    struct st *next;
};

struct st *push1(st *head, char a)
{
    st *ptr;

    if((ptr=(st*)malloc(sizeof(struct st)))==NULL)
    {
        puts("нет памяти");
        exit(-1);
    }
    ptr->c=a;
    ptr->next=head;
    return ptr;
}

char DEL(st **head)
{
    struct st *ptr;
    char a;
    if(*head==NULL) return '\0';
    ptr=*head;
    a=ptr->c;
    *head=ptr->next;
    free(ptr);
    return a;
}
int i;
char pf[1000];
int p= -1;
tree* f[1000];
int op(char a)
{
    if (a=='+'|| a=='-'||a=='*'||a=='/')
        return (-1);
    else if (a>= '1' ||a<= '9')
        return (1);
    else
        return (-100);
}
void push(tree *Tree)
{
    p++;
    f[p] = Tree;
}
tree *pop()
{
    p--;
    return (f[p + 1]);
}
void expression(char *a)
{
    char s;
    tree *newl, *p1, *p2;
    int fl;
    s = a[0];
    for (int i = 1; s!= 0; i++)
    {
        fl = op(s);
        if (fl == 1)
        {
            newl = new tree;
            newl->data = s;
            newl->left = NULL;
            newl->right = NULL;
            push(newl);
        }
        else
        {
            p1 = pop();
            p2 = pop();
            newl = new tree;
            newl->data = s;
            newl->left = p2;
            newl->right = p1;
            push(newl);
        }
        s = a[i];
    }
}


void show(tree *ptr, int n)
{
    if (ptr == NULL)
        return;
    else
    {
        show(ptr->left, ++n);
        for (int i=0; i<n; ++i)
            cout << "       ";
        cout << ptr->data << endl;
        n--;
    }
    show(ptr->right, ++n);
}

double calc(tree* ptr)

{

    double x1,x2;
    if (!ptr->left)

        return ptr->data - '0';

    x1=calc(ptr->left);

    x2=calc(ptr->right);
    switch (ptr->data )
    {
    case '+':
        return x1+x2;

    case '-':
        return x1-x2;

    case '*':
        return x1*x2;

    case '/':
        return x1/x2;

    }

}

int PRIOR(char a)
{
    switch(a)
    {
    case '*':
    case '/':
        return 3;

    case '-':
    case '+':
        return 2;

    case '(':
        return 1;
    }
}


int main()
{   setlocale(0, "Russian");
    struct st *OPERS=NULL;
    char a[1000], outstring[1000];
    int k, point;
    do
    {
        puts("Введите выpажение:");
        fflush(stdin);
        gets(a);
        k=point=0;
        while(a[k]!='\0'&&a[k]!='=')
        {
            if(a[k]==')')

            {
                while((OPERS->c)!='(')
                    outstring[point++]=DEL(&OPERS);
                DEL(&OPERS);
            }
            if(a[k]>='0'&&a[k]<='9')
                outstring[point++]=a[k];
            if(a[k]=='(')
                OPERS=push1(OPERS, '(');
            if(a[k]=='+'||a[k]=='-'||a[k]=='/'||a[k]=='*')
            {
                if(OPERS==NULL)
                    OPERS=push1(OPERS, a[k]);
                else
                    if(PRIOR(OPERS->c)<PRIOR(a[k]))
                        OPERS=push1(OPERS, a[k]);
                    else
                    {
                        while((OPERS!=NULL)&&(PRIOR(OPERS->c)>=PRIOR(a[k])))
                            outstring[point++]=DEL(&OPERS);
                        OPERS=push1(OPERS, a[k]);
                    }
            }
            k++;
        }
        while(OPERS!=NULL)
            outstring[point++]=DEL(&OPERS);
        outstring[point++]='\0';
        expression(outstring);
        cout<<endl;
        show(f[0],1);
        cout<<endl;
        cout<<"Результат:"<<calc(f[0]);

    }
    while(getchar()!='n');
    return 0;
}


