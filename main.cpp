#include <iostream>
#include <vector>
#include "plant.h"
using namespace std;

void input(int& k, vector<int>& L, int& M, int& N, vector<vector<double>>& T){
    cout<<"k = ";
    cin>>k;

    L.resize(k);
    cout << "L: ";
    for(int i = 0; i<k; i++) cin >> L[i];

    cout<<"M = ";
    cin>>M;

    cout<<"N = ";
    cin>>N;

    cout << "T: "<<endl;
    T.resize(N);
    for(int i=0; i<N; i++) T[i].resize(k);
    for(int i=0; i<N; i++)
        for(int j=0; j<k; j++)
            cin >> T[i][j];
}

double Use_n_watch(int M, vector<int> L, vector<double> T, Plant plant){
    double watch;
    int k = L.size();
    for(int j=0; j<k; j++) //Use
        plant_control(L[j], T[j], plant);
    watch = plant_measure(M, plant); //watch
    return watch;
}

double countV(double nextY, double currY,
              double nextU, double currU){
    return ((nextY-currY)/(nextU-currU));
}

int main()
{
    Plant plant; plant_init(plant);
    int k, M, N;
    vector<int> L;
    vector<vector<double>> T;
    input(k,L,M,N,T);
    vector<vector<double>> V(k);
    double curY, nextY;

    curY = Use_n_watch(M, L, T[0], plant);
    for(int i = 0; i < N-1; i++){
        nextY = Use_n_watch(M, L, T[i+1], plant);
        for (int j = 0; j<k; j++){
            if(T[i+1][j] != T[i][j])
            V[j].push_back(countV(nextY, curY, T[i+1][j], T[i][j]));
        }
        curY = nextY;
    }

    cout <<"---Average---"<< endl;
    for(int i=0; i<k; i++){
        int s = V[i].size();
        double av = 0;
        for(int j = 0; j<s; j++){
            av+=V[i][j];
        }
        av = av / s;
        cout <<"V"<<i+1<<": "<<av<< endl;
    }
}
