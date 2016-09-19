
#ifndef GComp_H
#define GComp_H

#include <afx.h>

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GCOMPDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GCOMPDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef GCOMPDLL_EXPORTS
#define GCOMPDLL_API __declspec(dllexport)
#else
#define GCOMPDLL_API __declspec(dllimport)
#endif



#ifndef BOOL
typedef int BOOL;
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

enum TCompoundTypes {
	by_extension = 0, //Do not use this when call DLL functions
	external_report = 1,
	meta_data = 2
};
enum TGComp_Languages {
	lang_Rus = 0,
	lang_Eng = 1,
	lang_Translit = 2
};
enum TLogType {
	LogType_stdout = 0,
	LogType_file = 1,
	LogType_ListBox = 2
};

//��� ���������� ��������� � wParam
enum TInfoMessageType {
	InfoMsg_Start = 0,
	InfoMsg_Stop = 1,
	InfoMsg_Total = 2,   //� lParam ��������� ����� ���������� ��������
	InfoMsg_Progress = 3 //� lParam ��������� ���������� ������������ ��������
};


struct CGCompParameters
{
	char* CompoundFileName;
	char* DirectoryName;

	TCompoundTypes CompoundType;
	TGComp_Languages Language;
	
	// -1 - supress all messagess (quiet mode)
	// 0 - errors only
	// 1 - real deeds, if any
	// 2 - all together, checks included.
	// (maybe enum?)
	int Verbose;
	TLogType LogType;
	HWND hwndLog;

	BOOL NoOrdering;
	BOOL NoProfiles;
	BOOL NoEmptyMxl;
	BOOL TruncateMMS;
	BOOL NotParseForms; //���������� ����� ����� ��������� AsIs
	BOOL NoDefaults; //don't use default values when extracting objects in beauty strings
	BOOL SaveVersion; //save gcomp's version into file gcomp.ver
	BOOL NoEmptyFolders;

	BOOL MetadataBySubfolders;

	//���� �� NULL, �� ��� ������ ������� ��� ��������/��������. 
	//��������:
	//   ����������\����������
	//   ����������\����������\�����������
	//   ����������\*\�����������
	char* MetadataPath;

	BOOL SaveWholeMMS; //�������� ������ �� ������������. �������� ��� �������������
	BOOL SortUserRightsObjects;
	BOOL SortFormControls;

	//progress reporter parameters
	HWND hwndInfoReceiver;
	UINT InfoMessage;

	//���� ������� ������� ��������� ��� ���������� � TRUE, �� � ������
	//�������� ��������������� ��������� ������ gcomp.dll ����� ��������
	BOOL volatile CancelWork;

	BOOL NoBrokenLinks; // �� ��������� ������� ���� � �����������, ����������� �� ������������� ����������

	BOOL MakeUserRightsInOneFile; // ��������� ������ csv ���� �� ����� ������� ����� (��� ���������� ������������)
};

extern "C" {
	GCOMPDLL_API const char* GComp_GetVersion();

	//��������� ��������� CGCompParameters ���������� �� ���������
	GCOMPDLL_API void GComp_SetDefaults(CGCompParameters* Parameters);
	//�������� ������� ��������� �� �����. ��� ������� ������� �������� 
	//����� ������� ��������� ������, ����� ��������� �� ����� �������� 
	//��������� ��������� ������, �������� �� ������ ������� ������.
	//���� ���������� (gcomp.ini) ������ � �������� Parameters->DirectoryName
	GCOMPDLL_API void GComp_ReadSettings(CGCompParameters* Parameters);
	//��������� ���������, �������� �� ������, � gcomp.ini
	GCOMPDLL_API void GComp_SaveSettings(CGCompParameters* Parameters);

	GCOMPDLL_API BOOL GComp_Decompile(CGCompParameters* Parameters);
	GCOMPDLL_API BOOL GComp_Compile(CGCompParameters* Parameters);

	//������� ��� ���������� ������������ ���������� ����
	GCOMPDLL_API BOOL GComp_ParseMainMetadataStream(LPCSTR fname, HWND hLogWnd);
	GCOMPDLL_API BOOL GComp_DecompileDialogForm(LPCSTR dest_fname, LPCSTR src_fname, int nObjectID);
	GCOMPDLL_API BOOL GComp_ReadObjectNameCache(LPCSTR fname, HWND hLogWnd);
	GCOMPDLL_API BOOL GComp_CompileDialogForm(LPCSTR dest_fname, LPCSTR src_fname);
	GCOMPDLL_API BOOL GComp_AssembleMainMetadataStream(LPCSTR szDir, LPCSTR szDestFileName);

	//����������� ��� ������� � ����
	GCOMPDLL_API BOOL GComp_MakeNamePath(LPCTSTR srcDir, 
		BOOL translite, 
		LPTSTR objName,
		int buffsize);
}

#endif