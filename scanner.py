from hachoir_parser import createParser
from hachoir_metadata import extractMetadata
from hachoir_core.cmd_line import unicodeFilename

import os

import movie

from movie import clean_title

def get_movies_in_directory(target):
	'''Returns movies in a directory'''
	movies = []
	extensions = [".avi",".mkv",".mp4"]
	for root, dirs, files in os.walk(target):
		for f in files:
			for ext in extensions:
				if f.endswith(ext):
					title = extract_title(f)
					temp_movie = movie.Movie(clean_title(title))
					movies.append(temp_movie)

	return movies

def extract_title(filename):
	filename, realname = unicodeFilename(filename), filename
	parser = createParser(filename, realname)
	metadata = extractMetadata(parser)

	text = metadata.exportPlaintext()

	return metadata.get('title')