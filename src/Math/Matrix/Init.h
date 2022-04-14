#ifndef MATRIX_INIT_H
#define MATRIX_INIT_H
#include "Mat.h"
namespace Matrix {
/******************************************************************************
* 
*                    ����������
* 
******************************************************************************/

/*---------------- ��λԪ ----------------*/
inline Mat<>& E(Mat<>& a) {
	a.zero();
	for (int i = 0; i < a.rows; i++)
		a(i, i) = 1;
	return a;
}

/*---------------- ȫ1Ԫ ----------------*/
inline Mat<>& ones(Mat<>& a) {
	a.fill(1);
	return a;
}

/*---------------- ���Ԫ ----------------*/
inline Mat<>& rands(Mat<>& a, double st, double ed) {
	for (int i = 0; i < a.size(); i++)
		a(i) = rand() / double(RAND_MAX) * (ed - st) + st;	//[st,ed)
	return a;
}

/*---------------- ���Լ������ ----------------*/
inline Mat<>& linspace(Mat<>& a, double xs, double xe, int n = 100) {
	double dx = (xe - xs) / (n - 1);
	a.alloc(n);
	for (int i = 0; i < a.size(); i++)
		a(i) = xs + dx * i;
	a(a.size() - 1) = xe;
	return a;
}

/*---------------- ����ԽǾ��� ----------------*/
inline Mat<>& diag(Mat<>& a, Mat<>& b) {
	if (b.rows == b.cols) {
		a.alloc(a.rows);

		for (int i = 0; i < a.rows; i++)
			a(i) = b(i, i);
	}
	else if (b.rows == 1 || b.cols == 1) {
		int n = b.rows > b.cols ? b.rows : b.cols;
		a.alloc(n, n);

		for (int i = 0; i < n; i++)
			a(i, i) = b(i);
	}
	else
		exit(-1);
	return a;
}

}
#endif