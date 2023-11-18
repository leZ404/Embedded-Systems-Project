#include <print.h>

Print print; // creation dinstance de Print 
#ifdef DEBUG   // debug refere a fct afficher caractere
# define DEBUG_PRINT(x) print.afficherCaractere(x) // ou par print  
#else 
# define  DEBUG_PRINT(x) do {} while (0)   // code mort 
#endif
