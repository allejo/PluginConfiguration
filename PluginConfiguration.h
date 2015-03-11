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

#ifndef __PLUGIN_CONFIG_OPTIONS_H__
#define __PLUGIN_CONFIG_OPTIONS_H__

#include <map>
#include <string>
#include <vector>

#include "plugin_config.h"

class PluginConfiguration
{
    protected:
        PluginConfiguration (std::string sectionName, std::string filePath);

        void configRegisterVector (std::string configOption, std::vector<std::string> defaultValue, std::string delimiter);
        void configRegisterString (std::string configOption, std::string defaultValue);
        void configRegisterBool   (std::string configOption, bool defaultValue);
        void configRegisterInt    (std::string configOption, int defaultValue);

        std::vector<std::string> vectorConfigOptions;
        std::vector<std::string> stringConfigOptions;
        std::vector<std::string> boolConfigOptions;
        std::vector<std::string> intConfigOptions;

        bool readConfigurationFile(const char* filePath);

        virtual void registerConfigOptions() = 0;

    private:
        PluginConfig pluginConfigObj;

        std::string pluginSectionName,
                    configFileName;
                    
        std::vector<std::string> split (std::string string, std::string delimeter);

        std::map<std::string, std::vector<std::string>>  vectorConfigValues;
        std::map<std::string, std::string>               stringConfigValues;
        std::map<std::string, bool>                      boolConfigValues;
        std::map<std::string, int>                       intConfigValues;

        std::string getString    (const char* itemName);
        bool        isOptionSet  (const char* itemName);
        bool        getBool      (const char* itemName);
        int         getInt       (const char* itemName);
};

#endif
