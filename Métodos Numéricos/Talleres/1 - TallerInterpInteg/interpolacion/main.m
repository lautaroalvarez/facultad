%% Agencia de Inteligencia MN16
clear;
format short;
presicionInfinita = 0.0001; % decímetros (10^{-4} kilómetros)

% Valor de dt (delta t) para tomar las muestras del ciudadano (intervalo de tiempo
% entre todos los pares de fotografías).
dt = ____________; % en horas

% Conversión a minutos
dt = dt * 60;

%% Ciudadanos
ciudadano = @ciudadanoMareado;
%ciudadano = @ciudadanoKane;

%% Método de interpolación
interpolacion = @interpolacionFragmentariaLineal;
%interpolacion = @interpolacionSplines;

%% Obtención de muestras - Interpolación.

% Una muestra tomada cada dt segundos de la posicion (X(t),Y(t))
caminataSample = caminataDe(ciudadano, dt);

% Interpolación de esa caminata con el método elegido (devuelve para cada t
% el valor de la posición (X(t),Y(t)))
caminataInterpolada = interpolarCaminataCon(interpolacion, caminataSample, presicionInfinita);

% Caminata real del ciudadano (muestra con presición "infinita")
caminataPresicionInf = caminataDe(ciudadano, presicionInfinita);

%% Gráficos (para entender mejor qué está pasando)
graficarCaminata(caminataPresicionInf, 'Caminata Real');
graficarCaminata(caminataInterpolada, 'Caminata Interpolada');

%% Máximo error de interpolacón en X y en Y.
maxErrorX = calcularMaximoError(caminataInterpolada(:,2), caminataPresicionInf(:,2)); % en metros
maxErrorY = calcularMaximoError(caminataInterpolada(:,3), caminataPresicionInf(:,3)); % en metros

maxErrorX = maxErrorX / 1000  % en km
maxErrorY = maxErrorY / 1000  % en km
