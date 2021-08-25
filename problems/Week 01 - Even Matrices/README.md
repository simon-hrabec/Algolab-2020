# Even Matrices - solution
Even Matrices is a natural extension of the Even Pairs problem from 1D to 2D. Similar approach can be used however some new ideas needs to be added.
- Extension from 1D to 2D
- Constant time sum of a 2D subarray
- Covering all matrices

## Extension from 1D to 2D
In Even Pairs we operate only on a 1D array. We can consider this to be a special subcase of the 2D problem where we examine matrices that have only length of 1 row. The question is how to operate on matrices that have more rows. Actually, it is suprisingly simple - all we need to do is to sum those rows and then apply the same algorithm. However computing these row sums could show rather difficult, but there is one trick to use.

## Constant time sum of a 2D subarray
There is a simple way how to achieve a constant time for a 2D subarray sum query. First we transform the 2D array into its 2D prefix sum. Similarly to 1D array each element will contain the sum of all the elements prior to it, but this time in both dimensions (left and up). This can be achieved in one iteration over the array. After that the queried sum can then be obtained by combining the sums (adding and substracting) in the right way to just get the subarray we are interested in.

    int sum(const int x1, const int x2, const int y1, const int y2) {
        return arr[x2][y2] - arr[x1-1][y2] - arr[x2][y1-1] + arr[x1-1][y1-1];
    }

## Covering all matrices
Using the sum function we can now perform the original algorithm on an arbitrary number of rows but instead of building the sum iterativelly we just always call the sum function. And to cover all possible matrices we need to run this algorithm on all i-j pairs (i <= i).

# Running time
    Test set 1 (30 pts / 0.600 s) - 0.0s
    Test set 2 (50 pts / 0.600 s) - 0.001s
    Test set 2 (20 pts / 0.600 s) - 0.027s
