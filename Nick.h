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

#if !defined(AFX_NICK_H__2D11FD8C_472A_4623_AA6D_4C87F5F8C170__INCLUDED_)
#define AFX_NICK_H__2D11FD8C_472A_4623_AA6D_4C87F5F8C170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNick {
	char* m_Nick;
	char* m_Prefixes;
public:
	CNick(const char* Nick);
	virtual ~CNick();

	virtual const char* GetNick(void);

	virtual bool IsOp(void);
	virtual bool IsVoice(void);
	virtual bool IsHalfop(void);

	virtual bool HasPrefix(char Prefix);
	virtual void AddPrefix(char Prefix);
	virtual void RemovePrefix(char Prefix);
	virtual void SetPrefixes(const char* Prefixes);
	virtual const char* GetPrefixes(void);
};

void DestroyCNick(CNick* P);

#endif // !defined(AFX_NICK_H__2D11FD8C_472A_4623_AA6D_4C87F5F8C170__INCLUDED_)