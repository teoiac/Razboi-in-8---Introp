#include <iostream>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
bool prima=true;
const wchar_t* filePath = L"D:/Proiecte extra/RAZBOI_IN_8/design/music_loop.wav";

void playSound(const wchar_t* filePath)
{
    PlaySoundW(filePath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void stopSound()
{
    PlaySoundW(NULL, NULL, 0);
}

struct tabla
{
    int x,y;
    bool este_valida, este_piesa;//toate piesele albe vor fi valide, pentru ca sunt posibile mutari; mutarea se va putea realiza doar daca nu este piesa in casuta selectata pentru mutare
} matrice_tabla[10][10];
//trebuie initializate pozitiile valide
struct piese
{
    //int x,y;
    char jucator[256];
   // bool este_blocata;
} piesa[8][8];

struct vect_finn
{
    int i,j;
} vector_finn[10];

struct vect_jake
{
    int i,j;
} vector_jake[10];
void homepage(bool prima);//trebuie apelata inainte de restul functiilor care o apeleaza pentru a nu da eroare

void setari()
{
    clearviewport();
    int x,y;
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);
    setbkcolor(RED);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 38);
    outtextxy(250, 250,"Mod sunet");
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/sound.jpg", 650, 150, 730, 230);//buton sound
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/mute.jpg", 650, 300, 730,380);//buton mute
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back.jpg", 25, 25, 65, 65);//buton back
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=25 && x<=65)
    {
        //daca am apasat pe back
        if(y>=25 && y<=65)
        {
            homepage(false);
        }
    }
    else if (x>=650 && x <=730)
        //daca am apasat pe sound
        if(y >= 150 && y <= 230)
        {
            playSound(filePath);
            delay(1500);
            homepage(0);
        }
        else if(y>=300 && y<=380)
        {
            stopSound();
            delay(1500);
            homepage(0);

        }

}


void punere_piese()//pune piesele pe tabla in configuratia de start
{
    int i,startx=450,starty=450;
    for(i=2; i<=8; i+=2)
    {
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",startx,starty,startx+50,starty+50);
        matrice_tabla[8][i].este_piesa=true;
        strcpy(piesa[8][i].jucator,"jake");
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",startx-50,starty-50,startx,starty);
        strcpy(piesa[7][i-1].jucator,"jake");
        matrice_tabla[7][i-1].este_piesa=true;
        startx+=100;
    }
    startx=450, starty=150;
    for(i=2; i<=8; i+=2)
    {
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",startx,starty,startx+50,starty+50);
        matrice_tabla[1][i-1].este_piesa=true;
        strcpy(piesa[1][i-1].jucator,"finn");
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",startx-50,starty-50,startx,starty);
        strcpy(piesa[2][i].jucator,"finn");
        matrice_tabla[2][i].este_piesa=true;
        startx+=100;
    }
}


void tabla_joc()
{

    clearviewport();
    int x,y;
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/home.jpg", 25, 535, 65, 575);//buton home
    int startx=400, starty=100;
    int tabla[10][10], i, j;
    rectangle(350,50,850,550);
    setfillstyle(SOLID_FILL,RGB(0,102,0));
    bar(351,51,850,550);
    for(i=1; i<=8; i++)
    {
        for(j=1; j<=8; j++)
        {
            if(i%2==1)
            {
                if(j%2==1)
                {
                    matrice_tabla[i][j].x=startx;
                    matrice_tabla[i][j].y=starty;
                    rectangle(startx,starty,startx+50,starty+50);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(startx+1,starty+1,startx+50,starty+50);
                    startx+=50;
                }
                if(j%2==0)
                {
                    matrice_tabla[i][j].x=startx;
                    matrice_tabla[i][j].y=starty;
                    rectangle(startx,starty,startx+50,starty+50);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(startx+1,starty+1,startx+50,starty+50);
                    startx+=50;
                }
            }
            else if(i%2==0)
            {
                if(j%2==1)
                {
                    matrice_tabla[i][j].x=startx;
                    matrice_tabla[i][j].y=starty;
                    rectangle(startx,starty,startx+50,starty+50);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(startx+1,starty+1,startx+50,starty+50);
                    startx+=50;
                }
                if(j%2==0)
                {
                    matrice_tabla[i][j].x=startx;
                    matrice_tabla[i][j].y=starty;
                    rectangle(startx,starty,startx+50,starty+50);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(startx+1,starty+1,startx+50,starty+50);
                    startx+=50;
                }
            }
        }
        startx=400;
        starty+=50;
    }
    setbkcolor(RGB(0,102,0));
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    startx=415;
    outtextxy(startx,510,"A");
    startx+=50;
    outtextxy(startx,510,"B");
    startx+=50;
    outtextxy(startx,510,"C");
    startx+=50;
    outtextxy(startx,510,"D");
    startx+=50;
    outtextxy(startx,510,"E");
    startx+=50;
    outtextxy(startx,510,"F");
    startx+=50;
    outtextxy(startx,510,"G");
    startx+=50;
    outtextxy(startx,510,"H");

    starty=115;
    outtextxy(365,starty,"8");
    starty+=50;
    outtextxy(365,starty,"7");
    starty+=50;
    outtextxy(365,starty,"6");
    starty+=50;
    outtextxy(365,starty,"5");
    starty+=50;
    outtextxy(365,starty,"4");
    starty+=50;
    outtextxy(365,starty,"3");
    starty+=50;
    outtextxy(365,starty,"2");
    starty+=50;
    outtextxy(365,starty,"1");
    punere_piese();


}

