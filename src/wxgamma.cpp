#include "wxgamma.h"
#include "wxgamma.h"
#include <iostream> 
#include <cstring>
#include <cstdio>
#include "wxImagePanel.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/utils.h> 
#include <wx/filedlg.h>

#include "../../platform.h"

#ifdef LINUX
#include "pipe_posix.cpp"
#endif

const wxString frame_caption = _T("gamma") ;

void MyFrame::ParseLabelsLang()
{
	wxFileInputStream input( wxT("../labels.lng") ) ;
	wxTextInputStream text( input , wxT("\x09"), wxConvUTF8 ) ;
	while(input.IsOk() && !input.Eof() )
	{
		wxString line = text.ReadLine() ;
		wxArrayString arr( wxSplit( line , wxChar('\t') ) ) ;
		if (arr.Count() >= 2)
		{
			m_labels_map[ arr[0] ] =  arr[1]  ; //wxString::FromUTF8
		}
	}
	
}

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
/*	wxFrame *frame = new wxFrame((wxFrame *)NULL, -1, "Hello World",
		wxPoint(50, 50), wxSize(450, 340));

	wxPanel *MainPanel = new wxPanel(frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer *VFrameMain = new wxBoxSizer(wxVERTICAL);
	wxTextCtrl * m_txt = new wxTextCtrl(MainPanel, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);	frame->Show(TRUE);
	
	return TRUE;
*/
	wxSize wxsize( FRAME_WIDTH , FRAME_HEIGHT ) ;
		
	MyFrame *frame = new MyFrame(NULL, frame_caption, wxsize ) ;//, wxDefaultPosition, wxSize(400.600 );	//Создаём главное окно программы
	//MyFrame *frame1 = new MyFrame(frame, wxT("Frame1"));	//Создаём
	//MyFrame *frame2 = new MyFrame(frame, wxT("Frame2"));	//вспомогательные окна

/*	frame2->Connect(wxID_EXIT,	// идентификатор элемента, от которого ожидается событие
		wxEVT_COMMAND_BUTTON_CLICKED, // тип события
		wxCommandEventHandler(MyFrame::OnQuit), // функция-обработчик
		NULL, // пользовательские данные
		frame1 // истачник события
	);
*/
	frame->Show(true);			//отображаем
	//frame1->Show(true);			//фреймы
	//frame2->Show(true);			//на экране
	return true; //Return true to continue processing, false to exit the application immediately.
}



