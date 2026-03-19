'''
Write a function build_and_sort_triples(nums, floats, words) that receives as input:
- nums: a list of integers
- floats: a list of floats (same length as nums)
- words: a list of strings (same length as nums)

The function should:
- first, build a list of triples by pairing (nums[i], floats[i], words[i]) for each index i (you are encouraged to implement this as a separate helper function build_triples(nums, floats, words)),
- then, return a new list of these triples sorted by:
    - the first element (int), ascending,
    - the second element (float), descending,
    - the third element (string), descending.

Example:
nums = [2, 3, 2, 1]
floats = [1.3, 2.4, 7.1, 9.5]
words = ['cat', 'dog', 'bat', 'cat']

build_and_sort_triples(nums, floats, words)
output: [
   (1, 9.5, 'cat'),
   (2, 7.1, 'bat'),
   (2, 1.3, 'cat'),
   (3, 2.4, 'dog')
]
'''
nums = [2, 3, 2, 1]
floats = [1.3, 2.4, 7.1, 9.5]
words = ['cat', 'dog', 'bat', 'cat']

def build_triples(nums, floats, words):
    # Your implementation here
    pass

def build_and_sort_triples(nums, floats, words):
    # Your implementation here
    rlist = list(zip(nums, floats, words))
    return sorted(rlist, key= lambda x: (x[0], -x[1], x[2]))
    pass

print(build_and_sort_triples(nums, floats, words))