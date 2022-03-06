#include <windows.h>
#include <stdio.h>
#include <lmaccess.h>
#include "beacon.h"

void ListDomainGroups(const wchar_t * domain)
{
	PNET_DISPLAY_GROUP pBuff = NULL, p = NULL;
	DWORD res = 0, dwRec = 0, i = 0;

	do
	{ 

		res = NETAPI32$NetQueryDisplayInformation(domain, 3, i, 100, MAX_PREFERRED_LENGTH, &dwRec, (PVOID*) &pBuff);
		if((res==ERROR_SUCCESS) || (res==ERROR_MORE_DATA) && dwRec != 0 && pBuff != NULL)
		{
			p = pBuff;
			for(;dwRec>0;dwRec--)
			{
				BeaconPrintf("Name:      %s\n"
				"Comment:   %s\n"
				"Group ID:  %lu\n"
				"Attributes: %lu\n"
				"--------------------------------\n",
				p->grpi3_name,
				p->grpi3_comment,
				p->grpi3_group_id,
				p->grpi3_attributes);
				i = p->grpi3_next_index;
				p++;
			}
			NETAPI32$NetApiBufferFree(pBuff);
			pBuff = NULL;
		}
		else
		{
			BeaconPrintf(CALLBACK_ERROR, "Error: %lu\n", res);
		}
	} while (res==ERROR_MORE_DATA);
}

void go(char *args, int alen) 
{
	datap parser;
	BeaconDataParse(&parser, args, alen);
	const wchar_t * domain = (wchar_t *)BeaconDataExtract(&parser, NULL);
	ListDomainGroups(domain);
}

