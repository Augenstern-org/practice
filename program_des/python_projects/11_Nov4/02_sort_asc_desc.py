'''
Write a function sort_triples_custom(triples) that receives as input:
- triples: a list of tuples, each of the form (int, float, string)

The function returns a new list of triples, sorted by:
- the first element (int) in ascending order,
- then, the second element (float) in descending order,
- finally, the third element (string) in ascending order.

Example:
triples = [
    (2, 1.3, "cat"),
    (2, 1.3, "ant"),
    (1, 9.5, "dog"),
    (2, 7.1, "bat"),
    (1, 7.5, "cat")
]
sort_triples_custom(triples)
# output: [
#   (1, 9.5, 'dog'),
#   (1, 7.5, 'cat'),
#   (2, 7.1, 'bat'),
#   (2, 1.3, 'ant'),
#   (2, 1.3, 'cat')
# ]
'''

triples = [
    (2, 1.3, "cat"),
    (2, 1.3, "ant"),
    (1, 9.5, "dog"),
    (2, 7.1, "bat"),
    (1, 7.5, "cat")
]

def sort_triples_custom(triples):
    # Your implementation here
    return sorted(triples, key=lambda x:(x[0], -x[1], x[2]))
    pass

print(sort_triples_custom(triples))