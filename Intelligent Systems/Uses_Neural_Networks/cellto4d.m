function [stack_frames_final, NN]=cellto4d(stack_frames1,dnn_NN)

stack_frames_final=[];
NN=[];

% Change stack_frames1 to 4-D
[~,b]=size(stack_frames1);
for i = 1:b
    stack_frames_final(:,:,:,i) = stack_frames1{1,:};
end

% Change dnn_NN to 4-D
[~,d]=size(dnn_NN);
for i = 1:d
    NN(1,1,:,i)=dnn_NN{1,i};
end
