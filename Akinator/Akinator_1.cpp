
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <string>
#include <Windows.h>
#include <stack>

const int STRING_SIZE = 100;
const int ANSWER_SIZE = 4;

struct Node {
	explicit Node(Node* parent_node = NULL) :
		parent(parent_node),
		right(NULL),
		left(NULL),
		data(NULL),
		depht(0) {
		if (parent_node != NULL)
			depht += parent_node->depht + 1;
	}

	~Node() {}

	Node* parent;
	Node* right;
	Node* left;
	char* data;
	int depht;
};

struct Tree {
	Tree() :
		root(new Node) {}

	~Tree() {
		delete root;
	}

	void TreeDump() {
		FILE * out = fopen("tree.gv", "w");
		fprintf(out, "digraph G {\n");
		NodeDump(out, root);
		fprintf(out, "}");
		fclose(out);
		printf("Ваш dot файл успешно создан.\n");
	}

	void NodeDump(FILE * out, const Node * node) {
		fprintf(out, "Node%p [shape=\"box\", label = \"%s\"]\n", node, node->data);
		if (node->left) {
			fprintf(out, "Node%p -> Node%p\n", node, node->left);
			NodeDump(out, node->left);
		}
		if (node->right) {
			fprintf(out, "Node%p -> Node%p\n", node, node->right);
			NodeDump(out, node->right);
		}
	}

	Node* root;
};

class GameManager {
public:
	GameManager() {
		printf(" Добро пожаловать в Акинатор !!!\n");
	}

	~GameManager() {
		if (tree.root)
			NodeDelete(tree.root);
		printf(" Игра завершена! Возвращайтесь скорее! :)\n");
	}

	void Ask(Node* node) {
		if (node == NULL) throw std::runtime_error("null_ptr!!!");

		if (node == NULL) throw std::runtime_error("null_ptr!!!");
		printf("Игра началась, отвечайте на вопросы! \n (вашим ответом может быть только \"да\" или \"нет\")\n");
		if (tree.root->data == NULL) {
			tree.root = new Node;
			tree.root->data = new char[STRING_SIZE];
			printf("Отсутствует база данных,\n Чтобы создать новое дерево, введите корневой элемент :\n");
			scanf("%99[^\n]", tree.root->data);
			node = tree.root;
		}

		char ans[10];
		while (true) {
			printf("%s?\n", node->data);
			scanf("%3s", ans);
			if (strcmp(ans, "да") == 0) {
				if (node->right == NULL) {
					printf("Хорошая работа!!!\n");
					return;
				}
				node = node->right;
			}
			else if (strcmp(ans, "нет") == 0) {
				if (node->left == NULL) {
					InsertHero(node);
					printf("Новый персонаж добавлен!\n");
					return;
				}
				node = node->left;
			}
			else
				printf("Пожалуйста, введите корректный ответ!\n");
		}
		
		std::stack<Node*> stack;
		/*
		while (node->left != NULL && node->right != NULL || stack.size() != 0) {
			printf("%s?\n", node->data);
			scanf("\n%9[^\n]", ans);
			if (strcmp(ans, "да") == 0) {
				if (node->left == NULL && node->right == 0) {
					printf("Хорошая работа!!!\n");
					return;
				}
				node = node->right;
			}
			else if (strcmp(ans, "нет") == 0) {
				if (node->left != NULL)
					node = node->left;
				else if (stack.size() != 0) {
					node = stack.top();
					stack.pop();
				}
				else {
					InsertHero(node);
					printf("Новый персонаж добавлен!\n");
					return;
				}
			}
			else if (strcmp(ans, "не знаю") == 0) {
				if (node->parent != NULL)
					if (node->parent->left == node)
						stack.push(node->parent->right);
					else
						stack.push(node->parent->left);
				else if (node == tree.root->left)
					stack.push(tree.root->right);
				else stack.push(tree.root->left);

				if (node->right != 0)
					stack.push(node->right);
				stack.push(node->left);

				node = stack.top();
				stack.pop();
			}
			 */

	}


