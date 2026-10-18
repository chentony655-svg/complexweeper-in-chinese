#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#define _UNICODE

#define WINVER        0x0A00
#define _WIN32_WINNT  0x0A00

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <limits.h>
#include <math.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// ============================================================
// 常量
// ============================================================
#define MAX_DIM          64
#define MAX_CELLS        (MAX_DIM * MAX_DIM)
#define CELL_SIZE        28
#define BOARD_MARGIN     8
#define BOARD_PAD_X      16
#define BOARD_PAD_Y      12
#define FACE_BTN_W       56
#define FACE_BTN_H       56
#define TOP_PANEL_H      168
#define LED_CHAR_W       22
#define LED_CHAR_H       40
#define COUNTER_DIGIT_X  36

#define MIN_ROWS         9
#define MAX_ROWS         30
#define MIN_COLS         9
#define MAX_COLS         40

#define WNDCLASS_NAME    L"ComplexSweeperMain"
#define DIALOG_CUSTOM    L"ComplexSweeperCustomDlg"
#define DIALOG_ABOUT     L"ComplexSweeperAboutDlg"
#define DIALOG_HIGHSCORE L"ComplexSweeperHighScoreDlg"
#define APP_TITLE        L"复扫雷 Complexweeper"
#define APP_VERSION      L"1.0.11"

#define IDC_EDIT_W          2100
#define IDC_EDIT_H          2101
#define IDC_EDIT_M1         2102
#define IDC_EDIT_M2         2103
#define IDC_EDIT_M3         2104
#define IDC_EDIT_M4         2105
#define IDC_BTN_AVG         2110
#define IDC_BTN_OK          2111
#define IDC_BTN_CANCEL      2112
#define IDC_ERR             2120

// 手写对话框里静态文本的 ID（布局/DPI 缩放时需要按 ID 定位）
#define IDC_ST_H            2130
#define IDC_ST_HINT_H       2131
#define IDC_ST_W            2132
#define IDC_ST_HINT_W       2133
#define IDC_ST_M1           2134
#define IDC_ST_M2           2135
#define IDC_ST_M3           2136
#define IDC_ST_M4           2137
#define IDC_ST_ABOUT        2138
#define IDC_ST_SCORE        2139

// 逻辑像素（96 DPI）下的窗口最小客户区。
// 顶部面板需要约 352 逻辑像素宽；这里留一点余量。
#define MIN_CLIENT_W        360
#define MIN_CLIENT_H        340
#define BASE_DPI            96

#define IDM_BEGINNER        1001
#define IDM_INTERMEDIATE    1002
#define IDM_EXPERT          1003
#define IDM_CUSTOM          1004
#define IDM_ZOOM_100        1010
#define IDM_ZOOM_200        1011
#define IDM_ZOOM_300        1012
#define IDM_HIGHSCORE       1020
#define IDM_HOWTOPLAY       1030
#define IDM_ABOUT           1031
#define IDM_EXIT            1099

#define IDT_TIMER           3000

#ifndef WM_DPICHANGED
#define WM_DPICHANGED       0x02E0
#endif

// ============================================================
// sprite sheet 坐标
// ============================================================
#define SPR_FACE_Y           0
#define SPR_FACE_W           96
#define SPR_FACE_H           96
#define SPR_FACE_NORMAL_X    128
#define SPR_FACE_PRESS_X     224
#define SPR_FACE_DEAD_X      320
#define SPR_FACE_WIN_X       416
#define SPR_FACE_WIN2_X      512

#define SPR_LED_X0           608
#define SPR_LED_STEP         52
#define SPR_LED_Y            0
#define SPR_LED_W            52
#define SPR_LED_H            92

#define SPR_LED_8_X          0
#define SPR_LED_9_X          52
#define SPR_LED_MINUS_X      156
#define SPR_LED_I_X          208
#define SPR_LED_ROW2_Y       128
#define SPR_LED_ROW2_W       52
#define SPR_LED_ROW2_H       92

#define SPR_VAL_W            64
#define SPR_VAL_H            64

#define SPR_VAL_ROW1_Y       128
#define SPR_VAL_0_X          260
#define SPR_VAL_1_X          324
#define SPR_VAL_R2_X         388
#define SPR_VAL_2_X          452
#define SPR_VAL_R5_X         516
#define SPR_VAL_2R2_X        580
#define SPR_VAL_3_X          644
#define SPR_VAL_R10_X        708
#define SPR_VAL_R13_X        772
#define SPR_VAL_4_X          836
#define SPR_VAL_R17_X        900

#define SPR_VAL_ROW2_Y       220
#define SPR_VAL_3R2_X        0
#define SPR_VAL_2R5_X        64
#define SPR_VAL_5_X          128
#define SPR_VAL_R26_X        192
#define SPR_VAL_R29_X        256
#define SPR_VAL_4R2_X        320
#define SPR_VAL_R34_X        384
#define SPR_VAL_6_X          448
#define SPR_VAL_R37_X        512
#define SPR_VAL_2R10_X       576
#define SPR_VAL_7_X          640
#define SPR_VAL_5R2_X        704
#define SPR_VAL_8_X          768
#define SPR_VAL_BLANK_X      832
#define SPR_VAL_PRESSED_X    896
#define SPR_MINE_POS_REAL_MARK_X  960

#define SPR_MINE_Y           284
#define SPR_MINE_W           64
#define SPR_MINE_H           64

#define SPR_MINE_POS_REAL_OPEN_X   0
#define SPR_MINE_POS_REAL_BOOM_X   64
#define SPR_MINE_POS_REAL_WRONG_X  128
#define SPR_MINE_NEG_REAL_MARK_X   192
#define SPR_MINE_NEG_REAL_OPEN_X   256
#define SPR_MINE_NEG_REAL_BOOM_X   320
#define SPR_MINE_NEG_REAL_WRONG_X  384
#define SPR_MINE_POS_IMAG_MARK_X   448
#define SPR_MINE_POS_IMAG_OPEN_X   512
#define SPR_MINE_POS_IMAG_BOOM_X   576
#define SPR_MINE_POS_IMAG_WRONG_X  640
#define SPR_MINE_NEG_IMAG_MARK_X   704
#define SPR_MINE_NEG_IMAG_OPEN_X   768
#define SPR_MINE_NEG_IMAG_BOOM_X   832
#define SPR_MINE_NEG_IMAG_WRONG_X  896

// ============================================================
// 数据结构
// ============================================================
enum { MINE_POS_REAL=0, MINE_NEG_REAL=1, MINE_POS_IMAG=2, MINE_NEG_IMAG=3, MINE_NONE=0xFF };
enum { FLAG_NONE=0, FLAG_POS_REAL=1, FLAG_NEG_REAL=2, FLAG_POS_IMAG=3, FLAG_NEG_IMAG=4 };
enum { FACE_BOOM=0, FACE_NORMAL=1, FACE_PRESS=2, FACE_WIN=3, FACE_WIN_SUN=4, FACE_WIN_IM=5 };

typedef struct { int k, n; BOOL has_mine_around; } CellValue;
typedef struct {
    BYTE mine_type, flag_type;
    BOOL opened, is_mine;
    CellValue display;
} Cell;

typedef struct {
    int width, height;
    int mine_count[4];
    Cell cells[MAX_CELLS];
    int opened_count;
    int flag_count[4];
    int start_x, start_y;
    BOOL started, over, win;
    DWORD start_tick, elapsed_ms;
    int zoom;
    int preset;             // 0=自定义 1=初级 2=中级 3=高级（用于最高分纪录）
} Board;

typedef struct { DWORD time_beginner, time_intermediate, time_expert; } HighScores;

// ============================================================
// 全局
// ============================================================
static HINSTANCE  g_hInst = NULL;
static HWND       g_hWnd  = NULL;
static Board      g_board;
static HighScores g_scores;
static int        g_faceState = FACE_NORMAL;
static int        g_pressX = -1, g_pressY = -1;
static BOOL       g_pressing = FALSE;
static BOOL       g_facePressing = FALSE;
static BOOL       g_chordPressed = FALSE;
static int        g_chordX = -1, g_chordY = -1;
static HBITMAP    g_hSprite = NULL;
static HDC        g_hSpriteDC = NULL;
static HBITMAP    g_hSpriteOld = NULL;
static HBRUSH     g_brWindow = NULL;
static HBRUSH     g_brCell   = NULL;
static HDC        g_backDC   = NULL;
static HBITMAP    g_backBmp  = NULL;
static HBITMAP    g_backOld  = NULL;
static int        g_backW    = 0, g_backH = 0;
static BOOL       g_dlgOK = FALSE;
static int        g_dpi = BASE_DPI;              // 主窗口当前 DPI
static int        g_scrollX = 0, g_scrollY = 0;  // 棋盘视口滚动偏移（像素）
static int        g_timerPauseDepth = 0;         // >0 时计时暂停（菜单/模态对话框）

static void RecordWin(const Board* b);   // 定义在注册表读写之后

// ============================================================
// 工具
// ============================================================
static int clampi(int v, int lo, int hi) { return v<lo?lo:(v>hi?hi:v); }
static int idx(const Board* b, int x, int y) { return y*b->width + x; }
static BOOL inBounds(const Board* b, int x, int y) { return x>=0 && y>=0 && x<b->width && y<b->height; }

// ============================================================
// DPI / 窗口度量
// 所有布局数字都以 96 DPI 为基准，运行时统一乘以 g_dpi/96。
// ============================================================
static HMODULE User32Module(void) {
    static HMODULE h = NULL;
    if (!h) h = GetModuleHandleW(L"user32.dll");
    return h;
}

static int GetSystemDpi(void) {
    typedef UINT (WINAPI *PFN_GetDpiForSystem)(void);
    static PFN_GetDpiForSystem p = NULL;
    static BOOL tried = FALSE;
    if (!tried) { tried = TRUE; p = (PFN_GetDpiForSystem)(void*)GetProcAddress(User32Module(), "GetDpiForSystem"); }
    if (p) { UINT d = p(); if (d) return (int)d; }
    HDC dc = GetDC(NULL);
    int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSY) : BASE_DPI;
    if (dc) ReleaseDC(NULL, dc);
    return dpi > 0 ? dpi : BASE_DPI;
}

// GetDpiForWindow/AdjustWindowRectExForDpi/GetSystemMetricsForDpi 都是 Win10 1607+ 的 API。
// 动态取地址，老系统上退回系统 DPI 的旧接口，不影响运行。
static int GetWindowDpi(HWND hwnd) {
    typedef UINT (WINAPI *PFN_GetDpiForWindow)(HWND);
    static PFN_GetDpiForWindow p = NULL;
    static BOOL tried = FALSE;
    if (!tried) { tried = TRUE; p = (PFN_GetDpiForWindow)(void*)GetProcAddress(User32Module(), "GetDpiForWindow"); }
    if (p && hwnd) { UINT d = p(hwnd); if (d) return (int)d; }
    HDC dc = GetDC(hwnd);
    int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSY) : BASE_DPI;
    if (dc) ReleaseDC(hwnd, dc);
    return dpi > 0 ? dpi : BASE_DPI;
}

static int DpiScale(int v) { return MulDiv(v, g_dpi, BASE_DPI); }
static int DpiScaleEx(int v, int dpi) { return MulDiv(v, dpi, BASE_DPI); }

static int ScrollBarWidth(void) {
    typedef int (WINAPI *PFN_GetSystemMetricsForDpi)(int, UINT);
    static PFN_GetSystemMetricsForDpi p = NULL;
    static BOOL tried = FALSE;
    if (!tried) { tried = TRUE; p = (PFN_GetSystemMetricsForDpi)(void*)GetProcAddress(User32Module(), "GetSystemMetricsForDpi"); }
    if (p) return p(SM_CXVSCROLL, (UINT)g_dpi);
    return DpiScale(GetSystemMetrics(SM_CXVSCROLL));
}
static int ScrollBarHeight(void) {
    typedef int (WINAPI *PFN_GetSystemMetricsForDpi)(int, UINT);
    static PFN_GetSystemMetricsForDpi p = NULL;
    static BOOL tried = FALSE;
    if (!tried) { tried = TRUE; p = (PFN_GetSystemMetricsForDpi)(void*)GetProcAddress(User32Module(), "GetSystemMetricsForDpi"); }
    if (p) return p(SM_CYHSCROLL, (UINT)g_dpi);
    return DpiScale(GetSystemMetrics(SM_CYHSCROLL));
}

