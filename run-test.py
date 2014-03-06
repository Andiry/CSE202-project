#!/usr/bin/python
#coding=utf-8

import time
import os
import sys

def do_work(filename):
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./linear %d %d %s %d %d' %(query, 0, filename, 2, 512))
			i += 1
		query += 1
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./binary %d %d %s %d %d' %(query, 0, filename, 2, 512))
			i += 1
		query += 1
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./btree %d %d %s %d %d' %(query, 0, filename, 2, 512))
			i += 1
		query += 1
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./bloom_filter %d %d %s %d %d' %(query, 1, filename, 2, 512))
			i += 1
		query += 1

def main():
	date = time.strftime("%Y-%m-%d_%X", time.localtime(time.time()))
	filename = "./results/results_" + date + ".csv"
	filename = filename.replace(':', '-')
	print filename
	f = open(filename, 'w')
	f.write("Algorithm,Query,CPU time (ns),Disk IO,Bloom-filter error\n")
	file.close(f)

	do_work(filename)

main()
