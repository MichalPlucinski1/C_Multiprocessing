przygotowanie:
problem jest rozwiązany za pomocą 4 semaforów: 
swiatlo0
swiatlo1
waga
osoby

semafory swiatła mogą mieć wartości z zakresu 0-1, zaczyna z 1 (światło zielone)

waga zaczyna z wartością max_waga

osoby zaczynaja z wartością 0

algorytm dla każdego procesu:
opuść swoje światła (czeka na zielone)
opuść światło przeciwnej strony (daj mu czerwone swiatlo)
podnieś światło swojej strony (żeby inni z jego strony mogli przejść)

opuść wagę o masę  (test masy)
podnieś ilość osób

//przechodzi\\

podnieś wagę

opuść ilość osób

jezeli ilość osób = 0
	podnieś swiatło drugiej strony (wszyscy maja wtedy zielone)