static void AdjustWindowRectForDpi(RECT* rc, DWORD style, BOOL menu, int dpi) {
    typedef BOOL (WINAPI *PFN_AdjustWindowRectExForDpi)(LPRECT, DWORD, BOOL, DWORD, UINT);
    static PFN_AdjustWindowRectExForDpi p = NULL;
    static BOOL tried = FALSE;
    if (!tried) { tried = TRUE; p = (PFN_AdjustWindowRectExForDpi)(void*)GetProcAddress(User32Module(), "AdjustWindowRectExForDpi"); }
    if (p) { p(rc, style, menu, 0, (UINT)dpi); return; }
    AdjustWindowRectEx(rc, style, menu, 0);
}

static void GetWorkArea(HWND hwnd, RECT* work) {
    MONITORINFO mi;
    mi.cbSize = sizeof(mi);
    HMONITOR mon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    if (mon && GetMonitorInfoW(mon, &mi)) { *work = mi.rcWork; return; }
    if (!SystemParametersInfoW(SPI_GETWORKAREA, 0, work, 0)) {
        work->left = work->top = 0;
        work->right = GetSystemMetrics(SM_CXSCREEN);
        work->bottom = GetSystemMetrics(SM_CYSCREEN);
    }
}

static HFONT CreateUiFontForDpi(int dpi) {
    NONCLIENTMETRICSW ncm;
    memset(&ncm, 0, sizeof(ncm));
    ncm.cbSize = sizeof(ncm);
    BOOL got = FALSE;
    typedef BOOL (WINAPI *PFN_SPIForDpi)(UINT, UINT, PVOID, UINT, UINT);
    static PFN_SPIForDpi p = NULL;
    static BOOL tried = FALSE;
    if (!tried) { tried = TRUE; p = (PFN_SPIForDpi)(void*)GetProcAddress(User32Module(), "SystemParametersInfoForDpi"); }
    if (p) got = p(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0, (UINT)dpi);
    if (!got) {
        got = SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
        if (got) {
            int sysDpi = GetSystemDpi();
            if (ncm.lfMessageFont.lfHeight != 0)
                ncm.lfMessageFont.lfHeight = MulDiv(ncm.lfMessageFont.lfHeight, dpi, sysDpi);
        }
    }
    LOGFONTW lf;
    if (got) lf = ncm.lfMessageFont;
    else {
        memset(&lf, 0, sizeof(lf));
        lf.lfWeight = FW_NORMAL;
        lf.lfCharSet = DEFAULT_CHARSET;
        wcscpy(lf.lfFaceName, L"Microsoft YaHei UI");
    }
    if (lf.lfHeight == 0) lf.lfHeight = -MulDiv(9, dpi, 72);
    lf.lfWidth = 0;
    return CreateFontIndirectW(&lf);
}

static void ZeroBoard(Board* b) {
    memset(b->cells, 0, sizeof(Cell)*MAX_CELLS);
    for (int i=0;i<MAX_CELLS;i++) { b->cells[i].mine_type=MINE_NONE; b->cells[i].flag_type=FLAG_NONE; }
    b->opened_count = 0;
    memset(b->flag_count, 0, sizeof(b->flag_count));
    b->started = b->over = b->win = FALSE;
    b->start_tick = b->elapsed_ms = 0;
}

static int DisplayN(const CellValue* v) { return v->k*v->k*v->n; }

static void Simplify(int N, int* out_k, int* out_n) {
    if (N<=0) { *out_k=0; *out_n=0; return; }
    int k=1, m=N;
    for (int i=(int)sqrt((double)N); i>=2; i--) {
        if (N%(i*i)==0) { k=i; m=N/(i*i); break; }
    }
    *out_k=k; *out_n=m;
}

static void InvalidateBoardArea(HWND hwnd);   // 定义在绘制部分

// 单元格边长：96 DPI 下 100% 为 28，随缩放和 DPI 一起放大。
static int GetCellSize(const Board* b) {
    return MulDiv(CELL_SIZE, b->zoom * g_dpi, 100 * BASE_DPI);
}

// 棋盘外框（顶部面板下方、窗口边距以内）
static void GetBoardPanelRect(HWND hwnd, RECT* r) {
    RECT rc; GetClientRect(hwnd, &rc);
    int m = DpiScale(BOARD_MARGIN);
    r->left = m;
    r->top = m + DpiScale(TOP_PANEL_H) + DpiScale(8);
    r->right = rc.right - m;
    r->bottom = rc.bottom - m;
    if (r->right < r->left) r->right = r->left;
    if (r->bottom < r->top) r->bottom = r->top;
}

// 棋盘可滚动视口（外框再内缩 padding）。棋盘比视口大时滚动，小时居中。
static void GetBoardViewRect(HWND hwnd, RECT* r) {
    GetBoardPanelRect(hwnd, r);
    int px = DpiScale(BOARD_PAD_X), py = DpiScale(BOARD_PAD_Y);
    r->left += px;   r->right -= px;
    r->top += py;    r->bottom -= py;
    if (r->right < r->left) r->right = r->left;
    if (r->bottom < r->top) r->bottom = r->top;
}

static void GetBoardOrigin(HWND hwnd, const Board* b, int* ox, int* oy) {
    RECT view; GetBoardViewRect(hwnd, &view);
    int cs = GetCellSize(b);
    int contentW = b->width * cs;
    int contentH = b->height * cs;
    int vw = view.right - view.left;
    int vh = view.bottom - view.top;

    int maxX = contentW > vw ? contentW - vw : 0;
    int maxY = contentH > vh ? contentH - vh : 0;
    int sx = clampi(g_scrollX, 0, maxX);
    int sy = clampi(g_scrollY, 0, maxY);

    *ox = view.left + (contentW <= vw ? (vw - contentW) / 2 : -sx);
    *oy = view.top  + (contentH <= vh ? (vh - contentH) / 2 : -sy);
}

static BOOL ClientToCell(HWND hwnd, int mx, int my, int* outX, int* outY) {
    RECT view; GetBoardViewRect(hwnd, &view);
    if (mx < view.left || my < view.top || mx >= view.right || my >= view.bottom) return FALSE;
    int ox, oy; GetBoardOrigin(hwnd, &g_board, &ox, &oy);
    int cs = GetCellSize(&g_board);
    if (cs <= 0) return FALSE;
    if (mx < ox || my < oy) return FALSE;
    int gx = (mx - ox) / cs, gy = (my - oy) / cs;
    if (!inBounds(&g_board, gx, gy)) return FALSE;
    *outX = gx; *outY = gy;
    return TRUE;
}

static int GetFaceBtnX(int winW) { return (winW - DpiScale(FACE_BTN_W)) / 2; }
static int GetFaceBtnY(void) { return DpiScale(BOARD_MARGIN + 56); }

// 计算与 clip 相交、且落在棋盘视口内的格子范围。返回 FALSE 表示没有可见格子。
static BOOL GetVisibleCellRange(HWND hwnd, const Board* b, const RECT* clip,
                                int* x0, int* y0, int* x1, int* y1,
                                int* originX, int* originY) {
    RECT view; GetBoardViewRect(hwnd, &view);
    if (view.right <= view.left || view.bottom <= view.top) return FALSE;

    RECT vis;
    if (!IntersectRect(&vis, clip, &view)) return FALSE;

    int ox, oy; GetBoardOrigin(hwnd, b, &ox, &oy);
    int cs = GetCellSize(b);
    if (cs <= 0) return FALSE;

    RECT content = { ox, oy, ox + b->width * cs, oy + b->height * cs };
    RECT q;
    if (!IntersectRect(&q, &vis, &content)) return FALSE;

    int cx0 = (q.left   - ox) / cs;
    int cy0 = (q.top    - oy) / cs;
    int cx1 = (q.right  - 1 - ox) / cs;
    int cy1 = (q.bottom - 1 - oy) / cs;
    cx0 = clampi(cx0, 0, b->width - 1);
    cy0 = clampi(cy0, 0, b->height - 1);
    cx1 = clampi(cx1, 0, b->width - 1);
    cy1 = clampi(cy1, 0, b->height - 1);
    if (cx0 > cx1 || cy0 > cy1) return FALSE;

    *x0 = cx0; *y0 = cy0; *x1 = cx1; *y1 = cy1;
    *originX = ox; *originY = oy;
    return TRUE;
}

// 根据当前客户区大小同步滚动条范围/位置；内容放得下时滚动条自动隐藏。
static void UpdateScrollBars(HWND hwnd) {
    RECT view; GetBoardViewRect(hwnd, &view);
    int vw = view.right - view.left;
    int vh = view.bottom - view.top;
    int cs = GetCellSize(&g_board);
    int cw = g_board.width * cs;
    int ch = g_board.height * cs;

    int maxX = cw > vw ? cw - vw : 0;
    int maxY = ch > vh ? ch - vh : 0;
    g_scrollX = clampi(g_scrollX, 0, maxX);
    g_scrollY = clampi(g_scrollY, 0, maxY);

    SCROLLINFO si;
    memset(&si, 0, sizeof(si));
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = 0;
    si.nMax = cw > 0 ? cw - 1 : 0;
    si.nPage = vw > 0 ? (UINT)vw : 1;
    si.nPos = g_scrollX;
    SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

    si.nMax = ch > 0 ? ch - 1 : 0;
    si.nPage = vh > 0 ? (UINT)vh : 1;
    si.nPos = g_scrollY;
    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
}

static void ScrollBoard(HWND hwnd, int dx, int dy) {
    if (dx == 0 && dy == 0) return;
    int oldX = g_scrollX, oldY = g_scrollY;
    g_scrollX += dx;
    g_scrollY += dy;
    UpdateScrollBars(hwnd);
    if (g_scrollX != oldX || g_scrollY != oldY) InvalidateBoardArea(hwnd);
}

// ============================================================
// 贴图
// ============================================================
static void DrawSpriteScaled(HDC hdc, int sx, int sy, int sw, int sh,
                             int dx, int dy, int dw, int dh) {
    if (!g_hSpriteDC) return;
    StretchBlt(hdc, dx, dy, dw, dh, g_hSpriteDC, sx, sy, sw, sh, SRCCOPY);
}

