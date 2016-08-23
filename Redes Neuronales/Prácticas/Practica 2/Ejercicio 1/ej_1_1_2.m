%-----------------------------------------------
%--- EJERCICIO 1.1.2 - XOR
%-----------------------------------------------

% x -> Entrada
x = [ -1 -1; 1 -1; -1 1; 1 1; ];

% y -> Resultados
y = [ -1; 1; 1; -1 ];

[w, b, cantErrores] = perceptronSimple(x, y);

if cantErrores > 0
	fprintf('Hay %d resultados incorrectos.\n', cantErrores);
else
	disp('--RESULTADOS--');
	disp('--W:');
	disp(w);
	disp('--b:');
	disp(b);
	disp('--------------');
end