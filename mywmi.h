#include <vector>
#include <string>
#using < system.management.dll>
using namespace std;
using namespace System;
using namespace System::Management; 


void MarshalString ( String ^ s, string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString ( String ^ s, wstring& os ) {
   using namespace Runtime::InteropServices;
   const wchar_t* chars = 
      (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}


ManagementObjectCollection::ManagementObjectEnumerator^ mywmi(String^ q)
{
	ConnectionOptions^ options = gcnew ConnectionOptions();
	//options->Password = L"";
	//options->Username = L"";
    //options->Authority = "NTLMDomain:";
    options->Impersonation = ImpersonationLevel::Impersonate;
   
	ManagementScope^ scope = gcnew ManagementScope("\\\\localhost\\root\\CIMV2",options);
    SelectQuery^ processorquery = gcnew SelectQuery(q);
   
	ManagementObjectSearcher^ query = gcnew ManagementObjectSearcher(scope, processorquery);
    ManagementObjectCollection^ resultcollection = query->Get();
    ManagementObjectCollection::ManagementObjectEnumerator^ enu = resultcollection->GetEnumerator();

	return enu;
} 