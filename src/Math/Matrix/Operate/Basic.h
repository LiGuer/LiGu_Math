#ifndef MATRIX_OPERATE_BASIC_H
#define MATRIX_OPERATE_BASIC_H
#include "../Mat.h"
#include "../Init.h"
namespace Matrix {
/******************************************************************************
* 
*                    ��������
* 
******************************************************************************/

	/*----------------�� [ negative - ]----------------*/
	inline Mat<>& negative(Mat<>& ans, Mat<>& a) {
		ans.alloc(a.rows, a.cols);
		for (int i = 0; i < a.size(); i++)
			ans[i] = -a[i];
		return ans;
	}

	inline Mat<>& operator-(Mat<>& a) {
		Mat<> ans;

		ans.alloc(a.rows, a.cols);
		for (int i = 0; i < a.size(); i++)
			ans[i] = -a[i];
		return ans;
	}

	/*----------------ת�� ----------------*/
	inline Mat<>& transpose(Mat<>& ans, Mat<>& a) {
		Mat<> ansTmp(a.cols, a.rows);

		for (int i = 0; i < a.rows; i++)
			for (int j = 0; j < a.cols; j++)
				ansTmp(j, i) = a(i, j);

		ans.eatMat(ansTmp);
		return ans;
	}

	/*----------------�ӷ� [ add + ]----------------*/
	inline Mat<>& add(Mat<>& ans, Mat<>& a, Mat<>& b) {
		if (a.rows != b.rows || a.cols != b.cols)
			exit(-1);

		ans.alloc(a.rows, a.cols);

		for (int i = 0; i < a.size(); i++)
			ans[i] = a[i] + b[i];
		return ans;
	}

	/*----------------���� [ sub - ]----------------*/
	inline Mat<>& sub(Mat<>& ans, Mat<>& a, Mat<>& b) {
		if (a.rows != b.rows || a.cols != b.cols)
			exit(-1);
		ans.alloc(a.rows, a.cols);

		for (int i = 0; i < a.size(); i++)
			ans[i] = a[i] - b[i];
		return ans;
	}

	/*----------------�˷� [ mul �� ]----------------*/
	inline Mat<>& mul(Mat<>& ans, Mat<>& a, Mat<>& b) {
		if (a.cols != b.rows)
			exit(-1);
		Mat<> ansTmp(a.rows, b.cols);

		for (int i = 0; i < a.rows; i++)
			for (int j = 0; j < b.cols; j++)
				for (int k = 0; k < a.cols; k++)
					ansTmp(i, j) += a(i, k) * b(k, j);

		ans.eatMat(ansTmp);
		return ans;
	}

	/*----------------���� [ mul �� ]----------------*/
	inline Mat<>& mul(Mat<>& ans, const double a, Mat<>& b) {
		ans.alloc(b.rows, b.cols);

		for (int i = 0; i < ans.size(); i++)
			ans[i] = a * b[i];
		return ans;
	}

	/*----------------Ԫ�س� [ elementMul �� ]----------------*/
	inline Mat<>& elementMul(Mat<>& ans, Mat<>& a, Mat<>& b) {
		if (a.rows != b.rows || a.cols != b.cols)
			exit(-1);
		ans.alloc(a.rows, a.cols);

		for (int i = 0; i < ans.size(); i++)
			ans[i] = a[i] * b[i];
		return ans;
	}

	/*----------------Ԫ�س� [ elementDiv / ]----------------*/
	inline Mat<>& elementDiv(Mat<>& ans, Mat<>& a, Mat<>& b) {
		if (a.rows != b.rows || a.cols != b.cols)
			exit(-1);
		ans.alloc(a.rows, a.cols);

		for (int i = 0; i < ans.size(); i++)
			ans[i] = a[i] / b[i];
		return ans;
	}

}
#endif