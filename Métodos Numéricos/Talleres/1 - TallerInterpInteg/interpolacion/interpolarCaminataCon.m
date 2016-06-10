% unMetodoDeInterpolacion:
%    Una función de interpolación que dada una matriz de muestras y un
%    vector de tiempos, devuelve [t, f(t)] = [t, X(t), Y(t)] como fila para
%    cada tiempo t \in tiempos.

% caminataSample:
%    Una matriz que en cada fila tendrá tuplas (t, X(t), Y(t))

% granularidad:
%    Tiempo entre cada par de mediciones en la caminata interpolada.

% caminataInterpolada:
%    Una matriz que en cada fila tendrá tuplas (t, X(t), Y(t)). El tiempo
%    inicial y final será el mismo que en caminataSample, lo que cambia es
%    la granularidad.

function caminataInterpolada = interpolarCaminataCon(unMetodoDeInterpolacion, caminataSample, granularidad)
    tiempos = caminataSample(1,1):granularidad:caminataSample(end,1);
    caminataInterpolada = unMetodoDeInterpolacion(caminataSample, tiempos);
end