static BOOL GetDisplaySprite(const CellValue* v, int* sx, int* sy, int* sw, int* sh) {
    *sw = SPR_VAL_W; *sh = SPR_VAL_H;
    if (!v->has_mine_around) { *sx=SPR_VAL_PRESSED_X; *sy=SPR_VAL_ROW2_Y; return TRUE; }

    struct { int k, n, x, y; } table[] = {
        {0,0,SPR_VAL_0_X,SPR_VAL_ROW1_Y},{1,1,SPR_VAL_1_X,SPR_VAL_ROW1_Y},
        {1,2,SPR_VAL_R2_X,SPR_VAL_ROW1_Y},{2,1,SPR_VAL_2_X,SPR_VAL_ROW1_Y},
        {1,5,SPR_VAL_R5_X,SPR_VAL_ROW1_Y},{2,2,SPR_VAL_2R2_X,SPR_VAL_ROW1_Y},
        {3,1,SPR_VAL_3_X,SPR_VAL_ROW1_Y},{1,10,SPR_VAL_R10_X,SPR_VAL_ROW1_Y},
        {1,13,SPR_VAL_R13_X,SPR_VAL_ROW1_Y},{4,1,SPR_VAL_4_X,SPR_VAL_ROW1_Y},
        {1,17,SPR_VAL_R17_X,SPR_VAL_ROW1_Y},
        {3,2,SPR_VAL_3R2_X,SPR_VAL_ROW2_Y},{2,5,SPR_VAL_2R5_X,SPR_VAL_ROW2_Y},
        {5,1,SPR_VAL_5_X,SPR_VAL_ROW2_Y},{1,26,SPR_VAL_R26_X,SPR_VAL_ROW2_Y},
        {1,29,SPR_VAL_R29_X,SPR_VAL_ROW2_Y},{4,2,SPR_VAL_4R2_X,SPR_VAL_ROW2_Y},
        {1,34,SPR_VAL_R34_X,SPR_VAL_ROW2_Y},{6,1,SPR_VAL_6_X,SPR_VAL_ROW2_Y},
        {1,37,SPR_VAL_R37_X,SPR_VAL_ROW2_Y},{2,10,SPR_VAL_2R10_X,SPR_VAL_ROW2_Y},
        {7,1,SPR_VAL_7_X,SPR_VAL_ROW2_Y},{5,2,SPR_VAL_5R2_X,SPR_VAL_ROW2_Y},
        {8,1,SPR_VAL_8_X,SPR_VAL_ROW2_Y},
    };
    for (int i=0;i<(int)(sizeof(table)/sizeof(table[0]));i++) {
        if (table[i].k==v->k && table[i].n==v->n) { *sx=table[i].x; *sy=table[i].y; return TRUE; }
    }
    *sx=SPR_VAL_PRESSED_X; *sy=SPR_VAL_ROW2_Y;
    return TRUE;
}

// ============================================================
// 棋盘逻辑
// ============================================================
// 把四类雷数修剪到合法范围：每类 >=0，总数 <= maxTotal。
// 正常流程不会触发（对话框已校验），但可防止异常参数把胜局判定弄乱。
static void TrimMineCounts(Board* b, int maxTotal) {
    if (maxTotal < 0) maxTotal = 0;
    int total = 0;
    for (int t=0;t<4;t++) {
        if (b->mine_count[t] < 0) b->mine_count[t] = 0;
        total += b->mine_count[t];
    }
    while (total > maxTotal) {
        int t = 0;
        for (int i=1;i<4;i++) if (b->mine_count[i] > b->mine_count[t]) t = i;
        if (b->mine_count[t] <= 0) break;
        b->mine_count[t]--; total--;
    }
}

static void InitGame(Board* b, int w, int h, int m1, int m2, int m3, int m4) {
    b->width = clampi(w,1,MAX_DIM);
    b->height = clampi(h,1,MAX_DIM);
    b->mine_count[0]=m1; b->mine_count[1]=m2;
    b->mine_count[2]=m3; b->mine_count[3]=m4;
    b->preset = 0;
    // 至少留一个安全格，否则生成的棋盘无法成立
    TrimMineCounts(b, b->width * b->height - 1);
    b->zoom = 100;
    ZeroBoard(b);
}

static void InitGameRandom(Board* b, int w, int h, int sum) {
    if (sum < 0) sum = 0;
    int m[4] = {0, 0, 0, 0};
    for (int i = 0; i < sum; i++) m[rand() % 4]++;
    InitGame(b, w, h, m[0], m[1], m[2], m[3]);
}

// 预设难度（只有它们参与最高分纪录）
static void StartPreset(Board* b, int preset, int w, int h, int sum) {
    InitGameRandom(b, w, h, sum);
    b->preset = preset;
}

static void NewGame(Board* b) {
    ZeroBoard(b);
    g_faceState = FACE_NORMAL;
    g_pressX = g_pressY = -1;
    g_pressing = g_facePressing = g_chordPressed = FALSE;
}

static void GenerateBoard(Board* b, int sx, int sy) {
    int total = b->width * b->height;

    for (int i=0;i<total;i++) { b->cells[i].mine_type = MINE_NONE; b->cells[i].is_mine = FALSE; }

    BOOL protect[MAX_CELLS]; memset(protect, 0, sizeof(protect));
    for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
        int nx=sx+dx, ny=sy+dy;
        if (inBounds(b,nx,ny)) protect[idx(b,nx,ny)] = TRUE;
    }

    // 可布雷格：首点保护范围之外的所有格子。
    // 直接洗牌取前 totalMines 个，而不是“随机重试直到放满”，
    // 这样布雷必然成功，不会出现“请求 99 雷实际只放了 N 雷”的坏局。
    int avail[MAX_CELLS];
    int availCount = 0;
    for (int i=0;i<total;i++) if (!protect[i]) avail[availCount++] = i;

    int totalMines = b->mine_count[0]+b->mine_count[1]+b->mine_count[2]+b->mine_count[3];
    if (totalMines > availCount) {
        // 极端/非法参数下收缩雷数，保证 mine_count 与实际棋盘一致
        TrimMineCounts(b, availCount);
        totalMines = b->mine_count[0]+b->mine_count[1]+b->mine_count[2]+b->mine_count[3];
    }

    for (int i=0;i<totalMines;i++) {
        int j = i + rand() % (availCount - i);
        int t = avail[i]; avail[i] = avail[j]; avail[j] = t;
    }

    int remain[4] = { b->mine_count[0], b->mine_count[1], b->mine_count[2], b->mine_count[3] };
    int left = totalMines;
    for (int i=0;i<totalMines;i++) {
        int roll = rand() % left;
        int acc = 0, t = 0;
        for (; t<4; t++) { acc += remain[t]; if (roll < acc) break; }
        if (t > 3) { for (t=0;t<4 && remain[t]<=0;t++) {} }
        if (t > 3) break;
        remain[t]--; left--;
        int ci = avail[i];
        b->cells[ci].is_mine = TRUE;
        b->cells[ci].mine_type = (BYTE)t;
    }

    b->start_x = sx; b->start_y = sy;
    b->started = TRUE;
    b->start_tick = GetTickCount();

    for (int y=0;y<b->height;y++) for (int x=0;x<b->width;x++) {
        Cell* c = &b->cells[idx(b,x,y)];
        if (c->is_mine) continue;
        int real=0, imag=0; BOOL has=FALSE;
        for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
            if (dx==0&&dy==0) continue;
            int nx=x+dx, ny=y+dy;
            if (!inBounds(b,nx,ny)) continue;
            Cell* n = &b->cells[idx(b,nx,ny)];
            if (!n->is_mine) continue;
            has = TRUE;
            switch (n->mine_type) {
                case MINE_POS_REAL: real+=1; break;
                case MINE_NEG_REAL: real-=1; break;
                case MINE_POS_IMAG: imag+=1; break;
                case MINE_NEG_IMAG: imag-=1; break;
            }
        }
        int N = real*real + imag*imag;
        int k=1, m=N; Simplify(N,&k,&m);
        c->display.k=k; c->display.n=m; c->display.has_mine_around=has;
    }
}

static void OnLose(Board* b, int mx, int my) {
    if (b->over) return;
    b->over = TRUE; b->win = FALSE;
    b->elapsed_ms = GetTickCount() - b->start_tick;
    g_faceState = FACE_BOOM;
    if (inBounds(b,mx,my)) b->cells[idx(b,mx,my)].opened = TRUE;
    InvalidateRect(g_hWnd, NULL, FALSE);
}

static void OnWin(Board* b) {
    if (b->over || !b->started) return;
    b->over = TRUE; b->win = TRUE;
    b->elapsed_ms = GetTickCount() - b->start_tick;
    g_faceState = FACE_WIN;
    RecordWin(b);
    InvalidateRect(g_hWnd, NULL, FALSE);
}

static BOOL CheckWin(Board* b) {
    if (!b->started) return FALSE;
    int total = b->width * b->height;
    int totalMines = b->mine_count[0]+b->mine_count[1]+b->mine_count[2]+b->mine_count[3];
    return b->opened_count >= (total - totalMines);
}

// 从 (x,y) 开始泛洪。每个格子最多入栈一次（queued 去重），
// 所以栈深不会超过棋盘格数；原先重复压栈可能超过 MAX_CELLS 造成栈溢出。
static void OpenRegion(Board* b, int x, int y) {
    int total = b->width * b->height;
    int stack[MAX_CELLS];
    BOOL queued[MAX_CELLS];
    int sp = 0;
    memset(queued, 0, sizeof(BOOL) * total);

    #define QUEUE_CELL(ni) \
        do { int _ni = (ni); \
             if (!queued[_ni] && !b->cells[_ni].opened && \
                 b->cells[_ni].flag_type == FLAG_NONE && sp < MAX_CELLS) { \
                 queued[_ni] = TRUE; stack[sp++] = _ni; } } while (0)

    Cell* start = &b->cells[idx(b,x,y)];
    if (start->opened) {
        // 双击/中键展开：以已翻开的格子为中心，展开周围格子
        for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
            if (dx==0&&dy==0) continue;
            if (inBounds(b,x+dx,y+dy)) QUEUE_CELL(idx(b,x+dx,y+dy));
        }
    } else {
        QUEUE_CELL(idx(b,x,y));
    }

    while (sp > 0) {
        int i = stack[--sp];
        int cx = i % b->width, cy = i / b->width;
        Cell* c = &b->cells[i];
        if (c->opened || c->flag_type != FLAG_NONE) continue;
        c->opened = TRUE; b->opened_count++;
        if (c->is_mine) { OnLose(b,cx,cy); return; }
        if (!c->display.has_mine_around) {
            for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
                if (dx==0&&dy==0) continue;
                if (inBounds(b,cx+dx,cy+dy)) QUEUE_CELL(idx(b,cx+dx,cy+dy));
            }
        }
    }

    #undef QUEUE_CELL
}

static void OpenCell(Board* b, int x, int y) {
    if (!inBounds(b,x,y) || b->over || !b->started) return;
    Cell* c = &b->cells[idx(b,x,y)];
    if (c->opened || c->flag_type != FLAG_NONE) return;
    c->opened = TRUE; b->opened_count++;
    if (c->is_mine) { OnLose(b,x,y); return; }
    if (!c->display.has_mine_around) OpenRegion(b,x,y);
    if (CheckWin(b)) OnWin(b);
}

// 双击 / 中键的“快速展开”：只有已翻开、周围旗数等于雷数的格子才生效。
// 返回是否真的展开了格子（用于局部刷新）。
static BOOL ChordCell(Board* b, int x, int y) {
    if (!b->started || b->over || !inBounds(b,x,y)) return FALSE;
    Cell* c = &b->cells[idx(b,x,y)];
    if (!c->opened || c->is_mine) return FALSE;

    int flags = 0, mines = 0;
    for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
        if (dx==0&&dy==0) continue;
        int nx=x+dx, ny=y+dy;
        if (!inBounds(b,nx,ny)) continue;
        Cell* n = &b->cells[idx(b,nx,ny)];
        if (n->flag_type != FLAG_NONE) flags++;
        if (n->is_mine) mines++;
    }
    if (flags == 0 || flags != mines) return FALSE;

    BOOL openedAny = FALSE;
    for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
        if (dx==0&&dy==0) continue;
        int nx=x+dx, ny=y+dy;
        if (!inBounds(b,nx,ny)) continue;
        Cell* n = &b->cells[idx(b,nx,ny)];
        if (n->opened || n->flag_type != FLAG_NONE) continue;
        n->opened = TRUE; b->opened_count++; openedAny = TRUE;
        if (n->is_mine) { OnLose(b,nx,ny); return TRUE; }
        if (!n->display.has_mine_around) OpenRegion(b,nx,ny);
        if (b->over) return TRUE;
    }
    if (openedAny && CheckWin(b)) OnWin(b);
    return openedAny;
}

static void ToggleFlag(Board* b, int x, int y) {
    if (!inBounds(b,x,y) || b->over) return;
    Cell* c = &b->cells[idx(b,x,y)];
    if (c->opened) return;
    c->flag_type = (c->flag_type + 1) % 5;
    memset(b->flag_count, 0, sizeof(b->flag_count));
    for (int i=0;i<b->width*b->height;i++) {
        if (b->cells[i].flag_type >= 1 && b->cells[i].flag_type <= 4)
            b->flag_count[b->cells[i].flag_type-1]++;
    }
}

