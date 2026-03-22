#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h> 

#define MAX 1000

unsigned char turkceKucukHarf(unsigned char c) {
    if (c == 'I') return 253; 
    if (c == 'İ') return 'i';
    if (c == 'Ş') return 254; 
    if (c == 'Ğ') return 240; 
    if (c == 'Ü') return 252; 
    if (c == 'Ö') return 246; 
    if (c == 'Ç') return 231; 
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

void metniKucukHarfYap(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)turkceKucukHarf((unsigned char)str[i]);
    }
}

int main() {
    SetConsoleCP(1254);
    SetConsoleOutputCP(1254);
    setlocale(LC_ALL, "Turkish");

    FILE *dosya, *rapor;
    char satir[MAX], kelime[50], dosyaAdi[50], devam;

    while (1) {
        int satirNo = 0, toplamTekrar = 0;

        printf("\n>>> Dosya adini giriniz (orn: metin.txt): ");
        scanf("%s", dosyaAdi);

        printf(">>> Aranacak kelimeyi giriniz: ");
        scanf("%s", kelime);

        metniKucukHarfYap(kelime);

        dosya = fopen(dosyaAdi, "r");
        if (dosya == NULL) {
            printf("\n[HATA] %s dosyasi bulunamadi! Lutfen dosya adini kontrol edin.\n", dosyaAdi);
            continue;
        }

        rapor = fopen("rapor.txt", "a");
        if (rapor == NULL) {
            printf("\n[HATA] Rapor dosyasi olusturulamadi!\n");
            fclose(dosya);
            continue;
        }

        fprintf(rapor, "\n--- ARAMA SONUCU (%s) ---\n", dosyaAdi);
        fprintf(rapor, "Aranan Kelime: %s\n", kelime);
        printf("\nBulunan Satirlar:\n-----------------\n");

        while (fgets(satir, MAX, dosya)) {
            satirNo++;
            char tempSatir[MAX];
            
            strcpy(tempSatir, satir);
            metniKucukHarfYap(tempSatir);

            char *ptr = tempSatir;
            int satirdaBulundu = 0;

            while ((ptr = strstr(ptr, kelime)) != NULL) {
                toplamTekrar++;
                satirdaBulundu = 1;
                ptr += strlen(kelime); 
            }

            if (satirdaBulundu) {
                printf("Satir %d: %s", satirNo, satir);
                fprintf(rapor, "Satir %d: %s", satirNo, satir);
            }
        }

        printf("-----------------\n");
        printf("Toplam %d adet eslesme bulundu.\n", toplamTekrar);
        fprintf(rapor, "Toplam Sonuc: %d\n", toplamTekrar);

        fclose(dosya);
        fclose(rapor);

        printf("\nYeni arama yapmak ister misiniz? (e/h): ");
        scanf(" %c", &devam);

        if (devam == 'h' || devam == 'H') {
            printf("Programdan cikiliyor...\n");
            break;
        }
    }

    return 0;
}
