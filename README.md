# Crypto

La commande make ou make run demandera n et k en arguments (N=? et K=? existe dejà dans le Makefile pour y mettre les valeurs).
Un exemple de make run est déjà prêt avec un grand N et K raisonnable.
On peut aussi faire make compile puis l'executer de la menière suivante: ./crypto (n) (k)

Les 3 algorithmes ainsi que la fonction de décomposition de n-1 en 2^s*t sont dans algos.c qui possède un header correspondant et les autres fonctions utilisés sont dans tools.c qui possède aussi sont header et le tout est executer dans le main.