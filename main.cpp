#include "CubicSpline.h"

int main(int argc, char *argv[])
{
	std::vector<double> sx{0,1,2,3,4,5,6,7,8,9,10};
	std::vector<double> sy{2.7,6,5,6.5,-3.2,6.1,1.5,4.1,2.4,-1.2,0.3};

	CubicSpline cubic_spline;
	cubic_spline.init(sy);
	std::vector<double> rx,ry;
	
	for(double i=0.0;i<=sx.back();i+=cubic_spline.sampling_time){
		rx.push_back(i);
		ry.push_back(cubic_spline.calc(i));
	}

	FILE *gp = popen("gnuplot -persist\n", "w");
	fprintf(gp, "set xlabel \"x\"\n");
	fprintf(gp, "set ylabel \"y\"\n");
	fprintf(gp, "plot '-' with points lt 7, '-' with lines lw 2\n");
	for(size_t i=0;i<sx.size();i++) fprintf(gp, "%f\t%f\n", sx[i], sy[i]); fprintf(gp,"e\n");
	for(size_t i=0;i<rx.size();i++) fprintf(gp, "%f\t%f\n", rx[i], ry[i]); fprintf(gp,"e\n");
	fprintf(gp, "exit\n");
	pclose(gp);
}
