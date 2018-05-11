#ifndef VOITURE_H
#define VOITURE_H

#include <QProcess>
#include <QColor>

class Car
{
public:
    QString name;
    QList<int> positionsX;
    QList<int> positionsY;
    QList<int> boostUsage;
    int velX;
    int velY;
    int nbMoves;
    int nbFailures;
    int boosts;
    int position;
    int finishPosition;
    QColor color;
    // Pour la gestion du carburant
    int gasoline;
    bool debug;
    // pointeur Ã  cause de QtVector
    QProcess* driver;


    Car();
    ~Car();

    void reset(int x, int y, int boosts, int position, QColor color);
    void fillTank(int value);
    bool isOutOfGas() const;
    void useGasoline(int value);
};


#endif
