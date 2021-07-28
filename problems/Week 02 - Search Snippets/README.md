# Search Snippets - solution
 This problem is rather easy. It can be solved with counter array and two pointers approach:
- Easier problem - counting letters
- Sorting the input
- Two pointer approach

## Easier problem - counting letters
In some programming/interview preparation books there is often the problem that works on letters and requires to find the shortest continuous subsequence to contain all letters. Search snippets is just a bit more complicated - the input is not given as a sequence of letters. Instead, we are given positions that do not come in the necessary order. Also, we don't have fixed number of how many words we are looking for (need to include).

## Sorting the input
To be able to process the words we first need to sort them by their positions. Since the list of words of interest is not continuous (it also contains words we are not interested in - gaps), we need to remember the indices of the words. And then work with these indices to calculate the length of the subsequence.

## Two pointer approach
Now we need to iterate over the text (relevant words). We have two points that denote the range which we consider. We also need an array of counter for each word. On top of that we need a counter to remember how many words we are missing. Then we move the forward pointer if we are missing some word. When we found all we move the backward pointer to shrink the sequence. By this approach we are guaranteed to stumble upon the optimal (shortest) continuous subsequence that contains all the required words.

# Running time
    Test set 1 (50 pts / 1 s) - 0.114s
    Test set 2 (20 pts / 1 s) - 0.211s
    Test set 3 (20 pts / 1 s) - 0.33s
