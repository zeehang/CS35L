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

#class comm:
#    def __init__(self, filename):
#        f1 = open(filename, 'r')
#        self.lines = f1.readlines()
#        f1.close()

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

    for i in compare1:
        print i
    for f in compare2:
        print f
    c3 = []
    file2num=len(compare2)
    file1num=len(compare1)
    file1num-=1
    file2num-=1
    m=0
    n=0
    while(m<file1num):
        while(n<file2num):
            checker=compare1[m]
            m+=1
            checkee=compare2[n]
            n+=1
            if checker==checkee:
                c3.append(checker)
                n-=1
                m-=1
                compare1.remove(checkee)
                compare2.remove(checkee)
                file1num-=1
                file2num-=1

    for x in compare1:
        print ("Col1" + x)
    for y in compare2:
        print("\t" + y)
    for z in c3:
        print("\t\t" +  z)
if __name__ == "__main__":
    main()
