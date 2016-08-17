% x -> Entrada
x = [-1 -1; 1 -1; -1 1; 1 1];

% y -> Salida
y = [ -1 1 1 1];

% w -> unidades de salida (inicializan random)
%----falta hacer que arranquen random
w = [-0.5; 0.2];

% E -> cota de error máximo
E = 0.01;

% T -> máxima cantidad de repeticiones
%T = 100000;
T = 2;

% v -> velocidad de aprendizaje
v = 0.05;

% inicializamos variables
t = 0;
e = 1;

while (e > E) & (t < T)
	e = 0;
	for i = 1:4
		disp('--------------------');
		res = x(i,:) * w;
		disp('--res1');
		disp(res);
		if res > 0
			res = 1;
		else
			res = -1;
		end
		disp('--res2');
		disp(res);
		err = y(i) - res;
		disp('--err');
		disp(err);
		dw = v * x(i,:)' * err;
		disp('--dw');
		disp(dw);
		w = w + dw;
		disp('--w');
		disp(w);
		e = e + err^2;
	end
	%e = 1/2 * e;
	t = t + 1;
end

disp('***********');
disp(w);
disp('***********');
disp(e);
disp('***********');
disp(t);
disp('***********');
disp(x(1,:) * w);
disp(x(2,:) * w);
disp(x(3,:) * w);
disp(x(4,:) * w);