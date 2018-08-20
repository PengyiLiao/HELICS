/*
Copyright © 2017-2018,
Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC
All rights reserved. See LICENSE file and DISCLAIMER for more details.
*/

/** @file
@brief The C-API function for valueFederates
*/
#ifndef HELICS_APISHARED_VALUE_FEDERATE_FUNCTIONS_H_
#define HELICS_APISHARED_VALUE_FEDERATE_FUNCTIONS_H_

#include "helics.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sub/pub registration */

/** a sequence of characters*/
#define HELICS_DATA_TYPE_STRING 0
/** a double precision floating point number*/
#define HELICS_DATA_TYPE_DOUBLE 1
/** a 64 bit integer*/
#define HELICS_DATA_TYPE_INT 2
/** a pair of doubles representing a complex number*/
#define HELICS_DATA_TYPE_COMPLEX 3
/** an array of doubles*/
#define HELICS_DATA_TYPE_VECTOR 4
/** a named point consisting of a string and a double*/
#define HELICS_DATA_TYPE_NAMEDPOINT 6

/** a boolean data type*/
#define HELICS_DATA_TYPE_BOOLEAN 7
/** raw data type*/
#define HELICS_DATA_TYPE_RAW 25

/** create a subscription
@details the subscription becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a subscription must have been create with helicsCreateValueFederate or
helicsCreateCombinationFederate
@param key the identifier matching a publication to get a subscription for
@param units a string listing the units of the subscription maybe NULL
@return an object containing the subscription
*/
HELICS_EXPORT helics_input helicsFederateRegisterSubscription (helics_federate fed,
                                                                      const char *key,                                                          
                                                                      const char *units, helics_error *err);


/** register a publication with a a known type
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication the global publication key will be prepended with the federate name
@param type a known type identifier  HELICS_DATA_TYPE_STRING, HELICS_DATA_TYPE_INT, HELICS_DATA_TYPE_DOUBLE,
HELICS_DATA_TYPE_COMPLEX, HELICS_DATA_TYPE_VECTOR, HELICS_DATA_TYPE_NAMEDPOINT, HELICS_DATA_TYPE_BOOLEAN,
HELICS_DATA_TYPE_RAW
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_publication helicsFederateRegisterPublication (helics_federate fed,
                                                                    const char *key,
                                                                    int type, const char *units, helics_error *err);

/** register a publication with a defined type
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication
@param type a code identifying the type of the publication one of HELICS_DATA_TYPE_STRING, HELICS_DATA_TYPE_INT, HELICS_DATA_TYPE_DOUBLE, HELICS_DATA_TYPE_COMPLEX,
HELICS_DATA_TYPE_VECTOR, HELICS_DATA_TYPE_NAMEDPOINT, HELICS_DATA_TYPE_BOOLEAN HELICS_DATA_TYPE_RAW
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_publication
helicsFederateRegisterTypePublication (helics_federate fed, const char *key, const char *type, const char *units, helics_error *err);

/** register a global named publication with an arbitrary type
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication
@param type a string describing the expected type of the publication
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_publication helicsFederateRegisterGlobalPublication (helics_federate fed,
                                                                          const char *key,
                                                                          int type, const char *units, helics_error *err);

/** register a global publication with a defined type
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication
@param type a code identifying the type of the publication one of HELICS_DATA_TYPE_STRING, HELICS_DATA_TYPE_INT, HELICS_DATA_TYPE_DOUBLE, HELICS_DATA_TYPE_COMPLEX,
HELICS_DATA_TYPE_VECTOR, HELICS_DATA_TYPE_NAMEDPOINT, HELICS_DATA_TYPE_BOOLEAN HELICS_DATA_TYPE_RAW
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_publication helicsFederateRegisterGlobalTypePublication (helics_federate fed,
                                                                              const char *key,
                                                                              const char *type, const char *units, helics_error *err);

/** register a named input
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication the global publication key will be prepended with the federate name
@param type a string describing the expected type of the publication
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_input helicsFederateRegisterInput(helics_federate fed,
    const char *name, const char *units, helics_error *err);

/** register a publication with a defined type
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication
@param type a code identifying the type of the publication one of HELICS_DATA_TYPE_STRING, HELICS_DATA_TYPE_INT, HELICS_DATA_TYPE_DOUBLE, HELICS_DATA_TYPE_COMPLEX,
HELICS_DATA_TYPE_VECTOR, HELICS_DATA_TYPE_NAMEDPOINT, HELICS_DATA_TYPE_BOOLEAN HELICS_DATA_TYPE_RAW
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_input
helicsFederateRegisterTypeInput (helics_federate fed, const char *key, const char *type, const char *units, helics_error *err);

/** register a global named input
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_publication helicsFederateRegisterGlobalInput(helics_federate fed,
    const char *key,
                                                                    const char *units,
                                                                    helics_error *err);

/** register a global publication with an arbitrary type
@details the publication becomes part of the federate and is destroyed when the federate is freed so there are no separate free functions
for subscriptions and publications
@param fed the federate object in which to create a publication
@param key the identifier for the publication
@param type a code identifying the type of the publication one of HELICS_DATA_TYPE_STRING, HELICS_DATA_TYPE_INT, HELICS_DATA_TYPE_DOUBLE, HELICS_DATA_TYPE_COMPLEX,
HELICS_DATA_TYPE_VECTOR, HELICS_DATA_TYPE_NAMEDPOINT, HELICS_DATA_TYPE_BOOLEAN HELICS_DATA_TYPE_RAW
@param units a string listing the units of the subscription maybe NULL
@return an object containing the publication
*/
HELICS_EXPORT helics_publication helicsFederateRegisterGlobalTypeInput(helics_federate fed,
    const char *key,
    const char *type, const char *units, helics_error *err);

