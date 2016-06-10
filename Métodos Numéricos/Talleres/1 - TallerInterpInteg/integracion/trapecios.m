% Calcula una integral propia usando trapecios.

% F = [f(t_0), f(t_1), ...., f(t_n)]
% h = t_{i+1} - t_{i}
% res = aproximación de integral de f entre t_0 y t_n usando trapecios.
function res=trapecios(F, h)
    res=h/2 * (2*sum(F(2:end-1)) + F(1) + F(end));
end