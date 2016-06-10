% Calcula una integral propia usando simpson.

% F = [f(x_0), f(x_1), ...., f(x_n)]
% h = x_{i+1} - x_{i}
% res = aproximación de integral de f entre x_0 y x_n usando simpson.
function res=simpson(F, h)
    if mod(length(F),2) == 0,
        F = F(1:end-1);
    end
    
    n = length(F) - 1;
    res = 0;
    for j=1:n/2,
       res = res + ________________; 
    end
end
