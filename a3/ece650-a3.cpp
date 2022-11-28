#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <vector>
#include <sys/wait.h>

using namespace std;

int rgenProcess(int argc, char** argv) {


	argv[0] = (char *)"rgen";
	execv("rgen", argv);

	return 0;
}

//REF referred from gitlab example


int assignment1Process(int argc, char** argv) {



	//char* argv[3];
	argv[0] = (char *)"python3";
	argv[1] = (char *)"ece650-a1.py";
	argv[2] = nullptr;

	execvp("python3", argv);

	return 0;

}

int assignment2Process(int argc, char** argv) {

	//char* argv[2];
	argv[0] = (char*)"ece650-a2";
	argv[1] = nullptr;

	execv("ece650-a2", argv);

	return 0;

}


int inpProcess(void) {


	while (!std::cin.eof()) {



		std::string inpu;
		std::getline(std::cin, inpu);

		if (inpu.size() > 0) {

			std::cout << inpu << std::endl;
		}
	}
	return 0;
}


int main (int argc, char** argv) {

	std::vector<pid_t> children;
	int street_num = 10, line_num = 5, wait_num = 5, range_num = 20;
	 string s_string, n_string, l_string, c_string;
	 int option;

	while((option=getopt(argc,argv,"s:n:l:c:")) != -1){
        switch (option) {
            case 's':
                s_string=optarg;
                street_num = atoi(s_string.c_str());
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



	int pipe1[2];
	pipe(pipe1);

	int pipe2[2];
	pipe(pipe2);

	pid_t offspring_pid;

	offspring_pid = fork();

	if (offspring_pid == 0)

	{

		dup2(pipe1[1], STDOUT_FILENO);
		close(pipe1[0]);
		close(pipe1[1]);


		return rgenProcess(argc,argv);

	}

	children.push_back(offspring_pid);

	offspring_pid = fork();


	if (offspring_pid == 0) {
		dup2(pipe1[0], STDIN_FILENO);
		close(pipe1[0]);
		close(pipe1[1]);

		dup2(pipe2[1], STDOUT_FILENO);
		close(pipe2[0]);
		close(pipe2[1]);
		return assignment1Process(argc,argv);

	}

	children.push_back(offspring_pid);
	offspring_pid = fork();

	if (offspring_pid == 0)

	{
		dup2(pipe2[0], STDIN_FILENO);
		close(pipe2[1]);
		close(pipe2[0]);



		return assignment2Process(argc, argv);

	}

	children.push_back(offspring_pid);

	offspring_pid = 0;



	dup2(pipe2[1], STDOUT_FILENO);
	close(pipe2[0]);
	close(pipe2[1]);
	int output = inpProcess();




    for (pid_t k : children) {

        int status;

        kill (k, SIGTERM);

        waitpid(k, &status, 0);

    }


	return output;


}
