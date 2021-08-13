#include <stdio.h>

double somme_tableau(double t[], int n)
{
	float s = 0.0;
	for (int i = 0; i < n; i++) {
		s += t[i];
	}
	return s;
}

double moyenne_tableau(double t[], int n)
{
	return somme_tableau(t, n) / n;
}

int main()
{
	printf("Tests somme:\n");
    double t1[] = {20.5, -3.0 , 4.5}; 
    double r1 = somme_tableau(t1, 3);
	printf("r1 = %f\n", r1);

    double t2[] = {13.0, 7.5, 18, 12, 13.5, 9 };
	double r2 = somme_tableau(t2, 6);
	printf("r2 = %f\n", r2);

	double m1 = moyenne_tableau(t1, 3);
	printf("m1 = %f\n", m1);
	
	return 0;
}

