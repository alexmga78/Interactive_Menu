#include <iostream>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <queue>
#include <stdlib.h>
#include <deque>

using namespace std;
ifstream f("Menus.in");


//Declarari Map=========================================================================================
ifstream citire_matricea_Romaniei("map_Romania.in");
ifstream km_intre_orase("km_between_cities.in");
ifstream nume_orase("cities.in");

int numar_orase,matricea_adiacenta[1000][1000];
int start,destinatie,option_for_map,resetare_4x_map,ultima_distanta;
int numarare_pentru_stergere_stationare;

const int oo=(1<<30);

int verificat[1000];
bool corect=true,ruta_cu_stationare=false,prima_parte_executata=false;

deque<long>nefolositi;
pair<int,int> D[1000];

char orase[10000],oras_start[10000],oras_destinatie[10000],stationare[10000];

deque<long>cod_oras;
//Declarari Map=========================================================================================


//Program Map===========================================================================================
void citirea_map()
{
    citire_matricea_Romaniei>>numar_orase;
    int x,y;
    while (citire_matricea_Romaniei>>x>>y)
    {   int km;
        km_intre_orase>>km;
        matricea_adiacenta[x][y]=matricea_adiacenta[y][x]=km;
    }
    nume_orase.get(orase,10000);
}

void validare_orase()
{
    corect=true;
    bool ok;
    if (oras_start[0])
    {
        int i=0,q=0;
        ok=false;
        while (orase[i])
        {
            if (orase[i]==oras_start[q])
                {ok=true;q++;}
            else
                {ok=false;q=0;}
            if (orase[i+1]==64&&oras_start[q]==0&&ok==true)
                break;

            i++;
        }
        if (ok==false)
        {   corect=false;
            cout<<"Numele orasului de pornire este scris gresit!"<<endl;
        }
    }

    if (oras_destinatie[0])
    {
        int i=0,q=0;
        ok=false;
        while (orase[i])
        {
            if (orase[i]==oras_destinatie[q])
                {ok=true;q++;}
            else
                {ok=false;q=0;}
            if (orase[i+1]==64&&oras_destinatie[q]==0&&ok==true)
                break;

            i++;
        }
        if (ok==false)
        {   corect=false;
            cout<<"Numele orasului destinatie este scris gresit!"<<endl;
        }
    }

    if (stationare[0]&&ruta_cu_stationare==true)
    {
        int i=0,q=0;
        ok=false;
        while (orase[i])
        {
            if (orase[i]==stationare[q])
                {ok=true;q++;}
            else
                {ok=false;q=0;}
            if (orase[i+1]==64&&stationare[q]==0&&ok==true)
                break;

            i++;
        }
        if (ok==false)
        {   corect=false;
            cout<<"Numele orasului de stationare este scris gresit!"<<endl;
        }
    }

    if (corect==false)
    {   cout<<endl<<"Tip: Tine minte ca numele oraselor incep cu litera mare, iar spatiile din numele acestora se inlocuiesc cu \"-\" ";
        _getch();
    }

}

