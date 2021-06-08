#include<stdio.h>
#include<stdlib.h>
#include<string.h>   //ihtiyacým olan fonksiyonlar
#include<locale.h>
#include<time.h>

#define lenght 40    //musteri adýnýn uzunluðu için belirlenen bir deðer

struct node          //node ismindeki ana yapýmýz
{
	int sira_no;                    //müþterinin sýra numarasýný saklayan deðiþken
	char musteri_tam_isim[lenght];  //müþterinin adýný saklayan deðiþken
	struct node *next;              //düðümlerin bir sonraki deðerleri için bir pointer
};

struct node *baslangic=NULL;        //düðümün baþlangýç deðeri
struct node *veri;                  //düðümün içindeki verileri saklayan pointer
struct node *temp;                  //geçici iþlemlerde kullanýlan pointer
struct node *silinecek;             //düðümden silmek istediklerimi eklediðim pointer

void sira_numarasi_ver();
void musteri_sirala();
void sirasi_geleni_sil();           //burada kullanýlan fonksiyonlar tanýmlý
void sirasi_geleni_goster();
void gecikme();
void temizle();

char menu();                        //void olmayan menu fonksiyonu

int ilk_sira=100;                   //ilk sýra deðiþkeni

int a=0,i;                          //sayaç deðiþkenleri

char key;                           //seçim deðiþkeni

struct node *getNode()    //istenilen veri icin bellekten yer ayirdigim fonksiyon
{
    return((struct node *)malloc(sizeof(struct node)));    
}

main()
{
	setlocale(LC_ALL,"Turkish");	//tr karakter için kütüphane çaðrýsý		
	musteri_sirala();               //müþteri sýralama fonksiyonunu çalýþtýrýyorum ki müþteriler ekranda gözüksün(sýrada müþteri varsa)
	key=menu();                     //kullanýcý iþlemi için deðer alýyorum
	while(key!=13&&key!=32)         //istenilen 2 deðer olduðu için bu deðerler olmazsa tekrar tekrar deðer istiyorum
	{
		key=getch();
	}
	if(key==13)                     //istenilen deðerlerden biri ENTER deðeri.
	{
		printf("\n\n");            //enter deðeri verilince sira numarasý veren fonksiyonu çalýþtýrýyorum
		sira_numarasi_ver();
	}
	else                           //istenilen deðerlerden birisi de BOÞLUK deðeri
	{
		sirasi_geleni_sil();      //sýrasý gelen müþteriyi (yani düðüme ilk giren elemaný) siliyorum
		temizle();
		main();
	}
}

char menu()                       //menu fonksiyonu
{
	printf("\n\n\n                                        SIRA NUMARASI ALMAK ÝÇÝN [ENTER]'A BASIN");         //burada sadece menu var
	printf("\n\n                                   MÜÞTERÝ ÝÞLEMÝNÝ TAMAMLAMAK ÝÇÝN [BOÞLUK]'A BASIN"); 
	
	key=getch(); return key;    //kullanýcýnýn iþlemini alýyor ve dýþarýya döndürüyor 
}

void sira_numarasi_ver()        //kullanýcýlarýn ismini girdiði ve kullanýcýlara sýra numarasý veren fonksiyon
{
	while(baslangic!=NULL)      //eðer düðüm boþsa
	{
		veri=getNode();         //veri deðerine bellekten yer ayýrýyorum
		temp=baslangic;         //geçici deðerle iþlem yapacaðým için onu ana fonksiyon deðerine eþitliyorum
		while(temp->next!=NULL) //son düðüme gelinceye kadar...
		{
			temp=temp->next;    //geçici deðeri bir sonraki deðere eþitliyorum(böyle böyle son deðere geliyoruz)
		}
		printf("Adýnýzý ve soyadýnýzý girin: "); gets(veri->musteri_tam_isim); //müþterinin adýný ve soyadýný saklýyorum
		if(strlen(veri->musteri_tam_isim)==0)                                  //tabi bir þey girilmediyse...
		{
			printf("\a"); temizle(); main();                                   //sesli uyarý atýp main'e gönderiyorum
		}
		veri->sira_no=ilk_sira+a;                                              //müþterinin sýra numarasýný veriyorum
		printf("\n%s sýra numaranýz ->%d",veri->musteri_tam_isim,veri->sira_no);//kullanýcýya girdiði ismi ve sýra numarasýný bildiriyorum
		gecikme(2);                                                            //geçikme verip iþlemleri devam ettiriyorum
		temp->next=veri;                                                       //aldýðýmýz deðerden sonraki deðiþkene veriyi atýyorum
		veri->next=NULL;                                                       //verinin bir sonraki deðerini NULL yapýyorum ki düðüm sonu olsun                   
		a++;
		temizle();                                                             //sonra ekraný temizleyip main'e atýyorum
		main();
	}
	//bu bölüm düðümü ilk oluþturduðumuz bölüm
	veri=getNode();       //veri deðeri için bellekten yer alýyorum
	baslangic=veri;       //ana düðümü veriye eþitliyorum
	temp=baslangic;       //geçici deðerle iþ yapacaðým için ona da baslangic deðerini eþitliyorum
	printf("Adýnýzý ve soyadýnýzý girin: "); gets(veri->musteri_tam_isim);     //kullanicidan isim alýyorum
	if(strlen(veri->musteri_tam_isim)==0)                                      //bir iþlem yapýlmadýysa...
	{
		printf("\a"); temizle(); baslangic=NULL; main();                       //sesli uarý veriyorum ve ana düðümü NULL yapýp main'e yolluyorum
	}
	veri->sira_no=ilk_sira+a;                 //kullanýcý ismini aldýktan sonra kullanýcýya bir sýra numarasý veriyorum
	printf("\n%s sýra numaranýz ->%d",veri->musteri_tam_isim,veri->sira_no);//kullanýcýya girdiði ismi ve sýra numarasýný bildiriyorum
	gecikme(2);                                                             //geçikme verip iþlemleri devam ettiriyorum
	veri->next=NULL;                          //verinin bir sonraki deðerini NULL yapýyorum ki düðüm sonu olsun
	a++;
	temizle();
	main();
}

