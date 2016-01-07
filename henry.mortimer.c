#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50; /*enough space for the fmlas we use*/
int inputs=6;


int i;
int j;

struct tableau {
  char *root;
  struct  tableau *left;
  struct tableau *right;
  struct tableau *parent;
}*tab, *node, *node1, *kid, *pa;

/* Use p, q, r, s for propositions.  Use ~ for negation.  Use v for OR, use ^ for AND, use > for implies.  Brackets are (, ). */


/* List processing methods  */

char *mytail(char *list)  /*given non-empty string, returns string without the first char*/
{
  if (strlen(list)>0)
  {
    printf("invalid string, length less than 0 \n");
    return NULL;
  }
  

  return list+1;
}

char *segment(char *list, int i, int j)/* characters from pos i up to j-1, provided i<=j*/
{
  if(i>j)
  {
    printf("error i is greater than j \n");
    return NULL;
  }
  int sectionLength = j-i;
  char *section = malloc(sizeof(char)*sectionLength);

  int x;

  for(x=0; x<sectionLength; x++)
   *(section+x) = *(list+x+i);

  return section;
}

/* Basics.  Recognise propositions and connectives.  */

int prop(char x)
{if((x=='p')||(x=='q')||(x=='r')||(x=='s')) return(1);else return(0);}

int bc(char x)
{if ((x=='v')||(x=='^')||(x=='>')) return(1);else return(0);}


/* The actual parsing methods.  */
char *partone(char *g)
{/* for binary connective formulas, returns first part*/
  int start = 1;
  int level = 0;
  int x;
  for(x=1; x<strlen(g); x++)
  {
    if (*(g+x)=='(')
      level++;
    else if (*(g+x)==')')
      level--;

    if (level == 0 && bc(*(g+x)))
        return segment(g, start, x);
  }
  printf("not a valid binary formula \n");
  return NULL;
}

char *parttwo(char *g)
{/* for binary connective formulas, returns second part*/
  int end = strlen(g) - 1;
  int level = 0;
  int x;

  for(x=1; x<strlen(g); x++)
  {
    if (*(g+x) == '(')
      level++;
    else if (*(g+x) == ')')
      level--;

    if (level == 0 && bc(*(g+x)))
      return segment(g, x, end);
  }

  printf("not a valid binary formula \n");
  return NULL;
}

int isBin(char *g)
{
  int level = 0;
  int connectives = 0;;
  int i;

  if(*g != '(' || *(g+strlen(g)-1) != ')')
    return 0;

  for(i=1; i<strlen(g)-1; i++)
  {
    if (*(g+i) == '(')
      level++;
    if (*(g+i) == ')')
      level--;
    if (level == 0 && bc(*(g+i)))
      connectives++;
  }

  if (connectives == 1)
    return 1;
  else
    return 0;
}

char connective(char *g)
{
  int level = 0;
  
  for(i=1; i<strlen(g)-1; i++)
  {
    if (*(g+i) == '(')
      level++;
    if (*(g+i) == ')')
      level--;
    if (level == 0 && bc(*(g+i)))
      return *(g+i);
  }

  return '\0';
}

int isFormula(char *g)
{
  if(strlen(g)==1 && prop(*g))
    return 1;
  else if (*g == '~')
    return isFormula(mytail(g));
  else if (isBin(g))
    return (isFormula(partone(g)) && isFormula(parttwo(g)));
  else
    return 0;
}
int parse(char *g)
{/* return 1 if a proposition, 2 if neg, 3 if binary, ow 0*/
  if(prop(*g))
    return 1;
  else if(*g == '~')
    return 2;
  else if(*g =='(')
    return 3;
  else
    return 0;
}

int isLiteral(char *g)
{
  if(strlen(g)==1 && prop(*g))
    return 1;
  else if (strlen(g) == 2 && *g == '~' && prop(*(g+1)))
    return 1;
  else
    return 0;
}

int type(char *g)
{/*return 0 if not a formula, 1 for literal, 2 for alpha, 3 for beta, 4 for double negation*/
  if(!isFormula(g))
    return 0;
  else if(isLiteral(g))
    return 1;
  else if(*g == '~')
  {
    char* tail = mytail(g);
    if(*tail == '~')
      return 4;
    else if(connective(tail) == 'v')
      return 2;
    else if (connective(tail) == '^')
      return 3;
    else
      return 2;
  }
  else
  {
    if(connective(g) == 'v')
      return 3;
    else if (connective(g) == '^')
      return 2;
    else
      return 3;
  }
}

