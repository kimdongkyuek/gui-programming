// ==========================================================================
//  v3 - 마우스 클릭하면 사각형 출력
// --------------------------------------------------------------------------
//  [이 단계에서 하는 일]
//    알림창 대신, 클릭하면 창에 사각형을 직접 그립니다.
//    WM_PAINT 가 아닌 곳에서 그리려면 도화지를 따로 빌려 와야 한다는 걸 배웁니다.
//
//  [새로 나온 것]
//    GetDC(hWnd)          : WM_PAINT 밖에서 도화지를 빌려 오는 함수
//    ReleaseDC(hWnd, hdc) : 다 쓴 도화지를 돌려주는 함수 (안 돌려주면 자원 누수!)
//      BeginPaint/EndPaint 는 WM_PAINT 안에서만,
//      GetDC/ReleaseDC 는 그 밖에서 쓴다고 외워 두면 됩니다.
//
//  [실행하면]
//    클릭하면 (20,20)-(300,300) 위치에 큰 사각형이 나타납니다.
//    항상 같은 자리에 그려집니다. (아직 마우스 좌표를 안 쓰고 있으니까)
//    중요! 창을 최소화했다 열면 이 사각형은 사라집니다. -> v6 문제점으로 이어집니다.
//
//  [바뀐 곳] WM_LBUTTONDOWN
// ==========================================================================
// W02Win32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "W02Win32.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_W02WIN32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_W02WIN32));

    MSG msg;

    // 기본 메시지 루프입니다:
    //   [설명] Windows 프로그램의 심장. 하는 일은 딱 세 가지가 반복될 뿐입니다.
    //     GetMessage    : 이 프로그램에게 온 메시지(클릭, 키 입력, 다시 그려라 ...)를 하나 꺼냄
    //     TranslateMsg  : 키보드 입력을 문자 메시지로 변환
    //     DispatchMsg   : 꺼낸 메시지를 WndProc 에게 배달
    //   즉 내가 WndProc 를 직접 부르는 게 아니라, 이 루프가 대신 불러 줍니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
//  [설명] "이런 모양/성격의 창을 만들 거야" 하고 Windows에 설계도를 등록하는 함수입니다.
//         여기서 제일 중요한 줄은 wcex.lpfnWndProc = WndProc; 입니다.
//         "이 창에 무슨 일이 생기면 WndProc 함수를 불러 줘"라고 알려 주는 곳입니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;                  // <- 메시지를 처리할 함수 지정
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_W02WIN32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // 배경을 칠할 브러시 (창을 지울 때 사용)
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_W02WIN32);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   [설명] 위에서 등록한 설계도(szWindowClass)로 실제 창을 하나 만들어서(CreateWindowW)
//          화면에 보여 줍니다(ShowWindow). 설계도 등록과 창 만들기는 다른 일입니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  [설명] 이 과목의 핵심 함수입니다. 창에 무슨 일이 생길 때마다 Windows가 이 함수를 부릅니다.
//         message  : 무슨 일이 생겼는지 (WM_PAINT = 다시 그려라, WM_LBUTTONDOWN = 왼쪽 클릭 ...)
//         wParam   : 그 일에 딸린 부가 정보 1
//         lParam   : 그 일에 딸린 부가 정보 2 (마우스 메시지에서는 클릭한 좌표가 들어옴)
//         내가 처리하지 않은 메시지는 마지막 default 에서 DefWindowProc 이 알아서 처리합니다.
//         (창 이동, 크기 조절, 닫기 버튼 같은 기본 동작이 전부 여기서 나옵니다.)
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
    case WM_LBUTTONDOWN:
        {
            //MessageBox(hWnd, L"왼쪽 버튼 클릭", L"마우스", MB_OK);

            // GetDC : WM_PAINT 밖에서 그리려고 도화지를 빌려 옵니다.
            HDC hdc = GetDC(hWnd);
            Rectangle(hdc, 20, 20, 300, 300);
            ReleaseDC(hWnd, hdc);   // 반드시 돌려주기!
        }
        break;
    case WM_PAINT:
        {
            // [설명] "창을 다시 그려라"라는 메시지. 창이 처음 열릴 때, 다른 창에 가려졌다
            //        나타날 때, 크기가 바뀔 때 등 Windows가 필요하다고 판단하면 보냅니다.
            PAINTSTRUCT ps;

            // BeginPaint : 그림을 그릴 도화지(DC)를 받아 옵니다. 반드시 EndPaint 와 짝!
            //   HDC = Handle to Device Context = "어디에 그릴지"를 가리키는 번호표
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 그리기 코드를 추가합니다...

            // Rectangle(도화지, 왼쪽, 위, 오른쪽, 아래)  -> 화면 좌상단이 (0,0), 아래로 갈수록 y 증가
            Rectangle(hdc, 10, 10, 100, 100);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        // [설명] 창이 파괴될 때 옵니다. PostQuitMessage 를 부르면 위의 GetMessage 가 0을 돌려주고,
        //        메시지 루프가 끝나면서 프로그램이 종료됩니다. 이 줄이 없으면 창은 사라져도
        //        프로그램은 계속 살아 있게 됩니다.
        PostQuitMessage(0);
        break;
    default:
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
