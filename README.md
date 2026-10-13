# ICPC TRD

### Правила сборки PDF
    0. Используйте Linux
    1. sudo apt update
    2. sudo apt install python3-pip texlive-luatex texlive-lang-korean texlive-latex-extra texlive-math-extra fonts-anonymous-pro texlive-latex-base
    5. chmod u+x compile.sh
    6. ./compile.sh
    7. PDF готов!

В репозитории настроен github workflow для автоматической сборки PDF на серверах Гитхаба.
Готовые файлы будут загружаться в раздел "Releases" с указанием даты и времени сборки в часовом поясе UTC+0 (-3 часа от Москвы).

Сборка с выгрузкой в Releases производится при каждом коммите в ветку `master`.
Сборка без выгрузки в Releases производится при каждом обновлении файлов в пулл-реквестах, такой файл можно будет найти в разделе Actions. 