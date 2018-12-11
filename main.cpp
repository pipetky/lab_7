#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

using namespace std;

void child(int field, string *in_file) {
    if (fork() == 0) {
        int f = field;
        string line;
        ifstream in(*in_file);
        if (in.is_open()) {

            while (getline(in, line)) {
                char *cstr = new char[line.length() + 1];
                strcpy(cstr, line.c_str());
                cstr[line.length()] = '\n';
                write(field, cstr, line.length() + 1);
                delete [] cstr;
            }
            char t = EOF;
            write(f, &t, 1);
            close(field);

            exit(0);

        }
    }


}


int main(int argc, char **argv) {


    string in1_file = argv[1];
    string in2_file = argv[2];
    string out_file = argv[3];
    char ch;
    int c;
    int flag = 0;

    int fields[2];
    pipe(fields);

    ofstream out;
    out.open(out_file);

    child(fields[1], &in1_file);
    child(fields[1], &in2_file);

    while (flag < 2) {     /*  цикл чтения символов из канала*/
        read(fields[0], &ch, 1);
        if (ch != EOF) {
            if (out.is_open())
            {
                out << ch;
            }

        } else {
            flag ++;
        }

        close(fields[1]);
    }


}
