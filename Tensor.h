/*
Copyright 2020,2021 LiGuer. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
	http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
[Reference]
[1]Introduction Algorithms.THOMAS H.CORMEN,CHARLES E.LEISERSON,RONALD L.RIVEST,CLIFFORD STEIN
==============================================================================*/
#ifndef TENSOR_H
#define TENSOR_H
#include "Matrix/Mat.h"
template<class T = double>
class Tensor {
public:
/******************************************************************************
*                    ��������
*	[ע]: Data�ѵ�����: ��ά����
******************************************************************************/
	T* data = NULL;	
	Mat<int> dim;										//{x, y, z, ...}
/******************************************************************************
*                    ����
******************************************************************************/
	/*---------------- ����/�������� ----------------*/
	Tensor() { ; }
	Tensor(int dimNum, int* dimLength) { zero(dimNum, dimLength); }
	Tensor(int x0, int y0, int z0)     { zero(x0, y0, z0); }
	Tensor(Tensor& a) { *this = a; }
	~Tensor() { delete data; }
	/*---------------- �������� ----------------*/
	void error() { exit(-1); }
	inline int size() { return dim.product(); }
	inline int size(int _dim) { 
		if (_dim == 1) return dim[0];
		if (_dim == 2) return dim[0] * dim[1];
		if (_dim == 3) return dim[0] * dim[1] * dim[2];
		int ans = 1; for(int i = 0; i < _dim; i++) ans *= dim[i]; return ans; 
	}
	/*---------------- ����ռ� ----------------*/
	Tensor& alloc(int dimNum, int* dimLength) {
		if (dim.rows != dimNum || memcmp(dim.data, dimLength, dimNum * sizeof(int)) != 0) {
			dim.alloc(dimNum) = (dimLength);
			if (data != NULL) delete data; data = (T*)malloc(size() * sizeof(T));
		} return *this;
	}
	Tensor& alloc(Mat<int> _dim)					{ alloc(_dim.rows, _dim.data);				 return *this; }
	Tensor& alloc(int x0)							{ int t[] = { x0 };				alloc(1, t); return *this; }
	Tensor& alloc(int x0, int y0)					{ int t[] = { x0, y0 };			alloc(2, t); return *this; }
	Tensor& alloc(int x0, int y0, int z0)			{ int t[] = { x0, y0, z0 };		alloc(3, t); return *this; }
	Tensor& alloc(int x0, int y0, int z0, int w0)	{ int t[] = { x0, y0, z0, w0 }; alloc(4, t); return *this; }
	/*---------------- ��Ԫ/���� ----------------*/
	Tensor& zero() { memset(data, 0, sizeof(T) * size()); return *this; }	//���� 
	Tensor& zero(int dimNum, int* dimLength)	{ alloc(dimNum, dimLength); zero(); return *this; }
	Tensor& zero(int x0, int y0, int z0)		{ alloc(x0, y0, z0);		zero(); return *this; }
	/*---------------- ���Ԫ ----------------*/
	Tensor& rands(T st, T ed) {	//[st,ed)
		for (int i = 0; i < size(); i++)
			data[i] = rand() / (double)RAND_MAX * (ed - st) + st;
		return *this;
	}
	Tensor& rands(int dimNum, int* dimLength, T st, T ed) { alloc(dimNum, dimLength); rands(st, ed); return *this; }
	/*---------------- "[]"ȡԪ�� ----------------
	*	[����]: { x, y, z, ...} = data[ x + y��X0 + z��X0��Y0 + ... ]
	*	[Data�ѵ�����]: ��x,һ�� => ��xy,һ���� => ��xyz,һ���� => ....
	**-------------------------------------------*/
	T& operator[](int i)				{ return data[i]; }
	T& operator()(int x)				{ return data[x]; }
	T& operator()(int x, int y)			{ return data[x + y * dim[0]]; }
	T& operator()(int x, int y, int z)	{ return data[x + y * dim[0] + z * dim[1] * dim[0]]; }
	T& operator()(int* dimIndex) {
		int index = 0, step = 1;
		for (int i = 0; i < dim.rows; i++) {
			index += step * dimIndex[i];
			step  *= dim[i];
		} return data[index];
	}
	T& operator()(std::initializer_list<T> list) {
		int index = 0, step = 1, i = 0;
		for (auto& item : list) {
			index += step * item;
			step  *= dim[i++];
		} return data[index];
	}
	inline int i2x(int i) { return i % dim[0]; }
	inline int i2y(int i) { return dim.rows == 2 ? i / dim[0]          : i %(dim[1] * dim[0])/ dim[0]; }
	inline int i2z(int i) { return dim.rows == 3 ? i /(dim[1] * dim[0]): i %(dim[2] * dim[1] * dim[0])/(dim[1] * dim[0]); }
	inline int xyz2i(int x, int y, int z) { return x + y * dim[0] + z * dim[1] * dim[0]; }
	/*----------------��ֵ [ = ]----------------*/ //���ܸ�ֵ�Լ�
	Tensor& operator=(Tensor& a) {
		if (a.data == NULL) error();
		alloc(a.dim);
		memcpy(data, a.data, size() * sizeof(T));
		return *this;
	}
	Tensor& eat(Tensor& a) {
		if (a.data == NULL) error();
		if (  data != NULL) delete data;
		data = a.data; a.data = NULL; dim.eatMat(a.dim);
		return *this;
	}
	/*----------------�ӷ� [ add + ]----------------*/
	Tensor& add(Tensor& a, Tensor& b) {
		if (!(a.dim == b.dim)) error();
		alloc(a.dim);
		for (int i = 0; i < b.size(); i++) data[i] = a[i] + b[i];
		return *this;
	}
	Tensor& operator+=(Tensor& a) {
		if (!(dim == a.dim)) error();
		for (int i = 0; i < size(); i++) data[i] += a[i];
		return *this;
	}
	/*----------------���� [ mul �� ]----------------*/
	Tensor& mul(const double a, Tensor& b) {
		alloc(b.dim);
		for (int i = 0; i < b.size(); i++) data[i] = a * b[i];
		return *this;
	}
	Tensor& operator*=(const double a) {
		for (int i = 0; i < size(); i++) data[i] *= a;
		return *this;
	}
	/*----------------���----------------*/
	Tensor& conv(Tensor& in, Tensor& kernel, int padding, int stride) {
		alloc(
			(in.dim[0] - kernel.dim[0] + 2 * padding) / stride + 1,
			(in.dim[1] - kernel.dim[1] + 2 * padding) / stride + 1,
			kernel.dim[2]
		);
		// for each element of out
		for (int i = 0; i < size(); i++)							// for each element of kernel
			for (int ky = 0; ky < kernel.dim[1]; ky++) 
				for (int kx = 0; kx < kernel.dim[0]; kx++) {			// get the corresponding element of in
					int xt = -padding + i2x(i) * stride + kx,
						yt = -padding + i2y(i) * stride + ky;
					if (xt < 0 || xt >= in.dim[0] || yt < 0 || yt >= in.dim[1]) continue;
					for (int z = 0; z < in.dim[2]; z++)
						data[i] += in(xt, yt, z) * kernel(kx, ky, i2z(i));
				}
	}
	/*----------------�ϲ� [ merge ]----------------
	*	�� dimIndex �����ͼ��ģ���ΪԪ�ؿ飬��������ڴ渴��
		�� dimIndex �����߼��ģ���Ϊ���ƴ���
	-----------------------------------------------*/
	Tensor& merge(Tensor* a[], const int N, int dimIndex) {
		// new memory
		int length = 0;
		for (int i = 0; i < N; i++) length += a[i]->dim[dimIndex];
		Mat<int> dimSize = a[0]->dim;
		dimSize[dimIndex] = length;
		Tensor ansTemp(dimSize.rows, dimSize.data);
		// merge
		int elementBlockSize = 1, copyTimes = 1;
		for (int i = 0; i < dimIndex; i++)    elementBlockSize *= dim[i];
		for (int i = dimIndex + 1; i < dim.rows; i++)copyTimes *= dim[i];
		int pos = 0;
		Mat<int> inputPosMem(N, 1);
		while (copyTimes--) {
			for (int i = 0; i < N; i++) {
				int t = elementBlockSize * a[i]->dim[dimIndex];
				memcpy((&data + pos), &(a[i]->data) + inputPosMem[i], t * sizeof(T));
				pos += t; inputPosMem[i] += t;
			}
		}
		eat(ansTemp); return *this;
	}
	/*----------------�������� []----------------*/
	template<typename F>
	Tensor& function(Tensor& x, F&& f) {
		alloc(x.dim);
		for (int i = 0; i < x.size(); i++) data[i] = f(x[i]);
		return *this;
	}
	template<typename F>
	Tensor& function(F&& f) {
		for (int i = 0; i <   size(); i++) data[i] = f(data[i]);
		return *this;
	}
};
#endif