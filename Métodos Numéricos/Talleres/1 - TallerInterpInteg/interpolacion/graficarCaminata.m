function graficarCaminata(caminata, titulo)
    figure('name', titulo);
    subplot(2,2,1);
    plot(caminata(:,1), caminata(:,2));
    title('X(t)');
    xlabel('t [min]');
    ylabel('X [mts]');
    grid on;

    subplot(2,2,2);
    plot(caminata(:,1), caminata(:,3));
    title('Y(t)');
    xlabel('t [min]');
    ylabel('Y [mts]');
    grid on;

    subplot('Position',[0.35, 0.1, 0.35, 0.35]);
    plot(caminata(:,2), caminata(:,3));
    title('Caminata en el plano');
    xlabel('X [mts]');
    ylabel('Y [mts]');
    grid on;
    
end