	void InsertHero(Node* node) {
		char* hero_name = new char[STRING_SIZE];
		char* ask = new char[STRING_SIZE];
		printf("А кто же это был?\nВведите имя героя - ");
		scanf("\n%99[^\n]", hero_name);
		printf("Он(а) ...  ");
		scanf("\n%99[^\n]", ask);
		Node* ask_node = new Node(node->parent);
		ask_node->data = ask;
		Node* new_hero = new Node(ask_node);
		new_hero->data = hero_name;
		if (node->parent != NULL)
			if (node->parent->left == node) {                        // We hook to the left of the parent
				node->parent->left = ask_node;
				ask_node->left = node;
				ask_node->right = new_hero;
				node->parent = ask_node;
				node->depht += 1;
				new_hero->depht = node->depht;
			}
			else {                                                   // We hook to the right of the parent
				node->parent->right = ask_node;
				ask_node->left = node;
				ask_node->right = new_hero;
				node->parent = ask_node;
				node->depht += 1;
				new_hero->depht = node->depht;
			}
		else {														 // If we create new tree
			tree.root = ask_node;
			node->parent = ask_node;
			ask_node->parent = NULL;
			ask_node->left = node;
			ask_node->right = new_hero;
		}
	}



	void FileOpener(char c) {
		FILE * file = NULL;
		if (c == 'w' && tree.root->data != NULL)
			file = fopen("mytree.txt", "wb");
		else if (c == 'r')
			file = fopen("mytree.txt", "rb");
		else														// Случай пустого дерева, 
			return;                    								// не открываем файл, чтобы старые данный не стёрлись.

		if (file != NULL && c == 'w')
			Write(tree.root, file);
		else if (file != NULL && c == 'r')
			Read(tree.root, NULL, file);

		else throw std::runtime_error("FileOpener() - Bad file reading!!!\n");
		fclose(file);
		printf("Действие с файлом прошло успешно.\n");
	}

	void Write(const Node* node, FILE * file) {
		if (node == NULL || !file) throw std::runtime_error("Write() argument - NULL pointer!!!");
		if (node->data == NULL) return;
		char c = '[';
		fwrite(&c, sizeof(char), 1, file);
		size_t len = strlen(node->data);
		fwrite(&len, sizeof(size_t), 1, file);
		fwrite(node->data, sizeof(char), len, file);
		c = ' ';

		if (node->left) {
			fwrite(&c, sizeof(char), 1, file);
			Write(node->left, file);
		}
		else
			fwrite("N", sizeof(char), 1, file);

		if (node->right) {
			fwrite(&c, sizeof(char), 1, file);
			Write(node->right, file);
		}
		else
			fwrite("N", sizeof(char), 1, file);
		c = ']';
		fwrite(&c, sizeof(char), 1, file);
	}

	void Read(Node*& node, Node* parent, FILE * file) {
		if (!file) throw std::runtime_error("Read() - Bad file reading!!!");

		char c = 0;
		size_t len = 0;
		node = new Node(parent);
		fread(&c, sizeof(char), 1, file);
		if (c == '[') {
			fread(&len, sizeof(size_t), 1, file);
			node->data = new char[len + 1];
			fread(node->data, sizeof(char), len, file);
			node->data[len] = '\0';

			fread(&c, sizeof(char), 1, file);
			if (c == ' ') {
				node->left = new Node(node);
				Read(node->left, node, file);
			}

			fread(&c, sizeof(char), 1, file);
			if (c == ' ') {
				node->right = new Node(node);
				Read(node->right, node, file);
			}
		}
		fread(&c, sizeof(char), 1, file);

	}

	Node* Search(Node* node, char* search_name) {
		if (node == NULL) throw std::runtime_error("Search() argument - NULL pointer!!!");

		Node* ans = NULL;
		if (node->left == NULL && node->right == NULL) {
			if (strcmp(search_name, node->data))
				return NULL;
			else return node;
		}
		else if (node->left)
			ans = Search(node->left, search_name);
		if (!ans) {
			if (node->right)
				ans = Search(node->right, search_name);
		}
		return ans;
	}

	void Describe() {
		char* hero_name = new char[STRING_SIZE];
		printf("Описание персонажа.\nВведите имя персонажа, которого необходимо описать : \n");
		scanf(" %99[^\n]", hero_name);

		Node * node = Search(tree.root, hero_name);

		if (node) {
			printf("Ваш персонаж найден! Описание : \n%s - это ", hero_name);
			Node ** description = GetDescription(node);
			PrintDescription(description, 1, node->depht);

			if (description[node->depht] == description[node->depht - 1]->left)
				printf("не ");
			printf("%s.\n", description[node->depht - 1]->data);
			delete[] description;
		}
		else {
			printf("Извините, но персонаж %s не найден :(\n", hero_name);
		}
	}


