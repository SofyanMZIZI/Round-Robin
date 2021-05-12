#include "BiblioRR.h"


int main()
{
    int n,i,qtm,t_exct,com_ctx;
    list l=NULL;
    process proc;

    remplissage(&l);

    printf("-Donnez le quantum:");
    scanf("%d",&qtm);

    AfficheProcess(l);

    ordonnancer(l, qtm, &t_exct, &com_ctx);

    return EXIT_SUCCESS;
}