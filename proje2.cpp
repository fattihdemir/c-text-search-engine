#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Küçük harfe çevirme

void kucukHarfYap(char *str) {
	int i;
    for(i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() { 

    FILE *dosya, *rapor;
    char satir[MAX];
    char kelime[50];
    char dosyaAdi[50];
    char devam;

    while(1) {

        int satirNo = 0;
        int toplamTekrar = 0;

        printf("\nDosya adini gir: ");
        scanf("%s", dosyaAdi);

        printf("Aranacak kelimeyi gir: ");
        scanf("%49s", kelime);

        // küçük harf yap
        kucukHarfYap(kelime);

        dosya = fopen(dosyaAdi, "r");

        if(dosya == NULL) {
            printf("Dosya acilamadi!\n");
            continue;
        }

        // Rapor dosyasý oluþtur
        rapor = fopen("rapor.txt", "a"); // a = ekleme modu

        fprintf(rapor, "\n===== YENI ARAMA =====\n");
        fprintf(rapor, "Dosya: %s\nKelime: %s\n\n", dosyaAdi, kelime);

        printf("\nKelimenin gectigi satirlar:\n");
        fprintf(rapor, "Kelimenin gectigi satirlar:\n");

        while(fgets(satir, MAX, dosya)) {
        	satir[strcspn(satir, "\n")] = '\0';

            satirNo++;

            char temp[MAX];
            strcpy(temp, satir);

            kucukHarfYap(temp);

            char *ptr = temp;
            int bulundu = 0;

            while((ptr = strstr(ptr, kelime)) != NULL) {
                toplamTekrar++;
                bulundu = 1;
                ptr++;
            }

            if(bulundu) {
                printf("Satir %d: %s", satirNo, satir);
                fprintf(rapor, "Satir %d: %s", satirNo, satir);
            }
        }

        printf("\nToplam tekrar sayisi: %d\n", toplamTekrar);
        fprintf(rapor, "\nToplam tekrar sayisi: %d\n", toplamTekrar);

        fclose(dosya);
        fclose(rapor);

        // tekrar çalýþtýrma
        printf("\nTekrar arama yapmak ister misin? (e/h): ");
        scanf(" %c", &devam);

        if(devam == 'h' || devam == 'H') {
            printf("Program sonlandirildi.\n");
            break;
        }
    }

    return 0;
}
