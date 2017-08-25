#include "Global_res.h"
#include "cp_laninterfaces.h"

int8 getMACAddressNumValue(char** value, ParameterType* type, DeviceNode*  deviceNode)
{
	char MACAddressNum[256];
	int instance;
	char attrname[34] = {0};

	memset( MACAddressNum, 0, sizeof(MACAddressNum) );
	instance = atoi(deviceNode->parentNode->name);
	
	sprintf(attrname,"macLimitPort%d",instance);
	tcapi_get("Lan_BridgeMacLimit",attrname,MACAddressNum);
	
	return getTheValue(value, type, deviceNode, MACAddressNum);
}
int8 setMACAddressNumValue(void* value, struct DeviceNode*  deviceNode)
{
	uint32 MACAddressNum;
	char buffer[256] = {0};
	int instance;
	char attrname[34] = {0};
	
	MACAddressNum = *(uint32*)value;

	instance = atoi(deviceNode->parentNode->name);
	sprintf(attrname,"macLimitPort%d",instance);
	sprintf(buffer,"%lu",MACAddressNum);
	
	tcapi_set("Lan_BridgeMacLimit",attrname,buffer);
	SetCfgNodeFlag( "Lan", -1);
	return 0;
}
int8 getMACAddressNumAttribute(uint8* notification, AccessEntry** acl, DeviceNode* deviceNode)
{
	uint8  attribute;
	int8  result;
	
	attribute = tcLANInterfacesAttr.aMACAddressNum;
	result=GetTheAttributes(attribute,notification, acl, deviceNode);
	return result;
}
int8 setMACAddressNumAttribute(uint8 notificationChange, uint8 notification, uint8 accessListChange, AccessEntry* acl, struct DeviceNode*  deviceNode)
{
	uint8 *attribute = NULL;
	int8 result = 0;

	attribute = &tcLANInterfacesAttr.aMACAddressNum;
	result = SetTheAttributes(attribute, notificationChange, notification, accessListChange, acl, deviceNode);
	rpc.attrFlags.theSettingFlag1 |= LANINTERFACES_ATTR_FLAG;
	return result;
}

int8 getLanEtherTypeFilterValue(char** value, ParameterType* type, DeviceNode*  deviceNode)
{
	char attrName[32] = {0};
	char retValue[32] = {0};
	int instance;
	
	instance = atoi(deviceNode->parentNode->name);	
	sprintf(attrName, "P%d", instance - 1);	
	tcapi_get("IpMacFilter_EtherTypeFilter", attrName, retValue);	
	return getTheValue(value, type, deviceNode, retValue);	
}
int8 setLanEtherTypeFilterValue(void* value, struct DeviceNode*  deviceNode)
{
	char attrName[32] = {0};
	char *setValue = NULL;
	int instance = 0;

	if(value == NULL){
		return -1;
	}
	instance = atoi(deviceNode->parentNode->name);
	setValue=(char*)value;	
	sprintf(attrName, "P%d", instance - 1);	
	tcapi_set("IpMacFilter_EtherTypeFilter", attrName, setValue);
	SetCfgNodeFlag( "IpMacFilter", -1);
	return 0;		
}
int8 getLanEtherTypeFilterAttribute(uint8* notification, AccessEntry** acl, DeviceNode* deviceNode)
{
	uint8  attribute;
	int8  result;
	
	attribute = tcLANInterfacesAttr.aLanEtherTypeFilter;
	result=GetTheAttributes(attribute,notification, acl, deviceNode);
	return result;
}
int8 setLanEtherTypeFilterAttribute(uint8 notificationChange, uint8 notification, uint8 accessListChange, AccessEntry* acl, struct DeviceNode*  deviceNode)
{
	uint8 *attribute = NULL;
	int8 result = 0;

	attribute = &tcLANInterfacesAttr.aLanEtherTypeFilter;
	result = SetTheAttributes(attribute, notificationChange, notification, accessListChange, acl, deviceNode);
	rpc.attrFlags.theSettingFlag1 |= LANINTERFACES_ATTR_FLAG;
	return result;
}

int	cwmpInitLANEthernetInterfaceConfigfuncsSubTree( DeviceNodePtr deviceNode )
{
	int num = LANINTERFACENUM, rtnCode = 0;

	rtnCode = RegisterDynNodeFromIndex( deviceNode, LANEthernetInterfaceConfigIndex, num );

	return rtnCode;
}

