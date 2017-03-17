function [ variable_out] = readTxtFile( varname, directory )
longname  = [directory varname '.txt'];
[variable_out,~]=importdata(longname);
end

