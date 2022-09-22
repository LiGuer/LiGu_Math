#ifndef FUNCTION_PLOYNOMIAL_FUNCTION_H
#define FUNCTION_PLOYNOMIAL_FUNCTION_H

#include <stdlib.h>
#include <float.h>
#include "../Matrix/Matrix.h"

using namespace Matrix;

namespace Function {

/* ------------------------------------------------
*
*		����ʽ����
*
** ------------------------------------------------*/
	/*
	 *	����ʽ����
	 */
	// һԪ
	double PolynomialFunction(double x, Mat<>& a) {
		int f = 0;

		for (int i = 0; i < a.rows; i++) {
			f += a(i) * pow(x, 0);
		}
		return f;
	}

	// ��Ԫ
	double PolynomialFunction(Mat<>& x, Tensor<>& a) {

	}

	/*
	 *	���Ժ���
	 *	f = a' x + f
	 */
	// һԪ
	double LinearFunction(double x, double a, double b) {
		return a * x + b;
	}

	// ��Ԫ
	double LinearFunction(double x, Mat<>& a, double b) {
		return dot(a, x) + b;
	}

	double LinearFunction(double x, Mat<>& a) {
		if (a.rows == x.rows + 1) {
			Mat<> x_(a.rows);
			x_(a.rows - 1) = 1;
			memcpy(x_.data, x.data, sizeof(double) * x.rows);

			return dot(a, x_);
		}
		else if (A.rows == x.rows) {
			return dot(a, x);
		}
		return DBL_MAX;
	}

	/*
	 *	���κ���
	 *	f = x' A x + b' x + c
	 */
	// һԪ
	double QuadraticFunction(double x, double a, double b, double c) {
		return a * x * x + b * x + c;
	}

	// ��Ԫ
	double QuadraticFunction(Mat<>& x, Mat<>& A, Mat<>& b, double c) {
		Mat<> tmp;

		return dot(x, mul(tmp, A, x)) + dot(b, x) + c;
	}

	double QuadraticFunction(Mat<>& x, Mat<>& A) {
		if (A.rows == x.rows + 1) {
			Mat<> x_(A.rows), tmp;
			x_(A.rows - 1) = 1;
			memcpy(x_.data, x.data, sizeof(double) * x.rows);

			return dot(x_, mul(tmp, A, x_));
		}
		else if(A.rows == x.rows) {
			Mat<> tmp;

			return dot(x, mul(tmp, A, x));
		}
		return DBL_MAX;
	}

	/*
	 *	�Ĵκ���
	 */
	// һԪ
	double QuarticFunction(double x, double a, double b, double c, double d, double e) {
		return a * pow(x, 4) + b * pow(x, 3) + c * pow(x, 2) + d * x + e;
	}

	// ��Ԫ
	double QuarticFunction(Mat<>& x, Tensor<>& a, Tensor<>& b, Mat<>& c, Mat<>& d, double e) {

		return 0;
	}

}

#endif