// ============================================================
// 绘制
// ============================================================
static void FormatFixed(wchar_t* out, int value, int digits, BOOL append_i) {
    wchar_t num[16];
    int neg = (value < 0) ? 1 : 0;
    int absv = neg ? -value : value;

    swprintf(num, 16, L"%d", absv);
    int numLen = (int)wcslen(num);

    int maxNumLen = digits - neg;
    if (maxNumLen < 1) maxNumLen = 1;

    int pad = maxNumLen - numLen;
    if (pad < 0) pad = 0;

    int p = 0;
    if (neg) out[p++] = L'-';
    for (int i = 0; i < pad; i++) out[p++] = L'0';
    wcscpy(out + p, num);
    p += numLen;

    if (append_i) out[p++] = L'i';
    out[p] = 0;
}

static void DrawLEDFixed(HDC hdc, int x, int y, int value, int digits, BOOL append_i) {
    wchar_t buf[16]; FormatFixed(buf, value, digits, append_i);
    int len = (int)wcslen(buf);
    int cw = DpiScale(LED_CHAR_W), chh = DpiScale(LED_CHAR_H);
    for (int i=0;i<len;i++) {
        wchar_t ch = buf[i];
        int sx, sy;
        if (ch == L'-') { sx = SPR_LED_MINUS_X; sy = SPR_LED_ROW2_Y; }
        else if (ch == L'i') { sx = SPR_LED_I_X; sy = SPR_LED_ROW2_Y; }
        else if (ch >= L'0' && ch <= L'9') {
            int d = ch - L'0';
            if (d <= 7) { sx = SPR_LED_X0 + d * SPR_LED_STEP; sy = SPR_LED_Y; }
            else        { sx = SPR_LED_8_X + (d-8) * SPR_LED_STEP; sy = SPR_LED_ROW2_Y; }
        } else continue;
        DrawSpriteScaled(hdc, sx, sy, SPR_LED_W, SPR_LED_H,
                         x + i*cw, y, cw, chh);
    }
}

static void PaintFace(HDC hdc, int state, int winW) {
    int sx, sy, sw, sh;
    switch (state) {
        case FACE_BOOM: sx = SPR_FACE_DEAD_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
        case FACE_PRESS: sx = SPR_FACE_PRESS_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
        case FACE_WIN: sx = SPR_FACE_WIN_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
        default: sx = SPR_FACE_NORMAL_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
    }
    DrawSpriteScaled(hdc, sx, sy, sw, sh,
                     GetFaceBtnX(winW), GetFaceBtnY(),
                     DpiScale(FACE_BTN_W), DpiScale(FACE_BTN_H));
}

// 松开鼠标/失去鼠标捕获后，表情应回到当前棋局真实状态，
// 而不是一律变回笑脸（输棋后点棋盘会把死脸变回笑脸）。
static void RestoreFaceState(void) {
    if (g_board.over) g_faceState = g_board.win ? FACE_WIN : FACE_BOOM;
    else              g_faceState = FACE_NORMAL;
}

static void PaintCounter(HDC hdc, Board* b) {
    int cx = DpiScale(BOARD_MARGIN) + DpiScale(8);
    int cy = DpiScale(BOARD_MARGIN) + DpiScale(8);
    int icon = DpiScale(32);
    int rowStep = DpiScale(40);
    for (int t=0;t<4;t++) {
        int icon_x, icon_y;
        switch (t) {
            case 0: icon_x = SPR_MINE_POS_REAL_MARK_X; icon_y = SPR_VAL_ROW2_Y; break;
            case 1: icon_x = SPR_MINE_NEG_REAL_MARK_X; icon_y = SPR_MINE_Y; break;
            case 2: icon_x = SPR_MINE_POS_IMAG_MARK_X; icon_y = SPR_MINE_Y; break;
            case 3: icon_x = SPR_MINE_NEG_IMAG_MARK_X; icon_y = SPR_MINE_Y; break;
            default: icon_x = SPR_MINE_POS_REAL_MARK_X; icon_y = SPR_VAL_ROW2_Y; break;
        }
        DrawSpriteScaled(hdc, icon_x, icon_y, 64, 64, cx, cy, icon, icon);
        int remain = b->mine_count[t] - b->flag_count[t];
        // 4 位 LED：负数最多显示 3 位，防止数字/刷新区域越界
        if (remain < -999) remain = -999;
        if (remain > 9999) remain = 9999;
        DrawLEDFixed(hdc, cx + DpiScale(COUNTER_DIGIT_X), cy - DpiScale(4), remain, 4, FALSE);
        cy += rowStep;
    }
}

static void PaintTimer(HDC hdc, Board* b, int winW) {
    DWORD elapsed = b->elapsed_ms;
    // 菜单/对话框打开期间计时暂停，显示冻结在暂停时的值
    if (b->started && !b->over && g_timerPauseDepth == 0)
        elapsed = GetTickCount() - b->start_tick;
    DWORD sec = elapsed / 1000; if (sec > 9999) sec = 9999;
    wchar_t buf[16]; FormatFixed(buf, (int)sec, 4, FALSE);
    int len = (int)wcslen(buf);
    int cw = DpiScale(LED_CHAR_W), chh = DpiScale(LED_CHAR_H);
    int totalW = len * cw;
    int x = winW - DpiScale(BOARD_MARGIN) - totalW;
    int y = GetFaceBtnY() + DpiScale(4);
    for (int i=0;i<len;i++) {
        wchar_t ch = buf[i];
        int sx, sy;
        if (ch == L'-') { sx = SPR_LED_MINUS_X; sy = SPR_LED_ROW2_Y; }
        else if (ch >= L'0' && ch <= L'9') {
            int d = ch - L'0';
            if (d <= 7) { sx = SPR_LED_X0 + d*SPR_LED_STEP; sy = SPR_LED_Y; }
            else        { sx = SPR_LED_8_X + (d-8)*SPR_LED_STEP; sy = SPR_LED_ROW2_Y; }
        } else continue;
        DrawSpriteScaled(hdc, sx, sy, SPR_LED_W, SPR_LED_H,
                         x + i*cw, y, cw, chh);
    }
}

// 后台缓冲：整局复用，避免每次 WM_PAINT 都创建/销毁位图与 DC
static void DestroyBackBuffer(void) {
    if (g_backDC) {
        if (g_backOld) SelectObject(g_backDC, g_backOld);
        DeleteDC(g_backDC);
        g_backDC = NULL;
    }
    if (g_backBmp) { DeleteObject(g_backBmp); g_backBmp = NULL; }
    g_backOld = NULL;
    g_backW = g_backH = 0;
}

static BOOL EnsureBackBuffer(HDC hdc, int w, int h) {
    if (g_backDC && g_backW == w && g_backH == h) return TRUE;
    DestroyBackBuffer();
    if (w <= 0 || h <= 0) return FALSE;
    g_backDC = CreateCompatibleDC(hdc);
    if (!g_backDC) return FALSE;
    g_backBmp = CreateCompatibleBitmap(hdc, w, h);
    if (!g_backBmp) { DeleteDC(g_backDC); g_backDC = NULL; return FALSE; }
    g_backOld = (HBITMAP)SelectObject(g_backDC, g_backBmp);
    SetStretchBltMode(g_backDC, COLORONCOLOR);
    g_backW = w; g_backH = h;
    return TRUE;
}

// 只失效需要重绘的小区域，快速右键时不再整窗重绘
static void InvalidateFaceButton(HWND hwnd) {
    RECT rc; GetClientRect(hwnd, &rc);
    int fx = GetFaceBtnX(rc.right), fy = GetFaceBtnY();
    int pad = DpiScale(2);
    RECT r = { fx-pad, fy-pad,
               fx + DpiScale(FACE_BTN_W) + pad,
               fy + DpiScale(FACE_BTN_H) + pad };
    InvalidateRect(hwnd, &r, FALSE);
}

static void InvalidateCounterArea(HWND hwnd) {
    RECT r = { DpiScale(BOARD_MARGIN), DpiScale(BOARD_MARGIN),
               DpiScale(BOARD_MARGIN + 8 + COUNTER_DIGIT_X + 6*LED_CHAR_W + 4),
               DpiScale(BOARD_MARGIN + TOP_PANEL_H) };
    InvalidateRect(hwnd, &r, FALSE);
}

static void InvalidateTimerArea(HWND hwnd) {
    RECT rc; GetClientRect(hwnd, &rc);
    int pad = DpiScale(2);
    int cw = DpiScale(LED_CHAR_W);
    int x = rc.right - DpiScale(BOARD_MARGIN) - 4*cw;
    int y = GetFaceBtnY() + DpiScale(4);
    RECT r = { x-pad, y-pad, x + 4*cw + pad, y + DpiScale(LED_CHAR_H) + pad };
    InvalidateRect(hwnd, &r, FALSE);
}

// 滚动/换局时需要重绘整个视口
static void InvalidateBoardArea(HWND hwnd) {
    RECT view; GetBoardViewRect(hwnd, &view);
    if (view.right > view.left && view.bottom > view.top)
        InvalidateRect(hwnd, &view, FALSE);
}

static void InvalidateCellArea(HWND hwnd, int x, int y) {
    if (!inBounds(&g_board, x, y)) return;
    RECT view; GetBoardViewRect(hwnd, &view);
    int ox, oy; GetBoardOrigin(hwnd, &g_board, &ox, &oy);
    int cs = GetCellSize(&g_board);
    RECT r = { ox + x*cs, oy + y*cs, ox + (x+1)*cs, oy + (y+1)*cs };
    RECT inter;
    if (IntersectRect(&inter, &r, &view))
        InvalidateRect(hwnd, &r, FALSE);
}

