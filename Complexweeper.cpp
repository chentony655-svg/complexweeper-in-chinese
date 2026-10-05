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
static BOOL       g_chordPressed = FALSE;
static int        g_chordX = -1, g_chordY = -1;
static HBITMAP    g_hSprite = NULL;
static BOOL       g_dlgOK = FALSE;

// ============================================================
// 工具
// ============================================================
static int clampi(int v, int lo, int hi) { return v<lo?lo:(v>hi?hi:v); }
static int idx(const Board* b, int x, int y) { return y*b->width + x; }
static BOOL inBounds(const Board* b, int x, int y) { return x>=0 && y>=0 && x<b->width && y<b->height; }

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

static int GetCellSize(const Board* b) { return CELL_SIZE * b->zoom / 100; }

static void GetBoardOrigin(HWND hwnd, Board* b, int* ox, int* oy) {
    RECT rc; GetClientRect(hwnd, &rc);
    int cs = GetCellSize(b);
    int boardW = b->width * cs;
    int x = (rc.right - boardW)/2;
    if (x < BOARD_MARGIN+BOARD_PAD_X) x = BOARD_MARGIN+BOARD_PAD_X;
    *ox = x;
    *oy = BOARD_MARGIN + TOP_PANEL_H + 8 + BOARD_PAD_Y;
}

static int GetFaceBtnX(int winW) { return (winW - FACE_BTN_W)/2; }
static int GetFaceBtnY(void) { return BOARD_MARGIN + 56; }

// ============================================================
// 贴图
// ============================================================
static void DrawSpriteScaled(HDC hdc, int sx, int sy, int sw, int sh,
                             int dx, int dy, int dw, int dh) {
    if (!g_hSprite) return;
    HDC m = CreateCompatibleDC(hdc);
    HBITMAP old = (HBITMAP)SelectObject(m, g_hSprite);
    SetStretchBltMode(hdc, COLORONCOLOR);
    StretchBlt(hdc, dx, dy, dw, dh, m, sx, sy, sw, sh, SRCCOPY);
    SelectObject(m, old); DeleteDC(m);
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
static void InitGame(Board* b, int w, int h, int m1, int m2, int m3, int m4) {
    b->width = clampi(w,1,MAX_DIM);
    b->height = clampi(h,1,MAX_DIM);
    b->mine_count[0]=m1; b->mine_count[1]=m2;
    b->mine_count[2]=m3; b->mine_count[3]=m4;
    b->zoom = 100;
    ZeroBoard(b);
}

static void InitGameRandom(Board* b, int w, int h, int sum) {
    int m[4] = {0, 0, 0, 0};
    for (int i = 0; i < sum; i++) m[rand() % 4]++;
    InitGame(b, w, h, m[0], m[1], m[2], m[3]);
}

static void NewGame(Board* b) {
    ZeroBoard(b);
    g_faceState = FACE_NORMAL;
    g_pressX = g_pressY = -1;
    g_pressing = g_chordPressed = FALSE;
}

static void GenerateBoard(Board* b, int sx, int sy) {
    int total = b->width * b->height;
    int mines[4] = { b->mine_count[0], b->mine_count[1], b->mine_count[2], b->mine_count[3] };
    int totalMines = mines[0]+mines[1]+mines[2]+mines[3];

    for (int i=0;i<total;i++) { b->cells[i].mine_type = MINE_NONE; b->cells[i].is_mine = FALSE; }

    BOOL protect[MAX_CELLS]; memset(protect, 0, sizeof(protect));
    for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
        int nx=sx+dx, ny=sy+dy;
        if (inBounds(b,nx,ny)) protect[idx(b,nx,ny)] = TRUE;
    }

    int placed = 0, guard = 0;
    while (placed < totalMines && guard++ < 1000000) {
        int r = rand() % total;
        if (protect[r] || b->cells[r].is_mine) continue;
        int type = -1, roll = rand() % (totalMines - placed), acc = 0;
        for (int t=0;t<4;t++) { acc += mines[t]; if (roll < acc) { type = t; break; } }
        if (type < 0) type = 0;
        b->cells[r].is_mine = TRUE;
        b->cells[r].mine_type = (BYTE)type;
        mines[type]--; placed++;
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
    if (b->over) return;
    b->over = TRUE; b->win = TRUE;
    b->elapsed_ms = GetTickCount() - b->start_tick;
    g_faceState = FACE_WIN;
    InvalidateRect(g_hWnd, NULL, FALSE);
}

static BOOL CheckWin(Board* b) {
    int total = b->width * b->height;
    int totalMines = b->mine_count[0]+b->mine_count[1]+b->mine_count[2]+b->mine_count[3];
    return b->opened_count >= (total - totalMines);
}

static void OpenRegion(Board* b, int x, int y) {
    int stack[MAX_CELLS], sp = 0;
    Cell* start = &b->cells[idx(b,x,y)];
    if (start->opened) {
        for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
            if (dx==0&&dy==0) continue;
            int nx=x+dx, ny=y+dy;
            if (!inBounds(b,nx,ny)) continue;
            int ni = idx(b,nx,ny);
            if (b->cells[ni].opened || b->cells[ni].flag_type != FLAG_NONE) continue;
            stack[sp++] = ni;
        }
    } else stack[sp++] = idx(b,x,y);

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
                int nx=cx+dx, ny=cy+dy;
                if (!inBounds(b,nx,ny)) continue;
                int ni = idx(b,nx,ny);
                if (b->cells[ni].opened || b->cells[ni].flag_type != FLAG_NONE) continue;
                stack[sp++] = ni;
            }
        }
    }
}

