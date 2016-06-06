#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

int time = 0;
struct Panel
{
    int step = 0;
    int next;
};

struct NextPos
{
    int w;
    int w2;
    int dre = 0;
    friend bool operator < (NextPos n1, NextPos n2)
    {
        if(n1.w == n2.w)
        {

            return n1.w2 < n2.w2;
        }
        else
        {
            return n1.w > n2.w;
        }
    }
};

struct Pos
{
    int dre = 0;
    priority_queue<NextPos> pq;
    int f = 1;
};



Panel **panel;
Pos *c;
bool flag;
int n;




void initPanel()
{
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            if(i == 0 || i == n - 1)
            {
                if(j == 0 || j == n - 1)
                {
                    panel[i][j].next = 2;
                } else if(j == 1 || j == n - 2)
                {
                    panel[i][j].next = 3;
                }
                else
                {
                    panel[i][j].next = 4;
                }
            }
            else if(i == 1 || i == n - 2)
            {
                if(j == 0 || j == n - 1)
                {
                    panel[i][j].next = 3;
                } else if(j == 1 || j == n - 2)
                {
                    panel[i][j].next = 4;
                }
                else
                {
                    panel[i][j].next = 6;
                }
            }
            else
            {
                if(j == 0 || j == n - 1)
                {
                    panel[i][j].next = 4;
                } else if(j == 1 || j == n - 2)
                {
                    panel[i][j].next = 6;
                }
                else
                {
                    panel[i][j].next = 8;
                }
            }
        }
    }
}

/*void initC()
{
    for(int i = 1; i < n * n + 1; i ++)
        c[i] = 0;
}*/

int getX(int x,int num)
{
    switch(num)
    {
    case 1:
        x-=2;break;
    case 2:
        x-=1;break;
    case 3:
        x+=1;break;
    case 4:
        x+=2;break;
    case 5:
        x+=2;break;
    case 6:
        x+=1;break;
    case 7:
        x-=1;break;
    case 8:
        x-=2;break;
    default:
        break;
    }
    return x;
}

int getY(int y,int num)
{
    switch(num)
    {
    case 1:
        y+=1;break;
    case 2:
        y+=2;break;
    case 3:
        y+=2;break;
    case 4:
        y+=1;break;
    case 5:
        y-=1;break;
    case 6:
        y-=2;break;
    case 7:
        y-=2;break;
    case 8:
        y-=1;break;
    default:
        break;
    }
    return y;
}

int reGetX(int x,int num)
{
    switch(num)
    {
    case 1:
        x+=2;break;
    case 2:
        x+=1;break;
    case 3:
        x-=1;break;
    case 4:
        x-=2;break;
    case 5:
        x-=2;break;
    case 6:
        x-=1;break;
    case 7:
        x+=1;break;
    case 8:
        x+=2;break;
    default:
        break;
    }
    return x;
}

int reGetY(int y,int num)
{
    switch(num)
    {
    case 1:
        y-=1;break;
    case 2:
        y-=2;break;
    case 3:
        y-=2;break;
    case 4:
        y-=1;break;
    case 5:
        y+=1;break;
    case 6:
        y+=2;break;
    case 7:
        y+=2;break;
    case 8:
        y+=1;break;
    default:
        break;
    }
    return y;
}

bool outPanelOrRun(int x,int y)
{
    if(x < 0 || x > n - 1 || y < 0 || y > n - 1 )
    {
        return false;
    }
    else if(panel[x][y].step != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool outPanel(int x,int y)
{
    if(x < 0 || x > n - 1 || y < 0 || y > n - 1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}


void showPanel()
{
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            cout<<panel[i][j].step<<" ";
        }
        cout<<endl;
    }
}

void showPanel_2()
{
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            cout<<panel[i][j].next<<" ";
        }
        cout<<endl;
    }
}

void start(int X,int Y)
{
    int x = X;
    int y = Y;
    flag = false;
    panel[x][y].step = 1;
    int k = 1;
    int xx,yy;
    while(k >= 1)
    {
        if(c[k].f)
        {
            for(int i = 1; i <= 8; i ++)
            {
                int nx = getX(x,i);int ny = getY(y,i);
                if(outPanelOrRun(nx,ny))
                {
                    NextPos s;
                    s.dre = i;
                    s.w2 = (nx - X) * (nx - X) + (ny - Y) * (ny - Y);
                    //s.w2 = abs(nx - X ) + abs(ny - Y);
                    s.w = panel[nx][ny].next;
                    c[k].pq.push(s);
                }
                c[k].f = 0;
            }
        }
        /*while(!c[k].pq.empty())
        {
            cout<<c[k].pq.top().dre<<" "<<c[k].pq.top().w<<endl;
            c[k].pq.pop();
        }*/
        while(!c[k].pq.empty())
        {
            c[k].dre = c[k].pq.top().dre;
            time ++;
            //cout<<x<<" "<<y<<endl;
            //cout<<c[k].dre<<endl;
            //showPanel();
            //showPanel_2();
            c[k].pq.pop();
            xx = getX(x,c[k].dre);
            yy = getY(y,c[k].dre);
            //cout<<xx<<" "<<yy<<endl;
            if(k == n*n - 1)
            {
                for(int i = 1; i <= 8; i ++)
                {
                    if((X==getX(xx,i))&&(Y==getY(yy,i)))
                    {
                        panel[xx][yy].step = k+1;
                        c[k+1].dre = i;
                        flag = true;
                        return;
                    }
                }
            }
            else
            {
                k ++;
                panel[xx][yy].step = k;
                for(int i = 1 ; i <= 8; i ++)
                {
                    int xxx = getX(xx,i);
                    int yyy = getY(yy,i);
                    if(outPanel(xxx,yyy))
                    {
                        if(panel[xxx][yyy].next != 0)
                            panel[xxx][yyy].next--;
                    }
                    if(outPanelOrRun(xxx,yyy))
                    {
                        NextPos s;
                        s.dre = i;
                        s.w2 = (xxx - X) * (xxx - X) + (yyy - Y) * (yyy - Y);
                        //s.w2 = abs(xxx - X ) + abs(yyy - Y);
                        s.w = panel[xxx][yyy].next;
                        c[k].pq.push(s);
                    }
                }
                x = xx;
                y = yy;
            }
        }
        panel[x][y].step = 0;
        x = reGetX(x,c[k-1].dre);
        y = reGetY(y,c[k-1].dre);
        c[k].dre = 0;
        k--;
    }
}

int main()
{
    int x,y;
    cin>>n>>x>>y;
    panel = new Panel*[n];
    for(int i = 0 ; i < n; i ++)
        panel[i] = new Panel [n];
    initPanel();
    //showPanel_2();
    c = new Pos[n*n + 1];
    start(x-1,y-1);
    //showPanel_2();
    //showPanel();
    if(flag)
        cout<<"Find!  "<<time<<endl;
    else
        cout<<"Not Find!"<<endl;
    return 0;
}
