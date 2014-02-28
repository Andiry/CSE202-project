#!/usr/bin/python
#coding=utf-8

import time
import os
import sys

def main():
	filename = "/root/test/converted1MQuery.txt"
	f = open(filename, 'r')
	id1 = 0
	for line in f:
		new_file = "./queries/" + str(id1)
		print new_file
		f1 = open(new_file, 'w')
		f1.write(line)
		file.close(f1)
		id1 = id1 + 1
		if id1 > 100: break
	file.close(f)

main()
