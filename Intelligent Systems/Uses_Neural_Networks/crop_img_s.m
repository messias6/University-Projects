function [f_gray] = crop_img_s(Data, new_location,i)
% Function to get an image portion with the car since using the all image
% in the neural network would probably make it last longer when running.
% Therefore, it only uses a portion (100x100).

% [xmin ymin width height]; xmin,ymin - where the crop will begin
% (upper left side) and width,height
% The values were chose looking at the image on the left (original).
I2 = imresize(imcrop(Data(i).cdata,[92 40 542 427]),[200 442]); % Image without the axis, title etc

% Get a square/rectangle surrouding the car

% Localization of the car
x_cent = new_location(1);
y_cent = new_location(2);

% size of the image
size_of_cropped_img = 100;

%I2 = imcrop(I,rect) crops the image I. rect is a four-element position vector of the
%form [xmin ymin width height] that specifies the size and position of the crop rectangle.
%imcrop returns the cropped image, I2.
xmin = x_cent-size_of_cropped_img/2;
ymin = y_cent-size_of_cropped_img/2;

% crop and resize of the square surrouding the car
I3 = imresize(imcrop(I2,[xmin ymin size_of_cropped_img size_of_cropped_img]),[90 90]);
f_gray = I3(:,:,1); % only the red part of the image

% if i == 1
%     % Will only take images for 1 frame - report purpose
%     figure;
%     subplot(2,2,1); imshow(Data.cdata); axis on;
%     subplot(2,2,2); imshow(I2);
%     subplot(2,2,3); imshow(I3);
%     subplot(2,2,4); imshow(f_gray);
% end