void afisare()
{
    for (int i=1;i<=numar_orase;i++)
    {   for (int j=1;j<=numar_orase;j++)
            cout<<matricea_adiacenta[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
}

void Dijkstra()
{
    while (nefolositi.front())
        nefolositi.pop_front();

    int q=0;

    for (int i=1;i<=numar_orase;i++)
        D[i].first=oo;
    D[start].first=0;


    int i=start;
    while (i)
    {
        pair<int,int>minim;
        minim.first=oo;

        for (int j=1;j<=numar_orase;j++)
        {   if (matricea_adiacenta[i][j]>0&&verificat[j]==0)
            {
                //nefolositi.push_back(j);
                //cout<<i<<" "<<j<<" "<<matricea_adiacenta[i][j]<<endl;
                q++;
                if (matricea_adiacenta[i][j]<minim.first)
                    {minim.first=matricea_adiacenta[i][j];minim.second=j;}

                if (D[i].first+matricea_adiacenta[i][j]<D[j].first)
                    {
                        //cout<<i<<" "<<j<<" "<<matricea_adiacenta[i][j]<<" | "<<D[j].first<<endl;
                        D[j].first=D[i].first+matricea_adiacenta[i][j];
                        D[j].second=i;

                    }
            }
        }

        /*
        for (int l=1;l<=q;l++)
        {
            if (nefolositi.front()==minim.second)
                nefolositi.pop_front();
            else
            {
                nefolositi.push_back(nefolositi.front());
                nefolositi.pop_front();
            }
        }
        */

        verificat[i]=1;



        if (minim.first!=oo)
            i=minim.second;
        else
            break;


    }


    /*
    while (nefolositi.front())
    {
        cout<<nefolositi.front()<<" ";
        nefolositi.pop_front();
    }

    cout<<endl<<endl;
    */

    ///cout<<endl<<endl<<"*"<<endl;


    for (int i=1;i<=numar_orase;i++)
        if (verificat[i]==0)
        {
            if (start<destinatie)
                {/*//cout<<i<<" ";//*/nefolositi.push_back(i);}
            else
                {/*//cout<<i<<" ";//*/nefolositi.push_front(i);}
        }

    ///cout<<endl;


    ///cout<<endl<<"*"<<endl<<endl;


    bool ok=false;
    while (ok==false)
    {   while (nefolositi.front())
        {
            i=nefolositi.front();
            nefolositi.pop_front();
            //cout<<i<<" ";

            pair<int,int>minim;
            minim.first=oo;

            for (int j=1;j<=numar_orase;j++)
            {
                //cout<<i<<" "<<j<<" "<<matricea_adiacenta[i][j]<<endl;
                if (matricea_adiacenta[i][j]>0&&verificat[j]==0)
                {
                    //cout<<"============"<<endl<<i<<" "<<j<<" "<<matricea_adiacenta[i][j]<<endl<<"============"<<endl;
                    //nefolositi.push_back(j);
                    if (matricea_adiacenta[i][j]<minim.first)
                        {minim.first=matricea_adiacenta[i][j];minim.second=j;}

                    if (D[i].first+matricea_adiacenta[i][j]<D[j].first)
                        {
                            D[j].first=D[i].first+matricea_adiacenta[i][j];
                            D[j].second=i;
                            //cout<<i<<" "<<j<<" "<<D[i].first<<endl;

                        }
                }
                else
                {
                    if (matricea_adiacenta[i][j]>0&&verificat[j]!=0&&D[i].first+matricea_adiacenta[i][j]<D[j].first)
                    {
                        D[j].first=D[i].first+matricea_adiacenta[i][j];
                        D[j].second=i;
                        if (start<destinatie)
                            nefolositi.push_back(i);
                        else
                            nefolositi.push_front(i);
                    }
                }
            }
                //_getch();

            /*
            for (int l=1;l<=q;l++)
            {
                if (nefolositi.front()==minim.second)
                    nefolositi.pop_front();
                else
                {
                    nefolositi.push_back(nefolositi.front());
                    nefolositi.pop_front();
                }
            }
            */

            verificat[i]=1;



            if (minim.first!=oo)
                i=minim.second;
            else
                {/*//cout<<endl<<endl<<"#"<<endl<<endl//*/;break;}


        }

        ok=true;
        for (int i=1;i<=numar_orase;i++)
            if (verificat[i]==0)
            {   //cout<<i<<" ";
                if (start<destinatie)
                    nefolositi.push_back(i);
                else
                    nefolositi.push_front(i);
                ok=false;
            }
        //cout<<endl<<endl;


    }




}

void afisare_ruta()
{
    bool nu_executa=false;
    if (prima_parte_executata==true)
            nu_executa=true;
    while (cod_oras.front())
    {
        int i=0,q=1;;
        bool validare,ok=false;
        while (orase[i]!=0)
        {
            if (orase[i-1]==64&&orase[i]!=64)
                q++;

            if (q==cod_oras.front()&&orase[i]!=64&&nu_executa==false)
                {cout<<orase[i];ok=true;validare=true;}
            else
                validare=false;
            if (validare=false&&ok==true)
                break;
            i++;

        }
        if (nu_executa==false)
        {   if (prima_parte_executata==false)
            {   cout<<" "<<D[cod_oras.front()].first<<" km"<<endl;
                ultima_distanta=D[cod_oras.front()].first;}

            else
                cout<<" "<<D[cod_oras.front()].first+ultima_distanta<<" km"<<endl;
        }

        cod_oras.pop_front();

        if (nu_executa==true)
            nu_executa=false;

    }
}

void codare_orase()
{

    /*//
    cout<<"Orasul in care te afli: ";
    cin>>oras_start;
    cout<<"Orasul la care vrei sa ajungi: ";
    cin>>oras_destinatie;
    system("cls");
    //*/

    int i=0,q=0,inceput_oras=0,sfarsit_oras;
    while (orase[i]!=0)
    {
        if (orase[i-1]==64&&orase[i]!=64||i==0&&orase[i]!=64)
        {       q++;
                inceput_oras=i;
                ///cout<<i<<" "<<inceput_oras<<"  | "<<q<<endl;
        }
        else
            if (orase[i]==64)
            {   bool ok_oras_start=true,ok_oras_destinatie=true;
                for (int j=inceput_oras;j<i;j++)
                {   if (orase[j]!=oras_start[j-inceput_oras])
                        ok_oras_start=false;
                    if (orase[j]!=oras_destinatie[j-inceput_oras])
                        ok_oras_destinatie=false;
                }
                if (ok_oras_start==true)
                    start=q;
                if (ok_oras_destinatie==true)
                    destinatie=q;
            }

        i++;
    }

    /*
    if (start==0||destinatie==0||start==destinatie)
        corect=false;
    */


}

void resetare_Offline_Map()
{
    for (int i=1;i<=numar_orase;i++)
        verificat[i]=0;


    for (int i=1;i<=numar_orase;i++)
        {D[i].second=D[i].first=0;}

    corect=true;
    start=destinatie=0;
}

void Map_main()
{
    codare_orase();

    ///cout<<"* "<<start<<" "<<destinatie<<endl<<endl<<endl<<endl;

    while (cod_oras.front())
        cod_oras.pop_front();

    ///citirea();
    ///afisare();
    Dijkstra();

    /*//
    for (int i=1;i<=numar_orase;i++)
        cout<<D[i].first<<" ";
    cout<<endl<<endl;
    for (int i=1;i<=numar_orase;i++)
        cout<<D[i].second<<" ";
    cout<<endl<<endl;
    //*/


    cod_oras.push_front(destinatie);
    bool ok=false;
    while (ok==false)
    {
        ///cout<<D[destinatie].second<<" ";
        cod_oras.push_front(D[destinatie].second);
        destinatie=D[destinatie].second;
        if (destinatie==start)
            ok=true;
    }


/*
    while (cod_oras.front())
    {   cout<<cod_oras.front()<<" ";
        cod_oras.pop_front();
    }
*/


    if (prima_parte_executata==false)
        cout<<"Ruta:"<<endl;
    afisare_ruta();
    if (prima_parte_executata==false)
        prima_parte_executata=true;

    /*
    else
        if (start!=destinatie)
            cout<<"Ai scris gresit!"<<endl<<"Tip: Tine minte ca numele oraselor incep cu litera mare, iar spatiile din numele acestora se inlocuiesc cu \"-\" ";
        else
            cout<<"Te aflii deja in acest oras!";
        */


    resetare_Offline_Map();

    if (ruta_cu_stationare==false)
    {
        _getch();
        system("cls");
    }
    else
        ruta_cu_stationare=false;
    //Sleep(10000);


    //if (start>destinatie)
      //  swap(destinatie,start);

    //cout<<destinatie<<" ";


    /*
    while (start<destinatie)
    {
        cout<<D[destinatie].second<<" ";
        destinatie=D[destinatie].second;
    }
    */

    //cout<<endl<<start<<" "<<destinatie<<endl<<endl;


    /*
    while (start>destinatie)
    {
        for (int i=1;i<=numar_orase;i++)
            if (D[i].second==destinatie&&i==start)
            {
                cout<<i<<" ";
                start=D[i].second;
            }
    }
    */
    resetare_4x_map++;

}
//Program Map===========================================================================================

//Meniu Map=============================================================================================
void meniu_map()
{
    while (1)
    {
        corect=false;
        bool ok=true;
        option_for_map=oo;
        cout<<"1) Orasul de plecare: "<<oras_start<<endl;
        cout<<"2) Orasul destinatie: "<<oras_destinatie<<endl;
        cout<<"3) Stationare: "<<stationare<<endl;
        cout<<"4) Afisare ruta";
        cout<<endl<<endl<<"9) Eliminare stationare";
        cout<<endl<<endl<<"0) Sub Menu";


        if (_kbhit())
            option_for_map=_getch()-48;
        if (option_for_map==1||option_for_map==2||option_for_map==3||option_for_map==4||option_for_map==9||option_for_map==0)
        {
            switch (option_for_map)
            {
                case 1:
                    system("cls");
                    cout<<"Introdu orasul de unde doresti sa pleci: ";
                    cin>>oras_start;
                    ok=false;
                    break;
                case 2:
                    system("cls");
                    cout<<"Introdu orasul unde vrei sa ajungi: ";
                    cin>>oras_destinatie;
                    ok=false;
                    break;
                case 3:
                    system("cls");
                    cout<<"Prin ce oras vrei sa treci?"<<endl;
                    cin>>stationare;
                    ok=false;
                    break;
                case 4:
                    system("cls");
                    if (oras_start[0]==0||oras_destinatie[0]==0)
                    {   cout<<"Adauga punctele de plecare si de sosire!";
                        while (1)
                            {Sleep(10);if (_kbhit())break;}
                    }
                    else
                        {   ok=false;
                            if (stationare[0]==0)
                            {   prima_parte_executata=false;
                                ruta_cu_stationare=false;
                                validare_orase();
                                if (corect==true)
                                    Map_main();


                            }
                            else
                            {
                                prima_parte_executata=false;
                                ruta_cu_stationare=true;
                                validare_orase();
                                if (corect==true)
                                {
                                    int lungime=0,masurare=0;
                                    while (oras_destinatie[masurare])
                                        {lungime++;masurare++;}
                                    int lungime_max=lungime;
                                    masurare=lungime=0;
                                    while (stationare[masurare])
                                        {lungime++;masurare++;}
                                    if (lungime>lungime_max)
                                    {
                                        for (int i=0;i<=lungime;i++)
                                            swap(oras_destinatie[i],stationare[i]);
                                        Map_main();
                                        masurare=lungime_max=0;
                                        while (oras_start[masurare])
                                            {lungime_max++;masurare++;}
                                        if (lungime>lungime_max)
                                        {
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],stationare[i]);
                                            Map_main();
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],stationare[i]);
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                        }
                                        else
                                        {
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],stationare[i]);
                                            Map_main();
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],stationare[i]);
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                        }
                                        for (int i=0;i<=lungime;i++)
                                            swap(oras_destinatie[i],stationare[i]);
                                    }
                                    else
                                    {
                                        for (int i=0;i<=lungime_max;i++)
                                            swap(oras_destinatie[i],stationare[i]);
                                        Map_main();
                                        masurare=lungime=0;
                                        while (oras_start[masurare])
                                            lungime++;
                                        if (lungime_max>lungime)
                                        {
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],stationare[i]);
                                            Map_main();
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],stationare[i]);
                                            for (int i=0;i<=lungime_max;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                        }
                                        else
                                        {
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                            Map_main();
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                            for (int i=0;i<=lungime;i++)
                                                swap(oras_destinatie[i],oras_start[i]);
                                        }
                                        for (int i=0;i<=lungime_max;i++)
                                            swap(oras_destinatie[i],stationare[i]);
                                    }

                                }
                            }
                        }
                    ok=false;
                    break;

                case 9:
                    numarare_pentru_stergere_stationare=0;
                    while (stationare[numarare_pentru_stergere_stationare])
                        {stationare[numarare_pentru_stergere_stationare]=0;numarare_pentru_stergere_stationare++;}
                    ok=false;
                    break;

                case 0:
                    resetare_4x_map=0;
                    ok=false;
                    break;

            }

        }

        if (option_for_map==0)
        {
            break;
        }
        else
        {
            if (ok==true)
            {
                if (resetare_4x_map>3)
                    {system("cls");break;}
                Sleep(200);
            }
            system("cls");
        }

    }

    system("cls");

}