	void Compare() {
		printf("Введите персонажей для сравнения :\n");
		char hero_name_1[STRING_SIZE];
		char hero_name_2[STRING_SIZE];
		scanf("\n%99[^\n]", hero_name_1);
		Node * ptr_1 = Search(tree.root, hero_name_1);
		if (!ptr_1) {
			printf("Извините, но персонаж %s не найден :(\n", hero_name_1);
			return;
		}
		scanf("\n%99[^\n]", hero_name_2);
		Node * ptr_2 = Search(tree.root, hero_name_2);

		if (!ptr_2) {
			printf("Извините, но персонаж %s не найден :(\n", hero_name_2);
			return;
		}

		Node ** description_1 = GetDescription(ptr_1);
		Node ** description_2 = GetDescription(ptr_2);

		int index = 0;
		while (description_1[index] == description_2[index])
			++index;

		printf("Результат сравнения :\n");
		if (description_1[1] == description_2[1]) {
			printf("%s и %s похожи тем, что они ", hero_name_1, hero_name_2);
			PrintDescription(description_1, 1, index);
			printf("но ");
		}

		printf("%s ", hero_name_1);
		PrintDescription(description_1, index, ptr_1->depht + 1);

		printf("а %s ", hero_name_2);
		PrintDescription(description_2, index, ptr_2->depht + 1);
		printf("\n");

		delete[] description_1;
		delete[] description_2;
	}

	void PrintDescription(Node ** description, int index_start, int index_finish) {
		for (int i = index_start; i < index_finish; ++i) {
			if (description[i] == description[i - 1]->left)
				printf("не ");
			printf("%s, ", description[i - 1]->data);
		}
	}

	Node ** GetDescription(Node* node) {
		if (node == NULL) throw std::runtime_error("Null prt!!!");

		Node ** description = new Node*[node->depht + 1];
		for (int i = node->depht; node; --i) {
			description[i] = node;
			node = node->parent;
		}
		return description;
	}

	int Exit() {
		printf("Вы уверены, что хотите закончить игру?\n"
			"[1] << Сохранить и выйти >> \n"
			"[2] << Выйти без сохранения >> \n"
			"[0] << Отмена >>\n");
		int ans = 0;
		while (true) {
			scanf("%d", &ans);
			switch (ans) {
			case 1: FileOpener('w');
				return 1;
			case 2: return 2;
			case 0: return 0;
			default: printf("Введите корректный ответ!\n");
				break;
			}
		}
	}

	void NodeDelete(Node* node) {
		if (node == NULL) throw std::runtime_error("NodeDelete() argument - NULL pointer!!!");

		if (node->data)
			delete[] node->data;
		if (node->left)
			NodeDelete(node->left);
		if (node->right)
			NodeDelete(node->right);
		if (node != tree.root)
			delete node;
	}

	int TreeRootChecker() {
		if (tree.root->data == NULL) {
			printf("Отсутствует база данных.\n");
			return 1;
		}
		else return 0;
	}

	int PlayGame() {
		printf(" << Меню >> \n [1]  << Играть в игру >> \n"
			" [2]  << Описание персонажа >> \n"
			" [3]  << Сохранить дерево в файл >> \n [4]  << Читать данные из файла >> \n"
			" [5]  << Cравнить персонажей >> \n [6]  << DOT >> \n [0]  << Закончить игру >> \n");
		while (true) {
			char ans = getchar();
			char next_symbol = '\0';
			if (ans == '\n')
				ans = getchar();
			next_symbol = getchar();
			if (next_symbol != '\n')
				ans = '\0';
			switch (ans) {
			case '1': Ask(tree.root);
				break;
			case '2': if (TreeRootChecker()) break;
				Describe();
				break;
			case '3': if (TreeRootChecker()) break;
				FileOpener('w');
				break;
			case '4': FileOpener('r');
				break;
			case '5': if (TreeRootChecker()) break;
				Compare();
				break;
			case '6': if (TreeRootChecker()) break;
				tree.TreeDump();
				break;
			case '0': if (Exit()) {
				return 0;
			}
					  else break;
			default: break;
			}
			printf("Введите номер команды : \n");
		}
		return 1;
	}

private:
	Tree tree;
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// Чтобы данные функции работали корректно необходимо установить в консоли шрифт Lucida Console.
	try {
		GameManager gm;
		gm.PlayGame();
		return 0;
	}
	catch (std::exception& ex) {
		printf("%s", ex.what());
	}
	catch (...) {
		printf("Неизвестная ошибка!\n");
	}
}
