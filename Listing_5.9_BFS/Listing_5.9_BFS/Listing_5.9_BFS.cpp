/*
***************** Поиск в ширину *********************
*/
#define MAXV 100

struct edgenode { // структура для информации о ребре
	int y; // номер вершины на конце ребра
	int weight; // вес ребра
	struct edgenode *next; // указатель на следующее инцидентное ребро
};

struct graph { // массив вершин графа
	edgenode *edges[MAXV + 1]; // массив списков ребер инцидентных вершинам
	int degree[MAXV + 1]; // массив степеней вершин
	int nvertices; // количество вершин
	int nedges; // количество ребер
	bool directed; // орграф?
};

// Массивы для пометки вершин при обходе стр. 187
bool processed[MAXV + 1]; /* Обработанные вершины*/
bool discovered[MAXV + 1]; /* Открытые вершины */
int parent[MAXV + 1]; /* Отношения открытия */

// Листинг 5.8 Инициализация вершин для поиска в ширину стр. 187
void initialize_search(graph *g)
{
	int i; /* Счетчик */
	for (i = 1; i <= g->nvertices; i++) {
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}
// Использование стандартного стека
#include<queue>
// Определение констант (Скина использует из языка С)
#define TRUE true
#define FALSE false

// Вспомогательные функции обработки ребер и вершин
typedef void(*process_vertex_late)(int v);
typedef void(*process_vertex_early)(int v);
typedef void(*process_edge)(int x, int y);
int nedges = 0; // Количество ребер графа (подсчитываемых при работе BFS)

// Листинг 5.9 Обход графа в ширину стр. 188
void bfs(graph *g, int start, process_vertex_early pve, process_edge pe, process_vertex_late pvl)
{
	std::queue<int> q; /* Очередь вершин для обработки */
	int v; /* Текущая вершина */
	int y; /* Следующая вершина */
	edgenode *p; /* Временный указатель */
	while (!q.empty()) // Очистка очереди
		q.pop();
	nedges = 0; // Обнуляем для подсчета найденных ребер
	q.push(start);
	discovered[start] = TRUE;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		pve(v);
		processed[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
			y = p->y;
			if ((processed[y] == FALSE) || g->directed)
				pe(v, y);
			if (discovered[y] == FALSE) {
				q.push(y);
				discovered[y] = TRUE;
				parent[y] = v;
			}
			p = p->next;
		}
		pvl(v);
	}
}
// Листинг 5.10 Функция постобработки вершины стр. 187
void r_process_vertex_late(int v)
{
	printf("processed vertex late %d\n", v);
}

// Листинг 5.11 Функция предобработки вершины и обработки ребра стр. 188
void r_process_vertex_early(int v)
{
	printf("processed vertex early %d\n", v);
}

void r_process_edge(int x, int y)
{

	printf("processed edge (%d, %d) \n", x, y);
	nedges++; // Подсчет количества ребер - из Листинга 5.12 стр. 188
}
