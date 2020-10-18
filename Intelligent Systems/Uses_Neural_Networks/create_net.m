load('netboa.mat')
load('Merda_3.mat')


options = trainingOptions('adam', 'Plots', 'training-progress',...
     'MiniBatchSize',200,'Plots','training-progress','Shuffle',...
     'every-epoch','MaxEpochs',1, 'Verbose',true,'VerboseFrequency',100);
net = trainNetwork(stack_frames_final,NN, netboa, options);
