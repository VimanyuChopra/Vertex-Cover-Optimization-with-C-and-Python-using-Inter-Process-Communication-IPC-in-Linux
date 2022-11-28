#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <random>
#include <math.h>
#include <time.h>
#include<bits/stdc++.h>
#include <fstream>
#include <vector>

using namespace std;

/*
int randomgenerator(int x, int y)
{

    int randomno = x + (rand() % (y-x+1));
    return randomno;
}
*/


int randomgenerator(int min, int max) { // refer to "Advanced linux programming" - Listing 6.1
	unsigned int random;

	int fd = -1;

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1) {

		cout << "cannot open /dev/urandom." << endl;

		exit(1);

	}

	read(fd, &random, sizeof(unsigned int));

	close(fd);

	return  min + (random % (max - min + 1));
}






vector<float> make_vert(int range_num, int range_num1)
{
    vector<float> vert;
    int x,y;
    x = randomgenerator(range_num, range_num1);
    y = randomgenerator(range_num, range_num1);
    vert.push_back((float)x);
    vert.push_back((float)y);
    return vert;
}

string randomnamegenerator(){
    string str = "abcdefghijklmnopqrstuvwxyz";
    string strname = "";
    for(int i=0; i<8; i++){
        int l = randomgenerator(1,26);
        strname += str[l];
    }
    //strname += " St";
    return strname;
}

bool intersection_checker(vector<vector<float>> v)
{
        bool val = false;
        for(unsigned int i=0; i<v.size()-2; i++)
        {
            int a = i+1;
            int b = i+1;
            unsigned int c = i+2;
            while(c<v.size())
            {
                float x1 = v[i][0];
                float y1 = v[i][1];
                float x2 = v[a][0];
                float y2 = v[a][1];
                float x3 = v[b][0];
                float y3 = v[b][1];
                float x4 = v[c][0];
                float y4 = v[c][1];
                float xaxes,yaxes,t,u;

                float num1 = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4);
                float den1 = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
                float num2 = (x1-x3)*(y1-y2) - (y1-y3)*(x1-x2);
                float den2 = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
                if(den1 == 0)
                {
                    val = false;
                }
                if(den2 == 0)
                {
                    val =  false;
                }
                t = num1/den1;
                u = num2/den2;

                if(t >= 0 and t<=1)
                {
                    xaxes = x1 + t*(x2-x1);
                    yaxes = y1 + t*(y2-y1);
                    vector<float> cmp;
                    cmp.push_back(xaxes);
                    cmp.push_back(yaxes);
                    if(!count(v.begin(), v.end(), cmp))
                    {

                        return true;
                    }
                }

                else if(u >= 0 and u<=1)
                {
                    xaxes = x3 + u*(x4-x3);
                    yaxes = y3 + u*(y4-y3);
                    vector<float> cmp;
                    cmp.push_back(xaxes);
                    cmp.push_back(yaxes);
                    if(!count(v.begin(), v.end(), cmp))
                    {

                        return true;
                    }
                }

                b++;
                c++;
            }
        }
    return val;
}

bool overlap_checker(vector<vector<float>> v)
{
    bool val = false;
    for(unsigned int i=0; i<v.size()-2; i++)
    {
        int a = i+1;
        int b = i+1;
        unsigned int c = i+2;
        while(c<v.size())
        {
            float x1 = v[i][0];
            float y1 = v[i][1];
            float x2 = v[a][0];
            float y2 = v[a][1];
            float x3 = v[b][0];
            float y3 = v[b][1];
            float x4 = v[c][0];
            float y4 = v[c][1];


            float s1 = (y2-y1)/(x2-x1);
            float s2 = (y4-y3)/(x4-x3);
            if(abs(s1)==abs(s2))
            {

                float x = x3;
                float y = y3 ;
                if((y-y1) == ((y2-y1)/(x2-x1))*(x-x1))
                {
                    if((x3<x2 && x3>x1) || (x3>x2 && x3<x1))
                    {return true;}
                }

                x = x4;
                y = y4 ;
                if((y-y1) == ((y2-y1)/(x2-x1))*(x-x1))
                {
                    if((x4<x2 && x4>x1) || (x4>x2 && x4>x1))
                    {return true;};
                }

                x = x1;
                y = y1;
                if((y-y3) == ((y4-y3)/(x4-x3))*(x-x3))
                {
                    if((x1<x3 && x1>x4) || (x1>x3 && x1<x4))
                    {return true;}
                }

                x = x2;
                y = y2 ;
                if((y-y3) == ((y4-y3)/(x4-x3))*(x-x3))
                {
                    if((x2<x3 && x2>x4) || (x2>x3 && x2<x4))
                    {return true;}
                }
            }

            b++;
            c++;
        }
    }
    return val;
}

