/*
Copyright � 2017-2018,
Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable Energy, LLC
All rights reserved. See LICENSE file and DISCLAIMER for more details.
*/
#include "BrokerApp.hpp"
#include "../common/argParser.h"
#include "../common/stringToCmdLine.h"
#include "../core/BrokerFactory.hpp"
#include "../core/CoreBroker.hpp"
#include "../core/core-exceptions.hpp"
#include "../core/helicsVersion.hpp"
#include "helics/helics-config.h"
#include <fstream>
#include <iostream>

static const helics::ArgDescriptors InfoArgs{
  {"name,n", "name of the broker"},
  {"type,t", "type of the broker (\"(zmq)\", \"ipc\", \"test\", \"mpi\", \"test\", \"tcp\", \"udp\")"}};

namespace helics
{
namespace apps
{
BrokerApp::BrokerApp (int argc, char *argv[]) { loadFromArguments (argc, argv); }

BrokerApp::BrokerApp (core_type ctype, int argc, char *argv[]) : type (ctype) { loadFromArguments (argc, argv); }

BrokerApp::BrokerApp (const std::string &argString)
{
    StringToCmdLine cmdargs (argString);
    loadFromArguments (cmdargs.getArgCount (), cmdargs.getArgV ());
}

BrokerApp::BrokerApp (core_type ctype, const std::string &argString) : type (ctype)
{
    StringToCmdLine cmdargs (argString);
    loadFromArguments (cmdargs.getArgCount (), cmdargs.getArgV ());
}

BrokerApp::~BrokerApp ()
{
    if (!broker)
    {
        return;
    }
    bool sleep_toggle = false;
    while (broker->isConnected ())
    {
        if (!sleep_toggle)
        {
            std::this_thread::yield ();
        }
        else
        {
            std::this_thread::sleep_for (std::chrono::milliseconds (200));
        }
        sleep_toggle = !sleep_toggle;
    }
    broker = nullptr;
    helics::BrokerFactory::cleanUpBrokers (500);
}

void BrokerApp::loadFromArguments (int argc, char *argv[])
{
    helics::variable_map vm;
    auto exit_early = helics::argumentParser (argc, argv, vm, InfoArgs);

    if (exit_early != 0)
    {
        if (exit_early == helics::helpReturn)
        {
            helics::BrokerFactory::displayHelp ();
        }
        else if (exit_early == helics::versionReturn)
        {
            std::cout << helics::versionString << '\n';
        }
        return;
    }

    std::string name = (vm.count ("name") > 0) ? vm["name"].as<std::string> () : "";
    if (vm.count ("type") > 0)
    {
        try
        {
            type = coreTypeFromString (vm["type"].as<std::string> ());
        }
        catch (std::invalid_argument &ie)
        {
            std::cerr << "Unable to generate broker from specified type: " << ie.what () << '\n';
            throw;
        }
    }

    broker = BrokerFactory::create (type, name, argc, argv);
    if (!broker->isConnected ())
    {
        throw (ConnectionFailure ("Broker is unable to connect\n"));
    }
}

/** run the Echo federate until the specified time
@param stopTime_input the desired stop time
*/
/** check if the Broker is running*/
bool BrokerApp::isActive () const { return ((broker) && (broker->isConnected ())); }

/** forceably disconnect the broker*/
void BrokerApp::forceTerminate ()
{
    if (!broker)
    {
        return;
    }
    if (broker->isConnected ())
    {
        broker->disconnect ();
    }
}

}  // namespace apps
}  // namespace helics