/*******************************************************************************
 * shroudBNC - an object-oriented framework for IRC                            *
 * Copyright (C) 2005 Gunnar Beutner                                           *
 *                                                                             *
 * This program is free software; you can redistribute it and/or               *
 * modify it under the terms of the GNU General Public License                 *
 * as published by the Free Software Foundation; either version 2              *
 * of the License, or (at your option) any later version.                      *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program; if not, write to the Free Software                 *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. *
 *******************************************************************************/

class CCore;
class CIRCConnection;
class CClientConnection;

/**
 * CModuleFar
 *
 * The interface for modules.
 */
struct CModuleFar {
	virtual void Destroy(void) = 0;
	virtual void Init(CCore *Root) = 0;

	virtual bool InterceptIRCMessage(CIRCConnection *Connection, int argc, const char **argv) = 0;
	virtual bool InterceptClientMessage(CClientConnection *Connection, int argc, const char **argv) = 0;
	virtual bool InterceptClientCommand(CClientConnection *Connection, const char *Subcommand, int argc, const char **argv, bool NoticeUser) = 0;

	virtual void AttachClient(const char *Client) = 0;
	virtual void DetachClient(const char *Client) = 0;

	virtual void ServerDisconnect(const char *Client) = 0;
	virtual void ServerConnect(const char *Client) = 0;
	virtual void ServerLogon(const char *Client) = 0;

	virtual void UserLoad(const char *User) = 0;
	virtual void UserCreate(const char *User) = 0;
	virtual void UserDelete(const char *User) = 0;

	virtual void SingleModeChange(CIRCConnection *IRC, const char *Channel, const char *Source, bool Flip, char Mode, const char *Parameter) = 0;

	virtual const char *Command(const char *Cmd, const char *Parameters) = 0;

	virtual void TagModified(const char *Tag, const char *Value) = 0;
	virtual void UserTagModified(const char *Tag, const char *Value) = 0;
};

class CModuleImplementation : public CModuleFar {
private:
	CCore *m_Core;

protected:
	virtual ~CModuleImplementation(void) { }

	virtual void Destroy(void) {
		delete this;
	}

	virtual void Init(CCore *Root) {
		m_Core = Root;
	}

	virtual bool InterceptIRCMessage(CIRCConnection *Connection, int argc, const char **argv) {
		return true;
	}

	virtual bool InterceptClientMessage(CClientConnection *Connection, int argc, const char **argv) {
		return true;
	}

	virtual bool InterceptClientCommand(CClientConnection *Connection, const char *Subcommand, int argc, const char **argv, bool NoticeUser) {
		return false;
	}

	virtual void AttachClient(const char *Client) {	}

	virtual void DetachClient(const char *Client) { }

	virtual void ServerDisconnect(const char *Client) { }
	virtual void ServerConnect(const char *Client) { }
	virtual void ServerLogon(const char *Client) { }

	virtual void UserLoad(const char *User) { }
	virtual void UserCreate(const char *User) { }
	virtual void UserDelete(const char *User) { }

	virtual void SingleModeChange(CIRCConnection *IRC, const char *Channel, const char *Source, bool Flip, char Mode, const char *Parameter) { }

	virtual const char *Command(const char *Cmd, const char *Parameters) {
		return NULL;
	}

	virtual void TagModified(const char *Tag, const char *Value) { }
	virtual void UserTagModified(const char *Tag, const char *Value) { }
public:
	CCore *GetCore(void) {
		return m_Core;
	}
};
