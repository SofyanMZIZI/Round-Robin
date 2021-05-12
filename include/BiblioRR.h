/********************************************************************************/
/*                                /               \                             */
/*                               ((__-^^'---'^^-__))                            */
/*                                `-_---'   '---_-'                             */
/*                                 <__|o'   'o|__>                              */
/*                                    \       /                                 */
/*                                .-'. ):   :( .'-.                             */
/*   ,-.                        .'  :   :o_o:   :  '.   .   , ,---, , ,---, ,   */
/*  (   `      ,-              /   /     "-"     \   \  |\ /|    /  |    /  |   */
/*   `-.  ,-.  |  . . ,-: ;-. :   ;               :   : | V |   /   |   /   |   */
/*  .   ) | |  |- | | | | | | :  `-._           _.-`  : |   |  /    |  /    |   */
/*   `-'  `-'  |  `-| `-` ' '  :     ""--. .--""     :  '   ' '---' ' '---' '   */
/*            -'  `-'           '.  _    ; ;       .'                           */
/*                               {"".''._.-._.''.""}                            */
/*                                \       :       /                             */
/*                                 \     / \     /                              */
/*                                  '-..'   '..-'                               */
/********************************************************************************/
#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    int pid;
    int ArrivalTime;
    int RunTime;
}process;

typedef struct elm
{
    process p;
    struct elm* suiv;
}elm;

typedef elm* list;





list AjoutProcessus(list l,process proc)
{
    elm* tmp=(elm*)malloc(sizeof(elm));

    tmp->p=proc;
    if (l==NULL)
    {
        tmp->suiv=tmp;
        return tmp;
    }
	
    tmp->suiv=l->suiv;
    l->suiv=tmp;
    l=tmp;
	
    return l;
}


void AfficheProcess(list l) 
{ 
    
    printf("-Ordre des processus: (PID,temps d'arrive,temps d'execution)\n\t");
    if (l==NULL) 
        printf("!!!!!VIDE!!!!!\n");
    else
    {
        list tmp=l->suiv; 
        do
        { 
            printf("(%d,%d,%d) --> ",tmp->p.pid,tmp->p.ArrivalTime,tmp->p.RunTime);
            tmp=tmp->suiv;
        } 
        while(tmp!=l->suiv);
    }
    printf("\n\n");
}


void SupprimerProc(elm** head)
{
    int i, count=0;
    elm *prev, *cur;

    if (*head == NULL)
    {
        printf("!!!!!AUVUN PROCESSUS A SUPPRIMER!!!!!\n");
        return;
    }

    cur   = *head;
    prev  = cur;
    while (prev->suiv != *head) 
    {
        prev = prev->suiv;
        count++;
    }

    i=0;
    while (i<=count)
    {
        if (cur->p.RunTime<=0)
        {
            if (cur->suiv != cur)
                prev->suiv = cur->suiv;
            else
                prev->suiv = NULL;
            if (cur == *head)
                *head = prev->suiv;
            free(cur);
            if (prev != NULL) 
                cur = prev->suiv;
            else
                cur = NULL;
        }
        else 
        {
            prev = cur;
            cur  = cur->suiv;
        }
        i++;
    }
}


void ordonnancer(list l,int qtm,int* com_ctx,int* t_exct)
{
    int pidAvant,pidApres;
    list tmp=l->suiv;

    *com_ctx=0;
    *t_exct=0;
    printf("\n-Ordonnancement des processus: ()<=>commutaion de contexte\n\t");
    while(1)
    {
        SupprimerProc(&tmp);
        if(tmp==NULL)
            break;
        tmp->p.RunTime-=qtm;
        if(pidApres!=pidAvant)
        {
            printf("() --> ");
            (*com_ctx)++;
            (*t_exct)++;
        }
        printf("P%d --> ",tmp->p.pid);


        pidAvant=tmp->p.pid;
        tmp=tmp->suiv;
        (*t_exct)++;
        pidApres=tmp->p.pid;
    }

    printf("\n\t%d commutations de contexe.\n\tTemps d'execution totale %d.\n",*com_ctx,*t_exct);
}




void remplissage(list* l)
{
    unsigned int n;
    process proc;

    do
    {
        printf("Donnez le nombre de processus suivant l'ordre temporaire:");
        scanf("%d",&n);
    }while (n <= 0);
    
    for(int i=0;i<n;i++)
    {
        printf("\t------------------------------------------\n");
        printf("\tREMPLIR P%d:\n",i);
        proc.pid=i;

        printf("\t\tDonnez le temps d'arrive:");
        scanf("%d",&proc.ArrivalTime);
        printf("\t\tDonnez le temps d'execution:");
        scanf("%d",&proc.RunTime);
        printf("\t------------------------------------------\n");
        *l=AjoutProcessus(*l,proc);
    }
}