static void OpenCell(Board* b, int x, int y) {
    if (!inBounds(b,x,y) || b->over) return;
    Cell* c = &b->cells[idx(b,x,y)];
    if (c->opened || c->flag_type != FLAG_NONE) return;
    c->opened = TRUE; b->opened_count++;
    if (c->is_mine) { OnLose(b,x,y); return; }
    if (!c->display.has_mine_around) OpenRegion(b,x,y);
    if (CheckWin(b)) OnWin(b);
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
                         x + i*LED_CHAR_W, y, LED_CHAR_W, LED_CHAR_H);
    }
}

static void PaintFace(HDC hdc, int state, int winW) {
    int sx, sy, sw, sh;
    switch (state) {
        case FACE_BOOM: sx = SPR_FACE_DEAD_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
        case FACE_PRESS: sx = SPR_FACE_WIN2_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
        case FACE_WIN: sx = SPR_FACE_WIN_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
        default: sx = SPR_FACE_NORMAL_X; sy = SPR_FACE_Y; sw = SPR_FACE_W; sh = SPR_FACE_H; break;
    }
    DrawSpriteScaled(hdc, sx, sy, sw, sh, GetFaceBtnX(winW), GetFaceBtnY(), FACE_BTN_W, FACE_BTN_H);
}

static void PaintCounter(HDC hdc, Board* b) {
    int cx = BOARD_MARGIN + 8, cy = BOARD_MARGIN + 8;
    for (int t=0;t<4;t++) {
        int icon_x, icon_y;
        switch (t) {
            case 0: icon_x = SPR_MINE_POS_REAL_MARK_X; icon_y = SPR_VAL_ROW2_Y; break;
            case 1: icon_x = SPR_MINE_NEG_REAL_MARK_X; icon_y = SPR_MINE_Y; break;
            case 2: icon_x = SPR_MINE_POS_IMAG_MARK_X; icon_y = SPR_MINE_Y; break;
            case 3: icon_x = SPR_MINE_NEG_IMAG_MARK_X; icon_y = SPR_MINE_Y; break;
            default: icon_x = SPR_MINE_POS_REAL_MARK_X; icon_y = SPR_VAL_ROW2_Y; break;
        }
        DrawSpriteScaled(hdc, icon_x, icon_y, 64, 64, cx, cy, 32, 32);
        int remain = b->mine_count[t] - b->flag_count[t];
        DrawLEDFixed(hdc, cx + COUNTER_DIGIT_X, cy - 4, remain, 4, FALSE);
        cy += 40;
    }
}

static void PaintTimer(HDC hdc, Board* b, int winW) {
    DWORD elapsed = b->elapsed_ms;
    if (b->started && !b->over) elapsed = GetTickCount() - b->start_tick;
    DWORD sec = elapsed / 1000; if (sec > 9999) sec = 9999;
    wchar_t buf[16]; FormatFixed(buf, (int)sec, 4, FALSE);
    int len = (int)wcslen(buf);
    int totalW = len * LED_CHAR_W;
    int x = winW - BOARD_MARGIN - totalW;
    int y = GetFaceBtnY() + 4;
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
                         x + i*LED_CHAR_W, y, LED_CHAR_W, LED_CHAR_H);
    }
}

