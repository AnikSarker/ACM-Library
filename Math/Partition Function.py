# Calculates Partition Function(x) for all x <= n 
# p(n) = number of distinct ways of representing n
# as sum of natural numbers (with order irrelevant).
# Complexity : O(n sqrt(n))

def PartitionFunction(n) :
    p = []
    for i in range (0, n+1) : p.append(0)

    p[0] = 1
    for i in range (1, n+1) :
        j = 1
        r = 1
        while i - (3 * j * j - j) // 2 >= 0 :
            p[i] += p[i - (3 * j * j - j) // 2] * r
            if i - (3 * j * j + j) // 2 >= 0 :
                p[i] += p[i - (3 * j * j + j) // 2] * r
            j += 1
            r *= -1
