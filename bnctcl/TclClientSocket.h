/*******************************************************************************
 * shroudBNC - an object-oriented framework for IRC                            *
 * Copyright (C) 2005-2007,2010 Gunnar Beutner                                 *
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

class CTclClientSocket : public CConnection {
public:
	CTclClientSocket(SOCKET Socket, bool SSL = false, connection_role_e Role = Role_Server);
	virtual ~CTclClientSocket();

	virtual int Read(bool DontProcess);
	virtual void Destroy(void);
	virtual bool ShouldDestroy(void) const;

	virtual const char *GetClassName(void) const;

	virtual void SetControlProc(const char *Proc);
	virtual const char *GetControlProc(void) const;

	virtual int GetIdx(void);

	virtual bool MayNotEnterDestroy(void);
	virtual void DestroyLater(void);

	virtual int SSLVerify(int PreVerifyOk, X509_STORE_CTX *Context) const {
		return true;
	}

	virtual void ParseLine(const char *Line);

private:
	SOCKET m_Socket;
	char *m_Control;
	int m_Idx;
	bool m_InTcl;
	bool m_Destroy;
	bool m_FirstTry;
};
