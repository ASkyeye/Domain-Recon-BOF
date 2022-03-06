#include <windows.h>
#include <stdio.h>
#include <lmaccess.h>
#include "beacon.h"

void ListGlobalGroupMembers(const wchar_t *domain, const wchar_t *groupname)
{
	PGROUP_INFO_0 pBuff = NULL, p = NULL;
	DWORD dwTotal = 0, dwRead = 0, i = 0;
	DWORD_PTR hResume = 0;
	NET_API_STATUS res = 0;
	do{
		res = NETAPI32$NetGroupGetUsers(domain, groupname, 0, (LPBYTE *) &pBuff, MAX_PREFERRED_LENGTH, &dwRead, &dwTotal, &hResume);
		if((res==ERROR_SUCCESS) || (res==ERROR_MORE_DATA))
		{
			p = pBuff;
			for(;dwRead>0;dwRead--)
			{
				BeaconPrintf("%s\n", p->grpi0_name);
				p++;
			}
			i = 0;
			NETAPI32$NetApiBufferFree(pBuff);
		}
		else
		{
			BeaconPrintf(CALLBACK_ERROR, "Error: %lu\n", res);
		}
	} while(res == ERROR_MORE_DATA);
}

void go(char *args, int alen) 
{
	datap parser;
	BeaconDataParse(&parser, args, alen);
	const wchar_t *domain = (wchar_t *)BeaconDataExtract(&parser, NULL);
	const wchar_t *group = (wchar_t *)BeaconDataExtract(&parser, NULL);
	ListGlobalGroupMembers(domain, group);
}
