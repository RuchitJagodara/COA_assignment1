// In this program we will measure the time taken by the program on the CPU using timespec

#include<iostream>
#include<time.h>
using namespace std;


// Assuming the first two numbers are 0 and 1 in the fibbonaci series
// refer: https://en.wikipedia.org/wiki/Fibonacci_sequence

long long fibb(long long n){
    if (n==1 || n==2){
        return n-1;
    }
    return fibb(n-1) + fibb(n-2);
}


long long fibb_memo(long long n, long long *memo){
    if (n==1 || n==2){
        return n-1;
    }
    if(memo[n]!=-1){
        return memo[n];
    }
    memo[n]=fibb_memo(n-1, memo) + fibb_memo(n-2, memo);
    return memo[n];
}


int main(){
    long long rec_avg_cpu_time = 0;
    long long loop_avg_cpu_time = 0;
    long long rec_memo_avg_cpu_time = 0;
    long long loop_memo_avg_cpu_time = 0;

    //here n signifies the position of the number in the fibbonaci series
    long long n=50;
    timespec start, end;


    /*
        finding fibbonaci number at position n using recursion
    */


    cout<<"\n\n------------------------------------------------------------\n";
    cout<<"Recursion Program"<<endl;

    for(int i=0; i<5; i++){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        for(int i=1; i<=n; i++){
            fibb(i);
        }
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

        long long cpu_time = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        rec_avg_cpu_time += cpu_time;
    }

    rec_avg_cpu_time /= 5;
    cout << "Average CPU time taken by the recursion program is: " << rec_avg_cpu_time / 1000000000LL << " seconds and " << rec_avg_cpu_time % 1000000000LL << " nano seconds" << endl;
    cout<<"------------------------------------------------------------\n";


    /*
        finding fibbonaci number at position n using loop
    */


    cout<<"\n\n------------------------------------------------------------\n";
    cout<<"Loop Program"<<endl;

    long long prev1=0, prev2=1, current=0;

    for(int i=0; i<5; i++){    
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

        // here i is the ith number in the fibbonaci series
        for(int i=1; i<=n; i++){
            if(i==1){
                current=prev1;
            }
            else if(i==2){
                current=prev2;
            }
            else{
                for(int j=3; j<=i; j++){
                    current=prev1+prev2;
                    prev1=prev2;
                    prev2=current;
                }
            }
        }

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

        long long cpu_time = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        loop_avg_cpu_time += cpu_time;
    }

    loop_avg_cpu_time /= 5;
    cout << "Average CPU time taken by the program is: " << loop_avg_cpu_time / 1000000000LL << " seconds and " << loop_avg_cpu_time % 1000000000LL << " nano seconds" << endl;
    cout<<"------------------------------------------------------------\n";    


    /*
        finding fibbonaci number at position n using recursion with memoization
    */


    cout<<"\n\n------------------------------------------------------------\n";
    cout<<"Recursion with Memoization Program"<<endl;
    long long *memo = new long long[n+1];

    // checking the CPU time to calculate the fibbonaci number

    for(int i=0; i<5; i++){
        for(int j=0; j<=n; j++) memo[i]=-1;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        for(int i=1; i<=n; i++){
            fibb_memo(i, memo);
        }
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

        long long cpu_time = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        rec_memo_avg_cpu_time += cpu_time;
    }

    rec_memo_avg_cpu_time /= 5;
    cout << "Average CPU time taken by the recursion with memoization program is: " << rec_memo_avg_cpu_time / 1000000000LL << " seconds and " << rec_memo_avg_cpu_time % 1000000000LL << " nano seconds" << endl;
    cout<<"------------------------------------------------------------\n";


    /*
        finding fibbonaci number at position n using loop with memoization
    */


    cout<<"\n\n------------------------------------------------------------\n";
    cout<<"Loop with Memoization Program"<<endl;
    for(int i=0; i<5; i++){
        for(int i=0; i<=n; i++){
            memo[i]=-1;
        }

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

        for(int i=1; i<=n; i++){
            if(i==1){
                memo[i]=0;
            }
            else if(i==2){
                memo[i]=1;
            }
            else{
                memo[i]=memo[i-1]+memo[i-2];
            }
        }

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        
        long long cpu_time = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        loop_memo_avg_cpu_time += cpu_time;
    }

    loop_memo_avg_cpu_time /= 5;
    cout << "Average CPU time taken by the program is: " << loop_memo_avg_cpu_time / 1000000000LL << " seconds and " << loop_memo_avg_cpu_time % 1000000000LL << " nano seconds" << endl;
    cout<<"------------------------------------------------------------\n";


    /*
        Calculating speedup of all programs with respect to the recursion program
    */

    cout << "Speedup of loop program with respect to recursion program is: " << (double)rec_avg_cpu_time/loop_avg_cpu_time << endl;
    cout << "Speedup of recursion with memoization program with respect to recursion program is: " << (double)rec_avg_cpu_time/rec_memo_avg_cpu_time << endl;
    cout << "Speedup of loop with memoization program with respect to recursion program is: " << (double)rec_avg_cpu_time/loop_memo_avg_cpu_time << endl;

    return 0;
}