// Sheep.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<easyx.h>
#include<tchar.h>
#include <mmsystem.h>
#include <Windows.h>

#pragma comment (lib,"winmm.lib")//winmm.lib库用来对windows录音设备采集录音数据
/* #pragma 是一条编译器指令,是给告诉编译器你要链接一些东西,然后在后面的comment里面指明是什么东西 */
IMAGE img_bk;
IMAGE img_item[3];
const int WIDTH = 400;
const int HEIGHT = 760;
const int INTERVAL = 48;

void loadImg()
{
    
    loadimage(&img_bk, _T("src/bk.png"), WIDTH, HEIGHT);
    loadimage(img_item + 0, _T("src/coffee.png"), 48, 48);
    loadimage(img_item + 1, _T("src/pluzzla.png"), 48, 48);
    loadimage(img_item + 2, _T("src/icecream.png"), 48, 48);
}
int main()
{
    //��ʼ������
    initgraph(WIDTH, HEIGHT);

    loadImg();

    mciSendString(_T("open src/music/msc.mp3"), NULL, 0, NULL);
    mciSendString(_T("play src/music/msc.mp3"), NULL, 0, NULL);

    //��ʼ������
    int map[3][3] = { 0 };
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {

            map[r][c] = r + 1;
        }
    }
    //��������
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            int row = rand() % 3;    //��
            int column = rand() % 3; //��
            int temp = map[row][column];
            map[row][column] = map[r][c];
            map[r][c] = temp;
        }
    }
    //����ƫ����
    int offsetX = (WIDTH - (INTERVAL * 2 + 3 * 48)) / 2;
    int offsetY = (HEIGHT - (INTERVAL * 2 + 3 * 48)) / 2;
    //�·�����������
    int store[7] = { 0 };
    while (true)
    {
        BeginBatchDraw();

        putimage(0, 0, &img_bk);
        //���Ҫ������ͼƬ
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if (map[r][c])
                {
                    putimage(offsetX + c * (48 + INTERVAL), offsetY + r * (48 + INTERVAL), img_item + map[r][c] - 1);
                }
            }
        }
        //��������
        for (int i = 0; i < 7; i++)
        {

            if (store[i])
            {
                putimage((i * 50) + 26, 620, img_item + store[i] - 1);
            }
        }
        //��ֹ����Ļ��ʼ����
        EndBatchDraw();
        //�����Ϣ
        ExMessage msg = { 0 };
        if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
        {
            //���ͼƬ��Ӧ���±�
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int x = offsetX + c * (48 + INTERVAL);
                    int y = offsetY + r * (48 + INTERVAL);
                    //�ж��Ƿ�����ͼƬ
                    if (msg.x > x && msg.x < x + 48 && msg.y > y && msg.y < y + 48)
                    {
                        int col = (msg.x - offsetX) / (48 + INTERVAL);
                        int row = (msg.y - offsetY) / (48 + INTERVAL);
                        //�����ͼƬ���ӵ�����
                        for (int i = 0; i < 7; i++)
                        {
                            if (store[i] == 0)
                            {
                                store[i] = map[row][col];
                                break;
                            }
                        }

                        int count = 0;
                        for (int i = 0; i < 7; i++)
                        {
                            if (store[i] == map[row][col])
                            {
                                count++;
                            }
                        }
                        if (count == 3)
                        {
                            for (int i = 0; i < 7; i++)
                            {

                                if (store[i] == map[row][col])
                                {

                                    store[i] = 0;
                                }
                            }
                        }
                        map[row][col] = 0;
                    }
                }
            }
        }
    }

    while (1)
        ;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
