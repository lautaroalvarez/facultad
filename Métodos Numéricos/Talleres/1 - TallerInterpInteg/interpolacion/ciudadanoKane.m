% t:
%    es un vector columna de tiempos ordenado de menor a mayor (en minutos)
% posicionesXY:
%    es una matrix que en cada fila contiene la posicion (X(t_i),Y(t_i))
%    para cada tiempo en t. (en metros)

function posicionesXY=ciudadanoKane(t)
    Xt = @(t) ((t-floor(t)/2)/2).*(mod(floor(t),2)==0) + ((floor(t) + 1)/4).*(mod(floor(t),2)==1);
    Yt = @(t) Xt(t+1) - 0.5;
    
    posicionesXY = zeros(length(t), 2);
    for i = 1:length(t),
        if t(i) <= 0,
           posicionesXY(i,:) = [0, 0];
        else
           posicionesXY(i,:) = [Xt(t(i)), Yt(t(i))];
        end
    end
    
    % escalar a metros razonables
    posicionesXY = 100*posicionesXY;
end