bool other_lines_overlap(vector<vector<vector<float>>> v)
{
    for(unsigned int i=0; i<v.size()-1; i++)
    {
        for(unsigned int j = i+1; j<v.size(); j++)
        {
            for(unsigned int k=0; k<v[i].size()-1; k++)
            {
                for(unsigned int l=0; l<v[j].size()-1; l++)
                {
                    float x1 = v[i][k][0];
                    float y1 = v[i][k][1];
                    float x2 = v[i][k+1][0];
                    float y2 = v[i][k+1][1];
                    float x3 = v[j][l][0];
                    float y3 = v[j][l][1];
                    float x4 = v[j][l+1][0];
                    float y4 = v[j][l+1][1];

                    float s1 = (y2-y1)/(x2-x1);
                    float s2 = (y4-y3)/(x4-x3);
                    if(abs(s1)==abs(s2))
                    {

                        float x = x3;
                        float y = y3 ;
                        if((y-y1) == ((y2-y1)/(x2-x1))*(x-x1))
                        {
                            if((x3<x2 && x3>x1) || (x3>x2 && x3<x1))
                            {return true;}
                        }

                        x = x4;
                        y = y4 ;
                        if((y-y1) == ((y2-y1)/(x2-x1))*(x-x1))
                        {
                            if((x4<x2 && x4>x1) || (x4>x2 && x4>x1))
                            {return true;};
                        }

                        x = x1;
                        y = y1;
                        if((y-y3) == ((y4-y3)/(x4-x3))*(x-x3))
                        {
                            if((x1<x3 && x1>x4) || (x1>x3 && x1<x4))
                            {return true;}
                        }
                        //case4
                        x = x2;
                        y = y2 ;
                        if((y-y3) == ((y4-y3)/(x4-x3))*(x-x3))
                        {
                            if((x2<x3 && x2>x4) || (x2>x3 && x2<x4))
                            {return true;}
                        }
                    }
                }
            }
        }
    }
    return false;
}

vector<vector<vector<float>>> generate_streets(int street_num, int line_num, int range_num)
{
    vector<vector<vector<float>>>final_vector_points;
    int street_number =randomgenerator(2,street_num);

    int routes[street_number];
    for(int i=0; i < street_number; i++)
    {
        int trycounter = 0;
        vector<vector<float>> coord_list;
        routes[i] = randomgenerator(1,line_num);


        for(int j=0; j<=routes[i]; j++)
        {


            vector<float> vert = make_vert(-range_num, range_num);




            if(count(coord_list.begin(), coord_list.end(), vert))
               {
                  trycounter++;
                   j--;
               }
            else
               {
                   coord_list.push_back(vert);
               }
            if(trycounter==25)
            {
                cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                exit(1);
            }

        }

        vector<vector<float>> interim_coord_list = coord_list;
        int errorcounter=0;

        while(intersection_checker(interim_coord_list) || overlap_checker(interim_coord_list))
        {
            vector<vector<float>> coord_list;
            for(int j=0; j<=randomgenerator(1,line_num); j++)
            {
              vector<float> vert = make_vert(-range_num, range_num);

            if(count(coord_list.begin(), coord_list.end(), vert))
               {
                   errorcounter++;
                   j--;
               }
            else
               {
                   coord_list.push_back(vert);
               }
            if(errorcounter==25)
            {
                cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                exit(0);
            }
            }
            interim_coord_list = coord_list;
        }
       final_vector_points.push_back(interim_coord_list);

    }

    return final_vector_points;
}







int main(int argc, char* argv[]) {

    int option;
    string s_string, n_string, l_string, c_string;

	int street_num = 10, line_num = 5, wait_num = 5, range_num = 20;

	while((option=getopt(argc,argv,"s:n:l:c:")) != -1){
        switch (option) {
            case 's':
                s_string=optarg;
                street_num = atoi(s_string.c_str());  //convert string(C-string) to integer
                if (street_num < 2)
                {
                    cerr << "Error: s should be greater than or equal to 2"<<endl;
                    exit(1);
                }
                break;

            case 'n':
                n_string=optarg;
                line_num = atoi(n_string.c_str());
                if (line_num < 1)
                {
                    cerr << "Error: n should be greater than or equal to 1"<<endl;
                    exit(1);
                }
                break;

            case 'l':
                l_string=optarg;
                wait_num = atoi(l_string.c_str());
                 if (wait_num < 5)
                {
                    cerr << "Error: l should be greater than or equal to 5"<<endl;
                    exit(1);
                }

                break;

            case 'c':
                c_string=optarg;
                range_num = atoi(c_string.c_str());
                if (range_num < 1)
                {
                    cerr << "Error: c should be greater than or equal to 1"<<endl;
                    exit(1);
                }
                break;

        }
    }





        while(1){

        std::vector<std::vector< std::vector<float> >> final_point_vector;
        vector<string> names;
		int loopcounter = 0;
		vector <string> street_name_vector;
		int street_number, line_number, wait_number, points_number;
		string street_name;


		//street_number = randomgenerator(2, street_num);
		wait_number = randomgenerator(5, wait_num);



         final_point_vector = generate_streets(street_num,line_num,range_num);

                while(other_lines_overlap(final_point_vector))
        {
            if(loopcounter==25)
            {
                cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                exit(1);
            }
            final_point_vector = generate_streets(street_num,line_num,range_num);
            loopcounter++;
        }




        for(unsigned int i=0;i<final_point_vector.size();i++)
        {
            string s=randomnamegenerator();
            names.push_back(s);
            cout<<"add \""<<s<<"\" ";


            for(unsigned int j=0; j<final_point_vector[i].size(); j++)
            {
                cout<<"("<<final_point_vector[i][j][0]<<","<<final_point_vector[i][j][1]<<") ";
            }
            cout<<endl;

        }
        cout<<"gg"<<endl;
        sleep(wait_number);
        for(unsigned int i=0;i<names.size();i++)
        {
            cout<<"rm \""<<names[i]<<"\""<<endl;
        }
    }

    return 0;

}








