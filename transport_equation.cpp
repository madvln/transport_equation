#include "transport_equation_solver.h"
int main()
{
	double length = 10000;//����� �����
	double dx = 1000;//������ ����
	int N = 5;//���-�� �����
	vector<double> flow(N, 0.5);//������ ������� �� ������ ����
	transport_equation_solver solver(N, length, dx);//��������� solver ��� ��������� ���������� � ������� ���������� �����
	int n = solver.get_point_count();//�������� ���������� �����
	vector<double> layer_zero(n, 870);//vector<double> layer_zero = solver.gen_layer_with_rho(n,860,20);//������� ������ ����, ������ ������� = ���-�� �����
	vector<double> rho_in(N, 860);//vector<double> rho_in = solver.gen_layer_with_rho(N,850,10);//������� ������ � �������� �����������, ������ ������� = ���-�� �����
	vector<double> rho_out(N, 880);//vector<double> rho_out = solver.gen_layer_with_rho(N,870,10);//������� ������ � ��������� �����������
	vector<vector<double>> layers = solver.get_and_print_layers(layer_zero,rho_in,rho_out,flow);//�������� ������� �� ���� �����, �������� � txt ��� ����
	vector<double> prev_layer = solver.get_layer_prev();//�������� ����
	vector<double> next_layer = solver.get_layer_next();//����� ����
}