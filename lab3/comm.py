#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import locale, string, random, sys
from optparse import OptionParser

class comm:
    def __init__(self, filename, supressone, supresstwo, supressthree, unsorted):
        f1 = open(filename, 'r')
        self.lines = f1.readlines()
        f1.close()

#    def lines(self):
#        linereturn = list(self.lines)
#        return linereturn

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="supressone", default=False,
                      help="don't show column 1 - lines unique to line file 1")
    parser.add_option("-2",
                      action="store_true", dest="supresstwo", default=False,
                      help="don't show column2 - lines unique fo file 2")
    parser.add_option("-3",
                      action="store_true", dest="supressthree", default=False,
                      help="don't show column 3- lines from both files")
    parser.add_option("-u",
                      action="store_true", dest="unsorted", default=False,
                      help="use comm with unsorted files")
    options, args = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        parser.error("wrong number of operands")
    input_file1 = args[0]
    input_file2 = args[1]
#    generator = comm(supressone,supresstwo,supressthree,unsorted)
    try:
        if input_file1=="-":
            compare1=sys.stdin.read().splitlines()
        else:
            f1 = open(input_file1, 'r')
            compare1  = list(f1.read().splitlines())
            f1.close()
        if input_file2=="-":
            compare2=sys.stdin.read().splitlines()
        else:
            f2 = open(input_file2, 'r')
            compare2 = list(f2.read().splitlines())
            f2.close()            
    except:
        parser.error("Input error, please use text file")

    dictfirst = {}
    dictsecond = {}

 #   for i in compare1:
 #       print i
 #   for f in compare2:
 #       print f
    c3 = []
    file2num=len(compare2)
    file1num=len(compare1)
    file1num-=1
    file2num-=1
    m=0
    n=0
    match=False
    while(len(compare1)!=0):
        checker=compare1[0]
#        print checker
        for n in compare2:
            match=False
            if checker==n:
                c3.append((n,3))
                compare2.remove(n)
                del compare1[0]
                match=True
                break
        if match==False:
            c3.append((checker,1))
            del compare1[0]
            match
        m+=1
    for k in compare2:
        c3.append((k,2))
    if options.unsorted==False:
        c3.sort()
    for z in c3:
        finalprint=""
        if z[1]==1 and options.supressone==False:
            print z[0]
        if z[1]==2 and options.supresstwo==False:
            if options.supressone==False:
                finalprint+="\t"
            print (finalprint+z[0])
        if z[1]==3 and options.supressthree==False:
            if options.supressone==False:
                finalprint+="\t"
            if options.supresstwo==False:
                finalprint+="\t"
            print (finalprint+z[0])
    
if __name__ == "__main__":
    main()
