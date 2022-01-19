#include "fstools.h"

struct cacheFichier* incrementerCompteurFichier(const char *path, struct cacheData *cache, int increment){
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

struct cacheFichier* trouverFichier(const char *path, struct cacheData *cache){
	return incrementerCompteurFichier(path, cache, 0);
}

void insererFichier(struct cacheFichier *infoFichier, struct cacheData *cache){
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

void retirerFichier(struct cacheFichier *infoFichier, struct cacheData *cache){
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