//Meniu Map=============================================================================================



//Declarari Snake=======================================================================================
queue<pair<int,int> >que;
int options=115;
bool Ok_food=false,Insane_mode=false,Retry_Snake=false,harta_este_aleasa,Hard_Mode=false,Mod_Triunghi=false;
int Matrice_Sarpe[122][122],Matrice_Hrana_Sarpe[122][122],Viteza_Sarpe;
int depasire_limita_mancare=1,marime_harta_sarpe,dimensiune_i_harta,dimensiune_j_harta,hrana_sarpe_mancata,hrana_inversa_prezenta;
//Declarari Snake=======================================================================================

//Declarari Menus=======================================================================================
int option,culoare;
bool permite_culoare=false;
char Main_Menu_Var[10],Sub_Menu_Var[15];

void Options_Main_Menu()
{   cout << endl << "1) Snake" <<endl;
    cout << endl << "2) Sub Menu" <<endl;
    cout << endl << "0) Exit" <<endl;
}
void Options_Sub_Menu()
{   cout << endl << "1) The \"Hello\" text" <<endl;
    cout << endl << "2) Offline GPS" <<endl;
    cout << endl << "0) Main Menu" <<endl;
}
//Declarari Menus=======================================================================================


//Program Snake===================================================================================================================
void Snake_Reset()
{   for (int i=0;i<=dimensiune_i_harta;i++)
        for (int j=0;j<=dimensiune_j_harta;j++)
            Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=0;
    while (que.front().first||que.front().second)
        que.pop();
}

