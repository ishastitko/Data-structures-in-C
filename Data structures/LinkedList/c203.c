/*    Queue_Init ...... inicializace fronty
**    nextIndex ....... pomocná funkce - viz popis výše
**    Queue_IsEmpty ... test na prázdnost fronty
**    Queue_IsFull .... test, zda je fronta zaplněna (vyčerpána kapacita)
**    Queue_Front ..... přečte hodnoty prvního prvku z fronty
**    Queue_Remove .... odstraní první prvek fronty
**    Queue_Dequeue ... přečte a odstraní první prvek fronty
**    Queue_Enqueue ... zařazení prvku na konec fronty
**/

#include "c203.h"

int QUEUE_SIZE = MAX_QUEUE;
int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 *
 * TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
 *
 * @param error_code Interní identifikátor chyby
 */
void Queue_Error( int error_code ) {
	static const char *QERR_STRINGS[MAX_QERR + 1] = {
			"Unknown error",
			"Queue error: ENQUEUE",
			"Queue error: FRONT",
			"Queue error: REMOVE",
			"Queue error: DEQUEUE",
			"Queue error: INIT"
	};

	if (error_code <= 0 || error_code > MAX_QERR)
	{
		error_code = 0;
	}
	printf("%s\n", QERR_STRINGS[error_code]);
	error_flag = 1;
}

/**
 * Inicializujte frontu následujícím způsobem:
 * - všechny hodnoty v poli queue->array nastavte na '*',
 * - index na začátek fronty nastavte na 0,
 * - index prvního volného místa nastavte také na 0.
 *
 * V případě, že funkce dostane jako parametr queue == NULL, volejte funkci
 * Queue_Error(QERR_INIT).
 *
 * @param stack Ukazatel na strukturu fronty
 */
void Queue_Init( Queue *queue ) {
	/** 
	 * Inicializace fronty nastavením hodnot všech prvku '*',
	 * firstIndex a freeIndex na hodnotu 0
	 */
	for (int i = 0; i < QUEUE_SIZE; i++)
		queue->array[i] = '*';
	queue->firstIndex = 0;
	queue->freeIndex = 0;
}

/**
 * Pomocná funkce, která vrací index následujícího prvku v poli.
 * Funkci implementujte jako jediný prikaz využívající operace '%'.
 * Funkci nextIndex budete využívat v dalších implementovaných funkcích.
 *
 * @param index Aktuální index
 */
int nextIndex( int index ) {
	return (index + 1) % QUEUE_SIZE;
}

/**
 * Vrací nenulovou hodnotu, pokud je frona prázdná, jinak vrací hodnotu 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 */
int Queue_IsEmpty( const Queue *queue ) {
	/* Fronta je prazdnou když první prvek je volný */
	return (queue->firstIndex == queue->freeIndex);
}

/**
 * Vrací nenulovou hodnotu, je-li fronta plná, jinak vrací hodnotu 0.
 * Funkci je vhodné implementovat jedním příkazem return
 * s využitím pomocné funkce nextIndex.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 */
int Queue_IsFull( const Queue *queue ) {
	/**
	 * Funkce nextIndex využívá operace '%'.
	 * Funkce vrací nenulovou hodnotu když index nasledujícího volného prvku
	 * bude stejný jako velikost pole což znamená, že fronta je plná.
	 * Jinak vrací nulu.
	 */
	return (nextIndex(queue->freeIndex) == 0);
}

/**
 * Prostřednictvím parametru dataPtr vrátí znak ze začátku fronty queue.
 * Pokud je fronta prázdná, ošetřete to voláním funkce Queue_Error(QERR_FRONT).
 * Volání této funkce při prázdné frontě je vždy nutné považovat za nekorektní.
 * Bývá to totiž důsledek špatného návrhu algoritmu, ve kterém je fronta
 * použita. O takové situaci se proto musí programátor-vývojář dozvědět.
 * V opačném případě je ladění programů obtížnější!
 *
 * Při implementaci využijte dříve definované funkce Queue_IsEmpty.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void Queue_Front( const Queue *queue, char *dataPtr ) {
	if (!Queue_IsEmpty(queue)){
		*dataPtr = queue->array[queue->firstIndex];
	} else Queue_Error(QERR_FRONT);
}

/**
 * Odstraní znak ze začátku fronty queue. Pokud je fronta prázdná, ošetřete
 * vzniklou chybu voláním funkce Queue_Error(QERR_REMOVE).
 * Hodnotu na uvolněné pozici ve frontě nijak neošetřujte (nepřepisujte).
 * Při implementaci využijte dříve definované funkce Queue_IsEmpty a nextIndex.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 */
void Queue_Remove( Queue *queue ) {
	if (!Queue_IsEmpty(queue)){
		queue->firstIndex = nextIndex(queue->firstIndex);

		/* Ošetření kruhovosti seznamu */
		if (queue->firstIndex > QUEUE_SIZE)
			queue->firstIndex = 1;
	} else Queue_Error(QERR_REMOVE);
}

/**
 * Odstraní znak ze začátku fronty a vrátí ho prostřednictvím parametru dataPtr.
 * Pokud je fronta prázdná, ošetřete to voláním funkce Queue_Error(QERR_DEQUEUE).
 *
 * Při implementaci využijte dříve definovaných funkcí Queue_IsEmpty,
 * Queue_Front a Queue_Remove.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void Queue_Dequeue( Queue *queue, char *dataPtr ) {
	if (!Queue_IsEmpty(queue)){
		/* Hodnota prvního prvku se zapiše do dataPtr */
		Queue_Front( queue, dataPtr );
		/* První prvek se odstraní */
		Queue_Remove(queue);
	} else Queue_Error(QERR_DEQUEUE);
}

/**
 * Vloží znak data do fronty. Pokud je fronta plná, ošetřete chybu voláním
 * funkce Queue_Error(QERR_ENQUEUE). Vkládání do plné fronty se považuje za
 * nekorektní operaci. Situace by mohla být řešena i tak, že by operace
 * neprováděla nic, ale v případě použití takto definované abstrakce by se
 * obtížně odhalovaly chyby v algoritmech, které by abstrakci využívaly.
 *
 * Při implementaci využijte dříve definovaných funkcí Queue_IsFull a nextIndex.
 *
 * @param queue Ukazatel na inicializovanou strukturu fronty
 * @param data Znak k vložení
 */
void Queue_Enqueue( Queue *queue, char data ) {
	if (!Queue_IsFull(queue)){
		queue->array[queue->freeIndex] = data;
		queue->freeIndex = nextIndex(queue->freeIndex);
		
		/* Ošetření kruhovosti seznamu */
		if (queue->freeIndex > QUEUE_SIZE)
			queue->freeIndex = 1;
	} else Queue_Error(QERR_ENQUEUE);
}

/* Konec příkladu c203.c */
