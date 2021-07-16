# SudokuGame
Скачать SFML библиотеку с сайта разработчика https://www.sfml-dev.org/download/sfml/2.5.1/ 
Инструкция по установке SFML библиотеки https://ravesli.com/graficheskaya-biblioteka-sfml-vstuplenie-i-ustanovka/ 
Дополнительные зависимости: 
sfml-graphics-d.lib
sfml-window-d.lib
sfml-audio-d.lib
sfml-system-d.lib

Для упрощения, можно использовать статическую линковку: к вышеописанному руководству, добавляем в настройках проекта C/C++ ->Preprocessor ->Preprocessor Definitions пишем SFML_STATIC; (Для всех конфигураций). В компоновщике, где прописывали зависимости, для каждого режима (!!!) отдельно — Debug и Release, копипастим следующее:
Для релиза :
sfml-graphics-s.lib
sfml-window-s.lib
sfml-system-s.lib
sfml-audio-s.lib
opengl32.lib
winmm.lib
gdi32.lib
freetype.lib
openal32.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib

Для дебага:
sfml-graphics-s-d.lib
sfml-window-s-d.lib
sfml-system-s-d.lib
sfml-audio-s-d.lib
opengl32.lib
winmm.lib
gdi32.lib
freetype.lib
openal32.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
