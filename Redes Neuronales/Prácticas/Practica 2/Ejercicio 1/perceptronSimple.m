function [w, errores] = perceptronSimple(x, y, v, T, E)

if nargin < 2
	disp('Datos de entrada de la función:    ( *opcional )');
	disp(' X -> datos de entrada');
	disp(' Y -> resultados de la entrada');
	disp(' V -> velocidad de aprendizaje *');
	disp(' T -> máxima cantidad de repeticiones *');
	disp(' E -> cota de error máximo *');
	return;
end

if nargin < 3
	% v -> velocidad de aprendizaje
	v = 0.05;
end

if nargin < 4
	% T -> máxima cantidad de repeticiones
	T = 100000;
end

if nargin < 5
	% E -> cota de error máximo
	E = 0.01;
end

% amplio la entrada x poniendo un -1 al final para el umbral
x = [x repmat(-1,length(x),1)];

% w -> unidades de salida (inicializan random)
%----falta hacer que arranquen random
w = rand(length(x(1)),1) * 2 - 1;

% inicializamos variables
t = 0;
e = E + 1;

while (e > E) & (t < T)
	e = 0;
	for i = 1 : length(x)
		%--multiplicamos
		res = x(i,:) * w;
		%--aplicamos la función de activación
		if res > 0
			res = 1;
		else
			res = -1;
		end
		%--calculamos el error
		err = y(i) - res;
		%--calculamos valor de aprendizaje
		dw = v * err * x(i,:)';
		%--aplicamos aprendizaje
		w = w + dw;
		%--acumulamos el error
		e = e + err^2;
	end
	%--multiplicamos la sumatoria de error por 1/2
	e = 1/2 * e;
	%--aumentamos el valor de repetición
	t = t + 1;
end

errores = 0;

for i = 1 : length(y)
	res = x(i,:) * w;
	if (res > 0)
		res = 1;
	else 
		res = -1;
	end
	if y(i) != res
		errores++;
	end
end