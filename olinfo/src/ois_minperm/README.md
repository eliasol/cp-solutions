Per prima cosa notiamo che possiamo esplicitare la richiesta del problema notando
che ciò che ci viene chiesto non è altro che trovare una permutazione raggiungibile
del vettore originale che sia "il più possibile ordinata", ovvero in cui il numero
di coppie di elementi non ordinati sia il minore possibile.<br />
Un'osservazione fondamentale è che gli spostamenti che possiamo fare non dipendono in
alcun modo dalla disposizione dei valori, ma solo dai valori L e dalla posizione considerata.
Osserviamo quindi che ogni posizione può essere vista come nodo di un grafo non diretto nel
quale c'è un arco fra A e B se |A-B| = K(i) per un qualche i.<br />
A questo punto l'osservazione che permette di risolvere il problema è che all'interno di ogni
componente connessa, siamo in grado di disporre i valori in una qualunque permutazione degli stessi,
e scegliamo quindi la permutazione che presenta i valori in ordine crescente in quando è quella che
minimizza il coefficiente.<br />
Riassumendo, ogni componente connessa è come se fosse un array a sé stante che ordiniamo.
Per trovare queste componenti possiamo, o servirci di una semplice dfs oppure utilizzare le dsu.
