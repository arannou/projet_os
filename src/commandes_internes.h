#ifndef _COMMANDES_INTERNES_H_
#define _COMMANDES_INTERNES_H_
#include "divers.h"
#include "parse.h"
#include <dirent.h>

t_bool  ActionSET (parse_info *info, int debut, int nbArg);
t_bool  ActionCD (parse_info *info, int debut, int nbArg);

#endif
