#include "stats.h"

/**
 * @brief Stats
 *
 * Constructor por defecto
 *
 */
Stats::Stats(Vector *v)
{
    if(v->size() > 0)
    {
        this->media = Media(v);
        this->varianza = Varianza(v);
        this->covarianza = Covarianza(v,v,this->media, this->media);
        this->maxNumber = maximo(v);
        this->minNumber = minimo(v);
        this->sumaCuadrados = sumaDeCuadrados(v);
    }

}

/**
 * @brief Media: Calcula la media de un vector de datos
 *
 * Calcula la media a partir de un vector pasado como parametro.
 *
 * @param v vector al cual se le calcula la media.
 *
 * @return valor con la media del vector pasado como parametro.
 */
float Stats::Media(Vector *v)
{
    accumulator_set<double, stats<tag::mean> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return mean(acc);
}

/**
 * @brief Varianza: Calcula la varianza
 *
 * A partir del vector pasado como parametro calcula la varianza.
 *
 * @param v vector al cual se la calcula el valor de varianza.
 *
 * @return varianza del vector.
 */
float Stats::Varianza(Vector *v)
{
    accumulator_set<double, features<tag::variance> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return variance(acc);
}

/**
 * @brief Covarianza: Calcula la covarianza
 *
 * Calcula la covarianza del vector, es decir cuan distinta es una variable
 * de otra.
 *
 * @param v vector al cual le calcula la covarianza
 * @return
 */
float Stats::Covarianza(Vector *v1, Vector *v2, float mediav1, float mediav2)
{
    float cov = 0;
    for(int i = 0; i < v1->size(); i++)
    {
        cov += (*v1->find(i)-mediav1)*(*v2->find(i)-mediav2);
    }
    cov /=(v1->size()-1);
    return (cov);
}

/**
 * @brief minimo: Obtiene el minimo valor del vector.
 *
 * @param v
 *
 * @return
 */
float Stats::minimo(Vector *v)
{
    accumulator_set<double, features<tag::min> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return min(acc);
}

/**
 * @brief maximo: Obtienen el maximo valor del vector.
 * @param v
 * @return
 */
float Stats::maximo(Vector *v)
{
    accumulator_set<double, features<tag::max> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return max(acc);
}

/**
 * @brief sumaDeCuadrados: calcula la suma de cuadrados del vector
 * @param v
 * @return
 */
float Stats::sumaDeCuadrados(Vector *v)
{
    return std::inner_product(v->begin(),v->end(), v->begin(),0.0);
}

/**
 * @brief getMedia
 * @return
 */
float Stats::getMedia() const
{
    return media;
}

/**
 * @brief getVarianza
 * @return
 */
float Stats::getVarianza() const
{
    return varianza;
}

/**
 * @brief getCovarianza
 * @return
 */
float Stats::getCovarianza() const
{
    return covarianza;
}

/**
 * @brief getMinNumber
 * @return
 */
float Stats::getMinNumber() const
{
    return minNumber;
}

/**
 * @brief getMaxNumber
 * @return
 */
float Stats::getMaxNumber() const
{
    return maxNumber;
}

/**
 * @brief getSumaCuadrados
 * @return
 */
float Stats::getSumaCuadrados() const
{
    return sumaCuadrados;
}
