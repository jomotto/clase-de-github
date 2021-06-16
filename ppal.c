#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 4
#define MAXCOLOR 6
#define LINK_DESCONECT 'D'
#define LINK_SOFT      'S'
#define LINK_HARD      'H'
// comentario 17:24

char colors[]={'w', 'r', 'b', 'o', 'g', 'y'};
//white, red, blue, orange, green, yellow

typedef struct insertos {
   int             row;
   int             column;
   char            color;

   char            connect_up_type;
   char            connect_down_type;
   char            connect_left_type;
   char            connect_right_type;
   struct insertos *connect_up;
   struct insertos *connect_down;
   struct insertos *connect_left;
   struct insertos *connect_right;
   struct insertos *p_sig;
} *t_bandeja;


int inicio_insertos(t_bandeja *pl)
{
  *pl=NULL;
  return 0;
}


/***************************************************************************/
int crear_nodo(t_bandeja *pl, int fila, int columna, char color)
{
  t_bandeja L;
  char      msg[255];
  
  L=(t_bandeja) malloc (sizeof(struct insertos));

  if (L == NULL) {
      sprintf(msg, "MEMORIA INSUFICIENTE [%i,%i,%c]\n", fila, columna, color);
      exit(0);
  }

  memset(L, '\0', sizeof(struct insertos));

  *pl=L;
  (*pl)->row    =fila;
  (*pl)->column =columna;
  (*pl)->color  = color;
  (*pl)->connect_up_type    = LINK_DESCONECT;
  (*pl)->connect_down_type  = LINK_DESCONECT;
  (*pl)->connect_left_type  = LINK_DESCONECT;
  (*pl)->connect_right_type = LINK_DESCONECT;
  (*pl)->connect_up         = NULL;
  (*pl)->connect_down       = NULL;
  (*pl)->connect_left       = NULL;
  (*pl)->connect_right      = NULL;
  (*pl)->p_sig              = NULL;

  printf("Nodo creado [%i,%i,%c]\n", fila, columna, color);
  return 0;
}

/***************************************************************************/
int insertar_det(t_bandeja *pl, t_bandeja nodo)
{
  char msg[255];

  if (*pl==nodo){
     printf("ERROR El nodo a agregar es al final es la cabecera[6]\n");
     exit(0);
  }

  if (*pl == NULL)
     *pl=nodo;
  else {
       /* buscamos el ultimo nodo */
       while ((*pl)->p_sig!=NULL)
           (*pl)=(*pl)->p_sig;

       (*pl)->p_sig=nodo;
  }

  return 0;
}



/***************************************************************************/
int search_address(t_bandeja *det_fin, int fila, int columna, char color)
{

   while ((*pl)->p_sig!=NULL)
   {
       if ((*pl)->row == fila && (*pl)->column == columna && (*pl)->color  = color)
       {
          printf("encontrado devuelvo direccion");
          break;
       }

      (*pl)=(*pl)->p_sig;
   }
}

/***************************************************************************/
int cargar_nodos(t_bandeja *det_fin)
{
  int       i, j, colorIdx;
  t_bandeja det_act;

  for (colorIdx=0; colorIdx < MAXCOLOR; colorIdx++)
  {
     for (i=0; i < MAX; i++)
     {
        for (j=0; j < MAX; j++)
        {
           crear_nodo(&det_act, i, j, colors[colorIdx]);
	   insertar_det(det_fin, det_act);

           search_address(det_fin, i, j, colors[colorIdx]);

        }
     }
     printf("----\n");
  }

  return 0;
}


/***************************************************************************/
int main()
{
  t_bandeja inserts;

  inicio_insertos(&inserts);
  cargar_nodos(&inserts);
  return 0;
}
