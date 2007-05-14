/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


//
// Class: ChatPanel
//
// Created on: Wed May  2 21:07:18 2007
//

#include "chatpanel.h"


//! @brief ChatPanel constructor.
//!
//! @param parent the parent wxWindow.
//! @param show_nick_list set to true if the nick list should be created.
//! @todo Fix nick list
//! @todo Enlarge the say input.
ChatPanel::ChatPanel( wxWindow* parent, bool show_nick_list ) : wxPanel( parent, -1 )
{
  // Setting default values
  m_show_nick_list = show_nick_list;
  m_chan_name = "";
  
  // Creating sizers
  m_main_sizer = new wxBoxSizer( wxHORIZONTAL );
  m_chat_sizer = new wxBoxSizer( wxVERTICAL );
  m_say_sizer = new wxBoxSizer( wxHORIZONTAL );
  if ( m_show_nick_list )
    m_nick_sizer = new wxBoxSizer( wxVERTICAL );
  else
    m_nick_sizer = NULL;
  
  // Creating ui elements
  m_chatlog_text = new wxTextCtrl( this, -1, _(""), wxDefaultPosition, wxDefaultSize, 
                             wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH | wxTE_AUTO_URL );

  m_say_text = new wxTextCtrl( this, -1, _(""), wxDefaultPosition, wxDefaultSize );
  m_say_button = new wxButton( this, -1, _T("Send") );
  
  // Adding elements to sizers
  m_say_sizer->Add( m_say_text, 1, wxEXPAND );
  m_say_sizer->Add( m_say_button );
  
  m_chat_sizer->Add( m_chatlog_text, 1, wxEXPAND );
  m_chat_sizer->Add( m_say_sizer, 0, wxEXPAND );
  
  m_main_sizer->Add( m_chat_sizer, 1, wxEXPAND );
  if ( m_show_nick_list )
    m_main_sizer->Add( m_nick_sizer );
  
  // Assign sizer to panel
  SetSizer( m_main_sizer );
}


//! @brief ChatPanel destructor.
ChatPanel::~ChatPanel()
{

}


//! @brief Output a message said in the channel.
//!
//! @param who nick of the person who said something.
//! @param message the message to be outputted.
//! @todo Fix nicer format of chat messages.
void ChatPanel::Said( wxString who, wxString message )
{
  m_chatlog_text->WriteText( who + _(": ")+ message + _("\n") );
}


//! @brief Output motd sent by server
//!
//! @param message The MOTD message to output
void ChatPanel::Motd( wxString message )
{
  m_chatlog_text->WriteText( _("* motd ")+ message + _("\n") );
}


//! @brief Set name of the chat/channel.
//!
//! @param chan_name the name of the channel.
//! @note The name is used as a reference when talking to the Server class.
void ChatPanel::SetChannelName( const string chan_name )
{
  m_chan_name = chan_name;
}


//! @brief Get name of the chat/channel.
//!
//! @return Name of the chat/channel.
string ChatPanel::GetChannelName()
{
  return m_chan_name;
}


//! @brief Check if ChatPanel controls a server output window.
//!
//! @return true if ChatPanel controls a server output window else false.
bool ChatPanel::IsServerPanel()
{
  return (m_chan_name == string(SERVER_CHAT_NAME));
}

