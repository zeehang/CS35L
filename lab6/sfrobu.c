#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int comparisonCount = 0;

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
  comparisonCount++;
  return frobcmp(a1, b1);
}

int main()
{
  int wordCount = 0;
  int letterCount = 0;
  char* individual = (char*)malloc(sizeof(char));
  //char** wordArray = (char**)malloc(sizeof(char*));
  char input;
  read(0, &input, sizeof(char));
  int finalchar = 0;
  int lastloop = 0;
  /*if(ferror(stdin))
    {
      fprintf(stderr, "Read file error");
      exit(1);
    }
  */
  struct stat fileInfo;
  if(fstat(0, &fileInfo)<0)
    {
      fprintf(stderr, "Read file error");
      exit(1);
    }
  char** wordArray = (char**)malloc(fileInfo.st_size);
  while (lastloop == 0)
    {
      if(finalchar==1)
	{
	  individual[letterCount] = ' ';
	  lastloop = 1;
	}
      else
	{
	  individual[letterCount] = input;
	}
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
      /* if (finalchar ==1)
	{
	  lastloop = 1;
	  individual[letterCount+1] = ' ';
	  char* checkFinal = realloc(individual, (letterCount+2)*sizeof(char));
	  if (check == NULL)
	    {
	      fprintf(stderr, "Memory allocation error");
	      free(individual);
	      exit(1);
	    }
	  individual= checkFinal;
	  }*/
      /* char* checkFinal = realloc(individual, (letterCount+2)*sizeof(char));
      if (check == NULL)
        {
          fprintf(stderr, "Memory allocation error");
          free(individual);
          exit(1);
        }
      */
      if (input == ' ' || finalchar == 1) //end of word
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
      int  checknext = read(0, &input, sizeof(char));
        if(ferror(stdin))
	  {
	    fprintf(stderr, "Read file error");
	    exit(1);
	  }
      if(checknext <= 0)
	{
	  finalchar = 1;
	}
      
     }
  //sort array
  qsort(wordArray, wordCount, sizeof(char*), frobcmpalt);
  for(int i = 0; i < wordCount; i++)
    {
      int flag = 1;
      for(int j = 0; flag == 1; j++)
	{
	  //if(putchar(wordArray[i][j]) != EOF)
	  if(wordArray[i][j] != EOF)
	  {
	    //char* display = &wordArray[i][j];
	    write(1, &wordArray[i][j], sizeof(char));
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
  free(wordArray);
  free(individual);
  fprintf(stderr, "Comparisons: %i", comparisonCount);
  fprintf(stderr, "\n");
  exit(0);
}
  // printf("%i", frobcmp("*{_CIA\030\031 ", "*`_GZY\v "));