void sterge_piese_blocate(tabla matrice_tabla[10][10])//bordez tabla cu piese, ca sa nu pot muta acolo
{
    for(int i=0; i<=9; i++)
    {
        matrice_tabla[0][i].este_piesa=1;
        matrice_tabla[9][i].este_piesa=1;
        matrice_tabla[i][0].este_piesa=1;
        matrice_tabla[i][9].este_piesa=1;
    }
    //puteam la fel de bine sa setez este_valida pe false
}
int piesa_blocata(int i, int j)
{
    //functia verifica daca piesa de pe linia i si coloana j este blocata; daca da, returneaza 1,altfel 0
    if(matrice_tabla[i-1][j-1].este_piesa && matrice_tabla[i-1][j+1].este_piesa && matrice_tabla[i+1][j-1].este_piesa && matrice_tabla[i+1][j+1].este_piesa)
        return 1;
    return 0;
}
int marceline;
struct obstacol_marceline
    {
        int i,j;
    } marceline_piesa[3];
 void obstacol(int marceline)
{
    int randi, randj, ok=0;
    if(marceline<2)
    {
        while(ok==0)
        {
            randi=rand()%8;
            randj=rand()%8;
            if(randi!=0 && randj!=0 && matrice_tabla[randi][randj].este_piesa==false && matrice_tabla[randi][randj].este_valida==true)
            {
                readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/marceline.jpg",matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
                matrice_tabla[randi][randj].este_piesa=true;
                strcpy(piesa[randi][randj].jucator,"marceline");
                marceline_piesa[marceline].i=randi;
                marceline_piesa[marceline].j=randj;
                ok=1;
            }
        }
    }
    else if(marceline==2)
    {
        for(int contor=0; contor<2; contor++)
        {
            randi=marceline_piesa[contor].i;
            randj=marceline_piesa[contor].j;
            rectangle(matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
            setfillstyle(SOLID_FILL,WHITE);
            bar(matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
            matrice_tabla[randi][randj].este_piesa=false;
            piesa[randi][randj].jucator[0]='\0';
        }
            marceline=0;
            while(marceline<2)
        {
            ok=0;
            while(ok==0)
            {
                randi=rand()%8;
                randj=rand()%8;
                if(randi!=0 && randj!=0 && matrice_tabla[randi][randj].este_piesa==false && matrice_tabla[randi][randj].este_valida==true)
                {
                    delay(500);
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/marceline.jpg",matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
                    matrice_tabla[randi][randj].este_piesa=true;
                    strcpy(piesa[randi][randj].jucator,"marceline");
                    marceline_piesa[marceline].i=randi;
                    marceline_piesa[marceline].j=randj;
                    ok=1;cout<<randi<<" "<<randj<<endl;
                }
            }
            marceline++;
        }
            }
}
void joc_1v1G(tabla matrice_tabla[10][10])
{
    tabla_joc();
    //pozitia initiala
    int nr_mutari=0, remiza=0;//mutari totale
    int i,c,d,j,i1,j1,nr_finn=8,nr_jake=8,finn=0,jake=1,a,b,finish=0;//nr_juc=nr. piese ramase si juc=randul cui e
    char ultima_mutare_coloana[2]="A",ultima_mutare_linie[2]="1";
    //setez casutele valide
    for(i=0; i<=9; i++)
    {
        for(j=0; j<=9; j++)
        {
            if(i==0 || i==9 || j==0 || j==9)
                matrice_tabla[i][j].este_valida=0;
            else if((i==1 || i==7) && j%2==1)
                matrice_tabla[i][j].este_valida=1;
            else if((i==2 || i==8) && j%2==0)
                matrice_tabla[i][j].este_valida=1;
            else if((i%2)==(j%2))
                matrice_tabla[i][j].este_valida=1;
            else
                matrice_tabla[i][j].este_valida=0;
            cout<<matrice_tabla[i][j].este_valida<<" ";
        }
        cout<<endl;
    }
    char minute[3]="00";
    char secunde[4]=":00";
    int contor=0;
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(50,100,"Este randul lui");
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",75,150,225,300);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    while(!finish)//cat timp nu s-a incheiat jocul
    {


        while (!ismouseclick(WM_LBUTTONDOWN))
        {

            delay(10);
            contor+=10;
            if(contor==1000)
            {
                secunde[2]++;
                if(secunde[2]=='9')
                {
                    secunde[2]='0';
                    secunde[1]++;
                }

                if(secunde[1]=='6'&&secunde[2]=='0')
                {
                    secunde[2]='0';
                    secunde[1]='0';
                    if(minute[1]=='9')
                    {
                        minute[1]='0';
                        minute[0]+=1;
                    }
                    else
                        minute[1]++;
                }
                outtextxy(1000,75,minute);
                outtextxy(1040,75,secunde);
                contor=0;
            }

        }

        getmouseclick(WM_LBUTTONDOWN, a, b);
        if(a>=25 && a<=65 && b>=535 && b<=575)
        {
            homepage(0);
            closegraph();
        }
        else
        {
            j=(a-400)/50+1;//linia primului click(casuta piesei pe care vreau sa o mut)
            i=(b-100)/50+1;//coloana primului click


if(strcmp(piesa[i][j].jucator,"jake")==0 && jake || strcmp(piesa[i][j].jucator,"finn")==0 && finn){
            setfillstyle(SOLID_FILL, RGB(34, 184, 7));
            if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true )
            {
                rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
            }
            if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
            {
                rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
            }
            if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true )
            {
                rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
            }
            if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
            {
                rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
            }

}
            while (!ismouseclick(WM_LBUTTONDOWN))
            {

                delay(10);
                contor+=10;
                if(contor==1000)
                {
                    secunde[2]++;
                    if(secunde[2]=='9')
                    {
                        secunde[2]='0';
                        secunde[1]++;
                    }

                    if(secunde[1]=='6'&&secunde[2]=='0')
                    {
                        secunde[2]='0';
                        secunde[1]='0';
                        if(minute[1]=='9')
                        {
                            minute[1]='0';
                            minute[0]+=1;
                        }
                        else
                            minute[1]++;
                    }
                    outtextxy(1000,75,minute);
                    outtextxy(1040,75,secunde);
                    contor=0;
                }

            }
            // afisez din nou cainele acolo
            getmouseclick(WM_LBUTTONDOWN, c, d);
            j1=(c-400)/50+1;//linia celui de-al doilea click(casuta pe care vreau sa mut)
            i1=(d-100)/50+1;//coloana celui de-al doilea click
            if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
                    }
                    if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
                    }
                    if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+51,matrice_tabla[i+1][j-1].y+51);
                    }
                    if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+51,matrice_tabla[i+1][j+1].y+51);
                    }
            if(matrice_tabla[i1][j1].este_valida==true && matrice_tabla[i1][j1].este_piesa==false && ((i1==i+1 && (j1==j-1 || j1==j+1)) || (i1==i-1 && (j1==j-1 || j1==j+1))))//coordonatele sunt pt a verifica daca casuta in care vreau sa mut este o accesare valida de pe cea selectata initial
                if((strcmp(piesa[i][j].jucator,"finn")==0 && finn==1) || (strcmp(piesa[i][j].jucator,"jake")==0 && jake==1))//daca piesa pe care vreau sa o mut e a jucatorului care este la rand
                {

                    if(jake)
                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",matrice_tabla[i1][j1].x,matrice_tabla[i1][j1].y,matrice_tabla[i1][j1].x+50,matrice_tabla[i1][j1].y+50);
                    else
                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[i1][j1].x,matrice_tabla[i1][j1].y,matrice_tabla[i1][j1].x+50,matrice_tabla[i1][j1].y+50);
                    matrice_tabla[i1][j1].este_piesa=true;//casuta in care ma mut
                    matrice_tabla[i][j].este_piesa=false;//casuta de pe care plec
                    nr_mutari++;
                    ultima_mutare_coloana[0]='A'+(j1-1);
                    ultima_mutare_coloana[1]=NULL;
                    ultima_mutare_linie[0]='8'-(i1-1);
                    ultima_mutare_linie[1]=NULL;
                    outtextxy(920,250,"Ultima mutare:");
                    outtextxy(1000,275,ultima_mutare_coloana);
                    outtextxy(1025,275,ultima_mutare_linie);
                     if(nr_mutari>=8)//fiecare juc are la dispozitie 4 mutari pt a-si elibera piesele initial blocate
                        sterge_piese_blocate(matrice_tabla);
                    if(finn)
                        strcpy(piesa[i1][j1].jucator,"finn");
                    else
                        strcpy(piesa[i1][j1].jucator,"jake");
                    piesa[i][j].jucator[0]='\0';
                    //eliberez casuta de pe care plec
                    rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                    //verific piesele blocate pt. a le elimina
                    if(nr_mutari==20)
                        obstacol(0);
                    if(nr_mutari==24)
                        obstacol(1);
                    if(nr_mutari>24 && nr_mutari%2==0)
                        obstacol(2);

                    for(int ci=1; ci<=8; ci++)
                        for(int cj=1; cj<=8; cj++)
                            if(matrice_tabla[ci][cj].este_piesa==1)
                                if(piesa_blocata(ci,cj))
                                {
                                    //verific cui apaertine piesa blocata
                                    if(strcmp(piesa[i][j].jucator,"finn")==0)
                                        nr_finn--;
                                    else if(strcmp(piesa[i][j].jucator,"jake")==0)
                                        nr_jake--;
                                    //elimin piesa blocata
                                    matrice_tabla[ci][cj].este_piesa=false;
                                    rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                }
                    //cand fac o mutare valida se schimba randul jucatorilor
                    swap(finn,jake);
                    if(finn)
                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",75,150,225,300);
                    else
                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",75,150,225,300);
                    if(nr_mutari<=50)
                    {
                        if((nr_finn==1 && nr_jake==2) || (nr_finn==2 && nr_jake==1))
                            finish=1;
                        else
                            finish=0;
                    }
                    else
                        finish=1,remiza=1;



                }
        }
    }

    if(remiza==1)
        outtextxy(300,300,"Remiza!");
    else if(nr_finn>nr_jake)
    {
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/winner_finn.jpg",0,0, 1200, 600);
        outtextxy(300,300, "Finn a castigat razboiul!");
    }

    else
    {
        outtextxy(300,300, "Jack a castigat razboiul!");
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/winner_jake.jpg",0,0, 1200, 600);
    }
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/buton_replay.jpg",900,500,1108,550 );
    getmouseclick(WM_LBUTTONDOWN, a, b);
    if(a>=900 && a<=1108 && b>=500 && b<=550)
    {
        joc_1v1G(matrice_tabla);
    }
}
void joc_1v1U(tabla matrice_tabla[10][10])
{
    tabla_joc();
    //pozitia initiala
    int nr_mutari=0, remiza=0;//mutari totale
    int i,c,d,j,i1,j1,nr_finn=8,nr_jake=8,finn=0,jake=1,a,b,finish=0;//nr_juc=nr. piese ramase si juc=randul cui e
    char ultima_mutare_coloana[2]="A",ultima_mutare_linie[2]="1";
    //setez casutele valide
    for(i=0; i<=9; i++)
    {
        for(j=0; j<=9; j++)
        {
            if(i==0 || i==9 || j==0 || j==9)
                matrice_tabla[i][j].este_valida=0;
            else if((i==1 || i==7) && j%2==1)
                matrice_tabla[i][j].este_valida=1;
            else if((i==2 || i==8) && j%2==0)
                matrice_tabla[i][j].este_valida=1;
            else if((i%2)==(j%2))
                matrice_tabla[i][j].este_valida=1;
            else
                matrice_tabla[i][j].este_valida=0;
            cout<<matrice_tabla[i][j].este_valida<<" ";
        }
        cout<<endl;
    }
    char minute[3]="00";
    char secunde[4]=":00";
    int contor=0;
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(50,100,"Este randul lui");
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",75,150,225,300);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    while(!finish)//cat timp nu s-a incheiat jocul
    {
        while (!ismouseclick(WM_LBUTTONDOWN))
        {

            delay(10);
            contor+=10;
            if(contor==1000)
            {
                secunde[2]++;
                if(secunde[2]=='9')
                {
                    secunde[2]='0';
                    secunde[1]++;
                }
                if(secunde[1]=='6'&&secunde[2]=='0')
                {
                    secunde[2]='0';
                    secunde[1]='0';
                    if(minute[1]=='9')
                    {
                        minute[1]='0';
                        minute[0]+=1;
                    }
                    else
                        minute[1]++;
                }
                contor=0;
                outtextxy(1000,75,minute);
                outtextxy(1050,75,secunde);
            }
        }
        getmouseclick(WM_LBUTTONDOWN, a, b);
        if(a>=25 && a<=65 && b>=535 && b<=575)
        {
            homepage(0);
            closegraph();
        }
        else{
        j=(a-400)/50+1;//linia primului click(casuta piesei pe care vreau sa o mut)
        i=(b-100)/50+1;//coloana primului click
        if(strcmp(piesa[i][j].jucator,"jake")==0 && jake || strcmp(piesa[i][j].jucator,"finn")==0 && finn){
        setfillstyle(SOLID_FILL, RGB(34, 184, 7));
            if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true )
            {
                rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
            }
            if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
            {
                rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
            }
            if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true )
            {
                rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
            }
            if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
            {
                rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
            }
        }
        //chenarul piesei selectate
        while (!ismouseclick(WM_LBUTTONDOWN))
        {
            delay(10);
            contor+=10;
            if(contor==1000)
            {
                secunde[2]++;
                if(secunde[2]=='9')
                {
                    secunde[2]='0';
                    secunde[1]++;
                }
                if(secunde[1]=='6'&&secunde[2]=='0')
                {
                    secunde[2]='0';
                    secunde[1]='0';
                    if(minute[1]=='9')
                    {
                        minute[1]='0';
                        minute[0]+=1;
                    }
                    else
                        minute[1]++;
                }
                contor=0;
                outtextxy(1000,75,minute);
                outtextxy(1050,75,secunde);
            }
        }
        getmouseclick(WM_LBUTTONDOWN, c, d);
        j1=(c-400)/50+1;//linia celui de-al doilea click(casuta pe care vreau sa mut)
        i1=(d-100)/50+1;//coloana celui de-al doilea click

        if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true)
            {
                rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
            }
            if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
            {
                rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
            }
            if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true)
            {
                rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+51,matrice_tabla[i+1][j-1].y+51);
            }
            if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
            {
                rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+51,matrice_tabla[i+1][j+1].y+51);
            }

        if(matrice_tabla[i1][j1].este_valida==true && matrice_tabla[i1][j1].este_piesa==false && ((i1==i+1 && (j1==j-1 || j1==j+1)) || (i1==i-1 && (j1==j-1 || j1==j+1))))//coordonatele sunt pt a verifica daca casuta in care vreau sa mut este o accesare valida de pe cea selectata initial
            if((strcmp(piesa[i][j].jucator,"finn")==0 && finn==1) || (strcmp(piesa[i][j].jucator,"jake")==0 && jake==1))//daca piesa pe care vreau sa o mut e a jucatorului care este la rand
            {
                if(jake)
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",matrice_tabla[i1][j1].x,matrice_tabla[i1][j1].y,matrice_tabla[i1][j1].x+50,matrice_tabla[i1][j1].y+50);
                else
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[i1][j1].x,matrice_tabla[i1][j1].y,matrice_tabla[i1][j1].x+50,matrice_tabla[i1][j1].y+50);
                matrice_tabla[i1][j1].este_piesa=true;//casuta in care ma mut
                matrice_tabla[i][j].este_piesa=false;//casuta de pe care plec
                nr_mutari++;
                if(nr_mutari==10)
                    obstacol(0);
                if(nr_mutari==14)
                    obstacol(1);
                if(nr_mutari>14 && nr_mutari%2==0)
                    obstacol(2);
                ultima_mutare_coloana[0]='A'+(j1-1);
                    ultima_mutare_coloana[1]=NULL;
                    ultima_mutare_linie[0]='8'-(i1-1);
                    ultima_mutare_linie[1]=NULL;
                    outtextxy(880,250,"Ultima mutare:");
                    outtextxy(1000,275,ultima_mutare_coloana);
                    outtextxy(1025,275,ultima_mutare_linie);
                if(nr_mutari==8)//fiecare juc are la dispozitie 4 mutari pt a-si elibera piesele initial blocate
                    sterge_piese_blocate(matrice_tabla);
                if(finn)
                    strcpy(piesa[i1][j1].jucator,"finn");
                else
                    strcpy(piesa[i1][j1].jucator,"jake");
                piesa[i][j].jucator[0]='\0';
                //eliberez casuta de pe care plec
                rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                //verific piesele blocate pt. a le elimina
                for(int ci=1;ci<=8;ci++){
                    for(int cj=1;cj<=8;cj++){
                        if(matrice_tabla[ci][cj].este_piesa==1)
                            if(piesa_blocata(ci,cj) && strcmp(piesa[ci][cj].jucator,"marceline"))
                            {
                                //verific cui apartine piesa blocata
                                if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                    nr_finn--;
                                else
                                    nr_jake--;
                                //elimin piesa blocata
                                matrice_tabla[ci][cj].este_piesa=false;
                                rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                setfillstyle(SOLID_FILL, WHITE);
                                piesa[ci][cj].jucator[0]='\0';
                                bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                            }
                            cout<<matrice_tabla[ci][cj].este_piesa<<piesa[ci][cj].jucator<<" ";
                    }
                    cout<<endl;
            } cout<<endl;
                //cand fac o mutare valida se schimba randul jucatorilor
                swap(finn,jake);
                if(finn)
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",75,150,225,300);
                else
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",75,150,225,300);
                //verific daca jocul s-a incheiat
                if(nr_mutari<=50)
                    if((nr_finn==1 && nr_jake>=2)||(nr_finn>=2 && nr_jake==1))
                        finish=1;
                    else
                        finish=0;
                else
                    remiza=1, finish=1;
            }
        }
    }

    if(remiza==1)
        outtextxy(300,300,"Remiza!");
    else if(nr_finn>nr_jake)
    {
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/winner_finn.jpg",0,0, 1200, 600);
        outtextxy(300,300, "Finn a castigat razboiul!");
    }

    else
    {
        outtextxy(300,300, "Jack a castigat razboiul!");
        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/winner_jake.jpg",0,0, 1200, 600);
    }
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/buton_replay.jpg",900,500,1108,550 );
    getmouseclick(WM_LBUTTONDOWN, a, b);
    if(a>=900 && a<=1108 && b>=500 && b<=550)
    {
        joc_1v1U(matrice_tabla);
    }
}



