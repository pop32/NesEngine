# NesEngine

memo

mingw32-make SHELL=CMD.exe -j4 -f makefile.gcc BUILD=release UNICODE=1 SHARED=0 MONOLITHIC=0 CXXFLAGS="-fno-keep-inline-dllexport -std=gnu++11 -static-libgcc -static-libstdc++"

※-static-libgcc -static-libstdc++　きかないっぽい
mingw の bin パス通せばOK



参考<br>
- http://bkclass.web.fc2.com/doc_wxsamples.html
