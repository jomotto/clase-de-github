#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 3
#define MAXCOLOR 6
#define LINK_DESCONECT 'D'
#define LINK_SOFT      'S'
#define LINK_HARD      'H'


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
  (*pl)->row    =fila+1;
  (*pl)->column =columna+1;
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

  t_bandeja det_tmp;

  det_tmp = *pl;

  if (det_tmp==nodo){
     printf("ERROR El nodo a agregar es al final es la cabecera[6]\n");
     exit(0);
  }

  if (det_tmp == NULL)
     *pl=nodo;
  else {
       /* buscamos el ultimo nodo */
       while (det_tmp->p_sig!=NULL)
           det_tmp=det_tmp->p_sig;

       det_tmp->p_sig=nodo;
  }

  return 0;
}

int print_det(t_bandeja *pl)
{

  t_bandeja nodo;

  nodo = *pl;

 while (nodo){

     printf("%i-%i-%c\n", nodo->row, nodo->column, nodo->color);
      nodo=nodo->p_sig;
  }
  return 0;
}

/***************************************************************************/
int search_address(t_bandeja *pl, int fila, int columna, char color, t_bandeja *foundNode)
{
  t_bandeja nodo;
  t_bandeja beforeNode;
  int		find;

  nodo = *pl;
  find = 0;

	beforeNode = *pl;
	while (nodo->p_sig!=NULL)
   {
       if (nodo->row == fila && nodo->column == columna && nodo->color  == color)
       {
          printf("encontrado devuelvo direccion");
		  *foundNode = beforeNode;
		  find = 1;
          break;
       }

	   beforeNode = nodo;
      nodo=nodo->p_sig;
   }

	if (!find)
	{
		*foundNode = NULL;
	}

return 0;
}

/***************************************************************************/
int cargar_nodos(t_bandeja *det_fin)
{
  int       r, c, colorIdx;
  t_bandeja det_act, addressNode;
  int       beforeR, beforeC;


  for (colorIdx=0; colorIdx < MAXCOLOR; colorIdx++)
  {
     for (r=1; r <= MAX; r++)
     {
        for (c=1; c <= MAX; c++)
        {
           crear_nodo(&det_act, r, c, colors[colorIdx]);
		   insertar_det(det_fin, det_act);
		   
		   beforeR = r-1,
		   beforeC = c-1;
		   if (r > 0 && beforeC >0)
		   {
				search_address(det_fin, r, beforeC, colors[colorIdx], &addressNode);
				det_act->connect_left = addressNode;
				
		   }

		   if (beforeR > 0 && c >0)
		   {
				search_address(det_fin, beforeR, c, colors[colorIdx], &addressNode);
				det_act->connect_up = addressNode;
		   }
        }
     }
     printf("----\n");
  }

  return 0;
}



int main( int argc, char** argv )
{
  t_bandeja inserts;

  inicio_insertos(&inserts);
  cargar_nodos(&inserts);
  print_det(&inserts);
  
  exit( EXIT_SUCCESS );
}
