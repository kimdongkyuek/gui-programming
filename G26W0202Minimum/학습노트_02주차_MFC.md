# [02주차] 「학번」 「이름」 — 가장 간단한 MFC

> 제출 전 이 줄은 지우세요. 「」 채우고, (캡처 N) 자리에 스크린샷 붙이면 됩니다.
> 지난 Win32 노트와 같은 주차라, 한 글에 합쳐 올려도 됩니다.

## 만든 것

MFC로 창을 띄우고, 클릭한 자리에 원을 그리는 프로그램.
지난주 Win32로 만든 것과 **결과는 똑같지만 코드 구조가 완전히 다르다.**
Win32는 C 스타일이었고, MFC는 C++ 클래스를 **상속받고 재정의**해서 만든다.

(캡처 1: 클릭해서 원이 그려진 실행 화면)

## 단계별로 배운 것

**1. 빈 프로젝트에 2줄만 쓰기** — Windows 데스크톱 마법사로 빈 프로젝트를 만들고
`main.cpp`에 딱 2줄을 썼는데 실행이 됐다.

```cpp
#include <afxwin.h>
CWinApp app;
```

`main` 함수도 없는데 실행된다는 게 이해가 안 됐는데, F11로 디버깅해 보니
`_tWinMain()`이 실행되는 게 보였다. **MFC가 `main`을 이미 갖고 있어서**
내가 안 써도 되는 거였다. 아무것도 안 하지만 에러 없이 도는 "완벽한 프로그램"이다.

**2. MFC 사용 설정** — 프로젝트 속성 → 고급 → **MFC 사용 → 공유 DLL에서 MFC 사용**.
이걸 안 하면 빌드가 안 된다. (아래 "막혔던 것" 참고)

**3. 상속과 재정의** — MS가 만든 `CWinApp`을 **수정하는 게 아니라 상속받아서**
필요한 함수만 덮어쓴다는 개념을 배웠다.

```cpp
class MyApp : public CWinApp {     // CWinApp을 상속
public:
    virtual BOOL InitInstance();   // 재정의할 함수 선언
};

BOOL MyApp::InitInstance() {       // 내 내용으로 덮어쓰기
    AfxMessageBox(L"파생 클래스의 InitInstance() 재정의");
    return TRUE;
}

MyApp app;                         // CWinApp app; 은 주석 처리!
```

`InitInstance()`는 내가 호출하지 않는다. **MFC가 시작할 때 알아서 불러준다.**
프레임워크가 정한 자리에 내 코드를 끼워 넣는 방식이다.

**4. 창 생성** — `CFrameWnd`를 상속해서 창을 만들었다.

```cpp
class CMainWnd : public CFrameWnd {
public:
    CMainWnd();
};

CMainWnd::CMainWnd() {
    Create(NULL, L"GUI 프로그래밍");   // 창을 실제로 만드는 함수
}

BOOL MyApp::InitInstance() {
    m_pMainWnd = new CMainWnd();          // 메인 창으로 등록
    m_pMainWnd->ShowWindow(m_nCmdShow);   // 화면에 보이기
    m_pMainWnd->UpdateWindow();           // 즉시 그리기
    return TRUE;
}
```

지난주 Win32에서 `MyRegisterClass` + `CreateWindowW` + `ShowWindow`로
길게 했던 걸 `Create()` 한 줄이 대신 한다.

**5. 원 그리기 (메시지 처리)** — 메시지 맵으로 클릭과 그리기를 연결했다.

```cpp
class CMainWnd : public CFrameWnd {
private:
    CPoint m_ptClick = CPoint(-100, -100);   // 클릭 좌표를 멤버 변수로 보관
public:
    CMainWnd();
    DECLARE_MESSAGE_MAP()                     // 이 클래스가 메시지를 받는다고 선언
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)   // 나, 그리고 내 부모
    ON_WM_LBUTTONDOWN()                  // 왼쪽 클릭 -> OnLButtonDown
    ON_WM_PAINT()                        // 다시 그리기 -> OnPaint
END_MESSAGE_MAP()

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point) {
    m_ptClick = point;   // 좌표만 저장
    Invalidate();        // 다시 그려달라고 요청
}

void CMainWnd::OnPaint() {
    CPaintDC dc(this);   // 그릴 도화지 (BeginPaint/EndPaint 자동)
    dc.Ellipse(m_ptClick.x - 30, m_ptClick.y - 30,
               m_ptClick.x + 30, m_ptClick.y + 30);
}
```

