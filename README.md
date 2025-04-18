# RUTM

A lightweight C++ header-only class for converting between geographic coordinates (latitude and longitude) and UTM (Universal Transverse Mercator) coordinates.

## ✨ Features

- Convert latitude/longitude to UTM (zone number and letter)
- Convert UTM to latitude/longitude
- Purely mathematical — no external libraries required
- Header-only: easy to integrate into any project
- Includes basic zone validation and projection formulas

## 📂 Structure

- `RUTM::from_latlon(...)`  
  Converts latitude and longitude to UTM coordinates

- `RUTM::to_latlon(...)`  
  Converts UTM coordinates back to latitude and longitude

## ⚙️ Usage

```cpp
#include "RUTM.h"

RUTM rutm;
RUTM::structUTMlatlong utm = rutm.from_latlon(35.6892, 51.3890, 0, 0);
std::cout << "Easting: " << utm.Latitude << ", Northing: " << utm.Logitude << std::endl;

RUTM::structlatlong latlon = rutm.to_latlon(utm.Latitude, utm.Logitude, utm.zoneUmber, utm.zoneLetter, true);
std::cout << "Latitude: " << latlon.Latitude << ", Longitude: " << latlon.Logitude << std::endl;
```

## 🔧 Compile

No external dependencies. Compile with any C++ compiler:

```bash
g++ main.cpp -o my_app
```

---

# 🇮🇷 تبدیل مختصات جغرافیایی به UTM با C++

کلاس `RUTM` یک هدر مستقل در زبان ++C است که به شما اجازه می‌دهد مختصات جغرافیایی (عرض و طول جغرافیایی) را به مختصات UTM تبدیل کرده و برعکس.

## ✨ امکانات

- تبدیل عرض و طول جغرافیایی به مختصات UTM
- تبدیل مختصات UTM به عرض و طول جغرافیایی
- بدون نیاز به هیچ کتابخانه خارجی
- فقط یک هدر: ساده برای استفاده در هر پروژه‌ای
- بررسی اعتبار ناحیه و محاسبات دقیق ریاضی

## 📦 ساختار توابع

- `from_latlon(...)`:  
  تبدیل طول و عرض جغرافیایی به مختصات UTM (شماره زون و حرف زون)

- `to_latlon(...)`:  
  تبدیل مختصات UTM به عرض و طول جغرافیایی

## 🚀 نحوه استفاده

```cpp
#include "RUTM.h"

RUTM rutm;
RUTM::structUTMlatlong utm = rutm.from_latlon(35.6892, 51.3890, 0, 0);
std::cout << "Easting: " << utm.Latitude << ", Northing: " << utm.Logitude << std::endl;

RUTM::structlatlong latlon = rutm.to_latlon(utm.Latitude, utm.Logitude, utm.zoneUmber, utm.zoneLetter, true);
std::cout << "Latitude: " << latlon.Latitude << ", Longitude: " << latlon.Logitude << std::endl;
```

## 🔨 کامپایل

برای کامپایل نیازی به هیچ وابستگی خارجی نیست:

```bash
g++ main.cpp -o my_app
```

---

## 📎 License

MIT License — Free for personal or commercial use.
