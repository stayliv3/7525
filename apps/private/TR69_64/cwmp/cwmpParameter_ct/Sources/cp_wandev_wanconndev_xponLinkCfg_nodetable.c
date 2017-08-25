#include "Global_res.h"
#include "cp_wandev_wanconndev_xponLinkCfg.h"


static NodeFunc EPonEnable=
{
	NULL,
	NULL,
	getWANPonLinkCfg1EPonEnableValue,
	setWANPonLinkCfg1EPonEnableValue,
	getWANPonLinkCfg1EPonEnableAttribute,
	setWANPonLinkCfg1EPonEnableAttribute,
	NULL
};

static NodeFunc GPonEnable=
{
	NULL,
	NULL,
	getWANPonLinkCfg1GPonEnableValue,
	setWANPonLinkCfg1GPonEnableValue,
	getWANPonLinkCfg1GPonEnableAttribute,
	setWANPonLinkCfg1GPonEnableAttribute,
	NULL
};

static NodeFunc Mode=
{
	NULL,
	NULL,
	getWANPonLinkCfg1ModeValue,
	setWANPonLinkCfg1ModeValue,
	getWANPonLinkCfg1ModeAttribute,
	setWANPonLinkCfg1ModeAttribute,
	NULL
};

static NodeFunc VLANIDMark=
{
	NULL,
	NULL,
	getWANPonLinkCfg1VLANIDMarkValue,
	setWANPonLinkCfg1VLANIDMarkValue,
	getWANPonLinkCfg1VLANIDMarkAttribute,
	setWANPonLinkCfg1VLANIDMarkAttribute,
	NULL
};

static NodeFunc V8021PMark=
{
	NULL,
	NULL,
	getWANPonLinkCfg18021PMarkValue,
	setWANPonLinkCfg18021PMarkValue,
	getWANPonLinkCfg18021PMarkAttribute,
	setWANPonLinkCfg18021PMarkAttribute,
	NULL
};

/*
	Parent Node: InternetGatewayDevice.WANDevice.1.WANConnectionDevice.{i}.X_CT-COM_WANEponLinkConfig.
	                    InternetGatewayDevice.WANDevice.1.WANConnectionDevice.{i}.X_CT-COM_WANGponLinkConfig.
	Parent Node Table Location: cp_wandev_wanconndev_nodetable.c
*/
CwmpParameterStruct WANEPonLinkConfig[] =
{
	{"Enable", BooleanW, NoLimite, &EPonEnable, NULL},
	{"Mode", UnsignIntW, NoLimite, &Mode, NULL},
	{"VLANIDMark", UnsignIntW, NoLimite, &VLANIDMark, NULL},
	{"802-1pMark", UnsignIntW, NoLimite, &V8021PMark, NULL},

	{NULL, -1, -1, NULL, NULL}
};

CwmpParameterStruct WANGEPonLinkConfig[] =
{
	{"Enable", BooleanW, NoLimite, &GPonEnable, NULL},
	{"Mode", UnsignIntW, NoLimite, &Mode, NULL},
	{"VLANIDMark", UnsignIntW, NoLimite, &VLANIDMark, NULL},
	{"802-1pMark", UnsignIntW, NoLimite, &V8021PMark, NULL},

	{NULL, -1, -1, NULL, NULL}
};


