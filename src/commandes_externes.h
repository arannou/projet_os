#ifndef _COMMANDES_EXTERNES_H_
#define _COMMANDES_EXTERNES_H_
#include "divers.h"
#include "parse.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

t_bool ActionEXEC (parse_info *info, int debut, int nbArg);

#endif
