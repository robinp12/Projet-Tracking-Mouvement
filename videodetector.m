% Diviser la video en plusieurs images
a=VideoReader('test.mp4');
for img = 1:1:100;
    filename=strcat('frame',num2str(img),'.jpg');
    b = read(a, img);
    imshow(b);
    imwrite(b,filename);
end
movie(img)
