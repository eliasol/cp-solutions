Per risolvere il problema è sufficiente vedere l'insieme dei numeri da 0 a 1e9 come un grafo diretto in cui esiste un arco fra A e B, se una delle operazioni
permesse applicata su A da come risultato B. <b>NOTA!</b> non è possibile costruire davvero il grafo ma comunque non è necessario.<br />
A questo punto dobbiamo trovare il percorso più corto che da N porta a 0, e siccome gli archi non sono pesati, è sufficiente una bfs.
