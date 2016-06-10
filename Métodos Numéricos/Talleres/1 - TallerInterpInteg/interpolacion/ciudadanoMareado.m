% t:
%    es un vector columna de tiempos (en minutos)
% posicionesXY:
%    es una matrix que en cada fila contiene la posicion (X(t_i),Y(t_i))
%    para cada tiempo en t. (en metros)

function posicionesXY=ciudadanoMareado(t)
    Xt = @(t) 500*(sin(t+10)/(t+10) + cos(t+10)/(t+10));
    Yt = @(t) t;
    
    posicionesXY = zeros(length(t), 2);
    for i = 1:length(t),
        if t(i) == -10,
           posicionesXY(i,:) = [0,0];
        else
           posicionesXY(i,:) = [Xt(t(i)), Yt(t(i))];
        end
    end
end