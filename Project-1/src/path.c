#include "path.h"
#include "libs.h"

void splitPath(char *fullPath, char *path, int lenPath, char *nomeArq, int lenNomeArq, char *extArq, int lenExtArq) {
  int point = 0;
  bool found = false;
  
  for (int i = 0; i < lenPath; i++){
    if (fullPath[i] == '/') {
      found = true;
    }
  }

  if (found) {
    getPath(fullPath, path, lenPath);
  } else {
    path = "";
  }

  for (int i = 0; i < lenNomeArq; i++) {
    if (fullPath[i] == '.') {
      point = i;
      found = true;
    } else {
      found = false;
    }
  }

  if (found) {
    getFileName(fullPath, nomeArq, lenNomeArq);
    for (int i = 0; i < point; i++) {
      extArq[i] = nomeArq[point];
      point++;
    }
    nomeArq[point] = '\0';
    return;
  } else {
    getFileName(fullPath, nomeArq, lenNomeArq);
    extArq = "";
    return;
  }
}

void joinFilePath(char *path, char *fileName, char *fullPath, int lenFullPath) {
  if (!path) {
    strcpy(fullPath, fileName);
    return;
  }
  
  if (path[strlen(path)-1] != '/') {
    strcpy(fullPath, path);
    strcat(fullPath, "/");
    strcat(fullPath, fileName);
    return;
  }

  strcpy(fullPath, path);
  strcat(fullPath, fileName);

  return;
}

void joinAll(char *path, char *fileName, char *ext, char *fullPath, int lenFullPath) {
  if (!path) {
    strcpy(fullPath, strcat(fileName, ext));
    return;
  }
  
  if (path[strlen(path)-1] != '/') {
    strcat(path, "/");
  }
  
  strcpy(fullPath, path);
  strcat(fullPath, fileName);
  strcat(fullPath, ext);

  return;
}

void getFileName(char *fullPath, char *fileName, int lenFileName) {
  bool found = false;
  int index =0;
  int j = 0;

  for (int i = 0; i < lenFileName; i++){
    if (fullPath[i] == '/') {
      index = i;
      found = true;
    }
  }

  if (found) {
    for (int i = index + 1; i < lenFileName; i++) {
      fileName[j] = fullPath[i];
      j++;
    }
    return;
  } else {
    strcpy(fileName, fullPath);
    return;
  }
}

void getPath(char *fullPath, char *path, int lenPath) {
  int index =0;
  bool found = false;
  
  for (int i = 0; i < lenPath; i++){
    if (fullPath[i] == '/') {
      index = i;
      found = true;
    }
  }

  if (found) {
    for (int i = 0; i < index; i++) {
      path[i] = fullPath[i];
    }
    return;
  } else {
    strcpy(path, "");
    return;
  }
}

void normalizePath(char *path, char *normPath, int lenNormPath) {
  strcpy(normPath, path);
  if (normPath[lenNormPath-1] == '/') {
    normPath[lenNormPath-1] = '\0';
    return;
  } else {
    return;
  }
}