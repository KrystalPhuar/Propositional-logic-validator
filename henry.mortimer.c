#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50; /*enough space for the fmlas we use*/
int inputs=6;

const char NEG = '-';

int i;
int j;

struct tableau {
  char *root;
  struct  tableau *left;
  struct tableau *right;
  struct tableau *parent;
}*tab, *node, *node1, *kid, *pa;

/* Use p, q, r, s for propositions.  Use - for negation.  Use v for OR, use ^ for AND, use > for implies.  Brackets are (, ). */


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
<<<<<<< HEAD
<<<<<<< HEAD
  char *section = calloc(sectionLength, sizeof(char));
=======
  char *section = malloc(sizeof(char)*sectionLength);
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
  char *section = malloc(sizeof(char)*sectionLength);
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc

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
<<<<<<< HEAD
<<<<<<< HEAD
  else if (*g == NEG)
    return isFormula(mytail(g));
  else if (isBin(g))
  {
    char *first = partone(g);
    char *second = parttwo(g);
    int result = isFormula(first) && isFormula(second);
    free(first);
    free(second);
    return result;
  }
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  else if (*g == '~')
    return isFormula(mytail(g));
  else if (isBin(g))
    return (isFormula(partone(g)) && isFormula(parttwo(g)));
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  else
    return 0;
}
int parse(char *g)
{/* return 1 if a proposition, 2 if neg, 3 if binary, ow 0*/
<<<<<<< HEAD
<<<<<<< HEAD
  if(prop(*g))
    return 1;
  else if(*g == NEG)
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  if(!isFormula(g))
    return 0;

  if(prop(*g))
    return 1;
  else if(*g == '~')
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
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
<<<<<<< HEAD
<<<<<<< HEAD
  else if (strlen(g) == 2 && *g == NEG && prop(*(g+1)))
=======
  else if (strlen(g) == 2 && *g == '~' && prop(*(g+1)))
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
  else if (strlen(g) == 2 && *g == '~' && prop(*(g+1)))
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
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
<<<<<<< HEAD
<<<<<<< HEAD
  else if(*g == NEG)
  {
    char* tail = mytail(g);
    if(*tail == NEG)
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  else if(*g == '~')
  {
    char* tail = mytail(g);
    if(*tail == '~')
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
      return 4;
    else if(connective(tail) == 'v')
      return 2;
    else if (connective(tail) == '^')
      return 3;
    else
      return 2;
  }
<<<<<<< HEAD
<<<<<<< HEAD
  else if(connective(g) == '(')
=======
  else
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
  else
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  {
    if(connective(g) == 'v')
      return 3;
    else if (connective(g) == '^')
      return 2;
    else
      return 3;
  }
<<<<<<< HEAD
<<<<<<< HEAD
  else
    return 0;

=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
}

char *negate(char *string)
{
  char *newString = malloc(sizeof(string)+1);

<<<<<<< HEAD
<<<<<<< HEAD
  *newString = NEG;
=======
  *newString = '~';
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
  *newString = '~';
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  for(i = 0; i < strlen(string); i++)
    *(newString+i+1) = *(string+i);

  free(string);

  return newString;
}

char *firstExpansion(char *g)
{
<<<<<<< HEAD
<<<<<<< HEAD
  if(*g == NEG)
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
=======
  if(*g == '~')
  {
    switch(connective(mytail(g)))
    {
=======
  if(*g == '~')
  {
    switch(connective(mytail(g)))
    {
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
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
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
    }
  }
  else
  {
    switch(connective(g))
    {
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
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
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
    }
  }
}

char *secondExpansion(char *g)
{
<<<<<<< HEAD
<<<<<<< HEAD
  if(*g == NEG)
    return negate(parttwo(mytail(g)));
  else
    return parttwo(g);
}


char *invert(char *g)
{
  char *inverted;
  if(*g == NEG)
  {
    inverted = calloc(strlen(g)-1, sizeof(char));
    strcpy(inverted, mytail(g));
  }
  else
  {
    inverted = calloc(strlen(g)+1, sizeof(char));
    *inverted = NEG;
    strcpy(mytail(inverted), g);
  }
  return inverted;
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  if(*g == '~')
    return negate(parttwo(mytail(g)));
  else
    return parttwo(g);
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
}

int find_above(struct tableau *t, char *g) /*Is g label of current node or above?*/
{
<<<<<<< HEAD
<<<<<<< HEAD
  if(t == NULL)
    return 0;
  else
    if(strcmp(t->root, g))
      return 1;
    else
      return find_above(t->parent, g);
=======
  return 0;
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
  return 0;
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
}

int closed1(struct tableau *t) /*check if p and not p at or above t*/
{
<<<<<<< HEAD
<<<<<<< HEAD
  if (t==NULL) 
    return(0);
  else
  {
    char *inverted = invert(t->root);
    int result = find_above(t->parent, inverted);

    free(inverted);
    return result;
  }
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  if (t==NULL) return(0);
  else
    {
    }
  return 0;
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
}
		  
int closed(struct tableau *t) /*check if either *t is closed 1, or if all children are closed, if so return 1, else 0 */
{
<<<<<<< HEAD
<<<<<<< HEAD
  if(closed1(t))
    return 1;
  else if(t==NULL)
    return 0;

  if(t->right != NULL)
    return closed(t->left) && closed(t->right);
  else
    return closed(t->left);
=======
  return 0;
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
  return 0;
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
}

struct tableau *add_one( struct tableau *t, char *g)/* adds g at every leaf below*/
{
  struct tableau *newNode = malloc(sizeof(struct tableau));

  newNode->root = g;
  newNode->parent = t;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
<<<<<<< HEAD
}

void doubleNeg(struct tableau *t, char *g)
{
  if(t->left == NULL)
    t->left = add_one(t, g);
  else
  {
    doubleNeg(t->left,g);
    if(t->right != NULL)
      doubleNeg(t->right,g);
  }
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
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
<<<<<<< HEAD
<<<<<<< HEAD
      doubleNeg(tp, formula+2);
=======
      tp->root = (formula + 2);
      expand(tp);
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
      tp->root = (formula + 2);
      expand(tp);
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
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
<<<<<<< HEAD
<<<<<<< HEAD
  printf("Help\n");
  char *names[inputs];/*to store each of the input strings*/
  printf("Starting\n");
  for (i=0;i<inputs;i++) names[i]=malloc(Fsize*sizeof(char));/*create enough space*/

  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
  printf("Parsing strings\n");
  /*lets check your parser*/
  for(i=0;i<inputs;i++)
  {
    j=parse(names[i]);
    switch(j)
    {
      case(0):fprintf(fpout,"%s is not a formula\n", names[i]);break;
      case(1):fprintf(fpout,"%s is a proposition\n",names[i]);break;
      case(2):fprintf(fpout,"%s is a negation\n",names[i]);break;
      case(3):fprintf(fpout,"%s is a binary formula\n",names[i]);break;
      default:fprintf(fpout,"%s is not a formula\n",names[i]);break;
    }
  }

  /*make 6 new tableaus each with name at root, no children, no parent*/

  struct tableau tabs[inputs];
  
  printf("Completing tabs \n");
  for(i=0;i<inputs;i++)
  {
    tabs[i].root=names[i];
    tabs[i].parent=NULL;
    tabs[i].left=NULL;
    tabs[i].right=NULL;

    /*expand each tableau until complete, then see if closed */
    complete(&tabs[i]);
   // if (closed(&tabs[i])) fprintf(fpout,"%s is not satisfiable\n", names[i]);
   // else fprintf(fpout,"%s is satisfiable\n", names[i]);
  }

 // fclose(fp);
 // fclose(fpout);

  return(0); 
=======
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
  char *testString = "(p>q))";

  int result = parse(testString);

  printf("%d\n", result);
  
  return 0;
//  char *names[inputs];/*to store each of the input strings*/
//
//  for (i=0;i<inputs;i++) names[i]=malloc(Fsize);/*create enough space*/
//
//
//
//  FILE *fp, *fpout, *fopen();
//
//  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
//  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/
//
//  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/
// 
//  /*lets check your parser*/
//  for(i=0;i<inputs;i++)
//    {j=parse(names[i]);
//      switch(j)
//  {
//  case(0):fprintf(fpout,"%s is not a formula", names[i]);break;
//  case(1):fprintf(fpout,"%s is a proposition",names[i]);break;
//  case(2):fprintf(fpout,"%s is a negation",names[i]);break;
//  case(3):fprintf(fpout,"%s is a binary formula",names[i]);break;
//  default:fprintf(fpout,"%s is not a formula",names[i]);break;
//  }
//    }
// 
//  /*make 6 new tableaus each with name at root, no children, no parent*/
//
//  struct tableau tabs[inputs];
//
//  for(i=0;i<inputs;i++)
//    {
//      tabs[i].root=names[i];
//      tabs[i].parent=NULL;
//      tabs[i].left=NULL;
//      tabs[i].right=NULL;
//
//      /*expand each tableau until complete, then see if closed */ 
//
//     complete(&tabs[i]);
//      if (closed(&tabs[i])) fprintf(fpout,"%s is not satisfiable\n", names[i]);
//      else fprintf(fpout,"%s is satisfiable\n", names[i]);
//    }
// 
//  fclose(fp);
//  fclose(fpout);
// 
//  return(0); 
<<<<<<< HEAD
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
=======
>>>>>>> parent of 39a12cc... fixed wierd ass bug with malloc
}
