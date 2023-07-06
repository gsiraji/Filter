function eeg_array = myReadSheet(filename, num_records)

num_columns = 16;
f = fopen(filename,"r");
% fgets(f)
% Scan and ignore a variable number of description lines at the beginning
% of the CSV file.
line = fgetl(f);

eeg_array = zeros(num_records,num_columns);

formatSpec = repmat('%f,', 1, num_columns-1);  % Repeat '%f,' 16 times
formatSpec = [formatSpec '%f\n'];
% Read each line in the CSV file till you reach EOF. Construct an array of
% datetime and double values (for time and temp columns).
while(~feof(f))

    [result,count] = fscanf(f,formatSpec,[num_columns,num_records]);

    for j = 1:num_columns
    eeg_array(:,j) = result(j,:);
    end

end

fclose(f);

end

