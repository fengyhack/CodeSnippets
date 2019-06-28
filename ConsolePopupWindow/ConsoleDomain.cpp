#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

// ����һ���Զ���Ĵ���
// �����Դ������ڵľ��(HWND)
HWND CreateMyWindow(HINSTANCE hInst, LPCSTR lpszName, LPCSTR lpszTitle, DWORD dwStyle, int left,int top,int width, int height)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance = hInst;
	wc.lpszClassName = lpszName;  // ��������, �Դ˹���, �൱��ȡ��һ������
	wc.style = CS_HREDRAW | CS_VREDRAW; // ˮƽ/��ֱ�����仯ʱ �������ػ�
	wc.hCursor = LoadCursor(hInst, IDC_ARROW); // ���
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 255)); // ���ڱ�����ɫ(��ɫ��ˢ)
	wc.lpfnWndProc = MyWindowProc; // ��Ϣ��������(������ΪĬ��,Ҳ�����Զ���һ��)

	// �����˴��ڹ��̺���(��������'��Ϣ��������')��
	// ʹ������ഴ���Ĵ��� ��Ӧ���¼� ��������������д���
	// ��Ϊʾ�� ������ʱʹ��Ĭ�ϵ�DefWindowProc
	// ��ʵ��Ӧ���и�����Ҫ�������ж���

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(lpszName, lpszTitle, dwStyle, left, top, width, height, NULL, NULL, hInst, NULL);

	return hWnd;
}

// ���ô��ڵĲ���,ע�������(RegisterClass), Ȼ��Ϳ�ʹ�������������ʵ����
// �������ڲ���ʾ����, Ϊ��ˢ�´������� ��Ҫ�¼�����/��Ϣѭ��
// ��Ϣѭ��: ĳ���¼��������ж�Ӧ����, �յ�'�ر�'��'�˳�'��Ϣʱ�رղ�����
int main(void)
{
	cout << "�����봰�ڱ���:";
	string strTitle;
	getline(cin, strTitle);
	cout << "�����봰�ڿ�� �߶�:";
	int width, height;
	cin >> width >> height;
	cin.get(); // ���ԡ����س���

	HINSTANCE hInst = (HINSTANCE)0xABADFACE;  // A Bad Face
	LPCSTR lpszName = "CustomizedWindow";  // �����������, ע��֮��ſ���ʹ��
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	HWND hWnd = CreateMyWindow(hInst, lpszName, strTitle.c_str(), dwStyle, 100, 100, width, height);
	cout << "����\'" << lpszName << "\'�Ѵ���" << endl;

	cout << "��ʾ�����´���" << endl;
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	cout << "Ҫ�رմ��ڣ��밴�س���";
	cin.get();  // �ȴ�����س�

	cout << "����\'" << lpszName << "\'�ѹر�." << endl;

	UnregisterClass(lpszName, hInst); // ע�� 

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