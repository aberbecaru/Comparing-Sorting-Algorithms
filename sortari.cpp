#include<iostream>
#include<fstream>
#include<algorithm>
#include<chrono>
#include<vector>
#include<cstdlib>
#include<random>
using namespace std;

ifstream fin("teste.in");

int *v, n, *sortat, *qs, *x;

void RadixSort(int v[],int n, int baza, int x[]){
    int i,maxim=0,exp=1;
    for(i=0;i<n;i++){
        if(v[i]>maxim)
            maxim=v[i];
    }

    while(maxim/exp>0){
        int a[baza]={0};
        for(i=0;i<n;i++)
            a[v[i]/exp%baza]++;
        for(i=1;i<baza;i++)
            a[i]+=a[i-1];
        for(i=n-1;i>=0;i--)
            x[--a[v[i]/exp%baza]]=v[i];
        for(i=0;i<n;i++)
            v[i]=x[i];
        exp*=baza;

    }
}

void MergeSort(int st, int dr, int v[], int sortat[]){
    if(st<dr){
        int mid=(st+dr)/2;
        MergeSort(st, mid, v, sortat);
        MergeSort(mid+1 , dr, v, sortat);
        int i=st;
        int j=mid+1;
        int k=0;
        while(i<=mid && j<=dr){
            if(v[i]<v[j])
                sortat[++k] = v[i++];
            else
                sortat[++k]=v[j++];
        }
        while(i<=mid)
            sortat[++k] = v[i++];
        while(j<=dr)
            sortat[++k] = v[j++];
        for(i=st, j=1; i<=dr; i++ , j++)
            v[i] = sortat[j];
    }
}


void shellsort(int v[], int n) {
    for (int i=n/2; i>0; i/=2) {
        for (int j=i; j<n; j++) {
            int aux=v[j];
            int t;
            for (t=j; t>=i && v[t-i]>aux; t-=i) {
                v[t] = v[t-i];
            }
        v[t]=aux;
        }
    }
}

int poz(int st, int dr){
    int dst=0;
    int ddr=-1;
    while(st!=dr){
        if(qs[st]>qs[dr]){
            swap(qs[st], qs[dr]);
            int aux=dst;
            dst=-ddr;
            ddr=-aux;
        }
        st+=dst;
        dr+=ddr;
    }
    return st;
}

void quicksort(int st, int dr){
    if(st<dr){
        int p=poz(st, dr);
        quicksort(st, p-1);
        quicksort(p+1, dr);
    }
}

void countingsort(int cnt[], int n, int f[]){

    int maxim=-1;
    for (int i=0; i<n; i++){
        f[cnt[i]]++;
        if(cnt[i]>maxim)
            maxim=cnt[i];

    }
    int k=-1;
    for (int i=0; i <=maxim; i++){

        while (f[i]!=0){
            cnt[++k] = i;
            f[i]--;
        }
    }
}


void sortare_nativa(int v[], int n){
    sort(v, v+n);
}

void Random(int n, int NMax){

        int *mrgsort, *cnt, *snativ, *radix, *shell, *sortat, *f;

        qs=new int[n];
        mrgsort=new int[n];
        cnt=new int[n];
        snativ=new int[n];
        radix=new int[n];
        shell=new int[n];
        sortat=new int [n];
        f=new int[NMax+1];
        x=new int[NMax+1];
        std::random_device rd;
        std::default_random_engine eng {rd()};
        std::uniform_int_distribution<> dist(0, NMax);

        for(int i=0; i<n; i++){
            mrgsort[i]=dist(eng);
            shell[i]=mrgsort[i];
            qs[i]=mrgsort[i];
            cnt[i]=mrgsort[i];
            snativ[i]=mrgsort[i];
            radix[i]=mrgsort[i];
            sortat[i]=0;
        }

        auto start1=std::chrono::steady_clock::now();
        MergeSort(0, n-1, mrgsort, sortat);
        for(int j=0; j<n-1; j++){
            if(mrgsort[j]>mrgsort[j+1]){
                cout<<"Algoritmul Mergesort nu a sortat corect";
                auto end1=std::chrono::steady_clock::now();
                double timp1=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end1-start1).count());
                break;
            }
        }
        auto end1=std::chrono::steady_clock::now();
        double timp1=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end1-start1).count());
        cout<<"Algoritmul Mergesort a sortat corect in: "<<timp1/1e9<<"\n";

        auto start2=std::chrono::steady_clock::now();
        shellsort(shell, n);
        for(int j=0; j<n-1; j++){
            if(shell[j]>shell[j+1]){
                cout<<"Algoritmul Shellsort nu a sortat corect";
                auto end2=std::chrono::steady_clock::now();
                break;
            }
        }
        auto end2=std::chrono::steady_clock::now();
        double timp2=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end2-start2).count());
        cout<<"Algoritmul Shellsort a sortat corect in: "<<timp2/1e9<<"\n";

        auto start3=std::chrono::steady_clock::now();
        quicksort(0, n-1);
        for(int j=0; j<n-1; j++){
            if(qs[j]>qs[j+1]){
                cout<<"Algoritmul Quicksort nu a sortat corect";
                auto end3=std::chrono::steady_clock::now();
                break;
            }
        }
        auto end3=std::chrono::steady_clock::now();
        double timp3=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end3-start3).count());
        cout<<"Algoritmul Quicksort a sortat corect in: "<<timp3/1e9<<"\n";

        for(int x=0; x<=NMax; x++)
            f[x]=0;
        auto start4=std::chrono::steady_clock::now();
        countingsort(cnt, n, f);
        for(int j=0; j<n-1; j++){
            if(cnt[j]>cnt[j+1]){
                cout<<"Algoritmul Countingsort nu a sortat corect";
                auto end4=std::chrono::steady_clock::now();
                break;
            }
        }
        auto end4=std::chrono::steady_clock::now();
        double timp4=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end4-start4).count());
        cout<<"Algoritmul Countingsort a sortat corect in: "<<timp4/1e9<<"\n";

        auto start5=std::chrono::steady_clock::now();
        sortare_nativa(snativ, n);
        for(int j=0; j<n-1; j++){
            if(snativ[j]>snativ[j+1]){
                cout<<"Algoritmul sortarii native nu a sortat corect";
                auto end5=std::chrono::steady_clock::now();
                break;
            }
        }
        auto end5=std::chrono::steady_clock::now();
        double timp5=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end5-start5).count());
        cout<<"Algoritmul sortarii native a sortat corect in: "<<timp5/1e9<<"\n";

        auto start6=std::chrono::steady_clock::now();
        RadixSort(radix, n, 10, x);
        for(int j=0; j<n-1; j++){
            if(radix[j]>radix[j+1]){
                cout<<"Algoritmul Radixsort nu a sortat corect";
                auto end6=std::chrono::steady_clock::now();
                break;
            }
        }
        auto end6=std::chrono::steady_clock::now();
        double timp6=double(std::chrono::duration_cast <std::chrono::nanoseconds>(end6-start6).count());
        cout<<"Algoritmul Radixsort a sortat corect in: "<<timp6/1e9<<"\n";



        cout<<"\n";

}

void teste(int T){
    int n, NMax;
    for(int j=0; j<T; j++){
        fin>>n>>NMax;
        cout<<"Testul "<<j+1<<" cu n = "<<n<<" si NMax = "<<NMax<<"\n";
        Random(n, NMax);
    }


}


int main(){
    int T;
    cin>>T;
    teste(T);
}






