#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if(argc != 3)
    {
      fprintf(stderr, "Error: Please use two arguments for this function\n");
      exit(1);
    }

  char *first = argv[1];
  char *second = argv[2];
  /*  while(1)
    {
      if(first[i] != '\0' &&  second[i] != '\0')
	{
	  i++;
	}
      else if (first[i] == '\0' && second[i] == '\0')
	{
	  break;
	}
      else
	{
	  fprintf(stderr, "Inputs are different lengths");
	  exit(1);
	}
    }
  */
  //check to see inputs are the same size
  int firstlen = strlen(first);
  int secondlen = strlen(second);
  if(firstlen != secondlen)
    {
      fprintf(stderr, "Inputs are different lengths");
      exit(1);
    }
  //check for duplicate bytes in from
  for (int i = 0; i < firstlen; i++)
    {
      for (int j = i + 1; j < firstlen; j++)
	{
	  if(first[i] == first[j])
	    {
	      fprintf(stderr, "First term contains duplicate bytes");
	      exit(1);
	    }
	}
    }
  char comp;
  // int loopcheck = read(0, &comp, 1);
  comp = getchar();
  while(comp != EOF)
    {
      int k = 0;
      while (k < firstlen)
	{
	  if (first[k] == comp)
	    {
	      break;
	    }
	  else
	    {
	      k++;
	    }
	}
      if (k == firstlen)
	{
	  //write(1, &comp, 1);
	  putchar(comp);
	}
      else
	{
	  comp = second[k];
	  //write(1, &comp, 1);
	  putchar(second[k]);
	}
      
      comp = getchar();
    }
  exit(0);
}