void verifica_blocare(int i, int j, int &mi, int &mj)
{
    mi = -1;
    mj = -1;

    // stanga sus, drpt sus, stg jos
    if (matrice_tabla[i - 1][j - 1].este_piesa == 1 &&
            matrice_tabla[i - 1][j + 1].este_piesa == 1 &&
            matrice_tabla[i + 1][j - 1].este_piesa == 1 && (strcmp(piesa[i+2][j-2].jucator,"jake")|| strcmp(piesa[i+2][j+2].jucator,"jake")|| strcmp(piesa[i-2][j+2].jucator,"jake")) )
    {

        mi = i + 1;
        mj = j + 1;

        return;
    }

    // stg sus, drp sus, drp jos
    if (matrice_tabla[i - 1][j - 1].este_piesa == 1 &&
            matrice_tabla[i - 1][j + 1].este_piesa == 1 &&
            matrice_tabla[i + 1][j + 1].este_piesa == 1 && (strcmp(piesa[i+2][j-2].jucator,"jake")|| strcmp(piesa[i+2][j+2].jucator,"jake")|| strcmp(piesa[i-2][j-2].jucator,"jake")))
    {
        mi = i + 1;
        mj = j - 1;
        return;
    }

    // stg jos, drp jos, drp sus
    if (matrice_tabla[i - 1][j + 1].este_piesa == 1 &&
            matrice_tabla[i + 1][j + 1].este_piesa == 1 &&
            matrice_tabla[i + 1][j - 1].este_piesa == 1 &&(strcmp(piesa[i-2][j-2].jucator,"jake")|| strcmp(piesa[i-2][j+2].jucator,"jake")|| strcmp(piesa[i+2][j-2].jucator,"jake")) )
    {
        mi = i - 1;
        mj = j - 1;
        return;
    }

    // stg jos, drp jos, stg sus
    if (matrice_tabla[i - 1][j - 1].este_piesa == 1 &&
            matrice_tabla[i + 1][j - 1].este_piesa == 1 &&
            matrice_tabla[i + 1][j + 1].este_piesa == 1 && (strcmp(piesa[i+2][j+2].jucator,"jake")|| strcmp(piesa[i-2][j+2].jucator,"jake")|| strcmp(piesa[i-2][j-2].jucator,"jake")))
    {
        mi = i - 1;
        mj = j + 1;
        return;
    }
}


