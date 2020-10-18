% This code was downloaded from github
clear all
close all hidden

%------ Initial Values
TRY_LOAD = 1;
PLOT = 1;
EXPLORE = 1; % Does Exploration

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
if(TRY_LOAD && exist('train_datafinal.mat', 'file'))
    load('train_datafinal.mat');
else
    % state is defined by (x, y, angle_idx); 3 are possible actions
    Q = zeros(size(circuit.img_circuit,1), size(circuit.img_circuit,2), 16, 3);
    episode = 0;
    R_history = [];
end

alpha = 0.001;      % learning rate
gamma = 0.85;       % discount rate
epsilon = 0.001;

R = 0;

for p = 1:400000
    
    episode = episode + 1;
    title(sprintf('Episode: %d\n', episode));
    
    %------ Car starts at Start Point
    % car_location = circuit.start; %[randi(size(circuit.img_circuit,2)); randi(size(circuit.img_circuit,1))];
    
    %------ Car starts at a random position
    random_start = circuit.road_location(randi(numel(circuit.road_location)));
    car_location = zeros(2, 1);
    [car_location(2), car_location(1)] = ind2sub([size(circuit.img_circuit, 1) size(circuit.img_circuit, 2)], random_start);
    
    car = MicroMachine('car_resized.png', car_location);
    car.angle = car.angles_vec(randi(numel(car.angles_vec))); %random angle
    actions = {@car.steer_left,@car.steer_right,@car.accelerate};
    
    episode_steps = 3000;
    
    old_location = car_location;
    old_angle_idx = car.angle_idx;
    
    for i=1:episode_steps
        
            [max_val, best_action] = max(Q(old_location(2), old_location(1), old_angle_idx, :));
            if(max_val==0)
                best_action = randi(length(actions),1);
            end
            
            %------ Exploration
            if(EXPLORE)
                if(rand()< epsilon)
                    best_action = randi(length(actions),1);
                end
            end
            
        actions{best_action}();
        [new_location, new_angle_idx] = car.move();
        
        if(PLOT)
            h = car.display_car();
        end
        
        [r_v(1), r_v(2), r_v(3)] = circuit.calculate_reward(car, old_location, new_location);
        % r = sum(r_v / numel(r_v));
        r = [0 0 1]*r_v';
        
        R = R + r;
        
        %------ UPDATE Q
        Q(old_location(2),old_location(1),old_angle_idx, best_action) = ...
            Q(old_location(2),old_location(1),old_angle_idx,best_action) + ...
            alpha * (r + gamma*max(Q(new_location(2), new_location(1), new_angle_idx, :)) - Q(old_location(2),old_location(1), old_angle_idx, best_action));
        
        if(r_v(1)<0) % offroad
            break;
        end
        
%         if(r_v(2)==1) % goal
%             fprintf(1, '\n\nGOAL!\n\n');
%             break;
%         end
        
        if(PLOT)
            drawnow;
        end
        
        old_location = new_location;
        old_angle_idx = new_angle_idx;
        
    end
    
    if(PLOT)
        delete(h); delete(car); clear car;
    end
    
    % SAVE DATA
    if(mod(episode,100)==0)
        fprintf('Episode: %d\n', episode);
        
        % Print reward of last 100 episodes
        fprintf(1, 'Mean reward of last 100 episodes: %d\n', round(R/100));
        
        % Save history
        R_history(episode) = R;
        save('train_datafinal.mat','Q','episode','R_history','-v7.3');
        
        R = 0;
    end
end