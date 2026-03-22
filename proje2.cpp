#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define MAX 1000
// Terminal için Kalın ve Sarı renk kodu
#define RENK_KALIN_SARI "\033[1;33m"
#define RENK_SIFIR      "\033[0m"

void metniKucukYap(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
}

int main() {
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
        strcpy(arananOrijinal, kelime);
        metniKucukYap(kelime);

        dosya = fopen(dosyaAdi, "r");
        if (!dosya) { printf("[HATA] Dosya acilamadi!\n"); continue; }

        rapor = fopen("rapor.txt", "a");
        fprintf(rapor, "\n--- ARAMA: %s | Kelime: %s ---\n", dosyaAdi, arananOrijinal);

        while (fgets(satir, MAX, dosya)) {
            satirNo++;
            char temp[MAX];
            strcpy(temp, satir);
            metniKucukYap(temp);

            char *bulunanYer = strstr(temp, kelime);
            if (bulunanYer) {
                toplam++;
                int idx = (int)(bulunanYer - temp);
                
                // TERMINAL CIKTISI (Kalın ve Sarı)
                printf("Satir %d: ", satirNo);
                for(int i = 0; i < idx; i++) printf("%c", satir[i]);
                printf(RENK_KALIN_SARI); // Parlak kalın sarıyı başlat
                for(int i = 0; i < strlen(kelime); i++) printf("%c", satir[idx + i]);
                printf(RENK_SIFIR); // Rengi sıfırla
                printf("%s", &satir[idx + strlen(kelime)]);

                // RAPOR DOSYASI CIKTISI
                // .txt'de kalınlık olmadığı için kelimeyi [ ] içine alarak belirginleştiriyoruz
                fprintf(rapor, "Satir %d: ", satirNo);
                for(int i = 0; i < idx; i++) fputc(satir[i], rapor);
                fprintf(rapor, "[%s]", arananOrijinal); // Kelimeyi paranteze al
                fprintf(rapor, "%s", &satir[idx + strlen(kelime)]);
            }
        }

        printf("\n>>> Toplam %d eslesme.\n", toplam);
        fprintf(rapor, "Toplam Eslesme: %d\n", toplam);
        fclose(dosya); fclose(rapor);

        printf("\nYeni arama? (e/h): "); scanf(" %c", &devam);
        if (devam == 'h' || devam == 'H') break;
    }
    return 0;
}