// 把整个界面画到 memDC（后台缓冲或测试用的离屏 DC）。
// 棋盘格子被裁剪在可滚动视口内，顶部面板保持固定。
static void RenderBoard(HDC memDC, HWND hwnd, Board* b, const RECT* clip, int winW) {
    FillRect(memDC, clip, g_brWindow);

    int m = DpiScale(BOARD_MARGIN);
    RECT topPanel = { m, m, winW-m, m + DpiScale(TOP_PANEL_H) };
    if (topPanel.right > topPanel.left && topPanel.bottom > topPanel.top)
        FrameRect(memDC, &topPanel, (HBRUSH)GetStockObject(GRAY_BRUSH));

    RECT boardPanel; GetBoardPanelRect(hwnd, &boardPanel);
    if (boardPanel.right > boardPanel.left && boardPanel.bottom > boardPanel.top)
        FrameRect(memDC, &boardPanel, (HBRUSH)GetStockObject(GRAY_BRUSH));

    int x0, y0, x1, y1, ox, oy;
    if (GetVisibleCellRange(hwnd, b, clip, &x0, &y0, &x1, &y1, &ox, &oy)) {
        RECT view; GetBoardViewRect(hwnd, &view);
        int cs = GetCellSize(b);

        // 只允许在视口内绘制，避免滚动到边缘的格子盖住外框/顶部面板
        int saved = SaveDC(memDC);
        IntersectClipRect(memDC, view.left, view.top, view.right, view.bottom);

        for (int y=y0;y<=y1;y++) for (int x=x0;x<=x1;x++) {
            Cell* c = &b->cells[idx(b,x,y)];
            RECT r = { ox+x*cs, oy+y*cs, ox+(x+1)*cs, oy+(y+1)*cs };

            // 底
            if (!c->opened) {
                DrawSpriteScaled(memDC, SPR_VAL_BLANK_X, SPR_VAL_ROW2_Y, SPR_VAL_W, SPR_VAL_H,
                                 r.left, r.top, cs, cs);
            } else {
                FillRect(memDC, &r, g_brCell);
            }

            // 已翻开且非雷：显示值
            if (c->opened && !c->is_mine) {
                int sx, sy, sw, sh;
                if (GetDisplaySprite(&c->display, &sx, &sy, &sw, &sh))
                    DrawSpriteScaled(memDC, sx, sy, sw, sh, r.left, r.top, cs, cs);
            }

            // 已翻开的雷（踩中的）：爆炸贴图
            if (c->opened && c->is_mine) {
                int mine_x;
                switch (c->mine_type) {
                    case MINE_POS_REAL: mine_x = SPR_MINE_POS_REAL_BOOM_X; break;
                    case MINE_NEG_REAL: mine_x = SPR_MINE_NEG_REAL_BOOM_X; break;
                    case MINE_POS_IMAG: mine_x = SPR_MINE_POS_IMAG_BOOM_X; break;
                    case MINE_NEG_IMAG: mine_x = SPR_MINE_NEG_IMAG_BOOM_X; break;
                    default: mine_x = SPR_MINE_POS_REAL_BOOM_X; break;
                }
                DrawSpriteScaled(memDC, mine_x, SPR_MINE_Y, SPR_MINE_W, SPR_MINE_H, r.left, r.top, cs, cs);
            }
            // 未翻开的真雷、且没插旗：画雷的“未开”贴图
            else if (b->over && c->is_mine && !c->opened && c->flag_type == FLAG_NONE) {
                int mine_x;
                switch (c->mine_type) {
                    case MINE_POS_REAL: mine_x = SPR_MINE_POS_REAL_OPEN_X; break;
                    case MINE_NEG_REAL: mine_x = SPR_MINE_NEG_REAL_OPEN_X; break;
                    case MINE_POS_IMAG: mine_x = SPR_MINE_POS_IMAG_OPEN_X; break;
                    case MINE_NEG_IMAG: mine_x = SPR_MINE_NEG_IMAG_OPEN_X; break;
                    default: mine_x = SPR_MINE_POS_REAL_OPEN_X; break;
                }
                DrawSpriteScaled(memDC, mine_x, SPR_MINE_Y, SPR_MINE_W, SPR_MINE_H, r.left, r.top, cs, cs);
            }
            // 未翻开、插错旗的非雷：画错误叉
            else if (b->over && !c->is_mine && c->flag_type != FLAG_NONE && !c->opened) {
                int wrong_x;
                switch (c->flag_type) {
                    case FLAG_POS_REAL: wrong_x = SPR_MINE_POS_REAL_WRONG_X; break;
                    case FLAG_NEG_REAL: wrong_x = SPR_MINE_NEG_REAL_WRONG_X; break;
                    case FLAG_POS_IMAG: wrong_x = SPR_MINE_POS_IMAG_WRONG_X; break;
                    case FLAG_NEG_IMAG: wrong_x = SPR_MINE_NEG_IMAG_WRONG_X; break;
                    default: wrong_x = SPR_MINE_POS_REAL_WRONG_X; break;
                }
                DrawSpriteScaled(memDC, wrong_x, SPR_MINE_Y, SPR_MINE_W, SPR_MINE_H, r.left, r.top, cs, cs);
            }

            // 旗帜绘制：
            //   未结束：所有未翻开、有旗的格子都画旗
            //   已结束：只有真雷上的旗保留，非雷上的旗已被错误叉代替
            if (c->flag_type != FLAG_NONE && !c->opened) {
                if (!b->over || c->is_mine) {
                    int flag_x;
                    switch (c->flag_type) {
                        case FLAG_POS_REAL: flag_x = SPR_MINE_POS_REAL_MARK_X; break;
                        case FLAG_NEG_REAL: flag_x = SPR_MINE_NEG_REAL_MARK_X; break;
                        case FLAG_POS_IMAG: flag_x = SPR_MINE_POS_IMAG_MARK_X; break;
                        case FLAG_NEG_IMAG: flag_x = SPR_MINE_NEG_IMAG_MARK_X; break;
                        default: flag_x = SPR_MINE_POS_REAL_MARK_X; break;
                    }
                    int flag_y = (c->flag_type == FLAG_POS_REAL) ? SPR_VAL_ROW2_Y : SPR_MINE_Y;
                    DrawSpriteScaled(memDC, flag_x, flag_y, SPR_MINE_W, SPR_MINE_H, r.left, r.top, cs, cs);
                }
            }

            FrameRect(memDC, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
        RestoreDC(memDC, saved);
    }

    PaintFace(memDC, g_faceState, winW);
    PaintCounter(memDC, b);
    PaintTimer(memDC, b, winW);
}

static void PaintBoard(HWND hwnd, Board* b) {
    PAINTSTRUCT ps; HDC hdc = BeginPaint(hwnd, &ps);
    RECT rc; GetClientRect(hwnd, &rc);

    RECT clip = ps.rcPaint;
    if (clip.left < 0) clip.left = 0;
    if (clip.top < 0) clip.top = 0;
    if (clip.right > rc.right) clip.right = rc.right;
    if (clip.bottom > rc.bottom) clip.bottom = rc.bottom;
    int clipW = clip.right - clip.left;
    int clipH = clip.bottom - clip.top;
    if (clipW <= 0 || clipH <= 0 || !EnsureBackBuffer(hdc, rc.right, rc.bottom)) {
        EndPaint(hwnd, &ps);
        return;
    }

    RenderBoard(g_backDC, hwnd, b, &clip, rc.right);

    BitBlt(hdc, clip.left, clip.top, clipW, clipH, g_backDC, clip.left, clip.top, SRCCOPY);
    EndPaint(hwnd, &ps);
}

// ============================================================
// 自动调整窗口大小
// ============================================================
static void ResizeWindowForBoard(HWND hwnd, Board* b) {
    g_scrollX = g_scrollY = 0;

    if (IsZoomed(hwnd)) {
        // 最大化时不要改窗口大小，只更新滚动范围
        UpdateScrollBars(hwnd);
        InvalidateRect(hwnd, NULL, FALSE);
        return;
    }

    int cs = GetCellSize(b);
    int boardW = b->width * cs;
    int boardH = b->height * cs;
    int clientW = boardW + 2*(DpiScale(BOARD_MARGIN) + DpiScale(BOARD_PAD_X));
    int clientH = DpiScale(TOP_PANEL_H) + DpiScale(8) + 2*DpiScale(BOARD_PAD_Y)
                + boardH + 2*DpiScale(BOARD_MARGIN);
    // 给滚动条预留空间：即使出现滚动条，顶部面板也放得下
    int minW = DpiScale(MIN_CLIENT_W) + ScrollBarWidth();
    int minH = DpiScale(MIN_CLIENT_H) + ScrollBarHeight();
    if (clientW < minW) clientW = minW;
    if (clientH < minH) clientH = minH;

    RECT rc = { 0, 0, clientW, clientH };
    AdjustWindowRectForDpi(&rc, WS_OVERLAPPEDWINDOW, TRUE, g_dpi);
    int winW = rc.right - rc.left, winH = rc.bottom - rc.top;

    // 不超过当前显示器工作区；放不下时靠滚动条浏览
    RECT work; GetWorkArea(hwnd, &work);
    int maxW = work.right - work.left;
    int maxH = work.bottom - work.top;
    if (winW > maxW) winW = maxW;
    if (winH > maxH) winH = maxH;

    // 先隐藏滚动条，让客户区恢复完整，避免因残留滚动条把窗口算小
    ShowScrollBar(hwnd, SB_BOTH, FALSE);

    RECT wr; GetWindowRect(hwnd, &wr);
    int x = wr.left, y = wr.top;
    if (x + winW > work.right)  x = work.right - winW;
    if (y + winH > work.bottom) y = work.bottom - winH;
    if (x < work.left) x = work.left;
    if (y < work.top)  y = work.top;

    SetWindowPos(hwnd, NULL, x, y, winW, winH, SWP_NOZORDER | SWP_NOACTIVATE);
    // SetWindowPos 期间 WM_SIZE 可能按“旧客户区”重新显示滚动条；
    // 先清掉再按新客户区重新判断，避免小棋盘缩放后残留滚动条。
    ShowScrollBar(hwnd, SB_BOTH, FALSE);
    UpdateScrollBars(hwnd);
    InvalidateRect(hwnd, NULL, FALSE);
}

// ============================================================
// 计时暂停：菜单/对话框打开期间不计时
// 用嵌套深度而不是布尔值，菜单里再弹对话框也不会提前恢复。
// ============================================================
static BOOL PauseGameTimer(Board* b) {
    if (!b->started || b->over) return FALSE;
    if (g_timerPauseDepth == 0)
        b->elapsed_ms = GetTickCount() - b->start_tick;
    g_timerPauseDepth++;
    return TRUE;
}

static void ResumeGameTimer(Board* b) {
    if (g_timerPauseDepth <= 0) return;
    if (--g_timerPauseDepth == 0) {
        if (b->started && !b->over)
            b->start_tick = GetTickCount() - b->elapsed_ms;
    }
}

// ============================================================
// 注册表
// ============================================================
static const wchar_t* REG_PATH = L"Software\\Complexweeper";
static void LoadHighScores(HighScores* s) {
    s->time_beginner = s->time_intermediate = s->time_expert = 0;
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, KEY_READ, &hKey) != ERROR_SUCCESS) return;
    DWORD sz = sizeof(DWORD), type = 0;
    RegQueryValueExW(hKey, L"Beginner", NULL, &type, (LPBYTE)&s->time_beginner, &sz);
    RegQueryValueExW(hKey, L"Intermediate", NULL, &type, (LPBYTE)&s->time_intermediate, &sz);
    RegQueryValueExW(hKey, L"Expert", NULL, &type, (LPBYTE)&s->time_expert, &sz);
    RegCloseKey(hKey);
}
static void SaveHighScores(HighScores* s) {
    HKEY hKey; DWORD disp;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, NULL, REG_OPTION_NON_VOLATILE,
                        KEY_WRITE, NULL, &hKey, &disp) != ERROR_SUCCESS) return;
    RegSetValueExW(hKey, L"Beginner", 0, REG_DWORD, (const BYTE*)&s->time_beginner, sizeof(DWORD));
    RegSetValueExW(hKey, L"Intermediate", 0, REG_DWORD, (const BYTE*)&s->time_intermediate, sizeof(DWORD));
    RegSetValueExW(hKey, L"Expert", 0, REG_DWORD, (const BYTE*)&s->time_expert, sizeof(DWORD));
    RegCloseKey(hKey);
}

// 胜利时登记最高分（只统计三个预设难度；自定义局不参与）。
// 原先 SaveHighScores 从未被调用，所以“最高分纪录”永远是空记录。
static void RecordWin(const Board* b) {
    if (!b->win || b->preset < 1 || b->preset > 3) return;
    DWORD sec = b->elapsed_ms / 1000;
    if (sec == 0) sec = 1;              // 0 在界面里表示“暂无记录”
    DWORD* best = NULL;
    switch (b->preset) {
        case 1: best = &g_scores.time_beginner; break;
        case 2: best = &g_scores.time_intermediate; break;
        default: best = &g_scores.time_expert; break;
    }
    if (*best != 0 && sec >= *best) return;
    *best = sec;
    SaveHighScores(&g_scores);
}

// ============================================================
// 手写对话框
// 控件先用 0 尺寸创建，再按当前 DPI 统一布局；WM_DPICHANGED 时重新布局。
// ============================================================
static HWND MakeStatic(HWND hDlg, int id, const wchar_t* text) {
    return CreateWindowExW(0, L"STATIC", text,
        WS_CHILD|WS_VISIBLE|SS_LEFT,
        0, 0, 0, 0, hDlg, (HMENU)(INT_PTR)id, g_hInst, NULL);
}
static HWND MakeEdit(HWND hDlg, int id, const wchar_t* text) {
    HWND c = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", text,
        WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_NUMBER,
        0, 0, 0, 0, hDlg, (HMENU)(INT_PTR)id, g_hInst, NULL);
    // 限制长度：否则把 15 位数字粘进编辑框会让 _wtoi 溢出（未定义行为）
    SendMessageW(c, EM_SETLIMITTEXT, 4, 0);
    return c;
}
static HWND MakeButton(HWND hDlg, int id, const wchar_t* text) {
    return CreateWindowExW(0, L"BUTTON", text,
        WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
        0, 0, 0, 0, hDlg, (HMENU)(INT_PTR)id, g_hInst, NULL);
}

