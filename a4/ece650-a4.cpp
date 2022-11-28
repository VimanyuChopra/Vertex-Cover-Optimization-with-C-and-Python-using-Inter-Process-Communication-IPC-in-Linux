#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <list>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include "minisat/mtl/IntTypes.h"
#include "minisat/mtl/Vec.h"

using namespace std;


using namespace Minisat;


vector<int> cover;


class Graph
{
     int V;




public:
    int set(int val);



};
int Graph::set(int val)
{
     V = val+1;


     return V;
}


void display(vector<int> vert_cover)
{


    for (unsigned int i = 0; i<vert_cover.size(); i++)
    {
        cout<<vert_cover[i]<<" ";
    }
    cout<<endl;
    vert_cover.clear();
}

vector<vector<Lit> > make_literals(int vert_num, int k, Minisat::Solver& solver)
{
    vector<vector<Lit> > x(vert_num);
    int i =0;
    while(i<vert_num)
    {
        int j =0;
        while(j<k)
        {
            Lit literal = mkLit(solver.newVar());
            x[i].push_back(literal);
            j++;
        }
        i++;
    }

    return x;

}

void clause_one(int k, int vert_num, Minisat::Solver& solver,vector<vector<Lit> > x)
{
    int i =0;
    while(i<k)
    {
        vec<Lit> temp;
        int j =0;
        while(j < vert_num)
        {
            temp.push(x[j][i]);
            j++;
        }
        solver.addClause(temp);
        temp.clear();
        i++;

    }

}

void clause_two(int k, int vert_num, Minisat::Solver& solver,vector<vector<Lit> > x)
{
    int i =0;
    while(i<vert_num)
    {
        int j =0;
        while(j<k-1)
        {
            int l =j+1;
            while(l<k)
            {
                solver.addClause(~x[i][j],~x[i][l]);
                l++;
            }
            j++;
        }
        i++;
    }
}

void clause_four(int k, int vert_num, Minisat::Solver& solver,vector<vector<Lit> > x)
{
    int i =0;
    while(i<k)
    {
        int j =0;
        while(j < vert_num-1)
        {
            int l = j+1;
            while(l<vert_num)
            {
                solver.addClause(~x[j][i], ~x[l][i]);
                l++;
            }
            j++;
        }
        i++;
    }
}

void clause_three(int k, int vert_num, Minisat::Solver& solver,vector<vector<Lit> > x, vector<int> minisatvertices)
{
    unsigned int j = 0;
    while(j< minisatvertices.size())
    {
        vec<Lit> temp1;
        int m = minisatvertices[j+1];
        int l = minisatvertices[j];

        int i =0;
        while(i<k)
        {
            temp1.push(x[l][i]);
            temp1.push(x[m][i]);
            i++;
        }
        solver.addClause(temp1);
        temp1.clear();
        j=j+2;

    }
}


void vertex_coversat(int vert_num,vector<int> minisatvertices)
{

    vector<int> vert_cover;

    int k = 0;
    int low = 0;
    int high = vert_num;


    while(low <= high)
    {
        Solver solver;
        vector<vector<Lit> > x(vert_num);
        k = int(low + high)/ 2;


        x = make_literals(vert_num, k, solver);

        clause_one(k,vert_num,solver,x);

        clause_two(k, vert_num, solver, x);

        clause_three(k,vert_num,solver,x,minisatvertices);

        clause_four(k,vert_num,solver,x);


        bool sat = solver.solve();
        if(sat)
        {
            vert_cover.clear();
            high = k - 1;
            int i =0;
            while(i<vert_num)
            {
                int j = 0;
                while(j< k)
                {
                    lbool tr_val = solver.modelValue(x[i][j]);
                    if(tr_val == l_True)
                    {
                        vert_cover.push_back(i);
                    }
                    j++;
                }
                i++;
            }
        }
        else
        {
            low = k+1;
        }

    }

    display(vert_cover);

}

string entry;
string final_data;
Graph g;
int size=0;

string InputProcess(string in)
{
    vector<int> vertex_cover;
    string hold;
    string out;
    istringstream splice(in, istringstream::in);
    //int Vi;


    splice>>entry;

    if(entry.compare("E")==0)
    {
        int newvar;
        //cout<<"V is "<<endl;
        //cout<<size<<endl;
       vector<int> new_vec;
       newvar=g.set(size);
       // cout<<"new variable is "<<endl;
       // cout<<newvar<<endl;
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
                 //cout<<"x is"<<endl;
                 //cout<<x_value<<endl;;
                 //cout<<"y is"<<endl;
                 //cout<<y_value;





                     if(x_value>size ||x_value<=0 || y_value>size ||y_value<=0 || x_value==y_value){

                         counter++;


                         if (counter==1){

                         cout<<"Error: Invalid input\n";
                         new_vec.clear();
                         g.set(0);
                         continue;


                         }
                         else if (counter>1){
                            continue;
                         }


                     }

                     new_vec.push_back(x_value);
                     new_vec.push_back(y_value);

                     //g.edgeadd(x_value, y_value);



                    x="";
                    y="";


            }


        }

        //cout<<"new_vec is "<<endl;
        //for(int i=0; i < new_vec.size(); i++)
        //std::cout << new_vec.at(i) << ' ';

        if(new_vec.empty())
        {

         cout << endl;
        }
        else{
        vertex_coversat(newvar,new_vec);
        new_vec.clear();
        }
    }

     //else if (entry.find('V') == 0)
     else if (entry.compare("V")==0)
     {
         splice >> hold ;
         stringstream value(hold);
         value>>size;
         //Vi=size;
         //new_vec.clear();
          try
                 {
                     if(size<1)
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
