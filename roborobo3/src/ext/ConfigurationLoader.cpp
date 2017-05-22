#include "Config/ConfigurationLoader.h"
#include "Config/TemplateWanderConfigurationLoader.h"
#include "Config/TemplateBoidsConfigurationLoader.h"
#include "Config/TemplateRandomwalkConfigurationLoader.h"
#include "Config/TemplateEEConfigurationLoader.h"
#include "Config/TemplateVanillaEEConfigurationLoader.h"
#include "Config/TemplateMedeaConfigurationLoader.h"
#include "Config/TestBoidsConfigurationLoader.h"
#include "Config/CookieRWConfigurationLoader.h"
#include "Config/BoidsEEConfigurationLoader.h"
#include "Config/PopConvceConfigurationLoader.h"
#include "Config/PopConvceConfigurationLoader.h"
#include "Config/SwapWalkConfigurationLoader.h"
#include "Config/CompassWalkConfigurationLoader.h"
#include "Config/CustomBoidsConfigurationLoader.h"
//###DO-NOT-DELETE-THIS-LINE###TAG:INCLUDE###//


ConfigurationLoader::ConfigurationLoader()
{
	//nothing to do
}

ConfigurationLoader::~ConfigurationLoader()
{
	//nothing to do
}

ConfigurationLoader* ConfigurationLoader::make_ConfigurationLoader (std::string configurationLoaderObjectName)
{
	if (0)
	{
		// >>> Never reached
	}
#if defined PRJ_TEMPLATEWANDER || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateWanderConfigurationLoader" )
	{
		return new TemplateWanderConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEBOIDS || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateBoidsConfigurationLoader" )
	{
		return new TemplateBoidsConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATERANDOMWALK || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateRandomwalkConfigurationLoader" )
	{
		return new TemplateRandomwalkConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEEE || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateEEConfigurationLoader" )
    {
        return new TemplateEEConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEVANILLAEE || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateVanillaEEConfigurationLoader" )
	{
		return new TemplateVanillaEEConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEMEDEA || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateMedeaConfigurationLoader" )
	{
		return new TemplateMedeaConfigurationLoader();
	}
#endif
#if defined PRJ_TESTBOIDS || !defined MODULAR
	else if (configurationLoaderObjectName == "TestBoidsConfigurationLoader" )
	{
		return new TestBoidsConfigurationLoader();
	}
#endif
#if defined PRJ_COOKIERW || !defined MODULAR
	else if (configurationLoaderObjectName == "CookieRWConfigurationLoader" )
	{
		return new CookieRWConfigurationLoader();
	}
#endif
#if defined PRJ_BOIDSEE || !defined MODULAR
	else if (configurationLoaderObjectName == "BoidsEEConfigurationLoader" )
	{
		return new BoidsEEConfigurationLoader();
	}
#endif
#if defined PRJ_POPCONVCE || !defined MODULAR
	else if (configurationLoaderObjectName == "PopConvceConfigurationLoader" )
	{
		return new PopConvceConfigurationLoader();
	}
#endif
#if defined PRJ_POPCONVCE || !defined MODULAR
	else if (configurationLoaderObjectName == "PopConvceConfigurationLoader" )
	{
		return new PopConvceConfigurationLoader();
	}
#endif
#if defined PRJ_SWAPWALK || !defined MODULAR
	else if (configurationLoaderObjectName == "SwapWalkConfigurationLoader" )
	{
		return new SwapWalkConfigurationLoader();
	}
#endif
#if defined PRJ_COMPASSWALK || !defined MODULAR
	else if (configurationLoaderObjectName == "CompassWalkConfigurationLoader" )
	{
		return new CompassWalkConfigurationLoader();
	}
#endif
#if defined PRJ_CUSTOMBOIDS || !defined MODULAR
	else if (configurationLoaderObjectName == "CustomBoidsConfigurationLoader" )
	{
		return new CustomBoidsConfigurationLoader();
	}
#endif
    //###DO-NOT-DELETE-THIS-LINE###TAG:SWITCH###//
	else
	{
		return NULL;
	}

}