void resetare_harta_curenta()
{
    hrana_inversa_prezenta=hrana_sarpe_mancata=0;
    depasire_limita_mancare=1;

    if (Mod_Triunghi==false)
    {   for (int i=1;i<dimensiune_i_harta;i++)
            for (int j=1;j<dimensiune_j_harta;j++)
                Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=0;
        while (que.front().first||que.front().second)
            que.pop();


        for (int i=0;i<=dimensiune_i_harta;i++)
            {Matrice_Sarpe[i][0]=Matrice_Sarpe[i][dimensiune_j_harta]=Matrice_Hrana_Sarpe[i][0]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta]=35;}
        for (int i=0;i<=dimensiune_j_harta;i++)
            {Matrice_Sarpe[0][i]=Matrice_Sarpe[dimensiune_i_harta][i]=Matrice_Hrana_Sarpe[0][i]=Matrice_Hrana_Sarpe[dimensiune_i_harta][i]=35;}

        system("cls");

        int i,j;
        i=rand()%(dimensiune_i_harta-4)+2;
        j=rand()%(dimensiune_j_harta-4)+2;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});
        i--;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});
        j++;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});


        srand(time(NULL));
        i=rand()%(dimensiune_i_harta-2)+1;
        j=rand()%(dimensiune_j_harta-2)+1;
        Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;
    }
    else
    {
        while (que.front().first||que.front().second)
            que.pop();

        for (int i=0;i<dimensiune_i_harta;i++)
            for (int j=dimensiune_j_harta/2-(i-2);j<=dimensiune_j_harta/2+(i-2);j++)
                Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=0;

        for (int i=0;i<dimensiune_i_harta;i++)
            Matrice_Sarpe[i][dimensiune_j_harta/2-i]=Matrice_Sarpe[i][dimensiune_j_harta/2+i]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2-i]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2+i]=35;
        for (int j=1;j<dimensiune_j_harta;j++)
            Matrice_Sarpe[dimensiune_i_harta][j]=Matrice_Hrana_Sarpe[dimensiune_i_harta][j]=35;
        for (int i=1;i<dimensiune_i_harta;i++)
            Matrice_Sarpe[i][dimensiune_j_harta/2-i+1]=Matrice_Sarpe[i][dimensiune_j_harta/2+i-1]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2-i+1]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2+i-1]=35;

        system("cls");

        int i=rand()%(dimensiune_i_harta-4)+3;
        int j=rand()%((i-1)*2-1);
        j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
        while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
        {   i=rand()%(dimensiune_i_harta-4)+3;
            j=rand()%((i-1)*2-1);
            j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
        }
        i+=2;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});
        i--;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});
        i--;;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});


        srand(time(NULL));
        i=rand()%(dimensiune_i_harta-4)+3;
        j=rand()%((i-1)*2-1);
        j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
        while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
        {   i=rand()%(dimensiune_i_harta-4)+3;
            j=rand()%((i-1)*2-1);
            j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
        }
        Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;

    }




}

