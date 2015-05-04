#ifndef OCTREE_H
#define OCTREE_H

/* �ENSG 2015
 * �cole nationale des sciences g�ographiques
 * 6-8 avenue Blaise Pascal
 * Cit� Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALL�E CEDEX 2
 * FRANCE */

/* Ce Point d�finit la classe Octree */

#include "../include/Arbre.h"
#include "NoeudOctree.h"
#include "Point.h"

typedef struct  // on d�clare ici une structure pour stocker le volume englobant
{
    Point           centre;         // Centre du volume englobant
    double          rayon;         // Rayon du volume eglobant
} Bounds;



class Octree : public Arbre<NoeudOctree>  // Cr�ation d'une classe Octree qui h�rite de la classe Arbre
{

public:

    // fonction de rappel pour la cr�ation des Points

    typedef bool            (*callback)(const Octree &o, void *data);

   // constructeur

    Octree();

    // destructeur
    virtual ~Octree();
    // m�thode permettant de construire l'octree

    virtual const   bool            construire(Point **points, // on r�cup�re la liste des points
                                               const unsigned int count,   // nombre total de points
                                               const unsigned int threshold, // seuil d'arr�t
                                               const unsigned int maximumDepth, // profondeur de l'arbre
                                               const Bounds &bounds,            // volume englobant
                                               const unsigned int currentDepth = 0); // profondeur courante

    // m�thode permettant de construire le volume englobant

    static  const   Bounds          calcCubicBounds(const Point * const * points,  // correspond  liste dans la classe Point
                                                    const unsigned int count);

    // d�finition de la fonction qui sera rappel�e pour la cr�ation des Points

    virtual const   bool            traverse(callback proc, void *data) const;

    // fonction de requ�te

    QVector<Point> requete(const Point &centre, double distance) const; // voisinage
    QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel

protected:

    Octree                  *m_enfant[8]; // tableau du nombre d'octant
    unsigned int            m_pointCount; // nombre de points
    Point                   **m_points;
    Point                   m_centre;
    double                 m_rayon;
private:
};

#endif // OCTREE_H
