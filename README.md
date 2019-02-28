# GateOpeningUnit

Scopul robotului e de a automatiza o poarta culisanta.

Foloseste un  motor de stergator de masina cu reductor, si e capabila sa deschida o poarta de pana la 250 kg.

Modalitatea de deschidere este fie prin telecomanda, fie prin semnale de pe laptop catre o aplicatie mobila, aflata pe un telefon in interiorul robotului.

Cea din urma modalitate de deschidere a fost implementata mai mult in scop didactic, pentru a imbina cunostintele de android cu cele de robotica, 
citind culoarea afisata de aplicatie in interiorul robotului, pentru a face diverse actiuni asupra portii. 
Acest mod de deschidere a portii de la mare distanta, se  poate, si va fi reimplementat folosind un shield gsm pentru a simplifica logica robotului.  

In rest, robotul foloseste:
	- O sursa de 12v 260w care  alimenteaza motorul principal 
	- O sursa mai mica de 5v ce alimenteaza relee.
	- 4 relee 
	- Un senzor infrarosu pentru control prin telecomanda
	- Un senzor de culoare pentru a interpreta semnalele primite pe telefon 
	
 