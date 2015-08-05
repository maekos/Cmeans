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

    /**
     * @brief Stats
     *
     * Constructor por defecto
     *
     */
    Stats(Vector *v);

    /**
     * @brief Media: Calcula la media de un vector de datos
     *
     * Calcula la media a partir de un vector pasado como parametro.
     *
     * @param v vector al cual se le calcula la media.
     *
     * @return valor con la media del vector pasado como parametro.
     */
    static float Media(Vector* v);

    /**
     * @brief Varianza: Calcula la varianza
     *
     * A partir del vector pasado como parametro calcula la varianza.
     *
     * @param v vector al cual se la calcula el valor de varianza.
     *
     * @return varianza del vector.
     */
    static float Varianza(Vector* v);

    /**
     * @brief Covarianza: Calcula la covarianza
     *
     * Calcula la covarianza del vector, es decir cuan distinta es una variable
     * de otra.
     *
     * @param v vector al cual le calcula la covarianza
     * @return
     */
    static float Covarianza(Vector* v1, Vector *v2, float mediav1, float mediav2);

    /**
     * @brief minimo: Obtiene el minimo valor del vector.
     *
     * @param v
     *
     * @return
     */
    static float minimo(Vector* v);

    /**
     * @brief maximo: Obtienen el maximo valor del vector.
     * @param v
     * @return
     */
    static float maximo(Vector *v);

    /**
     * @brief sumaDeCuadrados: calcula la suma de cuadrados del vector
     * @param v
     * @return
     */
    static float sumaDeCuadrados(Vector *v);

    /**
     * @brief getMedia
     * @return
     */
    float getMedia() const;

    /**
     * @brief getVarianza
     * @return
     */
    float getVarianza() const;

    /**
     * @brief getCovarianza
     * @return
     */
    float getCovarianza() const;

    /**
     * @brief getMinNumber
     * @return
     */
    float getMinNumber() const;

    /**
     * @brief getMaxNumber
     * @return
     */
    float getMaxNumber() const;

    /**
     * @brief getSumaCuadrados
     * @return
     */
    float getSumaCuadrados() const;

private:

    float media; /*<*/

    float varianza; /*<*/

    float covarianza; /*<*/

    float minNumber; /*<*/

    float maxNumber; /*<*/

    float sumaCuadrados; /*<*/
};

#endif // STATS_H
