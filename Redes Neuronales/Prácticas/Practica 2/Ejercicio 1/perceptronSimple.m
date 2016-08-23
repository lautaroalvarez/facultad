function [w, b, errores] = perceptronSimple(x, y, v, T, E)

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

% w -> unidades de salida (inicializan random)
%----falta hacer que arranquen random
w = rand(2,1) * 2 - 1;

% b -> desplazamiento de la recta ("")
b = 0;

% inicializamos variables
t = 0;
e = 1;

while (e > E) & (t < T)
	e = 0;
	for i = 1:4
		%--multiplicamos
		res = x(i,:) * w + b;
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
		%--calculamos valor de desplazamiento
		%bw = err * v;
		%--desplazamos la recta según el error
		b = b + v * err;
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
	res = x(i,:) * w + b;
	if (res > 0)
		res = 1;
	else 
		res = -1;
	end
	if y(i) != res
		errores++;
	end
end