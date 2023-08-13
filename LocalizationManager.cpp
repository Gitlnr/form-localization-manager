//-------------------------------------------------------------------------------------------------------------------------------
// Localization Functions
// Author: Rahul
// Description: This source file contains functions for localizing the "Caption," "Text," "Items," "Lines," and "Hint"
//              properties of various components on a form based on target languages and localization data.
//-------------------------------------------------------------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "LocalizationManager.h"
//-------------------------------------------------------------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMyPage *MyPage;
//-------------------------------------------------------------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
//-------------------------------------------------------------------------------------------------------------------------
//@@@
// Constructor: TMyPage::TMyPage
// Description: Constructor for the TMyPage class
// Parameters:  Owner -The owner component for the form
//@@@
//-------------------------------------------------------------------------------------------------------------------------

__fastcall TMyPage::TMyPage(TComponent* Owner)
	: TForm(Owner)
{
	//:::Get the path of the current executable:::
	String filename = ParamStr(0);
	String filepath = ExtractFilePath(filename);

	//:::Read localization data for "Caption" and "Text" properties:::
	String src1 = filepath + "\\Localize\\Caption&Text.txt";
	ReadTranslationData(src1, localizationData_C_T);

	//:::Read localization data for "Items" and "Lines" properties:::
	String src2 = filepath + "\\Localize\\Items&Lines.txt";
	ReadTranslationData(src2, localizationData_I_L);

	//:::Read localization data for "Hint" properties:::
	String src3 = filepath + "\\Localize\\Hint.txt";
	ReadTranslationData(src3, localizationData_H);

}

//-------------------------------------------------------------------------------------------------------------------------------
//@@@
// Note: This function performs localization for the "Caption" and "Text" property of various components on a form.
//@@@
//-------------------------------------------------------------------------------------------------------------------------------

