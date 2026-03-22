#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h> // Terminali UTF-8 yapmak için şart

#define MAX 1000

// UTF-8 uyumlu küçük harf dönüşümü (Basit ASCII korumalı)
void metniKucukYap(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

int main() {
    // 1. ADIM: Terminali Giriş ve Çıkışta UTF-8 (65001) moduna al
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // 2. ADIM: Yerel ayarları UTF-8 destekli yap
    setlocale(LC_ALL, ".UTF8");

    FILE *dosya, *rapor;
    char satir[MAX], kelime[50], dosyaAdi[50], devam;

    while (1) {
        int satirNo = 0, toplam = 0;

        printf("\n>>> Dosya adini girin (orn: metin.txt): "); 
        scanf("%s", dosyaAdi);
        printf(">>> Aranacak kelime: "); 
        scanf("%s", kelime);
        
        metniKucukYap(kelime);

        dosya = fopen(dosyaAdi, "r");
        if (!dosya) { 
            printf("[HATA] %s dosyasi acilamadi!\n", dosyaAdi); 
            continue; 
        }

        // 3. ADIM: Rapor dosyasını UTF-8 olarak aç/yaz
        rapor = fopen("rapor.txt", "a");
        
        fprintf(rapor, "\n--- YENI ARAMA ---\n");
        fprintf(rapor, "Dosya: %s | Kelime: %s\n", dosyaAdi, kelime);

        while (fgets(satir, MAX, dosya)) {
            satirNo++;
            char temp[MAX];
            strcpy(temp, satir);
            metniKucukYap(temp);

            if (strstr(temp, kelime)) {
                toplam++;
                // Terminale ve dosyaya yaz
                printf("Satir %d: %s", satirNo, satir);
                fprintf(rapor, "Satir %d: %s", satirNo, satir);
            }
        }

        fprintf(rapor, "Toplam Eslesme: %d\n", toplam);
        printf("\n>>> Toplam %d eslesme bulundu.\n", toplam);

        fclose(dosya);
        fclose(rapor);

        printf("\nYeni arama? (e/h): "); 
        scanf(" %c", &devam);
        if (devam == 'h' || devam == 'H') break;
    }
    return 0;
}
