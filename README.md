# Crypto

La commande make ou make interactive demandera n et k dans le terminal, et la command make run demandera n et k en arguments lors de l'execution (N=? et K=? existe dejà dans le Makefile pour y mettre les valeurs).
Malheureusement make interactive n'est pas utilisable sur les nombres excessivement grand car il nous est pas possible de récupérer tout les chiffres de celui-ci.
Un exemple de make run est déjà prêt avec un grand N et K raisonnable.
On peut aussi faire make compile puis l'executer de la menière suivante:
    ./crypto
       ou
    ./crypto (n) (k)

Les 3 algorithmes ainsi que la fonction de décomposition de n-1 en 2^s*t sont dans algos.c qui possède un header correspondant, leur variantes utilisant les threads se trouvent dans threads.c les autres fonctions utilisés sont dans tools.c et le tout est executé dans le main.

En cas de problème avec les threads il est possible de:
    - modifier leur nombres en modifiant NB_THREADS (ligne 8 du main.c).
    - les désactiver en mettant ACTIVE_THREADS à 0 (ligne 7 du main.c).

Il est aussi possible d'enlever l'affichage du temps en passant DISPLAY_TIME à 0 (ligne 6 du main.c).