#include<stdio.h>
#include<stdlib.h>
#include<string.h>   //ihtiyac�m olan fonksiyonlar
#include<locale.h>
#include<time.h>

#define lenght 40    //musteri ad�n�n uzunlu�u i�in belirlenen bir de�er

struct node          //node ismindeki ana yap�m�z
{
	int sira_no;                    //m��terinin s�ra numaras�n� saklayan de�i�ken
	char musteri_tam_isim[lenght];  //m��terinin ad�n� saklayan de�i�ken
	struct node *next;              //d���mlerin bir sonraki de�erleri i�in bir pointer
};

struct node *baslangic=NULL;        //d���m�n ba�lang�� de�eri
struct node *veri;                  //d���m�n i�indeki verileri saklayan pointer
struct node *temp;                  //ge�ici i�lemlerde kullan�lan pointer
struct node *silinecek;             //d���mden silmek istediklerimi ekledi�im pointer

void sira_numarasi_ver();
void musteri_sirala();
void sirasi_geleni_sil();           //burada kullan�lan fonksiyonlar tan�ml�
void sirasi_geleni_goster();
void gecikme();
void temizle();

char menu();                        //void olmayan menu fonksiyonu

int ilk_sira=100;                   //ilk s�ra de�i�keni

int a=0,i;                          //saya� de�i�kenleri

char key;                           //se�im de�i�keni

struct node *getNode()    //istenilen veri icin bellekten yer ayirdigim fonksiyon
{
    return((struct node *)malloc(sizeof(struct node)));    
}

main()
{
	setlocale(LC_ALL,"Turkish");	//tr karakter i�in k�t�phane �a�r�s�		
	musteri_sirala();               //m��teri s�ralama fonksiyonunu �al��t�r�yorum ki m��teriler ekranda g�z�ks�n(s�rada m��teri varsa)
	key=menu();                     //kullan�c� i�lemi i�in de�er al�yorum
	while(key!=13&&key!=32)         //istenilen 2 de�er oldu�u i�in bu de�erler olmazsa tekrar tekrar de�er istiyorum
	{
		key=getch();
	}
	if(key==13)                     //istenilen de�erlerden biri ENTER de�eri.
	{
		printf("\n\n");            //enter de�eri verilince sira numaras� veren fonksiyonu �al��t�r�yorum
		sira_numarasi_ver();
	}
	else                           //istenilen de�erlerden birisi de BO�LUK de�eri
	{
		sirasi_geleni_sil();      //s�ras� gelen m��teriyi (yani d���me ilk giren eleman�) siliyorum
		temizle();
		main();
	}
}

char menu()                       //menu fonksiyonu
{
	printf("\n\n\n                                        SIRA NUMARASI ALMAK ���N [ENTER]'A BASIN");         //burada sadece menu var
	printf("\n\n                                   M��TER� ��LEM�N� TAMAMLAMAK ���N [BO�LUK]'A BASIN"); 
	
	key=getch(); return key;    //kullan�c�n�n i�lemini al�yor ve d��ar�ya d�nd�r�yor 
}

void sira_numarasi_ver()        //kullan�c�lar�n ismini girdi�i ve kullan�c�lara s�ra numaras� veren fonksiyon
{
	while(baslangic!=NULL)      //e�er d���m bo�sa
	{
		veri=getNode();         //veri de�erine bellekten yer ay�r�yorum
		temp=baslangic;         //ge�ici de�erle i�lem yapaca��m i�in onu ana fonksiyon de�erine e�itliyorum
		while(temp->next!=NULL) //son d���me gelinceye kadar...
		{
			temp=temp->next;    //ge�ici de�eri bir sonraki de�ere e�itliyorum(b�yle b�yle son de�ere geliyoruz)
		}
		printf("Ad�n�z� ve soyad�n�z� girin: "); gets(veri->musteri_tam_isim); //m��terinin ad�n� ve soyad�n� sakl�yorum
		if(strlen(veri->musteri_tam_isim)==0)                                  //tabi bir �ey girilmediyse...
		{
			printf("\a"); temizle(); main();                                   //sesli uyar� at�p main'e g�nderiyorum
		}
		veri->sira_no=ilk_sira+a;                                              //m��terinin s�ra numaras�n� veriyorum
		printf("\n%s s�ra numaran�z ->%d",veri->musteri_tam_isim,veri->sira_no);//kullan�c�ya girdi�i ismi ve s�ra numaras�n� bildiriyorum
		gecikme(2);                                                            //ge�ikme verip i�lemleri devam ettiriyorum
		temp->next=veri;                                                       //ald���m�z de�erden sonraki de�i�kene veriyi at�yorum
		veri->next=NULL;                                                       //verinin bir sonraki de�erini NULL yap�yorum ki d���m sonu olsun                   
		a++;
		temizle();                                                             //sonra ekran� temizleyip main'e at�yorum
		main();
	}
	//bu b�l�m d���m� ilk olu�turdu�umuz b�l�m
	veri=getNode();       //veri de�eri i�in bellekten yer al�yorum
	baslangic=veri;       //ana d���m� veriye e�itliyorum
	temp=baslangic;       //ge�ici de�erle i� yapaca��m i�in ona da baslangic de�erini e�itliyorum
	printf("Ad�n�z� ve soyad�n�z� girin: "); gets(veri->musteri_tam_isim);     //kullanicidan isim al�yorum
	if(strlen(veri->musteri_tam_isim)==0)                                      //bir i�lem yap�lmad�ysa...
	{
		printf("\a"); temizle(); baslangic=NULL; main();                       //sesli uar� veriyorum ve ana d���m� NULL yap�p main'e yolluyorum
	}
	veri->sira_no=ilk_sira+a;                 //kullan�c� ismini ald�ktan sonra kullan�c�ya bir s�ra numaras� veriyorum
	printf("\n%s s�ra numaran�z ->%d",veri->musteri_tam_isim,veri->sira_no);//kullan�c�ya girdi�i ismi ve s�ra numaras�n� bildiriyorum
	gecikme(2);                                                             //ge�ikme verip i�lemleri devam ettiriyorum
	veri->next=NULL;                          //verinin bir sonraki de�erini NULL yap�yorum ki d���m sonu olsun
	a++;
	temizle();
	main();
}

