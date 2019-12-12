
%Ouvrir la fenetre
fig = figure;
%Importer la video
vid = VideoReader('test1.mp4');
get(vid);
%Stocker le nombre de frame
nbr = vid.NumberOfFrames;

%Enregistrer la video finale
vidfile = VideoWriter('final');
open(vidfile);

%Debut du traitement de chaque frame
for img = 1:nbr
    %Diviser la video en images
    image1 = read(vid, img);
    
    %Afficher chaque image de base
    imshow(image1);
    
    %Meilleur contour pour les couleurs
    diamond = strel('diamond', 3);
    erode = imerode(image1,diamond);
    
    %Soustraction de la couleur rouge
    diff = imsubtract(erode(:,:,1), rgb2gray(erode));
    %imshow(diff);
    
    %Garder seulement les zones voulues
    diff = im2bw(diff,0.15);
    diff = bwareaopen(diff,500);
    %imshow(diff);
    
    %Etiqueté chaque forme distinctement
    nb = bwlabel(diff, 8);
    box = regionprops(nb, 'BoundingBox', 'Centroid');
    
    hold on
    %Boucle permettant d'afficher le rectangle
    for object = 1:length(box)
        bb = box(object).BoundingBox;
        rectangle('Position',bb,'EdgeColor','red','LineWidth',1)
    end
    hold off
    
    %Enregistrement de la nouvelle video
    frm = getframe(fig);
    writeVideo(vidfile,frm);
    
    %Afficher dans matlab
    drawnow;
end

%Fermer le fichier video ecrit
close(vidfile);
