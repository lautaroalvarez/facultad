% caminataSample:
%    Una matriz que en la fila i tiene una muestra (t_i, X(t_i), Y(t_i)),
%    donde t_i es la variable de tiempo en segundos, X(t_i) es la posición
%    en X en metros e Y(t_i) es la posición en Y en metros.
%    Está ordenada según t_i ascensdente (t_i < t_{i+1} para todo i).

% tiempos:
%    Tiempos t para los cuales se desea conocer la posición (vector fila).
%    Se asume que caminataSample(1,1) <= t <= caminataSample(end,1)
%    para todo t y que tiempos está ordenado (tiempos_j < tiempos_{j+1}).

% ftt:
%    Devuelve el valor de f(t) = (X(t), Y(t)) para cada t \in tiempos.
%    Cada fila debe ser de la pinta [t, X(t), Y(t)].

function ftt=interpolacionSplines(caminataSample, tiempos)
    Xtt = spline(caminataSample(:,1)',caminataSample(:,2)', tiempos)';
    Ytt = spline(caminataSample(:,1)',caminataSample(:,3)', tiempos)';
    
    ftt = [tiempos', Xtt, Ytt];
end