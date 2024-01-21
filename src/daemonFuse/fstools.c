/* TP2 Hiver 2024 
 * Code source fourni
 * Marc-Andre Gardner
 */

#include "fstools.h"

struct cacheFichier* incrementerCompteurFichier(struct cacheData *cache, const char *path, int increment){
	struct cacheFichier *fichier = cache->firstFile;

	while(fichier != NULL){
		if(strcmp(fichier->nom, path) == 0){
			fichier->countOpen += increment;
			break;
        }
		fichier = fichier->next;
	}
	return fichier;
}

struct cacheFichier* trouverFichier(struct cacheData *cache, const char *path){
	return incrementerCompteurFichier(cache, path, 0);
}

void insererFichier(struct cacheData *cache, struct cacheFichier *infoFichier){
    if(cache->firstFile == NULL){
        infoFichier->next = NULL;
	infoFichier->prev = NULL;
    }
    else{
        infoFichier->next = cache->firstFile;
        cache->firstFile->prev = infoFichier;
    }
    cache->firstFile = infoFichier;
}

void retirerFichier(struct cacheData *cache, struct cacheFichier *infoFichier){
    free(infoFichier->nom);
    free(infoFichier->data);
    if(cache->firstFile == infoFichier)
        cache->firstFile = infoFichier->next;
    if(infoFichier->prev != NULL)
        infoFichier->prev->next = infoFichier->next;
    if(infoFichier->next != NULL)
        infoFichier->next->prev = infoFichier->prev;
    free(infoFichier);
}
