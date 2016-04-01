#ifndef ZONELOOKUP_H
#define ZONELOOKUP_H

#include <vector>
#include "map/point.h"
#include "tools/nanoflann.h"

namespace MAP {

class Map;
class Zone;

///
/// \brief The ZoneLookUp class
/// Based on the design found between two neurons
///
class ZoneLookUp
{
public:

    template <typename T>
    struct PointCloud
    {
        typedef T coord_t; //!< The type of each coordinate

        struct LPoint
        {
            T  x,y;
            MAP::Zone   *zone;
        };

        std::vector<LPoint>  pts;
    };

    // And this is the "dataset to kd-tree" adaptor class:
    template <typename Derived>
    struct PointCloudAdaptor
    {
        typedef typename Derived::coord_t coord_t;

        const Derived &obj; //!< A const ref to the data set origin

        /// The constructor that sets the data set source
        PointCloudAdaptor(const Derived &obj_) : obj(obj_) { }

        /// CRTP helper method
        inline const Derived& derived() const { return obj; }

        // Must return the number of data points
        inline size_t kdtree_get_point_count() const { return derived().pts.size(); }

        // Returns the distance between the vector "p1[0:size-1]" and the data point with index "idx_p2" stored in the class:
        inline coord_t kdtree_distance(const coord_t *p1, const size_t idx_p2,size_t /*size*/) const
        {
            const coord_t d0=p1[0]-derived().pts[idx_p2].x;
            const coord_t d1=p1[1]-derived().pts[idx_p2].y;
            return d0*d0+d1*d1;
        }

        // Returns the dim'th component of the idx'th point in the class:
        // Since this is inlined and the "dim" argument is typically an immediate value, the
        //  "if/else's" are actually solved at compile time.
        inline coord_t kdtree_get_pt(const size_t idx, int dim) const
        {
            if (dim==0) return derived().pts[idx].x;
            else return derived().pts[idx].y;
        }

        // Optional bounding-box computation: return false to default to a standard bbox computation loop.
        //   Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again.
        //   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
        template <class BBOX>
        bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }

    }; // end of PointCloudAdaptor

    typedef PointCloudAdaptor<PointCloud<double> > PC2KD;

    typedef nanoflann::KDTreeSingleIndexAdaptor<
        nanoflann::L2_Simple_Adaptor<double, PC2KD > ,
        PC2KD,
        2 /* dim */
        > my_kd_tree_t;

    ZoneLookUp();
    ~ZoneLookUp();

    void    createCloud(MAP::Map & m);
    Zone *  getNearestZone(double x, double y);


private:

    PointCloud<double>  _cloud;
    const PC2KD         * _pc2kd;
    my_kd_tree_t        * _tree;
};

}

#endif // ZONELOOKUP_H
