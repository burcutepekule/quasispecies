# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <stdio.h>
# include <random>
# include <fstream>
# include <cstdlib>
# include <ctime>
# include <stack>
# include <math.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sstream>

using namespace std;
typedef std::array<double,5> state_type;

double unifRand(double a, double b){
    return (b-a)*((double) rand() / (RAND_MAX))+a;
}

int binArr2dec(int *seq, int v){
    int sum = 0;
    for(int i=0;i<v;i++){
        sum = sum + (seq[v-i-1])*(pow(2,v-i-1));
    }
    return sum;
}

int hammDist(int *seq, int v){
    int sum = 0;
    for(int i=0;i<v;i++){
        sum = sum + seq[i];
    }
    sum = v-sum;
    return sum;
}

using namespace std;

int main (int argc, char **argv)
{
    string directory;
    directory = "/Users/burcu/desktop/"; // Enter the root directory for data storage
    stringstream myRoot;
    myRoot << directory << "quasiData"; // Enter the folder you want to create for data storage
    mkdir((myRoot.str()).c_str(),0775);

    myRoot << "/";
    double muMin       = 0;         // Minimum mutation rate per bit
    double muMax       = 0.15;      // Maximum mutation rate per bit
    int numOfBins      = 100;       // Number of mutation rates will be used (between muMin and muMax)
    int generations    = 2000;      // Number of generations
    int populationSize = 100;       // Number of strains
    int v              = 16;        // Number of bits per strain
    double fmaster     = 1;         // Replication rate of the master string
    double ffit        = 0.0025;    // Replication rate of the mutants of the master string
    double fflat       = 0.25;      // Replication rate of the flat strings
    double f           = 0;
    int maxDist        = 5;         // Maximum Hamming distance for the mutant strings (for hamming distance larger than 5,
                                    // the string is considered as flat.
    int numOfRuns      = 100;       // Number of independent runs
    FILE *result;
    stringstream stream;
    string fileName;
    
    for(int r=0;r<numOfRuns;r++){
        cout<<"runIdx : "<<r<<endl; // Print the runIdx to track (optinal)
        for(int mm=0;mm<numOfBins;mm++){
            double mu = muMin+((muMax-muMin)/numOfBins)*mm;
            
            int **sequences;
            sequences = new int*[populationSize];
            for(int i=0; i<populationSize; i++){
                sequences[i] = new int[v];
            }
            
            int **strains;
            strains = new int*[generations];
            for(int i=0; i<generations; i++){
                strains[i] = new int[populationSize];
            }
            
            int *strainToReplicate = new int[v];
            int *mutation          = new int[v];
            
            for(int i=0; i<populationSize; i++){
                for(int k=0;k<v;k++){
                    sequences[i][k] = 1;
                }
            }
            
            for (int i=0; i<generations; i++){
                for(int j=0;j<populationSize;j++){
                    int indexToReplicate  = rand() % populationSize;  // Index of the string to be replicated
                    int indexToReplace    = rand() % populationSize;  // Index of the string to be replaced
                    while(indexToReplace==indexToReplicate){
                        indexToReplace    = rand() % populationSize;
                    }
                    
                    for(int s=0;s<v;s++){
                        strainToReplicate[s] = sequences[indexToReplicate][s];
                    }
                    int hammingDistance   = hammDist(strainToReplicate,v);
                    
                    if(hammingDistance==0){  // Adjust the replication rate depending on the Hamming Distance
                        f = fmaster;
                    }else if(hammingDistance<(maxDist+1)){
                        f = ffit;
                    }else{
                        f = fflat;
                    }
                    
                    // Add mutation
                    if(unifRand(0,1)<=f){
                        for(int k=0;k<v;k++){
                            if(unifRand(0,1)<=mu){
                                sequences[indexToReplace][k] = 1-sequences[indexToReplicate][k];
                            }else{
                                sequences[indexToReplace][k] = sequences[indexToReplicate][k];
                            }
                        }
                    }
                }
                
                for(int q=0;q<populationSize;q++){
                    int *tempSeq = new int[v];
                    
                    for(int z=0;z<v;z++){
                        tempSeq[z]=sequences[q][z];
                    }
                    strains[i][q] = binArr2dec(tempSeq,v); //Keep the decimal values of the strings
                    delete [] tempSeq;
                }
            }
            
            stream.str(string());
            stream << myRoot.str() << "strains_runIdx_"<<r<<"_muIdx_"<<mm<< ".txt"; // Save the decimal values of the strings with mutation rate and run index.
            fileName = stream.str();
            result = fopen(fileName.c_str(),"w+");
            
            for(int i=0;i<generations;i++){
                for(int s=0;s<populationSize;s++){
                    fprintf(result,  "%d ", strains[i][s]);
                }
                fprintf(result, "\n");
            }
            fclose(result);
            
            delete [] sequences;
            delete [] strains;
            delete [] strainToReplicate;
            delete [] mutation;
        }
    }
}
