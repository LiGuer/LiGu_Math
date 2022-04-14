#ifndef COMPLEX_OPERATE_H
#define COMPLEX_OPERATE_H

#include "Complex.h"

namespace ComplexLib {

	/*
	 * ��������
	 */

	 //ģ
	double abs(Complex& a) {
		return sqrt(a.real * a.real + a.imag * a.imag);
	}

	//����
	double arg(Complex& a) {
		return atan(a.imag / a.real);
	}

	//��
	Complex& operator-(Complex& a) {
		Complex ans;

		ans.real = -a.real;
		ans.imag = -a.imag;
		return ans;
	}

	//��
	Complex& operator+(Complex& a, Complex& b) {
		Complex ans;

		ans.real = a.real + b.real;
		ans.imag = a.imag + b.imag;
		return ans;
	}

	Complex& operator+(Complex& a, double b) {
		Complex ans;

		ans.real = a.real + b;
		ans.imag = a.imag;
		return ans;
	}

	Complex& operator+(double a, Complex& b) {
		Complex ans;

		ans.real = b.real + a;
		ans.imag = b.imag;
		return ans;
	}

	//��
	Complex& operator-(Complex& a, Complex& b) {
		Complex ans;

		ans.real = a.real - b.real;
		ans.imag = a.imag - b.imag;
		return ans;
	}

	Complex& operator-(Complex& a, double b) {
		Complex ans;

		ans.real = a.real + b;
		ans.imag = a.imag;
		return ans;
	}

	Complex& operator-(double a, Complex& b) {
		Complex ans;

		ans.real = a - b.real;
		ans.imag = -b.imag;
		return ans;
	}

	//��
	Complex& operator*(Complex& a, Complex b) {
		Complex ans;

		ans.real = a.real * b.real - a.imag * b.imag;
		ans.imag = a.real * b.imag + a.imag * b.real;
		return ans;
	}

	Complex& operator*(Complex& a, double b) {
		Complex ans;

		ans.real = a.real * b;
		ans.imag = a.imag * b;
		return ans;
	}

	Complex& operator*(double a, Complex& b) {
		Complex ans;

		ans.real = a * b.real;
		ans.imag = a * b.imag;
		return ans;
	}

	//��
	Complex& operator/(Complex& a, Complex& b) {
		Complex ans;

		double t = b.real * b.real + b.imag * b.imag;
		ans.real = (a.real * b.real + a.imag * b.imag) / t;
		ans.imag = (a.imag * b.real - a.real * b.imag) / t;
		return ans;
	}

	Complex& operator/(Complex& a, double b) {
		Complex ans;

		ans.real = a.real / b;
		ans.imag = a.imag / b;
		return ans;
	}

	Complex& operator/(double a, Complex& b) {
		Complex ans;

		double t = b.real * b.real + b.imag * b.imag;
		ans.real = a * b.real / t;
		ans.imag = -a * b.imag / t;
		return ans;
	}

	//����
	Complex& conj(Complex& a) {
		Complex ans;

		ans.real = a.real;
		ans.imag = -a.imag;
		return ans;
	}

	//��  de Moiver��ʽ
	Complex& Pow(Complex& a, double p) {
		Complex ans;

		double r = pow(abs(a), p), theta = p * arg(a);
		ans.real = r * cos(theta);
		ans.imag = r * sin(theta);
		return ans;
	}

	Complex& Pow(Complex& a, Complex& p) {
		Complex ans;

		return ans;
	}

}

#endif