void musteri_sirala()     //sýra alan müþterileri ekrana sýralayan fonksiyon
{
	if(baslangic==NULL)  //düðüm boþsa...
	{
		printf("           LÝSTE BOÞ");  
	}
	else                 //düðüm boþ deðilse     
	{
		temp=baslangic;       //iþlemler için temp deðerini baþlangýca eþitliyorum
		while(temp!=NULL)     //temp NULL olmadýðý sürece
		{
			printf("           Siradaki->");//en baþtakini sýradaki olarak belirtmek için
			for(i=1;i<temp;i++)             //düðüm sayýsý kadar dönen bir döngü
			{
				printf("%d-%s\n                     ",temp->sira_no,temp->musteri_tam_isim); //her dönüþte düðümün içindeki isim ve sira bilgilerini basýyorum
				temp=temp->next;            //her dönüþte bir sonraki düðüme geçiyorum
			} 
		}
	}	
}

void sirasi_geleni_sil()     //bu fonksiyonda, artýk sýrasý gelen müþterinin ekranda yazmasýna gerek olmadýðýný düþündüðümüzden dolayý o müþteriyi siliyouz
{
	if(baslangic==NULL)     //düðüm boþsa...
	{
		printf("\a"); temizle(); main(); //sesli uyarý atýp zaten olduðu yere geri yolluyoruz
	}
	else                   //düðüm boþ deðilse
	{
		silinecek=baslangic;         //silinecek adlý deðiþkeni ana düðümün ilk deðerine eþitliyoruz 
		baslangic=baslangic->next;   //ana düðümün ilk deðerini bir sonraki deðer olarak gösteriyoruz
		sirasi_geleni_goster(silinecek);//burada o an silinen kiþiyi gösteren bir fonksiyon çalýþtýrýyorum
		gecikme(2);                     //burada bir delay yaptým. Silinecek(sýrasý gelen yani.d) kiþi ekranda gösteriliyor ve belirttiðim süreden sonra diðer iþlemler devam ediyor
		free(silinecek);                //veriyi siliyorum
	}
}

void gecikme(int saniye)         //bu fonksiyon, tamamen cilalama amaçlý, güzel dursun diye yaptýðým bir delay fonksiyonu
{
	int mili_saniye=1000 * saniye;  //burada, fonksiyona çalýþtýrýldýðý sýrada verilen deðere göre iþlem yaptýrýyorum. Milisaniye deðerini öðrenmek için
	
	clock_t start_time =clock();    //time.h kütüphanesinin hazýr fonksiyonu
	
	while(clock()<start_time+mili_saniye) //burada da gecikme döngüsü devreye giriyor
	; 
}

void sirasi_geleni_goster(struct node *veri)   //sadece sýrasý geleni ekranda göstere fonksiyon
{
	temizle();
	printf("\a\n\n\n\n\n                                                    SIRASI GELEN MÜÞTERÝ");              //sýrasý gelen kiþi ekranýn ortasýnda gösteriliyor
	printf("\n                                                     %d-%s",silinecek->sira_no,silinecek->musteri_tam_isim);//sýrasý gelen kiþinin bilgileri
}

void temizle()    //terminali gerektiði zamanlarda temizlemek için kullandýðým bir fonksiyon
{
	system("cls");
}

