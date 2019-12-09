figure(1)
for img = 1:1:750;
    data = imread(strcat('frame',num2str(img),'.jpg'));
    diff = imsubtract(data(:,:,1), rgb2gray(data));
    diff = im2bw(diff,0.15);
    diff = bwareaopen(diff,300);
    
    nb = bwlabel(diff, 8);
    box = regionprops(nb, 'BoundingBox', 'Centroid');
    
    subplot(111); 
    imshow(data);
    hold on
 
    for object = 1:length(box)
        bb = box(object).BoundingBox;
        rectangle('Position',bb,'EdgeColor','red','LineWidth',1)
    end
    hold off
    drawnow;
end
