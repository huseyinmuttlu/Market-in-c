#include <stdio.h> 
#include <locale.h>
int kayitliUrun=0;// toplam kay�tl� �r�n�n bulundu�u de�i�ken, global tan�mland�
struct Urunler // b�t�n �r�nlerin bulunaca�� tek y�nl� liste
{ 
	char kategori;// her �r�n�n kategorisi olacak
	char adi[20];// her �r�n�n ad� olacak
	float maliyet;// her �r�n�n maliyeti olacak - buradan sonraki de�i�kenler �r�n�n kategorisine g�re bo� olabilir
	char tip;//e�er kategori et ise rbp, tar�m ise ms, g�da d��� ise cpd olabilir. di�erlerinde yok
	char paketlemeTarihi[10];//##,##,#### - �eklinde tarih
	char sonKullanmaTarihi[10];//##,##,#### - �eklinde tarih
	char konserveSonKullanim[7];//e�er konserve ise ##,#### - �eklinde g�ns�z tarih
	char alinmaTarihi[10];//##,##,####-- �eklinde tarih tutacak
	char reyontipi;//a veya b olacak char
	int reyonNo;// tam say� reyon numaras�
	struct Urunler *sonraki; // sonraki urunun ramdeki adresini tutacak
}; 
void urun_kaydet(struct Urunler** basUrun) // yeni �r�n� kaydeden fonksiyon
{ 
	printf("---%d. �r�n bilgileri----\n",kayitliUrun+1);//kac�nc� �r�n� kaydedece�imizi yazd�rd�k
    struct Urunler* eklenecekUrun = (struct Urunler*) malloc(sizeof(struct Urunler)); //�r�ne ram'de yer ay�rd�k
    printf("�r�n Kategorisini Se�iniz(E,T,S,K,G) ->");// �r�n�n kategorisini
    scanf(" %[^\t\n]c",&eklenecekUrun->kategori);
    printf("\n�r�n ad�n� giriniz ->");//ad�n�
    scanf(" %[^\t\n]s",&eklenecekUrun->adi);//scanf %s ile bo�luk al�nmad��� i�in yeni sat�r girene kadar ald�k 
    printf("\n�r�n�n TL cinsinden birim maliyetini giriniz -> ");//ve maliyetini ald�rd�k
    scanf("%f",&eklenecekUrun->maliyet);//maliyeti float olarak ald�k
    
    if(eklenecekUrun->kategori == 'E'){//e�er kategorisi e ise �r�n�n 
    	printf("\nEt t�r�n� giriniz (R-B-P) ->");// t�r�n�
    	scanf(" %[^\t\n]c",&eklenecekUrun->tip);
    	printf("\nPaketlenme tarihini giriniz (##-##-####) ->");//paketlenme tarihini
    	scanf(" %[^\t\n]s",&eklenecekUrun->paketlemeTarihi);
    	printf("\nSon kullanim tarihini giriniz (##-##-####) ->");//ve sonkullanma tarihini ald�k
    	scanf(" %[^\t\n]s",&eklenecekUrun->sonKullanmaTarihi);//bunlar� da %s alabilirdik ama c �ok verilmli �al��mad��� i�in bu �ekilde ald�k kullan�c�dan
	}
	else if(eklenecekUrun->kategori == 'T'){//e�er t ise 
    	printf("\nTar�m t�r�n� giriniz (M-S) ->");//tip 
    	scanf(" %[^\t\n]c",&eklenecekUrun->tip);
    	printf("\nAl�nma tarihini giriniz (##-##-####) ->");// ve alinma tarihini ekleyecek
    	scanf(" %[^\t\n]s",&eklenecekUrun->alinmaTarihi);
	}
	else if(eklenecekUrun->kategori == 'S'){//e�er s ise
    	printf("\nSon kullan�m tarihini giriniz (##-##-####) ->");//sadece son kullanma tarihini alacak
    	scanf(" %[^\t\n]s",&eklenecekUrun->sonKullanmaTarihi);
	}
	else if(eklenecekUrun->kategori == 'K'){//e�er k ise
    	printf("\nSon kullanim tarihini giriniz (##-####) ->");// son kullan�m
    	scanf(" %[^\t\n]s",&eklenecekUrun->konserveSonKullanim);
    	printf("\nReyon numaras� giriniz ->");//reyon no
    	scanf("%d",&eklenecekUrun->reyonNo);
    	printf("\nReyon taraf� giriniz (A-B) ->");// reyon tipini alacak
    	scanf(" %[^\t\n]c",&eklenecekUrun->reyontipi);
	}
	else if(eklenecekUrun->kategori == 'G'){//e�er g ise
    	printf("\nT�r�n� giriniz (C-P-D) ->");//t�r�n�
    	scanf(" %[^\t\n]c",&eklenecekUrun->tip);
    	printf("\nReyon numaras� giriniz ->");//reyon no
    	scanf("%d",&eklenecekUrun->reyonNo);
    	printf("\nReyon taraf� giriniz (A-B) ->");// ve reyon tipini alacak
    	scanf(" %[^\t\n]c",&eklenecekUrun->reyontipi);
	}
	else{//e�er yukardaki etskg 'den ba�ka girdi varsa hatal� giri� olmu�tur, 
		printf("Hatal� giri�.");
		free(eklenecekUrun);//ramdeki urunu sildik
		return ;//geri d�nd�
	}
	eklenecekUrun->sonraki = NULL;//sonraki eleman� null yapt�k
	
    struct Urunler *enSon = *basUrun;//en sondaki �r�ne kadar gidip ondan sonraki eleman� bu yeni olu�an eleman yap�caz
    if (*basUrun == NULL) //e�er en ba�taki �r�n bo�sa yani eklenmemi�se
    { 
       *basUrun = eklenecekUrun; //en ba�taki eleman �imdiki eleman olacak
       kayitliUrun++;//kay�t say�s�n� art�r�p
       return; // bitecek
    } 
    
    while (enSon->sonraki != NULL) //en sondaki elemana kadar
        enSon = enSon->sonraki; //sonraki elemana ge�ecek
    enSon->sonraki = eklenecekUrun; //en sondaki eleman�n sonraki eleman� yeni eleman olacak
    kayitliUrun++;//kay�t say�s�n� bir artt�rd�
    return; //bitti
} 
void urun_goster(struct Urunler** basUrun){//urunleri yazd�racak fonksiyon parametre olarak yine urunler struct'� al�yor
	printf("-----------Kay�tl� �r�nler----------");
	struct Urunler* gecici = *basUrun;// ge�ici olarak bi struct nesnesi olu�turduk
	while(gecici != NULL){//bu eleman bo� olmad��� s�rece
		if(gecici->kategori == 'E'){//e�er e ise alttaki �ekilde
			printf("\nAdi : %s Maliyeti : %.2fTL T�r� : %c Paketleme Tarihi : %s Son Kullan�m Tarihi : %s",gecici->adi,gecici->maliyet,gecici->tip,gecici->paketlemeTarihi,gecici->sonKullanmaTarihi);
		}
		else if(gecici->kategori == 'T'){//e�er t ise allttaki �ekilde yazd�rma yapacak, zaten di�er de�i�kenler kullan�lmad��� i�in yaln�zca bunlar� yazd�rmal�y�z.
			printf("\nAdi : %s Maliyeti : %.2fTL T�r� : %c Al�nma Tarihi %s",gecici->adi,gecici->maliyet,gecici->tip,gecici->alinmaTarihi);
		}
		else if(gecici->kategori == 'S'){
			printf("\nAdi : %s Maliyeti : %.2fTL Son Kullan�m Tarihi : %s", gecici->adi,gecici->maliyet,gecici->sonKullanmaTarihi);
		}
		else if(gecici->kategori == 'K'){
			printf("\nAdi : %s Maliyeti : %.2fTL Son Kullan�m Tarihi : %s Reyon Numaras� : %d Reyon Taraf� : %c",gecici->adi, gecici->maliyet,gecici->sonKullanmaTarihi,gecici->reyonNo,gecici->reyontipi);
		}
		else if(gecici->kategori == 'G'){
			printf("\nAdi : %s Maliyeti : %.2fTL T�r� : %c Reyon Numaras� : %d Reyon Taraf� : %c",gecici->adi,gecici->maliyet,gecici->tip,gecici->reyonNo,gecici->reyontipi);
		}
		gecici=gecici->sonraki;//sonraki elemana ge�iyoruz 
	}
}
int main(){
	setlocale(LC_ALL,"Turkish");// t�rk�e karakter problemini ��zd�k
  	struct Urunler* bas = NULL; //yeni bi struct eleman� olu�turduk
	urun_kaydet(&bas);//yeni eleman kaydettik istedi�imiz kadar ekleme yapabiliriz bunu �o�altarak
	urun_kaydet(&bas);//yeni eleman kaydettik
	urun_goster(&bas);//elemanlar� yazd�rd�k.
	return 0;
}
