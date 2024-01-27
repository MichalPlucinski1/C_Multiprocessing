przygotowanie:
problem jest rozwiązany za pomocą 4 semaforów: 
swiatlo0
swiatlo1
waga
osoby

semafory swiatla moze miec wartosci z zakresu 0-1, zaczyna z 1 (swiatlo zielone)

waga zaczyna z wartoscia max_waga

osoby zaczynaja z wartoscia 0

algorytm dla kazdego procesu:
opusc swoje swiatla (czeka na zielone)
opusc swiatlo przeciwnej strony (daj mu czerwone swiatlo)
podnies swiatlo swojej strony (zeby inni z jego strony mogli przejsc)

opusc waga o masa  (test masy)
podnies ilosc osob

//przechodzi\\

opdnies waga

opusc ilosc osob

jezeli ilosc osob = 0
	podnies swiatlo drugiej strony (wszyscy maja wtedy zielone)
