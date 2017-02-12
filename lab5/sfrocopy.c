#include <stdlib.h>
#include <stdio.h>

int frobcmp(char const* a, char const* b)
{
  while((*a != ' ') && (*b != ' '))
    {
      if((*a^42) > (*b^42))
	{
	  return 1;
	}
      else if ((*b^42) > (*a^42))
	{
	  return -1;
	}
      else
	{
	  a++;
	  b++;
	}
    }
  if((*a) != ' ' && (*b) == ' ')
    {
      return -1;
    }
  else if((*a) == ' ' && (*b) != ' ')
    {
      return 1;
    }
  else{
    return 0;
  }
}

int frobcmpalt(const void* a, const void* b)
{
  char const* a1 = *(char const**)a;
  char const* b1 = *(char const**)b;
  return frobcmp(a1, b1);
}

int main()
{
  int wordCount = 0;
  int letterCount = 0;
  char* individual = (char*)malloc(sizeof(char));
  char** wordArray = (char**)malloc(sizeof(char*));
  char input = getchar();
  if(ferror(stdin))
    {
      fprintf(stderr, "Read file error");
      exit(1);
    }
  while (input != EOF)
    {
      individual[letterCount] = input;
      char* check = realloc(individual, (letterCount+2)*sizeof(char));
      if (check == NULL)
	{
	  fprintf(stderr, "Memory allocation error");
	  free(individual);
	  exit(1);
	}
      else
	{
	  letterCount++;
	  individual = check;
	}
      if (input == ' ') //end of word
	{
	  wordArray[wordCount] = individual;
	  char** recheck = realloc(wordArray, (wordCount+2)*sizeof(char*));
	  if (recheck == NULL)
	    {
	      fprintf(stderr, "Memory allocatoin error");
	      free(wordArray);
	      exit(1);
	    }
	  else
	    {
	      wordArray = recheck;
	      wordCount++;
	      individual = NULL;
	      individual = (char*)malloc(sizeof(char));
	      letterCount = 0;
	    }
	}
      char checknext = getchar();
      if(check == NULL)
	{
	  fprintf(stderr, "Memory allocation error");
          free(individual);
          exit(1);
	}
      if(input == EOF)
	{
	  break;
	}
      input = checknext;
     }
  //sort array
  qsort(wordArray, wordCount, sizeof(char*), frobcmpalt);
  for(int i = 0; i < wordCount; i++)
    {
      int flag = 1;
      for(int j = 0; flag == 1; j++)
	{
	  if(putchar(wordArray[i][j]) != EOF)
	    {
	      if(wordArray[i][j]==' ')
		{
		  flag = 0;
		}
	    }
	  else
	    {
	      fprintf(stderr, "Write error");
	      exit(1);
	    }
	  
	}
    }

      exit(0);
}
  // printf("%i", frobcmp("*{_CIA\030\031 ", "*`_GZY\v "));
