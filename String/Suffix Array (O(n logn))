#define MAX 100005

int wa[MAX],wb[MAX],wv[MAX],Ws[MAX];
int cmp(int *r,int a,int b,int l) {return r[a]==r[b] && r[a+l]==r[b+l];}

//(1-indexed) sa[i] = starting position of ith lexicographically smallest suffix in s
//(0-indexed) Rank[i] = lexicographical rank of s[i-1....n-1] (ith suffix by position)
//LCP[i] = longest common prefix of sa[i] & sa[i-1]
int sa[MAX],Rank[MAX],LCP[MAX];

//Suffix Array (O(nlogn))
void buildSA(string s,int* sa,int n,int m){
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++) Ws[i]=0;
	for(i=0;i<n;i++) Ws[x[i]=s[i]]++;
	for(i=1;i<m;i++) Ws[i]+=Ws[i-1];
	for(i=n-1;i>=0;i--) sa[--Ws[x[i]]]=i;
	for(j=1,p=1;p<n;j<<=1,m=p){
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;i++) wv[i]=x[y[i]];
		for(i=0;i<m;i++) Ws[i]=0;
		for(i=0;i<n;i++) Ws[wv[i]]++;
		for(i=1;i<m;i++) Ws[i]+=Ws[i-1];
		for(i=n-1;i>=0;i--) sa[--Ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j) ? p-1 : p++;
	}
}

//Kasai's LCP algorithm (O(n))
void buildLCP(string s,int *sa,int n){
	int i,j,k=0;
	for(i=1;i<=n;i++) Rank[sa[i]]=i;
	for(i=0;i<n;LCP[Rank[i++]]=k)
		for(k?k--:0, j=sa[Rank[i]-1];s[i+k]==s[j+k]; k++);
	return;
}