void mutare_random(int &mi, int &mj, int &randi, int & randj)
{
    int ok = 0;
    srand(time(0));
    while (ok == 0)
    {
        randi = rand()%8;
        randj = rand()%8;
        if(matrice_tabla[randi][randj].este_piesa == 1 && strcmp(piesa[randi][randj].jucator, "finn") == 0 && randi*randj)
        {
        if(matrice_tabla[randi + 1][randj - 1].este_piesa == 0 && randi!=7 && randj!=1 && matrice_tabla[randi+1][randj-1].este_valida==true)
            {
                mi = randi + 1;
                mj = randj - 1;
                ok = 1;
            }
            else
                if(matrice_tabla[randi + 1][randj + 1].este_piesa == 0 && randi!=7 && randj!=7 && matrice_tabla[randi+1][randj+1].este_valida==true)
            {
                mi = randi + 1;
                mj = randj + 1;
                ok = 1;
            }
            else
                if( matrice_tabla[randi - 1][randj - 1].este_piesa == 0 && randi!=1 && randj!=1 && matrice_tabla[randi-1][randj-1].este_valida==true)
            {
                mi = randi - 1;
                mj = randj - 1;
                ok = 1;
            }
            else
                if( matrice_tabla[randi - 1][randj + 1].este_piesa == 0 && randi!=1 && randj!=7 && matrice_tabla[randi-1][randj+1].este_valida==true)
            {
                mi = randi - 1;
                mj = randj + 1;
                ok = 1;
            }
        }
    }
}

