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

function ftt=interpolacionFragmentariaLineal(caminataSample, tiempos)
    % Inicialización del output.
    ftt = zeros(length(tiempos), 3);
    
    % Iterador de caminataSample (los tiempos allí también están ordenados)
    i = 1;
    
    % Iterador de ftt (para ir llenando las filas con f(t))
    j = 1;
    
    % Recorrer tiempos (están ordenados de menor a mayor)
    % Ojo que solo se pueden iterar vectores fila
    for t = tiempos,
        
        % Incrementar i hasta encontrar el intervalo donde está t.
        % En general tomo el intervalo tal que t \in (t_{i-1}, t_{i}],
        % salvo el caso i=1, que se toma [t_1, t_2].
        while caminataSample(i,1) < t
            i = i+1;
        end
        
        if i == 1,
            % El intervalo correspondiente a t es [t_1, t_2]
            a = caminataSample(1,1);
            Xa = caminataSample(1,2);    %% X(a)
            Ya = caminataSample(1,3);    %% Y(a)

            b = caminataSample(2,1);
            Xb = caminataSample(2,2);    %% X(b)
            Yb = caminataSample(2,3);    %% Y(b)
        else
            % El intervalo correspondiente a t es [t_{i-1}, t_i]
            a = caminataSample(i-1,1);
            Xa = caminataSample(i-1,2);  %% X(a)
            Ya = caminataSample(i-1,3);  %% Y(a)

            b = caminataSample(i,1);
            Xb = caminataSample(i,2);    %% X(b)
            Yb = caminataSample(i,3);    %% Y(b)
        end
    
        % Realizar interpolación lineal para X(t) con t \in [a,b]
        Xt = _______________; % X(t)

        % Realizar interpolación lineal para Y(t) con t \in [a,b]
        Yt = _______________; % Y(t)

        % f(t) = (X(t), Y(t))
        ft = [Xt, Yt];
        
        % Guardo el resultado de (t, X(t), Y(t)) en la fila j
        ftt(j,:) = [t, ft];
        j = j+1;
    end
end