지난주에 배운 **"그리기는 `OnPaint`에서, 다른 곳에선 값만 바꾸고 다시 그려달라고 요청"**
구조가 MFC에서도 똑같았다. 함수 이름만 바뀐 것이다.

(캡처 2: 창을 가렸다 열어도 원이 남아 있는 화면)

## 코드가 어떻게 연결되나

제일 헷갈렸던 부분이라 실행 순서대로 정리했다.

```
MyApp app;                   ← 전역 객체. main보다 먼저 만들어진다
      │
      ▼
MFC 안의 _tWinMain()         ← 내가 안 쓴 main. MFC가 갖고 있다
      │
      ▼
app.InitInstance()           ← 내가 재정의한 함수를 MFC가 호출
      │  m_pMainWnd = new CMainWnd();   → CMainWnd 생성자 → Create()로 창 생성
      │  ShowWindow / UpdateWindow      → 화면에 표시
      ▼
MFC 안의 Run()               ← 메시지 루프 (Win32의 while(GetMessage) 자리)
      │
      ├─ 왼쪽 클릭 ──→ 메시지 맵 ──→ OnLButtonDown()  → 좌표 저장 + Invalidate()
      └─ 다시 그리기 ─→ 메시지 맵 ──→ OnPaint()       → 저장된 좌표로 원 그리기
```

핵심은 **호출 방향이 반대**라는 점이다.
내가 프레임워크를 부르는 게 아니라, **프레임워크가 내 함수를 부른다.**
그래서 함수 이름과 인자 모양을 내 맘대로 정할 수 없고 MFC가 정한 대로 써야 한다.

전역 객체 `MyApp app;`이 시작점인 것도 여기서 이해됐다.
전역 객체는 `main`보다 먼저 생성되므로, MFC는 그 객체를 붙잡고 시작할 수 있다.
그래서 `CWinApp app;`을 **반드시 주석 처리**해야 한다. 앱 객체가 2개면 안 되기 때문이다.

## 명령어 정리

| 코드 | 의미 |
|---|---|
| `#include <afxwin.h>` | MFC 핵심 헤더. **AFX**는 MFC의 개발 당시 이름(Application Framework) |
| `CWinApp` | 애플리케이션 자체를 나타내는 클래스. 프로그램 하나에 객체 하나 |
| `CFrameWnd` | 테두리·제목줄이 있는 일반 창 클래스 |
| `virtual` | 자식이 재정의할 수 있게 하는 키워드. 없으면 재정의해도 MFC가 부모 것을 부른다 |
| `InitInstance()` | 프로그램 시작 시 MFC가 호출. 창을 만드는 자리 |
| `m_pMainWnd` | `CWinApp`의 멤버. 메인 창 포인터. `m_`은 member 뜻 |
| `m_nCmdShow` | 창을 어떻게 보일지(보통/최소화 등). 실행할 때 OS가 넘겨준 값 |
| `Create(NULL, L"제목")` | 실제로 창을 만드는 함수. 첫 인자는 창 클래스 이름(NULL이면 기본) |
| `DECLARE_MESSAGE_MAP()` | "이 클래스는 메시지를 처리한다"는 선언 (헤더 쪽) |
| `BEGIN_MESSAGE_MAP(내클래스, 부모클래스)` | 메시지 연결표 시작. 내가 처리 안 한 건 부모로 넘어간다 |
| `ON_WM_LBUTTONDOWN()` | 왼쪽 클릭 메시지를 `OnLButtonDown`에 연결 |
| `ON_WM_PAINT()` | 다시 그리기 메시지를 `OnPaint`에 연결 |
| `END_MESSAGE_MAP()` | 연결표 끝 |
| `afx_msg` | 메시지 처리 함수라는 표시 |
| `CPoint` | x, y를 담는 클래스. `point.x`, `point.y` |
| `Invalidate()` | "창 내용이 낡았다" 표시 → MFC가 `OnPaint`를 호출 |
| `CPaintDC dc(this)` | 그릴 도화지. **생성될 때 BeginPaint, 사라질 때 EndPaint를 자동으로** 한다 |
| `dc.Ellipse(l, t, r, b)` | 원/타원 그리기. `dc`가 도화지라서 인자로 안 넘긴다 |
| `AfxMessageBox(L"...")` | MFC의 알림창. `Afx`로 시작하는 건 클래스에 속하지 않은 MFC 전역 함수 |

