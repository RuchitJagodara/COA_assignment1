#include<iostream>

using namespace std;

template<typename T>
T **mat_mul(T **A, T **B, int n){
    T **C = new T*[n];
    for(int i=0; i<n; i++){
        C[i] = new T[n];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            C[i][j] = 0;
            for(int k=0; k<n; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }

    return C;
}

int main(){
    timespec program_start, program_end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &program_start);
    int n = 64;

    int **A = new int*[n];
    int **B = new int*[n];
    for(int i=0; i<n; i++){
        A[i] = new int[n];
        B[i] = new int[n];
    }

    // multiply the matrices
    timespec start, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int **C = mat_mul(A, B, n);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    long long execution_time = (end.tv_sec - start.tv_sec) * 1e9;
    execution_time += (end.tv_nsec - start.tv_nsec);

    cout << "Execution time: " << execution_time << " ns" << endl;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &program_end);

    long long program_execution_time = (program_end.tv_sec - program_start.tv_sec) * 1e9;
    program_execution_time += (program_end.tv_nsec - program_start.tv_nsec);

    cout << "Program execution time: " << program_execution_time << " ns" << endl;


    return 0;
}