void Snake()
{   int s=1,Score=0;
    options=32;
    while(s)
    {   if (_kbhit())
        {   int previous=options;
            options=_getch();
            if (options!=115&&options!=119&&options!=100&&options!=97&&options!=32)
                options=previous;
            if (options==115) //s
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first+1][que.back().second]==42)
                {   if (Matrice_Hrana_Sarpe[que.back().first+1][que.back().second]==42)
                    {   que.push({que.back().first+1,que.back().second});
                        Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                        Ok_food=true;
                        depasire_limita_mancare--;
                        hrana_sarpe_mancata++;
                        Score++;
                    }
                    else
                        s=0;
                }
                else
                    if (Matrice_Sarpe[que.back().first+1][que.back().second]==94)
                    {
                        Matrice_Sarpe[que.back().first+1][que.back().second]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first+1][que.back().second]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first+1][que.back().second]=42;
                            que.push({que.back().first+1,que.back().second});
                            que.pop();
                        }
            }
            if (options==119) //w
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first-1][que.back().second]==42)
                {   if (Matrice_Hrana_Sarpe[que.back().first-1][que.back().second]==42)
                    {   que.push({que.back().first-1,que.back().second});
                        Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                        Ok_food=true;
                        depasire_limita_mancare--;
                        hrana_sarpe_mancata++;
                        Score++;
                    }
                    else
                        s=0;
                }
                else
                    if (Matrice_Sarpe[que.back().first-1][que.back().second]==94)
                    {
                        Matrice_Sarpe[que.back().first-1][que.back().second]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first-1][que.back().second]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first-1][que.back().second]=42;
                            que.push({que.back().first-1,que.back().second});
                            que.pop();
                        }
            }
            if (options==100) //d
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first][que.back().second+1]==42)
                {   if (Matrice_Hrana_Sarpe[que.back().first][que.back().second+1]==42)
                    {   que.push({que.back().first,que.back().second+1});
                        Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                        Ok_food=true;
                        depasire_limita_mancare--;
                        hrana_sarpe_mancata++;
                        Score++;
                    }
                    else
                        s=0;
                }
                else
                    if (Matrice_Sarpe[que.back().first][que.back().second+1]==94)
                    {
                        Matrice_Sarpe[que.back().first][que.back().second+1]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first][que.back().second+1]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first][que.back().second+1]=42;
                            que.push({que.back().first,que.back().second+1});
                            que.pop();
                        }
            }
            if (options==97) //a
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first][que.back().second-1]==42)
                {   if (Matrice_Hrana_Sarpe[que.back().first][que.back().second-1]==42)
                    {   que.push({que.back().first,que.back().second-1});
                        Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                        Ok_food=true;
                        depasire_limita_mancare--;
                        hrana_sarpe_mancata++;
                        Score++;
                    }
                    else
                        s=0;
                }
                else
                    if (Matrice_Sarpe[que.back().first][que.back().second-1]==94)
                    {
                        Matrice_Sarpe[que.back().first][que.back().second-1]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first][que.back().second-1]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first][que.back().second-1]=42;
                            que.push({que.back().first,que.back().second-1});
                            que.pop();
                        }
            }

        }

        else
        {   if (options==115&&_kbhit()==0) //s
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first+1][que.back().second]==42)
                {   que.push({que.back().first+1,que.back().second});
                    Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                    Ok_food=true;
                    depasire_limita_mancare--;
                    hrana_sarpe_mancata++;
                    Score++;
                }
                else
                    if (Matrice_Sarpe[que.back().first+1][que.back().second]==94)
                    {
                        Matrice_Sarpe[que.back().first+1][que.back().second]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first+1][que.back().second]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first+1][que.back().second]=42;
                            que.push({que.back().first+1,que.back().second});
                            que.pop();
                        }
            }
            if (options==119&&_kbhit()==0) //w
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first-1][que.back().second]==42)
                {   que.push({que.back().first-1,que.back().second});
                    Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                    Ok_food=true;
                    depasire_limita_mancare--;
                    hrana_sarpe_mancata++;
                    Score++;
                }

                else
                    if (Matrice_Sarpe[que.back().first-1][que.back().second]==94)
                    {
                        Matrice_Sarpe[que.back().first-1][que.back().second]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first-1][que.back().second]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first-1][que.back().second]=42;
                            que.push({que.back().first-1,que.back().second});
                            que.pop();
                        }
            }
            if (options==100&&_kbhit()==0) //d
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first][que.back().second+1]==42)
                {   que.push({que.back().first,que.back().second+1});
                    Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                    Ok_food=true;
                    depasire_limita_mancare--;
                    hrana_sarpe_mancata++;
                    Score++;
                }
                else
                    if (Matrice_Sarpe[que.back().first][que.back().second+1]==94)
                    {
                        Matrice_Sarpe[que.back().first][que.back().second+1]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first][que.back().second+1]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first][que.back().second+1]=42;
                            que.push({que.back().first,que.back().second+1});
                            que.pop();
                        }
            }
            if (options==97&&_kbhit()==0) //a
            {   Matrice_Sarpe[que.front().first][que.front().second]=0;
                if (Matrice_Sarpe[que.back().first][que.back().second-1]==42)
                {   que.push({que.back().first,que.back().second-1});
                    Matrice_Hrana_Sarpe[que.back().first][que.back().second]=0;
                    Ok_food=true;
                    depasire_limita_mancare--;
                    hrana_sarpe_mancata++;
                    Score++;
                }
                else
                    if (Matrice_Sarpe[que.back().first][que.back().second-1]==94)
                    {
                        Matrice_Sarpe[que.back().first][que.back().second-1]=0;
                        hrana_inversa_prezenta--;
                        hrana_sarpe_mancata=0;
                        que.pop();
                        Score--;
                    }
                    else
                        if (Matrice_Sarpe[que.back().first][que.back().second-1]==35)
                            s=0;
                        else
                        {   Matrice_Sarpe[que.back().first][que.back().second-1]=42;
                            que.push({que.back().first,que.back().second-1});
                            que.pop();
                        }
            }

        }
        //if (que.back().first>marime_harta_sarpe-1||que.back().first<1||que.back().second>marime_harta_sarpe-1||que.back().second<1)
            //s=0;



        if (Ok_food==true&&depasire_limita_mancare<20&&Mod_Triunghi==false)
        {   Ok_food=false;

            bool hrana_suprapusa=true;
            while (hrana_suprapusa==true)
            {
                hrana_suprapusa=false;


                int i=rand()%(dimensiune_i_harta-1)+1;
                int j=rand()%(dimensiune_j_harta-1)+1;
                if (Matrice_Sarpe[i][j]==42||Matrice_Sarpe[i][j]==94)
                    hrana_suprapusa=true;
                else
                {
                    Matrice_Hrana_Sarpe[i][j]=42;
                    Matrice_Sarpe[i][j]=42;
                    depasire_limita_mancare++;
                }


            }



            if (Insane_mode==true)
            {   int i=rand()%(dimensiune_i_harta-1)+1;
                int j=rand()%(dimensiune_j_harta-1)+1;
                Matrice_Hrana_Sarpe[i][j]=42;
                Matrice_Sarpe[i][j]=42;
                i=rand()%(dimensiune_i_harta-1)+1;
                j=rand()%(dimensiune_j_harta-1)+1;
                Matrice_Hrana_Sarpe[i][j]=42;
                Matrice_Sarpe[i][j]=42;
                depasire_limita_mancare+=2;
            }

            if (Hard_Mode==true)
            {   if (hrana_sarpe_mancata>=3&&hrana_inversa_prezenta<3)
                {
                    hrana_sarpe_mancata=0;

                    bool hrana_suprapusa=true;
                    while (hrana_suprapusa==true)
                    {
                        hrana_suprapusa=false;


                        int i=rand()%(dimensiune_i_harta-1)+1;
                        int j=rand()%(dimensiune_j_harta-1)+1;
                        if (Matrice_Sarpe[i][j]==42||Matrice_Sarpe[i][j]==94)
                            hrana_suprapusa=true;
                        else
                        {
                            Matrice_Hrana_Sarpe[i][j]=94;
                            Matrice_Sarpe[i][j]=94;
                            hrana_inversa_prezenta++;
                            hrana_sarpe_mancata=0;
                        }


                    }

                }
            }
            else
                if (hrana_sarpe_mancata>=2&&hrana_inversa_prezenta<9)
                    if (Insane_mode==true)
                        {
                            hrana_sarpe_mancata=0;

                            int i=rand()%(dimensiune_i_harta-1)+1;
                            int j=rand()%(dimensiune_j_harta-1)+1;
                            Matrice_Hrana_Sarpe[i][j]=94;
                            Matrice_Sarpe[i][j]=94;
                            hrana_inversa_prezenta++;
                            i=rand()%(dimensiune_i_harta-1)+1;
                            j=rand()%(dimensiune_j_harta-1)+1;
                            Matrice_Hrana_Sarpe[i][j]=94;
                            Matrice_Sarpe[i][j]=94;
                            hrana_inversa_prezenta++;
                        }

        }
        else
            if (Ok_food==true&&Mod_Triunghi==true&&depasire_limita_mancare<20)
            {   Ok_food=false;
                int i=rand()%(dimensiune_i_harta-4)+3;
                int j=rand()%((i-1)*2-1);
                j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                {   i=rand()%(dimensiune_i_harta-4)+3;
                    j=rand()%((i-1)*2-1);
                    j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                }
                Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;
                depasire_limita_mancare++;

                if (Insane_mode==true)
                {   while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                    {   i=rand()%(dimensiune_i_harta-4)+3;
                        j=rand()%((i-1)*2-1);
                        j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                    }
                    Matrice_Hrana_Sarpe[i][j]=42;
                    Matrice_Sarpe[i][j]=42;
                    while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                    {   i=rand()%(dimensiune_i_harta-4)+3;
                        j=rand()%((i-1)*2-1);
                        j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                    }
                    Matrice_Hrana_Sarpe[i][j]=42;
                    Matrice_Sarpe[i][j]=42;
                    depasire_limita_mancare+=2;
                }

                if (Hard_Mode==true)
                {   if (hrana_sarpe_mancata>=3&&hrana_inversa_prezenta<3)
                    {
                        hrana_sarpe_mancata=0;

                        bool hrana_suprapusa=true;
                        while (hrana_suprapusa==true)
                        {
                            hrana_suprapusa=false;


                            int i=rand()%(dimensiune_i_harta-4)+3;
                            int j=rand()%((i-1)*2-1);
                            j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                            while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                            {   i=rand()%(dimensiune_i_harta-4)+3;
                                j=rand()%((i-1)*2-1);
                                j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                            }
                            if (Matrice_Sarpe[i][j]==42||Matrice_Sarpe[i][j]==94)
                                hrana_suprapusa=true;
                            else
                            {
                                Matrice_Hrana_Sarpe[i][j]=94;
                                Matrice_Sarpe[i][j]=94;
                                hrana_inversa_prezenta++;
                                hrana_sarpe_mancata=0;
                            }


                        }

                    }
                }
                else
                if (hrana_sarpe_mancata>=2&&hrana_inversa_prezenta<9)
                    if (Insane_mode==true)
                        {
                            hrana_sarpe_mancata=0;

                            int i=rand()%(dimensiune_i_harta-4)+3;
                            int j=rand()%((i-1)*2-1);
                            j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                            while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                            {   i=rand()%(dimensiune_i_harta-4)+3;
                                j=rand()%((i-1)*2-1);
                                j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                            }
                            Matrice_Hrana_Sarpe[i][j]=94;
                            Matrice_Sarpe[i][j]=94;
                            hrana_inversa_prezenta++;
                            i=rand()%(dimensiune_i_harta-4)+3;
                            j=rand()%((i-1)*2-1);
                            j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                            while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                            {   i=rand()%(dimensiune_i_harta-4)+3;
                                j=rand()%((i-1)*2-1);
                                j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                            }
                            Matrice_Hrana_Sarpe[i][j]=94;
                            Matrice_Sarpe[i][j]=94;
                            hrana_inversa_prezenta++;

                        }



            }

        if (s==1)
        {   for (int i=0;i<=dimensiune_i_harta;i++)
            {    for (int j=0;j<=dimensiune_j_harta;j++)
                    if (Matrice_Sarpe[i][j] == 0)
                    {
                        cout<<char(Matrice_Sarpe[i][j] + 32);
                    }else
                    {
                        cout<<char(Matrice_Sarpe[i][j]);
                    }
                cout<<endl;
            }
            Sleep(Viteza_Sarpe);
        }
        system("cls");
    }
    system("cls");
    cout<<"Game over!"<<endl<<"Score: "<<Score<<endl<<endl;
    for (int i=1;i<=Score+3;i++)
        que.pop();
    cout<<"Retry?"<<endl;
    cout<<"1)Yes"<<endl;
    cout<<"2)No"<<endl;
    int i=_getch()-48;
    while (1)
        if (i==1||i==2)
            break;
        else
            i=_getch()-48;
    system("cls");

    resetare_harta_curenta();

    Hard_Mode=false;
    Insane_mode=false;
    if (i==1)
        Retry_Snake=true;
    else
        Retry_Snake=false;
}

