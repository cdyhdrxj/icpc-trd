# ============================================================
# 1. БЫСТРЫЙ ВВОД / ВЫВОД (sys)
# ============================================================
import sys                                          # модуль для быстрого ввода-вывода
input = sys.stdin.readline                          # заменяем input на быстрый аналог (читает строку с '\n')
data = sys.stdin.read().split()                     # читаем весь ввод сразу в список токенов (быстрее всего)
sys.stdout.write("hello\n")                         # быстрый вывод без авто-'\n'
sys.stdout.write("\n".join(map(str, [1, 2, 3])) + "\n")   # быстрый вывод массива одной строкой
sys.setrecursionlimit(10**6)                        # увеличиваем лимит рекурсии
sys.stderr.write("debug\n")                         # отладочный вывод в stderr, не влияет на stdout
# sys.stdout = open("in.txt", "w")                  # перенаправление вывода в файл
# ============================================================
# 2. decimal — точная десятичная арифметика
# ============================================================
from decimal import Decimal, getcontext, ROUND_HALF_UP, ROUND_DOWN   # импорт классов и режимов округления
getcontext().prec = 50                              # задаём точность: 50 значащих цифр (по умолчанию 28)
a = Decimal("0.1")                                  # создаём Decimal из СТРОКИ — иначе унаследуется погрешность float
print(Decimal(1) / Decimal(3))                      # деление с точностью prec знаков
x = Decimal("2.34567")                              # число с 5 знаками после точки
print(x.quantize(Decimal("0.01"), rounding=ROUND_HALF_UP))   # округление до 2 знаков, математически
print(x.quantize(Decimal("0.001"), rounding=ROUND_DOWN))     # округление до 3 знаков, вниз
print(Decimal(2).sqrt())                            # квадратный корень с точностью prec
print(Decimal(100).ln())                            # натуральный логарифм
print(Decimal("0.1") + Decimal("0.2") == Decimal("0.3"))     # True — точное сравнение
# Decimal("Infinity"), Decimal("NaN"); x.is_nan(), x.is_infinite(), x.is_finite()   # спец. значения и проверки
# Смешивать Decimal и float нельзя — TypeError; приводи через Decimal(str(x))       # важное правило
# ============================================================
# 3. fractions — точные рациональные дроби
# ============================================================
from fractions import Fraction                      # импорт класса обыкновенных дробей
a = Fraction(1, 3)                                  # дробь 1/3
b = Fraction(2, 6)                                  # автоматически сократится до 1/3
print(Fraction("0.25"), Fraction("3.14"))           # 1/4 157/50 — разбор десятичной строки
print(f.numerator, f.denominator)                   # 3 2 — числитель и знаменатель (знаменатель всегда > 0)
print(Fraction(7, 2) % 1)                           # 1/2 — дробный остаток
print(Fraction(1, 3) < Fraction(1, 2))              # True — точное сравнение
print(sorted([Fraction(2, 3), Fraction(1, 4), Fraction(5, 6)]))   # сортировка без погрешностей
# ============================================================
# 4. datetime — даты и время
# ============================================================
from datetime import datetime, date, time, timedelta   # классы для дат, времени и разниц
import calendar                                        # модуль для календарных функций
d1 = date(2024, 1, 1)                               # дата 1 января 2024
d2 = date(2024, 12, 31)                             # дата 31 декабря 2024
dt = datetime(2024, 5, 15, 13, 30, 45)              # дата + время
print((d2 - d1).days)                               # 365 — разница в днях
print(d1 + timedelta(days=100))                     # 2024-04-10 — прибавление 100 дней
print(d1.weekday(), d1.isoweekday())                # 0 (Пн)  1 (1..7) — день недели
dt = datetime.strptime("2024-05-15 13:30:45", "%Y-%m-%d %H:%M:%S")   # разбор строки в datetime
print(dt.strftime("%d.%m.%Y %H:%M"))                # 15.05.2024 13:30 — форматирование в строку
# Коды: %Y %y — год, %m %B %b — месяц, %d — день, %H %M %S — время, %A %a — день недели, %j — день года
print(calendar.isleap(2024))                        # True — високосный ли год
print(date(2024, 1, 1).toordinal() - date(2023, 1, 1).toordinal())   # 365 — разница через порядковый номер дня
# ============================================================
# 5. re — регулярные выражения
# ============================================================
import re                                           # модуль регулярных выражений
s = "abc 123 def 456 xyz"                           # тестовая строка
print(re.findall(r"\d+", s))                        # ['123','456'] — все числа
print(re.findall(r"[a-z]+", s))                     # ['abc','def','xyz'] — все слова из строчных букв
m = re.search(r"\d+", s)                            # первый Match; search() ищет в любом месте строки
print(m.group(), m.start(), m.end())                # '123' 4 7 — совпадение и его позиции
print(bool(re.match(r"abc", s)))                    # True — match() якорит начало строки
print(re.sub(r"\d+", "#", s))                       # abc # def # xyz — замена всех совпадений
print(re.sub(r"\d+", lambda m: str(int(m.group()) * 2), s))   # удвоить все числа через функцию
print(re.split(r"\s+", s))                          # ['abc','123','def','456','xyz'] — разбиение по пробелам
text = "Иван 25, Мария 30, Пётр 17"                 # строка с именем и возрастом
for name, age in re.findall(r"(\w+)\s+(\d+)", text):   # группы захвата: имя и число
    print(name, age)                                # печатаем каждую пару