/**
* \defgroup publications Publication functions
@details functions for publishing data of various kinds
The data will get translated to the type specified when the publication was constructed automatically
regardless of the function used to publish the data
* @{
*/

/** publish raw data from a char * and length
@param pub the publication to publish for
@param data a pointer to the raw data
@param len the size in bytes of the data to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishRaw (helics_publication pub, const void *data, int inputDataLength, helics_error *err);

/** publish a string
@param pub the publication to publish for
@param str a pointer to a NULL terminated string
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishString (helics_publication pub, const char *str, helics_error *err);

/** publish an integer value
@param pub the publication to publish for
@param val the numerical value to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishInteger (helics_publication pub, int64_t val, helics_error *err);

/** publish a Boolean Value
@param pub the publication to publish for
@param val the boolean value to publish either helics_true or helics_false
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishBoolean (helics_publication pub, helics_bool_t val, helics_error *err);

/** publish a double floating point value
@param pub the publication to publish for
@param val the numerical value to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishDouble (helics_publication pub, double val, helics_error *err);

/** publish a complex value (or pair of values)
@param pub the publication to publish for
@param real the real part of a complex number to publish
@param imag the imaginary part of a complex number to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishComplex (helics_publication pub, double real, double imag, helics_error *err);

/** publish a vector of doubles
@param pub the publication to publish for
@param data a pointer to an array of double data
@param len the number of points to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishVector (helics_publication pub, const double *vectorInput, int vectorlength, helics_error *err);

/** publish a named point
@param pub the publication to publish for
@param str a pointer a null terminated string
@param val a double val to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationPublishNamedPoint (helics_publication pub, const char *str, double val, helics_error *err);

/** add a named input to the list of targets a publication publishes to
@param pub the publication to add the target for
@param target the name of an input that the data should be sent to
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsPublicationAddTarget (helics_publication pub, const char *target, helics_error *err);

/** add a publication to the list of data that an input subscribes to
@param ipt the named input to modify
@param target the name of a publication that an input should subscribe to
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputAddTarget (helics_input ipt, const char *target, helics_error *err);

/**@}*/

