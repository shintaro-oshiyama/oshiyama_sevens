#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int show(int a[4][14]); /*カードを表示する関数*/
int showp(int p[4][14], int pc, int pp); /*手札を表示する関数*/
int shows(int pc[4], int pp[4]); /*全員の手札残り枚数、パス残り関数を表示*/
int divide(int c[4][14], int p0[4][14], int p1[4][14], int p2[4][14], int p3[4][14]); /*カードを配る関数*/
int turn(int d[4][14], int p[4][14], int *pq, int *pc, int *pp, int *l); /*プレイヤーのターンの関数*/
int judge(int pq[4]); /*勝敗判定の関数*/
int bankrupt(int d[4][14], int p[4][14], int *pc); /*パス回数超過後処理*/
int change(void); /*交代*/

int GetRandom(int min, int max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

int main(void)
{
    int pq[4]={1,1,1,1}; /*参加資格*/
    int pc[4]={12,12,12,12}; /*手札残り枚数*/
    int pp[4]={3,3,3,3}; /*パス残り回数*/
    int i=0,j,k=1,l=1;

    srand((unsigned int)time(NULL));

    /*000はダイヤ、100はハート、200はクラブ、300はスペード*/
    /*1000はカードあり、0000はカードなし*/
    /*カード一覧*/
    int cards[4][14] = {
        {0,1001,1002,1003,1004,1005,1006,7,1008,1009,1010,1011,1012,1013},
        {0,1101,1102,1103,1104,1105,1106,107,1108,1109,1110,1111,1112,1113},
        {0,1201,1202,1203,1204,1205,1206,207,1208,1209,1210,1211,1212,1213},
        {0,1301,1302,1303,1304,1305,1306,307,1308,1309,1310,1311,1312,1313}};

    /*1000はカードあり、0000はカードなし*/
    int desk[4][14] = {
        {0,1,2,3,4,5,6,1007,8,9,10,11,12,13},
        {0,101,102,103,104,105,106,1107,108,109,110,111,112,113},
        {0,201,202,203,204,205,206,1207,208,209,210,211,212,213},
        {0,301,302,303,304,305,306,1307,308,309,310,311,312,313}
    };

    int p0[4][14] = {
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
        {0,101,102,103,104,105,106,107,108,109,110,111,112,113},
        {0,201,202,203,204,205,206,207,208,209,210,211,212,213},
        {0,301,302,303,304,305,306,307,308,309,310,311,312,313}
    };
    int p1[4][14] = {
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
        {0,101,102,103,104,105,106,107,108,109,110,111,112,113},
        {0,201,202,203,204,205,206,207,208,209,210,211,212,213},
        {0,301,302,303,304,305,306,307,308,309,310,311,312,313}
    };
    int p2[4][14] = {
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
        {0,101,102,103,104,105,106,107,108,109,110,111,112,113},
        {0,201,202,203,204,205,206,207,208,209,210,211,212,213},
        {0,301,302,303,304,305,306,307,308,309,310,311,312,313}
    };
    int p3[4][14] = {
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
        {0,101,102,103,104,105,106,107,108,109,110,111,112,113},
        {0,201,202,203,204,205,206,207,208,209,210,211,212,213},
        {0,301,302,303,304,305,306,307,308,309,310,311,312,313}
    };

    printf("盤面\n");
    show(desk);

    divide(cards,p0,p1,p2,p3);
    printf("p0の手札\n");
    showp(p0,pc[0],pp[0]);
    change();
    printf("p1の手札\n");
    showp(p1,pc[1],pp[1]);
    change();
    printf("p2の手札\n");
    showp(p2,pc[2],pp[3]);
    change();
    printf("p3の手札\n");
    showp(p3,pc[3],pp[3]);
    change();

    /*ゲーム開始*/
    while(k==1 && l==1){
        j=i%4;
        if(pq[j]==1){
            shows(pc,pp);
            printf("p%dのターン\n", j);
            switch(j){
                case 0:{
                    turn(desk,p0,&pq[j],&pc[j],&pp[j], &l);
                    break;
                }
                case 1:{
                    turn(desk,p1,&pq[j],&pc[j],&pp[j], &l);
                    break;
                }
                case 2:{
                    turn(desk,p2,&pq[j],&pc[j],&pp[j], &l);
                    break;
                }
                case 3:{
                    turn(desk,p3,&pq[j],&pc[j],&pp[j], &l);
                    break;
                }
            }
            k=judge(pq);
        }
        else if(pq[j]==0){
            printf("p%dは敗退しました。\n", j);
        }
        change();
        i++;
    }
    
    return 0;
}

int show(int a[4][14])
{
    int i,j;

    for(i=0;i<4;i++){
        switch(i){
            case 0:{
                printf("ダイヤ (  1~ 13)");
                break;
            }
            case 1:{
                printf("ハート (101~113)");
                break;
            }
            case 2:{
                printf("クラブ (201~213)");
                break;
            }
            case 3:{
                printf("スペド (301~313)");
                break;
            }
        }

        for(j=1;j<=9;j++){
            if(a[i][j]>1000){
                printf("%d ", j);
            }
            else{
                printf("- ");
            }
        }
        for(j=10;j<=13;j++){
            if(a[i][j]>1000){
                printf("%d ",j);
            }
            else{
                printf("-- ");
            }
        }
        printf("\n");
    }
    return 0;
}

int showp(int p[4][14], int pc, int pp)
{
    show(p);
    printf("手札のこり%d枚、パス残り%d回\n", pc,pp);
    return 0;
}

int shows(int pc[4], int pp[4])
{
    int i;

    for(i=0;i<=3;i++){
        printf("p%dの手札%d枚、パス%d回\n", i, pc[i], pp[i]);
    }

    return 0;
}

int divide(int c[4][14], int p0[4][14], int p1[4][14], int p2[4][14], int p3[4][14])
{
    int a,b,i=0,j=0;

    /*p0に配る*/
    while(i<12){
        a = GetRandom(0,3);
        b = GetRandom(1,13);
        if(c[a][b]>1000){
            c[a][b] -= 1000;
            p0[a][b] += 1000;
            i++;
        }
    }
    i=0;

    /*p1に配る*/
    while(i<12){
        a = GetRandom(0,3);
        b = GetRandom(1,13);
        if(c[a][b]>1000){
            c[a][b] -= 1000;
            p1[a][b] += 1000;
            i++;
        }
    }
    i=0;

    /*p2に配る*/
    while(i<12){
        a = GetRandom(0,3);
        b = GetRandom(1,13);
        if(c[a][b]>1000){
            c[a][b] -= 1000;
            p2[a][b] += 1000;
            i++;
        }
    }
    i=0;

    /*残りはp3*/
    for(i=0;i<=3;i++){
        for(j=0;j<=13;j++){
            p3[i][j]=c[i][j];
        }
    }

    return 0;
}

int turn(int d[4][14], int p[4][14], int *pq, int *pc, int *pp, int *l)
{
    int a,b,c,i;

    printf("盤面\n");
    show(d);
    printf("あなたの手札\n");
    showp(p,*pc,*pp);

    printf("出すカードのマーク、またはパスを選んでください。\n");
    printf("0:ダイヤ 1:ハート 2:クラブ 3:スペド 4:パス 100:ゲーム終了\n");
    scanf("%d", &a);
    if(0<=a && a<=3){
        printf("出すカードの数字を答えてください。\n");
        scanf("%d", &b);
        if(1<=b && b<=6 && d[a][b+1]>1000 && p[a][b]>1000){
            c=1;
            for(i=b+1;i<8;i++){
                if(d[a][i]<1000){
                    c=0;
                }
            }

            if(c==1){
                d[a][b]+=1000;
                p[a][b]-=1000;
                *pc-=1;
                switch(a){
                    case 0:{
                        printf("ダイヤ");
                        break;
                    }
                    case 1:{
                        printf("ハート");
                        break;
                    }
                    case 2:{
                        printf("クラブ");
                        break;
                    }
                    case 3:{
                        printf("スペド");
                        break;
                    }
                }
                printf("の%dを出しました。\n", b);

                if(*pc==0){
                    *pq=2;
                }
            }
            else{
                printf("そのカードは出せません。考え直してください。\n");
                turn(d,p,pq,pc,pp,l);
            }
            
        }
        else if(8<=b && b<=13 && d[a][b-1]>1000 && p[a][b]>1000){
            c=1;
            for(i=7;i<b;i++){
                if(d[a][i]<1000){
                    c=0;
                }
            }

            if(c==1){
                d[a][b]+=1000;
                p[a][b]-=1000;
                *pc-=1;
                if(*pc==0){
                    *pq=2;
                }
            }
            else{
                printf("そのカードは出せません。考え直してください。\n");
                turn(d,p,pq,pc,pp,l);
            }
        }
        else{
            printf("そのカードは出せません。考え直してください。\n");
            turn(d,p,pq,pc,pp,l);
        }      
    }
    else if(a==4){
        if(*pp==0){
            printf("パスが残り0回なのでもう一度パスすると負けてしまいます。\n");
            printf("それでもよろしければもう一度、4を入力してください。\n");
            printf("考え直す場合は、5を入力してください。\n");
            scanf("%d", &b);
            if(b==4){
                printf("パスします。あなたは負けてしまいました。\n");
                *pp-=1;
                *pq=0;
                bankrupt(d,p,pc);
            }
            else{
                turn(d,p,pq,pc,pp,l);
            }

        }
        else{
            printf("パスします。\n");
            *pp-=1;
        }
    }
    else if(a==100){
        *l=0;
    }
    else{
        printf("その行動はできません。考え直してください。");
        turn(d,p,pq,pc,pp,l);
    }

    return 0;
}

int judge(int pq[4])
{
    int i,j,sum=0;

    for(i=0;i<=3;i++){

        sum+=pq[i];
        if(pq[i]==1){
            j=i;
        }

        if(pq[i]==2){
            printf("p%dの勝利\n", i);
            return 0;
        }
    }
    
    if(sum==1){
        printf("p%dの勝利\n", j);
        return 0;
    }

    return 1;
}

int bankrupt(int d[4][14], int p[4][14], int *pc)
{
    int i,j;

    for(i=0;i<=3;i++){
        for(j=1;j<=13;j++){
            if(p[i][j]>1000){
                p[i][j]-=1000;
                d[i][j]+=1000;
            }
        }
    }

    *pc=0;

    return 0;
}

int change(void)
{
    int c;
    printf("次のプレイヤーに交代してください。\n");
    printf("交代したら 0 を入力してください。\n");
    scanf("%d", &c);
    if(c!=0){
        printf("0 以外が入力されました。やり直します。\n");
        change();
    }
    return 0;
}