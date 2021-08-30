#include <stdio.h>
#include <math.h>

int main(){
    FILE* fp;
    fp = fopen("test.txt", "w+");
    double header = pow(10, (double)(-10));

    for(int oom = 0; oom < 21; oom++){
        // Print row header
        double header = pow(10, (double)(oom - 10));
        fprintf(fp, "%.2e\n", header);
        fprintf(fp, "%.2e\n", header);
        fprintf(fp, "%.2g\n", header);
        fprintf(fp, "%e\n", header);
        fprintf(fp, "%g\n", header);
        fputs("\n", fp);
    }
    
    fclose(fp);
    return 1;
}