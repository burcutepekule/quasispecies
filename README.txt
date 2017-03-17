HOW TO RUN THE CODE

1. To begin with, you should open the quasi_main.cpp in any kind of text editor, and change the directory that you want to save your data because currently it is specific to my computer :) So you should change the following line (line 45)

directory = "/Users/burcu/desktop/"; // Enter the root directory for data storage

to whichever directory you want, save the file, and quit. This part of code will create a folder called “quasiData” under the directory you specified. 

2. Open the Terminal

3. Make the bash script executable by typing

chmod +x ./quasi.sh

4. Run the bash script by typing

./quasi.sh

5. You should see the index of the run,

runIdx : 0
runIdx : 1
runIdx : 2
…

as the code is being executed. 

After all the runs are completed (there are 100 independent runs), you will see the data in text files stored in the quasiData folder (You specified the address of that folder at the first step by changing the line 45). 

6. I chose MATLAB to generate the plots. So you have to read this data with MATLAB first, and save the data in a .mat file. This is completely optional, you can use the data with whichever software you want.

In order to read the data and save it as a .mat file, first go to READ_QUASI_DATA.m, and specify the following line (line 5) according to the directory you generated at the first step.

directory='/Users/burcu/desktop/quasiData/'; %Specify the directory of the text files

Run the script afterwards. This script will create a .mat file called quasi_data.mat. Keep in mind that you also need the function readTxtFile.m to run this script, so don’t forget to put that in your current MATLAB folder as well :)

I also uploaded the quasi_data.m file that I generated, so you can just use it for the next step (which is plotting) and ignore all the steps before that.

7. You can use the quasi_data.mat file to generate the plot by running PLOT_QUASI_DATA.m.

P.S. : Since I don’t know the system you will use, C++ code is written sequentially on purpose. You can parallelize it if you’re familiar with parallel programming. I am sorry that the whole thing depends on C++ and MATLAB, unfortunately they are the first two languages that I am very familiar with. 

Hope you enjoy :) 

 


 




