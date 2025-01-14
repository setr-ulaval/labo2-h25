/* TP2 Hiver 2025
 * Code source fourni
 * Marc-Andre Gardner
 */

#ifndef FSTOOLS_H
#define FSTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// pthread pour les mutex
#include <pthread.h>

// Cette structure est utilisée pour stocker un fichier en mémoire
// Le stockage est fait sous la forme d'une liste chaînée; des fonctions vous
// sont proposées pour utiliser ce cache plus facilement.
struct cacheFichier{
	char* nom;                     // Nom du fichier
	char* data;                    // Données contenues dans le fichier
	size_t len;                    // Longueur des données
	off_t offset;                  // Décalage (offset) actuel par rapport au début du fichier
	unsigned int countOpen;        // Nombre de programmes ayant ouvert ce fichier
	struct cacheFichier *prev;     // Pointeur vers le fichier précédent dans la liste chaînée
	struct cacheFichier *next;     // Pointeur vers le fichier suivant dans la liste chaînée
};

// Structure centrale du cache, contenant l'information sur les noms des fichiers du répertoire
// ainsi que sur le début de la liste chaînée.
// Contient également un mutex utilisé pour synchroniser les accès au cache entre les threads.
struct cacheData{
		char* rootDirIndex;
		struct cacheFichier *firstFile;
		pthread_mutex_t mutex;
};

// ATTENTION : toutes les fonctions suivantes supposent que vous avez _déjà_ l'accès exclusif au cache
// (en ayant verrouillé son mutex)
// Vous DEVEZ vous assurer que ces fonctions peuvent s'exécuter sans deadlock ou race condition.
// Toutes ces fonctions reçoivent la structure de cache comme premier argument

// Reçoit en entrée un nom de fichier et le cache à utiliser. Retourne un pointeur vers la structure
// contenant l'information sur le fichier en cas, si ce dernier existe. Sinon, retourne NULL.
struct cacheFichier* trouverFichier(struct cacheData *cache, const char *path);

// Utilise les mêmes arguments que trouverFichierEnCache, mais ajoute en plus un incrément, qui sera
// ajouté à la variable membre countOpen de la structure. Cet incrément peut être positif ou négatif.
struct cacheFichier* incrementerCompteurFichier(struct cacheData *cache, const char *path, int increment);

// Insère un nouveau fichier dans le cache
void insererFichier(struct cacheData *cache, struct cacheFichier *infoFichier);

// Retire un fichier du cache : attention, cette fonction ne vérifie pas que plus personne n'utilise
// ce fichier (en vérifiant que countOpen == 0).
void retirerFichier(struct cacheData *cache, struct cacheFichier *infoFichier);

#endif
