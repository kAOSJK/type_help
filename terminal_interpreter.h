#ifndef TERMINAL_INTERPRETER
#define TERMINAL_INTERPRETER

#include "terminal_row.h"

#define CMD_HELP "TYPE HELP DEMO BRO\nBRO\nBRO..."
#define REPORT01 \
"================================================================================\n" \
"RAPPORT 01 - LANCEMENT                                      11 AVRIL 1970, 14:13\n" \
"================================================================================\n" \
" \n" \
"EQUIPAGE\n" \
"       CDR Lovell\n" \
"       CMP Swigert\n" \
"       LMP Haise\n" \
" \n" \
"COMPTE-RENDU\n" \
"       Deux jours avant le départ, le pilote du module de commande est\n" \
"       remplacé -- rubéole confirmée, immunité nulle. Swigert le remplace.\n" \
"       La substitution passe sans accroc.\n" \
" \n" \
"       Décollage nominal. Le moteur central du S-II s'arrête 132 secondes\n" \
"       trop tôt -- les quatre restants compensent. Orbite : 100 x 98 miles.\n" \
"       44 secondes de retard à l'insertion. Rien d'alarmant.\n" \
" \n" \
"STATUT\n" \
"       Tout nominal. Rien à signaler."

#define REPORT02 \
"================================================================================\n" \
"RAPPORT 02 - L'INCIDENT                                     13 AVRIL 1970, 21:08\n" \
"================================================================================\n" \
" \n" \
"COMPTE-RENDU\n" \
"       Brassage de routine des réservoirs d'oxygène. Swigert actionne\n" \
"       le contacteur. Deux secondes plus tard, un court-circuit.\n" \
" \n" \
"       Un bang sourd traverse le vaisseau. Alarme principale. L'ordinateur\n" \
"       redémarre. Le réservoir O2 N.2 chute à zéro. Le N.1 suit lentement.\n" \
"       Lovell aperçoit du gaz s'échapper du module de service.\n" \
"       Les piles tombent l'une après l'autre. T+55:54:53.\n" \
" \n" \
"       L'alunissage est annulé. L'objectif : rentrer vivants.\n" \
" \n" \
"STATUT\n" \
"       Situation critique. La mission est perdue, pas l'équipage."

#define REPORT03 \
"================================================================================\n" \
"RAPPORT 03 - AQUARIUS                                       14 AVRIL 1970, 04:00\n" \
"================================================================================\n" \
" \n" \
"COMPTE-RENDU\n" \
"       Odyssey est mis hors tension. L'équipage se regroupe dans Aquarius,\n" \
"       prévu pour deux hommes et 44 heures. Il devra en abriter trois\n" \
"       pendant 83 heures. Consommation réduite à 12 ampères.\n" \
" \n" \
"       Le CO2 monte. Les cartouches d'Odyssey sont carrées, celles\n" \
"       d'Aquarius sont rondes. Houston improvise un adaptateur : sac\n" \
"       plastique, carton, ruban adhésif. Assemblé à bord. Ça marche.\n" \
" \n" \
"       Deux tirs moteur pour rentrer plus vite. Zone d'amerrissage\n" \
"       déplacée vers le Pacifique Sud. Transit raccourci de 9 heures.\n" \
" \n" \
"STATUT\n" \
"       Sous contrôle. Chaque heure compte."

#define REPORT04 \
"================================================================================\n" \
"RAPPORT 04 - LE RETOUR                                          15-16 AVRIL 1970\n" \
"================================================================================\n" \
" \n" \
"COMPTE-RENDU\n" \
"       12 degrés dans la cabine. Condensation sur les parois. L'équipage\n" \
"       dort par intermittence. Haise souffre -- une infection urinaire\n" \
"       sera confirmée à la récupération.\n" \
" \n" \
"       À T+105h, correction manuelle : Lovell utilise le terminateur de\n" \
"       la Terre comme référence dans la lunette. 14 secondes à 10%.\n" \
"       La précision est suffisante.\n" \
" \n" \
"       À T+138h, le module de service est séparé. Par le hublot, Lovell\n" \
"       découvre les dégâts : le panneau de la baie 4 a disparu.\n" \
" \n" \
"STATUT\n" \
"       L'équipage tient. L'entrée atmosphérique approche."

#define REPORT05 \
"================================================================================\n" \
"RAPPORT 05 - AMERISSAGE                                     17 AVRIL 1970, 12:07\n" \
"================================================================================\n" \
" \n" \
"COMPTE-RENDU\n" \
"       À T+141:30, Aquarius est largué. La pression du tunnel fournit\n" \
"       la vitesse de séparation. Le module brûle à l'entrée atmosphérique.\n" \
" \n" \
"       Rentrée nominale à T+142:40. Pic de décélération : 5g. Trois\n" \
"       parachutes. Amerrissage à T+142:54:41, un mile du point cible.\n" \
"       L'USS Iwo Jima est en vue. Récupération en 45 minutes.\n" \
" \n" \
"       Lovell. Swigert. Haise. Indemnes. 142 heures après le départ.\n" \
" \n" \
"STATUT\n" \
"       Mission perdue. Équipage sain et sauf."

void terminal_interpret(const Row *row);

#endif
