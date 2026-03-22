# 📄 Metin İçinde Kelime Arama Programı (C)

## 📌 Proje Hakkında
Bu C programı, kullanıcıdan alınan bir metin dosyasında belirli bir kelimeyi arar, bulunan eşleşmeleri hem terminalde vurgulayarak gösterir hem de bir rapor dosyasına kaydeder.

Program, büyük/küçük harf duyarsız (case-insensitive) arama yapar ve Türkçe karakter desteği için UTF-8 uyumludur.

---

## ⚙️ Özellikler

- 🔍 Dosya içinde kelime arama
- 🔤 Büyük/küçük harf duyarsız karşılaştırma
- 🎨 Terminalde bulunan kelimenin renkli gösterimi
- 📝 Sonuçları `rapor.txt` dosyasına kaydetme
- 🔁 Sürekli arama yapabilme (loop sistemi)
- 🇹🇷 UTF-8 desteği ile Türkçe karakter uyumu

---

## 🧠 Çalışma Mantığı

1. Kullanıcıdan:
   - Dosya adı
   - Aranacak kelime alınır

2. Kelime küçük harfe çevrilir.

3. Dosya satır satır okunur:
   - Her satırın kopyası küçük harfe çevrilir
   - `strstr()` ile arama yapılır

4. Eşleşme bulunursa:
   - Terminalde sadece eşleşen kelime sarı renkte gösterilir
   - Satır `rapor.txt` dosyasına yazılır

5. Toplam eşleşme sayısı hem ekrana hem rapora yazılır

---

## 🛠️ Kullanılan Teknolojiler

- C Programlama Dili
- `stdio.h` → Giriş/çıkış işlemleri
- `string.h` → String işlemleri
- `locale.h` → UTF-8 desteği
- `windows.h` → Konsol karakter seti ayarları

---

## 📂 Dosya Yapısı

```
proje/
│
├── main.c        → Program kodu
├── rapor.txt     → Arama sonuçlarının kaydedildiği dosya
└── README.md     → Proje açıklaması
```

---

## ▶️ Nasıl Çalıştırılır

### 1. Derleme
```bash
gcc main.c -o arama
```

### 2. Çalıştırma
```bash
./arama
```

---

## 💡 Örnek Kullanım

```
>>> Dosya adini girin: metin.txt
>>> Aranacak kelime: bilgisayar

Sonuclar:
Satir 3: bu bir bilgisayar programidir
Satir 7: bilgisayar muhendisligi

>>> Toplam 2 eslesme bulundu.
```

---

## ⚠️ Notlar

- Program yalnızca ilk eşleşmeyi bulur (satır başına tek sonuç).
- Büyük dosyalarda performans lineer olarak düşer (O(n)).
- Windows terminalinde renklerin düzgün görünmesi için ANSI desteği gerekebilir.

---

## 🚀 Geliştirme Önerileri

- Aynı satırda birden fazla eşleşme bulma
- Regex desteği ekleme
- GUI (arayüz) geliştirme
- Linux/Mac uyumluluğu artırma
- Kelime frekans analizi ekleme

---

## 👨‍💻 Geliştirici

Bu proje, metin işleme ve dosya işlemleri pratiği yapmak amacıyla geliştirilmiştir.
