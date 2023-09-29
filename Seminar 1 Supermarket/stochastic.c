/*
 * Programa exemple del funcionament d'una simulacio orientada en events
 * basada en el codi donat en el llibre Jorba, Capitol 2
 * 
 * LLibreria de funcions estocastiques del sistema de cues
 * 
 * File:   stochastic.c
 * Author: Dolors Sala
 */

#include <math.h>

double drand48();

// Provides the next random value of an exponential distribution of mean m
float expo(float m){
    static double d = 0.0;

    //float alea1(long int *ap_llavor);
    d = drand48();
    return(-m*log(d));
}


