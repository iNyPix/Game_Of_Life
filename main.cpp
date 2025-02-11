#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <curses.h>
#include <cstdlib> // Pour _putenv_s

using namespace std;

// Constantes
constexpr int MAX_SIZE = 20;
constexpr int ALIVE = 1;
constexpr int DEAD = 0;

// Initialise les cellules à l'état "morte".
void initialisation(int t[MAX_SIZE][MAX_SIZE])
{
    for (int row = 0; row < MAX_SIZE; row++)
        for (int col = 0; col < MAX_SIZE; col++)
            t[row][col] = DEAD;
}

// Demander une configuration NON-OPTIMALE
/*void askConfiguration(int t[MAX_SIZE][MAX_SIZE])
{
    string config;
    cout << "Enter the configuration of the life (1 for alive, 0 for dead, size = "<< pow(MAX_SIZE,2) << endl;
    cin >> config;
    if (config.size()!= floor(pow(MAX_SIZE, 2)))
        throw invalid_argument("Invalid configuration size");

    for (int row = 0; row < MAX_SIZE; row++)
        for (int col = 0; col < MAX_SIZE; col++)
            t[row][col] = config[row * MAX_SIZE + col] - '0';
}*/

// Demander une configuration OPTIMALE (ligne par ligne)
void askConfiguration(int t[MAX_SIZE][MAX_SIZE])
{
    string config;
    int row = 0;

    cout <<
        "Entrez la configuration de la vie ligne par ligne (20 lignes, chaque ligne de 20 caractères, 1 pour vivant, 0 pour mort):"
        << endl;

    while (row < MAX_SIZE)
    {
        cout << "Ligne " << row + 1 << ": ";
        cin >> config;

        config.erase(remove(config.begin(), config.end(), ' '), config.end());

        // Vérifier que la ligne a la bonne taille
        if (config.size() != MAX_SIZE)
        {
            cout << "Erreur: chaque ligne doit contenir exactement " << MAX_SIZE << " caractères." << endl;
            continue;
        }

        // Remplir la ligne du tableau avec les valeurs de la configuration
        for (int col = 0; col < MAX_SIZE; col++)
        {
            if (config[col] == '1')
                t[row][col] = ALIVE;
            else if (config[col] == '0')
                t[row][col] = DEAD;
            else
            {
                cout << "Erreur: La configuration doit uniquement contenir '1' ou '0'." << endl;
                return;
            }
        }

        row++;
    }
}

// Crée une configuration aléatoire de la vie.
void randomConfiguration(int t[MAX_SIZE][MAX_SIZE])
{
    srand(static_cast<unsigned>(time(nullptr)));

    for (int row = 0; row < MAX_SIZE; row++)
    {
        for (int col = 0; col < MAX_SIZE; col++)
        {
            t[row][col] = rand() % 2;
        }
    }
}

// Affiche le plateau.
void display(int t[MAX_SIZE][MAX_SIZE])
{
    for (int row = 0; row < MAX_SIZE; row++)
    {
        for (int col = 0; col < MAX_SIZE; col++)
        {
            mvprintw(row + 3, col * 2, t[row][col] == ALIVE ? "O" : ". "); // mvprintw(row, col, message)
        }
    }
}

// Compte le nombre de voisins vivants d'une cellule.
int countNeighbors(int row, int col, int t[MAX_SIZE][MAX_SIZE])
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) // On ne compte pas la cellule elle-même
                continue;
            int newRow = (row + i + MAX_SIZE) % MAX_SIZE;
            int newCol = (col + j + MAX_SIZE) % MAX_SIZE;
            if (t[newRow][newCol] != DEAD)
                count++;
        }
    }
    return count;
}

// Compter le nombre de cellules vivantes.
int countAlive(int t[MAX_SIZE][MAX_SIZE])
{
    int count = 0;

    for (int row = 0; row < MAX_SIZE; row++)
        for (int col = 0; col < MAX_SIZE; col++)
            if (t[row][col] == ALIVE)
                count++;

    return count;
}

// Remplace le plateau source par le plateau destination.
void replace(int src[MAX_SIZE][MAX_SIZE], int dest[MAX_SIZE][MAX_SIZE])
{
    for (int row = 0; row < MAX_SIZE; row++)
        for (int col = 0; col < MAX_SIZE; col++)
            dest[row][col] = src[row][col];
}

// Evolution de l'état d'une cellule
void evolution(int t[MAX_SIZE][MAX_SIZE], int temp[MAX_SIZE][MAX_SIZE])
{
    for (int row = 0; row < MAX_SIZE; row++)
    {
        for (int col = 0; col < MAX_SIZE; col++)
        {
            int neighbors = countNeighbors(row, col, t);

            // Une cellule morte devient vivante, si trois de ses cellules voisines sont vivantes.
            if (t[row][col] == DEAD && neighbors == 3)
                temp[row][col] = ALIVE;
            else
            {
                // Une cellule vivante le reste, si deux ou trois de ses cellules voisines sont aussi vivantes.
                if (t[row][col] == ALIVE && (neighbors == 2 || neighbors == 3))
                    temp[row][col] = ALIVE;
                else
                    temp[row][col] = DEAD;
            }
        }
    }

    replace(temp, t);
}

int main()
{
    // Définir les variables d'environnement en fonction de MAX_SIZE pour la bibliothèque ncurses
    string lines = std::to_string(MAX_SIZE + 5);
    string columns = std::to_string(MAX_SIZE * 2 + 10);

    _putenv_s("LINES", lines.c_str());
    _putenv_s("COLUMNS", columns.c_str());

    int state[MAX_SIZE][MAX_SIZE];
    int temp[MAX_SIZE][MAX_SIZE];

    initialisation(state);

    cout << "Configuration aléatoire (1) ou manuelle (2) ?" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        randomConfiguration(state);
    }
    else
    {
        askConfiguration(state);
    }

    initscr(); // Initialise ncurses
    noecho(); // Désactive l'écho des touches
    cbreak(); // Désactive la mise en mémoire tampon des touches
    nodelay(stdscr, TRUE); // Empêcher getch de bloquer

    int generation = 0;

    while (true)
    {
        clear();
        mvprintw(0, 0, "----------------------------------------");
        mvprintw(1, 0, "Conway's Game of Life (Generation: %d Cell alive: %d)", generation, countAlive(state));
        mvprintw(2, 0, "----------------------------------------");
        display(state);
        evolution(state, temp);
        mvprintw(MAX_SIZE + 3, 0, "----------------------------------------");
        refresh();
        this_thread::sleep_for(chrono::milliseconds(100));
        generation++;

        if (getch() == 'q')
            break;
    }

    endwin();
    return 0;
}