void musteri_sirala()     //s�ra alan m��terileri ekrana s�ralayan fonksiyon
{
	if(baslangic==NULL)  //d���m bo�sa...
	{
		printf("           L�STE BO�");  
	}
	else                 //d���m bo� de�ilse     
	{
		temp=baslangic;       //i�lemler i�in temp de�erini ba�lang�ca e�itliyorum
		while(temp!=NULL)     //temp NULL olmad��� s�rece
		{
			printf("           Siradaki->");//en ba�takini s�radaki olarak belirtmek i�in
			for(i=1;i<temp;i++)             //d���m say�s� kadar d�nen bir d�ng�
			{
				printf("%d-%s\n                     ",temp->sira_no,temp->musteri_tam_isim); //her d�n��te d���m�n i�indeki isim ve sira bilgilerini bas�yorum
				temp=temp->next;            //her d�n��te bir sonraki d���me ge�iyorum
			} 
		}
	}	
}

void sirasi_geleni_sil()     //bu fonksiyonda, art�k s�ras� gelen m��terinin ekranda yazmas�na gerek olmad���n� d���nd���m�zden dolay� o m��teriyi siliyouz
{
	if(baslangic==NULL)     //d���m bo�sa...
	{
		printf("\a"); temizle(); main(); //sesli uyar� at�p zaten oldu�u yere geri yolluyoruz
	}
	else                   //d���m bo� de�ilse
	{
		silinecek=baslangic;         //silinecek adl� de�i�keni ana d���m�n ilk de�erine e�itliyoruz 
		baslangic=baslangic->next;   //ana d���m�n ilk de�erini bir sonraki de�er olarak g�steriyoruz
		sirasi_geleni_goster(silinecek);//burada o an silinen ki�iyi g�steren bir fonksiyon �al��t�r�yorum
		gecikme(2);                     //burada bir delay yapt�m. Silinecek(s�ras� gelen yani.d) ki�i ekranda g�steriliyor ve belirtti�im s�reden sonra di�er i�lemler devam ediyor
		free(silinecek);                //veriyi siliyorum
	}
}

void gecikme(int saniye)         //bu fonksiyon, tamamen cilalama ama�l�, g�zel dursun diye yapt���m bir delay fonksiyonu
{
	int mili_saniye=1000 * saniye;  //burada, fonksiyona �al��t�r�ld��� s�rada verilen de�ere g�re i�lem yapt�r�yorum. Milisaniye de�erini ��renmek i�in
	
	clock_t start_time =clock();    //time.h k�t�phanesinin haz�r fonksiyonu
	
	while(clock()<start_time+mili_saniye) //burada da gecikme d�ng�s� devreye giriyor
	; 
}

void sirasi_geleni_goster(struct node *veri)   //sadece s�ras� geleni ekranda g�stere fonksiyon
{
	temizle();
	printf("\a\n\n\n\n\n                                                    SIRASI GELEN M��TER�");              //s�ras� gelen ki�i ekran�n ortas�nda g�steriliyor
	printf("\n                                                     %d-%s",silinecek->sira_no,silinecek->musteri_tam_isim);//s�ras� gelen ki�inin bilgileri
}

void temizle()    //terminali gerekti�i zamanlarda temizlemek i�in kulland���m bir fonksiyon
{
	system("cls");
}

