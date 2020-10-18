%% Intelligent Systems Projet - Reinforcement Learning
% This script can only be runned with Matlab 2018b or higher since it uses
% the deep learning toolbox which is only available with 2018b.

clear all
close all hidden

%------ Initial Values
LOAD = 1;
PLOT = 1;
NEURO = 0; % To use or not use angle_idx from Neural Network

%------ Create and display circuit
circuit = Circuit('circuit_resized.png');
circuit.start=[38;19];
circuit.goal=[3;18];

% subplot(212);
% circuit.display_best_path();

% subplot(211);
FigH = figure('Position',[700 100 560 420]);
circuit.display_circuit();

hold on;

%------ Draw start and end point
% plot(circuit.start(1),circuit.start(2),'r*');
% plot(circuit.goal(1),circuit.goal(2),'g*');

%------ Load training data if existent (Q, episodes, reward across episodes...)
if(LOAD)
    % state is defined by (x, y, angle_idx); 3 are possible actions
    load('layers.mat'); % load the layers
    load('net.mat'); % loads the trained net
    load('data_used_to_train_NN.mat'); % This loads the data that was used to train the neural network
    episode = 0;
    R_history = [];
else
    Q = zeros(size(circuit.img_circuit,1), size(circuit.img_circuit,2), 16, 3);
    episode = 0;
    R_history = [];
end

%------ Q learning hyperparameters
alpha = 0.001;             % Learning Rate
gamma = 0.1;               % Discounting rate

% Exploration parameters for epsilon greedy strategy
explore_start = 1.0;         % exploration probability at start
explore_stop = 0.001;        % minimum exploration probability
decay_rate = 0.0001;         % exponential decay rate for exploration prob

R = 0;
%---------------------
dnn_NN = [];
stack_frames1 = [];
decay_step = 0;
%%%%%%%%%%%%%%%%%%%%%%

