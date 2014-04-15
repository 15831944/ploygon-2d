#include <string>

 
#include <ObjBase.h>
 

using namespace std;

namespace guid
{
	string createGuid()
	{
		char buffer[128] = {0};
		GUID _guid;
		CoInitialize(NULL);

		if(S_OK == CoCreateGuid(&_guid))
		{
			sprintf(buffer,"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",_guid.Data1,_guid.Data2,_guid.Data3,_guid.Data4[0],_guid.Data4[1],_guid.Data4[2],_guid.Data4[3],_guid.Data4[4],_guid.Data4[5],_guid.Data4[6],_guid.Data4[7]);	
		}
		 
		CoUninitialize();
		return buffer;
	}
}