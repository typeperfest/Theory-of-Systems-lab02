#include <iostream>
#include <vector>
#include <iomanip>


static const int left = -4;
static const int right = 3;

double main_function(double x)
{
	return pow(1 - x, 2) + exp(x);
}

// Функция, генерирующая случайное действительное число от -4 до 3
double random_x()
{
	return (double)(rand()) / RAND_MAX * 7 - 4;
}

class Experiment
{
	float P;
	float q;
	int N;
	double result_value;
	double find_result_value()
	{
		double min = 10000;
		double iter;
		for (int i = 0; i < N; i++)
		{
			iter = main_function(random_x());
			if (iter < min)
			{
				min = iter;
			}
		}
		return min;
	}
public:
	Experiment(double P_, double q_)
	{
		P = P_;
		q = q_;
		N = (log(1 - P)) / (log(1 - q)) + 1;
		result_value = find_result_value();
	};
	double get_N()
	{
		return N;
	}
	double get_result()
	{
		return result_value;
	}
};

template<bool T>
void get_table_func()
{
	std::cout << "+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+"
		<< std::endl;
	std::cout << "|  q\P    |   0.9  |  0.91  |  0.92  |  0.93  |  0.94  |  0.95  |  0.96  |  0.97  |  0.98  |  0.99  |"
		<< std::endl;
	std::cout << "+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+"
		<< std::endl;
	std::cout << std::setprecision(4);
	for (double j = 0.005; j <= 0.1; j += 0.005)
	{
		std::cout << "|";
		std::cout << std::setw(7) << std::right << j << " |";
		for (double i = 0.9; i < 1; i += 0.01)
		{
			Experiment ex(i, j);
			if (T == true)
			{
				int value = ex.get_N();
				std::cout << "  " << std::left << std::setw(6) << value << '|';
			}
			else
			{
				double value = ex.get_result();
				std::cout << "  " << std::left << std::setw(6) << value << '|';
			}
			if (abs(i - 0.99) < 0.00000000001) std::cout << std::endl;
		}
	}
	std::cout << "+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+"
		<< std::endl;
}

int main()
{
	get_table_func<true>();
	std::cout << std::endl;
	get_table_func<false>();
}
