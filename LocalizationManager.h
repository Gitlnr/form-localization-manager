//---------------------------------------------------------------------------
#ifndef LocalizationManagerH
#define LocalizationManagerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <string>
#include <map>
#include<fstream>
using namespace std;
//---------------------------------------------------------------------------
class TMyPage : public TForm
{
__published:
	TComboBox *ComboBoxToSelectLang;
	void __fastcall ComboBoxToSelectLangChange(TObject *Sender);

private:
	void LocalizeComponentCaptionAndText(TForm* formToLocalize, const String& targetLanguage,map<String, map<String, String>>& localizationData_C_T);
	void LocalizeComponentItemsAndLines(TForm* formToLocalize, const String& targetLanguage,map<String,map<String,map<String, String>>>& localizationData_I_L);
	void LocalizeHint(TForm* formToLocalize, String targetLanguage, map<String,map<String, String>>& localizationData_H);
	void ReadTranslationData(const String& filePath, map<String, map<String, String>>& finallocalizationData);
	void __fastcall fixNewline(string& buf);

public:
	__fastcall TMyPage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyPage *MyPage;
//---------------------------------------------------------------------------
#endif
