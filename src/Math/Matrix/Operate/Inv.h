#ifndef MATRIX_OPERATE_INV_H
#define MATRIX_OPERATE_INV_H
#include "../Mat.h"
#include "../Init.h"
#include "../Decompose.h"
#include "Basic.h"

namespace Matrix {

/*----------------ȡ�� [ inv x^{-1} ]----------------*/
	inline Mat<>& inv(Mat<>& ans, Mat<>& a) {
		if (a.rows != a.cols)
			exit(-1);

		Mat<> tmp(a.rows, a.cols);
		int n = a.rows;

		// LUP�ֽ�
		Mat<> L, U, P;
		LUP(a, U, L, P);

		//��ÿһ��
		Mat<> b(n), x(n);
		for (int k = 0; k < n; k++) {
			b.zero();
			b[k] = 1;

			// �����Է����� //solve y
			for (int i = 0; i < n; i++) {
				x[i] = b[P[i]];		//yi
				for (int j = 0; j < i; j++)
					x[i] -= x[j] * L(i, j);
			}

			//solve x
			for (int i = n - 1; i >= 0; i--) {
				for (int j = i + 1; j < n; j++)
					x[i] -= x[j] * U(i, j);
				x[i] /= U(i, i);
			}

			//�ϲ������
			for (int i = 0; i < a.rows; i++)
				tmp(i, k) = x[i];
		}
		return ans.eatMat(tmp);
	}
}

#endif