//Number of subsequence
Formula 1 :   2^n
Formula 2 :   C(n,0)+C(n,1)+......+C(n,n)
Formula 3 :   f(n)=2*f(n-1)  //take s[n] or don't take


//Number of distinct subsequence
Formula 1 :   f(n) = 2*f(n-1)-f(m)  //here, m=index of previous occurrence of s[n]
                                  //m=0 if s[n] not found previously

//Longest Common Subsequence
Formula 1 :   f(i,j)=0                                                  if(i==0 || j==0)
              f(i,j)=1+f(i-1,j-1)                                       if(X[i]==Y[j])
              f(i,j)=max(f(i,j-1),f(i-1,j))                             if(X[i]!=Y[j])
Space Optimization trick: [2][N]
Time Optimization trick:  use LIS in O(nlogn) if at most one string contains repetitions of characters


//Longest Repeating Subsequence
//Longest Subsequence that occurs at least twice in a string without overlapping
Formula 1 :   f(i,j)=0                                                  if(i==0 || j==0)
              f(i,j)=1+f(i-1,j-1)                                       if(s[i]==s[j] and i!=j)
              f(i,j)=max(f(i,j-1),f(i-1,j))                             if(s[i]!=s[j] or i==j)


//Edit Distance
//Operations: Insert,Delete,Replace
Formula 1 :   f(i,j)=j /* insert Y[1...j] in X */                       if(i==0)
              f(i,j)=i /* insert X[1...i] in Y */                       if(j==0)
              f(i,j)=f(i-1,j-1)                                         if(X[i]==Y[j])
              f(i,j)=1+min(f(i,j-1),f(i-1,j),f(i-1,j-1))                if(X[i]!=Y[j])


//Edit Distance
//Operations: Insert,Delete
Formula 1 :   f(i,j)=Size(x)+Size(Y)-LCS(X,Y)


//Number of palindromic subsequence
Formula 1 :   f(i,j)=1                                                  if(i==j)
              f(i,j)=f(i+1,j)+f(i,j-1)-f(i+1,j-1)+ [f(i+1,j-1)+1]       if(s[i]==s[j])
              f(i,j)=f(i+1,j)+f(i,j-1)-f(i+1,j-1)                       if(s[i]!=s[j])


//Number of distinct palindromic subsequence
Formula 1 :   f(i,j,x)=0                                                if(i==j and s[i]!=x)
              f(i,j,x)=1                                                if(i==j and s[i]=x)
              f(i,j,x)=f(i+1,j,x)+f(i,j-1,x)-f(i+1,j-1,x)               if(s[i]!=x or s[j]!=x)
              f(i,j,x)=2 + sum of all y in a-z (f(i+1,j-1,y))           if(s[i]==x and s[j]==x)
              //2 added for xx and x[longest sequence]x


//Longest Palindromic Subsequence
Formula 1 :   f(i,j)=0                                                  if(i>j)
              f(i,j)=1                                                  if(i==j)
              f(i,j)=f(i+1,j-1)+2                                       if(s[i]==s[j])
              f(i,j)=max(f(i+1,j),f(i,j-1))                             if(s[i]!=s[j])


//Longest Common Substring
Formula 1 :   f(i,j)=0                                                  if(i==0 || j==0)
              f(i,j)=1+f(i-1,j-1)                                       if(X[i]==Y[j])
              f(i,j)=0                                                  if(X[i]!=Y[j])
              ans=max of all f(i,j)


//Longest Palnidromic Substring
Formula 1 :   isPal(i,j)=0                                              if(i>j)
              isPal(i,j)=1                                              if(i==j)
              isPal(i,j)=2+isPal(i+1,j-1)                               if(i<j and s[i]==s[j])
              isPal(i,j)=0                                              if(i<j and s[i]!=s[j])
