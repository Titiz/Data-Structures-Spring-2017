### Problem 1

#### (a)

Begin with a leaf node $n_k$ at depth k, without loss of generality, in the right subtree of the root. It must have a parent $n_{k-1}$ at  depth k-1. Since we have an AVL tree, the depth of the right and left subtree at a given node can differ by at most 1. Therefore by knowing that the left subtree has depth k, its right subtree can have depth at most k+1. 
If $n_{k-1}$ is not the root of the tree, we continue this process upwards. At each decrement of $k$ we are able to create a left subtree with depth 1 greater than the left subtree. We are able to do this $k$ times, as the chain of parents to the root continue at $k$ depth is $k$ pointers long. Thus, when we are at the root, the largest subtree we are able to create on the left of the root is of size $2k$. This proves the theorem.

#### (b)

First take an arbitrary AVL tree with a node leaf of depth k, without loss of generality, in the left subtree. 
This means that the minimum depth of both subtrees is at least $k$. We will denote the root left and right subtree minimum depth leafs as $m_L$ and $m_R$ respectively. Now assume that we take an arbitrary node at depth less than $k-2$. We then have two 
cases:

Case 1: $m_L$ or $m_R$ is in one of the subtrees of the randomly picked node $N$. If this happens, 
then the depth of this subtree is at least k. Since the node is of depth less than k-2, a disbalance forms at $N$. Therefore it requires another subtree
of depth at least 1 for balance. Therefore we must add a child to a node that already has 1 child, proving the node $N$ has two children.

Case 2: $m_L$ or $m_R$ is NOT in one of the subtrees of the randomly picked node $N$ with depth $d$. If this happens 
we proceed to find the nearest ancestor of $N$ that has $m_L$ or $m_R$ in one of its subtrees.
To find our ancestor we go up the tree n times, where $n\leq k-4$ times.The ancestor contains a subtree without $N$ with depth at least $k$. 
This means we must balance the tree such that the subtree containing $N$ has depth at least k. In any scenario, the node at depth $k-3$ has to have two children.
This is because of the following reasoning:

Firstly we want the ancestor $A$'s subtree containing $N$ to have a depth of $k$. This means that we must add two layers of children. However, we cannot add two layers of children without creating 
a disbalance at $N$. Therefore $N$ must have two children, so that at least one more child would be attached to one of its children, increasing the rooted at $A$ left subtree's depth by 2.

If $N$ is at depth < k-3, then the same explanation applies, except more children layers need to be created, which is impossible in an AVL tree due to balancing issues if the node $N$ does not have 2 children.

The consideration of these two cases proves the theorem.

The lower bound that is created is deduced as follows. All trees up to and including depth $k-2$ are filled, by the condition we proved.
This gives us $2^{k-1}-1 nodes.
 Then, to preserve balance,
 the depth $k-1$ of the tree has $2^{k-2}+2$ (half of the slots +2 filled.) nodes. The $+2$ comes from
the nodes that are supporting the two leaves $m_L$ or $m_R$, assuming both of them have depth $k$. These two nodes are also part of the tree so that adds two more nodes. 
Therefore in total we have at least:

$$ 2^{k-1}-1 + 2^{k-2}+2 + 2 = 2^{k-1} + 2^{k-2} + 3 = 3(2^{k-2} + 1) \text{ nodes}. $$



#### (c)

The height and the depth of a tree are the same. Therefore the part (a) gives us that given any AVL tree, if its leaf with the least depth has depth $k$, 
then the maximum height of the tree is $2k$. 
We also know that the number of nodes $n$ are bounded by the following:

$$ n \geq 3(2^{k-2} + 1) $$

Solving for k we obtain:

$$ k \leq log(\frac{n}{3}-1) + 2  $$

So if our maximum height is $2k$ we obtain:

$$ 2k = \text{ max height }  \leq 2(log(\frac{n}{3}-1) + 2) $$

This implies that:

$$ \text{ max height } = O(\log n)$$


