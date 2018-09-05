struct Pyramid{
    int n;     //number of side of the pyramid
    double l;  //length of each side
    double ang;

    Pyramid(int n, double l) {this->n=n; this->l=l; ang=pi/n;}

    double getBaseArea() {return l * l * n / (4* tan(ang));}
    double getHeight() {return l * sqrt(1 - 1 / (4*sin(ang)*sin(ang)) );}
    double getVolume() {return getBaseArea() * getHeight() / 3;}
};