for m in re.finditer(r"(?P<name>\w+)\s+(?P<age>\d+)", text):   # именованные группы, ленивый итератор
    print(m.group("name"), m.group("age"))          # доступ по имени группы
rx = re.compile(r"\d+")                             # скомпилированный шаблон — экономит время при переиспользовании
# Синтаксис: . \d \D \w \W \s \S  *  +  ?  {n,m}  ^  $  \b  [abc] [^abc]  ( ) (?: )  |  (?P<name>)
nums = list(map(int, re.findall(r"-?\d+", sys.stdin.read())))   # вытащить все числа (в т.ч. отрицательные) из ввода
# ============================================================
# 6. itertools — комбинаторика и ленивые итераторы
# ============================================================
import itertools as it                              # модуль комбинаторики и ленивых итераторов
print(list(it.permutations([1, 2, 3])))             # все перестановки (n! = 6)
print(list(it.permutations([1, 2, 3], 2)))          # размещения по 2 (порядок важен)
print(list(it.combinations([1, 2, 3, 4], 2)))       # сочетания по 2 (порядок не важен)
print(list(it.combinations_with_replacement([1, 2, 3], 2)))   # сочетания с повторами
print(list(it.product([0, 1], "ab")))               # декартово произведение двух множеств
print(list(it.product([0, 1], repeat=3)))           # все 8 двоичных строк длины 3
print(list(it.accumulate([1, 2, 3, 4])))            # [1,3,6,10] — префиксные суммы
print(list(it.accumulate([1, 2, 3, 4], lambda a, b: a * b)))   # префиксные произведения
print(list(it.accumulate([3, 1, 4, 1, 5], max)))    # [3,3,4,4,5] — префиксные максимумы
data = sorted([("a", 1), ("a", 2), ("b", 3), ("a", 4)])   # groupby требует сортировки по ключу!
for key, g in it.groupby(data, key=lambda x: x[0]):   # группировка по первому элементу
    print(key, list(g))                             # печатаем ключ и элементы группы
print(list(it.islice(it.count(), 5)))               # [0,1,2,3,4] — берём 5 первых из бесконечного счётчика
print(list(it.islice(it.cycle("ab"), 7)))           # ['a','b','a','b','a','b','a'] — цикл, обрезанный до 7
print(list(it.chain([1, 2], [3, 4], "ab")))         # [1,2,3,4,'a','b'] — склеивание итераторов
print(list(it.takewhile(lambda x: x < 5, [1, 3, 7, 1])))   # [1,3] — берёт, пока условие True
print(list(it.dropwhile(lambda x: x < 5, [1, 3, 7, 1])))   # [7,1] — пропускает, пока условие True
print(list(it.starmap(pow, [(2, 3), (3, 2)])))      # [8,9] — как map, но распаковывает кортежи в аргументы
