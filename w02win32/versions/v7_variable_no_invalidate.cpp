// ==========================================================================
//  v7 - 변수 사용 (★ 아직 안 되는 단계 ★)
// --------------------------------------------------------------------------
//  [이 단계에서 하는 일]
//    v6의 "지워짐" 문제를 고치려고 발상을 바꿉니다.
//      클릭했을 때  : 그리지 않고 좌표만 변수에 저장
//      WM_PAINT에서 : 저장된 좌표를 보고 그림
//    이렇게 하면 WM_PAINT 가 몇 번 불려도 항상 같은 그림이 다시 나옵니다.
//
//  [새로 나온 것]
//    static int x = -100, y = 100;  <- 함수 밖(전역)에 좌표 저장용 변수
//      처음 값이 -100 인 이유: 프로그램 시작 직후에는 화면 밖에 그려서
//      아무것도 안 보이게 하려는 것입니다.
//    WM_LBUTTONDOWN 은 좌표 저장만, 그리기 코드는 전부 주석 처리했습니다.
//    그리기 코드는 통째로 WM_PAINT 로 옮겼습니다.
//
//  [실행하면]
//    ★ 클릭해도 아무 일도 안 일어납니다! (강의노트가 일부러 보여 주는 실패 단계)
//      그런데 창을 화면 밖으로 내렸다 올리면 그제서야 원이 나타납니다.
//      v6 과 정반대 증상이라 재미있습니다.
//    
//      원인: 좌표는 잘 저장됐지만, "화면을 다시 그려라"라고 아무도 말해 주지 않았습니다.
//            Windows 는 x, y 가 바뀐 걸 모르니 WM_PAINT 를 보낼 이유가 없습니다.
//            창을 가렸다 열면 그때는 Windows 가 알아서 WM_PAINT 를 보내므로 그려집니다.
//      해결: v8 에서 InvalidateRect 한 줄을 추가합니다.
//
//  [바뀐 곳] 전역 변수 추가 + WM_LBUTTONDOWN + WM_PAINT
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

// 마지막으로 클릭한 좌표를 저장해 두는 변수.
// -100 으로 시작해서 프로그램을 켠 직후에는 화면 밖에 그려집니다(=안 보임).
static int x = -100, y = 100;

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

            //int x, y;         <- 지역 변수를 지우고 위의 전역 변수를 씁니다.
            x = LOWORD(lParam); //    여기서는 좌표를 "기억"만 합니다.
            y = HIWORD(lParam);

            // ※ 아직 화면을 다시 그리라는 요청이 없어서 클릭해도 변화가 없습니다. (v8에서 해결)

            // 아래는 v6까지 여기서 그리던 코드입니다.
            // 이제 그리기는 WM_PAINT 담당이므로 전부 주석 처리했습니다.
            //HDC hdc = GetDC(hWnd);
            //HBRUSH yellow, oldBrush;
            //yellow = CreateSolidBrush(RGB(255, 255, 0));
            //oldBrush = (HBRUSH)SelectObject(hdc, yellow);

            //HPEN blue, oldPen;
            //blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            //oldPen = (HPEN)SelectObject(hdc, blue);

            //Ellipse(hdc, x - 30, y - 30, x + 30, y + 30);

            //SelectObject(hdc, oldPen);
            //DeleteObject(blue);

            //SelectObject(hdc, oldBrush);
            //DeleteObject(yellow);
            //ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_PAINT:
        {
            // [설명] 이제 그리기는 전부 여기서만 합니다.
            //        WM_PAINT 는 "언제든 다시 불려도 똑같은 그림이 나오게" 짜야 합니다.
            //        그래야 창을 가렸다 열어도 그림이 살아남습니다.
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 그리기 코드를 추가합니다...

            HBRUSH yellow, oldBrush;
            yellow = CreateSolidBrush(RGB(255, 255, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, yellow);

            HPEN blue, oldPen;
            blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            oldPen = (HPEN)SelectObject(hdc, blue);

            // 전역 변수 x, y 에 저장해 둔 좌표를 사용합니다.
            Ellipse(hdc, x - 30, y - 30, x + 30, y + 30);

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