static const wchar_t* DLG_FONT_PROP = L"CSDlgFont";

static BOOL CALLBACK ApplyFontProc(HWND c, LPARAM lp) {
    SendMessageW(c, WM_SETFONT, (WPARAM)lp, TRUE);
    return TRUE;
}

// 对话框按自身 DPI 创建/更新字体；字体句柄挂在窗口属性上，销毁窗口时释放
static void UpdateDialogFont(HWND hDlg, int dpi) {
    HFONT old = (HFONT)RemovePropW(hDlg, DLG_FONT_PROP);
    HFONT f = CreateUiFontForDpi(dpi);
    if (f) {
        SetPropW(hDlg, DLG_FONT_PROP, (HANDLE)f);
        EnumChildWindows(hDlg, ApplyFontProc, (LPARAM)f);
    }
    // 先让控件换上新字体，再删除旧字体
    if (old) DeleteObject(old);
}
static void FreeDialogFont(HWND hDlg) {
    HFONT f = (HFONT)RemovePropW(hDlg, DLG_FONT_PROP);
    if (f) DeleteObject(f);
}

static void MoveCtrl(HWND hDlg, int id, int dpi, int x, int y, int w, int h) {
    HWND c = GetDlgItem(hDlg, id);
    if (!c) return;
    SetWindowPos(c, NULL,
        DpiScaleEx(x, dpi), DpiScaleEx(y, dpi),
        DpiScaleEx(w, dpi), DpiScaleEx(h, dpi),
        SWP_NOZORDER | SWP_NOACTIVATE);
}

// 96 DPI 下的逻辑布局：客户区 300×280
static void LayoutCustomDialog(HWND hDlg, int dpi) {
    MoveCtrl(hDlg, IDC_ST_H,       dpi,  10,  12,  60, 18);
    MoveCtrl(hDlg, IDC_EDIT_H,     dpi,  75,  10,  60, 22);
    MoveCtrl(hDlg, IDC_ST_HINT_H,  dpi, 145,  12,  80, 18);

    MoveCtrl(hDlg, IDC_ST_W,       dpi,  10,  42,  60, 18);
    MoveCtrl(hDlg, IDC_EDIT_W,     dpi,  75,  40,  60, 22);
    MoveCtrl(hDlg, IDC_ST_HINT_W,  dpi, 145,  42,  80, 18);

    MoveCtrl(hDlg, IDC_ST_M1,      dpi,  10,  72,  60, 18);
    MoveCtrl(hDlg, IDC_EDIT_M1,    dpi,  75,  70,  60, 22);
    MoveCtrl(hDlg, IDC_ST_M2,      dpi, 145,  72,  50, 18);
    MoveCtrl(hDlg, IDC_EDIT_M2,    dpi, 200,  70,  60, 22);

    MoveCtrl(hDlg, IDC_ST_M3,      dpi,  10, 102,  60, 18);
    MoveCtrl(hDlg, IDC_EDIT_M3,    dpi,  75, 100,  60, 22);
    MoveCtrl(hDlg, IDC_ST_M4,      dpi, 145, 102,  50, 18);
    MoveCtrl(hDlg, IDC_EDIT_M4,    dpi, 200, 100,  60, 22);

    MoveCtrl(hDlg, IDC_BTN_AVG,    dpi,  10, 132, 100, 24);
    MoveCtrl(hDlg, IDC_BTN_OK,     dpi,  80, 166,  60, 24);
    MoveCtrl(hDlg, IDC_BTN_CANCEL, dpi, 150, 166,  60, 24);
    MoveCtrl(hDlg, IDC_ERR,        dpi,  10, 196, 250, 18);
}

static void LayoutAboutDialog(HWND hDlg, int dpi) {
    MoveCtrl(hDlg, IDC_ST_ABOUT, dpi,  15,  15, 300, 110);
    MoveCtrl(hDlg, IDOK,         dpi, 130, 140,  70,  26);
}

static void LayoutHighScoreDialog(HWND hDlg, int dpi) {
    MoveCtrl(hDlg, IDC_ST_SCORE, dpi,  20,  20, 250, 90);
    MoveCtrl(hDlg, IDOK,         dpi, 110, 120,  70, 26);
}

static void DialogDpiChanged(HWND hDlg, WPARAM wParam, LPARAM lParam, void (*layout)(HWND, int)) {
    RECT* r = (RECT*)lParam;
    if (r) {
        SetWindowPos(hDlg, NULL, r->left, r->top,
                     r->right - r->left, r->bottom - r->top,
                     SWP_NOZORDER | SWP_NOACTIVATE);
    }
    int dpi = (int)LOWORD(wParam);
    if (dpi > 0) {
        UpdateDialogFont(hDlg, dpi);
        layout(hDlg, dpi);
    }
}

static LRESULT CALLBACK CustomDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            int dpi = (int)(INT_PTR)((CREATESTRUCTW*)lParam)->lpCreateParams;
            if (dpi <= 0) dpi = GetWindowDpi(hDlg);

            MakeStatic(hDlg, IDC_ST_H,      L"高度(H):");
            MakeEdit  (hDlg, IDC_EDIT_H,    L"9");
            MakeStatic(hDlg, IDC_ST_HINT_H, L"9 - 30 行");

            MakeStatic(hDlg, IDC_ST_W,      L"宽度(W):");
            MakeEdit  (hDlg, IDC_EDIT_W,    L"9");
            MakeStatic(hDlg, IDC_ST_HINT_W, L"9 - 40 列");

            MakeStatic(hDlg, IDC_ST_M1,     L"正实雷:");
            MakeEdit  (hDlg, IDC_EDIT_M1,   L"5");
            MakeStatic(hDlg, IDC_ST_M2,     L"负实雷:");
            MakeEdit  (hDlg, IDC_EDIT_M2,   L"5");

            MakeStatic(hDlg, IDC_ST_M3,     L"正虚雷:");
            MakeEdit  (hDlg, IDC_EDIT_M3,   L"5");
            MakeStatic(hDlg, IDC_ST_M4,     L"负虚雷:");
            MakeEdit  (hDlg, IDC_EDIT_M4,   L"5");

            MakeButton(hDlg, IDC_BTN_AVG,    L"按合计均分");
            MakeButton(hDlg, IDC_BTN_OK,     L"确定");
            MakeButton(hDlg, IDC_BTN_CANCEL, L"取消");
            MakeStatic(hDlg, IDC_ERR,        L"");

            UpdateDialogFont(hDlg, dpi);
            LayoutCustomDialog(hDlg, dpi);
            SetFocus(GetDlgItem(hDlg, IDC_EDIT_H));
            return 0;
        }
        case WM_DPICHANGED:
            DialogDpiChanged(hDlg, wParam, lParam, LayoutCustomDialog);
            return 0;
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDOK:              // 回车（由模态循环转成 IDOK）
                case IDC_BTN_OK: {
                    wchar_t buf[16];
                    GetDlgItemTextW(hDlg, IDC_EDIT_H, buf, 16); int h = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_W, buf, 16); int w = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M1, buf, 16); int m1 = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M2, buf, 16); int m2 = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M3, buf, 16); int m3 = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M4, buf, 16); int m4 = _wtoi(buf);
                    int total = m1+m2+m3+m4;
                    if (h < MIN_ROWS || h > MAX_ROWS) {
                        SetDlgItemTextW(hDlg, IDC_ERR, L"高度必须在 9 到 30 行之间");
                        return 0;
                    }
                    if (w < MIN_COLS || w > MAX_COLS) {
                        SetDlgItemTextW(hDlg, IDC_ERR, L"宽度必须在 9 到 40 列之间");
                        return 0;
                    }
                    if (total == 0) {
                        SetDlgItemTextW(hDlg, IDC_ERR, L"合计不能为 0");
                        return 0;
                    }
                    if (total > w*h - 9) {
                        SetDlgItemTextW(hDlg, IDC_ERR, L"雷数太多，放不下");
                        return 0;
                    }
                    InitGame(&g_board, w, h, m1, m2, m3, m4);
                    NewGame(&g_board);
                    g_dlgOK = TRUE;
                    DestroyWindow(hDlg);
                    return 0;
                }
                case IDC_BTN_AVG: {
                    wchar_t buf[16];
                    GetDlgItemTextW(hDlg, IDC_EDIT_M1, buf, 16); int m1 = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M2, buf, 16); int m2 = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M3, buf, 16); int m3 = _wtoi(buf);
                    GetDlgItemTextW(hDlg, IDC_EDIT_M4, buf, 16); int m4 = _wtoi(buf);
                    int total = m1+m2+m3+m4;
                    int avg = total/4, rem = total%4;
                    swprintf(buf, 16, L"%d", avg + (rem>0?1:0)); SetDlgItemTextW(hDlg, IDC_EDIT_M1, buf);
                    swprintf(buf, 16, L"%d", avg + (rem>1?1:0)); SetDlgItemTextW(hDlg, IDC_EDIT_M2, buf);
                    swprintf(buf, 16, L"%d", avg + (rem>2?1:0)); SetDlgItemTextW(hDlg, IDC_EDIT_M3, buf);
                    swprintf(buf, 16, L"%d", avg);              SetDlgItemTextW(hDlg, IDC_EDIT_M4, buf);
                    SetDlgItemTextW(hDlg, IDC_ERR, L"");
                    return 0;
                }
                case IDCANCEL:          // Esc
                case IDC_BTN_CANCEL:
                    g_dlgOK = FALSE;
                    DestroyWindow(hDlg);
                    return 0;
            }
            return 0;
        }
        case WM_DESTROY:
            FreeDialogFont(hDlg);
            return 0;
        case WM_CLOSE:
            g_dlgOK = FALSE;
            DestroyWindow(hDlg);
            return 0;
    }
    return DefWindowProcW(hDlg, msg, wParam, lParam);
}

static LRESULT CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            int dpi = (int)(INT_PTR)((CREATESTRUCTW*)lParam)->lpCreateParams;
            if (dpi <= 0) dpi = GetWindowDpi(hDlg);
            wchar_t buf[256];
            swprintf(buf, 256,
                L"复扫雷 Complexweeper %s\n"
                L"copyright◎skamerr\n"
                L"全是吃干饭的大肥鱼ds帮我vibe的\n"
                L"复数扫雷：正实雷/负实雷/正虚雷/负虚雷\n"
                L"灵感来源于b站up主青月晓的复扫雷",
                APP_VERSION);
            CreateWindowExW(0, L"STATIC", buf,
                WS_CHILD|WS_VISIBLE|SS_LEFT,
                0, 0, 0, 0, hDlg, (HMENU)(INT_PTR)IDC_ST_ABOUT, g_hInst, NULL);
            MakeButton(hDlg, IDOK, L"确定");
            UpdateDialogFont(hDlg, dpi);
            LayoutAboutDialog(hDlg, dpi);
            SetFocus(GetDlgItem(hDlg, IDOK));
            return 0;
        }
        case WM_DPICHANGED:
            DialogDpiChanged(hDlg, wParam, lParam, LayoutAboutDialog);
            return 0;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) { DestroyWindow(hDlg); return 0; }
            return 0;
        case WM_DESTROY:
            FreeDialogFont(hDlg);
            return 0;
        case WM_CLOSE: DestroyWindow(hDlg); return 0;
    }
    return DefWindowProcW(hDlg, msg, wParam, lParam);
}

