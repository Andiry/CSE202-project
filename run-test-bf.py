#!/usr/bin/python
#coding=utf-8

import time
import os
import sys

def do_work(filename):
	for bf_count in [1, 2, 4, 8]:
	    for bf_size in [128, 256, 512, 1024]:
	      print bf_count
	      print bf_size
	      query = 0
	      while query <= 100:
		i = 0
		while i < 10:
			os.system('./bloom_filter %d %d %s %d %d' %(query, 1, filename, bf_count, bf_size))
			i += 1
		query += 1

def main():
	date = time.strftime("%Y-%m-%d_%X", time.localtime(time.time()))
	filename = "./results/results_" + date + ".csv"
	filename = filename.replace(':', '-')
	print filename
	f = open(filename, 'w')
	f.write("Algorithm,Query,CPU time (ns),Disk IO,Bloom-filter error,Hash cycles,Bloom-filter size (byte) \n")
	file.close(f)

	do_work(filename)

main()
