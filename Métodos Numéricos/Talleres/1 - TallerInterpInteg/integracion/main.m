%% Integración
clear;
format long;

% Para integrar se usan los puntos {x_0, ..., x_n}. n determina la cantidad
% de puntos. x_0 = 0. x_n = 1.
n_trapecios = _____________;
n_simpson = ___________;

% Función a integrar
f = @(x) exp(-x.^2);

%% Resolver integral usando Trapecios
% Distancia entre cada par de puntos h = x_{i+1} - x_{i}.
h = 1/n_trapecios;

% Obtener un vector con los valores [x_0, ..., x_n], x_0 = 0, x_n = 1.
X = 0:h:1;

% Obtener un vector con la evaluación de la función [f(x_0), ..., f(x_n)]
F = f(X);

% Integrar usando Simpson
int_trapecios = trapecios(F,h)

%% Resolver integral usando Simpson
% Distancia entre cada par de puntos h = x_{i+1} - x_{i}.
h = 1/n_simpson;

% Obtener un vector con los valores [x_0, ..., x_n], x_0 = 0, x_n = 1.
X = 0:h:1;

% Obtener un vector con la evaluación de la función [f(x_0), ..., f(x_n)]
F = f(X);

% Integrar usando Simpson
int_simpson = simpson(F,h)

%% Resolver integral usando Matlab

int_matlab = integral(f,0,1)


%% Comparación

errorAbsolutoTrapecios = abs(int_matlab - int_trapecios)

errorAbsolutoSimpson = abs(int_matlab - int_simpson)

[errorAbsolutoTrapecios < 10^(-6), errorAbsolutoSimpson < 10^(-6)]

