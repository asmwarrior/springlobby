/* This file is part of the Springlobby (GPL v2 or later), see COPYING */


/**
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

DO NOT CHANGE THIS FILE!

this file is deprecated and will be replaced with

lsl/spring/springprocess.cpp

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**/


#include "springprocess.h"
#include "spring.h"
#include "utils/debug.h"
#include "utils/conversion.h"
#include <wx/log.h>


DEFINE_LOCAL_EVENT_TYPE( wxEVT_SPRING_EXIT )


SpringProcess::SpringProcess( Spring& sp ) :
		m_sp( sp ), m_exit_code( 0 )
{
	wxLogDebugFunc( wxEmptyString );
}


SpringProcess::~SpringProcess()
{
	wxLogDebugFunc( wxEmptyString );
}


void SpringProcess::SetCommand( const wxString& cmd )
{
	m_cmd = cmd;
}


void SpringProcess::OnExit()
{
	wxLogDebugFunc( wxEmptyString );
	wxCommandEvent event( wxEVT_SPRING_EXIT, PROC_SPRING );
	event.SetExtraLong( m_exit_code );
	m_sp.AddPendingEvent( event );
}


void* SpringProcess::Entry()
{
	wxLogDebugFunc( wxEmptyString );
	m_exit_code = system( m_cmd.mb_str( wxConvUTF8 ) );
	wxLogMessage( _T( "Spring closed." ) );
	return 0;
}
