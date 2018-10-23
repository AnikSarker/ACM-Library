namespace FastlO {
    #define BUF_SIZE 100000 //
    bool IOError = 0; //I0Error == false
    inline char NextChar() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOError = 1;
                return -1;

            }
            return *p1++;
        }
    }
    inline bool Blank(char c) {
        return c ==' ' || c =='\n'||c=='\r'||c =='\t';
    }

    inline void read(int &x) {
        bool sign=0;
        char ch=NextChar();
        x=0;
        for (; Blank(ch); ch=NextChar());
        if (IOError)return;
        if (ch=='-')sign=1,ch=NextChar();
        for (; ch>='0'&&ch<='9'; ch=NextChar())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(long long &x) {
        bool sign=0;
        char ch=NextChar();
        x=0;
        for (; Blank(ch); ch=NextChar());
        if (IOError)return;
        if (ch=='-')sign=1,ch=NextChar();
        for (; ch>='0'&&ch<='9'; ch=NextChar())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(double &x) {
        bool sign=0;
        char ch = NextChar();
        x=0;
        for (; Blank(ch); ch = NextChar());
        if (IOError)return;
        if (ch=='-')sign=1,ch=NextChar();
        for (; ch>='0'&&ch<='9'; ch=NextChar())x=x*10+ch-'0';
        if (ch=='.') {
            double tmp=1;
            ch=NextChar();
            for (; ch>= '0'&&ch<='9'; ch=NextChar())tmp/=10.0,x+=tmp*(ch-'0');
        }
        if (sign)x=-x;
    }
    inline void read(char *s) {
        char ch=NextChar();
        for (; Blank(ch); ch=NextChar());
        if (IOError)return;
        for (; !Blank(ch)&!IOError; ch=NextChar())*s++=ch;
        *s=0;
    }
    inline void read(char &c) {
        for (c=NextChar(); Blank(c); c=NextChar());
        if (IOError) {
            c=-1;
            return;
        }
    }
}
using namespace FastlO;
