import os

import movie

def get_movies_in_directory(target):
	'''Returns movies in a directory'''
	movies = []
	extensions = [".avi",".mkv",".mp4"]
	for root, dirs, files in os.walk(target):
		for f in files:
			for ext in extensions:
				if f.endswith(ext):
					temp_movie = movie.Movie(f)
					movies.append(temp_movie)

	return movies