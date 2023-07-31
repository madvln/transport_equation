#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <clocale>
using namespace std;

class transport_equation_solver {
public:

	transport_equation_solver(int steps, double pipe_len, double step_len)
	{
		setlocale(LC_CTYPE, "rus"); //в консоли чтобы кириллица была
		N = steps;
		n = static_cast<int>(pipe_len / step_len + 0.5) + 1;//считаем количество точек
	}

	int get_point_count() const {
		return n;
	}

	vector<double> get_layer_prev() const {
		return layer_prev;
	}

	vector<double> get_layer_next() const {
		return layer_next;
	}

	vector<double> gen_layer_with_rho(int points, double mid_rho, int spread)
	{
		srand(time(0));
		vector<double> layer(points);
		for (int i = 0; i < points; i++)
			layer[i] = rand() % spread + mid_rho;
		return layer;
	}

	vector<vector<double>> get_and_print_layers(vector<double> zero_layer, vector<double> rho_in, vector<double> rho_out, vector<double> flow)
	{
		ofstream fout("layers.txt");
		if (fout.is_open())
		{
			vector<vector<double>> layers(2, zero_layer);

			for (int j = 0; j < n; j++)
				fout << layers[0][j] << "\t";
			fout << "\n";
			int Nin = rho_in.size();
			int Nout = rho_out.size();
			for (int i = 0; i < N; i++)
				if (flow[i] > 0)
				{
					layers[0] = layers[1];
					layers[1][0] = rho_in[Nin - 1 - i];

					for (int k = 0; k < n - 1; k++)
						layers[1][k + 1] = layers[0][k];

					for (int j = 0; j < n; j++)
						fout << layers[1][j] << "\t";
					fout << "\n";
				}
				else
				{
					layers[0] = layers[1];
					layers[1][n - 1] = rho_out[i];

					for (int k = n - 1; k > 0; k--)
						layers[1][k - 1] = layers[0][k];

					for (int j = 0; j < n; j++)
						fout << layers[1][j] << "\t";
					fout << "\n";
				}
			layer_prev = layers[0];
			layer_next = layers[1];
			return layers;
		}
		fout.close();
	}
private:
	int N;
	int n;
	vector<double> layer_prev;
	vector<double> layer_next;
};