for p = 1:400000
    %---------------------
    dnn4=[];
    stack_frames=[];
    %%%%%%%%%%%%%%%%%%%%%%
    
    episode = episode + 1;
    title(sprintf('Episode: %d\n', episode));
    
    %------ Car starts at START POINT
    car_location = circuit.start; %[randi(size(circuit.img_circuit,2)); randi(size(circuit.img_circuit,1))];
    
    %------ Car starts at a RANDOM POSITION
    % random_start = circuit.road_location(randi(numel(circuit.road_location)));
    % car_location = zeros(2, 1);
    % [car_location(2), car_location(1)] = ind2sub([size(circuit.img_circuit, 1) size(circuit.img_circuit, 2)], random_start);
    
    car = MicroMachine('car_resized.png', car_location);
    car.angle = 0;
    actions = {@car.steer_left,@car.steer_right,@car.accelerate};
    
    episode_steps = 3000;
    
    old_location = car_location;
    old_angle_idx = car.angle_idx;
    
    for i = 1:episode_steps
        
        %------------------- EXPLORATION/EXPLOITATION ---------------------
        if i == 1
            best_action = 3; % Get the car in the first frame (does not do anything)
        else
            decay_step = decay_step + 1;
            exp_exp_tradeoff = rand(); % random value
            explore_probability = explore_stop + (explore_start - explore_stop) * ...
                exp(-decay_rate * decay_step);
            %------ Exploration
            if explore_probability > exp_exp_tradeoff
                % Make a random action (exploration)
                car.NEURO = 0;
                best_action = randi(length(actions),1);
            else
                %------ Exploitation
                % Get an action from Q-network (exploitation)
                car.NEURO = 1;
                act = predict(net,stack_frames{1,i-1});
                [a,action] = max(act);
                if (1<=action) && (action<=16)
                    best_action = 1;
                    car.angle_idx = action;
                elseif (17<=action) && (action<=32)
                    best_action = 2;
                    car.angle_idx = action-16;
                elseif (33<=action) && (action<=48)
                    best_action = 3;
                    car.angle_idx = action-(16*2);
                end
            end
        end
        actions{best_action}();
        [new_location, new_angle_idx] = car.move();
        
        if(PLOT)
            h = car.display_car();
        end
        
        [r_v(1), r_v(2), r_v(3)] = circuit.calculate_reward(car, old_location, new_location);
        r = [0 0 1]*r_v';
        
        R = R + r;
        
        %------ UPDATE Q
        Q(old_location(2),old_location(1),old_angle_idx, best_action) = ...
            Q(old_location(2),old_location(1),old_angle_idx,best_action) + ...
            alpha * (r + gamma*max(Q(new_location(2), new_location(1), new_angle_idx, :)) - Q(old_location(2),old_location(1), old_angle_idx, best_action));
        
        if(r_v(1)<0) % offroad
            break;
        end
        
        if(r_v(2)==1) % goal
            fprintf(1, '\n\nGOAL!\n\n');
            break;
        end
        
        if(PLOT)
            drawnow;
            Data(i) = getframe(FigH); % records the data of the open figure
        end
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %--------------------- CROP and STACK FRAMES ----------------------
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        [img_gray] = crop_img(Data, new_location,i);
        
        %------------------------- STACK FRAMES ---------------------------
        if i == 1
            for stack = 1:4
                d(:,:,stack) = img_gray;
            end
            stack_frames{1,i} = d;
        else
            d(:,:,1) = d(:,:,2);
            d(:,:,2) = d(:,:,3);
            d(:,:,3) = d(:,:,4);
            d(:,:,4) = img_gray;
            stack_frames{1,i} = d;
        end
        
        dnn3=[];
        % For each frame (step)
        for num_act = 1:3
            for j = 1:16
                dnn3 = [dnn3 Q(old_location(2),old_location(1),j,num_act)];
            end
        end
        dnn4{1,i}=dnn3; % each step (i)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        old_location = new_location;
        old_angle_idx = new_angle_idx;
        
    end
    %----------------------------------------------------------------------
    clear Data
    
    
    stack_frames1 = [stack_frames1 stack_frames];
    dnn_NN = [dnn_NN dnn4];
    if length(stack_frames1)>10000
        stack_frames1 = stack_frames1{1,(length(stack_frames1)-5000):end};
        dnn_NN = dnn_NN{1,(length(dnn_NN)-5000):end};
    end
    
    % Only trains every 50 episodes
    if(mod(episode,50)==0)
        
        [stack_frames_final, NN]=cellto4d(stack_frames1,dnn_NN); % Get variables in 4-D
        
        [~,~,~,r]=size(stack_frames_final);
        rand_numb1=randi(r,1,2000);
        for ra = 1:length(rand_numb1)
            stack_batch(:,:,:,ra)=stack_frames_final(:,:,:,rand_numb1(ra));
            nn_batch(:,:,:,ra)=NN(:,:,:,rand_numb1(ra));
        end
        
        %------ NEURAL NETWORK
        options = trainingOptions('adam', 'Plots', 'training-progress',...
            'MiniBatchSize', 200,'Plots','training-progress','Shuffle',...
            'every-epoch','MaxEpochs',1, 'Verbose',true,'VerboseFrequency',100);
        net = trainNetwork(stack_batch,nn_batch, netboa, options);
    end
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    if(PLOT)
        delete(h); delete(car); clear car;
    end
    
    %------ SAVE DATA
    if(mod(episode,100)==0)
        fprintf('Episode: %d\n', episode);
        
        % Print reward of last 100 episodes
        fprintf(1, 'Mean reward of last 100 episodes: %d\n', round(R/100));
        
        % Save history
        R_history(episode) = R;
        
        save('train_data.mat','Q','episode','R_history','-v7.3');
        save('stack_frames.mat','stack_frames','-v7.3');
        save('dnn_NN.mat','dnn_NN','-v7.3');
        
        R = 0;
    end
end