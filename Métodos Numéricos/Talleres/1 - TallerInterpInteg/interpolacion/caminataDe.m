% unCiudadano:
%    función que toma un vector columna de tiempos y devuelve
%    una matriz que en cada fila contiene la posición
%    (X(t_i),Y(t_i)) para cada tiempo.

% tiempoEntreDosImagenes:
%    tiempo utilizado para discretizar el minuto de
%    duración de la caminata.

% listaDePosicionesXYPorTiempo:
%    Una matrix que en cada fila contiene (t, X(t),Y(t)), es decir el
%    instante de tiempo y la posición del ciudadano en ese instante.

function listaDePosicionesXYPorTiempo=caminataDe(unCiudadano, tiempoEntreDosImagenes)
    h = tiempoEntreDosImagenes;
    listaDePosicionesXYPorTiempo = [(0:h:30)', unCiudadano((0:h:30)')];
end