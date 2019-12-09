%{
X1 = imread('photo.jpg');
SE = strel('diamond', 3);
X2 = imerode(X1,SE);
im_gray=rgb2gray(X2);
im_R=X2(:,:,1);
im_r=imsubtract(im_R,im_gray);

figure(1)
subplot(121); imshow(X1); title('Image couleur RGB');
subplot(122); imshow(im_r); title('Image résultante');
%}

%{
a=VideoReader('test.mp4');
for img = 1:1:100;
    filename=strcat('frame',num2str(img),'.jpg');
    b = read(a, img);
    imshow(b);
    imwrite(b,filename);
end
movie(img)
%}

a=VideoReader('test.mp4');
for img = 1:1:100;
    
end