void Forme_Harti_Snake(int tip_harti, int numar_forma)
{
    Mod_Triunghi=Hard_Mode=Insane_mode=false;
    Snake_Reset();

    harta_este_aleasa=true;

    if (tip_harti==1)
    {   if (numar_forma==1)
            marime_harta_sarpe=10;
        else
            if (numar_forma==2)
                marime_harta_sarpe=22;
            else
                if (numar_forma==3)
                    marime_harta_sarpe=28;
                else
                    if (numar_forma==4)
                        marime_harta_sarpe=50;
        dimensiune_i_harta=dimensiune_j_harta=marime_harta_sarpe;
        for (int i=0;i<=marime_harta_sarpe;i++)
        {Matrice_Sarpe[i][0]=35;Matrice_Sarpe[i][marime_harta_sarpe]=35;Matrice_Sarpe[0][i]=35;Matrice_Sarpe[marime_harta_sarpe][i]=35;}
        for (int i=0;i<=marime_harta_sarpe;i++)
        {Matrice_Hrana_Sarpe[i][0]=35;Matrice_Hrana_Sarpe[i][marime_harta_sarpe]=35;Matrice_Hrana_Sarpe[0][i]=35;Matrice_Hrana_Sarpe[marime_harta_sarpe][i]=35;}

        int i,j;
        i=rand()%(marime_harta_sarpe-2)+1;
        j=i;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});
        i--;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});
        j++;
        Matrice_Sarpe[i][j]=42;
        que.push({i,j});

        srand(time(NULL));
        i=rand()%(marime_harta_sarpe-4)+1;
        j=rand()%(marime_harta_sarpe-4)+1;
        Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;

    }
    else
        if (tip_harti==2)
        {
            if (numar_forma==1)
            {
                dimensiune_i_harta=13;
                dimensiune_j_harta=41;
                for (int i=0;i<=dimensiune_i_harta;i++)
                    {Matrice_Sarpe[i][0]=Matrice_Sarpe[i][dimensiune_j_harta]=Matrice_Hrana_Sarpe[i][0]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta]=35;}
                for (int i=0;i<=dimensiune_j_harta;i++)
                    {Matrice_Sarpe[0][i]=Matrice_Sarpe[dimensiune_i_harta][i]=Matrice_Hrana_Sarpe[0][i]=Matrice_Hrana_Sarpe[dimensiune_i_harta][i]=35;}

                int i,j;
                i=rand()%(dimensiune_i_harta-4)+2;
                j=rand()%(dimensiune_j_harta-4)+2;
                Matrice_Sarpe[i][j]=42;
                que.push({i,j});
                i--;
                Matrice_Sarpe[i][j]=42;
                que.push({i,j});
                j++;
                Matrice_Sarpe[i][j]=42;
                que.push({i,j});


                srand(time(NULL));
                i=rand()%(dimensiune_i_harta-2)+1;
                j=rand()%(dimensiune_j_harta-2)+1;
                Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;
            }
            else
                if (numar_forma==2)
                {
                    dimensiune_i_harta=20;
                    dimensiune_j_harta=(dimensiune_i_harta+1)*2;

                    for (int i=0;i<dimensiune_i_harta;i++)
                    {
                        Matrice_Sarpe[i][dimensiune_j_harta/2-i]=Matrice_Sarpe[i][dimensiune_j_harta/2+i]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2-i]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2+i]=35;
                    }

                    for (int j=1;j<dimensiune_j_harta;j++)
                        Matrice_Sarpe[dimensiune_i_harta][j]=Matrice_Hrana_Sarpe[dimensiune_i_harta][j]=35;


                    for (int i=1;i<dimensiune_i_harta;i++)
                        Matrice_Sarpe[i][dimensiune_j_harta/2-i+1]=Matrice_Sarpe[i][dimensiune_j_harta/2+i-1]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2-i+1]=Matrice_Hrana_Sarpe[i][dimensiune_j_harta/2+i-1]=35;



                    int i=0,j=dimensiune_j_harta/2;





                    srand(time(NULL));
                    while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35)
                    {   i=rand()%(dimensiune_i_harta-4)+3;
                        j=rand()%((i-1)*2-1);
                    }
                    j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                    i+=2;
                    Matrice_Sarpe[i][j]=42;
                    que.push({i,j});
                    i--;
                    Matrice_Sarpe[i][j]=42;
                    que.push({i,j});
                    i--;;
                    Matrice_Sarpe[i][j]=42;
                    que.push({i,j});

                    srand(time(NULL));
                    i=rand()%(dimensiune_i_harta-4)+3;
                    j=rand()%((i-1)*2-1);
                    j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                    while (Matrice_Sarpe[i][j]==35||Matrice_Sarpe[i+2][j]==35||Matrice_Sarpe[i][j]==42)
                    {   i=rand()%(dimensiune_i_harta-4)+3;
                        j=rand()%((i-1)*2-1);
                        j+=(dimensiune_j_harta-((i-1)*2-1))/2+1;
                    }
                    Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;


                    Mod_Triunghi=true;

                }
                else
                    if (numar_forma==3)
                    {

                    }

        }

    tip_harti=marime_harta_sarpe=0;
}