static LRESULT CALLBACK HighScoreDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            int dpi = (int)(INT_PTR)((CREATESTRUCTW*)lParam)->lpCreateParams;
            if (dpi <= 0) dpi = GetWindowDpi(hDlg);
            wchar_t buf[256];
            const wchar_t* p1 = g_scores.time_beginner     ? L"" : L"———";
            const wchar_t* p2 = g_scores.time_intermediate ? L"" : L"———";
            const wchar_t* p3 = g_scores.time_expert       ? L"" : L"———";
            swprintf(buf, 256,
                L"初级：%u 秒 %s\n中级：%u 秒 %s\n高级：%u 秒 %s",
                g_scores.time_beginner, p1,
                g_scores.time_intermediate, p2,
                g_scores.time_expert, p3);
            CreateWindowExW(0, L"STATIC", buf,
                WS_CHILD|WS_VISIBLE|SS_LEFT,
                0, 0, 0, 0, hDlg, (HMENU)(INT_PTR)IDC_ST_SCORE, g_hInst, NULL);
            MakeButton(hDlg, IDOK, L"确定");
            UpdateDialogFont(hDlg, dpi);
            LayoutHighScoreDialog(hDlg, dpi);
            SetFocus(GetDlgItem(hDlg, IDOK));
            return 0;
        }
        case WM_DPICHANGED:
            DialogDpiChanged(hDlg, wParam, lParam, LayoutHighScoreDialog);
            return 0;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) { DestroyWindow(hDlg); return 0; }
            return 0;
        case WM_DESTROY:
            FreeDialogFont(hDlg);
            return 0;
        case WM_CLOSE: DestroyWindow(hDlg); return 0;
    }
    return DefWindowProcW(hDlg, msg, wParam, lParam);
}

static void ShowModalDialog(HWND parent, const wchar_t* cls, const wchar_t* title, int cx, int cy) {
    g_dlgOK = FALSE;

    int dpi = GetWindowDpi(parent);
    RECT rc = { 0, 0, DpiScaleEx(cx, dpi), DpiScaleEx(cy, dpi) };
    AdjustWindowRectForDpi(&rc, WS_POPUP | WS_CAPTION | WS_SYSMENU, FALSE, dpi);

    HWND hDlg = CreateWindowExW(
        WS_EX_DLGMODALFRAME,
        cls, title,
        WS_POPUP | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        parent, NULL, g_hInst, (LPVOID)(INT_PTR)dpi);
    if (!hDlg) return;

    RECT rp, rd;
    GetWindowRect(parent, &rp);
    GetWindowRect(hDlg, &rd);
    int w = rd.right - rd.left, h = rd.bottom - rd.top;
    int x = rp.left + (rp.right - rp.left - w) / 2;
    int y = rp.top  + (rp.bottom - rp.top - h) / 2;

    // 对话框不要跑出工作区
    RECT work; GetWorkArea(parent, &work);
    if (x + w > work.right) x = work.right - w;
    if (y + h > work.bottom) y = work.bottom - h;
    if (x < work.left) x = work.left;
    if (y < work.top) y = work.top;

    SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

    PauseGameTimer(&g_board);

    ShowWindow(hDlg, SW_SHOW);
    SetActiveWindow(hDlg);
    EnableWindow(parent, FALSE);

    MSG msg;
    while (IsWindow(hDlg)) {
        BOOL got = GetMessageW(&msg, NULL, 0, 0);
        if (got == 0) { PostQuitMessage((int)msg.wParam); break; }  // 主窗口被关闭，继续退出流程
        if (got == -1) break;
        if (msg.message == WM_KEYDOWN) {
            if (msg.wParam == VK_ESCAPE) {
                SendMessageW(hDlg, WM_CLOSE, 0, 0);
                continue;
            }
            if (msg.wParam == VK_RETURN) {
                SendMessageW(hDlg, WM_COMMAND, IDOK, 0);
                continue;
            }
        }
        if (!IsDialogMessageW(hDlg, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    ResumeGameTimer(&g_board);

    if (IsWindow(parent)) {
        EnableWindow(parent, TRUE);
        SetActiveWindow(parent);
    }
}

// ============================================================
// 菜单
// ============================================================
static HMENU BuildMenu(void) {
    HMENU hMenu = CreateMenu();
    HMENU hGame = CreatePopupMenu();
    AppendMenuW(hGame, MF_STRING, IDM_BEGINNER,     L"初级 9×9 · 10 雷");
    AppendMenuW(hGame, MF_STRING, IDM_INTERMEDIATE, L"中级 16×16 · 40 雷");
    AppendMenuW(hGame, MF_STRING, IDM_EXPERT,       L"高级 30×16 · 99 雷");
    AppendMenuW(hGame, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hGame, MF_STRING, IDM_CUSTOM,       L"自定义...");
    AppendMenuW(hGame, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hGame, MF_STRING, IDM_HIGHSCORE,    L"最高分纪录");
    AppendMenuW(hGame, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hGame, MF_STRING, IDM_EXIT,         L"退出");
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hGame, L"游戏");

    HMENU hZoom = CreatePopupMenu();
    AppendMenuW(hZoom, MF_STRING, IDM_ZOOM_100, L"100%");
    AppendMenuW(hZoom, MF_STRING, IDM_ZOOM_200, L"200%");
    AppendMenuW(hZoom, MF_STRING, IDM_ZOOM_300, L"300%");
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hZoom, L"缩放");

    HMENU hHelp = CreatePopupMenu();
    AppendMenuW(hHelp, MF_STRING, IDM_HOWTOPLAY, L"玩法与操作");
    AppendMenuW(hHelp, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hHelp, MF_STRING, IDM_ABOUT, L"关于");
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hHelp, L"帮助");
    return hMenu;
}

