/*
    Copyright (c) 2015 Vladimir Jimenez

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <map>
#include <string>
#include <vector>

#include "plugin_utils.h"

#include "PluginConfiguration.h"

PluginConfiguration::PluginConfiguration (std::string sectionName, std::string filePath)
{
    pluginSectionName = sectionName;
    configFileName = filePath;
}

void PluginConfiguration::readConfigurationFile(const char* filePath)
{
    registerConfigOptions();

    pluginConfigObj = PluginConfig(filePath);

    if (pluginConfigObj.errors)
    {
        bz_debugMessage(0, "Your configuration file has one or more errors. Using default configuration values.");

        return false;
    }

    for (auto option : vectorConfigValues)
    {
        if (isOptionSet(option.c_str()))
        {
            vectorConfigValues[option] = split(getString(option.c_str()), "\\n");
        }
    }

    for (auto option : stringConfigOptions)
    {
        if (isOptionSet(option.c_str()))
        {
            stringConfigValues[option] = getString(option.c_str());
        }
    }

    for (auto option : boolConfigOptions)
    {
        if (isOptionSet(option.c_str()))
        {
            boolConfigValues[option] = getBool(option.c_str());
        }
    }

    for (auto option : intConfigOptions)
    {
        if (isOptionSet(option.c_str()))
        {
            intConfigValues[option] = getInt(option.c_str());
        }
    }

    return true;
}

std::vector<std::string> PluginConfiguration::split (std::string string, std::string delimeter)
{
    return tokenize(string, delimeter, 0, true);
}

void PluginConfiguration::configRegisterVector (std::string configOption, std::vector<std::string> defaultValue, std::string delimiter)
{
    vectorConfigValues[configOption] = split(defaultValue, delimiter);
}

void PluginConfiguration::configRegisterString (std::string configOption, std::string defaultValue)
{
    stringConfigValues[configOption] = defaultValue;
}

void PluginConfiguration::configRegisterBool (std::string configOption, bool defaultValue)
{
    boolConfigValues[configOption] = defaultValue;
}

void PluginConfiguration::configRegisterInt (std::string configOption, int defaultValue)
{
    intConfigValues[configOption] = defaultValue;
}

bool PluginConfiguration::isOptionSet(const char* itemName)
{
    return (!pluginConfigObj.item(pluginSectionName, itemName).empty());
}

bool PluginConfiguration::getBool(const char* itemName)
{
    return toBool(getString(itemName));
}

int PluginConfiguration::getInt(const char* itemName)
{
    return atoi(getString(itemName).c_str());
}

std::string PluginConfiguration::getString(const char* itemName)
{
    return pluginConfigObj.item(pluginSectionName, itemName);
}
