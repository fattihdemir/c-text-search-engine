#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define MAX 1000
// Renk Kodlarý
#define RENK_SARI  "\033[1;33m"
#define RENK_SIFIR "\033[0m"

void metniKucukYap(char *str) {
	int i;
    for (i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
}

int main() {
    // türkçe karakterler için terminali UTF-8 moduna alýyoruz 
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

    FILE *dosya, *rapor;
    char satir[MAX], kelime[50], dosyaAdi[50], devam;

    while (1) {
        int satirNo = 0, toplam = 0;

        printf("\n>>> Dosya adini girin: "); scanf("%s", dosyaAdi);
        printf(">>> Aranacak kelime: "); scanf("%s", kelime);
        
        char arananOrijinal[50];
        strcpy(arananOrijinal, kelime); // Ekranda göstermek için orijinal hali
        metniKucukYap(kelime);

        dosya = fopen(dosyaAdi, "r");
        if (!dosya) { printf("[HATA] Dosya acilamadi!\n"); continue; }

        rapor = fopen("rapor.txt", "a");
        fprintf(rapor, "\n--- ARAMA: %s | Kelime: %s ---\n", dosyaAdi, arananOrijinal);

        printf("\nSonuclar:\n");

        while (fgets(satir, MAX, dosya)) {
            satirNo++;
            char temp[MAX];
            strcpy(temp, satir);
            metniKucukYap(temp);

            char *bulunanYer = strstr(temp, kelime);
            if (bulunanYer) {
                toplam++;
                
                // --- TERMINALDE SADECE KELIMEYI RENKLI YAZDIRMA ---
                int baslangicIndeksi = (int)(bulunanYer - temp);
                
                printf("Satir %d: ", satirNo);
                
                // Kelimeye kadar olan kýsmý yazdýr
                int i;
                for(i = 0; i < baslangicIndeksi; i++) printf("%c", satir[i]);
                
                // Sadece kelimeyi SARI yazdýr
                printf(RENK_SARI);
                for(i = 0; i < strlen(kelime); i++) printf("%c", satir[baslangicIndeksi + i]);
                printf(RENK_SIFIR);
                
                //  Kelimeden sonrasýný yazdýr
                printf("%s", &satir[baslangicIndeksi + strlen(kelime)]);

                // --- RAPORA NORMAL YAZDIRMA ---
                fprintf(rapor, "Satir %d: %s", satirNo, satir);
            }
        }

        printf("\n>>> Toplam %d eslesme bulundu.\n", toplam);
        fprintf(rapor, "Toplam Eslesme: %d\n", toplam);

        fclose(dosya);
        fclose(rapor);

        printf("\nYeni arama? (e/h): "); scanf(" %c", &devam);
        if (devam == 'h' || devam == 'H') break;
    }
    return 0;
}
