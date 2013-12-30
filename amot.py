'''
Copyright (C) 2013 - Anthony Crognale
See LICENSE for licensing details

amot - another movie organization tool
'''

import sys

import scanner

if __name__ == "__main__":
	if sys.argv[1] == "scan":
		print scanner.get_movies_in_directory('.')
