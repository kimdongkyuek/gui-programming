// ==========================================================================
//  v6 - 원으로 변경 및 테두리 색 지정 (펜)
// --------------------------------------------------------------------------
//  [이 단계에서 하는 일]
//    사각형을 원으로 바꾸고, 테두리를 파란색 굵기 2로 지정합니다.
//    브러시(안쪽)와 펜(테두리)은 서로 다른 물건이라는 걸 배웁니다.
//
//  [새로 나온 것]
//    HPEN                          : 도형의 테두리(선)를 그리는 펜
//    CreatePen(PS_SOLID, 2, RGB(...)) : 실선, 굵기 2, 지정한 색의 펜
//    Ellipse(hdc, l, t, r, b)      : 사각형 대신 그 사각형에 딱 맞는 타원을 그림
//      -> 가로세로가 같으면 원이 됩니다. 인자는 Rectangle 과 똑같습니다.
//    펜도 브러시와 완전히 같은 4단계 규칙(만들기-끼우기-되돌리기-지우기)을 따릅니다.
//    되돌릴 때는 끼운 순서의 반대로 하는 습관을 들이세요.
//
//  [실행하면]
//    클릭하면 파란 테두리에 노란 속을 가진 원이 그려집니다.
//    
//    ★★ 여기서 강의노트가 말하는 "문제점"이 나옵니다 ★★
//       창을 다른 창으로 가렸다 열거나, 화면 밖으로 내렸다 올리거나,
//       창 크기를 바꾸면 그려 둔 원이 전부 지워집니다.
//       원인: 화면을 다시 그리는 일은 WM_PAINT 담당인데,
//            우리는 WM_LBUTTONDOWN 에서 그려 놓고 아무 기록도 남기지 않았습니다.
//            Windows 는 우리가 뭘 그렸는지 모르므로 복원해 줄 수가 없습니다.
//       해결: v7 로 진행합니다.
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
            int x, y;
            x = LOWORD(lParam);
            y = HIWORD(lParam);

            HDC hdc = GetDC(hWnd);

            // 안쪽을 칠할 브러시 (노랑)
            HBRUSH yellow, oldBrush;
            yellow = CreateSolidBrush(RGB(255, 255, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, yellow);

            // 테두리를 그릴 펜 (파랑, 실선, 굵기 2)
            HPEN blue, oldPen;
            blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            oldPen = (HPEN)SelectObject(hdc, blue);

            // Rectangle -> Ellipse 로만 바꾸면 원이 됩니다. 인자는 동일!
            Ellipse(hdc, x - 30, y - 30, x + 30, y + 30);

            // 끼운 순서의 반대로 되돌리고 지웁니다.
            SelectObject(hdc, oldPen);
            DeleteObject(blue);

            SelectObject(hdc, oldBrush);
            DeleteObject(yellow);
            ReleaseDC(hWnd, hdc);
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