void Snake_Input()
{

    int optiune_dificultate=oo;
    //cout<<endl<<endl<<marime_harta_sarpe<<" "<<dimensiune_i_harta<<" "<<dimensiune_j_harta<<endl<<endl;
    cout<<"Difficulty:"<<endl;
    cout<<"1) Easy"<<endl;
    cout<<"2) Medium"<<endl;
    cout<<"3) Hard"<<endl;
    cout<<"4) Insane"<<endl;
    cout<<"5) Harti"<<endl;
    cout<<endl<<"0) Main Menu";
    optiune_dificultate=oo;

    while (1)
    {
        optiune_dificultate=_getch()-48;
        if (optiune_dificultate==5)
        {
            system("cls");
            int tip_harti=oo;
            cout<<"Harti:"<<endl<<endl;
            cout<<"1) Classic"<<endl;
            cout<<"2) In forme"<<endl;
            while (tip_harti!=1&&tip_harti!=2)
                tip_harti=_getch()-48;
            system("cls");

            if (tip_harti==1)
            {
                cout<<"Harti obisnuite:"<<endl<<endl;
                cout<<"1) Small (9x9)"<<endl;
                cout<<"2) Normal (17x17)"<<endl;
                cout<<"3) Large (21x21)"<<endl;
                cout<<"4) Huge (27x27)"<<endl;
                while (marime_harta_sarpe!=1&&marime_harta_sarpe!=2&&marime_harta_sarpe!=3&&marime_harta_sarpe!=4)
                    marime_harta_sarpe=_getch()-48;
                Forme_Harti_Snake(tip_harti,marime_harta_sarpe);
            }
            else
                if (tip_harti==2)
                {
                    cout<<"Harti cu forme:"<<endl<<endl;
                    cout<<"1) Dreptunghi (12x20x12x20)"<<endl;
                    cout<<"2) Triunghi (18x18x18)"<<endl;
                    cout<<"3) Cerc (12)"<<endl;
                    while (marime_harta_sarpe!=1&&marime_harta_sarpe!=2&&marime_harta_sarpe!=3)
                        marime_harta_sarpe=_getch()-48;
                    Forme_Harti_Snake(tip_harti,marime_harta_sarpe);
                }

        }
        else
            if (optiune_dificultate==1||optiune_dificultate==2||optiune_dificultate==3||optiune_dificultate==4||optiune_dificultate==0)
                break;





                system("cls");

                cout<<"Difficulty:"<<endl;
                cout<<"1) Easy"<<endl;
                cout<<"2) Medium"<<endl;
                cout<<"3) Hard"<<endl;
                cout<<"4) Insane"<<endl;
                cout<<"5) Harti"<<endl;
                cout<<endl<<"0) Main Menu";


        }



    //optiune_dificultate=_getch()-48;
    system("cls");


    resetare_harta_curenta();

    if (dimensiune_i_harta<=20&&dimensiune_j_harta<=20)
    {   if (optiune_dificultate==1)
            Viteza_Sarpe=300;
        else
            if (optiune_dificultate==2)
                Viteza_Sarpe=165;
            else
                if (optiune_dificultate==3)
                    {Viteza_Sarpe=115;Hard_Mode=true;}
                else
                    {Viteza_Sarpe=70;Insane_mode=true;}

    }
    else
        if (dimensiune_i_harta>20&&dimensiune_i_harta<=41&&dimensiune_j_harta<=41||dimensiune_j_harta>20&&dimensiune_j_harta<=41&&dimensiune_i_harta<=41)
        {   if (optiune_dificultate==1)
                Viteza_Sarpe=200;
            else
                if (optiune_dificultate==2)
                    Viteza_Sarpe=130;
                else
                    if (optiune_dificultate==3)
                        {Viteza_Sarpe=70;Hard_Mode=true;}
                    else
                        {Viteza_Sarpe=45;Insane_mode=true;}

        }
        else
            if (optiune_dificultate==1)
                Viteza_Sarpe=200;
            else
                if (optiune_dificultate==2)
                    Viteza_Sarpe=100;
                else
                    if (optiune_dificultate==3)
                        {Viteza_Sarpe=50;Hard_Mode=true;}
                    else
                        if (Mod_Triunghi==false)
                            {Viteza_Sarpe=2;Insane_mode=true;}
                        else
                            {Viteza_Sarpe=30;Insane_mode=true;}




    if (optiune_dificultate!=0)
        Snake();

    /*if (optiune_dificultate!=0)
    {   //for (int i=0;i<=marime_harta_sarpe;i++)
            //for (int j=0;j<=marime_harta_sarpe;j++)
                //f>>Matrice_Sarpe[i][j];


        if (harta_este_aleasa==false)
        {
            dimensiune_i_harta=dimensiune_j_harta=marime_harta_sarpe;
            for (int i=0;i<=marime_harta_sarpe;i++)
            {Matrice_Sarpe[i][0]=35;Matrice_Sarpe[i][marime_harta_sarpe]=35;Matrice_Sarpe[0][i]=35;Matrice_Sarpe[marime_harta_sarpe][i]=35;}
            for (int i=0;i<=marime_harta_sarpe;i++)
            {Matrice_Hrana_Sarpe[i][0]=35;Matrice_Hrana_Sarpe[i][marime_harta_sarpe]=35;Matrice_Hrana_Sarpe[0][i]=35;Matrice_Hrana_Sarpe[marime_harta_sarpe][i]=35;}

            int i,j;
            i=rand()%(marime_harta_sarpe-2)+1;
            j=i;
            Matrice_Sarpe[i][j]=42;
            que.push({i,j});
            i--;
            Matrice_Sarpe[i][j]=42;
            que.push({i,j});
            j++;
            Matrice_Sarpe[i][j]=42;
            que.push({i,j});

            srand(time(NULL));
            i=rand()%(marime_harta_sarpe-4)+1;
            j=rand()%(marime_harta_sarpe-4)+1;
            Matrice_Sarpe[i][j]=Matrice_Hrana_Sarpe[i][j]=42;

        }


        if (optiune_dificultate==1)
            Viteza_Sarpe=600;
        else
            if (optiune_dificultate==2)
                Viteza_Sarpe=300;
            else
                if (optiune_dificultate==3)
                    Viteza_Sarpe=150;
                else
                    {Viteza_Sarpe=80;Insane_mode=true;}


        Snake();

    }

    else
    */
    if (optiune_dificultate==0)
        Retry_Snake=false;

}
//Program Snake===================================================================================================================

