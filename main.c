#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TABLOBUYUKLUK 8
#define MAYINSAYIM 7
#define WIN 1
#define LOSE -1
#define CONTINUE 0

/*

*/


int botTab[MAYINSAYIM+2][MAYINSAYIM+2];//10 a 10 luk bir matris olusturuyoruz.
char tab[MAYINSAYIM+2][MAYINSAYIM+2];// Oynanabilir alan
int mayinSayisi,y=0;
int b_sayim=0;

void altTablo();//Alt Tabloyu oluşturur.
void tabloBaslat();//ilk tabloyu oluşturur.(ön oluşturma)
void altTabloPrint();//Alt tabloyu konsola bastır.
void tabloPrint();//tüm tabloyu bastırır.
void mayinYerlestir();//mayın yerleştir.
int kontrol();//Kazanıp kazanmadığını kontrol eden fonksiyon.
void explore();//Mayın tarlasındaki nesneleri keşfediyor.

int kazmak(int satir, int sutun);//Mayın tarlasındaki istediğin koordinatı açar.



int main()
{
    int satir,sutun;

    int ilerleme;
    int tekrar;
    int b_sayim;//kac bayrak koydugunu sayan degisken

    char secim;//hangi harfi sectigini belirtir.

    setlocale(LC_ALL, "Turkish");
    printf("Mayin Tarlasi Oyuna Hosgeldiniz...\n\n");

    altTablo();
    tabloBaslat();
    //oynanabilir tabloyu main dosyasına bastırıyoruz.

    do{
        tabloPrint();
        printf("\n");
        printf("Eger o bolgeyi patlatmak isterseniz m,bayrak koymak isterseniz b, bayragi kaldirmak isterseniz de e ye basiniz ve su formatta giris yapiniz:\n m/b/e,satir,sutun");
        scanf("%c,%d,%d",&secim,&satir,&sutun);
        printf("\n");

        if(secim=='m'){
            ilerleme = kazmak(satir,sutun);
        }else if(secim=='b'){
            if(mayinSayisi > b_sayim){
                b_sayim++;
                tab[satir][sutun]='B';
                ilerleme = kontrol();
            }


        }else if(secim =='e'){

            if(b_sayim>0){

                b_sayim--;
            }

            tab[satir][sutun] ='#';
            ilerleme = kazmak(satir,sutun);
        }
        if(ilerleme == LOSE){

            printf("Oyunu kaybettiniz...\n");
            altTabloPrint();
            printf("Oyunu tekrar oynamak ister misiniz?\n[1-EVET]\n[0-HAYIR]\n");
            scanf("%d",&tekrar);
            switch(tekrar){

            case 0:
                printf("Tesekkurler\n");
                return 0;
                break;
            case 1:
                b_sayim=0;
                ilerleme=CONTINUE;

                altTablo();
                tabloBaslat();
                break;

            default:
                printf("Yanlis deger  girdiniz...");
                break;
            }
        }

        if(ilerleme==WIN){
            printf("Tebrikler Oyunu kazandiniz...");
            altTabloPrint();
            printf("Oyunu tekrar oynamak ister misiniz?\n[1-EVET]\n[0-HAYIR]\n");
            scanf("%d",&tekrar);
            switch(tekrar){


            case 0:
                printf("Umarım yeniden gorusuruz\n");
                return 0;
                break;

            case 1:
                b_sayim=0;
                ilerleme=CONTINUE;

                altTablo();
                tabloBaslat();
                break;

            default:
                printf("Yanlis deger  girdiniz...");
                break;
            }
        }

    }while(1);




    return 0;
}

void altTablo(){
    /*
    burada alt tablodaki 0 ları ve 1 den 8 e olacak şekilde sıralama satırlarını oluşturuyoruz.
    */
    int i,j,mayinSayisi;
    for(i=0;i<=TABLOBUYUKLUK+1;i++){
        for(j=0;j<=TABLOBUYUKLUK+1;j++){
            botTab[i][j] = 0;
    }
    }

    for(i=0;i<=TABLOBUYUKLUK;i++){
        botTab[i][0] = 1;
        botTab[i][TABLOBUYUKLUK+1]=1;
    }
    for(j=0;j<=TABLOBUYUKLUK;j++){
        botTab[0][j] = 1;
        botTab[TABLOBUYUKLUK+1][j] = 1;
    }
    mayinSayisi=MAYINSAYIM;
    mayinYerlestir();//mayınları burada yerleştiriyoruz.
}