/**
* \defgroup getValue GetValue functions
@details data can be returned in number of formats,  for instance if data is published as a double it can be returned as a string
and vice versa,  not all translations make that much sense but they do work.
* @{
*/
/** get the size of the raw value for subscription
@returns the size of the raw data/string in bytes
*/
HELICS_EXPORT int helicsInputGetRawValueSize (helics_input ipt, helics_error *err);

/** get the raw data for the latest value of a subscription
@param ipt the input to get the data for
@param[out] data the memory location of the data
@param maxlen the maximum size of information that data can hold
@param[out] actualLength  the actual length of data copied to data
@return a void value, helics_ok if everything went fine
*/
HELICS_EXPORT int helicsInputGetRawValue (helics_input ipt, void *data, int maxlen, helics_error *err);

/** get the size of a value for subscription assuming return as a string
@returns the size of the string
*/
HELICS_EXPORT int helicsInputGetStringSize (helics_input ipt, helics_error *err);

/** get a string value from a subscription
@param ipt the input to get the data for
@param[out] str storage for copying a null terminated string
@param maxlen the maximum size of information that str can hold
@param[out] the actual length of the string
@return a void value, helics_ok if everything went fine
*/
HELICS_EXPORT int helicsInputGetString (helics_input ipt, char *outputString, int maxStringlen, helics_error *err);

/** get an integer value from a subscription
@param ipt the input to get the data for
@param[out] val memory location to place the value
@return a void value, helics_ok if everything went fine
*/
HELICS_EXPORT int64_t helicsInputGetInteger (helics_input ipt, helics_error *err);

/** get a boolean value from a subscription
@param ipt the input to get the data for
@param[out] val memory location to place the value
@return a void value, helics_ok if everything went fine
*/
HELICS_EXPORT helics_bool_t helicsInputGetBoolean (helics_input ipt, helics_error *err);

/** get a double value from a subscription
@param ipt the input to get the data for
@param[out] val memory location to place the value
@return a void value, helics_ok if everything went fine
*/
HELICS_EXPORT double helicsInputGetDouble (helics_input ipt, helics_error *err);

/** get a pair of double forming a complex number from a subscriptions
@param ipt the input to get the data for
@param[out] real memory location to place the real part of a value
@param[out] imag memory location to place the imaginary part of a value
@return a void value, helics_ok if everything went fine
*/
HELICS_EXPORT void helicsInputGetComplex (helics_input ipt, double *real, double *imag, helics_error *err);

/** get the size of a value for subscription assuming return as an array of doubles
@returns the number of double in a return vector
*/
HELICS_EXPORT int helicsInputGetVectorSize (helics_input ipt, helics_error *err);

/** get a vector from a subscription
@param ipt the input to get the result for
@param[out] data the location to store the data
@param maxlen the maximum size of the vector
@param[out] actualSize pointer to variable to store the actual size
*/
HELICS_EXPORT int helicsInputGetVector (helics_input ipt, double data[], int maxlen, helics_error *err);


/** get a named point from a subscription
@param ipt the input to get the result for
@param[out] str storage for copying a null terminated string
@param maxlen the maximum size of information that str can hold
@param[out] the actual length of the string
@param[out] val the double value for the named point
*/
HELICS_EXPORT int
helicsInputGetNamedPoint (helics_input ipt, char *outputString, int maxlen, double *val, helics_error *err);

/**@}*/

/**
* \defgroup default_values Default Value functions
@details these functions set the default value for a subscription. That is the value returned if nothing was published from elsewhere
* @{
*/

