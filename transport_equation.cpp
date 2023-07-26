#include "transport_equation_solver.h"
int main()
{
	double length = 10000;//длина трубы
	double dx = 1000;//размер шага
	int N = 5;//кол-во шагов
	vector<double> flow(N, 0.5);//массмв потоков на каждом шагу
	transport_equation_solver solver(N, length, dx);//объявляем solver как классовую переменную и считаем количество точек
	int n = solver.get_point_count();//получаем количество точек
	vector<double> layer_zero(n, 870);//vector<double> layer_zero = solver.gen_layer_with_rho(n,860,20);//генерим первый слой, размер массива = кол-во точек
	vector<double> rho_in(N, 860);//vector<double> rho_in = solver.gen_layer_with_rho(N,850,10);//генерим массив с входными плотностями, размер массива = кол-во шагов
	vector<double> rho_out(N, 880);//vector<double> rho_out = solver.gen_layer_with_rho(N,870,10);//генерим массив с выходными плотностями
	vector<vector<double>> layers = solver.get_and_print_layers(layer_zero,rho_in,rho_out,flow);//получаем матрицу из двух слоев, печатаем в txt все слои
	vector<double> prev_layer = solver.get_layer_prev();//предыдущ слой
	vector<double> next_layer = solver.get_layer_next();//текущ слой
}