#include "randcpuid.h"
#include <dlfcn.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

    /* Now that we know we have work to do, arrange to use the
       appropriate library.  */
unsigned long long (*rand64) (void);
void* library;
char* error;

if(rdrand_supported()){
  library = dlopen("./randlibhw.so", RTLD_NOW);
  if(!library)
  {
    printf("dlopen() error - %s\n", dlerror());
    exit(1);
  }
  printf("HW\n");
  rand64 = dlsym(library, "hardware_rand64");
  error = dlerror();
  if(error != NULL)
  {
    printf("dlsym hardware_rand64 errror - %s\n",dlerror());
    exit(1);
  }

}
else{
  library = dlopen("./randlibsw.so", RTLD_NOW);
  if(!library)
  {
    printf("dlopen() error - %s/n", dlerror());
    exit(1);
  }
  printf("SW\n");
  rand64 = dlsym(library, "software_rand64");
  error=dlerror();
  if(error != NULL)
  {
    printf("dlsym software_rand64 error - %s\n", dlerror());
    exit(1);
  }
}
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      printf("%llu\n", x);
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      return 1;
    }
  dlclose(library);
  return 0;
}
