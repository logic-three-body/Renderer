#include <GraphicsDevice.h>
#include <GraphicsLibrary.h>
#include "stdio.h"
class Texture
{
private:
	COLORREF img[2][2] = {
	{RGB(255,0,0),RGB(0,255,0)},
	{RGB(0,0,255),RGB(255,123,172)}
	};
	double width = 2, heigth = 2;
public:
	COLORREF texture2D(double u, double v)
	{
		int row = (int)(v * width);
		int column = (int)(u * width);
		row =_min(_max(0, row), (int)heigth -1);
		column =_min(_max(0, column), (int)width-1);
		return img[row][column];//因为u表示横轴，在我们这定义里面应该是最低维的数据，所以应该是img[v][u]表示纹素坐标
	}
};
Texture texture;

Point4 Persective(Point4& p, double n)
{
	auto pn = p.Normalize();//先将齐次坐标变成三维坐标
	return Point4(pn.X * n, pn.Y * n,  -1, pn.Z);//执行透视变换
}

COLORREF FS(std::vector<double>& values)
{
	return texture.texture2D(values[0], values[1]);
};
int main()
{
	GraphicsDevice gd(640, 480);
	GraphicsLibrary gl(gd);

	gl.clean_depth(1000);//先将深度值设置为一个较大的值

	Point4 a1(0, 0, 10, 1);
	Point4 b1(0, 480, 10, 1);
	Point4 c1(1280, 0, 100, 1);
	auto ta1 = Persective(a1, 9);
	auto tb1 = Persective(b1, 9);
	auto tc1 = Persective(c1, 9);
	ta1.ValueArray = { 0,0 };
	tb1.ValueArray = { 0,1 };
	tc1.ValueArray = { 1,0 };
	gl.ClipAndDraw(ta1, tb1, tc1, 2, 15, FS);//绘制第一个三角形


	Point4 a2(1280, 0, 100, 1);
	Point4 b2(0, 480, 10, 1);
	Point4 c2(1280, 480, 100, 1);
	auto ta2 = Persective(a2, 9);
	auto tb2 = Persective(b2, 9);
	auto tc2 = Persective(c2, 9);
	ta2.ValueArray = { 1,0 };
	tb2.ValueArray = { 0,1 };
	tc2.ValueArray = { 1,1 };
	gl.ClipAndDraw(ta2, tb2, tc2, 2, 15, FS);//绘制第二个三角形


	Point4 a3(0, 0, 55, 1);
	Point4 b3(0, 480, 55, 1);
	Point4 c3(1280, 0, 55, 1);
	auto ta3 = Persective(a3, 9);
	auto tb3 = Persective(b3, 9);
	auto tc3 = Persective(c3, 9);
	ta3.ValueArray = { 0,0 };
	tb3.ValueArray = { 0,1 };
	tc3.ValueArray = { 1,0 };
	gl.ClipAndDraw(ta3, tb3, tc3, 2, 15, FS);//绘制第三个三角形


	Point4 a4(1280, 480, 55, 1);
	Point4 b4(0, 480, 55, 1);
	Point4 c4(1280, 0, 55, 1);
	auto ta4 = Persective(a4, 9);
	auto tb4 = Persective(b4, 9);
	auto tc4 = Persective(c4, 9);
	ta4.ValueArray = { 1,1 };
	tb4.ValueArray = { 0,1 };
	tc4.ValueArray = { 1,0 };
	gl.ClipAndDraw(ta4, tb4, tc4, 2, 15, FS);//绘制第四个三角形

	getchar();
	return 0;
}