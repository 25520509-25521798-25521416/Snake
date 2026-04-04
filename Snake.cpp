#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <cctype>
using namespace std;
void gotoxy( int column, int line );

#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

void VeKhung()
{
    for (int i = MINX; i <= MAXX; i++)
    {
        for (int j = MINY; j <= MAXY; j++)
        {
            if (i == MINX || i == MAXX || j == MINY || j == MAXY)
            {
                gotoxy(i, j);
                cout << "+";
            }
        }
    }
}

struct Point
{
    int x,y;
};

class CONRAN
{
public:
    struct Point A[500];
    int DoDai;

    CONRAN()
    {
        DoDai = 3;
        A[0].x = 15;
        A[0].y = 10;
        A[1].x = 16;
        A[1].y = 10;
        A[2].x = 17;
        A[2].y = 10;
    }

    void Ve(Point Qua, Point QuaTo, bool isQuaToActive)
    {
        for (int i = 0; i < DoDai; i++)
        {
            gotoxy(A[i].x,A[i].y);
            if (i == 0) cout << "0";
            else cout<<"X";
        }

        // Ve moi nho
        gotoxy(Qua.x, Qua.y);
        cout << "*";

        // Ve moi to (ky hieu $) neu dang duoc kich hoat
        if (isQuaToActive)
        {
            gotoxy(QuaTo.x, QuaTo.y);
            cout << "$";
        }
    }

    // Ham kiem tra xem toa do (x,y) co bi trung voi than ran hay khong
    bool TrungRan(int x, int y)
    {
        for (int i = 0; i < DoDai; i++)
        {
            if (A[i].x == x && A[i].y == y)
            {
                return true;
            }
        }
        return false;
    }

    void DiChuyen(int Huong, Point& Qua, Point& QuaTo, bool& isQuaToActive, int& countMoiNho, int& targetMoiTo, int& timerMoiTo, int& Diem)
    {
        for (int i = DoDai-1; i>0; i--)
            A[i] = A[i-1];

        if (Huong==0) A[0].x = A[0].x + 1; // Phai
        if (Huong==1) A[0].y = A[0].y + 1; // Xuong
        if (Huong==2) A[0].x = A[0].x - 1; // Trai
        if (Huong==3) A[0].y = A[0].y - 1; // Len

        // Xu ly khi an MOI NHO
        if ((A[0].x == Qua.x) && (A[0].y == Qua.y))
        {
            DoDai++;
            Diem += 10; // Moi nho cong 10 diem
            countMoiNho++;

            // Random cho moi cho moi nho, dam bao khong trung than ran
            do
            {
                Qua.x = MINX + 1 + rand() % (MAXX - MINX - 1);
                Qua.y = MINY + 1 + rand() % (MAXY - MINY - 1);
            }
            while (TrungRan(Qua.x, Qua.y));

            // Neu an du so luong moi nho yeu cau thi tha moi to
            if (!isQuaToActive && countMoiNho >= targetMoiTo)
            {
                isQuaToActive = true;
                timerMoiTo = 60; // Moi to ton tai trong khoang 60 nhip

                // Dam bao moi to ko de len moi nho va khong trung than ran
                do
                {
                    QuaTo.x = MINX + 1 + rand() % (MAXX - MINX - 1);
                    QuaTo.y = MINY + 1 + rand() % (MAXY - MINY - 1);
                }
                while (TrungRan(QuaTo.x, QuaTo.y) || (QuaTo.x == Qua.x && QuaTo.y == Qua.y));

                countMoiNho = 0; // Reset bo dem
                targetMoiTo = 5 + rand() % 6; // Random muc tieu tiep theo tu 5 den 10
            }
        }

        // Xu ly khi an MOI TO
        if (isQuaToActive && (A[0].x == QuaTo.x) && (A[0].y == QuaTo.y))
        {
            DoDai++;
            Diem += 50; // Moi to cong tan 50 diem
            isQuaToActive = false; // An xong thi bien mat
        }
    }

    bool KiemTraChamTuong()
    {
        if (A[0].x <= MINX || A[0].x >= MAXX || A[0].y <= MINY || A[0].y >= MAXY)
        {
            return true;
        }
        return false;
    }

    // Ham kiem tra xem dau ran co can trung duoi khong
    bool KiemTraCanDuoi()
    {
        // Chay tu 1 vi 0 la cai dau, khong the tu so sanh voi chinh no
        for (int i = 1; i < DoDai; i++)
        {
            if (A[0].x == A[i].x && A[0].y == A[i].y)
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    CONRAN r;
    int Huong = 2;
    char t;
    srand((int)time(0));

    // Cac bien cho he thong diem va moi
    int Diem = 0;
    Point Qua;

    // Khoi tao moi nho, tranh than ran
    do
    {
        Qua.x = MINX + 1 + rand() % (MAXX - MINX - 1);
        Qua.y = MINY + 1 + rand() % (MAXY - MINY - 1);
    }
    while (r.TrungRan(Qua.x, Qua.y));

    Point QuaTo;
    bool isQuaToActive = false;
    int countMoiNho = 0;
    int targetMoiTo = 5 + rand() % 6; // Random n tu 5 den 10
    int timerMoiTo = 0;

    bool gameover = false;

    while (!gameover)
    {
        if (kbhit())
        {
            t = getch();
            t = tolower(t);
            if (t=='a' && Huong != 0) Huong = 2;
            if (t=='w' && Huong != 1) Huong = 3;
            if (t=='d' && Huong != 2) Huong = 0;
            if (t=='s' && Huong != 3) Huong = 1;
        }

        // Xu ly thoi gian dem nguoc cua moi to
        if (isQuaToActive)
        {
            timerMoiTo--;
            if (timerMoiTo <= 0)
            {
                isQuaToActive = false; // Het gio moi to tu bien mat
            }
        }

        system("cls");
        VeKhung();

        // In bang diem ben ngoai khung
        gotoxy(MAXX + 5, MINY + 2);
        cout << "DIEM SO: " << Diem;
        if (isQuaToActive)
        {
            gotoxy(MAXX + 5, MINY + 4);
            cout << "MOI TO ($): " << timerMoiTo << "s";
        }

        r.Ve(Qua, QuaTo, isQuaToActive);
        r.DiChuyen(Huong, Qua, QuaTo, isQuaToActive, countMoiNho, targetMoiTo, timerMoiTo, Diem);

        // Kiem tra ca dung tuong lan tu can vao duoi
        if (r.KiemTraChamTuong() || r.KiemTraCanDuoi())
        {
            gameover = true;
        }

        Sleep(150);
    }

    // Man hinh Game Over
    system("cls");
    VeKhung();
    // Goi lai ham Ve de giu nguyen xac con ran tai hien truong
    r.Ve(Qua, QuaTo, isQuaToActive);

    gotoxy(MAXX + 5, MINY + 6);
    cout << "GAME OVER!";
    gotoxy(MAXX + 5, MINY + 8);
    cout << "Tong diem cuoi cung: " << Diem;
    gotoxy(0, MAXY + 2);
    system("pause");
    return 0;
}

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}
