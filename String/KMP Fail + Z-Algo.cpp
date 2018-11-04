//0-indexed string s[0...n-1]
//fail[i] = maximum x such that s[1....x] matches with s[i-x+1...i]
int fail[MAX];
void build_failure(string s){
    int n=s.size();
    for(int i=1;i<n;i++){
        int j=fail[i-1];
        while(j>0 && s[i]!=s[j]) j=fail[j-1];
        if(s[i]==s[j]) j++;
        fail[i]=j;
    }
}
// s er modhe t khujo
int SubstringSearch(string s, string t)
{
    bool flg = false;

    for(int i = 0, j = 0; i <= s.size(); ){
            if(j == t.size()){
                flg = true;
                break;
            }
            if(i == s.size()) break;
            if(s[i] == t[j]){
                i++, j++;
                continue;
            }
            else{
                if(j != 0) j = fail[j - 1];
                else i++;
            }
        }
        if(flg) return 1;
        else return 0;
}

//0-indexed string s[0...n-1]
//z[i] = maximum x such that s[1....x] matches with s[i..i+x-1]
int z[MAX];
void zAlgo(string s){
    int L=0,R=0;
    int n=s.size();
    for(int i=1;i<n;i++){
        if(i>R) {L=R=i; while(R<n && s[R-L]==s[R]) R++; z[i]=R-L; R--;}
        else{
            int k=i-L;
            if(z[k]<R-i+1) z[i]=z[k];
            else {L=i; while(R<n && s[R-L]==s[R]) R++; z[i]=R-L; R--;}
        }
    }
}
