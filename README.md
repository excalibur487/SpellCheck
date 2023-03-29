# SpellCheck v1.0
Text-based implementation of a spell checker in C

How to use: ```bin/spellcheck [filename] [optional dictionary]```

Example: ```bin/spellcheck SpellCheck/test/test-files/tolstoy.txt```

# Implementation

Uses a custom hash function to hash words and load them into a hash table. The hash table is an array of doubly-linked lists.

