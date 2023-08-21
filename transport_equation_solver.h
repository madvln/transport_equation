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

	vector<vector<double>> get_and_print_layers(vector<double> zero_layer, vector<double> zero_layer2, vector<double> flow, vector<double> rho_in = vector<double>(1, 0), vector<double> rho_out = vector<double>(1, 0), vector<double> sera_in = vector<double>(1, 0), vector<double> sera_out = vector<double>(1, 0))
	{
		ofstream fout("layers.txt");
		if (fout.is_open())
		{
			int K = 0;
			if (sera_in[0] > 0)
				K = K + 2;
			if (rho_in[0] > 0)
				K = K + 2;
			vector<vector<double>> inoutlayers(4);
			inoutlayers[0] = rho_in;
			inoutlayers[1] = rho_out;
			inoutlayers[2] = sera_in;
			inoutlayers[3] = sera_out;
			vector<vector<double>> layers(4);
			layers[0] = zero_layer;
			layers[1] = zero_layer;
			layers[2] = zero_layer2;
			layers[3] = zero_layer2;



			int Nin = rho_in.size();
			int Nout = rho_out.size();
			for (int k = 0; k < K; k = k + 2)
			{
				for (int j = 0; j < n; j++)
					fout << layers[k][j] << "\t";
				fout << "\n";
				for (int i = 0; i < N; i++)
					if (flow[i] > 0)
					{
						layers[k] = layers[k + 1];
						layers[k + 1][0] = inoutlayers[k][Nin - 1 - i];

						for (int l = 0; l < n - 1; l++)
							layers[k + 1][l + 1] = layers[k][l];

						for (int j = 0; j < n; j++)
							fout << layers[k + 1][j] << "\t";
						fout << "\n";
					}
					else
					{
						layers[k] = layers[k + 1];
						layers[k + 1][n - 1] = inoutlayers[k + 1][i];

						for (int l = n - 1; l > 0; l--)
							layers[k + 1][l - 1] = layers[k][l];

						for (int j = 0; j < n; j++)
							fout << layers[k + 1][j] << "\t";
						fout << "\n";
					}
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