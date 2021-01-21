# Asterix in Switzerland - solution
If you ever heard about the [Jewish problems](https://arxiv.org/pdf/1110.1556.pdf) (also sometimes called as Coffin problems), this problem could indeed work as one. It is quite difficult to solve but once you figure out the idea behind the solution the implementation is extremely straightforward. Looking at the code you might actually think it is a toy problem (such as "First steps with BGL" or "What is the Maximum"), but it could not be further from the truth.
- The wrong approach
- The million dollar idea

## The wrong approach
Basically all ideas that come to mind as a possible solution are not gonna work. We can look at the problem as looking for a subset out of the provinces. However there is up to 1000 provinces which is way too much (this approach has exponential complexity). Another approached deemed to fail is to somehow iteratively build the subset of provinces.

## The million dollar idea
The first piece of information that leads to this solution is that we don't need to know what provinces are part of that free-standing subset, only if it exist or not. When exploring possible way how to represent the problem on of the seemingly possible options is flow. We create source and sink. If province has positive balance it has incoming edge from the source (of such value). If negative it has an outgoing edge to sink. All debts will be modeled as edges between the provinces. In this definition a free-standing subset is a group of provinces that will receive more flow (money) from the source than will need to give. In terms of flow we can say it will create a bottle neck in the network. This is the main idea. If there is such subset than some of the money will stay and we detect that the flow is smaller that the sum of the incoming edges. Therefore we just call the maximum flow algorithm and compare the result with the expected value.

# Running time
    Test set 1 (20 pts / 1 s) - 0.0s
    Test set 2 (20 pts / 1 s) - 0.229s
    Test set 3 (20 pts / 1 s) - 0.149s
    Test set 4 (40 pts / 1 s) - 0.232s