void joc_1vC(tabla matrice_tabla[10][10])
{
    tabla_joc();
    //pozitia initiala
    int nr_mutari=0;//mutari totale
    int i,c,d,j,i1,j1,nr_finn=8,nr_jake=8,finn=0,jake=1,a,b,finish=0, remiza=0;//nr_juc=nr. piese ramase si juc=randul cui e
    char minute[3]="00";
    char secunde[4]=":00";
    int contor=0;
    punere_piese();
    //setez casutele valide(casutele albe)
    for(i=0; i<=9; i++)
        for(j=0; j<=9; j++)
            if(i==0 || i==9 || j==0 || j==9)
                matrice_tabla[i][j].este_valida=0;
            else if((i==1 || i==7) && j%2==1)
                matrice_tabla[i][j].este_valida=1;
            else if((i==2 || i==8) && j%2==0)
                matrice_tabla[i][j].este_valida=1;
            else if((i%2)==(j%2))
                matrice_tabla[i][j].este_valida=1;
            else
                matrice_tabla[i][j].este_valida=0;
    while(!finish)//cat timp nu s-a incheiat jocul
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(50,100,"Este randul lui");
        if(jake==1)//daca e randul lui jake
        {
             readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",75,150,225,300);
            while (!ismouseclick(WM_LBUTTONDOWN))
            {
                delay(100);
            }
            getmouseclick(WM_LBUTTONDOWN, a, b);
            if(a>=25 && a<=65 && b>=535 && b<=575)
            {
                homepage(0);
                closegraph();
            }
            else
            {
                j=(a-400)/50+1;//linia primului click(casuta piesei pe care vreau sa o mut)
                i=(b-100)/50+1;//coloana primului click
                if(strcmp(piesa[i][j].jucator, "jake")==0)
                {


                setfillstyle(SOLID_FILL, RGB(34, 184, 7));

                if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true )
                {
                    rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                    bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
                }
                if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
                {
                    rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                    bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
                }
                if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true )
                {
                    rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                    bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                }
                if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
                {
                    rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                    bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                }
}

                while (!ismouseclick(WM_LBUTTONDOWN))
                {
                    delay(10);
                }
                getmouseclick(WM_LBUTTONDOWN, c, d);
                j1=(c-400)/50+1;//linia celui de-al doilea click(casuta pe care vreau sa mut)
                i1=(d-100)/50+1;//coloana celui de-al doilea click
                if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
                    }
                    if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
                    }
                    if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+51,matrice_tabla[i+1][j-1].y+51);
                    }
                    if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+51,matrice_tabla[i+1][j+1].y+51);
                    }
                if(strcmp(piesa[i][j].jucator,"jake")==0 && matrice_tabla[i1][j1].este_valida==true && matrice_tabla[i1][j1].este_piesa==false && ((i1==i+1 && (j1==j-1 || j1==j+1)) || (i1==i-1 && (j1==j-1 || j1==j+1))))//coordonatele sunt pt a verifica daca casuta in care vreau sa mut este o accesare valida de pe cea selectata initial
                {

                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",matrice_tabla[i1][j1].x,matrice_tabla[i1][j1].y,matrice_tabla[i1][j1].x+50,matrice_tabla[i1][j1].y+50);
                    matrice_tabla[i1][j1].este_piesa=true;//casuta in care ma mut
                    matrice_tabla[i][j].este_piesa=false;//casuta de pe care plec
                    for(int ci=1; ci<=8; ci++)
                        for(int cj=1; cj<=8; cj++)
                            if(matrice_tabla[ci][cj].este_piesa==1)
                                if(piesa_blocata(ci,cj))
                                {
                                    //verific cui apartine piesa blocata
                                    if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                        nr_finn--;
                                    else
                                        nr_jake--;
                                    //elimin piesa blocata
                                    matrice_tabla[ci][cj].este_piesa=false;
                                    piesa[ci][cj].jucator[0]='\0';
                                    rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                }
                    nr_mutari++;
                    strcpy(piesa[i1][j1].jucator,"jake");
                    piesa[i][j].jucator[0]='\0';
                    //eliberez casuta de pe care plec
                    rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                    //verific piesele blocate pt. a le elimina
                    for(int ci=1; ci<=8; ci++)
                        for(int cj=1; cj<=8; cj++)
                            if(matrice_tabla[ci][cj].este_piesa==1)
                                if(piesa_blocata(ci,cj))
                                {
                                    //verific cui apartine piesa blocata
                                    if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                        nr_finn--;
                                    else
                                        nr_jake--;
                                    //elimin piesa blocata
                                    matrice_tabla[ci][cj].este_piesa=false;
                                    piesa[ci][cj].jucator[0]='\0';
                                    rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                }
                    //cand fac o mutare valida se schimba randul jucatorilor
                    swap(finn,jake);
                }
            }
        }
        else
        {
            readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",75,150,225,300);
            if(nr_mutari==1)
            {
                matrice_tabla[2][2].este_piesa=false;
                matrice_tabla[3][1].este_piesa=true;
                delay(500);
                readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[3][1].x,matrice_tabla[3][1].y,matrice_tabla[3][1].x+50,matrice_tabla[3][2].y+50);
                nr_mutari++;
                rectangle(matrice_tabla[2][2].x,matrice_tabla[2][2].y,matrice_tabla[2][2].x+50,matrice_tabla[2][2].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[2][2].x,matrice_tabla[2][2].y,matrice_tabla[2][2].x+50,matrice_tabla[2][2].y+50);
                strcpy(piesa[3][1].jucator,"finn");
                piesa[2][2].jucator[0]='\0';
            }
            else if(nr_mutari==3)
            {
                matrice_tabla[2][6].este_piesa=false;
                matrice_tabla[3][5].este_piesa=true;
                delay(500);
                readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[3][5].x,matrice_tabla[3][5].y,matrice_tabla[3][5].x+50,matrice_tabla[3][5].y+50);
                nr_mutari++;
                rectangle(matrice_tabla[2][6].x,matrice_tabla[2][6].y,matrice_tabla[2][6].x+50,matrice_tabla[2][6].y+50);
                setfillstyle(SOLID_FILL, WHITE);
                bar(matrice_tabla[2][6].x,matrice_tabla[2][6].y,matrice_tabla[2][6].x+50,matrice_tabla[2][6].y+50);
                strcpy(piesa[3][5].jucator,"finn");
                piesa[2][6].jucator[0]='\0';
            }
            else
            {
                int mi=-1,ci=0,cj=0, mj=-1;
                int ok=0;
                for(i=1; i<=8 && ci*cj==0; i++)
                    for(j=1; j<=8 && ci*cj==0; j++)
                        if(i%2==j%2)
                            if(strcmp(piesa[i][j].jucator,"finn")==0)
                            {
                                if(matrice_tabla[i-1][j-1].este_piesa==0)
                                {
                                    matrice_tabla[i-1][j-1].este_piesa=true;
                                    if(piesa_blocata(i-2,j-2) && strcmp(piesa[i-2][j-2].jucator,"jake")==0)
                                        ci=i-2, cj=j-2;
                                    else if(piesa_blocata(i-2,j) && strcmp(piesa[i-2][j].jucator,"jake")==0)
                                        ci=i-2, cj=j;
                                    else if(piesa_blocata(i,j-2) && strcmp(piesa[i][j-2].jucator,"jake")==0)
                                        ci=i,cj=j-2;
                                    else
                                        matrice_tabla[i-1][j-1].este_piesa=false;
                                    if(ci*cj)
                                    {
                                        delay(500);
                                        cout<<"1"<<ci<<" "<<cj;
                                        matrice_tabla[ci][cj].este_piesa=false;
                                        strcpy(piesa[i-1][j-1].jucator,"finn");
                                        piesa[ci][cj].jucator[0]='\0';
                                        rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        nr_jake--;
                                        bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                                    }
                                }
                                else if(matrice_tabla[i-1][j+1].este_piesa==0)
                                {
                                    matrice_tabla[i-1][j+1].este_piesa=true;
                                    if(piesa_blocata(i-2,j) && strcmp(piesa[i-2][j].jucator,"jake")==0)
                                        ci=i-2, cj=j;
                                    else if(piesa_blocata(i-2,j+2) && strcmp(piesa[i-2][j+2].jucator,"jake")==0)
                                        ci=i-2, cj=j+2;
                                    else if(piesa_blocata(i,j+2) && strcmp(piesa[i][j+2].jucator,"jake")==0)
                                        ci=i,cj=j+2;
                                    else
                                        matrice_tabla[i-1][j+1].este_piesa=false;
                                    if(ci*cj)
                                    {
                                        delay(500);
                                        cout<<"2"<<ci<<" "<<cj;
                                        matrice_tabla[ci][cj].este_piesa=false;
                                        strcpy(piesa[i-1][j+1].jucator,"finn");
                                        piesa[ci][cj].jucator[0]='\0';
                                        rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        nr_jake--;
                                        bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                                    }
                                }
                                else if(matrice_tabla[i+1][j-1].este_piesa==0)
                                {
                                    matrice_tabla[i+1][j-1].este_piesa=true;
                                    if(piesa_blocata(i+2,j) && strcmp(piesa[i+2][j].jucator,"jake")==0)
                                        ci=i+2, cj=j;
                                    else if(piesa_blocata(i+2,j-2) && strcmp(piesa[i+2][j-2].jucator,"jake")==0)
                                        ci=i+2, cj=j-2;
                                    else if(piesa_blocata(i,j-2) && strcmp(piesa[i][j-2].jucator,"jake")==0)
                                        ci=i,cj=j-2;
                                    else
                                        matrice_tabla[i+1][j-1].este_piesa=false;
                                    if(ci*cj)
                                    {
                                        delay(500);
                                        cout<<"3"<<ci<<" "<<cj;

                                        matrice_tabla[ci][cj].este_piesa=false;
                                        strcpy(piesa[i+1][j-1].jucator,"finn");
                                        piesa[ci][cj].jucator[0]='\0';
                                        rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        nr_jake--;
                                        bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                                    }
                                }
                                else if(matrice_tabla[i+1][j+1].este_piesa==0)
                                {
                                    matrice_tabla[i+1][j+1].este_piesa=true;
                                    if(piesa_blocata(i+2,j) && strcmp(piesa[i+2][j].jucator,"jake")==0)
                                        ci=i+2, cj=j;
                                    else if(piesa_blocata(i+2,j+2) && strcmp(piesa[i+2][j+2].jucator,"jake")==0)
                                        ci=i+2, cj=j+2;
                                    else if(piesa_blocata(i,j+2) && strcmp(piesa[i][j+2].jucator,"jake")==0)
                                        ci=i,cj=j+2;
                                    else
                                        matrice_tabla[i+1][j+1].este_piesa=false;
                                    if(ci*cj)
                                    {
                                        delay(500);
                                        cout<<"4"<<ci<<" "<<cj;
                                        matrice_tabla[ci][cj].este_piesa=false;
                                        strcpy(piesa[i+1][j+1].jucator,"finn");
                                        piesa[ci][cj].jucator[0]='\0';
                                        rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        nr_jake--;
                                        bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                                    }
                                }
                            }
                if(ci*cj==0)
                {
                    for(i=1; i<=8 && ok==0; i++)
                        for(j=1; j<=8 && ok==0; j++)
                            if(i%2==j%2)
                                if(strcmp(piesa[i][j].jucator,"finn")==0)
                                {
                                    // prioritate 2 : verifica daca o piesa risca sa fie luata

                                    verifica_blocare(i,j,mi,mj);
                                    if(mi!=-1 && mj!=-1)
                                    {
                                        matrice_tabla[i][j].este_piesa=false;
                                        matrice_tabla[mi][mj].este_piesa=true;
                                        delay(500);
                                        readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[mi][mj].x,matrice_tabla[mi][mj].y,matrice_tabla[mi][mj].x+50,matrice_tabla[mi][mj].y+50);
                                        nr_mutari++;
                                        rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        setfillstyle(SOLID_FILL, WHITE);
                                        bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                                        strcpy(piesa[mi][mj].jucator,"finn");
                                        piesa[i][j].jucator[0]='\0';
                                        ok=1;
                                        cout<<"mutare defensiva"<<endl;

                                    }
                                }

                }

                if(mi==-1 && mj==-1 && ci==0 && cj==0)
                {

                    int randi, randj, t,w, b;
                    mutare_random(t,w, randi, randj);
                    matrice_tabla[t][w].este_piesa=true;
                    matrice_tabla[randi][randj].este_piesa=false;
                    delay(500);
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[t][w].x,matrice_tabla[t][w].y,matrice_tabla[t][w].x+50,matrice_tabla[t][w].y+50);
                    nr_mutari++;
                    rectangle(matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
                    strcpy(piesa[t][w].jucator,"finn");
                    piesa[randi][randj].jucator[0]='\0';
                    cout<<"mutare random"<<endl;
                }
            }
            if(nr_mutari==8)
                sterge_piese_blocate(matrice_tabla);
            for(int ci=1; ci<=8; ci++)
                for(int cj=1; cj<=8; cj++)
                    if(matrice_tabla[ci][cj].este_piesa==1)
                        if(piesa_blocata(ci,cj))
                        {

                            ;//verific cui apartine piesa blocata
                            if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                nr_finn--;
                            else
                                nr_jake--;
                            //elimin piesa blocata
                            matrice_tabla[ci][cj].este_piesa=false;
                            piesa[ci][cj].jucator[0]='\0';
                            rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                            setfillstyle(SOLID_FILL, WHITE);
                            bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                        }
            swap(finn,jake);
        }
    }

    if(nr_mutari<=50)
        if((nr_finn==1 && nr_jake>=2)||(nr_finn>=2 && nr_jake==1))
            finish=1;
        else
            finish=0;
    else
        remiza=1, finish=1;
}


