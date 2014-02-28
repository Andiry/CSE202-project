#!/usr/bin/python
#coding=utf-8

import time
import os
import sys

def main():
	filename = "/root/test/convertedIndex100GB.txt"
	f = open(filename, 'r')
	id1 = 0
	for line in f:
		new_file = "./files/" + str(id1) +".txt"
		print new_file
		f1 = open(new_file, 'w')
		f1.write(line)
		file.close(f1)
		id1 = id1 + 1
	file.close(f)

main()