static void PaintBoard(HWND hwnd, Board* b) {
    PAINTSTRUCT ps; HDC hdc = BeginPaint(hwnd, &ps);
    RECT rc; GetClientRect(hwnd, &rc);
    int winW = rc.right;
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBmp = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);
    HBRUSH bg = CreateSolidBrush(RGB(192,192,192));
    FillRect(memDC, &rc, bg); DeleteObject(bg);

    RECT topPanel = { BOARD_MARGIN, BOARD_MARGIN, rc.right-BOARD_MARGIN, BOARD_MARGIN+TOP_PANEL_H };
    FrameRect(memDC, &topPanel, (HBRUSH)GetStockObject(GRAY_BRUSH));
    RECT boardPanel = { BOARD_MARGIN, BOARD_MARGIN+TOP_PANEL_H+8, rc.right-BOARD_MARGIN, rc.bottom-BOARD_MARGIN };
    FrameRect(memDC, &boardPanel, (HBRUSH)GetStockObject(GRAY_BRUSH));

    int cs = GetCellSize(b);
    int ox, oy; GetBoardOrigin(hwnd, b, &ox, &oy);

    for (int y=0;y<b->height;y++) for (int x=0;x<b->width;x++) {
        Cell* c = &b->cells[idx(b,x,y)];
        RECT r = { ox+x*cs, oy+y*cs, ox+(x+1)*cs, oy+(y+1)*cs };

        // 底
        if (!c->opened) {
            DrawSpriteScaled(memDC, SPR_VAL_BLANK_X, SPR_VAL_ROW2_Y, SPR_VAL_W, SPR_VAL_H,
                             r.left, r.top, cs, cs);
        } else {
            HBRUSH br = CreateSolidBrush(RGB(224,224,224));
            FillRect(memDC, &r, br); DeleteObject(br);
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

    PaintFace(memDC, g_faceState, winW);
    PaintCounter(memDC, b);
    PaintTimer(memDC, b, winW);

    BitBlt(hdc, 0, 0, rc.right, rc.bottom, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBmp); DeleteObject(memBmp); DeleteDC(memDC);
    EndPaint(hwnd, &ps);
}

// ============================================================
// 自动调整窗口大小
// ============================================================
static void ResizeWindowForBoard(HWND hwnd, Board* b) {
    int cs = GetCellSize(b);
    int boardW = b->width * cs;
    int boardH = b->height * cs;
    int clientW = boardW + 2*(BOARD_MARGIN+BOARD_PAD_X);
    int clientH = TOP_PANEL_H + 8 + 2*BOARD_PAD_Y + boardH + 2*BOARD_MARGIN;
    RECT rc = { 0, 0, clientW, clientH };
    AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, TRUE, 0);
    int winW = rc.right - rc.left, winH = rc.bottom - rc.top;
    if (winW < 360) winW = 360;
    if (winH < 480) winH = 480;
    SetWindowPos(hwnd, NULL, 0, 0, winW, winH,
                 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    InvalidateRect(hwnd, NULL, FALSE);
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

// ============================================================
// 手写对话框
// ============================================================
static HWND MakeStatic(HWND hDlg, const wchar_t* text, int x, int y, int w, int h) {
    HWND c = CreateWindowExW(0, L"STATIC", text,
        WS_CHILD|WS_VISIBLE|SS_LEFT,
        x, y, w, h, hDlg, NULL, g_hInst, NULL);
    SendMessageW(c, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    return c;
}
static HWND MakeEdit(HWND hDlg, int id, const wchar_t* text, int x, int y, int w, int h) {
    HWND c = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", text,
        WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_NUMBER,
        x, y, w, h, hDlg, (HMENU)(INT_PTR)id, g_hInst, NULL);
    SendMessageW(c, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    return c;
}
static HWND MakeButton(HWND hDlg, int id, const wchar_t* text, int x, int y, int w, int h) {
    HWND c = CreateWindowExW(0, L"BUTTON", text,
        WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
        x, y, w, h, hDlg, (HMENU)(INT_PTR)id, g_hInst, NULL);
    SendMessageW(c, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    return c;
}

static LRESULT CALLBACK CustomDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            MakeStatic(hDlg, L"高度(H):", 10, 12, 60, 18);
            MakeEdit(hDlg, IDC_EDIT_H, L"9", 75, 10, 60, 22);
            MakeStatic(hDlg, L"9 - 30 行", 145, 12, 80, 18);

            MakeStatic(hDlg, L"宽度(W):", 10, 42, 60, 18);
            MakeEdit(hDlg, IDC_EDIT_W, L"9", 75, 40, 60, 22);
            MakeStatic(hDlg, L"9 - 40 列", 145, 42, 80, 18);

            MakeStatic(hDlg, L"正实雷:", 10, 72, 60, 18);
            MakeEdit(hDlg, IDC_EDIT_M1, L"5", 75, 70, 60, 22);
            MakeStatic(hDlg, L"负实雷:", 145, 72, 50, 18);
            MakeEdit(hDlg, IDC_EDIT_M2, L"5", 200, 70, 60, 22);

            MakeStatic(hDlg, L"正虚雷:", 10, 102, 60, 18);
            MakeEdit(hDlg, IDC_EDIT_M3, L"5", 75, 100, 60, 22);
            MakeStatic(hDlg, L"负虚雷:", 145, 102, 50, 18);
            MakeEdit(hDlg, IDC_EDIT_M4, L"5", 200, 100, 60, 22);

            MakeButton(hDlg, IDC_BTN_AVG, L"按合计均分", 10, 132, 100, 24);
            MakeButton(hDlg, IDC_BTN_OK, L"确定", 80, 166, 60, 24);
            MakeButton(hDlg, IDC_BTN_CANCEL, L"取消", 150, 166, 60, 24);

            HWND e = CreateWindowExW(0, L"STATIC", L"",
                WS_CHILD|WS_VISIBLE|SS_LEFT,
                10, 196, 250, 18, hDlg, (HMENU)(INT_PTR)IDC_ERR, g_hInst, NULL);
            SendMessageW(e, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
            return 0;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
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
                case IDC_BTN_CANCEL:
                    g_dlgOK = FALSE;
                    DestroyWindow(hDlg);
                    return 0;
            }
            return 0;
        }
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
            wchar_t buf[256];
            swprintf(buf, 256,
                L"复扫雷 Complexweeper %s\n"
                L"copyright◎skamerr"
                L"全是吃干饭的大肥鱼ds帮我vibe的\n"
                L"复数扫雷：正实雷/负实雷/正虚雷/负虚雷\n"
                L"灵感来源于b站up主青月晓的复扫雷",
                APP_VERSION);
            HWND e = CreateWindowExW(0, L"STATIC", buf,
                WS_CHILD|WS_VISIBLE|SS_LEFT,
                15, 15, 280, 90, hDlg, NULL, g_hInst, NULL);
            SendMessageW(e, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
            MakeButton(hDlg, IDOK, L"确定", 120, 120, 70, 26);
            return 0;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) { DestroyWindow(hDlg); return 0; }
            return 0;
        case WM_CLOSE: DestroyWindow(hDlg); return 0;
    }
    return DefWindowProcW(hDlg, msg, wParam, lParam);
}

static LRESULT CALLBACK HighScoreDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            wchar_t buf[256];
            const wchar_t* p1 = g_scores.time_beginner     ? L"" : L"———";
            const wchar_t* p2 = g_scores.time_intermediate ? L"" : L"———";
            const wchar_t* p3 = g_scores.time_expert       ? L"" : L"———";
            swprintf(buf, 256,
                L"初级：%u 秒 %s\n中级：%u 秒 %s\n高级：%u 秒 %s",
                g_scores.time_beginner, p1,
                g_scores.time_intermediate, p2,
                g_scores.time_expert, p3);
            HWND e = CreateWindowExW(0, L"STATIC", buf,
                WS_CHILD|WS_VISIBLE|SS_LEFT,
                20, 20, 240, 90, hDlg, NULL, g_hInst, NULL);
            SendMessageW(e, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
            MakeButton(hDlg, IDOK, L"确定", 110, 120, 70, 26);
            return 0;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) { DestroyWindow(hDlg); return 0; }
            return 0;
        case WM_CLOSE: DestroyWindow(hDlg); return 0;
    }
    return DefWindowProcW(hDlg, msg, wParam, lParam);
}

