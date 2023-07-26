
data = load('layers.txt');
[n,m] = size(data)
x = linspace(1,11,11);
for i = 1:n % цикл по строкам матрицы данных
    y = data(i,1:m); % извлечение значений y
    plot(x,y); % построение графика
    xlim([1 m]);
    ylim([850 880]);
    xlabel('x'); % подпись оси x
    ylabel('rho'); % подпись оси y
    title(sprintf('Шаг %d', i-1)); % название графика
    % Сохранение графика в папку "my_folder"    
    filename = sprintf('my_plot_%d.png', i);
    fullpath = fullfile('plots', filename);
    saveas(gcf, fullpath);
end