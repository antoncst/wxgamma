#pragma once
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <wx/wx.h>
#include <map>

#define NARROW_BUT_WIDTH 120 
#define NARROW_BUT_HEIGHT 15
#define SMALL_BUT_WIDTH 27
#define SMALL_BUT_HEIGHT 27
#define SPACE_WIDTH 4
#define IMAGE_WIDTH 100
#define IMAGE_HEIGHT 100
#define FRAME_WIDTH NARROW_BUT_WIDTH + IMAGE_WIDTH + SPACE_WIDTH*4
#define FRAME_HEIGHT 400

const wxString gamma_file_extension = ".gm" ;

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame: public wxFrame //наследуемся от wxFrame
{
public:
	MyFrame(wxWindow* parent, wxString title = wxT("Simple App"), wxSize wxsize = wxDefaultSize); //Объявляем конструктор

//	void OnAbout(wxCommandEvent &event);	//объявляем
//	void OnQuit(wxCommandEvent &event);	//обработчики
//	void OnSave(wxCommandEvent &event);	//событий
//	void OnLoad(wxCommandEvent &event);	//
//	void OnSize(wxSizeEvent &event);	//
	void OnBtnEncrypt( wxCommandEvent &event ) ;	//
	void OnBtnDecrypt( wxCommandEvent &event ) ;	//
	void OnBtnSrcFileDlg( wxCommandEvent &event ) ;	//
	void OnChkbxKeyFile( wxCommandEvent &event ) ;
	void OnTxtctrlFilename( wxFocusEvent & event ) ;
	
	bool ExecGammaPipe( char ** argv ) ;
//	void OnButtonV2(wxCommandEvent &event);	//

private:
	std::map< wxString , wxString > m_labels_map ;
	char * margv[30] ;
	int mcurr_index_argv ;
	//wxString mSrcFileName ;
	
	void PrintCommand( int n ) ;
	void ParseLabelsLang() ;
	void SaveParameters() ;
	void LoadParameters() ;
	
	wxTextCtrl *m_txt;
//	wxListBox *m_lstList;

	// saved parameters:
	wxTextCtrl * m_FileName ;
	wxTextCtrl * m_Password ;
	wxCheckBox *m_chkBox_Keyfile;
	
	
	DECLARE_EVENT_TABLE()	//Макрос, необходимый для связывания событий и обработчиков
};

enum {
    ID_BTN_ENCRYPT  = 108,
	ID_BTN_DECRYPT ,
	ID_BTN_SRC_FILEDLG ,
	ID_BTN_ENC_FILEDLG ,
	ID_CHKBX_KEYFILE ,
	ID_TXTCTRL_FILENAME ,
    ID_LIST
};

