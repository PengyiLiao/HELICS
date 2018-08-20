/*
Copyright © 2017-2018,
Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC
All rights reserved. See LICENSE file and DISCLAIMER for more details.
*/
#ifndef HELICS_CPP98_FEDERATE_HPP_
#define HELICS_CPP98_FEDERATE_HPP_
#pragma once

#include "../shared_api_library/MessageFilters.h"
#include "../shared_api_library/helics.h"
#include "helicsExceptions.hpp"
#include "Filter.hpp"
#include "config.hpp"
#include <complex>

#include <string>
#include <vector>

// defines for setFlag values in core/flag-definitions.h
// enum for core_type:int in core/core-types.h

namespace helicscpp
{
class FederateInfo
{
  public:
    FederateInfo () { fi = helicsCreateFederateInfo (); }

    FederateInfo ( const std::string &coretype)
    {
        fi = helicsCreateFederateInfo ();
        helicsFederateInfoSetCoreTypeFromString (fi, coretype.c_str ());
    }

    ~FederateInfo () { helicsFederateInfoFree (fi); }

    void setCoreName (const std::string &corename) { helicsFederateInfoSetCoreName (fi, corename.c_str ()); }

    void setCoreInitString (const std::string &coreInit)
    {
        helicsFederateInfoSetCoreInitString (fi, coreInit.c_str ());
    }

    void setCoreTypeFromString (const std::string &coretype)
    {
        helicsFederateInfoSetCoreTypeFromString (fi, coretype.c_str ());
    }

    void setCoreType (int coretype) { helicsFederateInfoSetCoreType (fi, coretype); }

    void setFlagOption (int flag, int value) { helicsFederateInfoSetFlagOption (fi, flag, value); }

    void setTimeProperty (int timeProperty, helics_time_t timeValue) { helicsFederateInfoSetTimeProperty (fi,timeProperty, timeValue); }

    
    void setIntegerProperty (int integerProperty, int intValue) { helicsFederateInfoSetIntegerProperty (fi,integerProperty, intValue); }

    helics_federate_info_t getInfo () { return fi; }

  private:
    helics_federate_info_t fi;
};


typedef struct
{
  public:
    helics_time_t grantedTime;  //!< the time of the granted step
    helics_iteration_status status;  //!< the convergence state
    /** default constructor*/
} helics_iteration_time;

class Federate
{
  public:
    // Default constructor, not meant to be used
      Federate() : fed(NULL), exec_async_iterate(false) {};

    Federate (const Federate &fedObj) : exec_async_iterate (fedObj.exec_async_iterate)
    {
        fed = helicsFederateClone (fedObj.fed);
    }
    Federate &operator= (const Federate &fedObj)
    {
        exec_async_iterate = fedObj.exec_async_iterate;
        fed = helicsFederateClone (fedObj.fed);
        return *this;
    }
#ifdef HELICS_HAS_RVALUE_REFS
    Federate (Federate &&fedObj) : exec_async_iterate (fedObj.exec_async_iterate)
    {
        fed = fedObj.fed;
        fedObj.fed = NULL;
    }
    Federate &operator= (Federate &&fedObj)
    {
        exec_async_iterate = fedObj.exec_async_iterate;
        fed = fedObj.fed;
        fedObj.fed = NULL;
        return *this;
    }
#endif
    virtual ~Federate() {
        if (fed != NULL)
        {
            helicsFederateFree(fed);
        }
    }

    operator helics_federate () const { return fed; }

    helics_federate baseObject () const { return fed; }

    void setFlag (int flag, int value) { helicsFederateSetFlagOption (fed, flag, value); }

    void setTimeProperty (int tProperty, helics_time_t timeDelta) { helicsFederateSetTimeProperty (fed,tProperty, timeDelta); }


    void setIntegerProperty (int intProperty, int value) { helicsFederateSetIntegerProperty(fed, intProperty, value); }

    federate_state getState() const
    {
        federate_state fedState;
        helicsFederateGetState(fed, &fedState);
        return fedState;
    }

    void enterInitializingMode ()
    {
        if (helics_ok != helicsFederateEnterInitializingMode (fed))
        {
            throw (InvalidStateTransition ("cannot transition from current mode to initialization mode"));
        }
    }

    void enterInitializingModeAsync ()
    {
        if (helics_ok != helicsFederateEnterInitializingModeAsync (fed))
        {
            throw (InvalidStateTransition ("cannot transition from current mode to initialization mode"));
        }
    }

