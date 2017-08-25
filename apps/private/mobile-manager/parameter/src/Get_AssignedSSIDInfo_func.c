/************************************************************************
 *
 *	Copyright (C) 2003 Trendchip Technologies, Corp.
 *	All Rights Reserved.
 *
 * Trendchip Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of Trendchip Technologies, Co. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * Trendchip Technologeis, Co.
 *
 *************************************************************************/
#include "Get_AssignedSSIDInfo_func.h"

json_t* Get_AssignedSSIDInfo(json_t* req_root,  json_t* req_para)
{
	json_t *cursor = NULL, *reply_root = NULL, *reply_para = NULL;
	char *cSSIDIndex = NULL, nodeName[48] = {0}, cur_ssid_name[33] = {0}, cur_authmode[32] = {0}, maxBitRate[5] = {0};
	char ssidEnable[10]= {0}, channel[10]= {0};
	unsigned int cur_ssid_idx = 0;
	int ret = -1;

	if(!TCSUPPORT_WLAN_VAL){
		mobile_printf(MOBILE_INFO,"%s:wlan is not support!...\n",__FUNCTION__);
		return ParameterBuildJSON(req_root,req_para,CMD_UNRECOGNIZE);
	}

	mobile_printf(MOBILE_DEBUG, "%s, line = %d\n",__FUNCTION__,__LINE__);

	cSSIDIndex = ParameterSearchValue(req_para, "SSIDIndex");

	if(cSSIDIndex != NULL)
	{
		cur_ssid_idx = atoi(cSSIDIndex) - 1;
		if( (cur_ssid_idx > 7) || (cur_ssid_idx < 0) )
		{
			ret = -1;
		}
		else{
			ret = 0;

			sprintf(nodeName, "WLan_Entry%d", cur_ssid_idx);
			
			tcapi_get(nodeName, "SSID", cur_ssid_name);			
			tcapi_get(nodeName, "AuthMode", cur_authmode);
			if(strcmp(cur_authmode, "OPEN") == 0){
				strcpy(cur_authmode,"1");
			}
			if(strstr(cur_authmode, "WEP") != NULL){
				strcpy(cur_authmode,"2");
			}
			else if(strcmp(cur_authmode, "WPAPSK") == 0){
				strcpy(cur_authmode,"3");
			}
			else if(strcmp(cur_authmode, "WPA2PSK") == 0){
				strcpy(cur_authmode,"4");
			}
			else if( strcmp(cur_authmode, "WPAPSKWPA2PSK") == 0 ) {
				strcpy(cur_authmode, "5");
			}
			tcapi_get(nodeName, "EnableSSID", ssidEnable);			
			tcapi_get("WLan_Common", "Channel", channel);			
			tcapi_get("WLan_Common", "TxPowerLevel", maxBitRate);
			if(strcmp(maxBitRate, "1") == 0){
				strcpy(maxBitRate,"100");
			}
			if(strstr(maxBitRate, "2") != NULL){
				strcpy(maxBitRate,"80");
			}
			else if(strcmp(maxBitRate, "3") == 0){
				strcpy(maxBitRate,"60");
			}
			else if(strcmp(maxBitRate, "4") == 0){
				strcpy(maxBitRate,"30");
			}
			else if ( strcmp(maxBitRate, "5") == 0 ) {
				strcpy(maxBitRate, "20");
			}
		}	
	}
	else
	{
		ret = -1;
	}

	//build parameter
	if(ret == -1){
		if(!(reply_para = ParameterBuildJSONReplyPara(req_para, 1))){
			mobile_printf(MOBILE_INFO,"%s:ParameterBuildJSONReplyPara Err!...\n",__FUNCTION__);
			goto err;
		}
		if(JSON_OK != ParameterAddNewJSONChild(reply_para, PARA_FAIL_REASON, "The Assigned WLan Is Not Exist")){
			mobile_printf(MOBILE_INFO,"%s:ParameterAddNewJSONChild Err!...\n",__FUNCTION__);
			goto err;
		}
	}
	else{
		if(!(reply_para = ParameterBuildJSONReplyPara(req_para, 0))){//ok
			mobile_printf(MOBILE_INFO,"%s:ParameterBuildJSONReplyPara Err!...\n",__FUNCTION__);
			goto err;
		}
		if(JSON_OK != ParameterAddNewJSONChild(reply_para, PARA_SSID , cur_ssid_name)){
			mobile_printf(MOBILE_INFO,"%s:ParameterAddNewJSONChild Err!...\n",__FUNCTION__);
			goto err;
		}
		if(JSON_OK != ParameterAddNewJSONChild(reply_para, PARA_ENCRYPT , cur_authmode)){
			mobile_printf(MOBILE_INFO,"%s:ParameterAddNewJSONChild Err!...\n",__FUNCTION__);
			goto err;
		}
		if(JSON_OK != ParameterAddNewJSONChild(reply_para, PARA_POWERLEVEL , maxBitRate)){
			mobile_printf(MOBILE_INFO,"%s:ParameterAddNewJSONChild Err!...\n",__FUNCTION__);
			goto err;
		}
		if(JSON_OK != ParameterAddNewJSONChild(reply_para, PARA_CHANNEL , channel)){
			mobile_printf(MOBILE_INFO,"%s:ParameterAddNewJSONChild Err!...\n",__FUNCTION__);
			goto err;
		}
		if(JSON_OK != ParameterAddNewJSONChild(reply_para, PARA_ENABLE , ssidEnable)){
			mobile_printf(MOBILE_INFO,"%s:ParameterAddNewJSONChild Err!...\n",__FUNCTION__);
			goto err;
		}
	}
	//build head
	if(!(reply_root = ParameterBuildJSONReplyHead(req_root,PARA_RESULT_SUCCESS))){
		mobile_printf(MOBILE_INFO,"%s:ParameterBuildJSONReplyHead Err!...\n",__FUNCTION__);
		goto err;
	}
	if(ParameterBuildJSONAddPara2Head(reply_root, reply_para)){
		mobile_printf(MOBILE_INFO,"%s:ParameterBuildJSONAddPara2Head Err!...\n",__FUNCTION__);
		goto err;
	}	
		
#if PARAMETER_REPLAY_DBG
	char* value_str = NULL; 
	json_tree_to_string(reply_root,&value_str);
	mobile_printf(MOBILE_INFO, "%s: reply json pkt=%s!...\n", __FUNCTION__,value_str);
	free(value_str);	
#endif	

	return reply_root;
	
err:
	if(reply_root) ParameterFreeJSON(&reply_root);
	if(reply_para) ParameterFreeJSON(&reply_para);
	return NULL;
}

