1. In order to first start parallelizing the program, I started by taking
a look at the presentation slides presented in class. I decided to utilize
a very similar format for creating nthreads and joining them. This meant
I had to move the majority of the program out of main and into its
own function.

This didn't work entirely at first - I was greeted with a lot of compile
errors, so I had to make some variables global.

In order to make sure there were no race conditions - rather than having
each thread print out its own info to the file, I saved all the information
in an array and created a file at the end of the program once all the
threads had been joined.

My strategy to parallelzing the program was to essentially divide
the for loop figuring out the colors so that each thread handled a different
"width" of the pixel grid. The biggest problem I ran into here was that when
the number of pixels wasn't cleanly divisible by the numbe of threads, which
would leave line(s) of unrendered pixels. I was able to fix this by
extending the final for loop n times, where n was equal to the modulus
of the number of pixels and threads.

Let's take a look at how the program fared time wise:
I've copied the times in for convenience

time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m54.245s
user	0m54.187s
sys	0m0.002s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m28.366s
user	0m54.854s
sys	0m0.008s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m18.775s
user	0m55.259s
sys	0m0.002s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m12.094s
user	0m57.086s
sys	0m0.002s


As we can see, more threads increased the speed of the parallelized program.
Using two threads doubled the time, while subsequent additions (4, 8 threads)
reduced the time further by around 1/3. This speed up makes sense,
as instead of going pixel by pixel, the program is now able to split up the
image between multiple thread and work on multiple print outs at once.
