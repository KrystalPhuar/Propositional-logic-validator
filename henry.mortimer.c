#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize=50; /*enough space for the fmlas we use*/
int inputs=6;

const char NEG = '-';
int i;
int j;
int c;
int d;

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
    if (strlen(list)<1)
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
    char *section = calloc(sectionLength, sizeof(char));
    
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
    int end = (int)strlen(g) - 1;
    int level = 0;
    int x;
    
    for(x=1; x<strlen(g); x++)
    {
        if (*(g+x) == '(')
            level++;
        else if (*(g+x) == ')')
            level--;
        
        if (level == 0 && bc(*(g+x)))
            return segment(g, x+1, end);
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
    {
        return 1;
    }
    else
    {
        return 0;
    }
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
    else if (*g == NEG)
        return isFormula(mytail(g));
    else if (isBin(g))
        return (isFormula(partone(g)) && isFormula(parttwo(g)));
    else
        return 0;
}
int parse(char *g)
{/* return 1 if a proposition, 2 if neg, 3 if binary, ow 0*/
    if(!isFormula(g))
        return 0;
    
    if(prop(*g))
        return 1;
    else if(*g == NEG)
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
    else if (strlen(g) == 2 && *g == NEG && prop(*(g+1)))
        return 1;
    else
        return 0;
}

int type(char *g)
{/*return 0 if not a formula, 1 for literal, 2 for alpha, 3 for beta, 4 for double negation*/
  if(isLiteral(g))
    return 1;
  else if(*g == NEG)
  {
    char* tail = mytail(g);
    if(*tail == NEG)
      return 4;
    else if(connective(tail) == 'v')
      return 2;
    else if (connective(tail) == '^')
      return 3;
    else
      return 2;
  }
  else if (*g == '(')
  {
    if(connective(g) == 'v')
      return 3;
    else if (connective(g) == '^')
      return 2;
    else
      return 3;
  }
  else
    return 0;
}

char *negate(char *string)
{
  char *newString = malloc(sizeof(string)+1);
  
  *newString = NEG;
  for(i = 0; i < strlen(string); i++)
    *(newString+i+1) = *(string+i);
  
  free(string);
  
  return newString;
}

char *firstExpansion(char *g)
{
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
  if(*g == NEG)
    return negate(parttwo(mytail(g)));
  else
    return parttwo(g);
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
    int kind = type(tp->root);
    printf("%d\n", kind);
    switch(kind)
    {
        case(0):
            printf("Error, trying to expand invalid formula\n");
            printf("Erroneuos formula: %s\n", tp->root);
            printf("%i\n", type(tp->root));
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
{
    if (t!=NULL)
    {
        if(parse(t->root) == 0)
            return;
        expand(t);
        complete(t->left);
        complete(t->right);
    }
}

void printTableau(struct tableau *t)
{
    static int z = 0;
    if(t!=NULL)
    {
        z++;
        printTableau(t->left);
        printTableau(t->right);
    }
    
}

char *invert(char *g)
{
  int x;
  char *inverted;
  if(*g == '-')
  {
    inverted = malloc((strlen(g)-1)* sizeof(char));
    for(x = 0; x<(strlen(g)-1); x++)
    {
      *(inverted+x) = *(g+x+1);
    }
  }
  else
  {
    inverted = malloc((strlen(g)+1)* sizeof(char));
    *inverted = NEG;
    for(x = 0; x<strlen(g); x++)
    {
      *(inverted+x+1) = *(g+x);
    }
  }
  return inverted;
}

void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}

int find_above(struct tableau *t, char *g) /*Is g label of current node or above?*/
{
  if(t == NULL)
    return 0;
  else
    if(strcmp(t->root, g)==0)
      return 1;
    else
      return find_above(t->parent, g);
}

int closed1(struct tableau *t) /*check if p and not p at or above t*/
{
  if (t==NULL) 
    return(0);
  else
  {
    char *inverted = invert(t->root);
    int result = find_above(t->parent, inverted);

    return result;
  }
}
      
int closed(struct tableau *t) /*check if either *t is closed 1, or if all children are closed, if so return 1, else 0 */
{
  if(closed1(t))
    return 1;
  else if(t==NULL)
    return 0;

  if(t->right != NULL)
    return (closed(t->left) && closed(t->right));
  else
    return closed(t->left);
}
int main()
{ /*input 6 strings from "input.txt" */
  char *names[inputs];/*to store each of the input strings*/

  for (c=0;c<inputs;c++) names[c]=malloc(Fsize*sizeof(char));/*create enough space*/

  FILE *fp, *fpout, *fopen();

  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}/*ouputs to be sent to "output.txt"*/

  fscanf(fp,"%s %s %s %s %s %s",names[0],names[1], names[2], names[3],names[4],names[5]);/*read input strings from "input.txt"*/

  /*lets check your parser*/
  for(c=0;c<inputs;c++)
  {
    d=parse(names[c]);
    
    switch(d)
    {
      case(0):fprintf(fpout,"%s is not a formula\n", names[c]);break;
      case(1):fprintf(fpout,"%s is a proposition\n",names[c]);break;
      case(2):fprintf(fpout,"%s is a negation\n",names[c]);break;
      case(3):fprintf(fpout,"%s is a binary formula\n",names[c]);break;
      default:fprintf(fpout,"%s is not a formula\n",names[c]);break;
    }
  }

  /*make 6 new tableaus each with name at root, no children, no parent*/

  struct tableau tabs[inputs];

  for(c=0;c<inputs;c++)
  {
    tabs[c].root=names[c];
    tabs[c].parent=NULL;
    tabs[c].left=NULL;
    tabs[c].right=NULL;
      
    /*expand each tableau until complete, then see if closed */

    complete(&tabs[c]);

    printTableau(&tabs[c]);
    if (closed(&tabs[c])) fprintf(fpout,"%s is not satisfiable\n", names[c]);
    else fprintf(fpout,"%s is satisfiable\n", names[c]);
  }
  fclose(fp);
  fclose(fpout);

  return(0); 
}
