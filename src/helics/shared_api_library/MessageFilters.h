/*
Copyright © 2017-2018,
Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC
All rights reserved. See LICENSE file and DISCLAIMER for more details.
*/

/** @file
@brief functions related the message filters for the C api
*/

#ifndef HELICS_APISHARED_MESSAGE_FILTER_FEDERATE_FUNCTIONS_H_
#define HELICS_APISHARED_MESSAGE_FILTER_FEDERATE_FUNCTIONS_H_

#include "helics.h"

#ifdef __cplusplus
extern "C" {
#endif

/** create a source Filter on the specified federate
@details filters can be created through a federate or a core , linking through a federate allows
a few extra features of name matching to function on the federate interface but otherwise equivalent behavior
@param fed the fed to register through
@param type the type of filter to create
@param target the name of endpoint to target
@param name the name of the filter (can be NULL)
@return a helics_filter object
*/
HELICS_EXPORT helics_filter helicsFederateRegisterFilter (helics_federate fed,
                                                                helics_filter_type_t type,
                                                          const char *name,
                                                          helics_error *err);

/** create a cloning Filter on the specified federate
@details cloning filters copy a message and send it to multiple locations source and destination can be added
through other functions
@param fed the fed to register through
@param deliveryEndpoint the specified endpoint to deliver the message
@return a helics_filter object
*/
HELICS_EXPORT helics_filter helicsFederateRegisterCloningFilter (helics_federate fed, const char *deliveryEndpoint, helics_error *err);

/** create a source Filter on the specified core
@details filters can be created through a federate or a core , linking through a federate allows
a few extra features of name matching to function on the federate interface but otherwise equivalent behavior
@param core the core to register through
@param type the type of filter to create
@param target the name of endpoint to target
@param name the name of the filter (can be NULL)
@return a helics_filter object
*/
HELICS_EXPORT helics_filter helicsCoreRegisterFilter (helics_core core,
                                                            helics_filter_type_t type, const char *name, helics_error *err);

/** create a cloning Filter on the specified core
@details cloning filters copy a message and send it to multiple locations source and destination can be added
through other functions
@param core the core to register through
@param deliveryEndpoint the specified endpoint to deliver the message
@return a helics_filter object
*/
HELICS_EXPORT helics_filter helicsCoreRegisterCloningFilter (helics_core core, const char *deliveryEndpoint, helics_error *err);

/** get the target of the filter and store in the given string
@param filt the given filter
@param[out] outputString storage for the name of the target
@param maxlen the maximum length of string that str can store
@return a void enumeration helics_ok if everything worked*/
HELICS_EXPORT int helicsFilterGetTarget (helics_filter filt, char *outputString, int maxlen, helics_error *err);

/** get the name of the filter and store in the given string
@param filt the given filter
@param[out] outputString storage for the name of the target
@param maxlen the maximum length of string that str can store
@return a void enumeration helics_ok if everything worked*/
HELICS_EXPORT int helicsFilterGetName (helics_filter filt, char *outputString, int maxlen, helics_error *err);

/** set a property on a filter
@param filt the filter to modify
@param property a string containing the property to set
@param val a numerical value of the property
*/
HELICS_EXPORT void helicsFilterSet (helics_filter filt, const char *property, double val, helics_error *err);

/** set a string property on a filter
@param filt the filter to modify
@param property a string containing the property to set
@param val a string containing the new value
*/
HELICS_EXPORT void helicsFilterSetString (helics_filter filt, const char *property, const char *val, helics_error *err);

/**
* \defgroup clone filter functions
@details functions that manipulate cloning filters in some way
* @{
*/

/** add a destination target to a filter
@details all messages going to a destination are copied to the delivery address(es)*/
HELICS_EXPORT void helicsFilterAddDestinationTarget (helics_filter filt, const char *dest, helics_error *err);

/** add a source target to a filter
@details all messages coming from a source are copied to the delivery address(es)*/
HELICS_EXPORT void helicsFilterAddSourceTarget (helics_filter filt, const char *source, helics_error *err);

/** add a delivery endpoint to a cloning filter
@details all cloned messages are sent to the delivery address(es)
*/
HELICS_EXPORT void helicsFilterAddDeliveryEndpoint (helics_filter filt, const char *deliveryEndpoint, helics_error *err);

/** remove a destination target from a filter*/
HELICS_EXPORT void helicsFilterRemoveTarget (helics_filter filt, const char *dest, helics_error *err);

/** remove a delivery destination from a cloning filter*/
HELICS_EXPORT void helicsFilterRemoveDeliveryEndpoint (helics_filter filt, const char *deliveryEndpoint, helics_error *err);

/**@}*/
#ifdef __cplusplus
} /* end of extern "C" { */
#endif

#endif /* HELICS_APISHARED_MESSAGE_FILTER_FEDERATE_FUNCTIONS_H_*/
