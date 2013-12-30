'''
Copyright (C) 2013 - Anthony Crognale
See LICENSE for licensing details

amot - another movie organization tool
'''

import sys

from scanner import get_movies_in_directory

if __name__ == "__main__":
	if sys.argv[1] == "scan":
		print get_movies_in_directory('.')
