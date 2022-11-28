#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <list>
#include<typeinfo>

using namespace std;
class Graph
{
    int V;


    vector<int> *adj;

public:
    void set(int val);
    string route;


    void edgeadd(int v, int w);



   bool BFS( int source, int destination, int v, int previous[], int distances[]);
   void displayshortestpath( int s,int destination);
};



bool Graph::BFS( int source, int destination, int v, int previous[], int distances[])
{

    list<int> queue;

    bool marked[v];

    for (int i = 0; i < v; i++) {
        marked[i] = false;
        distances[i] = INT_MAX;
        previous[i] = -1;
    }


    marked[source] = true;
    distances[source] = 0;
    queue.push_back(source);


    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (unsigned int i = 0; i < adj[u].size(); i++) {
            if (marked[adj[u][i]] == false) {
                marked[adj[u][i]] = true;
                distances[adj[u][i]] = distances[u] + 1;
                previous[adj[u][i]] = u;
                queue.push_back(adj[u][i]);

                if (adj[u][i] == destination)
                   return true;
            }
        }
    }

    return false;
}

void Graph::displayshortestpath( int s,int destination)
{
    if (V==1)
    {
        cout<<"Error: graph is empty"<<endl;

    }
    else{

    int previous[V], distances[V];

    if (BFS(s, destination, V, previous, distances) == false)
    {
        cout << "Error: No path exists\n";
        return;
    }


    vector<int> route;
    int trav = destination;
    route.push_back(trav);
    while (previous[trav] != -1) {
        route.push_back(previous[trav]);
        trav = previous[trav];
    }


    for (int i = route.size() - 1; i >= 0; i--)
        if(i==0)
            cout << route[i]<<endl;
        else
            cout << route[i] << "-";
    }
}


void Graph::set(int val)
{
     V = val+1;

     adj = new vector<int>[V];
}

 void Graph::edgeadd(int v, int w)
{

    adj[v].push_back(w);
    adj[w].push_back(v);

}

string entry;
string final_data;
 int size=0;
 Graph g;



string InputProcess(string in)
{
    string yo= in;
    //cout<<"type of inp is "<<typeid(yo).name()<<endl;
    string hold;
    string out;
    istringstream splice(in, istringstream::in);


    splice>>entry;


    if(entry.compare("E")==0)
    {
        cout<<in<<endl;

       g.set(size);
       int counter = 0;


        splice >> hold ;
        int n = hold.length();

        char arr [n+1];

        strncpy(arr, hold.c_str(),sizeof(arr));
        string x="",y="";

        for (int i=0;i<n;i++)
        {
            if(arr[i]=='<' )
            {

                while(arr[++i]!=',')
                {

                    x.push_back(arr[i]);

                }

                while(arr[++i]!='>')
                {

                    y.push_back(arr[i]);


                }

                 stringstream x_val(x);
                 stringstream y_val(y);
                 int x_value=0,y_value=0;
                 x_val>>x_value;
                 y_val>>y_value;



                     if(x_value>size ||x_value<0 || y_value>size ||y_value<0 || x_value==y_value){

                         counter++;


                         if (counter==1){

                         cout<<"Error: Invalid input\n";
                         g.set(0);
                         continue;


                         }
                         else if (counter>1){
                            continue;
                         }


                     }


                     g.edgeadd(x_value, y_value);



                    x="";
                    y="";


            }


        }


    }
    else if (entry.compare("s")==0)
    //else if (yo[0]=='s')
    {


        string beginning;
        string end;
        int x=0,y=0;
        splice>>beginning;


         stringstream value(beginning);
         value>>x;

        splice>>end;
       stringstream value2(end);
         value2>>y;

         if(x<=0 || y<=0 ){
            cout<<"Error: invalid input"<<endl;
         }
         else{
         try
         {
            g.displayshortestpath(x, y);
         }
         catch(...)
         {
             cerr<<"Error: invalid op" << endl;
         }
    }
    }
     //else if (entry.find('V') == 0)
     else if (entry.compare("V")==0)
     {
         cout<<in<<endl;

         splice >> hold ;
         stringstream value(hold);
         value>>size;
          try
                 {
                     if(size<=-1)
                         throw "Error: Invalid input\n";




                 }

                 catch(const char* msg)
                 {

                     cerr << msg << endl;
                    // return "";
                 }



     }
     else if (entry.compare("")==0)
        {

        }



    return out;


}
int main(int argc, char** argv) {

    string inp;
    string info;


    while(!std::cin.eof()){
    {

        try
        {


            getline(cin, inp);

            if (inp.empty())
            {
                continue;
            }



           info = InputProcess(inp);


        }
        catch(...)
        {

            cerr << "Error: Incorrect Execution." << endl;

        }
    }
}
    return 0;
}


