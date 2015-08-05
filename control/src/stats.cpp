#include "stats.h"

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

float Stats::Media(Vector *v)
{
    accumulator_set<double, stats<tag::mean> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return mean(acc);
}

float Stats::Varianza(Vector *v)
{
    accumulator_set<double, features<tag::variance> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return variance(acc);
}

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

float Stats::minimo(Vector *v)
{
    accumulator_set<double, features<tag::min> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return min(acc);
}

float Stats::maximo(Vector *v)
{
    accumulator_set<double, features<tag::max> > acc;

    acc = for_each(v->begin(), v->end(), acc);

    return max(acc);
}

float Stats::sumaDeCuadrados(Vector *v)
{
    return std::inner_product(v->begin(),v->end(), v->begin(),0.0);
}

float Stats::getMedia() const
{
    return media;
}

float Stats::getVarianza() const
{
    return varianza;
}

float Stats::getCovarianza() const
{
    return covarianza;
}

float Stats::getMinNumber() const
{
    return minNumber;
}

float Stats::getMaxNumber() const
{
    return maxNumber;
}

float Stats::getSumaCuadrados() const
{
    return sumaCuadrados;
}
