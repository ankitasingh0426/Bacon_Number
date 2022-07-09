#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <map>
#include <string>
#include <iomanip>
#include <tgmath.h>
#include <set>
#include <list>
#include <fstream>
#define vll vector<ll>
#define ll long long
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define M1 1000000007
#define mod 1000000007
using namespace std;

void add_edge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}
 
// a modified version of BFS that stores predecessor
// of each vertex in array p
// and its distance from source in array d
bool BFS(vector<int> adj[], int src, int dest, int v,
         int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
// utility function to print the shortest distance
// between source vertex and destination vertex
int printShortestDistance(vector<int> adj[], int s,
                           int dest, int v)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
//        cout << "Given source and destination"
//             << " are not connected";
        return -1;
    }
 
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // distance from source is in distance array
    return dist[dest];
//    cout << "Shortest path length is : "
//         << dist[dest];
//
//    // printing path from source to destination
//    cout << "\nPath is::\n";
//    for (int i = path.size() - 1; i >= 0; i--)
//        cout << path[i] << " ";
}
 

 
int main(){
    ifstream infile("sample.txt");
//    ifstream infile("imdb.small.txt");
//    ifstream infile("imdb.top250.txt");
    map< string, vector<string> > m;
    string s;
    set<string>a;
    while(getline(infile,s)){
//        string s;
//        cin>>s;
        string actor, movie;
        string delim="|";
        size_t pos = s.find(delim);
        actor= s.substr(0, pos);
        a.insert(actor);
        movie = s.substr(pos+1, s.length() - (pos+1) );
        m[movie].pb(actor);
   }
//    map<string, set<string>> adj;
    map<string, int> num;
    int i=1;
    for(auto it= a.begin(); it!=a.end(); it++){
        num[*it]=i;
        i++;
    }
    vector<int> adj[100000];
    for(auto mov:m){
        for(int i=0; i<mov.second.size()-1; i++){
            for(int j=i+1; j<mov.second.size(); j++){
                add_edge(adj, num[mov.second[i]], num[mov.second[j]]);
            }
        }
    }
    
    map<string, int> bn;
    map<int,int> numofbn;
    
    for(auto i: a){
        bn[i] = printShortestDistance(adj, num["Kevin Bacon (I)"], num[i], (int)a.size());
        numofbn[bn[i]]++;
    }
    
    cout<<"Type 1 for Q1 and Type 2 for Q2"<<endl;
    int qno;
    cin>>qno;
    
    if(qno==1){
        cout<<"Type the name of actor whose Bacon Number you want to know"<<endl;
        string actorname;
        cin>>actorname;
        if(bn[actorname]==-1){
            cout<<"infinity"<<endl;
        }
        else{
            cout<<bn[actorname]<<endl;
        }
    }
    else if(qno==2){
        cout<<"To find the number of actors with Bacon Number i. Type your i"<<endl;
        int x;
        cin>>x;
        cout<<numofbn[x]<<endl;
    }
        
   
    return 0;
}
