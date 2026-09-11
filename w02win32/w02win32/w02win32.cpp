// ==========================================================================
//  v9 - 좋은 구조 : 모델 분리 (model.h / model.cpp)
// --------------------------------------------------------------------------
//  [이 단계에서 하는 일]
//    원을 여러 개(최대 3개) 그릴 수 있게 확장합니다.
//    동시에 "데이터를 다루는 코드"와 "화면에 그리는 코드"를 파일로 분리합니다.
//      model.h / model.cpp : 점들을 저장하고 관리 (데이터 = 모델)
//      W02Win32.cpp        : 화면에 그리고 마우스를 받음 (화면 = 뷰)
//    이렇게 나누면 나중에 "원을 별로 바꾸기"는 W02Win32.cpp 만,
//    "100개까지 저장하기"는 model.cpp 만 고치면 됩니다.
//
//  [새로 나온 것]
//    POINT   : x, y 를 한 덩어리로 담는 Windows 기본 구조체 (p.x, p.y 로 사용)
//    AddPoint(p)      : 점 하나 추가
//    GetNumPoints()   : 저장된 점 개수
//    GetPoint(i)      : i 번째 점 꺼내기
//    DeleteLastPoint(): 마지막 점 지우기 (Undo 용. 도전 과제에서 사용)
//    MODEL_MAX_POINTS : 최대 저장 개수 (지금은 3)
//    WM_PAINT 안에서 for 문으로 저장된 점 전부를 다시 그립니다.
//
//  [실행하면]
//    클릭할 때마다 원이 하나씩 추가됩니다. 최대 3개까지.
//    창을 가렸다 열어도 원 3개가 모두 그대로 남아 있습니다.
//    
//    [도전 과제 - 강의노트]
//      · 마우스 오른쪽 버튼(WM_RBUTTONDOWN)을 누르면 Undo 되게 만들기
//        힌트: DeleteLastPoint() 를 부르고 InvalidateRect 를 부르면 됩니다.
//      · 버튼을 누른 채 움직이면(WM_MOUSEMOVE) 원이 계속 추가되게 만들기
//      · MODEL_MAX_POINTS 를 늘려 보기
//
//  [바뀐 곳] 파일 3개 (W02Win32.cpp + model.h + model.cpp)
// ==========================================================================
// W02Win32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "W02Win32.h"

#include "model.h"    // 점 저장/조회 함수들 (모델)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

//static int x = -100, y = 100;   // 모델로 옮겨서 더 이상 필요 없습니다.

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
            // [설명] 이제 x, y 를 따로 쓰지 않고 POINT 구조체 하나로 묶어서 모델에 넘깁니다.
            POINT p;
            p.x = LOWORD(lParam);
            p.y = HIWORD(lParam);

            AddPoint(p);                    // 모델(model.cpp)에 점 하나 추가

            InvalidateRect(hWnd, NULL, TRUE);   // 다시 그려 달라고 요청
        }
        break;
    case WM_RBUTTONDOWN:
        {
            // [도전 과제] 오른쪽 버튼을 누르면 마지막에 찍은 원을 하나 지웁니다. (Undo)
            DeleteLastPoint();                  // 모델에서 마지막 점 삭제
            InvalidateRect(hWnd, NULL, TRUE);   // 다시 그려 달라고 요청
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 그리기 코드를 추가합니다...

            HBRUSH yellow, oldBrush;
            yellow = CreateSolidBrush(RGB(255, 255, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, yellow);

            HPEN blue, oldPen;
            blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            oldPen = (HPEN)SelectObject(hdc, blue);

            // [설명] 저장된 점을 처음부터 끝까지 돌면서 전부 다시 그립니다.
            //        브러시와 펜은 한 번만 끼우고 반복문 안에서 계속 재사용합니다.
            int n = GetNumPoints();
            for (int i = 0; i < n; i++) {
                POINT p = GetPoint(i);
                Ellipse(hdc, p.x - 30, p.y - 30, p.x + 30, p.y + 30);
            }

            SelectObject(hdc, oldPen);
            DeleteObject(blue);

            SelectObject(hdc, oldBrush);
            DeleteObject(yellow);

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
