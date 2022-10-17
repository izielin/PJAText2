# Projekt semestralny
## Opis
Aplikacja uruchamiana z wiersza poleceń, która na podstawie przekazanych flag, zwraca odpowiednie informacje odpowiadające działaniu poszczególnych flag.

## Flagi
	Nazwa
		-f, --file
	Użycie
		-f [file path]
	Opis
		Wywołanie tej flagi powoduje wczytanie danych z podanego pliku źródłowego. Dane te będą podstawą do działania innych flag.
	OPTIONS
	   -n, --newlines
       Wyświetla liczbę wierszy z pliku wejściowego.
     -d, --digits
       Wyświetla liczbę cyfr z pliku wejściowego
     -dd, --numbers
       Wyświetla liczbę liczb z pliku wejściowego. Jako liczbę definiujemy każde słowo, które możemy całościowo zinterpretować jako liczbę rzeczywistą.
     -c, --chars
       Wyświetla liczbę znaków z pliku wejściowego.
     -w, --words
        Wyświetla liczbę słów z pliku wejściowego. Jako słowo definiujemy dowolny ciąg znaków innych niż białe. Liczby traktujemy również jako słowa.
     -s, --sorted
        Wyświetla wszystkie słowa z pliku wejściowego w porządku alfabetycznym.
     -rs, --reverse-sorted
        Wyświetla wszystkie słowa w pliku wejściowym w kolejności odwrotnej do alfabetycznej.
     -l, --by-length
       Modyfikuje zachowanie pierwszej flagi następującej po -s lub -rs. Po użyciu flagi -l kolejność słów będzie określona przez ich długość.
     -a [words ...], --anagrams [words ...]
       Wyświetla wszystkie anagramy słów po fladze, które pojawiają się w pliku wejściowym. Powinna to być ostatnia podana flaga. Liczba słów jest nieograniczona,            również 0.
     -p [words ...], --palindromes [words ...]
       Wyświetla wszystkie słowa następujące po fladze, które są palindromami i pojawiają się w pliku wejściowym. Powinna to być ostatnia podana flaga. Liczba słów            jest nieograniczona, również 0.
     -o [file path], --output [file path]
        Wynik działania programu zostanie zwrócony zamiast na konsoli do pliku o ścieżce określonej po fladze.
	
	Nazwa
			-i, --input
	Użycie
			-i [file path]
	Opis
			Gdy ta flaga jest wywoływana, kolejne instrukcje są ładowane z pliku o ścieżce określonej po fladze. Ta flaga powinna być jedyną określoną podczas uruchamiania         aplikacji
			
	Nazwa
			-m, --merge
	Użycie
			-f [file path] -m [file paths]
	Opis
		  Gdy ta flaga zostanie wywołana, pliki, których ścieżki podano po opcji -m zostaną połączone z plikiem określonym po opcji -f. Obecność flagi -f jest obowiązkowa.
      Flaga -m powinna pojawić się zaraz za flagą -f.
  Ostrzeżenie
      Użycie tej falgi zmnienia zawartość pliku wejsciowego.