`ON_WM_...()`는 전부 **매크로**다. Win32에서 `switch(message) { case WM_PAINT: ... }`로
직접 쓰던 분기문을 이 매크로들이 대신 만들어 준다. 그래서 MFC에는 `switch`문이 안 보인다.

## 지난주 Win32와 비교

같은 프로그램인데 코드가 이렇게 달라졌다.

| Win32 (지난주) | MFC (이번주) |
|---|---|
| `WndProc`의 `switch`문 | `BEGIN_MESSAGE_MAP` ~ `END_MESSAGE_MAP` |
| `case WM_LBUTTONDOWN:` | `ON_WM_LBUTTONDOWN()` + `OnLButtonDown()` |
| `LOWORD(lParam)`, `HIWORD(lParam)` | `CPoint point` **(이미 좌표라 자를 필요 없음)** |
| `HDC hdc = BeginPaint(...)` / `EndPaint(...)` | `CPaintDC dc(this)` **(짝 맞추기 자동)** |
| `Ellipse(hdc, ...)` | `dc.Ellipse(...)` |
| `InvalidateRect(hWnd, NULL, TRUE)` | `Invalidate()` |
| `static int x, y` 전역 변수 | `m_ptClick` 멤버 변수 |
| `while(GetMessage(...))` 직접 작성 | MFC의 `Run()`이 대신 |

특히 `CPaintDC`가 좋았다. Win32에서는 `BeginPaint`/`EndPaint` 짝을 내가 챙겨야 했는데,
MFC는 객체가 사라질 때 자동으로 정리해 준다. 깜빡할 일이 없다.

## 막혔던 것

**1. `error C1189` — MFC 설정 누락 (제일 오래 잡았다)**

```
error C1189: #error: Building MFC application with /MD[d] (CRT dll version)
requires MFC shared dll version. Please #define _AFXDLL or do not use /MD[d]
```

한글 인코딩을 UTF-8로 바꾼 직후에 나서 인코딩 문제인 줄 알고 한참 헤맸는데,
**"공유 DLL에서 MFC 사용" 설정이 프로젝트에서 빠져 있던 것**이었다.
속성 창에서 다시 설정하니 해결됐다.

처음 2줄 코드일 때는 문제없이 넘어갔는데, 창을 만들고 메시지 맵을 쓰는 단계부터
에러가 났다. 설정을 다시 확인해 보니 프로젝트 파일(`.vcxproj`)에 설정이 저장되어
있지 않았다. 속성을 바꿀 때 **구성을 "모든 구성"으로 해놓고 확인을 눌러야** 한다는 걸
알게 됐다.

**2. 한글 주석/문자열 때문에 빌드 에러**

`AfxMessageBox(L"파생 클래스의...")`처럼 한글을 쓰면 빌드가 안 됐다.
파일 → 다른 이름으로 저장 → 인코딩하여 저장 → **"유니코드(서명 있는 UTF-8)"** 로
바꾸면 해결된다. "서명"이 붙은 쪽을 골라야 한다.

## 정리하면서 알게 된 것

프레임워크는 **"완벽하지만 아무것도 하지 않는 프로그램"을 주고,
내가 필요한 부분만 상속·재정의해서 채워 넣는 구조**였다.
MFC뿐 아니라 iOS, Android, WinForms, WPF도 같은 방식이라고 한다.

그래서 프레임워크를 쓰려면
**어떤 클래스가 있는지(상속 대상)**, **어떤 함수가 언제 불리는지(재정의 대상)**를
알아야 한다는 말이 이해됐다. 설계를 내가 바꾸는 게 아니라 따라가는 것이다.

## 더 알아볼 것

- `CFrameWnd` 말고 어떤 창 클래스들이 있는지
- `OnPaint` 외에 재정의할 수 있는 함수가 또 뭐가 있는지 찾는 방법
- `afx_msg`가 실제로 컴파일될 때 어떻게 되는지

---

GitHub: 「본인 저장소 링크」

---

## 📌 제출 전 체크 (이 아래는 지우세요)

**캡처 2장**

| # | 화면 | 방법 |
|---|---|---|
| 1 | 원이 그려진 실행 화면 | `Ctrl+F5` 실행 → 창 아무 데나 클릭 |
| 2 | 원이 유지되는 화면 | 이어서 창을 다른 창으로 가렸다 다시 열기 |

**그 외**

- 「학번」「이름」「GitHub 링크」 채우기
- **Allow liking** 체크
