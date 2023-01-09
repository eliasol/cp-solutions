Se memorizziamo i tempi di apertura e di chiusura di ogni nodo nella dfs, tutti i nodi appartenenti ad un certo sottoalbero
hanno entrambi i tempi compresi fra l'apertura e la chiusura della radice di questo sottoalbero.
Siccome il problema chiede di effettuare degli update su tutto un sottoalbero data la radice, possiamo "linearizzare" l'albero
rappresentando i tempi di apertura e chiusura, in modo che ogni sottoalbero sia un segmento contiguo, e a questo punto
è sufficiente costruire un segment tree con point query e range update.
