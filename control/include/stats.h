#ifndef STATS_H
#define STATS_H
#include "fuzzy_clustering.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/covariance.hpp>
#include <boost/accumulators/statistics/variates/covariate.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <stdlib.h>
#include <iostream>
/*
typedef double Value;
typedef unsigned int Index;
typedef boost::numeric::ublas::vector<Value> Vector;
typedef boost::numeric::ublas::zero_vector<Value> ZeroVector;
typedef boost::numeric::ublas::matrix<Value> Matrix;
typedef boost::numeric::ublas::zero_matrix<Value> ZeroMatrix;
*/

using namespace Clustering;
using namespace boost::accumulators;

/**
 * @brief Contiene metodos estadisticos.
 *
 * Contiene metodos estaticos los cuales sirven para calcular estadisticas de un
 * determinado vector de datos el cual se le pasa como parametro a la mayoria de
 * los metodos.
 *
 */
class Stats
{
public:

    Stats(Vector *v);

    static float Media(Vector* v);
    static float Varianza(Vector* v);
    static float Covarianza(Vector* v1, Vector *v2);
    static float minimo(Vector* v);
    static float maximo(Vector *v);
    static float sumaDeCuadrados(Vector *v);
    static float desviacionEstandar(Vector *v);

    float getMedia() const;
    float getDesviacionEstandar() const;
    float getVarianza() const;
    float getCovarianza() const;
    float getMinNumber() const;
    float getMaxNumber() const;
    float getSumaCuadrados() const;

private:

    float media; /*<*/
    float desviacionStd; /*<*/
    float varianza; /*<*/
    float covarianza; /*<*/
    float minNumber; /*<*/
    float maxNumber; /*<*/
    float sumaCuadrados; /*<*/
};

#endif // STATS_H
