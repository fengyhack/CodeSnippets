/*
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <time.h>
#pragma comment(lib,"opencv_core249.lib")
#pragma comment(lib,"opencv_highgui249.lib")
using namespace cv;

#define POINT_NUM 100
#define WIDTH 1000
#define HEIGHT 750
#define ZERO 1e-12

inline float DIS(CvPoint a, CvPoint b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline int SGN(float x)
{
	return fabs(x) < ZERO ? 0 : (x > 0 ? 1 : -1);
}

inline float CROSS(CvPoint a, CvPoint b, CvPoint c)
{
	return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)); //叉积，用来判断旋转方向
}

inline bool CMP(CvPoint a, CvPoint b)
{
	return (a.x < b.x || SGN(a.x - b.x) == 0 && a.y < b.y); //坐标的比较
}

inline float RAND()
{
	return (rand() % 100000 / 100000.0f);//产生0-1之间的浮点数
}

CvPoint p[POINT_NUM];
CvPoint* hull_p = new CvPoint[POINT_NUM];//用来储存凸包上的点
int hull_size = 0;
IplImage* img;
//下面简单实现了栈操作
inline void push(CvPoint* S, CvPoint pt)
{
	S[hull_size++] = pt;
}
inline CvPoint pop(CvPoint* S)
{
	return S[--hull_size];
}

inline void swap(int x, int y)
{
	CvPoint pt = p[x];
	p[x] = p[y];
	p[y] = pt;
}

inline bool compare(CvPoint a, CvPoint b, CvPoint c)
{
	int tmp = SGN(CROSS(a, b, c));
	if (tmp != 0)
		return tmp > 0;
	else//如果两点共线的话，就需要比较远近了
		return DIS(a, b) < DIS(a, b);
}
//快排，极角的排序
void sort(int l, int r)
{
	CvPoint tmp = p[(l + r) / 2];
	int i = l;
	int j = r;
	do
	{
		while (compare(p[0], p[i], tmp))i++;
		while (compare(p[0], tmp, p[j]))j--;
		if (i <= j)
		{
			swap(i, j);
			i++;
			j--;
		}
	} while (i <= j);
	if (i < r)sort(i, r);
	if (j > l)sort(l, j);
}

void draw_hull()
{
	int min = -1;
	for (int j = 0; j < POINT_NUM; j++)//找出x坐标最小的，作为起始点
	{
		if (min == -1 || CMP(p[j], p[min]))
			min = j;
	}
	if (min != 0)
		swap(0, min);

	sort(1, POINT_NUM - 1);//其他点排序

	push(hull_p, p[0]);
	push(hull_p, p[1]);
	push(hull_p, p[2]);
	for (int i = 3; i < POINT_NUM; i++)
	{
		while (CROSS(hull_p[hull_size - 2], hull_p[hull_size - 1], p[i]) < 0)//非左转
		{
			pop(hull_p);
			cvLine(img, hull_p[hull_size - 1], p[i], cvScalar(i / hull_size * 255, 0, 255));//为了看清运行过程而加的
			cvShowImage("Image", img);
			cvWaitKey(500);
		}
		cvLine(img, hull_p[hull_size - 1], p[i], cvScalar(255, 0, 255));
		push(hull_p, p[i]);
	}

	cvPolyLine(img, &hull_p, &hull_size, 1, 1, cvScalar(0, 0, 255), 2);//最终画出凸包
}

void show_outcome()
{
	cvSet(img, cvScalar(255, 255, 255));
	CvScalar color = cvScalar(0, 0, 0);
	for (int i = 0; i < POINT_NUM; i++)//画出每个点，十字
	{
		int x = p[i].x;
		int y = p[i].y;
		cvLine(img, cvPoint(x - 5, y), cvPoint(x + 5, y), color, 2);
		cvLine(img, cvPoint(x, y - 5), cvPoint(x, y + 5), color, 2);
	}
	draw_hull();
	cvShowImage("Image", img);
	cvWaitKey(0);
}


int main()
{
	img = cvCreateImage(cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);

	srand((unsigned)time(NULL));
	double phase = RAND() * CV_PI * 2.0;
	for (int i = 0; i < POINT_NUM / 2; i++) 
	{
		double r = RAND() * WIDTH / 2.0;
		double theta = RAND() * 1.5 * CV_PI + phase;
		p[i] = cvPoint(WIDTH / 4 + r * cos(theta), HEIGHT / 2 + 2 * r * sin(theta));//椭圆
	}
	phase = RAND() * CV_PI * 2.0;
	for (int i = 0; i < POINT_NUM / 2; i++) 
	{
		double r = RAND() * WIDTH / 2.0;
		double theta = RAND() * 1.5 * CV_PI + phase;
		p[i + POINT_NUM / 2] = cvPoint(WIDTH / 4 * 3 + r * cos(theta), HEIGHT / 2 + r * sin(theta));//圆
	}

	show_outcome();
	delete[] hull_p;
	return 0;
}
*/
//QuickHull

#include <iostream>
#include <math.h>
#define maxn 100000
#define zero 1e-12
#define sgn(x) (fabs(x)<zero?0:(x>0?1:-1))
#define cross(a,b,c) ((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))
#define cmp(a,b) (a.x<b.x || sgn(a.x-b.x)==0 && a.y<b.y)

#pragma warning(disable:4996)

using namespace std;
struct point
{
	double x, y;
};

point p[maxn];
double s[maxn];

void hull(int l, int r, point a, point b)
{
	printf("Hull...\n");
	int x = l, i = l - 1, j = r + 1, k;
	for (k = l; k <= r; k++)
	{
		double temp = sgn(s[x] - s[k]);
		if (temp < 0 || temp == 0 && cmp(p[x], p[k]))
		{
			x = k;
		}
	}
	point y = p[x];
	for (k = l; k <= r; k++)
	{
		s[++i] = cross(p[k], a, y);
		if (sgn(s[i]) > 0)
		{
			swap(p[i], p[k]);
		}
		else
		{
			i--;
		}
	}
	for (k = r; k >= l; k--)
	{
		s[--j] = cross(p[k], y, b);
		if (sgn(s[j]) > 0)
		{
			swap(p[j], p[k]);
		}
		else
		{
			j++;
		}
	}
	if (l <= i)
	{
		hull(l, i, a, y);
	}
	printf("%3.0f %3.0f\n", y.x, y.y);
	if (j <= r)
	{
		hull(j, r, y, b);
	}
}

int main(void)
{
	int i, x, y, n = 500, k = 0;
	FILE* dat = fopen("data.txt", "w");
	fprintf(dat, "%d\n", n);
	for (i = 0; i < n; ++i)
	{
		x = rand() % 300 - 100;
		y = rand() % 200 - 100;
		fprintf(dat, "%3d %3d\n", x, y);
		p[i].x = x;
		p[i].y = y;
		if (k == 0 || cmp(p[i], p[k])) k= i;
	}
	fclose(dat);
	swap(p[0], p[k]);
	printf("%3.0f %3.0f\n", p[0].x, p[0].y);
	hull(2, n, p[0], p[0]);

	printf("press ENTER to continue...");
	getchar();
	return 0;
}