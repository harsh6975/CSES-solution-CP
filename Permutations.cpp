#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iomanip>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 ;
#define FOR0(i,n) for(ll i = 0; i < n; i++)
#define FORa(i,a,b) for(ll i = a; i < b; i++)
#define rFOR0(i,s) for(ll i = s; i >= 0; i--)
#define rFORa(i,s,e) for(ll i = s; i >= e; i--)
#define n1 'n' 
#define PB push_back
#define F first
#define S second
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define T    int test;cin>>test;while(test--)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())


ll gcd(ll a, ll b){
    if (a == 0)
       return b;
    return gcd(b % a, a);
}  

int main()
{
// read the question correctly (ll vs int)
 fast_cin();
 ll n;
 cin>>n;
 ll arr[n];
 int j=0;
 if( n>1&& n<4){
     cout<<"NO SOLUTION";
     return 0;
 }
 for(int i=1;i<=n;i+=2){
     arr[j]=i;
     j++;
 }
 reverse(arr,arr+j);
 int k=j;
 for(int i=2;i<=n;i+=2){
     arr[j]=i;
     j++;
 }
 reverse(arr+k,arr+n);

 FOR0(i,n){
     cout<<arr[i]<<" ";
 }
 return 0;
}