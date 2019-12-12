figure(1)
vid = VideoReader('test1.mp4');
get(vid);
nbr = vid.NumberOfFrames;

for img = 1:1:nbr
    %Diviser la video en images
    image1 = read(vid, img);
    imshow(image1,[]);
    
    diamond = strel('diamond', 3);
    erode = imerode(image1,diamond);
    
    %Soustraction de la couleur rouge
    diff = imsubtract(erode(:,:,1), rgb2gray(erode));
    diff = im2bw(diff,0.15);
    diff = bwareaopen(diff,500);
    
    nb = bwlabel(diff, 8);
    box = regionprops(nb, 'BoundingBox', 'Centroid');
    
    %Affichage de l'image
    subplot(111); 
    imshow(image1);
    
    hold on
    %Boucle permettant d'afficher le rectangle
    for object = 1:length(box)
        bb = box(object).BoundingBox;
        rectangle('Position',bb,'EdgeColor','red','LineWidth',1)
    end
    hold off
    drawnow;
end