#ifdef TCSUPPORT_WLAN
int8 getAssociateNumValue(char** value, ParameterType* type, DeviceNode*  deviceNode)
{
	char nodeName[34] = {0};
	char AssociateNum[10] = {0};
	int instance;
	
	instance = atoi(deviceNode->parentNode->name);	
	sprintf(nodeName, "WLan_Entry%d", instance - 1);
	
	tcapi_get(nodeName, "MaxStaNum", AssociateNum);

	
	return getTheValue(value, type, deviceNode, AssociateNum);
}
int8 setAssociateNumValue(void* value, struct DeviceNode*  deviceNode)
{	
	char nodeName[34] = {0};
	uint32 AssociateNum = 0;
	int instance = 0;
	char maxNumStr[10]={0};

	instance = atoi(deviceNode->parentNode->name);	

	SetCfgNodeFlag( "WLan", instance - 1);
	
	if(value == NULL){
		return -1;
	}

	AssociateNum = *((uint32*)value);
	
	sprintf(nodeName, "WLan_Entry%d", instance - 1);	
	sprintf(maxNumStr, "%lu", AssociateNum);
	tcapi_set(nodeName, "MaxStaNum", maxNumStr);
	return 0;	
}
int8 getAssociateNumAttribute(uint8* notification, AccessEntry** acl, DeviceNode* deviceNode)
{
	uint8  attribute;
	int8  result;
	
	attribute = tcLANInterfacesAttr.aAssociateNum;
	result=GetTheAttributes(attribute,notification, acl, deviceNode);
	return result;
}
int8 setAssociateNumAttribute(uint8 notificationChange, uint8 notification, uint8 accessListChange, AccessEntry* acl, struct DeviceNode*  deviceNode)
{
	uint8 *attribute = NULL;
	int8 result = 0;

	attribute = &tcLANInterfacesAttr.aAssociateNum;
	result = SetTheAttributes(attribute, notificationChange, notification, accessListChange, acl, deviceNode);
	rpc.attrFlags.theSettingFlag1 |= LANINTERFACES_ATTR_FLAG;
	return result;
}

int8 getWlanEtherTypeFilterValue(char** value, ParameterType* type, DeviceNode*  deviceNode)
{
	char attrName[32] = {0};
	char retValue[32] = {0};
	int instance;
	
	instance = atoi(deviceNode->parentNode->name);	
	sprintf(attrName, "P%d", instance - 1 + 4);	
	tcapi_get("IpMacFilter_EtherTypeFilter", attrName, retValue);	
	return getTheValue(value, type, deviceNode, retValue);	
}
int8 setWlanEtherTypeFilterValue(void* value, struct DeviceNode*  deviceNode)
{	
	char attrName[32] = {0};
	char *setValue = NULL;
	int instance = 0;

	if(value == NULL){
		return -1;
	}
	instance = atoi(deviceNode->parentNode->name);
	setValue=(char*)value;	
	sprintf(attrName, "P%d", instance - 1 + 4);	
	tcapi_set("IpMacFilter_EtherTypeFilter", attrName, setValue);
	SetCfgNodeFlag( "IpMacFilter", -1);
	return 0;
}
int8 getWlanEtherTypeFilterAttribute(uint8* notification, AccessEntry** acl, DeviceNode* deviceNode)
{
	uint8  attribute;
	int8  result;
	
	attribute = tcLANInterfacesAttr.aWlanEtherTypeFilter;
	result=GetTheAttributes(attribute,notification, acl, deviceNode);
	return result;
}
int8 setWlanEtherTypeFilterAttribute(uint8 notificationChange, uint8 notification, uint8 accessListChange, AccessEntry* acl, struct DeviceNode*  deviceNode)
{
	uint8 *attribute = NULL;
	int8 result = 0;

	attribute = &tcLANInterfacesAttr.aWlanEtherTypeFilter;
	result = SetTheAttributes(attribute, notificationChange, notification, accessListChange, acl, deviceNode);
	rpc.attrFlags.theSettingFlag1 |= LANINTERFACES_ATTR_FLAG;
	return result;
}

int	cwmpInitWLANConfigurationFuncsSubTree( DeviceNodePtr deviceNode )
{
	int rtnCode = 0, BssidNum;
	char buf[10];
	
	if ( deviceNode == NULL ) {
		return -1;
	}

	memset( buf, 0, sizeof(buf) );
	tcapi_get( "WLan_Common", "BssidNum", buf );
	
	BssidNum = atoi(buf);
	
	rtnCode = RegisterDynNodeFromIndex( deviceNode, WLANConfigurationIndex, BssidNum );

	return rtnCode;
}
#endif