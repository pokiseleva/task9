/* Алгоритм:
После ввода выржения строится постфиксная запись выражения. Далее вызываем функцию  expression(outstring),
 которая строит бинарное дерево по постфиксной записи:
 если fl = 1 когда это операнд
 fl= -1 когда это оператор
 Если операнд - записываем его в стек ,
если  операция, то снимаем два числа из стека, помещаем в дерево, выполняем операцию.*/
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

char* getline()
{
    char* line = (char*)malloc(1024), *linep = line;
    int lenmax = 100, len = lenmax;
    int c;
    if (!line)
        return NULL;
    while (1)
    {
        c = fgetc(stdin);
        if (c == '\n' && linep == line)
            continue;
        if (c == EOF)
            break;
        if (--len == 0)
        {
            len = lenmax;
            char* linen = (char*)realloc(linep, lenmax *= 2);
            if (!linen)
            {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }
        if ((*line++ = c) == '\n')
            break;
    }
    *(line-1) = '\0';
    *line = '\0';
    return linep;
}




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
tree* __f[1000];

struct TreeStack
{
    tree* t;
    struct TreeStack *next;
};

TreeStack *f0 = NULL, *f_tail = NULL;


struct TreeStack *push2(tree* t_)
{
    TreeStack *ptr;

    ptr = new TreeStack;
    ptr->t = t_;
    ptr->next = NULL;

    if (!f0)
    {
        f_tail = f0 = ptr;
    }
    else
    {
        f_tail->next = ptr;
        f_tail = ptr;
    }
    return ptr;
}



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
    push2(Tree);
}
tree *pop()
{
    TreeStack* ptr = f_tail;
    tree* Tree = ptr->t;
    //
    if (f_tail == f0)
    {
        f0 = f_tail = NULL;
    }
    else
    {
        TreeStack* s = f0;
        while (s->next->next)
        {
            s = s->next;
        }
        s->next = NULL;
        f_tail = s;
    }
    delete ptr;
    return Tree;
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
    char *a;
    char outstring[1000];
    int k, point;
    do
    {
        puts("Введите выpажение:");
        fflush(stdin);
        a = getline();
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
        cout<<outstring<<endl;
        show(f0->t,1);
        cout<<endl;
        cout<<"Результат:"<<calc(f0->t);

    }
    while(getchar()!='n');
    return 0;
}