    bool isAsyncOperationCompleted () const
    {
        // returns int, 1 = true, 0 = false
        return helicsFederateIsAsyncOperationCompleted (fed) > 0;
    }

    void enterInitializingModeComplete ()
    {
        if (helics_ok != helicsFederateEnterInitializingModeComplete (fed))
        {
            throw (InvalidFunctionCall ("cannot call finalize function without first calling async function"));
        }
    }

    helics_iteration_status enterExecutingMode (helics_iteration_request iterate = no_iteration)
    {
        helics_iteration_status out_iterate = next_step;
        if (iterate == no_iteration)
        {
            helicsFederateEnterExecutingMode (fed);
        }
        else
        {
            helicsFederateEnterExecutingModeIterative (fed, iterate, &out_iterate);
        }
        return out_iterate;
    }

    void enterExecutingModeAsync (helics_iteration_request iterate = no_iteration)
    {
        if (iterate == no_iteration)
        {
            helicsFederateEnterExecutingModeAsync (fed);
            exec_async_iterate = false;
        }
        else
        {
            helicsFederateEnterExecutingModeIterativeAsync (fed, iterate);
            exec_async_iterate = true;
        }
    }

    helics_iteration_status enterExecutingModeComplete ()
    {
        helics_iteration_status out_iterate = next_step;
        if (exec_async_iterate)
        {
            helicsFederateEnterExecutingModeIterativeComplete (fed, &out_iterate);
        }
        else
        {
            helicsFederateEnterExecutingModeComplete (fed);
        }
        return out_iterate;
    }

    void finalize () { helicsFederateFinalize (fed); }

    helics_time_t requestTime (helics_time_t time)
    {
        helics_time_t grantedTime;
        helicsFederateRequestTime (fed, time, &grantedTime);
        return grantedTime;
    }

    helics_iteration_time requestTimeIterative (helics_time_t time, helics_iteration_request iterate)
    {
        helics_iteration_time itTime;
        helicsFederateRequestTimeIterative (fed, time, iterate, &(itTime.grantedTime), &(itTime.status));
        return itTime;
    }

    void requestTimeAsync (helics_time_t time)
    {
        if (helics_ok != helicsFederateRequestTimeAsync (fed, time))
        {
            throw (InvalidFunctionCall ("cannot call request time in present state"));
        }
    }

    void requestTimeIterativeAsync (helics_time_t time, helics_iteration_request iterate)
    {
        helicsFederateRequestTimeIterativeAsync (fed, time, iterate);
    }

    helics_time_t requestTimeComplete ()
    {
        helics_time_t newTime;
        helicsFederateRequestTimeComplete (fed, &newTime);
        return newTime;
    }

    helics_iteration_time requestTimeIterativeComplete ()
    {
        helics_iteration_time itTime;
        helicsFederateRequestTimeIterativeComplete (fed, &(itTime.grantedTime), &(itTime.status));
        return itTime;
    }

    std::string getName () const
    {
        char str[255];
        helicsFederateGetName (fed, &str[0], sizeof (str));
        std::string result (str);
        return result;
    }
    /** make a query of the core
    @details this call is blocking until the value is returned which make take some time depending on the size of
    the federation and the specific string being queried
    @param target  the target of the query can be "federation", "federate", "broker", "core", or a specific name of
    a federate, core, or broker
    @param queryStr a string with the query see other documentation for specific properties to query, can be
    defined by the federate
    @return a string with the value requested.  this is either going to be a vector of strings value or a json
    string stored in the first element of the vector.  The string "#invalid" is returned if the query was not valid
    */
    std::string query (const std::string &target, const std::string &queryStr)
    {
        // returns helics_query
        helics_query q = helicsCreateQuery (target.c_str (), queryStr.c_str ());
        std::string result (helicsQueryExecute (q, fed));
        helicsQueryFree (q);
        return result;
    }

    Filter registerFilter (helics_filter_type_t type,
                                 const std::string &name = std::string ())
    {
        return Filter (helicsFederateRegisterFilter (fed, type, name.c_str ()));
    }


    /** create a cloning Filter on the specified federate
    @details cloning filters copy a message and send it to multiple locations source and destination can be added
    through other functions
    @param fed the fed to register through
    @param deliveryEndpoint the specified endpoint to deliver the message
    @return a helics_filter object
    */
    CloningFilter registerCloningFilter (const std::string &deliveryEndpoint)
    {
        return CloningFilter (helicsFederateRegisterCloningFilter (fed, deliveryEndpoint.c_str ()));
    }

  protected:
    helics_federate fed;
    bool exec_async_iterate;
};

}  // namespace helicscpp
#endif