void joc_1vC1(tabla matrice_tabla[10][10])
{
    tabla_joc();
    //pozitia initiala
    int nr_mutari=0;//mutari totale
    int i,c,d,j,i1,j1,nr_finn=8,nr_jake=8,finn=0,jake=1,a,b,finish=0,remiza=0;//nr_juc=nr. piese ramase si juc=randul cui e
    char ultima_mutare_coloana[2]="A",ultima_mutare_linie[2]="1";
    punere_piese();
    //setez casutele valide(casutele albe)
    for(i=0; i<=9; i++)
        for(j=0; j<=9; j++)
            if(i==0 || i==9 || j==0 || j==9)
                matrice_tabla[i][j].este_valida=0;
            else if((i==1 || i==7) && j%2==1)
                matrice_tabla[i][j].este_valida=1;
            else if((i==2 || i==8) && j%2==0)
                matrice_tabla[i][j].este_valida=1;
            else if((i%2)==(j%2))
                matrice_tabla[i][j].este_valida=1;
            else
                matrice_tabla[i][j].este_valida=0;
    while(!finish)//cat timp nu s-a incheiat jocul
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(50,100,"Este randul lui");

        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        if(jake==1)//daca e randul lui jake
        {
            readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",75,150,225,300);
            while (!ismouseclick(WM_LBUTTONDOWN))
            {
                delay(100);
            }
            getmouseclick(WM_LBUTTONDOWN, a, b);
            if(a>=25 && a<=65 && b>=535 && b<=575)
            {
                homepage(0);
                closegraph();
            }
            else
            {
                j=(a-400)/50+1;//linia primului click(casuta piesei pe care vreau sa o mut)
                i=(b-100)/50+1;//coloana primului click
                if(strcmp(piesa[i][j].jucator,"jake")==0){
                setfillstyle(SOLID_FILL, RGB(34, 184, 7));
                if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true )
                {
                    rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                    bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
                }
                if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
                {
                    rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                    bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
                }
                if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true )
                {
                    rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                    bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                }
                if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
                {
                    rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                    bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                }
                }
                while (!ismouseclick(WM_LBUTTONDOWN))
                {
                    delay(10);
                }
                getmouseclick(WM_LBUTTONDOWN, c, d);
                j1=(c-400)/50+1;//linia celui de-al doilea click(casuta pe care vreau sa mut)
                i1=(d-100)/50+1;//coloana celui de-al doilea click
                if(matrice_tabla[i-1][j-1].este_piesa==false && matrice_tabla[i-1][j-1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+50,matrice_tabla[i-1][j-1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i-1][j-1].x,matrice_tabla[i-1][j-1].y,matrice_tabla[i-1][j-1].x+51,matrice_tabla[i-1][j-1].y+51);
                    }
                    if(matrice_tabla[i-1][j+1].este_piesa==false && matrice_tabla[i-1][j+1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+50,matrice_tabla[i-1][j+1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i-1][j+1].x,matrice_tabla[i-1][j+1].y,matrice_tabla[i-1][j+1].x+51,matrice_tabla[i-1][j+1].y+51);
                    }
                    if(matrice_tabla[i+1][j-1].este_piesa==false && matrice_tabla[i+1][j-1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+50,matrice_tabla[i+1][j-1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i+1][j-1].x,matrice_tabla[i+1][j-1].y,matrice_tabla[i+1][j-1].x+51,matrice_tabla[i+1][j-1].y+51);
                    }
                    if(matrice_tabla[i+1][j+1].este_piesa==false && matrice_tabla[i+1][j+1].este_valida==true)
                    {
                        rectangle(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+50,matrice_tabla[i+1][j+1].y+50);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(matrice_tabla[i+1][j+1].x,matrice_tabla[i+1][j+1].y,matrice_tabla[i+1][j+1].x+51,matrice_tabla[i+1][j+1].y+51);
                    }
                if(strcmp(piesa[i][j].jucator,"jake")==0 && matrice_tabla[i1][j1].este_valida==true && matrice_tabla[i1][j1].este_piesa==false && ((i1==i+1 && (j1==j-1 || j1==j+1)) || (i1==i-1 && (j1==j-1 || j1==j+1))))//coordonatele sunt pt a verifica daca casuta in care vreau sa mut este o accesare valida de pe cea selectata initial
                {
                    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_jake.jpg",matrice_tabla[i1][j1].x,matrice_tabla[i1][j1].y,matrice_tabla[i1][j1].x+50,matrice_tabla[i1][j1].y+50);
                    matrice_tabla[i1][j1].este_piesa=true;//casuta in care ma mut
                    matrice_tabla[i][j].este_piesa=false;//casuta de pe care plec
                    for(int ci=1; ci<=8; ci++)
                        for(int cj=1; cj<=8; cj++)
                            if(matrice_tabla[ci][cj].este_piesa==1)
                                if(piesa_blocata(ci,cj))
                                {
                                    //verific cui apartine piesa blocata
                                    if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                        nr_finn--;
                                    else
                                        nr_jake--;
                                    //elimin piesa blocata
                                    matrice_tabla[ci][cj].este_piesa=false;
                                    piesa[ci][cj].jucator[0]='\0';
                                    rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                }
                    nr_mutari++;
                    ultima_mutare_coloana[0]='A'+(j1-1);
                    ultima_mutare_coloana[1]=NULL;
                    ultima_mutare_linie[0]='8'-(i1-1);
                    ultima_mutare_linie[1]=NULL;
                    outtextxy(920,250,"Ultima mutare:");
                    outtextxy(1000,275,ultima_mutare_coloana);
                    outtextxy(1025,275,ultima_mutare_linie);
                    strcpy(piesa[i1][j1].jucator,"jake");
                    piesa[i][j].jucator[0]='\0';
                    //eliberez casuta de pe care plec
                    rectangle(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(matrice_tabla[i][j].x,matrice_tabla[i][j].y,matrice_tabla[i][j].x+50,matrice_tabla[i][j].y+50);
                    //verific piesele blocate pt. a le elimina
                    for(int ci=1; ci<=8; ci++)
                        for(int cj=1; cj<=8; cj++)
                            if(matrice_tabla[ci][cj].este_piesa==1)
                                if(piesa_blocata(ci,cj))
                                {
                                    //verific cui apartine piesa blocata
                                    if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                        nr_finn--;
                                    else
                                        nr_jake--;
                                    //elimin piesa blocata
                                    matrice_tabla[ci][cj].este_piesa=false;
                                    rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                                }
                    //cand fac o mutare valida se schimba randul jucatorilor
                    swap(finn,jake);
                }
            }
        }
        else
        {
            readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",75,150,225,300);
            int randi, randj, t,w, b;
            mutare_random(t,w, randi, randj);
            cout<<randi<<" "<<randj<<" -> "<<t<<" "<<w<<endl;
            matrice_tabla[t][w].este_piesa=true;
            matrice_tabla[randi][randj].este_piesa=false;

            delay(500);
            readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/piesa_finn.jpg",matrice_tabla[t][w].x,matrice_tabla[t][w].y,matrice_tabla[t][w].x+50,matrice_tabla[t][w].y+50);
            nr_mutari++;
            rectangle(matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
            setfillstyle(SOLID_FILL, WHITE);
            bar(matrice_tabla[randi][randj].x,matrice_tabla[randi][randj].y,matrice_tabla[randi][randj].x+50,matrice_tabla[randi][randj].y+50);
            strcpy(piesa[t][w].jucator,"finn");
            piesa[randi][randj].jucator[0]='\0';
            if(nr_mutari==8)
                sterge_piese_blocate(matrice_tabla);
            for(int ci=1; ci<=8; ci++)
                for(int cj=1; cj<=8; cj++)
                    if(matrice_tabla[ci][cj].este_piesa==1)
                        if(piesa_blocata(ci,cj))
                        {
                            if(strcmp(piesa[ci][cj].jucator,"finn")==0)
                                nr_finn--;
                            else
                                nr_jake--;
                            //elimin piesa blocata
                            matrice_tabla[ci][cj].este_piesa=false;
                            rectangle(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                            setfillstyle(SOLID_FILL, WHITE);
                            bar(matrice_tabla[ci][cj].x,matrice_tabla[ci][cj].y,matrice_tabla[ci][cj].x+50,matrice_tabla[ci][cj].y+50);
                        }
            ultima_mutare_coloana[0]='A'+(j1-1);
            ultima_mutare_coloana[1]=NULL;
            ultima_mutare_linie[0]='8'-(i1-1);
            ultima_mutare_linie[1]=NULL;
            outtextxy(920,250,"Ultima mutare:");
            outtextxy(1000,275,ultima_mutare_coloana);
            outtextxy(1025,275,ultima_mutare_linie);
            ultima_mutare_coloana[0]='A'+(w-1);
            ultima_mutare_coloana[1]=NULL;
            ultima_mutare_linie[0]='8'-(t-1);
            ultima_mutare_linie[1]=NULL;
            outtextxy(920,250,"Ultima mutare:");
            outtextxy(1000,275,ultima_mutare_coloana);
            outtextxy(1025,275,ultima_mutare_linie);
            swap(finn,jake);
            if(nr_mutari<=70)
                if((nr_finn==1 && nr_jake>=2)||(nr_finn>=2 && nr_jake==1))
                    finish=1;
                else
                    finish=0;
            else
                remiza=1, finish=1;
        }
    }
     if(remiza)
    {
        readimagefile("remiza.jpg", 0, 0, 1200, 600);
        readimagefile("replay.jpg",950,300,1150,350);
    }
    else
        if(nr_finn>nr_jake)
        {
            readimagefile("finnwin.jpg", 0, 0, 1200, 600);
            readimagefile("replay.jpg",950,300,1150,350);
        }
        else
        {
            readimagefile("jakewin.jpg", 0, 0, 1200, 600);
            readimagefile("replay.jpg",950,300,1150,350);
        }
 while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, a, b);
    if(a>=950 && a<=1150 && b>=300 && b<=350)
    {
        homepage(0);
        closegraph();
    }
    delay(5000);
}

