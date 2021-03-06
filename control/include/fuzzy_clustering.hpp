#ifndef FUZZY_CLUSTERING
#define FUZZY_CLUSTERING 1
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <stdlib.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace Clustering{

typedef double Value;
typedef unsigned int Index;
typedef boost::numeric::ublas::vector<Value> Vector;
typedef boost::numeric::ublas::zero_vector<Value> ZeroVector;
typedef boost::numeric::ublas::matrix<Value> Matrix;
typedef boost::numeric::ublas::zero_matrix<Value> ZeroMatrix;

class Fuzzy{
public:
    //
    // Notation
    //
    //   i  -> is used for point
    //   j  -> is used for cluster
    //   f  -> is used for dimension (feature)
    //
    Fuzzy(Matrix& rows, Index number_clusters,
          Value fuzziness = 1.3, Value epsilon=0.0001):
        m_(fuzziness), // fuzzyness
        epsilon_(epsilon), // epsilon
        number_clusters_(number_clusters), // number clusters
        number_points_(rows.size1()), // number points
        size_of_a_point_(rows.size2()), // dimension of a point
        p_centroids_(new Matrix(number_clusters, size_of_a_point_)), // we have num_clusters centroids
        //                      number_clusters X rows.size2()
        // each row is member of a cluster to some extent
        p_membership_(new Matrix(number_clusters_, number_points_)),
        //                       number_clusters X rows.size1()
        // each row is member of a cluster to some extent
        p_new_membership_(new Matrix(number_clusters_, number_points_)),
        //                       number_clusters X rows.size1()
        // preserve the dataset
        rows_(rows)
    {
        // random membership for each row
        /* Step 6 */
        double normalization_factor;

        for (Index i = 0 ; i < number_points_; i++){
            normalization_factor = 0.0;
            for (Index j = 0; j < number_clusters; j++)
                normalization_factor +=
                        (*p_membership_)(j, i) = (rand() / (RAND_MAX + 0.0));

            for (Index j = 0; j < number_clusters; j++)
                (*p_membership_)(j, i) /= normalization_factor;
        }
        //std::cout << "Fuzzy membership (n_clusters X n_points)" << std::endl
        //        << " " << (*p_membership_) << std::endl;

        computeCentroids();
    };

    void computeCentroids();

    void computeCentroids2();

    bool updateMembership();

    void clusterClassification(Matrix *ks, int cluster);

    inline bool can_stop()
    {
        Value t = norm_1( (*p_membership_)-(*p_new_membership_) );
        //std::cout << " norm t = " << t << std::endl;
        return  t < epsilon_;
    }

    inline void clustering(unsigned int num_iteration=300){
        unsigned int iteration = 0;
        while (!updateMembership() && iteration++ < num_iteration){
            computeCentroids2();
        }

        std::cout << "Centroids (n_clusters X dim_point)"
                  <<std::endl << " " << (*p_centroids_) << std::endl;

        FPI();
        NCE();
    }



private:

    Value m_;                // fuzzyness
    Value epsilon_;                 // epsilon convergence

    Index number_clusters_;         // number clusters
    Index number_points_;           // number points in dataset
    Index size_of_a_point_;         // size of a single point

    Matrix * p_centroids_;          // centroids
    Matrix * p_membership_;         // membership
    Matrix * p_new_membership_;      // new membership
    Matrix& rows_;                  // dataset

    double FPI();

    double NCE();    

};
};
#endif

////