void tabloBaslat(){
    /*
    koşeler * ve oynanabilir alanı # yapan fonksiyon
    */
    int i,j;
    for(i=0;i<=TABLOBUYUKLUK+1;i++){
        for(j=0;j<=TABLOBUYUKLUK+1;j++){
            tab[i][j] ='#';
    }
    }

    for(i=0;i<=TABLOBUYUKLUK+1;i++){
        tab[i][0] = '*';
        tab[i][TABLOBUYUKLUK+1]='*';
    }
    for(j=0;j<=TABLOBUYUKLUK;j++){
        tab[0][j] = '*';
        tab[TABLOBUYUKLUK+1][j] ='*';
    }

}
void tabloPrint(){
	int i,j;

	printf("\n");
	for(i=1;i<=TABLOBUYUKLUK;i++){
		printf("%3d",i);
	}
	printf("\n");
	for(i=1;i<=TABLOBUYUKLUK;i++){
		printf("---");
	}
	printf("\n");
    //3 boşluk vererek tabloyu yazdırıyor 1,2,3,..,8 şeklinde

	for(i=1;i<=TABLOBUYUKLUK;i++){
		for(j=1;j<=TABLOBUYUKLUK;j++){
			printf("%3c",tab[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}
    //tekrardan 3 satir bos bırakarak sondaki |1,|2, |3 olan kısmı yazar.

	for(i=1;i<=TABLOBUYUKLUK;i++){
		printf("___");
	}

}
void altTabloPrint(){
	int i,j;

	printf("\n");
	//Sütunları numaralandırıyoruz
	for(i=1;i<=TABLOBUYUKLUK;i++){
		printf("%3d",i);
	}
	printf("\n");

	//Tablonun üstünü sınırlıyoruz
	for(i=1;i<=TABLOBUYUKLUK;i++){
		printf("---");
	}
	printf("\n");

	//Tabloyu ekrana yazdırıyoruz
	for(i=1;i<=TABLOBUYUKLUK;i++){
		for(j=1;j<=TABLOBUYUKLUK;j++){
			printf("%3d",botTab[i][j]);
		}
		printf(" |%d",i);	//Satırları alfabetik olarak sıralıyoruz
		printf("\n");
	}

	//Tablonun altını sınırlıyoruz
	for(i=1;i<=TABLOBUYUKLUK;i++){
		printf("___");
	}
	printf("\n");
}



void mayinYerlestir()
{
	srand(time(NULL));
	int i,j,k,p,satir,sutun;
	mayinSayisi = MAYINSAYIM;
        //Madenlerin zorluk derecesine göre rastgele konumu
	for(i=1;i<=mayinSayisi;i++)
    {
        satir=1+rand()%TABLOBUYUKLUK;//Satir rastgele seçilir.
        sutun=1+rand()%TABLOBUYUKLUK;//Sütun rastgele seçilir.
        if(botTab[satir][sutun]== -1)
        {
            i--;
        } //Burada mayin varsa önceki adima döng
        botTab[satir][sutun]= -1;
        for(k=-1;k<=1;k++){//Sol Orta Sag
            for(p=-1;p<=1;p++){//Üst Orta Alt
            if(botTab[satir][sutun]==-1){//Bombaysa
            if(botTab[satir+k][sutun+p]!=-1)//Komsusu bomba deðilse
                {
                botTab[satir+k][sutun+p]++;//Çevresindeki bomba sayisini 1 arttir
                  }
                }
            }

        }

    }
}


int kontrol()
{
	int i,j,y=0,sonuc;
	for(i=1;i<=TABLOBUYUKLUK;i++)
	{
        for(j=1;j<=TABLOBUYUKLUK;j++)
        {
            if(tab[i][j]=='B')//Bayraksa say
			{
                if(botTab[i][j]==-1)
                {
                    y++;
                }
			}

        }
	}
	if(y==MAYINSAYIM) //Bayraklarin sayisiýla açilmamislarin sayisinin toplami bomba sayisina esitse

	{
		sonuc=WIN;
	}
	else
		sonuc=CONTINUE;

	return sonuc;
}

void explore(int satir, int sutun) {
	int i, j;


	tab[satir][sutun] = '0' + botTab[satir][sutun]; //Alt tablodaki deðeri üst tabloya karakter olarak atiyoruz(açma operasyonu)
  //Tüm komsular için
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			//Sayi varsa (komsusu mayinliysa)ve açik degilse
			if (botTab[satir + i][sutun + j] > 0 && tab[satir + i][sutun + j] == '#')//En az bir madene bitişik ve açıkta olmayan açık kareler
			{
				tab[satir + i][sutun + j] = '0'+ botTab[satir + i][sutun + j];//Komþuyu aç
			}
			//Sayý 0 sa (komþusu mayýnsýzsa)
			else if (botTab[satir + i][sutun + j] == 0 && tab[satir + i][sutun + j] == '#')//Herhangi bir madene bitişik olmayan ve açıkta olmayan tüm kareleri ortaya çıkarın
			{
				explore(satir + i, sutun + j);//Komsuya geç ayni islemi tekrar  recursive olarak yap
			}
		}
	}
}


int kazmak(int satir, int sutun)
{
	int x=0;
    if (botTab[satir][sutun] == -1)
    {
    	x=LOSE;//Öldün
    }

    else if (botTab[satir][sutun] > 0){
        tab[satir][sutun] = ('0' + botTab[satir][sutun]);//Aç
    	x=kontrol();//Bitti mi, kontrol et.
    	x=CONTINUE;
	}
    else
    {
    	explore(satir, sutun);}

    return x;
    }