void nivel_dificultate1vC()
{
    int x,y;
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);
    setbkcolor(RGB(0,102,0));
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 16);
    outtextxy(250,100, "Ce nivel de dificultate doresti?");
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/usor.jpg", 524, 225, 656, 265);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/greu.jpg", 524, 325, 656, 365);
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=524 && x<=666)
        if(y>=225 && y<=265)
            joc_1vC1(matrice_tabla);
        else if(y>=325 && y<=365)
            joc_1vC(matrice_tabla);

}

void nivel_dificultate1v1()
{
    int x,y;
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);
    setbkcolor(RGB(0,102,0));
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 16);
    outtextxy(250,100, "Ce nivel de dificultate doresti?");
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/usor.jpg", 524, 225, 656, 265);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/greu.jpg", 524, 325, 656, 365);
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=524 && x<=666)
        if(y>=225 && y<=265)
            joc_1v1U(matrice_tabla);
        else if(y>=325 && y<=365)
            joc_1v1G(matrice_tabla);

}

void mod_joc()
{
    int x,y;

    clearviewport();
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/1juc.jpg", 504, 225, 696, 275);//1juc
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/2juc.jpg", 504, 325, 696, 375);//buton 2 jucatori
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back.jpg", 25, 25, 65, 65);//buton back
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=504 && x<=696)
        //1 jucator
        if(y>=225 && y<=275)
        {
            nivel_dificultate1vC();
        }

        else
            //2 jucatori
            if(y>=325 && y<=375)
            {
               nivel_dificultate1v1();
            }

    if(x>=25 && x<=65)
        //daca am apasat pe back
        if(y>=25 && y<=65)
        {

            homepage(0);

        }
    closegraph();
}
void reguli()
{
    clearviewport();
    int x,y;
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);
    //rectangle(200,100,1000,500);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/reguli_joc.jpg",100, 70, 1100, 530);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back.jpg", 25, 25, 65, 65);//buton back
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=25 && x<=65)
        //daca am apasat pe back
        if(y>=25 && y<=65)
        {

            homepage(0);


        }

}

