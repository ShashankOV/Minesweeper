#include<simplecpp>
#include<time.h>
int sizex=0,sizey=0;
int mine;
int level;
bool winCheck(short int matrix[30][16], bool overturn[30][16])
{
    bool win=true;
    for(int i=0; i<sizex; i++)
        for(int j=0; j<sizey; j++)
        {
            if(!overturn[i][j])
                win=win&&matrix[i][j]==9;
        }
    return win;
}
void gameOver(bool win)
{
    beginFrame();
    Rectangle clear(0,0,5000,5000);
    clear.setFill(1);
    clear.setColor(COLOR(255,255,255));
    Rectangle game(1250/2,350,200,50);
    game.setFill(1);
    Text over1(1250/2,350,"GAME OVER");
    Text over2(1250/2,350,"You Won!");
    over1.hide();
    over2.hide();

    if (!win) {
        game.setColor(COLOR("red"));
        over1.show();
    }
    else {
        game.setColor(COLOR("green"));
        over2.show();
    }

    repeat(5)
    {
        wait(0.5);
        clear.hide();
        wait(0.5);
        clear.show();
    }
    exit(0);
}
void makeTen(short int matrix[30][16],int i,int j, int iprev,int jprev)
{
    matrix[i][j]=10;

    if((i+1<sizex&&j+1<sizey&&matrix[i+1][j+1]==0)&&(i+1!=iprev||j+1!=jprev))
        makeTen(matrix,i+1,j+1,i,j);
    if((j+1<sizey&&matrix[i][j+1]==0)&&(i!=iprev||j+1!=jprev))
        makeTen(matrix,i,j+1,i,j);
    if((i+1<sizex&&matrix[i+1][j]==0)&&(i+1!=iprev||j!=jprev))
        makeTen(matrix,i+1,j,i,j);
    if((i-1>=0&&j-1>=0&&matrix[i-1][j-1]==0)&&(i-1!=iprev||j-1!=jprev))
        makeTen(matrix,i-1,j-1,i,j);
    if((j-1>=0&&matrix[i][j-1]==0)&&(i!=iprev||j-1!=jprev))
        makeTen(matrix,i,j-1,i,j);
    if((i-1>=0&&matrix[i-1][j]==0)&&(i-1!=iprev||j!=jprev))
        makeTen(matrix,i-1,j,i,j);
    if((i+1<sizex&&j-1>=0&&matrix[i+1][j-1]==0)&&(i+1!=iprev||j-1!=jprev))
        makeTen(matrix,i+1,j-1,i,j);
    if((i-1>=0&&j+1<sizey&&matrix[i-1][j+1]==0)&&(i-1!=iprev||j+1!=jprev))
        makeTen(matrix,i-1,j+1,i,j);

}
bool getBlock(int &i, int &j)
{
    XEvent event;
    while(1)
    {
        nextEvent(event);
        if(mouseButtonPressEvent(event))
        {
            int x=event.xbutton.x-1250/2+(sizex*40)/2;
            int y=event.xbutton.y-350+sizey*40/2;
            if(x<0||y<0||x>sizex*40||y>sizey*40)
                continue;
            x=x/40;
            y=y/40;
            i=x;
            j=y;
            if(event.xbutton.button==1)
                return true;
            else if(event.xbutton.button==3)

                return false;

        }
    }
}
/*bool setCustom()
{
    cout<<"Enter No. of rows : \n";
    cin>>sizey;
    if(sizey>)
}*/
void setLevel()
{
    {
        Line bombline(0,0,30,0);
        bombline.setColor(COLOR(128,128,128));
        Circle bombcircle(0,0,8);
        bombcircle.setFill(1);
        bombcircle.setColor(COLOR(128,128,128));
        for(int i=0; i<13; i++)
        {
            beginFrame();
            bombline.moveTo(1250/2-150-50+40*i+20,350-150);
            repeat(8)
            {
                bombline.imprint();
                bombline.rotate(PI/6);

            }
            bombcircle.reset(1250/2-150+40*i+20-50,350-150,8);
            bombcircle.imprint();
            endFrame();
        }
        for(int i=0; i<13; i++)
        {
            beginFrame();
            bombline.moveTo(1250/2-150+40*i+20-50,350+260);
            repeat(8)
            {
                bombline.imprint();
                bombline.rotate(PI/6);

            }
            bombcircle.reset(1250/2-150+40*i+20-50,350+260,8);
            bombcircle.imprint();
            endFrame();
        }
    }
    Text minesweeper(1250/2-50,250,"MINESWEEPER");
    Text info(1250/2+100-50,270,"-Developed by Shashank OV");
    Text levelpick(1250/2-50,300,"Pick your Level : ");
    Rectangle l1(1250/2-50,350,200,50);
    Rectangle l2(1250/2-50,420,200,50);
    Rectangle l3(1250/2-50,490,200,50);
    Rectangle cust(1250/2+150-50,560,200,50);
    Text mines(1250/2+200-50,300,"TILES");
    Text tiles(1250/2+300-50,300,"MINES");
    Text level1(1250/2-50,350,"BEGGINER");
    Text level2(1250/2-50,420,"INTERMEDIATE");
    Text level3(1250/2-50,490,"MASTER");
    Text custom(1250/2+150-50,560,"CUSTOM");
    Text level1tiles(1250/2+100+100-50,350,"10x10");
    Text level2tiles(1250/2+100+100-50,420,"16x16");
    Text level3tiles(1250/2+100+100-50,490,"30x16");
    Text level1mines(1250/2+100+100+100-50,350,"10");
    Text level2mines(1250/2+100+100+100-50,420,"40");
    Text level3mines(1250/2+100+100+100-50,490,"80");
    while(1)
    {
        int click=getClick();
        int clickx=click/65536,clicky=click%65536;
        if(clickx<=725-50&&clickx>=525-50&&clicky>=325&&clicky<=375)
        {
            sizex=sizey=10;
            level=1;
            break;
        }
        if(clickx<=725-50&&clickx>=525-50&&clicky>=395&&clicky<=445)
        {
            sizex=sizey=16;
            level=2;
            break;
        }
        if(clickx<=725-50&&clickx>=525-50&&clicky>=465&&clicky<=515)
        {
            sizex=30;
            sizey=16;
            level=3;
            break;
        }
        if(clickx<=725+100&&clickx>=525+100&&clicky>=525&&clicky<=575)
        {
            //setCustom();
            break;
        }
    }
}
main_program
{
    initCanvas("MINESWEEPER",1250,700);
    
    Rectangle clear(0,0,5000,5000);
    clear.setFill(0);
    clear.setColor(COLOR(255,255,255));
    setLevel();
    clear.setFill(1);

    beginFrame();
    Rectangle block[30][16];
    Rectangle borderblock[30][16];
    Text number[30][16];
    Text count;
    bool flag[30][16];
    bool overturn[30][16];
    Rectangle border(1250/2,350,sizex*40+2,sizey*40+2);
    short int matrix[32][16];
    srand(time(NULL));
    for(int i=0; i<sizex; i++)
    {
        for(int j=0; j<sizey; j++)
        {
            matrix[i][j]=0;
            flag[i][j]=1;
            overturn[i][j]=0;
            borderblock[i][j].init(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+j*40,38,38);
            block[i][j].init(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+j*40,38,38);
            block[i][j].setColor(COLOR(50,205,50));
            block[i][j].setFill(true);

        }
    }
    endFrame();
    int mines=0;
    int i,j;
    if(getBlock(i,j))
    {
        matrix[i][j]=10;
    }
    switch(level)
    {
        case 1:
            mine=10;
            break;
        case 2:
            mine=40;
            break;
        case 3:
            mine=80;
            break;
    }

    count.reset(1250/2-(sizex-1)*40/2+(sizex)*40,350-(sizey-1)*40/2+(sizey)*40, mine);

    while(mines!=mine)
    {
        int x,y;
        x=(int)randuv(0,sizex);
        y=(int)randuv(0,sizey);
        if(matrix[x][y]<9&&(x<i-1||x>i+1||y<j-1||y>j+1))
        {
            matrix[x][y]=9;
            mines++;
        }
    }
    /*
    for(int i=0; i<sizex; i++)
    {
        for(int j=0; j<sizey; j++)
        {
            cout<<matrix[i][j]<<" ";
            if(j==sizey-1) cout<<endl;
        }
    }
    */
    cout<<endl<<endl;
    for(int i=0; i<sizex; i++)
    {
        for(int j=0; j<sizey; j++)
        {
            if(matrix[i][j]==9)
            {
                if(i+1<sizex&&j+1<sizey&&matrix[i+1][j+1]!=9)
                    matrix[i+1][j+1]++;
                if(j+1<sizey&&matrix[i][j+1]!=9)
                    matrix[i][j+1]++;
                if(i+1<sizex&&matrix[i+1][j]!=9)
                    matrix[i+1][j]++;
                if(i-1>=0&&j-1>=0&&matrix[i-1][j-1]!=9)
                    matrix[i-1][j-1]++;
                if(j-1>=0&&matrix[i][j-1]!=9)
                    matrix[i][j-1]++;
                if(i-1>=0&&matrix[i-1][j]!=9)
                    matrix[i-1][j]++;
                if(i+1<sizex&&j-1>=0&&matrix[i+1][j-1]!=9)
                    matrix[i+1][j-1]++;
                if(i-1>=0&&j+1<sizey&&matrix[i-1][j+1]!=9)
                    matrix[i-1][j+1]++;
            }
        }
    }
    for(int i=0; i<sizex; i++)
    {
        for(int j=0; j<sizey; j++)
        {
            cout<<matrix[j][i]<<" ";
            if(j==sizey-1) cout<<endl;
        }
    }
    makeTen(matrix,i,j,i,j);
    beginFrame();
    for(int i=0; i<sizex; i++)
    {
        for(int j=0; j<sizey; j++)
        {
            if(matrix[i][j]==10)
            {
                overturn[i][j]=1;
                block[i][j].setColor(COLOR(210,210,210));
                if(i+1<sizex&&j+1<sizey&&matrix[i+1][j+1]!=10)
                {
                    overturn[i+1][j+1]=1;
                    block[i+1][j+1].setColor(COLOR(210,210,210));
                    number[i+1][j+1].reset(1250/2-(sizex-1)*40/2+(i+1)*40,350-(sizey-1)*40/2+(j+1)*40,matrix[i+1][j+1]);
                }
                if(j+1<sizey&&matrix[i][j+1]!=10)
                {
                    overturn[i][j+1]=1;
                    block[i][j+1].setColor(COLOR(210,210,210));
                    number[i][j+1].reset(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+(j+1)*40,matrix[i][j+1]);
                }
                if(i+1<sizex&&matrix[i+1][j]!=10)
                {
                    overturn[i+1][j]=1;
                    block[i+1][j].setColor(COLOR(210,210,210));
                    number[i+1][j].reset(1250/2-(sizex-1)*40/2+(i+1)*40,350-(sizey-1)*40/2+j*40,matrix[i+1][j]);
                }
                if(i-1>=0&&j-1>=0&&matrix[i-1][j-1]!=10)
                {
                    overturn[i-1][j-1]=1;
                    block[i-1][j-1].setColor(COLOR(210,210,210));
                    number[i-1][j-1].reset(1250/2-(sizex-1)*40/2+(i-1)*40,350-(sizey-1)*40/2+(j-1)*40,matrix[i-1][j-1]);
                }
                if(j-1>=0&&matrix[i][j-1]!=10)
                {
                    overturn[i][j-1]=1;
                    block[i][j-1].setColor(COLOR(210,210,210));
                    number[i][j-1].reset(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+(j-1)*40,matrix[i][j-1]);
                }
                if(i-1>=0&&matrix[i-1][j]!=10)
                {
                    overturn[i-1][j]=1;
                    block[i-1][j].setColor(COLOR(210,210,210));
                    number[i-1][j].reset(1250/2-(sizex-1)*40/2+(i-1)*40,350-(sizey-1)*40/2+j*40,matrix[i-1][j]);
                }
                if(i+1<sizex&&j-1>=0&&matrix[i+1][j-1]!=10)
                {
                    overturn[i+1][j-1]=1;
                    block[i+1][j-1].setColor(COLOR(210,210,210));
                    number[i+1][j-1].reset(1250/2-(sizex-1)*40/2+(i+1)*40,350-(sizey-1)*40/2+(j-1)*40,matrix[i+1][j-1]);
                }
                if(i-1>=0&&j+1<sizey&&matrix[i-1][j+1]!=10)
                {
                    overturn[i-1][j+1]=1;
                    block[i-1][j+1].setColor(COLOR(210,210,210));
                    number[i-1][j+1].reset(1250/2-(sizex-1)*40/2+(i-1)*40,350-(sizey-1)*40/2+(j+1)*40,matrix[i-1][j+1]);
                }

            }
        }
    }
    endFrame();
    while(1)
    {
        int i,j;
        if(getBlock(i,j))
        {
            if(flag[i][j]&&!overturn[i][j])
            {
                overturn[i][j]=1;
                block[i][j].setColor(COLOR(210,210,210));
                if(matrix[i][j]==9)
                    break;
                if(matrix[i][j]==0)
                {
                    beginFrame();
                    makeTen(matrix,i,j,i,j);
                    for(int i=0; i<sizex; i++)
                    {
                        for(int j=0; j<sizey; j++)
                        {
                            if(matrix[i][j]==10)
                            {
                                overturn[i][j]=1;
                                block[i][j].setColor(COLOR(210,210,210));
                                if(i+1<sizex&&j+1<sizey&&matrix[i+1][j+1]!=10)
                                {
                                    overturn[i+1][j+1]=1;
                                    block[i+1][j+1].setColor(COLOR(210,210,210));
                                    number[i+1][j+1].reset(1250/2-(sizex-1)*40/2+(i+1)*40,350-(sizey-1)*40/2+(j+1)*40,matrix[i+1][j+1]);
                                }
                                if(j+1<sizey&&matrix[i][j+1]!=10)
                                {
                                    overturn[i][j+1]=1;
                                    block[i][j+1].setColor(COLOR(210,210,210));
                                    number[i][j+1].reset(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+(j+1)*40,matrix[i][j+1]);
                                }
                                if(i+1<sizex&&matrix[i+1][j]!=10)
                                {
                                    overturn[i+1][j]=1;
                                    block[i+1][j].setColor(COLOR(210,210,210));
                                    number[i+1][j].reset(1250/2-(sizex-1)*40/2+(i+1)*40,350-(sizey-1)*40/2+j*40,matrix[i+1][j]);
                                }
                                if(i-1>=0&&j-1>=0&&matrix[i-1][j-1]!=10)
                                {
                                    overturn[i-1][j-1]=1;
                                    block[i-1][j-1].setColor(COLOR(210,210,210));
                                    number[i-1][j-1].reset(1250/2-(sizex-1)*40/2+(i-1)*40,350-(sizey-1)*40/2+(j-1)*40,matrix[i-1][j-1]);
                                }
                                if(j-1>=0&&matrix[i][j-1]!=10)
                                {
                                    overturn[i][j-1]=1;
                                    block[i][j-1].setColor(COLOR(210,210,210));
                                    number[i][j-1].reset(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+(j-1)*40,matrix[i][j-1]);
                                }
                                if(i-1>=0&&matrix[i-1][j]!=10)
                                {
                                    overturn[i-1][j]=1;
                                    block[i-1][j].setColor(COLOR(210,210,210));
                                    number[i-1][j].reset(1250/2-(sizex-1)*40/2+(i-1)*40,350-(sizey-1)*40/2+j*40,matrix[i-1][j]);
                                }
                                if(i+1<sizex&&j-1>=0&&matrix[i+1][j-1]!=10)
                                {
                                    overturn[i+1][j-1]=1;
                                    block[i+1][j-1].setColor(COLOR(210,210,210));
                                    number[i+1][j-1].reset(1250/2-(sizex-1)*40/2+(i+1)*40,350-(sizey-1)*40/2+(j-1)*40,matrix[i+1][j-1]);
                                }
                                if(i-1>=0&&j+1<sizey&&matrix[i-1][j+1]!=10)
                                {
                                    overturn[i-1][j+1]=1;
                                    block[i-1][j+1].setColor(COLOR(210,210,210));
                                    number[i-1][j+1].reset(1250/2-(sizex-1)*40/2+(i-1)*40,350-(sizey-1)*40/2+(j+1)*40,matrix[i-1][j+1]);
                                }

                            }
                        }

                    }
                    endFrame();
                }

                else if(matrix[i][j]!=10)
                    number[i][j].reset(1250/2-(sizex-1)*40/2+i*40,350-(sizey-1)*40/2+j*40,matrix[i][j]);

            }
            if(winCheck(matrix,overturn))
                break;
        }
        else if(!overturn[i][j])
        {
            flag[i][j]=!flag[i][j];
            if(flag[i][j]) {
                mine++;
                block[i][j].setColor(COLOR(50,205,50));
                count.reset(1250/2-(sizex-1)*40/2+(sizex)*40,350-(sizey-1)*40/2+(sizey)*40, mine);
            }
            else {
                mine--;
                block[i][j].setColor(COLOR(255,100,50));
                count.reset(1250/2-(sizex-1)*40/2+(sizex)*40,350-(sizey-1)*40/2+(sizey)*40, mine);
            }
        }

    }
    //BOMBS

    Line bombline(0,0,30,0);
    bombline.setColor(COLOR(128,128,128));
    Circle bombcircle(0,0,8);
    bombcircle.setFill(1);
    bombcircle.setColor(COLOR(128,128,128));
    beginFrame();
    for(int i=0; i<sizex; i++)
        for(int j=0; j<sizey; j++)
        {
            if(matrix[i][j]==9)
            {
                block[i][j].imprint();
                block[i][j].hide();
                bombline.moveTo(1250/2-sizex*40/2+40*i+20,350-sizey*40/2+40*j+20);
                for (int k = 0; k < 8; k++)
                {
                    bombline.imprint();
                    bombline.rotate(PI/6);

                }
                bombcircle.reset(1250/2-sizex*40/2+40*i+20,350-sizey*40/2+40*j+20,8);
                bombcircle.imprint();
            }

        }
    endFrame();
    wait(2);
    gameOver(winCheck(matrix,overturn));
}