MyFrame::MyFrame(wxWindow *parent, wxString title, wxSize wxsize ) //реализация конструктора
	: wxFrame(parent,
		wxID_ANY, //присвоить идентификатор автоматически
		title, //заголовок окна
		wxDefaultPosition, //не указывать расположение окна
		wxsize ) //не указывать размер окна
{
/*	wxMenu *file_menu = new wxMenu();	//Создаём
	wxMenu *about_menu = new wxMenu();	//меню
	file_menu->Append(wxID_ANY, _T("&Test\tAlt-T"), _T("Test"));	//Создаём пункты меню
	file_menu->Append(wxID_EXIT);					//Стандартные идентификаторы обладают забавным свойством - 
	about_menu->Append(wxID_ABOUT);					//они могут заполнять некоторые поля значениями по-умолчанию
*/
/*	wxMenuBar *menu_bar = new wxMenuBar(); //создаём менюбар
	menu_bar->Append(file_menu, wxT("&File"));	//добавляем
	menu_bar->Append(about_menu, wxT("&Help"));	//меню в менюбар
	SetMenuBar( menu_bar ); //Устанавливаем созданный менюбар в качестве менюбара данного фрейма
*/
	ParseLabelsLang() ;

	wxInitAllImageHandlers();
	
//	int bar_tmp[4];
//	bar_tmp[0] = -1; //Размер первого поля будет высчитываться автоматически
//	bar_tmp[1] = 50;
//	bar_tmp[2] = 100;
//	bar_tmp[3] = 150;
	CreateStatusBar(1); //Создаём статусбар
	//SetStatusWidths(4, bar_tmp); //выставляем ширины разделов
	SetStatusText(_T("Status bar"), 0); //текст надписи в первом поле
	//SetStatusText(_T("StatBar"), 1); //текст надписи во втором поле

/*	wxStatusBar *barStatus = GetStatusBar(); //Для более сложных манипуляций со статусбаром требуется прямой доступ к его объекту
	bar_tmp[0] = wxSB_FLAT;		//Плоский
	bar_tmp[1] = wxSB_NORMAL;	//Обычный (вдавленный)
	bar_tmp[2] = wxSB_RAISED;	//Выпуклый
	bar_tmp[3] = wxSB_NORMAL;
	barStatus->SetStatusStyles(4, bar_tmp); //устанавливаем стили полей
*/

// Создаём панель и сайзеры
	wxPanel *MainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer *VFrameMain = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *HFrameHead = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *VFrameHead = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *HFrameFile = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *HFramePsw = new wxBoxSizer(wxHORIZONTAL);
//	wxBoxSizer *HFrameBtns1 = new wxBoxSizer(wxHORIZONTAL);

//	wxStaticBoxSizer *VFrameControls1 = new wxStaticBoxSizer(wxVERTICAL, MainPanel, _T("Group 1")); //тот же BoxSizer
//	wxStaticBoxSizer *VFrameHead = new wxStaticBoxSizer(wxVERTICAL, MainPanel, _T("Group 2")); //только с рамочкой

	m_chkBox_Keyfile = new wxCheckBox( MainPanel, ID_CHKBX_KEYFILE , m_labels_map[_T( "CHKBX_KEYFILE" ) ] ) ; 

// Создаём контролы
	//wxSize wxsize2( FRAME_WIDTH - SPACE_WIDTH*2 , 200 ) ;
	//wxsize2.SetHeight( 100 ) ;
	m_txt = new wxTextCtrl( MainPanel, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_FileName = new wxTextCtrl( MainPanel, ID_TXTCTRL_FILENAME , _T("") , wxDefaultPosition, wxDefaultSize , 0 ) ;
	m_FileName->Connect( wxEVT_KILL_FOCUS,wxFocusEventHandler( MyFrame::OnTxtctrlFilename ) , NULL , this ) ;

	m_Password = new wxTextCtrl( MainPanel, wxID_ANY , _T("") , wxDefaultPosition, wxDefaultSize , wxTE_PASSWORD ) ;
//	m_lstList = new wxListBox(MainPanel, ID_LIST);
//	wxButton *butExit = new wxButton(MainPanel, wxID_EXIT, _T("Выход"));
	wxStaticText *txtFile = new wxStaticText( MainPanel, wxID_ANY, m_labels_map[_T( "TEXT_FILE" ) ] ) ;
	wxStaticText *txtPsw = new wxStaticText( MainPanel, wxID_ANY, m_labels_map[_T( "TEXT_PSW" ) ] ) ;
	wxButton *btnEncrypt = new wxButton(MainPanel, ID_BTN_ENCRYPT, m_labels_map[_T( "BUT_ENCRYPT_TX" ) ] ) ;
	wxButton *btnSrcFileDlg = new wxButton(MainPanel, ID_BTN_SRC_FILEDLG , _T( "..." ) , wxDefaultPosition, wxSize( SMALL_BUT_WIDTH, SMALL_BUT_HEIGHT ) ) ;
	btnSrcFileDlg->SetToolTip( m_labels_map[_T( "BUT_SRCFILEDLG_TOOLTIP" ) ] ) ;
	wxButton *btnDecrypt = new wxButton(MainPanel, ID_BTN_DECRYPT, m_labels_map[_T( "BUT_DECRYPT_TX" ) ] ) ;
	wxButton *butBut1 = new wxButton(MainPanel, wxID_ANY , wxEmptyString,wxDefaultPosition, wxSize( NARROW_BUT_WIDTH, NARROW_BUT_HEIGHT ) ) ;
	wxButton *butBut2 = new wxButton(MainPanel, wxID_ANY , wxEmptyString,wxDefaultPosition, wxSize( NARROW_BUT_WIDTH, NARROW_BUT_HEIGHT ) ) ;
	wxButton *butBut3 = new wxButton(MainPanel, wxID_ANY , wxEmptyString,wxDefaultPosition, wxSize( NARROW_BUT_WIDTH, NARROW_BUT_HEIGHT ) ) ;
/*	wxRadioButton *rdbRadio1 = new wxRadioButton(MainPanel, wxID_ANY, _T("Радиокнопка 1"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	wxRadioButton *rdbRadio2 = new wxRadioButton(MainPanel, wxID_ANY, _T("Радиокнопка 2"));
	wxRadioButton *rdbRadio3 = new wxRadioButton(MainPanel, wxID_ANY, _T("Радиокнопка 3"));
	wxRadioButton *rdbRadio4 = new wxRadioButton(MainPanel, wxID_ANY, _T("Радиокнопка 4"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	wxRadioButton *rdbRadio5 = new wxRadioButton(MainPanel, wxID_ANY, _T("Радиокнопка 5"));
	wxRadioButton *rdbRadio6 = new wxRadioButton(MainPanel, wxID_ANY, _T("Радиокнопка 6"));
	rdbRadio6->SetValue(true);
*/

	LoadParameters() ;
	
	MainPanel->SetSizer( VFrameMain ); //Устанавливаем сайзер верхнего уровня


	VFrameMain->Add(
		HFrameHead, // элемент, который добавляем
		0, //Пропорция (0 => размер ячейки определяется её содержимым)
		wxEXPAND); //Флаги (wxEXPAND => максимально растягивать содержимое по размеру ячейки)

	HFrameHead->Add(
		VFrameHead,
		0,
		wxEXPAND);

	VFrameHead->Add(
		butBut1,
		0,
		wxALL | wxEXPAND | wxBU_NOTEXT ,//wxALL | wxEXPAND, // Флаги (wxALL => делать отступ от всех границ содержимого)
		SPACE_WIDTH); //величина отступа

	VFrameHead->Add(
		butBut2,
		0,
		wxALL | wxEXPAND | wxBU_NOTEXT ,//wxALL | wxEXPAND, // Флаги (wxALL => делать отступ от всех границ содержимого)
		SPACE_WIDTH ) ; //величина отступа

	VFrameHead->Add(
		butBut3,
		0,
		wxALL | wxEXPAND | wxBU_NOTEXT ,//wxALL | wxEXPAND, // Флаги (wxALL => делать отступ от всех границ содержимого)
		SPACE_WIDTH); //величина отступа

	wxImagePanel * drawPane = new wxImagePanel( MainPanel, wxT("logo.jpg"), wxBITMAP_TYPE_JPEG);
	HFrameHead->Add(
		drawPane,
		1,
		wxALL | wxEXPAND  //wxALL | wxEXPAND, // Флаги (wxALL => делать отступ от всех границ содержимого)
		, SPACE_WIDTH ); //величина отступа

            //sizer->Add(drawPane, 1, wxEXPAND);
		
	VFrameMain->Add(
		HFrameFile, // элемент, который добавляем
		0, //Пропорция (0 => размер ячейки определяется её содержимым)
		wxALL | wxEXPAND); //Флаги (wxEXPAND => максимально растягивать содержимое по размеру ячейки)

	HFrameFile->Add(
		txtFile, // элемент, который добавляем
		0 //Пропорция (0 => размер ячейки определяется её содержимым)
		, wxALIGN_CENTER_VERTICAL | wxALL
		, SPACE_WIDTH ); //Флаги (wxEXPAND => максимально растягивать содержимое по размеру ячейки)

	HFrameFile->Add(
		m_FileName,
		1, //Пропорция (1 => занимаем всё свободное место)
		 wxALL | wxEXPAND
		, SPACE_WIDTH );

	HFrameFile->Add(
		btnSrcFileDlg,
		0,
		wxEXPAND | wxALL, // Флаги (wxALL => делать отступ от всех границ содержимого)
		SPACE_WIDTH); //величина отступа

	VFrameMain->Add(
		HFramePsw, // элемент, который добавляем
		0, //Пропорция (0 => размер ячейки определяется её содержимым)
		wxALL | wxEXPAND); //Флаги (wxEXPAND => максимально растягивать содержимое по размеру ячейки)


	HFramePsw->Add(
		txtPsw, // элемент, который добавляем
		0 //Пропорция (0 => размер ячейки определяется её содержимым)
		, wxALIGN_CENTER_VERTICAL | wxALL
		, SPACE_WIDTH ); //Флаги (wxEXPAND => максимально растягивать содержимое по размеру ячейки)

	HFramePsw->Add(
		m_Password,
		1, //Пропорция (1 => занимаем всё свободное место)
		 wxALL | wxEXPAND
		, SPACE_WIDTH );

	VFrameMain->Add(
		btnEncrypt,
		0,
		wxEXPAND | wxALL, // Флаги (wxALL => делать отступ от всех границ содержимого)
		SPACE_WIDTH); //величина отступа
		

	VFrameMain->Add(
		btnDecrypt,
		0,
		wxALL | wxEXPAND, // Флаги (wxALL => делать отступ от всех границ содержимого)
		SPACE_WIDTH); //величина отступа

	VFrameMain->Add(
		m_chkBox_Keyfile,
		0,
		wxALL | wxEXPAND);

	//m_txt->AppendText( wxString::Format(wxT("%i"), m_txt->GetSize().GetHeight()) ) ;
	VFrameMain->Add(
		m_txt,
		1, //Пропорция (1 => занимаем всё свободное место)
		 wxALL | wxEXPAND );

/*	HFrameHead->Add(
		butBut2,
		0,
		wxALL | wxEXPAND,
		4);
	HFrameHead->Add(
		butBut3,
		0,
		wxALL | wxEXPAND,
		4);
	HFrameHead->AddStretchSpacer();	// Разделитель (займёт всё свободное место)
	HFrameHead->Add(
		butExit,
		0,
		wxALL | wxEXPAND,
		4);
*//*	HFrameControls2->Add(
		m_lstList,
		2, // Ширина листбокса будет в два раза больше ширин радиобатонов
		wxALL | wxEXPAND,
		4);
*//*	HFrameControls2->Add(
		VFrameControls1,
		1, //Равнопропорционально разделять место между блоками радиобатонов
		wxALL | wxEXPAND,
		4);
	HFrameControls2->Add(
		VFrameHead,
		1, //Равнопропорционально разделять место между блоками радиобатонов
		wxALL | wxEXPAND,
		4);
*//*	VFrameControls1->Add(
		rdbRadio1,
		1,
		wxALL | wxALIGN_RIGHT,
		4);
	VFrameControls1->Add(
		rdbRadio2,
		2,
		wxALL | wxALIGN_CENTRE,
		4);
	VFrameControls1->Add(
		rdbRadio3,
		3,
		wxALL | wxALIGN_LEFT,
		4);
	VFrameHead->Add(
		rdbRadio4,
		3,
		wxALL | wxALIGN_LEFT,
		4);
	VFrameHead->Add(
		rdbRadio5,
		2,
		wxALL | wxALIGN_CENTRE,
		4);
	VFrameHead->Add(
		rdbRadio6,
		1,
		wxALL | wxALIGN_RIGHT,
		4);
*/
//	VFrameMain->SetSizeHints(this); //Фиксируем минимальный размер окна по данной компоновке.

	m_FileName->ShowPosition( m_FileName->GetValue().Length() ) ;

	MainPanel->Layout();	//Перерисовать окно
/*
	Connect(wxID_EXIT,	// идентификатор элемента, от которого ожидается событие
		wxEVT_COMMAND_BUTTON_CLICKED, // тип события
		wxCommandEventHandler(MyFrame::OnQuit) // функция-обработчик
		);
 либо так:
	Connect(wxID_EXIT,	// идентификатор элемента, от которого ожидается событие
		wxEVT_COMMAND_BUTTON_CLICKED, // тип события
		(wxObjectEventFunction)&MyFrame::OnQuit // функция-обработчик
		);
*/
	Connect( btnEncrypt->GetId(),	// идентификатор элемента, от которого ожидается событие
		wxEVT_COMMAND_BUTTON_CLICKED, // тип события
		wxCommandEventHandler(MyFrame::OnBtnEncrypt) // функция-обработчик
		);
	Connect( btnDecrypt->GetId(),	// идентификатор элемента, от которого ожидается событие
		wxEVT_COMMAND_BUTTON_CLICKED, // тип события
		wxCommandEventHandler(MyFrame::OnBtnDecrypt) // функция-обработчик
		);
//	Connect(butBut3->GetId(),	// идентификатор элемента, от которого ожидается событие
//		wxEVT_COMMAND_BUTTON_CLICKED, // тип события
//		wxCommandEventHandler(MyFrame::OnButtonV2) // функция-обработчик
//		);
}


void MyFrame::OnBtnSrcFileDlg( wxCommandEvent &event )
{
	wxFileDialog saveFileDialog( this , _("Open source data file"), "" , m_FileName->GetValue(),
                       "", wxFD_SAVE ); // | wxFD_OVERWRITE_PROMPT
    if ( saveFileDialog.ShowModal() == wxID_CANCEL )
		return ;     // the user changed idea...
	
	m_FileName->SetValue( saveFileDialog.GetPath() ) ;
	m_FileName->ShowPosition( m_FileName->GetValue().Length() ) ;
	m_txt->AppendText( _T("\nSource file: ")) ;
	m_txt->AppendText( m_FileName->GetValue() ) ;
	m_txt->AppendText( _T("\n")) ;

	SaveParameters() ;
}

void MyFrame::PrintCommand( int n )
{
	for ( int i = 0 ; i < n - 1 ; ++i )
	{
		// do not out password :
		if ( std::strcmp( margv[ i ] , "-p" ) == 0 )
		{
			i ++ ;
			continue ;
		}
		
		m_txt->AppendText( wxString( margv[ i ] ) ) ;
		m_txt->AppendText( _T(" ") ) ;
	}
	m_txt->AppendText( "\n") ;
}
	
void MyFrame::OnBtnEncrypt( wxCommandEvent &event )
{
	char c_psw[200] ;
	char c_filename1[500] ;
	char c_filename2[500] ;
	mcurr_index_argv = 0 ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( "gamma" ) ; ++mcurr_index_argv ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( "-f" ) ; ++mcurr_index_argv ;
	
	wxString spsw = "1234567890AB" ;
	if ( m_Password->GetValue() != _T("") ) 
		spsw = m_Password->GetValue() ;
	std::strcpy(  c_psw , spsw.ToStdString().c_str() ) ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( "-p" ) ; ++mcurr_index_argv ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( c_psw ) ; ++mcurr_index_argv ;
	
	if ( m_chkBox_Keyfile->GetValue() )
	{
		margv[ mcurr_index_argv ] = const_cast<char * const>( "-k" ) ; ++mcurr_index_argv ;
	}
		
	margv[ mcurr_index_argv ] = const_cast<char * const>( "-e" ) ; ++mcurr_index_argv ;
	if ( m_FileName->GetValue() != _T("") )
	{
		//Source file :
		wxString FileName = m_FileName->GetValue() ;
		// Does file exist
		FILE * fp = std::fopen( FileName.ToStdString().c_str(), "r") ;
		if ( !fp ) 
		{
			wxMessageBox( FileName + _T(" ") + _T("file does not exist") , frame_caption ) ;
			return ;
		}
		std::fclose( fp ) ;
		//
		std::strcpy( c_filename1 , FileName.ToStdString().c_str() ) ;
		margv[ mcurr_index_argv ] = const_cast<char * const>( c_filename1 ) ; ++mcurr_index_argv ;
		
		// Destination file :
		wxString DestFileName = FileName + gamma_file_extension ;
		fp = std::fopen( DestFileName.ToStdString().c_str(), "r") ;
		if ( fp ) 
		{
			std::fclose( fp ) ;
			wxMessageDialog *dial = new wxMessageDialog( NULL, 
				DestFileName + _T(" ") + m_labels_map[ _T( "OVERWRITE_QSTN" ) ] ,  frame_caption , 
				 wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
			if ( dial->ShowModal() == wxID_NO )
				return ;
		}

		std::strcpy( c_filename2 , DestFileName.ToStdString().c_str() ) ;
		margv[ mcurr_index_argv ] = const_cast<char * const>( c_filename2 ) ; ++mcurr_index_argv ;
	}
	
	margv[ mcurr_index_argv ] = NULL ; ++mcurr_index_argv ;
	
	//out command
	PrintCommand( mcurr_index_argv ) ;
	
	ExecGammaPipe( margv ) ;
}

void MyFrame::OnBtnDecrypt( wxCommandEvent &event )
{
	char c_psw[200] ;
	char c_filename1[500] ;
	char c_filename2[500] ;
	mcurr_index_argv = 0 ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( "gamma" ) ; ++mcurr_index_argv ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( "-f" ) ; ++mcurr_index_argv ;
	
	wxString spsw = "1234567890AB" ;
	if ( m_Password->GetValue() != _T("") ) 
		spsw = m_Password->GetValue() ;
	std::strcpy(  c_psw , spsw.ToStdString().c_str() ) ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( "-p" ) ; ++mcurr_index_argv ;
	margv[ mcurr_index_argv ] = const_cast<char * const>( c_psw ) ; ++mcurr_index_argv ;
	
	if ( m_chkBox_Keyfile->GetValue() )
	{
		margv[ mcurr_index_argv ] = const_cast<char * const>( "-k" ) ; ++mcurr_index_argv ;
	}
		
	margv[ mcurr_index_argv ] = const_cast<char * const>( "-d" ) ; ++mcurr_index_argv ;
	if ( m_FileName->GetValue() != _T("") )
	{
		//Source (encrypted) file :
		wxString FileName = m_FileName->GetValue() ;
		wxString DestFile ;
		
		if ( ! FileName.EndsWith( gamma_file_extension , &DestFile ) )
		{
			DestFile = FileName ;
			FileName += gamma_file_extension ;
		}
		
		std::strcpy( c_filename1 , FileName.ToStdString().c_str() ) ;
		// Does source (encrypted) file exist
		FILE * fp = std::fopen( FileName.ToStdString().c_str(), "r") ;
		if ( !fp ) 
		{
			wxMessageBox( FileName + _T(" ") + _T( "file does not exists" ) , frame_caption ) ;
			return ;
		}
		std::fclose( fp ) ;
		//
		
		//Destination (decrypted) File
		fp = std::fopen( DestFile.ToStdString().c_str(), "r") ;
		if ( fp ) 
		{
			std::fclose( fp ) ;
			wxMessageDialog *dial = new wxMessageDialog( NULL, 
				  DestFile + _T(" ") + m_labels_map[ _T( "OVERWRITE_QSTN" ) ] ,  frame_caption , 
				  wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
			if ( dial->ShowModal() == wxID_NO )
				return ;
		}
		std::strcpy( c_filename2 , DestFile.ToStdString().c_str() ) ;

		margv[ mcurr_index_argv ] = const_cast<char * const>( c_filename1 ) ; ++mcurr_index_argv ;
		margv[ mcurr_index_argv ] = const_cast<char * const>( c_filename2 ) ; ++mcurr_index_argv ;
	}
	
	margv[ mcurr_index_argv ] = NULL ; ++mcurr_index_argv ;
	
	//out command
	PrintCommand( mcurr_index_argv ) ;
	
	ExecGammaPipe( margv ) ;
}

void MyFrame::OnChkbxKeyFile( wxCommandEvent &event )
{
	SaveParameters() ;
}

void MyFrame::OnTxtctrlFilename( wxFocusEvent & event ) 
{
	if ( m_FileName->IsModified () )
	{
		std::cout << " FileName " << std::endl ;
		m_FileName->SetModified( false ) ;
		SaveParameters() ;
	}
}

void MyFrame::LoadParameters()
{
	wxFileInputStream input( wxT("wxgamma.cfg") ) ;
	wxTextInputStream text( input , wxT("\x09"), wxConvUTF8 ) ;
	std::map< wxString , wxString > prm_map ;

	while(input.IsOk() && !input.Eof() )
	{
		wxString line = text.ReadLine() ;
		wxArrayString arr( wxSplit( line , wxChar('\t') ) ) ;
		if (arr.Count() >= 2)
		{
			prm_map[ arr[0] ] = arr[1]  ; //wxString::FromUTF8
		}
	}
	
	m_FileName->ChangeValue( prm_map[ _T( "FILE_NAME" ) ] ) ;
	
	if ( prm_map[ _T( "USE_KEYFILE") ] == _T( "1" ) )
		m_chkBox_Keyfile->SetValue( true ) ;
	else
		m_chkBox_Keyfile->SetValue( false ) ;
	
}


void MyFrame::SaveParameters()
{
	wxFileOutputStream output( _T("wxgamma.cfg" ) ) ;
	if ( output.IsOk() )
	{
		std::string str ;
		
		str = "FILE_NAME\t" + m_FileName->GetValue().ToStdString() + "\n" ;
		output.Write( str.c_str(), str.size() ) ;
		
		str = "USE_KEYFILE\t" ;
		if ( m_chkBox_Keyfile->GetValue() )
			str += "1" ;
		else 
			str += "0" ;
		str += "\n" ;
		output.Write( str.c_str(), str.size() ) ;
	}
	
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
//	EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
//	EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
	EVT_BUTTON(ID_BTN_ENCRYPT,  MyFrame::OnBtnEncrypt)
	EVT_BUTTON(ID_BTN_DECRYPT,  MyFrame::OnBtnDecrypt)
	EVT_BUTTON(ID_BTN_SRC_FILEDLG,  MyFrame::OnBtnSrcFileDlg )
	EVT_CHECKBOX( ID_CHKBX_KEYFILE , MyFrame::OnChkbxKeyFile )
	//EVT_SET_FOCUS( MyFrame::OnTxtctrlFilename ) 
	//EVT_TEXT_ENTER( ID_TXTCTRL_FILENAME , MyFrame::OnTxtctrlFilename )
//	EVT_LISTBOX_DCLICK(ID_LIST, MyFrame::OnLoad)
//	EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()
