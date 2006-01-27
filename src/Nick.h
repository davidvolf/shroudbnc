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

class CChannel;
class CConfig;

/**
 * CNick
 *
 * Represents a user on a single channel.
 */
class CNick {
	CChannel *m_Owner; /**< the channel which this nick object belongs to */
	char *m_Nick; /**< the nickname of the user */
	char *m_Prefixes; /**< the user's prefixes (e.g. @, +) */
	char *m_Site; /**< the ident\@host of the user */
	char *m_Realname; /**< the realname of the user */
	char *m_Server; /**< the server this user is using */
	time_t m_Creation; /**< a timestamp, when this user object was created */
	time_t m_IdleSince; /**< a timestamp, when the user last said something */
	CConfig *m_Tags; /**< any tags which belong to this nick object */

	const char *InternalGetSite(void);
	const char *InternalGetRealname(void);
	const char *InternalGetServer(void);
public:
#ifndef SWIG
	CNick(CChannel *Owner, const char *Nick);
#endif
	virtual ~CNick(void);

	virtual const char *GetNick(void);
	virtual bool SetNick(const char *Nick);

	virtual bool IsOp(void);
	virtual bool IsVoice(void);
	virtual bool IsHalfop(void);

	virtual bool HasPrefix(char Prefix);
	virtual bool AddPrefix(char Prefix);
	virtual bool RemovePrefix(char Prefix);
	virtual bool SetPrefixes(const char* Prefixes);
	virtual const char *GetPrefixes(void);

	virtual bool SetSite(const char *Site);
	virtual const char *GetSite(void);

	virtual bool SetRealname(const char *Realname);
	virtual const char *GetRealname(void);

	virtual bool SetServer(const char *Server);
	virtual const char *GetServer(void);

	virtual time_t GetChanJoin(void);

	virtual time_t GetIdleSince(void);
	virtual bool SetIdleSince(time_t Time);
	
	virtual bool SetTag(const char *Name, const char *Value);
	virtual const char *GetTag(const char *Name);

	virtual CChannel *GetChannel(void);
};