void TMyPage::LocalizeComponentCaptionAndText(TForm* formToLocalize, const String& targetLanguage,
									 map<String, map<String, String>>& localizationData_C_T)
{
	//::::Iterate through each component on the form::::
	for (int i = 0; i < formToLocalize->ComponentCount; i++)
	{
		//::::Get the name of the current component::::
		String componentName = formToLocalize->Components[i]->Name;

		//::::Iterator for the localization data map::::
		auto componentLocalization = localizationData_C_T.find(formToLocalize->Name + "_" + componentName);

		//::::If the component's localization data is found::::
		if (componentLocalization != localizationData_C_T.end())
		{
			auto languageData = componentLocalization->second.find(targetLanguage);

			//::::If the target language data is found::::
            if (languageData != componentLocalization->second.end())
			{
				//::::Check if "Caption" is a published property and localize it::::
				if (IsPublishedProp(formToLocalize->Components[i], L"Caption"))
                {
					//::::Set the localized value for the "Caption" property::::
                    SetPropValue(formToLocalize->Components[i], L"Caption", languageData->second);
                }

				//::::Check if "Text" is a published property and localize it::::
                if (IsPublishedProp(formToLocalize->Components[i], L"Text"))
                {
					//::::Set the localized value for the "Text" property::::
					SetPropValue(formToLocalize->Components[i], L"Text", languageData->second);
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
//@@@
// Note: This function performs localization for the "Items" and "Lines" property of various components on a form.
//@@@
//-------------------------------------------------------------------------------------------------------------------------------

void TMyPage::LocalizeComponentItemsAndLines(TForm* formToLocalize, const String& targetLanguage, map<String,
									map<String, map<String, String>>>& localizationData_I_L)
{
	//::::Iterate through each component on the form::::
    for (int i = 0; i < formToLocalize->ComponentCount; i++)
	{
		String componentName = formToLocalize->Components[i]->Name;

		//::::Iterator for the outermost level of localization  data map::::
        auto componentlocalization = localizationData_I_L.find(formToLocalize->Name + "_" + componentName);

		//::::If the components localization data is found::::
        if (componentlocalization != localizationData_I_L.end())
        {
			auto classlocalization = componentlocalization->second.find(formToLocalize->Components[i]->ClassName());

			//::::If the components class localization is found::::
            if (classlocalization != componentlocalization->second.end())
            {
                auto languageData = classlocalization->second.find(targetLanguage);

				//::::If the target language data is found::::
                if (languageData != classlocalization->second.end())
				{
					//::::Localize "Lines" property of TMemo components::::
					if (IsPublishedProp(formToLocalize->Components[i], L"Lines"))
					{
                        if (TMemo* memoComponent = dynamic_cast<TMemo*>(formToLocalize->Components[i]))
                        {
                            memoComponent->Lines->Text = languageData->second;
                        }
                    }

					//::::Localize "Items" property of specific components below::::
                    if (IsPublishedProp(formToLocalize->Components[i], L"Items"))
                    {
                        if (TRadioGroup* radioGroup = dynamic_cast<TRadioGroup*>(formToLocalize->Components[i]))
                        {
							radioGroup->Items->Text = languageData->second;
                        }
                        else if (TListBox* listBox = dynamic_cast<TListBox*>(formToLocalize->Components[i]))
                        {
                            listBox->Items->Text = languageData->second;
                        }
						else if (TComboBox* comboBox = dynamic_cast<TComboBox*>(formToLocalize->Components[i]))
                        {
                            comboBox->Items->Text = languageData->second;
                        }
                        else if (TCheckListBox* checkListBox = dynamic_cast<TCheckListBox*>(formToLocalize->Components[i]))
                        {
							checkListBox->Items->Text = languageData->second;
                        }
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
//@@@
// Note: This function performs localization for the "Hint" property of various components on a form.
//@@@
//-------------------------------------------------------------------------------------------------------------------------------

void TMyPage::LocalizeHint(TForm* formToLocalize, String targetLanguage, map<String, map<String,
				  String>>& localizationData_H)
{
    String hintSuffix = "_Hint";

	//::::Iterate through each component on the form::::
	for (int i = 0; i < formToLocalize->ComponentCount; i++)
    {
        String componentName = formToLocalize->Components[i]->Name;

		//::::Iterator for the outermost level of localization data map::::
		auto componentlocalization = localizationData_H.find(formToLocalize->Name + "_" + componentName + hintSuffix);

		//::::If the components hint localization  data is found::::
		if (componentlocalization!= localizationData_H.end())
        {
			auto languageData = componentlocalization->second.find(targetLanguage);

			//::::If the target language data is found::::
            if (languageData != componentlocalization->second.end())
			{
				//::::Check if "Hint" is a published property and localize it::::
				if (IsPublishedProp(formToLocalize->Components[i], L"Hint"))
				{
					TControl* control = dynamic_cast<TControl*>(formToLocalize->Components[i]);

					if (control != NULL)
					{
						control->Hint = languageData->second;
					}
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//@@@
// NOte:This is a Function to read localization data from a file
//@@@
//---------------------------------------------------------------------------------------------------------------------------

void TMyPage::ReadTranslationData(const String& filePath,map<String, map<String,
						 String>>& finallocalizationData)
{
    fstream myFile;
	myFile.open(filePath.c_str(), ios::in | ios::app);

    string buf;

    while (getline(myFile, buf))
    {
		fixNewline(buf);

		//:::Convert the UTF-8 string to a UnicodeString:::
		int linesize = buf.length();
		UTF8String utf8Str(buf.c_str(), linesize);
		UnicodeString unicodeStr = utf8Str;

		//:::Create a new TStringList to store and manipulate the delimited data:::
		TStringList* lst = new TStringList();
        lst->StrictDelimiter = true;
        lst->Delimiter = L',';
        lst->DelimitedText = unicodeStr;

        String a1 = lst->Strings[0];
        String a2 = lst->Strings[1];
        String a3 = lst->Strings[2);

        if (lst->Count > 3)
        {
			String a4 = lst->Strings[3];

			//:::Assuming this is for localizationData_I_L:::
			finallocalizationData[a1][a2][a3] = a4;
        }
        else
		{
		   //:::Assuming this is for localizationData_C_T and localizationData_H:::
			finallocalizationData[a1][a2] = a3;
        }

        delete lst;
    }

    myFile.close();
}
//------------------------------------------------------------------------------------------------------------------------
//Note: Function to replace "\\n" with actual newline characters ("\n") in a given string
//@@@
//------------------------------------------------------------------------------------------------------------------------

 void __fastcall TMyPage::fixNewline(string& buf)
{
	size_t start_pos = 0;
	 while ((start_pos = buf.find("\\n", start_pos)) != string::npos)
	{
		buf.replace(start_pos, 2, "\n");
		start_pos += 1;
	}

}

//---------------------------------------------------------------------------------------------------------------------------
//@@@
// Event Handler: TMyPage::ComboBoxToSelectLangChange
// Description: Handles the change event of the language selection combo box.
// Parameters:  Sender -  object that triggered the the combo box
//@@@
//----------------------------------------------------------------------------------------------------------------------------

void __fastcall TMyPage::ComboBoxToSelectLangChange(TObject *Sender)
{
	//:::Localize component captions and text of Form"MyPage" based on selected language from the combox :::
	LocalizeComponentCaptionAndText(MyPage,ComboBoxToSelectLang->Text, localizationData_C_T);

	//:::Localize component items and lines of Form"MyPage" based on selected language from the combox:::
	LocalizeComponentItemsAndLines(MyPage,ComboBoxToSelectLang->Text, localizationData_I_L);

	//:::Localize hint text of Form"MyPage" based on selected language from the combox:::
	LocalizeHint(MyPage,ComboBoxToSelectLang->Text, localizationData_H);
}
//------------------------------------------------------------------------------------------------------------------------------
