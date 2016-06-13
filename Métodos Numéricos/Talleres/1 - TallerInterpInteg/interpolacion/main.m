%% Agencia de Inteligencia MN16
clear;
format short;
presicionInfinita = 0.0001; % decímetros (10^{-4} kilómetros)

% Valor de dt (delta t) para tomar las muestras del ciudadano (intervalo de tiempo
% entre todos los pares de fotografías).
dt = 0.000125; % en horas

% Conversión a minutos
dt = dt * 60;

disp("1/8--Crea ciudadanoMareado");
%% Ciudadanos
ciudadano = @ciudadanoMareado;
%ciudadano = @ciudadanoKane;

disp("2/8--Crea interpolacion interpolacionFragmentariaLineal");
%% Método de interpolación
interpolacion = @interpolacionFragmentariaLineal;
%interpolacion = @interpolacionSplines;

%% Obtención de muestras - Interpolación.

disp("3/8--Toma muestras para interpolar");
% Una muestra tomada cada dt segundos de la posicion (X(t),Y(t))
caminataSample = caminataDe(ciudadano, dt);

disp("4/8--Interpola las muestras");
% Interpolación de esa caminata con el método elegido (devuelve para cada t
% el valor de la posición (X(t),Y(t)))
caminataInterpolada = interpolarCaminataCon(interpolacion, caminataSample, presicionInfinita);

disp("5/8--crea caminata real");
% Caminata real del ciudadano (muestra con presición "infinita")
caminataPresicionInf = caminataDe(ciudadano, presicionInfinita);

disp("6/8--grafica caminatas");
%% Gráficos (para entender mejor qué está pasando)
graficarCaminata(caminataPresicionInf, 'Caminata Real');
graficarCaminata(caminataInterpolada, 'Caminata Interpolada');

disp("7/8--calcula errores maximos");
%% Máximo error de interpolacón en X y en Y.
maxErrorX = calcularMaximoError(caminataInterpolada(:,2), caminataPresicionInf(:,2)); % en metros
maxErrorY = calcularMaximoError(caminataInterpolada(:,3), caminataPresicionInf(:,3)); % en metros

disp("8/8--pasa errores maximos a km");
maxErrorX = maxErrorX / 1000  % en km
maxErrorY = maxErrorY / 1000  % en km
disp(maxErrorX);
disp(maxErrorY);