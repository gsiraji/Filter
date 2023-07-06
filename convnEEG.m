EEG = readmatrix("data/sample_EEG_data.csv");
%%
test_C = readmatrix("data/output2.csv");

%%

h = [1.0, 2.0, 3.0]';
x = [1.0, 2.0 3.0 4.0 5.0 6.0 7.0, 8.0 9.0 10.0]';

x = [1.0, 2.0; 3.0 4.0; 5.0 6.0; 7.0, 8.0; 9.0 10.0];

x = [1.0; 3.0 ; 5.0 ; 7.0; 9.0 ];

test_C = convn(h,x,"full")
%%
y = zeros(6,1);
for col = 1:3
    for i = 1:6
        x_start = max(1,i-3+1)
        x_end = min(i+1, 4)
        h_start = min(i+1, 2)
        for j = x_start:x_end
            y(i + (col-1)*(3+4-1)) = y(i + (col-1)*(3+4-1))  + (h(h_start)*x(j+ (col-1)*4) );
            h_start = h_start - 1;
        end
    end
end


%%

% test = fir1()
windowed = buffer(eeg(:,1),4*500,3*500); 
C = convn(HznotchFIRweights,windowed,"full");
C = reshape(C, [159600, 1]);
plot(C)
%%
signal = eeg(:,1);
epochLength = 4*500;                  % Length of each epoch in seconds
overlapSize = 3*500;                  % Amount of overlap between consecutive epochs

samplingRate = 1;                % Sampling rate of the signal in samples per second
epochSize = epochLength * samplingRate;  % Number of samples in each epoch

% Calculate the required padding length
paddingLength = (numel(signal) - 1) * (epochSize - overlapSize) + epochSize;

% Zero-pad the signal
paddedSignal = [signal; zeros(1, paddingLength - numel(signal))'];

% Create a matrix to store the epochs
numEpochs = floor((numel(paddedSignal) - epochSize) / (epochSize - overlapSize)) + 1;
epochs = zeros(epochSize, numEpochs);
filterSize= length(filter);
C = zeros(epochSize+filterSize-1,numEpochs);
%%
% Extract the epochs with overlap
trimmedOutput = zeros(500,numEpochs);
for i = 1:numEpochs
    startIdx = (i-1) * (epochSize - overlapSize) + 1;
    epochs(:, i) = paddedSignal(startIdx:startIdx+epochSize-1);
    % Apply convolution on the epoch
    C(:,i) = convn(epochs(:, i),HznotchFIRweights,'full');
    % Trim the output to remove edge effects
    trimmedOutput(:,i) = C(startIdx:startIdx+epochSize-overlapSize-1,i);

    % Use the trimmed output as needed
    plot(trimmedOutput)
end
%%
signal = eeg(:,1);  % Example signal
epochLength = 4*500;                  % Length of each epoch in seconds

samplingRate = 1;                % Sampling rate of the signal in samples per second
epochSize = epochLength * samplingRate;  % Number of samples in each epoch

% Calculate the number of epochs
numEpochs = floor(numel(signal) / epochSize);

% Create a matrix to store the epochs
epochs = zeros(epochSize, numEpochs);

% Extract the epochs
for i = 1:numEpochs
    startIdx = (i-1) * epochSize + 1;
    epochs(:, i) = signal(startIdx:startIdx+epochSize-1);
end
filter = HznotchFIRweights;
filterSize= length(filter);
C = zeros(epochSize+filterSize-1,numEpochs);
% Perform convolution on each epoch
for i = 1:numEpochs
    % Apply convolution on the epoch
    C(:,i) = convn(epochs(:,i),filter);
    % Use the output as needed
end

% Perform convolution on each epoch
% for i = 1:numEpochs
%     
% end


%%

C1 = convn(eeg,filter,"full");
%%
% plot(EEG(:,1), 'o')
% hold on;
% plot(HznotchFIRweights,'o')
% hold on;
% plot(C1,'o')
% 
% %%
Fs=500;
[popen,fopen] = periodogram(eeg,[],[],Fs);
[pbutt,fbutt] = periodogram(test_C,[],[],Fs);
%%
plot(fopen,20*log10(abs(popen)),'ok',fbutt,20*log10(abs(pbutt)),':or')
ylabel('Power/frequency (dB/Hz)')
xlabel('Frequency (Hz)')
title('Power Spectrum')
legend('Unfiltered','Filtered')
grid
