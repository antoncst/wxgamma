#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdio>

bool MyFrame::ExecGammaPipe( char ** argv )
{
    FILE* fp = std::fopen("../../gamma/Release/gamma", "r");
    if(!fp) {
        m_txt->AppendText( _T( "gamma executable is not found\n" ) ) ;
        return false;
    }    
	int fd[2]; 
    if ( pipe(fd) != 0 )
    {
	std::cerr << "Error connecting\n" ;
	return false ;
    }
    if( fork() ) 
    { //родитель
		enum { str_size = 256 } ;
		char str[ str_size ] ;
		dup2(fd[0],0); //подменили STDIN
		//close(fd[0]); // read
		//close(fd[1]); // write
		while ( true )
		{
			std::cin.getline( str , str_size ) ;
			if ( std::strcmp( str , "done" ) == 0 )
			break ;
			//std::cout << str << "\n" ;
			
			m_txt->AppendText( wxString( str ) ) ;
			m_txt->AppendText( _T("\n") ) ;
			//m_txt->Update() ;
		}
		close( fd[0] ) ;
		close( fd[1] ) ;
    } 
    else 
    { //дочерний процесс
		dup2(fd[1],1); //подменили STDOUT
	//		close(fd[0]);
	//		close(fd[1]);
	//	char * argv[10] ;
	//	//char argv0[] = "gamma" ;
	//	int curr_index_argv = 0 ;
	//	argv[ curr_index_argv ] = const_cast<char * const>( "gamma" ) ; ++curr_index_argv ;
	//	argv[ curr_index_argv ] = const_cast<char * const>( "-h" ) ; ++curr_index_argv ;
	//	argv[ curr_index_argv ] = NULL ; ++curr_index_argv ;
		if ( execv("../../gamma/Release/gamma", argv ) == -1 )
		{
			m_txt->AppendText( _T( "Error exec gamma \n" ) ) ;
		}
		close( fd[0] ) ;
		close( fd[1] ) ;

    }	
	return true;
}
