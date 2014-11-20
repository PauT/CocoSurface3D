#include "platform/CSDevice.h"
USING_NS_CC;
NS_CS_BEGIN
std::string CSDevice::openFileDialog()
{
	char szFileName[MAX_PATH] = "";

	OPENFILENAME file = { 0 };
	file.lStructSize = sizeof(file);
	file.hwndOwner = Director::getInstance()->getOpenGLView()->getWin32Window();
	file.lpstrFile = (LPWSTR)szFileName;
	file.nMaxFile = MAX_PATH;
	file.lpstrFileTitle = (LPWSTR)"hahahah";
	file.nFilterIndex = 1;//默认选择第一个
	file.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	file.lStructSize       = sizeof (OPENFILENAME) ;  
	//file.hwndOwner         = hwnd ;  
	file.hInstance         = NULL ;  
	file.lpstrFilter       = NULL ;  
	file.lpstrCustomFilter = NULL ;  
	file.nMaxCustFilter    = 0 ;  
	file.nFilterIndex      = 0 ;  
	//file.lpstrFile         = NULL ;          // Set in Open and Close functions  
	file.nMaxFile          = MAX_PATH ;  
	file.lpstrFileTitle    = NULL ;          // Set in Open and Close functions  
	file.nMaxFileTitle     = MAX_PATH ;  
	file.lpstrInitialDir   = NULL ;  
	file.lpstrTitle        = NULL ;  
	file.Flags             = 0 ;             // Set in Open and Close functions  
	file.nFileOffset       = 0 ;  
	file.nFileExtension    = 0 ;  
	file.lpstrDefExt       = NULL;  
	file.lCustData         = 0L ;  
	file.lpfnHook          = NULL ;  
	file.lpTemplateName    = NULL ;  
	

	// 弹出打开文件的对话框
	if(::GetOpenFileName(&file))
	{
		//::SetWindowText(::GetDlgItem(hDlg, IDC_FILE), szFileName);
		int nLen = WideCharToMultiByte(CP_ACP, 0, file.lpstrFile, -1, NULL, 0, NULL, NULL);

		if (nLen<= 0) return std::string("");

		char* pszDst = new char[nLen];
		if (NULL == pszDst) return std::string("");

		WideCharToMultiByte(CP_ACP, 0, file.lpstrFile, -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen -1] = 0;

		std::string strTemp(pszDst);
		delete [] pszDst;

		return strTemp;
	}
	return "";
}
NS_CS_END