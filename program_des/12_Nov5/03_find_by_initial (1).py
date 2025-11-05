'''
Write a function find_values_by_key_initial(data_dict, char_a, char_b) that receives as input:
- data_dict: a dictionary with string keys and string values,
- char_a: a single-character string,
- char_b: a single-character string.

The function must return a list containing values from data_dict whose key's initial letter is alphabetically between char_a and char_b (inclusive), always ignoring case.

The returned list must be sorted first by decreasing length, and, in case of a tie, in alphabetical order (case-insensitive).

To organize your solution, you are encouraged to implement helper functions, such as:
- key_starts_between(key, a, b): Returns True if the first character of key is between a and b (inclusive, ignoring case).
- sort_strings_by_length_then_alpha(strings): Returns a list of strings sorted by length (descending) and alphabetically in case of ties.

Example:
data_dict = {
    'Car': 'GoOd',
    'floor': 'bAd',
    'Wild': 'EXCELLENT',
    'cocoon': 'greaT',
    'cotton': 'zinc',
    'moon': 'Igloo',
    'apple': 'Another'
}
char_a = 'c'
char_b = 'G'

find_values_by_key_initial(data_dict, char_a, char_b)
output: ['greaT', 'GoOd', 'zinc', 'bAd']
Both 'zinc' and 'bAd' have length 4, so they are sorted alphabetically (case-insensitive).
'Igloo' and 'Another' are not present in the output because the keys 'moon' and 'apple' do not qualify.
'''

def find_values_by_key_initial(data_dict, char_a, char_b):
    # Your implementation here
    pass
