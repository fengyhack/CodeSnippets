#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

// 创建一个自定义的窗口
// 返回以创建窗口的句柄(HWND)
HWND CreateMyWindow(HINSTANCE hInst, LPCSTR lpszName, LPCSTR lpszTitle, DWORD dwStyle, int left,int top,int width, int height)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance = hInst;
	wc.lpszClassName = lpszName;  // 窗口类名, 以此关联, 相当于取了一个名字
	wc.style = CS_HREDRAW | CS_VREDRAW; // 水平/垂直发生变化时 都进行重绘
	wc.hCursor = LoadCursor(hInst, IDC_ARROW); // 光标
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 255)); // 窗口背景颜色(蓝色画刷)
	wc.lpfnWndProc = MyWindowProc; // 消息处理例程(可以设为默认,也可以自定义一个)

	// 关联了窗口过程函数(即上述的'消息处理例程')后
	// 使用这个类创建的窗口 对应的事件 都由这个函数进行处理
	// 作为示例 我们暂时使用默认的DefWindowProc
	// 在实际应用中根据需要可以自行定义

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(lpszName, lpszTitle, dwStyle, left, top, width, height, NULL, NULL, hInst, NULL);

	return hWnd;
}

// 设置窗口的参数,注册这个类(RegisterClass), 然后就可使用这个类来创建实例了
// 创建窗口并显示窗口, 为了刷新窗口内容 需要事件驱动/消息循环
// 消息循环: 某个事件发生进行对应处理, 收到'关闭'或'退出'消息时关闭并结束
int main(void)
{
	cout << "请输入窗口标题:";
	string strTitle;
	getline(cin, strTitle);
	cout << "请输入窗口宽度 高度:";
	int width, height;
	cin >> width >> height;
	cin.get(); // ‘吃’掉回车符

	HINSTANCE hInst = (HINSTANCE)0xABADFACE;  // A Bad Face
	LPCSTR lpszName = "CustomizedWindow";  // 窗口类的名称, 注册之后才可以使用
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	HWND hWnd = CreateMyWindow(hInst, lpszName, strTitle.c_str(), dwStyle, 100, 100, width, height);
	cout << "窗口\'" << lpszName << "\'已创建" << endl;

	cout << "显示并更新窗口" << endl;
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	cout << "要关闭窗口，请按回车键";
	cin.get();  // 等待输入回车

	cout << "窗口\'" << lpszName << "\'已关闭." << endl;

	UnregisterClass(lpszName, hInst); // 注销 

	system("pause");
	return 0;
}

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0L;
	}
	else
	{
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
}