//Schimbarea culorii=============================================================================================================
void Schimba_Culoarea()
{
    int culoare_precedenta=culoare;
    while (culoare==culoare_precedenta)
        culoare=rand()%9;

    if (culoare==0)
        system("color 0");
    else
        if (culoare==1)
            system("color 1");
        else
            if (culoare==2)
                system("color 2");
            else
                if (culoare==3)
                    system("color 3");
                else
                    if (culoare==4)
                        system("color 4");
                    else
                        if (culoare==5)
                            system("color 5");
                        else
                            if (culoare==6)
                                system("color 6");
                            else
                                if (culoare==7)
                                    system("color 7");
                                else
                                    if (culoare==8)
                                        system("color 8");
                                    else
                                        if (culoare==9)
                                            system("color 9");

}
//Schimbarea culorii=============================================================================================================

//Program Menu===================================================================================================================
void Sub_Menu()
{   option=oo;
    while(1)
    {
        for (int i=0;i<=strlen(Sub_Menu_Var);i++)
        {   cout<<"--------------------"<<endl;
            for (int j=i;j<=strlen(Sub_Menu_Var);j++)
                cout<<Sub_Menu_Var[j];
            for (int j=1;j<=11;j++)
                cout<<" ";
            for (int j=0;j<i;j++)
                cout<<Sub_Menu_Var[j];
            cout<<endl<<"--------------------";
            Options_Sub_Menu();
            Sleep(100);
            system("cls");
            if (_kbhit())
                option=_getch()-48;
            if (option==1||option==2||option==0)
                break;
        }
        if (_kbhit())
            option=_getch()-48;
        if (option==1||option==2||option==0)
            break;
        for (int j=11;j>=1;j--)
        {   cout<<"--------------------"<<endl;
            for (int o=1;o<=j;o++)
                cout<<" ";
            cout<<"Sub Menu"<<endl;
            cout<<"--------------------";
            Options_Sub_Menu();
            Sleep(200);
            system("cls");
            if (_kbhit())
                option=_getch()-48;
            if (option==1||option==2||option==0)
                break;
        }
        if (_kbhit())
                option=_getch()-48;
            if (option==1||option==2||option==0)
                break;




    }
    //option=_getch()-48;
}

void Main_Menu()
{   option=oo;
    while(1)
    {
        for (int i=0;i<=strlen(Main_Menu_Var);i++)
        {   cout<<"--------------------"<<endl;
            for (int j=i;j<=strlen(Main_Menu_Var);j++)
                cout<<Main_Menu_Var[j];
                //Sleep(12);
            for (int j=1;j<=10;j++)
                cout<<" ";
            for (int j=0;j<i;j++)
                cout<<Main_Menu_Var[j];
            cout<<endl<<"--------------------";
            Options_Main_Menu();
            Sleep(100);
            system("cls");
            if (_kbhit())
                option=_getch()-48;
            if (option==1||option==2||option==0)
                break;
        }
        if (_kbhit())
            option=_getch()-48;
        if (option==1||option==2||option==0)
            break;
        for (int j=10;j>=1;j--)
        {   cout<<"--------------------"<<endl;
            for (int o=1;o<=j;o++)
                cout<<" ";
            cout<<"Main Menu"<<endl;
            cout<<"--------------------";
            Options_Main_Menu();
            Sleep(200);
            system("cls");
            if (_kbhit())
                option=_getch()-48;
            if (option==1||option==2||option==0)
                break;
        }

        if (_kbhit())
            option=_getch()-48;
        if (option==1||option==2||option==0)
            break;

    }

    //option=_getch()-48;


}

void MainMenu()
{   while (1)
    {   Main_Menu();
        system("cls");
        switch (option)
        {   case 1:
                que.push({1,1});
                marime_harta_sarpe=dimensiune_i_harta=dimensiune_j_harta=18;
                Snake_Input();
                while(Retry_Snake==true)
                    Snake_Input();
                break;
            case 2: //Sub-Menu
                while(1)
                {   Sub_Menu();
                    system("cls");
                    switch (option)
                    {   case 1:
                            cout<<"Hello"<<endl;
                            option=_getch()-48;
                            Schimba_Culoarea();
                            system("cls");
                            break;
                        case 2:
                            resetare_4x_map=1;
                            while (resetare_4x_map)
                                {resetare_4x_map=0;meniu_map();}
                            break;
                        case 0: //Main-Menu
                            break;
                    }
                    if (option==0)
                        break;

                }
                break;
            case 0: //Exit
                exit(1);

        }
    }

}
//Program Menu===================================================================================================================

int main()
{   system("color ");
    f.get(Main_Menu_Var,10);
    f.get(Sub_Menu_Var,10);
    citirea_map();


    MainMenu();
    return 0;
}


                        //Letters:  Font:
                    //0-Black   A-Light Green
                    //1-Blue    B-Light Aqua
                    //2-Green   C-Light Red
                    //3-Aqua    D-Light Purple
                    //4-Red     E-Light Yellow
                    //5-Purple  F-Bright White
                    //6-Yellow
                    //7-White
                    //8-Grey
                    //9-Light Blue
