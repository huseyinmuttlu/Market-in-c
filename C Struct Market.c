#include <stdio.h> 
#include <locale.h>
int kayitliUrun=0;// toplam kayýtlý ürünün bulunduðu deðiþken, global tanýmlandý
struct Urunler // bütün ürünlerin bulunacaðý tek yönlü liste
{ 
	char kategori;// her ürünün kategorisi olacak
	char adi[20];// her ürünün adý olacak
	float maliyet;// her ürünün maliyeti olacak - buradan sonraki deðiþkenler ürünün kategorisine göre boþ olabilir
	char tip;//eðer kategori et ise rbp, tarým ise ms, gýda dýþý ise cpd olabilir. diðerlerinde yok
	char paketlemeTarihi[10];//##,##,#### - þeklinde tarih
	char sonKullanmaTarihi[10];//##,##,#### - þeklinde tarih
	char konserveSonKullanim[7];//eðer konserve ise ##,#### - þeklinde günsüz tarih
	char alinmaTarihi[10];//##,##,####-- þeklinde tarih tutacak
	char reyontipi;//a veya b olacak char
	int reyonNo;// tam sayý reyon numarasý
	struct Urunler *sonraki; // sonraki urunun ramdeki adresini tutacak
}; 
void urun_kaydet(struct Urunler** basUrun) // yeni ürünü kaydeden fonksiyon
{ 
	printf("---%d. ürün bilgileri----\n",kayitliUrun+1);//kacýncý ürünü kaydedeceðimizi yazdýrdýk
    struct Urunler* eklenecekUrun = (struct Urunler*) malloc(sizeof(struct Urunler)); //ürüne ram'de yer ayýrdýk
    printf("Ürün Kategorisini Seçiniz(E,T,S,K,G) ->");// ürünün kategorisini
    scanf(" %[^\t\n]c",&eklenecekUrun->kategori);
    printf("\nÜrün adýný giriniz ->");//adýný
    scanf(" %[^\t\n]s",&eklenecekUrun->adi);//scanf %s ile boþluk alýnmadýðý için yeni satýr girene kadar aldýk 
    printf("\nÜrünün TL cinsinden birim maliyetini giriniz -> ");//ve maliyetini aldýrdýk
    scanf("%f",&eklenecekUrun->maliyet);//maliyeti float olarak aldýk
    
    if(eklenecekUrun->kategori == 'E'){//eðer kategorisi e ise ürünün 
    	printf("\nEt türünü giriniz (R-B-P) ->");// türünü
    	scanf(" %[^\t\n]c",&eklenecekUrun->tip);
    	printf("\nPaketlenme tarihini giriniz (##-##-####) ->");//paketlenme tarihini
    	scanf(" %[^\t\n]s",&eklenecekUrun->paketlemeTarihi);
    	printf("\nSon kullanim tarihini giriniz (##-##-####) ->");//ve sonkullanma tarihini aldýk
    	scanf(" %[^\t\n]s",&eklenecekUrun->sonKullanmaTarihi);//bunlarý da %s alabilirdik ama c çok verilmli çalýþmadýðý için bu þekilde aldýk kullanýcýdan
	}
	else if(eklenecekUrun->kategori == 'T'){//eðer t ise 
    	printf("\nTarým türünü giriniz (M-S) ->");//tip 
    	scanf(" %[^\t\n]c",&eklenecekUrun->tip);
    	printf("\nAlýnma tarihini giriniz (##-##-####) ->");// ve alinma tarihini ekleyecek
    	scanf(" %[^\t\n]s",&eklenecekUrun->alinmaTarihi);
	}
	else if(eklenecekUrun->kategori == 'S'){//eðer s ise
    	printf("\nSon kullaným tarihini giriniz (##-##-####) ->");//sadece son kullanma tarihini alacak
    	scanf(" %[^\t\n]s",&eklenecekUrun->sonKullanmaTarihi);
	}
	else if(eklenecekUrun->kategori == 'K'){//eðer k ise
    	printf("\nSon kullanim tarihini giriniz (##-####) ->");// son kullaným
    	scanf(" %[^\t\n]s",&eklenecekUrun->konserveSonKullanim);
    	printf("\nReyon numarasý giriniz ->");//reyon no
    	scanf("%d",&eklenecekUrun->reyonNo);
    	printf("\nReyon tarafý giriniz (A-B) ->");// reyon tipini alacak
    	scanf(" %[^\t\n]c",&eklenecekUrun->reyontipi);
	}
	else if(eklenecekUrun->kategori == 'G'){//eðer g ise
    	printf("\nTürünü giriniz (C-P-D) ->");//türünü
    	scanf(" %[^\t\n]c",&eklenecekUrun->tip);
    	printf("\nReyon numarasý giriniz ->");//reyon no
    	scanf("%d",&eklenecekUrun->reyonNo);
    	printf("\nReyon tarafý giriniz (A-B) ->");// ve reyon tipini alacak
    	scanf(" %[^\t\n]c",&eklenecekUrun->reyontipi);
	}
	else{//eðer yukardaki etskg 'den baþka girdi varsa hatalý giriþ olmuþtur, 
		printf("Hatalý giriþ.");
		free(eklenecekUrun);//ramdeki urunu sildik
		return ;//geri döndü
	}
	eklenecekUrun->sonraki = NULL;//sonraki elemaný null yaptýk
	
    struct Urunler *enSon = *basUrun;//en sondaki ürüne kadar gidip ondan sonraki elemaný bu yeni oluþan eleman yapýcaz
    if (*basUrun == NULL) //eðer en baþtaki ürün boþsa yani eklenmemiþse
    { 
       *basUrun = eklenecekUrun; //en baþtaki eleman þimdiki eleman olacak
       kayitliUrun++;//kayýt sayýsýný artýrýp
       return; // bitecek
    } 
    
    while (enSon->sonraki != NULL) //en sondaki elemana kadar
        enSon = enSon->sonraki; //sonraki elemana geçecek
    enSon->sonraki = eklenecekUrun; //en sondaki elemanýn sonraki elemaný yeni eleman olacak
    kayitliUrun++;//kayýt sayýsýný bir arttýrdý
    return; //bitti
} 
void urun_goster(struct Urunler** basUrun){//urunleri yazdýracak fonksiyon parametre olarak yine urunler struct'ý alýyor
	printf("-----------Kayýtlý Ürünler----------");
	struct Urunler* gecici = *basUrun;// geçici olarak bi struct nesnesi oluþturduk
	while(gecici != NULL){//bu eleman boþ olmadýðý sürece
		if(gecici->kategori == 'E'){//eðer e ise alttaki þekilde
			printf("\nAdi : %s Maliyeti : %.2fTL Türü : %c Paketleme Tarihi : %s Son Kullaným Tarihi : %s",gecici->adi,gecici->maliyet,gecici->tip,gecici->paketlemeTarihi,gecici->sonKullanmaTarihi);
		}
		else if(gecici->kategori == 'T'){//eðer t ise allttaki þekilde yazdýrma yapacak, zaten diðer deðiþkenler kullanýlmadýðý için yalnýzca bunlarý yazdýrmalýyýz.
			printf("\nAdi : %s Maliyeti : %.2fTL Türü : %c Alýnma Tarihi %s",gecici->adi,gecici->maliyet,gecici->tip,gecici->alinmaTarihi);
		}
		else if(gecici->kategori == 'S'){
			printf("\nAdi : %s Maliyeti : %.2fTL Son Kullaným Tarihi : %s", gecici->adi,gecici->maliyet,gecici->sonKullanmaTarihi);
		}
		else if(gecici->kategori == 'K'){
			printf("\nAdi : %s Maliyeti : %.2fTL Son Kullaným Tarihi : %s Reyon Numarasý : %d Reyon Tarafý : %c",gecici->adi, gecici->maliyet,gecici->sonKullanmaTarihi,gecici->reyonNo,gecici->reyontipi);
		}
		else if(gecici->kategori == 'G'){
			printf("\nAdi : %s Maliyeti : %.2fTL Türü : %c Reyon Numarasý : %d Reyon Tarafý : %c",gecici->adi,gecici->maliyet,gecici->tip,gecici->reyonNo,gecici->reyontipi);
		}
		gecici=gecici->sonraki;//sonraki elemana geçiyoruz 
	}
}
int main(){
	setlocale(LC_ALL,"Turkish");// türkçe karakter problemini çözdük
  	struct Urunler* bas = NULL; //yeni bi struct elemaný oluþturduk
	urun_kaydet(&bas);//yeni eleman kaydettik istediðimiz kadar ekleme yapabiliriz bunu çoðaltarak
	urun_kaydet(&bas);//yeni eleman kaydettik
	urun_goster(&bas);//elemanlarý yazdýrdýk.
	return 0;
}