static void ShowModalDialog(HWND parent, const wchar_t* cls, const wchar_t* title, int cx, int cy) {
    g_dlgOK = FALSE;
    HWND hDlg = CreateWindowExW(
        WS_EX_DLGMODALFRAME,
        cls, title,
        WS_POPUP | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, cx, cy,
        parent, NULL, g_hInst, NULL);
    if (!hDlg) return;

    RECT rp, rd;
    GetWindowRect(parent, &rp);
    GetWindowRect(hDlg, &rd);
    int x = rp.left + (rp.right-rp.left - (rd.right-rd.left))/2;
    int y = rp.top  + (rp.bottom-rp.top - (rd.bottom-rd.top))/2;
    SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    ShowWindow(hDlg, SW_SHOW);
    EnableWindow(parent, FALSE);

    MSG msg;
    while (IsWindow(hDlg) && GetMessageW(&msg, NULL, 0, 0)) {
        if (!IsDialogMessageW(hDlg, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    EnableWindow(parent, TRUE);
    SetActiveWindow(parent);
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
                if (g_board.started && !g_board.over) {
                    DWORD oldSec = g_board.elapsed_ms / 1000;
                    g_board.elapsed_ms = GetTickCount() - g_board.start_tick;
                    if (g_board.elapsed_ms/1000 != oldSec) InvalidateRect(hwnd, NULL, FALSE);
                }
            }
            return 0;

        case WM_ERASEBKGND: return 1;
        case WM_PAINT: PaintBoard(hwnd, &g_board); return 0;
        case WM_SIZE: InvalidateRect(hwnd, NULL, FALSE); return 0;

        case WM_LBUTTONDOWN: {
            int mx = LOWORD(lParam), my = HIWORD(lParam);
            RECT rc; GetClientRect(hwnd, &rc);
            int fx = GetFaceBtnX(rc.right), fy = GetFaceBtnY();
            if (mx>=fx && mx<fx+FACE_BTN_W && my>=fy && my<fy+FACE_BTN_H) {
                g_faceState = FACE_PRESS;
                InvalidateRect(hwnd, NULL, FALSE);
                return 0;
            }
            int ox, oy; GetBoardOrigin(hwnd, &g_board, &ox, &oy);
            int cs = GetCellSize(&g_board);
            int gx=(mx-ox)/cs, gy=(my-oy)/cs;
            if (inBounds(&g_board, gx, gy)) {
                if (!g_pressing) {
                    g_pressing = TRUE;
                    g_pressX = gx;
                    g_pressY = gy;
                }
                g_faceState = FACE_PRESS;
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        }

        case WM_LBUTTONUP: {
            int mx = LOWORD(lParam), my = HIWORD(lParam);
            RECT rc; GetClientRect(hwnd, &rc);
            int fx = GetFaceBtnX(rc.right), fy = GetFaceBtnY();
            if (mx>=fx && mx<fx+FACE_BTN_W && my>=fy && my<fy+FACE_BTN_H) {
                g_faceState = FACE_NORMAL;
                NewGame(&g_board);
                InvalidateRect(hwnd, NULL, FALSE);
                return 0;
            }
            if (g_pressing) {
                g_pressing = FALSE; g_faceState = FACE_NORMAL;
                if (!g_board.over) {
                    if (!g_board.started) GenerateBoard(&g_board, g_pressX, g_pressY);
                    OpenCell(&g_board, g_pressX, g_pressY);
                }
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        }

        case WM_LBUTTONDBLCLK: {
            g_pressing = FALSE;
            int mx = LOWORD(lParam), my = HIWORD(lParam);
            int ox, oy; GetBoardOrigin(hwnd, &g_board, &ox, &oy);
            int cs = GetCellSize(&g_board);
            int gx=(mx-ox)/cs, gy=(my-oy)/cs;
            if (!inBounds(&g_board, gx, gy) || g_board.over) return 0;
            Cell* c = &g_board.cells[idx(&g_board, gx, gy)];
            if (!c->opened || c->is_mine) return 0;
            int flags = 0, mines = 0;
            for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
                if (dx==0&&dy==0) continue;
                int nx=gx+dx, ny=gy+dy;
                if (!inBounds(&g_board, nx, ny)) continue;
                Cell* n = &g_board.cells[idx(&g_board, nx, ny)];
                if (n->flag_type != FLAG_NONE) flags++;
                if (n->is_mine) mines++;
            }
            if (flags == mines && flags > 0) {
                for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
                    if (dx==0&&dy==0) continue;
                    int nx=gx+dx, ny=gy+dy;
                    if (!inBounds(&g_board, nx, ny)) continue;
                    Cell* n = &g_board.cells[idx(&g_board, nx, ny)];
                    if (n->opened || n->flag_type != FLAG_NONE) continue;
                    if (n->is_mine) { n->opened=TRUE; g_board.opened_count++; OnLose(&g_board, nx, ny); InvalidateRect(hwnd, NULL, FALSE); return 0; }
                    n->opened=TRUE; g_board.opened_count++;
                    if (!n->display.has_mine_around) OpenRegion(&g_board, nx, ny);
                }
                if (CheckWin(&g_board)) OnWin(&g_board);
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        }

        case WM_RBUTTONDOWN: {
            int mx = LOWORD(lParam), my = HIWORD(lParam);
            int ox, oy; GetBoardOrigin(hwnd, &g_board, &ox, &oy);
            int cs = GetCellSize(&g_board);
            int gx=(mx-ox)/cs, gy=(my-oy)/cs;
            ToggleFlag(&g_board, gx, gy);
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        }

        case WM_MBUTTONDOWN: {
            int mx = LOWORD(lParam), my = HIWORD(lParam);
            int ox, oy; GetBoardOrigin(hwnd, &g_board, &ox, &oy);
            int cs = GetCellSize(&g_board);
            g_chordPressed = TRUE;
            g_chordX = (mx-ox)/cs;
            g_chordY = (my-oy)/cs;
            return 0;
        }

        case WM_MBUTTONUP: {
            if (g_chordPressed) {
                g_chordPressed = FALSE;
                int x = g_chordX, y = g_chordY;
                if (inBounds(&g_board, x, y) && !g_board.over) {
                    for (int dy=-1;dy<=1;dy++) for (int dx=-1;dx<=1;dx++) {
                        if (dx==0&&dy==0) continue;
                        int nx=x+dx, ny=y+dy;
                        if (!inBounds(&g_board, nx, ny)) continue;
                        Cell* n = &g_board.cells[idx(&g_board, nx, ny)];
                        if (n->opened || n->flag_type != FLAG_NONE) continue;
                        if (n->is_mine) { n->opened=TRUE; g_board.opened_count++; OnLose(&g_board, nx, ny); InvalidateRect(hwnd, NULL, FALSE); return 0; }
                        n->opened=TRUE; g_board.opened_count++;
                        if (!n->display.has_mine_around) OpenRegion(&g_board, nx, ny);
                    }
                    if (CheckWin(&g_board)) OnWin(&g_board);
                }
                InvalidateRect(hwnd, NULL, FALSE);
            }
            return 0;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_BEGINNER:
                    InitGameRandom(&g_board, 9, 9, 10);
                    NewGame(&g_board);
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_INTERMEDIATE:
                    InitGameRandom(&g_board, 16, 16, 40);
                    NewGame(&g_board);
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_EXPERT:
                    InitGameRandom(&g_board, 30, 16, 99);
                    NewGame(&g_board);
                    ResizeWindowForBoard(hwnd, &g_board);
                    break;
                case IDM_CUSTOM: {
                    ShowModalDialog(hwnd, DIALOG_CUSTOM, L"自定义雷区", 290, 250);
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
                    MessageBoxW(hwnd, L"左键翻开，右键插旗，双击展开，中键展开。", L"玩法", MB_OK);
                    break;
                case IDM_EXIT: DestroyWindow(hwnd); break;
            }
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, IDT_TIMER);
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
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmdLine, int nCmdShow) {
    (void)hPrev;
    g_hInst = hInst;
    (void)lpCmdLine;

    SetProcessDPIAware();
    srand(GetTickCount());

    g_hSprite = (HBITMAP)LoadImageW(
        NULL, L"sprite.bmp", IMAGE_BITMAP, 0, 0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (!g_hSprite) {
        MessageBoxW(NULL, L"找不到 sprite.bmp，请把它放到 exe 同目录。", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }

    // 大图标、小图标都从 sprite 左上角 128×128 抠出
    HICON hIconBig   = CreateIconFromSprite(g_hSprite, 0, 0, 128, 128);
    HICON hIconSmall = CreateIconFromSprite(g_hSprite, 0, 0, 128, 128);

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

    InitGameRandom(&g_board, 9, 9, 10);
    LoadHighScores(&g_scores);

    g_hWnd = CreateWindowExW(
        WS_EX_COMPOSITED,
        WNDCLASS_NAME, APP_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 600,
        NULL, BuildMenu(), hInst, NULL);

    SendMessageW(g_hWnd, WM_SETICON, ICON_BIG,   (LPARAM)hIconBig);
    SendMessageW(g_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);
    ResizeWindowForBoard(g_hWnd, &g_board);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}