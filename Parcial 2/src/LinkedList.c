#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this= NULL;
	this = (LinkedList*) malloc (sizeof(LinkedList));
	if(this!=NULL)
	{
		this->pFirstNode = NULL;
		this->size = 0;
	}
	return this;
}
/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
  int returnAux = -1;

  if(this != NULL)
  {
	returnAux = this->size;
  }

  return returnAux;
}
/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
    Node* nodoDevuelto = NULL;

    if(this!=NULL && nodeIndex>-1 && nodeIndex<ll_len(this))
    	{
        	nodoDevuelto=this->pFirstNode;
			for(i=0; i<nodeIndex; i++)
			{
				nodoDevuelto = nodoDevuelto->pNextNode;
			}
    	}
    return nodoDevuelto;
}
/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}
/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
*/
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);
    Node* pNewNode=NULL;
    Node* pPrevNode=NULL;

    if(this!=NULL && nodeIndex>-1 && len>=nodeIndex)
    {
    	pNewNode = (Node*)malloc(sizeof(Node));
    	if(pNewNode!=NULL)
    	{
    		pNewNode->pElement = pElement;
    		if(nodeIndex==0)//si se quiere añadir en la primera posición
    		{
				pNewNode->pNextNode = this->pFirstNode;
				this->pFirstNode = pNewNode;
    		}
    		else//añadir en cualquier otra paosición
    		{
    			pPrevNode = getNode(this, nodeIndex-1);
    			pNewNode->pNextNode=pPrevNode->pNextNode;
    			pPrevNode->pNextNode = pNewNode;
    		}
    		this->size++;
    		returnAux=0;
    	}
    }
    return returnAux;
}
/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}
/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{

   int returnAux = -1;
   int len=ll_len(this);

   if(this!=NULL && len>-1)
   {
		addNode(this, len, pElement); //añado a la lista
		returnAux=0;
   }
   return returnAux;
}
/** \brief Obtiene un elemento de la lista.
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* returnAux = NULL;
	Node* auxNode;
   if(this!=NULL && index>-1 && index<ll_len(this))
   {
		auxNode=getNode(this, index);
		if(auxNode!=NULL)
		{
			returnAux=auxNode->pElement;
		}
   }
   return returnAux;
}
/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNode;

    if(this!=NULL && index>-1)
    {
    	auxNode=getNode(this, index);
    	if(auxNode!=NULL)
    	{
    		auxNode->pElement=pElement;
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pPrevNode;
    Node* pRemovingNode;
    int len=ll_len(this);

    if(this!=NULL && index>-1 && len>=index)
    {
    	pRemovingNode=getNode(this, index);
    	pPrevNode=getNode(this, (index-1));
		if(pRemovingNode!=NULL)
		{
			if(!pPrevNode)
			{
				this->pFirstNode=pRemovingNode->pNextNode;
			}
			else
			{
				pPrevNode->pNextNode=pRemovingNode->pNextNode;
			}
			free(pRemovingNode);
			this->size=this->size-1;
			returnAux=0;
		}
    }
    return returnAux;
}
/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int len=ll_len(this);
    int i;

    if(this!=NULL)
    {
    	for(i=0; i<len; i++)
    	{
    		ll_remove(this, i);
    	}
    	this->pFirstNode = NULL;
    	this->size=0;
    	returnAux = 0;
    }
    return returnAux;
}
/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL && !ll_clear(this))
    {
    	free(this);
		returnAux = 0;
    }
    return returnAux;
}
/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);
    void* auxElement;

    if(this!=NULL)
    {
    	for(int index=0; index<len; index++)
    	{
    		//auxElement tiene el pElement del nodo que está en ese índice
    		auxElement = ll_get(this, index);
    		if(auxElement==pElement)
    		{
        		returnAux=index;
        		break;
    		}
    	}
    }
    return returnAux;
}
/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int len=ll_len(this);

    if(this!=NULL)
    {
    	if(!len)
    	{
    		returnAux=1;
    	}
    	else
    	{
    		returnAux=0;
    	}
    }
    return returnAux;
}
/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this);

    if(this!=NULL && index>-1 && index<=len &&
    		!addNode(this, index, pElement))
    {
    	returnAux = 0;
    }

    return returnAux;
}
/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
	void* returnAux = NULL;
	void* pAuxElement=NULL;

	if(this!=NULL && index>-1 && index<ll_len(this))
	{
		//auxElement tiene el pElement del nodo que está en ese índice
		pAuxElement = ll_get(this, index);
		if(pAuxElement!=NULL)
		{
			this->size--;
			ll_remove(this, index);
			returnAux = pAuxElement;
		}
	}
	return returnAux;
}
/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this !=NULL)
    {
		if(ll_indexOf(this, pElement)>-1)
		{
			returnAux=1;
		}
		else
		{
			returnAux=0;
		}
    }
    return returnAux;
}
/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{

    int returnAux=-1;
	void *pElement2;
    int len = ll_len(this2);

    if(this != NULL && this2 != NULL)
    {
    	returnAux=1;
    	for(int index2=0; index2<len ; index2++)
		{
    		pElement2 =ll_get(this2, index2);
    		if(ll_contains(this, pElement2)<1)
			{
				returnAux=0;
				break;
			}
		}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
	LinkedList *cloneArray = NULL;
	void* pAuxElement=NULL;
	int len = ll_len(this);

	if(this!=NULL && from>-1 && to>-1 && from<=to && from<len && to<=len)
	{
		cloneArray = ll_newLinkedList();
		if(cloneArray != NULL)
		{
			for(int i = from; i < to; i++)
			{
				pAuxElement = ll_get(this, i);
				if(pAuxElement!= NULL)
				{
					ll_add(cloneArray, pAuxElement);
				}
			}
		}
	}
	return cloneArray;
}
/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
	LinkedList *cloneArray = NULL;
	if(this != NULL)
	{
		cloneArray = ll_newLinkedList();
		if(cloneArray != NULL)
		{
			cloneArray = this;
		}
	}
	return cloneArray;
}
/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    Node* pFirstNode=NULL;
    Node* pSecondNode=NULL;
    Node* pAuxNode=NULL;
    int len=ll_len(this);
    int flagSwap=0;
    if(this!=NULL && pFunc!=NULL && (order==1 || order==0))
    {
    	do
    	{
    		flagSwap=1;
			for(int i=0;i<len-1;i++)
			{
				pFirstNode=ll_get(this, i);//primer elemento de la comparación
				pSecondNode=ll_get(this, i+1);//segundo elemento de la comparación
				if((order==1 && pFunc(pFirstNode,pSecondNode)>0) ||
					(order==0 && pFunc(pFirstNode, pSecondNode)<0))
				{
					flagSwap=0;
					pAuxNode=pFirstNode;
					ll_set(this, i, pSecondNode);
					ll_set(this, i+1, pAuxNode);
				}
			}
    	}while(flagSwap==0);
    	returnAux=0;
    }
    return returnAux;
}
/*
 * \brief Recorre los elementos de la lista y ejecuta sobre ellos la operación de la función del parámetro.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
						( 0) Si ok
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int output=-1;
	int len = ll_len(this);
	void* pElement;
	if(this!=NULL && pFunc != NULL)
	{
		for(int i = 0; i < len ; i++)
		{
			pElement = ll_get(this, i);
			pFunc(pElement);
		}
		output = 0 ;
	}
	return output;
}
//MAP DOS

int ll_mapConElemento(LinkedList* this, int (pFunc)(void*,void*),void* element)
{
    int returnAux = -1;
    int len = ll_len(this);
    void* auxElement;
    if(this != NULL)
    {
        for(int i = 0 ; i < len ; i++)
        {
            auxElement = ll_get(this, i);
            if(!pFunc(auxElement, element))
            {
            	returnAux = 0;
            }
        }
    }
    return returnAux;
}

/*
 * \brief Recorre los elementos de la lista y ejecuta sobre ellos la operación de la función del parámetro.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
						( 0) Si no existe en la base el valor introducido por parámetro.
						( 1) Si existe en la base el valor introducido por parámetro.
 */

