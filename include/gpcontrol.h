#ifndef GPCONTROL_H
#define GPCONTROL_H

#include <QObject>
#include <QPair>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QTimer>


#include "car.h"

enum NextCarMode {
    RANDOM,
    DETERMINIST,
    SEQUENTIAL
};


/** @brief Structure pour le position d'un élément sur la map avec des coordonnées entières
 */
typedef struct {
	int x;
	int y;
} pos2Dint;

/** @brief Structure pour une position 2D avec des coordonnées floattantes
 */
typedef struct {
	float x;
	float y;
} pos2Dfloat;

/** @brief Structure permettant de définir un segment et de ce déplacer le long
 */
typedef struct {
	pos2Dint posStart; /*< Début du segment */
	pos2Dint posEnd; /*< Fin du segment */
	pos2Dfloat posActual; /*< Position Actuel sur le segment */
	pos2Dfloat delta; /*< Variation en x et en y pour le déplacement */
	int len; /*< Longueur suivant l'axe principale */
	int pos; /*< Position de référence sur la ligne */
} infoLine;

/** @brief Définition d'un segment entre deux points
  */
void line(int x1, int y1, int x2, int y2, infoLine* data);

/** @brief Déplacement sur un segment dans un sens donné (+1 vers la fin, et -1 vers le début)
  */
int nextPoint(infoLine* data, pos2Dint* point, int sens);

class GPControl : public QObject
{
    Q_OBJECT

public:
    explicit GPControl(QObject *parent = 0);
    ~GPControl();

    enum Tile {
        OUT    = 0,
        NORMAL = 1,
        SAND   = 2,
        START1 = 3,
        START2 = 4,
        START3 = 5,
        GOAL   = 6
    };

    enum TileChar {
        OUT_CHAR    = '.',
        NORMAL_CHAR = '#',
        SAND_CHAR   = '~',
        START1_CHAR = '1',
        START2_CHAR = '2',
        START3_CHAR = '3',
        GOAL_CHAR   = '='
    };

    enum FollowMode {
      FollowAll,
      FollowCar1,
      FollowCar2,
      FollowCar3
    };

private:
    QVector<GPControl::Tile> tiles;
    QVector<Car> cars;

    QTimer timer;

    NextCarMode nextCarMode;
    int sizeX;
    int sizeY;
    int nbCars;
    int currentCarIndex;
    static const int nbrMaxBoost = 5; /* Valeur par défaut dans le cas de la gestion du carburant */
    int delay;
    int carburantAuDepart;
    void nextCar();

    int finishPosition;


signals:
    void carMoved();
    void carMovedWithBoost();
    void driverTimeout();
    void invalidMove();
    void syntaxError();
    void end(QString res);

public:

    bool setMap(const QString &mapPath);
    int getSizeX();
    int getSizeY();
    int getNbCars();
    int getPosCarX(int noCar);
    int getPosCarY(int noCar);
    int getCarburant(int noCar);
    int getVelCarX(int noCar);
    int getVelCarY(int noCar);
    int getOldPosCarX(int noCar, int numPos);
    int getOldPosCarY(int noCar, int numPos);
    int getBoost(int noCar);
    int getNbBoostUsed(int noCar);
    int getIndexBoostUsed(int noCar, int numBoost);
    int getNbMoves(int noCar);
    int getNbFailures(int noCar);
    int getNbPositions(int noCar);
    int getPosDepart(int noCar);
    QColor getColor(int noCar);
    void setCarDebug(int car, bool debug);
    bool getCarDebug(int car);
    QString getDriverName(int noCar);

    void setNextCarMode(NextCarMode mode);
    GPControl::Tile getTile(int x, int y);
    char getTileChar(int x, int y);
    int getCurrentCar();
    void setDriverPath(int noCar, const QString &driverPath);
    QByteArray mapData();
    QByteArray positionsData();

    int gasolineAtStart() const;
    int gasolineConsumption(int accX, int accY, int velX, int velY);
    void moveCurrentCar(int accX, int accY);
    QSet< QPair<int, int> > availableMoves(int noCar);
    bool isFree(int x, int y);
    void setDelay(int value);
    bool isEnd();
    QString results();
    bool noCollision(int noCar, int accX, int accY);

public slots:
    void nextMove();
private slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void timeout();
};

#endif // GPCONTROL_H
