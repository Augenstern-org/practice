'''
Write a function select_words_by_char_count(words, k, S) that receives as input:
- words: a list of strings.
- k: an integer.
- S: a set of characters.

The function returns a dictionary where:
- each key is a word from the input list,
- each value is the count of characters from S present in that word,
- but includes only words that contain at least k characters from S.

To organize your solution, implement and use these helper functions:

1. count_chars_in_set(word, S): Returns the number of characters in word that are present in S.

2. filter_words_by_count(words, k, S): Uses count_chars_in_set to return a dictionary as described above.

3. select_words_by_char_count(words, k, S): Calls filter_words_by_count and returns its output.

Example:
words = ['hello', 'world', 'language', 'apple', 'orange', 'banana', 'friend', 'education', 'tiger']
k = 3
S = {'a','e','i','o','u'}
select_words_by_char_count(words, k, S)
output: {'language': 4, 'education': 5, 'orange': 3, 'banana': 3}
'''

def count_chars_in_set(word, S):
    # Your implementation here
    pass

def filter_words_by_count(words, k, S):
    # Your implementation here
    pass

def select_words_by_char_count(words, k, S):
    # Your implementation here
    # count ch
    counter = [] # tuple list
    for word in words:
        temp = 0
        for ch in word:
            if ch in S:
                temp += 1
        counter.append((word, temp))
    # filter words
    filtered_list = filter(lambda x: x[1] >= k, counter)
    # generate dict
    return dict(filtered_list)
    pass

words = ['hello', 'world', 'language', 'apple', 'orange', 'banana', 'friend', 'education', 'tiger']
k = 3
S = {'a','e','i','o','u'}

print(select_words_by_char_count(words, k, S))