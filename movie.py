def get_words(words_file):
	with open(words_file) as f:
		return f.readlines()

def clean_title(title):
	WORDS = get_words('words.txt')
	JUNK = ".-_;|[]{}<>="

	for word in WORDS:
		title.replace(word, ' ')

	for char in JUNK:
		title.replace(char, ' ')
		
	return title

class Movie(object):
	def __init__(self, name=None):
		self.name = name
		clean_title(self.name)

	def __repr__(self):
		return self.name

		