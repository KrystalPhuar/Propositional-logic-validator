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
  
  char *tail = malloc(sizeof(char)*(strlen(list)-1));

  for(i=0; i<strlen(list)-1; i++)
    *(tail+i)=*(list+i+1);
  return tail;
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

char bin(char *g)
{/*for binary connective formulas, returns binary connective*/
  int level = 0;
  int i;

  for(i = 0; i < strlen(g); i++)
  {
    if (*(g+i) == '(')
      level++;
    else if(*(g+i) == ')')
      level--;

    if (level == 0 && bc(*(g+i)))
      return *(g+i);
  }

  printf("not a valid binary formula \n");
  return '\0';
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
  if(!isFormula(g))
    return 0;

  if(prop(*g))
    return 1;
  else if(*g == '~')
    return 2;
  else if(*g =='(')
    return 3;
  else
    return 0;
}



int type(char *g)
{/*return 0 if not a formula, 1 for literal, 2 for alpha, 3 for beta, 4 for double negation*/
  int type = parse(g);
  
  if(type == 1)
    return 0;
  else if(type == 2)
  {
  }

}

char *firstexp(char *g)
{/* for alpha and beta formulas*/
//  if (parse(g)==3)/*binary fmla*/  switch(bin(g))
//		     {case('v'): return '0';break;
//		     case('^'): return;break;
//		     case('>'): return(??);break;
//		     default:printf("what the f**k?");return(0);
//		     }
//  if ((parse(g)==2)&& (parse(mytail(g))==2)/*double neg*/) return(??);/*throw away first two chars*/
//
//  if ((parse(g)==2)&&parse(mytail(g))==3) /*negated binary*/ 
//	switch(bin(mytail(g)))
//	{
//		case('v'):return(??);break;
//		case('^'):return(??);break;
//		case('>'): return(??);break;
//	} 
//  return(0);
}		     


char *secondexp(char *g)
{/* for alpha and beta formulas, but not for double negations, returns the second expansion formula*/
}		     

int find_above(struct tableau *t, char *g) /*Is g label of current node or above?*/
{
}

int closed1(struct tableau *t) /*check if p and not p at or above t*/
{
  if (t==NULL) return(0);
  else
    {
    }
}
		  
int closed(struct tableau *t) /*check if either *t is closed 1, or if all children are closed, if so return 1, else 0 */
{
}

void  add_one( struct tableau *t, char *g)/* adds g at every leaf below*/
{
}

void alpha(struct tableau *t, char *g, char *h)/*not for double negs, adds g then h at every leaf below*/
{
}

void  add_two(struct tableau *t, char *g, char *h)/*for beta s, adds g, h on separate branches at every leaf below*/
{
}

void expand(struct tableau *tp)/*must not be null.  Checks the root.  If literal, does nothing.  If beta calls add_two with suitable fmlas, if alpha calls alpha with suitable formulas unless a double negation then � */
{ 
}

void complete(struct tableau *t)/*expands the root then recursively expands any children*/
{ if (t!=NULL)
    { 
      expand(t);
      complete((*t).left);
      complete((*t).right); 
    }
}

int main()
{ /*input 6 strings from "input.txt" */
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
}
