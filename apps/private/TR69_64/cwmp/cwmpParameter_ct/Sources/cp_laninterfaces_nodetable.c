#include "Global_res.h"
#include "cp_laninterfaces.h"


static NodeFunc MACAddressNum=
{
	NULL,
	NULL,
	getMACAddressNumValue, 
	setMACAddressNumValue, 
	getMACAddressNumAttribute, 
	setMACAddressNumAttribute, 
	NULL,
};

static NodeFunc LanEtherTypeFilter=
{
	NULL,
	NULL,
	getLanEtherTypeFilterValue, 
	setLanEtherTypeFilterValue, 
	getLanEtherTypeFilterAttribute, 
	setLanEtherTypeFilterAttribute, 
	NULL,
};

static NodeFunc LANEthernetInterfaceConfigfuncs=
{
	NULL,
	NULL,
	NULL, 
	NULL, 
	NULL, 
	NULL, 
	cwmpInitLANEthernetInterfaceConfigfuncsSubTree
};

#ifdef TCSUPPORT_WLAN
static NodeFunc WLANConfigurationFuncs=
{
	NULL,
	NULL,
	NULL, 
	NULL, 
	NULL, 
	NULL, 
	cwmpInitWLANConfigurationFuncsSubTree
};

static NodeFunc AssociateNum=
{
	NULL,
	NULL,
	getAssociateNumValue, 
	setAssociateNumValue, 
	getAssociateNumAttribute, 
	setAssociateNumAttribute, 
	NULL,
};

static NodeFunc WlanEtherTypeFilter=
{
	NULL,
	NULL,
	getWlanEtherTypeFilterValue, 
	setWlanEtherTypeFilterValue, 
	getWlanEtherTypeFilterAttribute, 
	setWlanEtherTypeFilterAttribute, 
	NULL,
};
#endif

/*
	Parent Node: InternetGatewayDevice.LANInterfaces.
	Parent Node Table Location: cp_topnodetable.c 
*/
CwmpParameterStruct LANInterfaces[] = 
{
	{"LANEthernetInterfaceConfig",ObjectR,NoLimite,&LANEthernetInterfaceConfigfuncs,NULL},
#ifdef TCSUPPORT_WLAN
	{"WLANConfiguration",ObjectR,NoLimite,&WLANConfigurationFuncs,NULL},
#endif
	{NULL, -1, -1, NULL, NULL}
};

CwmpParameterStruct LANEthernetInterfaceConfigIndex[] = 
{
	{NULL,ObjectR, NoLimite,NULL,LANEthernetInterfaceConfig},
	{NULL, -1, -1, NULL, NULL}	
};

#ifdef TCSUPPORT_WLAN
CwmpParameterStruct WLANConfigurationIndex[] = 
{
	{NULL,ObjectR, NoLimite,NULL,WLANConfiguration},
	{NULL, -1, -1, NULL, NULL}	
};

CwmpParameterStruct WLANConfiguration[] = 
{
	{X_CMCC"AssociateNum",UnsignIntW, NoLimite,&AssociateNum,NULL},
	{X_CMCC"EtherTypeFilter",StrW, NoLimite,&WlanEtherTypeFilter,NULL},
	{NULL, -1, -1, NULL, NULL}	
};
#endif

CwmpParameterStruct LANEthernetInterfaceConfig[] = 
{
	{X_CMCC"MACAddressNum",UnsignIntW, NoLimite,&MACAddressNum,NULL},
	{X_CMCC"EtherTypeFilter",StrW, NoLimite,&LanEtherTypeFilter,NULL},
	{NULL, -1, -1, NULL, NULL}	
};
