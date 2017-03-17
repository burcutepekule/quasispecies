clear all;clc;close all;
directory='/Users/burcu/desktop/quasiData/'; %Specify the directory of the text files
D = dir([directory,'strains_*']);
numOfFiles = size(D,1);
numOfMuValues = 100;
numOfRuns     = numOfFiles/numOfMuValues;
maxFitDist    = 5;
v             = 16;
hammingDists  = 0:v;
for i=1:length(hammingDists)
    indexes{i} = sum(2.^((combntns(1:v,v-(hammingDists(i))))-1),2);
end
deleteriousDist  = [1 2 3 4 5]; % Take the first 5 hamming distances for master sequence mutants
deleteriousDecs  = [];
for m=1:length(deleteriousDist)
    deleteriousDecs  = [deleteriousDecs;indexes{m+1}];
end
mm = 0:99;
muVec=0+((0.15-0)/100).*mm;
for k=1:numOfRuns
    for m=1:numOfMuValues
        [k m]
        fileName = ['strains_runIdx_' num2str(k-1) '_muIdx_' num2str(m-1)];
        tempStrains = readTxtFile(fileName,directory);
        for t=1:length(indexes)
            indxs = indexes{t};
            summa = 0;
            for g=1:length(indxs)
                summa = summa + length(find(tempStrains(end,:)==indxs(g)));
            end
            masterSeq(k,m,t) = summa;
        end
    end
end
save('quasi_data')


