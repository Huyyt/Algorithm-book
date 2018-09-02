#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int L = 4, S = 10, maxt = 9, Size = 5040;
//���ָ��������ַ�Χ[0,S)�����²��������ͬ�Ĵ𰸸���
const pair<int, int> error = make_pair(-1, -1);
//����²�ʱ��Χ����Ϣ
const pair<int, int> over = make_pair(-2, -2);
//�²�����Ѵ����²������δ�³��𰸣�������Ϸ�Զ�����

string AIname = "Noname";

class game {
    int P, Ps, T[maxt + 1];
    //�Ѳ¾������ܾ�����T[i]��ʾi�β³��ľ�����T[0]��ʾδ�³��ľ���
    int a[L], t;
    //��ǰ�ֵ����֣���ǰ���Ѳ´���
    int time;
    //��¼ʱ��
    public:
    game()
    //��ʼ��
    {
        P = t = 0;
        Ps = 1;
        for (int i = 0; i < L; ++i)
            Ps *= S - i;
        memset(T, 0, sizeof(T));
        for (int i = 0; i < L; ++i)
            a[i] = i;
    }
    pair<int, int> guess(int* b)
    //�����֣�b����Ϊ���µ�L�����֣���pair<A,B>���ز²���
    {
        if (!P && !t)
            freopen((AIname + "_log.txt").c_str(), "w", stdout);
        if (!t) {
            cout << "Game  " << P + 1 << " : ";
            for (int i = 0; i < L; ++i)
                cout << a[i] << " ";
            cout << endl;
        }
        ++t;
        int A = 0, B = 0;
        for (int i = 0; i < L; ++i)
            if (b[i] < 0 || b[i] > S) return error;
        for (int i = 0; i < L; ++i)
            for (int j = i + 1; j < L; ++j)
                if (b[i] == b[j]) return error;
        for (int i = 0; i < L; ++i)
            if (a[i] == b[i]) ++A;
        for (int i = 0; i < L; ++i)
            for (int j = 0; j < L; ++j)
                if (a[i] == b[j]) ++B;
        cout << "guess " << t << " : ";
        for (int i = 0; i < L; ++i)
            cout << b[i] << " ";
        cout << " " << A << "A" << B - A << "B" << endl;
        if (A == L || t == maxt) {
            if (A == L) {
                ++T[t];
                cout << "Seccessful game in " << t << " guesses" << endl << endl;
            }else {
                ++T[0];
                cout << "Failed game" << endl << endl;
            }
            if (++P == Ps) {
                freopen((AIname + "_summary.txt").c_str(), "w", stdout);
                //cout << P << " Games: " << P - T[0] << " Y / " << T[0] << " N" << endl;
                int max = 0, sum = 0;
                for (int i = 1; i <= maxt; ++i) {
                    if (T[i]) max = i;
                    sum += i * T[i];
                }
                cout << fixed;
                cout.precision(3);
                cout << "ƽ���²���� : " << double(sum) / (P - T[0]) << endl;
                cout << "���²���� : " << max << endl;
                cout << "�ܺ�ʱ       ��" << clock() / 1000.0  << " seconds" << endl;
                cout << "ÿ�ֲ²���������Ϸ�ľ������£�" << endl;
                cout << "����" << "\t";
                for (int i = 1; i <= maxt; ++i)
                    cout << i << "\t";
                cout << endl;
                cout << "����" << "\t";
                for (int i = 1; i <= maxt; ++i)
                    cout << T[i] << "\t";
                cout << endl;
                exit(0);
            }else {
                t = 0;
                bool u[S];
                memset(u, 0, sizeof(u));
                int x = P;
                for (int i = 0; i < L; ++i) {
                    int y = x;
                    for (int j = i + 1; j < L; ++j)
                        y /= S - j;
                    for (int j = 0; j < S; ++j)
                        if (!u[j]) {
                            --y;
                            if (y < 0) {
                                u[j] = true;
                                a[i] = j;
                                break;
                            }
                        }
                    y = 1;
                    for (int j = i + 1; j < L; ++j)
                        y *= S - j;
                    x %= y;
                }
            }
        }
        return make_pair(A, B - A);
    }
} G;

pair<int, int> guess(int* b)
{
    return G.guess(b);
}

pair<int, int> guess(vector<int> vb)
{
    int b[L];
    for (int i = 0; i < L; ++i)
        b[i] = vb[i];
    return G.guess(b);
}
