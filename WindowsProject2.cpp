// WindowsProject2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject2.h"
#include <wingdi.h>
#include <math.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
// wchar_t 타입 변수 배열 100개
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
// wchar_t 타입 변수 배열 100개
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
// ATOM = unsigned short
ATOM                MyRegisterClass(HINSTANCE hInstance);
// BOOL = int
BOOL                InitInstance(HINSTANCE, int);
// LRESULT = __int64 
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// INT_PTR = long long
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 메인 함수 ( SAL )
// 실행 된 프로세스의 시작 주소
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 참조 되지 않는 변수 입니다
    // 이 코드는 아무 의미도 없다. UNPEFERENCED_PARAMERTER (변수) = 변수
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    // 메세지 구조체
    MSG msg;

    SetTimer(g_hWnd, 10, 0, nullptr);

    // 발생한 윈도우의 정보까지도 msg구조체에 저장되어 있다
    // 하나의 프로세스가 여러개의 윈도우(창)을 보유하고 있을 수도 있다
    // 프로시저(처리기) 함수라고 하는데, 각자 윈도우(창)들은 자기한테 어떤 일이 발생했을 때 처리해주는 함수를 같이 들고 있다
    //msg.hwnd;

    // 기본 메시지 루프입니다:
    // 해당 프로세스가 포커스를 받고 있을 때 메세지를 받고 있다
    // GetMassge : 해당 프로그램 쪽으로 발생한 메세지들을 메세지 큐에 받아놓고 꺼내놓는 것이다. 
    // 메세지큐에서 메세지 확인할때까지 대기
    // 해당 GetMassge는 Queue 메모리 형태로 되어있기 때문에 가장 처음 받은 것부터 처리한다
    // GetMassge의 정보를 메세지 구조체에 채우기 위해서 &msg 주소를 보내준다
    // msg.massage == WM_QUIT 일때만 false를 반환 -> 프로그램 종료
    // window가 destory -> msg.massage = WM_QUIT -> 프로그램 종료
    while (GetMessage(&msg, nullptr, 0, 0))
	{

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg));
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    KillTimer(g_hWnd, 10);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
// 윈도우의 정보 데이터들을 이야기 한다
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // struct 구조체
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // 프로시저
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    // 해당 키 값에 데이터 정보를 세팅한다
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 윈도우의 정보를 szWindowClass의 키값으로 찾는다
   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

#include <vector>

using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos = { 500, 300 };
    POINT g_ptObjScale = { 100, 100 };
};

vector<tObjInfo> g_vecInfo;

POINT g_ptLT;       // 좌 상단
POINT g_ptRB;       // 우 하단

bool bLbtnDown = false;

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  // 무효화 영역(Invalidate)이 발생한 경우
        {
            PAINTSTRUCT ps;
           
            // Device Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context (그리기)
            // DC의 목적지는 hWnd
            // DC의 펜은 기본펜(black)
            // DC의 브러쉬는 기본 브러쉬(White)

            // 직접 펜을 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // 기본 펜 ID 값을 받아 둠
            HPEN hDefalutPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefalutBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            // 변경된 펜과 브러쉬로 사각형 그림
            if (bLbtnDown)
            {
                Rectangle(hdc
                    , g_ptLT.x, g_ptLT.y
                    , g_ptRB.x, g_ptRB.y);
            }

            // 추가된 사각형들도 그려준다
            for (int i = 0; i < g_vecInfo.size(); i++)
            {
                Rectangle(hdc
                    , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
                    , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
                    , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
                    , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }

            // DC의 펜을 원래 펜으로 되돌림
            SelectObject(hdc, hDefalutPen);
            SelectObject(hdc, hDefalutBrush);

            // 다 쓴 Red펜 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);
            
            // 윈도우 핸들
            // HDC ?
            
            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_DOWN:
            //g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            //g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            //g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        }
    }
        break;

        // 마우스 클릭을 했을 때, lParam에서 마우스의 좌표가 들어간다
        // lParam은 'long' 타입 4바이트 자료형이다. 
        // 마우스 좌표는 2바이트 씩 나눠서 저장한다
    case WM_LBUTTONDOWN:
    {
        g_ptLT.x = LOWORD(lParam); // 비트 연산자로 처음부터 16비트까지 데이터를 잡아준다
        g_ptLT.y = HIWORD(lParam); // 비트 연산자로 16비트부터 32비트까지 데이터를 잡아준다
        bLbtnDown = true;
    }
        break;

    case WM_MOUSEMOVE:
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_TIMER:

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        // 기본 프로시저
        // 키 입력 관련되서는 아무것도 안해준다
        // 내가 직접 관리하지 않는 모든 메세지는 여기서 처리해준다
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

