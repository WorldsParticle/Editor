#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "tools.hpp"

// TODO
// - Changer dans le code certain nom de variable (conf, mod, ..)
// - utilisation des tr() pour faire classe (et choix pour la langue des variable, comm, ...)
// - suivre la norme et commenter en doxygen ou autre
// <!> passer les indexages en String vers du Int (id) <!>

class Model
{
public:
    enum LANDTYPE
    {
        PLAINE = 0,
        MONTAGNE,
        FORET,
        DESERT,
        PLAGE
    };

    enum CLIMATTYPE // Weather
    {
        PLUIE = 0,
        NEIGE,
        DEGAGE,
        BRUME
    };

    // représente une instance d'un Modèle 3D (attributs en absolu pour le moment)
    // il va falloir trouver un meilleur nom <<Blague censuré>> !
    struct Mod
    {
        String  name;
        String  path; // a voir si on stock les modèles par fichier ou dans une bdd
        void*   data; // si jamais on stock directement en mémoire (série de Vec3D ?)
        float   apparitionRate; // valeur relative.. a expliciter (/km, /objtot)
        Vec3D   scale;
        Vec3D   angle;
    };

    // contient toutes les propriétés necessaire à la génération d'un monde
    struct WorldConf
    {
        String              name;
        LANDTYPE            landtype;
        CLIMATTYPE          climattype;
        int                 windPower; // idem as apparitionRate
        Map<String, Mod *>  mods;
    };

    Model();
    ~Model();

    WorldConf*  createWorldConf(const String &name, WorldConf *clone = NULL); // clone pour plus tard (sinon constructeur par copie, plus propre)
    WorldConf*  getWorldConfByName(String &confName) const;

private:
    Map<String, WorldConf*> _WorldConfs;
};

#endif /* !__MODEL_HPP__ */