void homepage(bool prima)
{
    if(prima==false)
    {
        closegraph();
    }
    int x=0,y=0;
    initwindow(1200,600, "Razboi in 8"); // Fereastra micã
    // initwindow(1920, 1080); // Fereastra full
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/meniu.jpg", 0, 0, 1200, 600);
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/reguli.jpg", 530, 180, 669, 230);//buton reguli
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/start.jpg", 530, 280, 669, 330);//buton start
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/setari.jpg", 530, 380, 669, 430);//buton setari
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
    }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=530 && x<=669)
        //daca am apasat pe reguli
        if(y>=180 && y<=230)
            reguli();
        else
            //daca am apasat pe start
            if(y>=280 && y<=330)
                mod_joc();
            else
                //daca am apasat pe setari
                if(y>=380 && y<=430)
                {
                    setari();
                }



}
void incarcareJoc()
{
    initwindow(1200,600, "Razboi in 8");
    readimagefile("D:/Proiecte extra/RAZBOI_IN_8/design/back_joc.jpg", 0, 0, 1200, 600);

    setbkcolor(WHITE);
    setcolor(BLUE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
    outtextxy(470,220, "Loading...");


    rectangle(400,250,700,300);
    setfillstyle(SOLID_FILL, WHITE);
    bar(400,250,700,300);

    for(int i=0; i<250; i++)
    {
        setcolor(RGB(255, 87, 51));
        rectangle(430,260,430+i,290);
        setfillstyle(SOLID_FILL, RGB(255, 87, 51));
        bar(431,261,431+i,291);
        delay(1);
    }
    closegraph();
}
int main()
{
    int x,y;
    bool prima=true;


    incarcareJoc();

    homepage(prima);
    getch();
    closegraph();
    return 0;
}
