#include<iostream>
#include<fstream>
#include<string>
#include<omp.h>

using namespace std;

struct matrix {
    int x, y;
    double ** m;
};

matrix loadFromFile(string filename) {
    matrix m;

    ifstream in(filename.c_str());

    in >> m.x;
    in >> m.y;

    m.m = new double*[m.x];
    for(int i = 0; i < m.x; i++) {
        m.m[i] = new double[m.y];
    }

    for(int j = 0; j < m.y; j++) {
        for(int i = 0; i < m.x; i++) {
            in >> m.m[i][j];
        }
    }

    in.close();

    return m;
}

void writeToFile(string filename, matrix m) {
    ofstream out(filename.c_str());

    out << m.x << ' ' << m.y << endl;
    for(int j = 0; j < m.y; j++) {
        for(int i = 0; i < m.x; i++) {
            out << m.m[i][j] << "\t";
        }
        out << endl;
    }

    out.close();
}

matrix sum(matrix A, matrix B) {
    matrix C;

    C.x = A.x;
    C.y = A.y;

    C.m = new double*[C.x];
    for(int i = 0; i < C.x; i++) {
        C.m[i] = new double[C.y];
    }

    /* SUM */
	int i(0), j(0);
	#pragma omp parallel for private(i, j)
    for(i = 0; i < C.x; i++) {
        for(j = 0; j < C.y; j++) {
            C.m[i][j] = A.m[i][j] + B.m[i][j];
        }
    }

    return C;
}


int main() {
    matrix A = loadFromFile("A.txt");
    matrix B = loadFromFile("B.txt");

    if(A.x == B.x && A.y == B.y) {
        matrix C = sum(A, B);
        writeToFile("C.txt", C);
		int a;
		cin >> a;
        return 0;
    } else {
        cerr << "Invalid matrix dimention" << endl;
        return 1;
    }
}
