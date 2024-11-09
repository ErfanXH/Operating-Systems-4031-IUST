در جستجوی چند‌ پردازه‌ای و چند‌نخی بخاطر تعداد محدود هسته‌های cpu
تعداد محدودی پروسس/ترد ساختیم. ساختن بیشتر از آن سرعت را افزایش نمی‌دهد. چرا که بیش از این موازی نمی‌شوند. جستجو همروند است و فقط سربار داده ایم.

### Sample 1
n = 6
```
~/u/ta/OS/A-HeapSearch ./a.out < sample.in.txt 
normal search took 0
multi thread search took 808
multi process search took 1732
```
### Sample 2
n = 5000
```
~/u/ta/OS/A-HeapSearch ./a.out < sample2.in.txt
normal search took 13
multi thread search took 427
multi process search took 960

~/u/ta/OS/A-HeapSearch ./a.out < sample2.in.txt
normal search took 13
multi thread search took 664
multi process search took 903

~/u/ta/OS/A-HeapSearch ./a.out < sample2.in.txt
normal search took 14
multi thread search took 484
multi process search took 936
```
در این ابعاد جستجوی چند پردازه‌ای یا چند نخی سودی ندارد و فقط سربار اضافه می‌کند. سربار فورک بخاطر کپی کردن حافظه بیشتر است.
### Sample 3
n = 100000
```
~/u/ta/OS/A-HeapSearch ./a.out < sample3.in.txt
normal search took 1539
multi thread search took 837
multi process search took 1433

~/u/ta/OS/A-HeapSearch ./a.out < sample3.in.txt
normal search took 1181
multi thread search took 730
multi process search took 1190

~/u/ta/OS/A-HeapSearch ./a.out < sample3.in.txt
normal search took 1083
multi thread search took 770
multi process search took 1144
```
با افزایش تعداد عناصر، مزیت جستجوی چند‌نخی مشخص می‌شود. اما بین جستجوی معمولی و چند پردازه‌ای نتیجه مشخص نیست.
### Sample 4
n = 100000000
```
~/u/ta/OS/A-HeapSearch ./a.out < sample4.in.txt
normal search took 612666
multi thread search took 142871
multi process search took 143505
```
در نهایت با افزایش اندازه، جستجوی چند‌پردازه‌ای خیلی سریع‌تر از جستجوی عادی می‌شود. بخاطر اینکه تعداد محدودی ترد ساختیم، مقدار اختلاف ترد و پروسس  رشد نمی‌کند . این مقدار ثابت در ابعاد خیلی زیاد به چشم نمی‌آید.