int Lp[MAX];
vector<int>Primes;

void Sieve(){
    for (int i=2; i < MAX; i++){
        if(!Lp[i]) Lp[i] = i, Primes.push_back (i);

        for(int j=0; j< Primes.size() && Primes[j] <= Lp[i] && i * Primes[j] < MAX; j++){
            Lp[ i * Primes[j] ] = Primes[j];
        }
    }
}
