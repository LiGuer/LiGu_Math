# LiGu_AlgorithmLib
LiGu's Basic Algorithm Library.  
* <Mat.h>                   矩阵类  
* <ComputationalGeometry.h> 计算几何类  
* <NeuralNetworks.h>        神经网络类
* <BasicMachineLearning.h>  基础机器学习类
*   
* <Tensor.h>                张量类  
* <GraphTheory.h>           图论类 
* <BasicAlgorithm.h>        基础算法类  
* <list.h>                  链表类  
* <NumberTheory.h>          数论类
* <PartialDifferentialEquation.h>   偏微分方程类  
* <rb_tree.h>               红黑树  
* <LSTM.h>                  长短期记忆网络  

## <Mat.h> 矩阵类  
```
/**************** 核心数据 ****************/
T* data = NULL;
int rows = 0, cols = 0;
/**************** 基础函数 ****************/
Mat();                                      //构造析构函数  
Mat(const int _rows, const int _cols);  
Mat(const Mat& a);  
~Mat();
void clean();                               //清零  
void error();                               //报错  
void eatMat(Mat& a);                        //
/**************** 基础矩阵 ****************/  
[1] 零元 zero		[2] 单位元 E		[3] 随机元 rands  
/**************** 基础运算 ****************/  
T& operator[](int i)                        // "[]"取元素  
T& operator()(int i, int j)                 // "()"取元素  
T& operator()(int i) 
T max()                                     // max/min 
T max(int& index) 
T min()  
T min(int& index)  
bool operator==(const Mat& b);              //判断相等 [ == ]
Mat& operator=(const Mat& a)                //赋矩阵 [ = ]  //不能赋值自己
Mat& add(Mat& a, Mat& b)                    //加法 [ add ]
Mat& mult(const Mat& a, const Mat& b)       //乘法 [ mult ]
Mat& mult(const double a, const Mat& b)     //数乘 [ mult ]
Mat& dot(const Mat& a, const Mat& b)        //点乘 [ dot ]
Mat& crossProduct(Mat& a, Mat& b)           //叉乘 [ crossProduct ]
Mat& negative(Mat& ans)                     //负 [ negative ]
Mat& transposi(Mat& ans)                    //转置 [ trans ]
void sum(int dim, Mat& ans)                 //元素求和 [ sum ]
T norm()                                    //范数 [ norm ]
T comi(int i0, int j0)                      //余子式 [ comi ]
Mat& inv(Mat& ans)                          //取逆 [ inv ]
T abs()                                     //行列式 [ abs ]
Mat& adjugate(Mat& ans)                     //伴随矩阵 [ adjugate ]
void eig(T esp, Mat& eigvec, Mat& eigvalue) //特征值特征向量 [ eig ]
Mat& solveEquations(Mat& b, Mat& x)         //解方程组 [ solveEquations ]
void LUPdecomposition(Mat& U, Mat& L, Mat& P) //LUP分解 [ LUPdecomposition ]
Mat& normalization()                        //归一化 [ normalization ]
/**************** 特殊操作 ****************/  
Mat& horizStack(Mat& a, Mat& b)             //水平向拼接 [ horizStack ]
void swap(Mat& a)                           //交换数据 [ swap ]
Mat& getCol(int _col, Mat& a)               //读/写一列 [ getCol/setCol ]
```

## <ComputationalGeometry.h> 计算几何类
```
/*----------------[ 2D 二维 ]----------------*/
void ThreePointsToCircle(Mat<double> Points[], Mat<double>& center, double& R); //平面三点确定圆方程
bool isInCircle(Mat<double> Points[]);                                          //判断四点共圆
Mat<double>* ConvexHull(Mat<double> point[], int n, int& ansPointNum);          //凸包
Mat<double>* Delaunay(Mat<double> point[], int n, int& TrianglesNum);           //Delaunay三角剖分
/*----------------[ 3D 三维 ]----------------*/
Mat<double>* getSphereFibonacciPoint(int& n);                                   //球面均匀点分布
```

## <NeuralNetworks.h> 神经网络类
```
/*----------------[ 核心类 ]----------------*/
class NeuralLayer(int inputSize, int outputSize)    //神经网络层
class ConvLayer(int _inChannelNum, int _outChannelNum,int kernelSize,int _padding,int _stride)  //卷积层
class PoolLayer(int _kernelSize, int _padding, int _stride, int _poolType)      //下采样层
/*----------------[ 经典结构 ]----------------*/
class BackPropagation_NeuralNetworks()              //反向传播神经网络 : 1986.Rumelhart,McClelland
class LeNet_NeuralNetworks()                        //LeNet卷积神经网络 : 1998.Yann LeCun
class Inception()                                   //Inception模块: 2014.Google
```