int ll_mapExists(LinkedList* this, int (pFunc)(void*,void*),
												void* element)//la cadena que queremos saber si está en el sistema
{
    int retorno = -1;
    int len = ll_len(this);
    void* auxElement;
    if(this != NULL)
    {
        for(int i = 0 ; i < len ; i++)
        {
            //recupera el puntero a la lista
        	auxElement = ll_get(this, i);
            if(pFunc(auxElement, element))
            {
            	retorno = 1;
            	break;
            }
            else
            {
            	 retorno = 0;
            }
        }
    }
    return retorno;
}
/*
 * \brief crea una lista nueva que cumple la condición que entra por parámetro.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return   NULL   = algo salio mal
             Linkedlist*= OK.
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int len = ll_len(this);
	LinkedList* auxList = NULL;
	void* pElement=NULL;

	if(this!=NULL && pFunc!=NULL)
	{
		auxList = ll_newLinkedList();
		if(auxList!=NULL)
		{
			for(int i=0; i<len;i++)
			{
				pElement = ll_get(this, i);
				if(pElement!=NULL && pFunc(pElement)==0)
				{
					ll_add(auxList, pElement);
				}
			}
		}
	}
	return auxList;
}


int ll_reduceInt(LinkedList* this, int (*pFunc)(void*, void*), int id,int* pResultado)
{
	int returnAux=-1;
	int len = ll_len(this);
	int acc=0;
	void* pElement=NULL;
	if(this!=NULL && pFunc!=NULL && len>-1)
	{
		for(int i=0;i<len;i++)
		{
			pElement = ll_get(this, i);
			acc= acc + pFunc(pElement,(void*) id);
		}
		*pResultado = acc;
		returnAux=0;
	}
	return returnAux;
}
