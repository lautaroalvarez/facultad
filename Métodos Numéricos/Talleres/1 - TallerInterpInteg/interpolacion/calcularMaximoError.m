function maxError = calcularMaximoError(original, muestra)
    if length(original) < length(muestra)
        muestra = muestra(1:length(original));
    end
    
    if length(muestra) < length(original)
        original = original(1:length(muestra));
    end
    
    maxError = max(abs(original - muestra));
end