char *negate(char *string)
{
  char *newString = malloc(sizeof(string)+1);

  *newString = '~';
  for(i = 0; i < strlen(string); i++)
    *(newString+i+1) = *(string+i);

  free(string);

  return newString;
}

char *firstExpansion(char *g)
{
  if(*g == '~')
  {
    switch(connective(mytail(g)))
    {
      case '>':
        return partone(mytail(g));
        break;
      case '^':
        return negate(partone(mytail(g)));
        break;
      case 'v':
        return negate(partone(mytail(g)));
        break;
      default:
        printf("Error expanding first part\n");
        return NULL;
    }
  }
  else
  {
    switch(connective(g))
    {
      case '>':
        return negate(partone(g));
        break;
      case '^':
        return partone(g);
        break;
      case 'v':
        return partone(g);
        break;
      default:
        printf("Error expanding first part\n");
        return NULL;
    }
  }
}

char *secondExpansion(char *g)
{
  if(*g == '~')
    return negate(parttwo(mytail(g)));
  else
    return parttwo(g);
}

int find_above(struct tableau *t, char *g) /*Is g label of current node or above?*/
{
  return 0;
}

int closed1(struct tableau *t) /*check if p and not p at or above t*/
{
  if (t==NULL) return(0);
  else
    {
    }
  return 0;
}
		  
int closed(struct tableau *t) /*check if either *t is closed 1, or if all children are closed, if so return 1, else 0 */
{
  return 0;
}

struct tableau *add_one( struct tableau *t, char *g)/* adds g at every leaf below*/
{
  struct tableau *newNode = malloc(sizeof(struct tableau));

  newNode->root = g;
  newNode->parent = t;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}
void alpha(struct tableau *t, char *g, char *h)/*not for double negs, adds g then h at every leaf below*/
{
  if(t->left == NULL)
  {
    t->left = add_one(t, g);
    t->left->left = add_one(t->left, h);
  }
  else
  {
    alpha(t->left, g, h);
    if(t->right != NULL)
      alpha(t->right, g, h);
  }
}

void  beta(struct tableau *t, char *g, char *h)/*for beta s, adds g, h on separate branches at every leaf below*/
{
  if(t->left == NULL)
  {
    t->left = add_one(t, g);
    t->right = add_one(t, h);
  }
  else
  {
    beta(t->left, g, h);
    if(t->right != NULL)
    {
      beta(t->right, g, h);
    }
  }
}



void expand(struct tableau *tp)/*must not be null.  Checks the root.  If literal, does nothing.  If beta calls add_two with suitable fmlas, if alpha calls alpha with suitable formulas unless a double negation then � */
{ 
  char *formula = tp->root;

  switch(type(formula))
  {
    case(0):
      printf("Error, trying to expand invalid formula");
      break;
    case(1):
      break;
    case(2):
      alpha(tp, firstExpansion(formula), secondExpansion(formula));
      break;
    case(3):
      beta(tp, firstExpansion(formula), secondExpansion(formula));
      break;
    case(4):
      tp->root = (formula + 2);
      expand(tp);
      break;
  }
      
}

void complete(struct tableau *t)/*expands the root then recursively expands any children*/
{ if (t!=NULL)
    { 
      expand(t);
      complete(t->left);
      complete(t->right); 
    }
}

int main()
{ /*input 6 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/



  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
 
  /*lets check your parser*/
  for(i=0;i<inputs;i++)
    {j=parse(names[i]);
      switch(j)
  {
  case(0):fprintf(fpout,"%s is not a formula", names[i]);break;
  case(1):fprintf(fpout,"%s is a proposition",names[i]);break;
  case(2):fprintf(fpout,"%s is a negation",names[i]);break;
  case(3):fprintf(fpout,"%s is a binary formula",names[i]);break;
  default:fprintf(fpout,"%s is not a formula",names[i]);break;
  }
    }
 
  /*make 6 new tableaus each with name at root, no children, no parent*/

  struct tableau tabs[inputs];

  for(i=0;i<inputs;i++)
    {
      tabs[i].root=names[i];
      tabs[i].parent=NULL;
      tabs[i].left=NULL;
      tabs[i].right=NULL;

      /*expand each tableau until complete, then see if closed */ 

     complete(&tabs[i]);
      if (closed(&tabs[i])) fprintf(fpout,"%s is not satisfiable\n", names[i]);
      else fprintf(fpout,"%s is satisfiable\n", names[i]);
    }
 
  fclose(fp);
  fclose(fpout);
 
  return(0);
}