/** set the default as a raw data array
@param ipt the input to set the default for
@param data a pointer to the raw data to use for the default
@param len the size of the raw data
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultRaw (helics_input ipt, const void *data, int inputDataLength, helics_error *err);

/** set the default as a string
@param ipt the input to set the default for
@param str a pointer to the default string
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultString (helics_input ipt, const char *str, helics_error *err);

/** set the default as an integer
@param ipt the input to set the default for
@param val the default integer
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultInteger (helics_input ipt, int64_t val, helics_error *err);

/** set the default as a boolean
@param ipt the input to set the default for
@param val the default boolean value
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultBoolean (helics_input ipt, helics_bool_t val, helics_error *err);

/** set the default as a double
@param ipt the input to set the default for
@param val the default double value
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultDouble (helics_input ipt, double val, helics_error *err);

/** set the default as a complex number
@param ipt the input to set the default for
@param real the default real value
@param imag the default imaginary value
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultComplex (helics_input ipt, double real, double imag, helics_error *err);

/** set the default as a vector of doubles
@param ipt the input to set the default for
@param data a pointer to an array of double data
@param len the number of points to publish
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultVector (helics_input ipt, const double *vectorInput, int vectorlength, helics_error *err);


/** set the default as a named_point
@param ipt the input to set the default for
@param str a pointer to a string representing the name
@param val a double value for the value of the named point
@return helics_ok if everything was OK
*/
HELICS_EXPORT void helicsInputSetDefaultNamedPoint (helics_input ipt, const char *str, double val, helics_error *err);


/**@}*/

/**
 * \defgroup information retrieval
 * @{
 */

/** get the type of an input
@param ipt the input to query
@param[out] outputString a pointer to a memory location to store the resulting string
@param maxlen the maximum size of string that str can store
@return a void enumeration, helics_ok if everything worked*/
HELICS_EXPORT int helicsInputGetType (helics_input ipt, char *outputString, int maxlen, helics_error *err);

/** get the type of a publication
@param pub the publication to query
@param[out] outputString a pointer to a memory location to store the resulting string
@param maxlen the maximum size of string that str can store
@return a void enumeration, helics_ok if everything worked*/
HELICS_EXPORT int helicsPublicationGetType (helics_publication pub, char *outputString, int maxlen, helics_error *err);

/** get the key of a subscription
@param ipt the input to query
@param[out] outputString a pointer to a memory location to store the resulting string
@param maxlen the maximum size of string that str can store
@return a void enumeration, helics_ok if everything worked*/
HELICS_EXPORT int helicsInputGetKey (helics_input ipt, char *outputString, int maxlen, helics_error *err);

/** get the key of a publication
@details this will be the global key used to identify the publication to the federation
@param pub the publication to query
@param[out] outputString a pointer to a memory location to store the resulting string
@param maxlen the maximum size of string that str can store
@return a void enumeration, helics_ok if everything worked*/
HELICS_EXPORT int helicsPublicationGetKey (helics_publication pub, char *outputString, int maxlen, helics_error *err);

/** get the units of an input
@param ipt the input to query
@param[out] outputString a pointer to a memory location to store the resulting string
@param maxlen the maximum size of string that str can store
@return a void enumeration, helics_ok if everything worked*/
HELICS_EXPORT int helicsInputGetUnits (helics_input ipt, char *outputString, int maxlen, helics_error *err);

/** get the units of a publication
@param pub the publication to query
@param[out] outputString a pointer to a memory location to store the resulting string
@param maxlen the maximum size of string that str can store
@return a void enumeration, helics_ok if everything worked*/
HELICS_EXPORT int helicsPublicationGetUnits (helics_publication pub, char *outputString, int maxlen, helics_error *err);

/**@}*/

/** check if a particular subscription was updated
@return true if it has been updated since the last value retrieval*/
HELICS_EXPORT helics_bool_t helicsInputIsUpdated (helics_input ipt, helics_error *err);
/** get the last time a subscription was updated */
HELICS_EXPORT helics_time_t helicsInputLastUpdateTime (helics_input ipt, helics_error *err);
/** get the number of publications in a federate
@return (-1) if fed was not a valid federate otherwise returns the number of publications*/
HELICS_EXPORT int helicsFederateGetPublicationCount (helics_federate fed, helics_error *err);

/** get the number of subscriptions in a federate
@return (-1) if fed was not a valid federate otherwise returns the number of subscriptions*/
HELICS_EXPORT int helicsFederateGetInputCount (helics_federate fed, helics_error *err);

#ifdef __cplusplus
} /* end of extern "C" { */
#endif

#endif /* HELICS_APISHARED_VALUE_FEDERATE_FUNCTIONS_H_*/
