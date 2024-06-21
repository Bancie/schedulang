#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std; 
#define maxm 1000
#define maxn 1000
#define var 5 // <-- sVariables Summarizing in Data File

// Scanning Data File
void readfile (int a[maxm][maxn], int &job_amount, int &prec, int &plan_time, int &job_scale) {
	FILE *f;
	f=fopen("/Users/chibangnguyen/Documents/schedulang/data/data inp/na.inp","rt");
    fscanf(f, "%d", &job_amount);
    fscanf(f, "%d", &prec);
    fscanf(f, "%d", &plan_time);
    fscanf(f, "%d", &job_scale);
    for (int i=0; i<job_amount; i++) {
        for (int j=0; j<var; j++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }
	fclose(f);
}

// Process Variable
double process (int i, int a[maxm][maxn], int job_amount, int job_scale) {
    double p = (double) (a[i][1]*job_amount)/job_scale;
    return p;
}

// Non-precedence p-factor Variable
double p_factor_nonprec (int i, int a[maxm][maxn], double p) {
    double p_factor_nonprec = (double) a[i][4]/p;
    return p_factor_nonprec;
}

// Precedence p-factor Variable
double p_factor_prec_tu (int i, int a[maxm][maxn], double p) {
    if (i<0) {
        return 0;
    }
    return a[i][4] + p_factor_prec_tu(i-1,a,p);
}
double p_factor_prec (int i, int a[maxm][maxn], int job_amount, int job_scale, double p, double sum) {
    return p_factor_prec_tu(i,a,p)/sum;
}

// Printing Output File
void writefile (int a[maxm][maxn], int job_amount, int prec, int plan_time, int job_scale) {
	FILE *f;
    double sum=0;
	f=fopen("/Users/chibangnguyen/Documents/schedulang/data/data out/na.out","wt");
	fprintf(f, "%d\n", job_amount);
    fprintf(f, "%d\n", prec);
    fprintf(f, "%d\n", plan_time);
    fprintf(f, "%d\n", job_scale);
    for (int i=0; i<job_amount; i++) {
        for (int j=0; j<var; j++) {
            fprintf(f, "%d ", a[i][j]);
        }
        if (prec==0) {
            fprintf(f, "%.4lf %.4lf\n", process(i,a,job_amount,job_scale), p_factor_nonprec(i,a,process(i,a,job_amount,job_scale)));
        } else if (prec==1) {
            sum += process(i,a,job_amount,job_scale);
            double p = process(i,a,job_amount,job_scale);
            fprintf(f, "%.4lf %.4lf\n", p, p_factor_prec(i,a,job_amount,job_scale,p,sum));
        }
    }
	fclose(f);
}

/*/ Sorting Job
void writefile (int a[maxm][maxn], int job_amount, int prec, int plan_time, int job_scale) {
    FILE *f;
	f=fopen("/Users/chibangnguyen/Documents/schedulang/data/data out/na.out","r+");
    fscanf(f, "%d", &job_amount);
    fscanf(f, "%d", &prec);
    fscanf(f, "%d", &plan_time);
    fscanf(f, "%d", &job_scale);
    for (int i=0; i<job_amount; i++) {
        for (int j=0; j<var+1; j++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }
    double max = a[0][6];
    for (int i=0; i<job_amount; i++) {
        for (int j=0; j<var+1; j++) {
        }
        if (a[i][6]>max) {
            max=a[i][6];
        }
    }

}*/

int main () {
	int a[maxm][maxn];
    int job_amount, plan_time, job_scale;
    int prec;
    readfile(a, job_amount, prec, plan_time, job_scale);
    writefile(a, job_amount, prec, plan_time, job_scale);
	return 0;
} 