// ============================================================
// 主窗口
// ============================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            SetTimer(hwnd, IDT_TIMER, 100, NULL);
            return 0;

        case WM_TIMER:
            if (wParam == IDT_TIMER) {
                if (g_timerPauseDepth > 0) return 0;   // 菜单/对话框打开期间冻结
                if (g_board.started && !g_board.over) {
                    DWORD oldSec = g_board.elapsed_ms / 1000;
                    g_board.elapsed_ms = GetTickCount() - g_board.start_tick;
                    if (g_board.elapsed_ms/1000 != oldSec) InvalidateTimerArea(hwnd);
                }
            }
            return 0;

        case WM_ENTERMENULOOP: PauseGameTimer(&g_board); return 0;
        case WM_EXITMENULOOP:  ResumeGameTimer(&g_board); return 0;

        case WM_GETMINMAXINFO: {
            // 最小窗口：保证顶部面板放得下，并且即使在滚动条出现时也留出可视棋盘
            MINMAXINFO* mmi = (MINMAXINFO*)lParam;
            RECT rc = { 0, 0,
                        DpiScale(MIN_CLIENT_W) + ScrollBarWidth(),
                        DpiScale(MIN_CLIENT_H) + ScrollBarHeight() };
            AdjustWindowRectForDpi(&rc, WS_OVERLAPPEDWINDOW, TRUE, g_dpi);
            mmi->ptMinTrackSize.x = rc.right - rc.left;
            mmi->ptMinTrackSize.y = rc.bottom - rc.top;
            return 0;
        }

        case WM_DPICHANGED: {
            int oldDpi = g_dpi;
            int newDpi = (int)LOWORD(wParam);
            if (newDpi > 0 && newDpi != g_dpi) {
                g_dpi = newDpi;
                if (oldDpi > 0) {
                    // 保持大致相同的可视位置
                    g_scrollX = MulDiv(g_scrollX, g_dpi, oldDpi);
                    g_scrollY = MulDiv(g_scrollY, g_dpi, oldDpi);
                }
            }
            RECT* r = (RECT*)lParam;
            if (r) {
                SetWindowPos(hwnd, NULL, r->left, r->top,
                             r->right - r->left, r->bottom - r->top,
                             SWP_NOZORDER | SWP_NOACTIVATE);
            }
            UpdateScrollBars(hwnd);
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        }

        case WM_ERASEBKGND: return 1;
        case WM_PAINT: PaintBoard(hwnd, &g_board); return 0;
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED) {
                UpdateScrollBars(hwnd);
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;

        case WM_HSCROLL: {
            int cs = GetCellSize(&g_board);
            RECT view; GetBoardViewRect(hwnd, &view);
            int page = (view.right - view.left) - cs;
            if (page < cs) page = cs;
            int pos = g_scrollX;
            switch (LOWORD(wParam)) {
                case SB_LINELEFT:  pos -= cs; break;
                case SB_LINERIGHT: pos += cs; break;
                case SB_PAGELEFT:  pos -= page; break;
                case SB_PAGERIGHT: pos += page; break;
                case SB_THUMBPOSITION:
                case SB_THUMBTRACK: {
                    SCROLLINFO si; memset(&si, 0, sizeof(si));
                    si.cbSize = sizeof(si); si.fMask = SIF_TRACKPOS;
                    GetScrollInfo(hwnd, SB_HORZ, &si);
                    pos = si.nTrackPos;
                    break;
                }
                case SB_LEFT:  pos = 0; break;
                case SB_RIGHT: pos = INT_MAX; break;
                default: return 0;
            }
            ScrollBoard(hwnd, pos - g_scrollX, 0);
            return 0;
        }

        case WM_VSCROLL: {
            int cs = GetCellSize(&g_board);
            RECT view; GetBoardViewRect(hwnd, &view);
            int page = (view.bottom - view.top) - cs;
            if (page < cs) page = cs;
            int pos = g_scrollY;
            switch (LOWORD(wParam)) {
                case SB_LINEUP:   pos -= cs; break;
                case SB_LINEDOWN: pos += cs; break;
                case SB_PAGEUP:   pos -= page; break;
                case SB_PAGEDOWN: pos += page; break;
                case SB_THUMBPOSITION:
                case SB_THUMBTRACK: {
                    SCROLLINFO si; memset(&si, 0, sizeof(si));
                    si.cbSize = sizeof(si); si.fMask = SIF_TRACKPOS;
                    GetScrollInfo(hwnd, SB_VERT, &si);
                    pos = si.nTrackPos;
                    break;
                }
                case SB_TOP:    pos = 0; break;
                case SB_BOTTOM: pos = INT_MAX; break;
                default: return 0;
            }
            ScrollBoard(hwnd, 0, pos - g_scrollY);
            return 0;
        }

        case WM_MOUSEWHEEL: {
            static int wheelAccum = 0;
            wheelAccum += GET_WHEEL_DELTA_WPARAM(wParam);
            int lines = wheelAccum / WHEEL_DELTA;
            wheelAccum -= lines * WHEEL_DELTA;
            if (lines == 0) return 0;
            int cs = GetCellSize(&g_board);
            int step = cs * 3 * lines;
            if (GET_KEYSTATE_WPARAM(wParam) & MK_SHIFT)
                ScrollBoard(hwnd, -step, 0);
            else
                ScrollBoard(hwnd, 0, -step);
            return 0;
        }

        case WM_LBUTTONDOWN: {
            int mx = (short)LOWORD(lParam), my = (short)HIWORD(lParam);
            RECT rc; GetClientRect(hwnd, &rc);
            int fx = GetFaceBtnX(rc.right), fy = GetFaceBtnY();
            int fw = DpiScale(FACE_BTN_W), fh = DpiScale(FACE_BTN_H);
            if (mx>=fx && mx<fx+fw && my>=fy && my<fy+fh) {
                g_facePressing = TRUE;
                g_pressing = FALSE;
                g_faceState = FACE_PRESS;
                SetCapture(hwnd);
                InvalidateFaceButton(hwnd);
                return 0;
            }
            int gx, gy;
            if (!g_board.over && ClientToCell(hwnd, mx, my, &gx, &gy)) {
                g_pressing = TRUE;
                g_facePressing = FALSE;
                g_pressX = gx;
                g_pressY = gy;
                g_faceState = FACE_PRESS;
                SetCapture(hwnd);
                InvalidateFaceButton(hwnd);
            }
            return 0;
        }

        case WM_LBUTTONUP: {
            int mx = (short)LOWORD(lParam), my = (short)HIWORD(lParam);
            BOOL wasFace = g_facePressing, wasCell = g_pressing;
            g_facePressing = FALSE;
            g_pressing = FALSE;
            ReleaseCapture();

            RECT rc; GetClientRect(hwnd, &rc);
            int fx = GetFaceBtnX(rc.right), fy = GetFaceBtnY();
            int fw = DpiScale(FACE_BTN_W), fh = DpiScale(FACE_BTN_H);
            BOOL onFace = (mx>=fx && mx<fx+fw && my>=fy && my<fy+fh);

            if (wasFace) {
                if (onFace) {
                    NewGame(&g_board);
                    InvalidateRect(hwnd, NULL, FALSE);
                } else {
                    RestoreFaceState();
                    InvalidateFaceButton(hwnd);
                }
                return 0;
            }

            if (wasCell) {
                // 只有松开时仍在按下的那一格才翻开：拖到别处/窗口外松开视为取消，
                // 避免误点（也避免“按 A 松在 B，翻开 A”这种意外）。
                int gx, gy;
                BOOL sameCell = !g_board.over &&
                                ClientToCell(hwnd, mx, my, &gx, &gy) &&
                                gx == g_pressX && gy == g_pressY;
                RestoreFaceState();     // 先恢复，若踩雷/获胜 OnLose/OnWin 会再改成对应表情
                if (sameCell) {
                    if (!g_board.started) GenerateBoard(&g_board, g_pressX, g_pressY);
                    OpenCell(&g_board, g_pressX, g_pressY);
                    InvalidateBoardArea(hwnd);
                }
                InvalidateFaceButton(hwnd);
            }
            return 0;
        }

        case WM_CAPTURECHANGED:
            // 鼠标捕获被别处抢走（Alt+Tab、弹窗等）时取消按下状态，
            // 否则会卡在“按下”表情并保留过期的按下坐标。
            if (g_pressing || g_facePressing) {
                g_pressing = FALSE;
                g_facePressing = FALSE;
                RestoreFaceState();
                InvalidateFaceButton(hwnd);
            }
            return 0;

        case WM_LBUTTONDBLCLK: {
            int gx, gy;
            if (!ClientToCell(hwnd, LOWORD(lParam), HIWORD(lParam), &gx, &gy) || g_board.over) return 0;
            if (ChordCell(&g_board, gx, gy)) InvalidateBoardArea(hwnd);
            return 0;
        }

        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK: {
            // 快速右键时 Windows 会把第二次点击发成 WM_RBUTTONDBLCLK，
            // 两个消息都处理，右键插旗就不会漏掉了。
            int gx, gy;
            if (ClientToCell(hwnd, LOWORD(lParam), HIWORD(lParam), &gx, &gy)) {
                ToggleFlag(&g_board, gx, gy);
                InvalidateCellArea(hwnd, gx, gy);
                InvalidateCounterArea(hwnd);
            }
            return 0;
        }

        case WM_MBUTTONDOWN: {
            int gx, gy;
            g_chordPressed = ClientToCell(hwnd, LOWORD(lParam), HIWORD(lParam), &gx, &gy);
            if (g_chordPressed) {
                g_chordX = gx;
                g_chordY = gy;
            }
            return 0;
        }

        case WM_MBUTTONUP: {
            if (g_chordPressed) {
                g_chordPressed = FALSE;
                if (ChordCell(&g_board, g_chordX, g_chordY)) InvalidateBoardArea(hwnd);
            }
            return 0;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_BEGINNER:
                    StartPreset(&g_board, 1, 9, 9, 10);
                    NewGame(&g_board);
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_INTERMEDIATE:
                    StartPreset(&g_board, 2, 16, 16, 40);
                    NewGame(&g_board);
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_EXPERT:
                    StartPreset(&g_board, 3, 30, 16, 99);
                    NewGame(&g_board);
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_CUSTOM: {
                    ShowModalDialog(hwnd, DIALOG_CUSTOM, L"自定义雷区", 300, 280);
                    if (g_dlgOK) ResizeWindowForBoard(hwnd, &g_board);
                    break;
                }
                case IDM_ZOOM_100:
                    g_board.zoom = 100;
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_ZOOM_200:
                    g_board.zoom = 200;
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_ZOOM_300:
                    g_board.zoom = 300;
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_HIGHSCORE:
                    ShowModalDialog(hwnd, DIALOG_HIGHSCORE, L"最高分纪录", 290, 200);
                    break;
                case IDM_ABOUT:
                    ShowModalDialog(hwnd, DIALOG_ABOUT, L"关于", 330, 190);
                    break;
                case IDM_HOWTOPLAY:
                    PauseGameTimer(&g_board);
                    MessageBoxW(hwnd,
                        L"左键翻开，右键插旗（连点可切换四种旗）。\n"
                        L"双击或中键：在已翻开的格子上快速展开周围——\n"
                        L"该格周围的旗数必须等于雷数，否则不会展开。\n"
                        L"滚轮上下滚动棋盘，Shift+滚轮横向滚动。\n"
                        L"菜单/对话框打开期间计时暂停。\n"
                        L"数字是复数雷的模：k√n。",
                        L"玩法", MB_OK);
                    ResumeGameTimer(&g_board);
                    break;
                case IDM_EXIT: DestroyWindow(hwnd); break;
            }
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, IDT_TIMER);
            DestroyBackBuffer();
            if (g_hSpriteDC) {
                if (g_hSpriteOld) SelectObject(g_hSpriteDC, g_hSpriteOld);
                DeleteDC(g_hSpriteDC);
                g_hSpriteDC = NULL;
            }
            if (g_hSprite) { DeleteObject(g_hSprite); g_hSprite = NULL; }
            if (g_brWindow) { DeleteObject(g_brWindow); g_brWindow = NULL; }
            if (g_brCell) { DeleteObject(g_brCell); g_brCell = NULL; }
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// ============================================================
// 图标
// ============================================================
static HICON CreateIconFromSprite(HBITMAP hSprite, int sx, int sy, int sw, int sh) {
    HDC hdc = GetDC(NULL);

    HDC srcDC = CreateCompatibleDC(hdc);
    HBITMAP srcOld = (HBITMAP)SelectObject(srcDC, hSprite);

    HDC colorDC = CreateCompatibleDC(hdc);
    HBITMAP hColor = CreateCompatibleBitmap(hdc, sw, sh);
    HBITMAP colorOld = (HBITMAP)SelectObject(colorDC, hColor);
    BitBlt(colorDC, 0, 0, sw, sh, srcDC, sx, sy, SRCCOPY);

    HDC maskDC = CreateCompatibleDC(hdc);
    HBITMAP hMask = CreateBitmap(sw, sh, 1, 1, NULL);
    HBITMAP maskOld = (HBITMAP)SelectObject(maskDC, hMask);
    PatBlt(maskDC, 0, 0, sw, sh, BLACKNESS);

    ICONINFO ii = {0};
    ii.fIcon = TRUE;
    ii.hbmColor = hColor;
    ii.hbmMask  = hMask;
    HICON hIcon = CreateIconIndirect(&ii);

    SelectObject(srcDC, srcOld);
    SelectObject(colorDC, colorOld);
    SelectObject(maskDC, maskOld);
    DeleteDC(srcDC);
    DeleteDC(colorDC);
    DeleteDC(maskDC);
    DeleteObject(hColor);
    DeleteObject(hMask);
    ReleaseDC(NULL, hdc);

    return hIcon;
}

// ============================================================
// WinMain
// ============================================================
// 优先启用 Per-Monitor V2 DPI 感知（Win10 1703+），失败则退回系统 DPI 感知。
static void EnableDpiAwareness(void) {
    typedef BOOL (WINAPI *PFN_SetProcessDpiAwarenessContext)(HANDLE);
    PFN_SetProcessDpiAwarenessContext p =
        (PFN_SetProcessDpiAwarenessContext)(void*)GetProcAddress(User32Module(), "SetProcessDpiAwarenessContext");
    if (p && p((HANDLE)(INT_PTR)-4)) return;   // DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
    SetProcessDPIAware();
}

// sprite.bmp 相对 exe 所在目录查找：用相对路径时，从快捷方式/其他目录启动会找不到贴图。
static BOOL GetSpritePath(wchar_t* out, size_t cch) {
    DWORD n = GetModuleFileNameW(NULL, out, (DWORD)cch);
    if (n == 0 || n >= cch) return FALSE;
    wchar_t* slash = wcsrchr(out, L'\\');
    if (!slash) return FALSE;
    size_t dirLen = (size_t)(slash - out) + 1;
    const wchar_t* name = L"sprite.bmp";
    if (dirLen + wcslen(name) + 1 > cch) return FALSE;
    wcscpy(out + dirLen, name);
    return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmdLine, int nCmdShow) {
    (void)hPrev;
    g_hInst = hInst;
    (void)lpCmdLine;

    EnableDpiAwareness();
    g_dpi = GetSystemDpi();
    srand(GetTickCount());

    wchar_t spritePath[MAX_PATH];
    if (!GetSpritePath(spritePath, MAX_PATH)) wcscpy(spritePath, L"sprite.bmp");
    g_hSprite = (HBITMAP)LoadImageW(
        NULL, spritePath, IMAGE_BITMAP, 0, 0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (!g_hSprite) {
        MessageBoxW(NULL, L"找不到 sprite.bmp，请把它放到 exe 同目录。", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }

    // 大图标、小图标都从 sprite 左上角 128×128 抠出
    HICON hIconBig   = CreateIconFromSprite(g_hSprite, 0, 0, 128, 128);
    HICON hIconSmall = CreateIconFromSprite(g_hSprite, 0, 0, 128, 128);

    // 贴图源 DC 与画刷整局复用，绘制时不再反复创建/销毁 GDI 对象
    g_hSpriteDC = CreateCompatibleDC(NULL);
    if (g_hSpriteDC) g_hSpriteOld = (HBITMAP)SelectObject(g_hSpriteDC, g_hSprite);
    g_brWindow = CreateSolidBrush(RGB(192,192,192));
    g_brCell   = CreateSolidBrush(RGB(224,224,224));

    WNDCLASSEXW wc = { 0 };
    wc.cbSize        = sizeof(wc);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = WNDCLASS_NAME;
    wc.hIcon         = hIconBig;
    wc.hIconSm       = hIconSmall;
    RegisterClassExW(&wc);

    WNDCLASSEXW wcDlg = { 0 };
    wcDlg.cbSize        = sizeof(wcDlg);
    wcDlg.style         = CS_HREDRAW | CS_VREDRAW;
    wcDlg.hInstance     = hInst;
    wcDlg.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wcDlg.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

    wcDlg.lpfnWndProc = CustomDlgProc;
    wcDlg.lpszClassName = DIALOG_CUSTOM;
    RegisterClassExW(&wcDlg);

    wcDlg.lpfnWndProc = AboutDlgProc;
    wcDlg.lpszClassName = DIALOG_ABOUT;
    RegisterClassExW(&wcDlg);

    wcDlg.lpfnWndProc = HighScoreDlgProc;
    wcDlg.lpszClassName = DIALOG_HIGHSCORE;
    RegisterClassExW(&wcDlg);

    StartPreset(&g_board, 1, 9, 9, 10);
    LoadHighScores(&g_scores);

    g_hWnd = CreateWindowExW(
        WS_EX_COMPOSITED,
        WNDCLASS_NAME, APP_TITLE,
        WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT, DpiScale(400), DpiScale(600),
        NULL, BuildMenu(), hInst, NULL);
    if (!g_hWnd) {
        MessageBoxW(NULL, L"创建主窗口失败。", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }

    g_dpi = GetWindowDpi(g_hWnd);

    SendMessageW(g_hWnd, WM_SETICON, ICON_BIG,   (LPARAM)hIconBig);
    SendMessageW(g_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);

    // 先按棋盘算好尺寸再显示，避免启动时闪一下 400×600 的默认大小
    ResizeWindowForBoard(g_hWnd, &g_board);
    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}