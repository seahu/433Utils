#!/usr/bin/python

import time
import sys

while 1==1:
    code=sys.stdin.readline()
    if code=='' : continue
    code=code[:-1] #delete enter from end string
    code=code[:-2] #delete protocol number
    if len(code) > len('Received '):
	if code[:len('Received ')]=='Received ':
	    code=code[len('Received '):]
    #print code
    ncode=""
    p=0
    for c in code:
	p=p+1
	if p==1 :
	    c1=c
	    continue
	p=0
	c2=c
	if (c1=='1' and c2=='0') : ncode=ncode+'1'
	elif (c1=='0' and c2=='1') : ncode=ncode+'0'
	else : ncode=ncode+'P'
    print ncode