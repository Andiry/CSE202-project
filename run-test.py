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
#			os.system('./linear %d %d %s' %(query, 0, filename))
			i += 1
		query += 1
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./binary %d %d %s' %(query, 0, filename))
			i += 1
		query += 1
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./btree %d %d %s' %(query, 0, filename))
			i += 1
		query += 1
	query = 0
	while query <= 100:
		i = 0
		while i < 10:
			os.system('./bloom_filter %d %d %s' %(query, 1, filename))
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
