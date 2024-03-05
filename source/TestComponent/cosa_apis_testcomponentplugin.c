/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "ansc_platform.h"
#include "cosa_apis.h"
#include "cosa_apis_testcomponentplugin.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern ANSC_HANDLE bus_handle;//lnt
extern char g_Subsystem[32];//lnt

static unsigned int TestSampleParamUlongValue = 1;
static char TestSampleParam[64] = "Welcome To RDKB";
static char MyString[10];
/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_GetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                char*                       pValue,
                ULONG*                      pUlSize
            );

    description:

        This function is called to retrieve string parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/
BOOL
TestComponent_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{

	if( AnscEqualString(pParamName, "MyString", TRUE))
	{
		*pUlSize = strlen(MyString);

		if (strcpy(pValue, MyString))
			return TRUE;
		return FALSE;
	}
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_GetParamBoolValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                BOOL*                       pBool
            );

    description:

        This function is called to retrieve Boolean parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        BOOL*                       pBool
    )
{
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_GetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                ULONG*                      puLong
            );

    description:

        This function is called to retrieve ULONG parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        ULONG*                      puLong
    )
{
	if( AnscEqualString(pParamName, "TestSampleParamUlong", TRUE))
	{
		*puLong =  TestSampleParamUlongValue;
		return TRUE;
	}
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_GetParamIntValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                int*                        pInt
            );

    description:

        This function is called to retrieve integer parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                int*                        pInt
                The buffer of returned integer value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_GetParamIntValue
    (
         ANSC_HANDLE                 hInsContext,
        char*                        pParamName,
        int*                      	 pInt
    )
{
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

       BOOL
       TestComponent_SetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamArray,
                char*                       pString,
            );

    description:

        This function is called to set bulk parameter values; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name array;

                char*                       pString,
                The size of the array;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        char*                       pString
    )
{	
	if( AnscEqualString(pParamName, "MyString", TRUE))
	{
        if (!strcmp(pString, "error"))
            return FALSE;

		if (strcpy(MyString, pString))
			return TRUE;
		return FALSE;
	}


    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_SetParamBoolValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                BOOL                        bValue
            );

    description:

        This function is called to set BOOL parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                BOOL                        bValue
                The updated BOOL value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        BOOL                        bValue
    )
{
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_SetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                ULONG                       uValue
            );

    description:

        This function is called to set ULONG parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                ULONG                       uValue
                The updated ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        ULONG                       uValue
    )
{
    if (AnscEqualString(pParamName, "TestSampleParamUlong", TRUE))
    {
		TestSampleParamUlongValue = uValue;
		return TRUE;
    }
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

        BOOL
        TestComponent_SetParamIntValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       pParamName,
                int                         iValue
            );

    description:

        This function is called to set integer parameter value; 

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       pParamName,
                The parameter name;

                int                         iValue
                The updated integer value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
TestComponent_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        int                         iValue
    )
{
    return FALSE;
}

/**********************************************************************  

    caller:     owner of this object 

    prototype: 

       ULONG
       TestComponent_Commit
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to finally commit all the update.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/
ULONG
TestComponent_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
   
    return 0;
}


/***********************************************************************

 APIs for Object:

    X_RDKCENTRAL-COM_XDNS.TestTable.{i}.

    *  TestTable_GetEntryCount
    *  TestTable_GetEntry
    *  TestTable_IsUpdated
    *  TestTable_Synchronize
    *  TestTable_AddEntry
    *  TestTable_DelEntry
    *  TestTable_GetParamStringValue
    *  TestTable_SetParamStringValue
    *  TestTable_Validate
    *  TestTable_Commit
    *  TestTable_Rollback

***********************************************************************/

typedef  struct
_COSA_DML_TESTCOMPONENT_TEST_TABLE
{
    char TableTestString[256];
}
COSA_DML_TESTCOMPONENT_TEST_TABLE, *PCOSA_DML_TESTCOMPONENT_TEST_TABLE;

/* Collection */
typedef  struct
_COSA_DML_TESTCOMPONENT
{
    UINT TestSampleParamUlong;
    char *MyString; 
    PCOSA_DML_TESTCOMPONENT_TEST_TABLE  Test_Tables;
    UINT TestTableNumberOfEntries;
}
COSA_DML_TESTCOMPONENT, *PCOSA_DML_TESTCOMPONENT;

COSA_DML_TESTCOMPONENT_TEST_TABLE table[120];

ULONG
TestTable_GetEntryCount
    (
        ANSC_HANDLE hInsContext
    )

{
    PCOSA_CONTEXT_LINK_OBJECT       pLinkObj     = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    PCOSA_DML_TESTCOMPONENT               p      = (PCOSA_DML_TESTCOMPONENT        )pLinkObj->hContext;
       
    return 120;
}

ANSC_HANDLE
TestTable_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    *pInsNumber  = nIndex + 1; 
    return table+nIndex;
}

BOOL
TestTable_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    )
{
    return TRUE;
}

ULONG
TestTable_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    )
{
    PCOSA_CONTEXT_LINK_OBJECT       pLinkObj     = (PCOSA_CONTEXT_LINK_OBJECT     )hInsContext;
    PCOSA_DML_TESTCOMPONENT         p            = (PCOSA_DML_TESTCOMPONENT       )pLinkObj->hContext;

    /*release data allocated previous time*/
    // if (p->TestTableNumberOfEntries)
    // {
    //     AnscFreeMemory(p->Test_Tables);
    //     p->Test_Tables = NULL;
    //     p->TestTableNumberOfEntries = 0;
    // }
    
    // p->Test_Tables = table;
    // p->TestTableNumberOfEntries = 120;

    return ANSC_STATUS_SUCCESS;
}

ULONG
TestTable_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )

{
    PCOSA_DML_TESTCOMPONENT_TEST_TABLE  p   = (PCOSA_DML_TESTCOMPONENT_TEST_TABLE)hInsContext;

    if( AnscEqualString(ParamName, "TableTestString", TRUE))
	{
		*pUlSize = strlen(p->TableTestString);

		if (strcpy(pValue, p->TableTestString))
			return TRUE;
		return FALSE;
	}

    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}


BOOL
TestTable_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    )

{
    PCOSA_DML_TESTCOMPONENT_TEST_TABLE  p   = (PCOSA_DML_TESTCOMPONENT_TEST_TABLE)hInsContext;

	if( AnscEqualString(ParamName, "TableTestString", TRUE))
	{
        if (!strcmp(strValue, "error"))
            return FALSE;

		if (strcpy(p->TableTestString, strValue))
			return TRUE;
		return FALSE;
	}


    return FALSE;
}
