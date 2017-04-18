close all;
clear all;

[X,Y]= meshgrid(-5:.1:5);
Z=20 + X.^2 + Y.^2 -10*(cos(2*pi*X) + cos(2*pi*Y));
figure;
meshc(X,Y,Z);
title('Rastrigin Function');

Z=(1-X).^2 +100*(Y-X.^2).^2;
figure;
meshc(X,Y,Z);
title('Rosenbrock Function');

Z=(X.^2 + Y.^2).*exp(-(X.^2 + Y.^2));
%Z(50,50)=1;
figure;
meshc(X,Y,Z);
title('CI class Function');

Z= -X.^4 - Y.^4 + 4.*X.*Y;
figure;
meshc(X,Y,Z);
title('Sudeep Function');

Z = X.^2 + Y - 11 + (X+ (Y.^2)-7).^2
figure;
meshc(X,Y,Z);
title('Rachit Function');

Z = abs(X-Y-5);
figure;
meshc(X,Y,Z);
title('Pallav Function');

Z = X.^2 + Y.^2 - X.*Y;
figure;
meshc(X,Y,Z);
title('Mayank Function');
