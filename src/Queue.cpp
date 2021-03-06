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

#include "StdAfx.h"

/**
 * PeekItems
 *
 * Retrieves the next item from the queue without removing it.
 */
RESULT<const char *> CQueue::PeekItem(void) const {
	int LowestPriority = 99999;
	queue_item_t *ThatItem = NULL;

	for (int i = 0; i < m_Items.GetLength(); i++) {
		if (m_Items[i].Priority < LowestPriority) {
			LowestPriority = m_Items[i].Priority;
			ThatItem = m_Items.GetAddressOf(i);
		}
	}

	if (ThatItem != NULL) {
		RETURN(const char *, ThatItem->Line);
	} else {
		THROW(const char *, Generic_Unknown, "The queue is empty.");
	}
}

/**
 * DequeueItem
 *
 * Retrieves the next item from the queue and removes it.
 */
RESULT<char *> CQueue::DequeueItem(void) {
	int Index = 0;
	queue_item_t *Item = NULL;
	char *Line;

	for (int i = 0; i < m_Items.GetLength(); i++) {
		if (Item == NULL || m_Items[i].Priority < Item->Priority) {
			Item = m_Items.GetAddressOf(i);
			Index = i;
		}
	}

	if (Item != NULL) {
		Line = Item->Line;

		m_Items.Remove(Index);

		RETURN(char *, Line);
	} else {
		THROW(char *, Generic_Unknown, "The queue is empty.");
	}
}

/**
 * QueueItem
 *
 * Inserts a new item at the end of the queue.
 *
 * @param Line the item which is to be inserted
 */
RESULT<bool> CQueue::QueueItem(const char *Line) {
	queue_item_t Item;

	if (Line == NULL) {
		THROW(bool, Generic_InvalidArgument, "Line cannot be NULL.");
	}

	// ignore new items if the queue is full
	if (m_Items.GetLength() >= MAX_QUEUE_SIZE) {
		THROW(bool, Generic_Unknown, "The queue is full.");
	}

	Item.Line = strdup(Line);

	if (AllocFailed(Item.Line)) {
		THROW(bool, Generic_OutOfMemory, "strdup() failed.");
	}

	Item.Priority = 0;

	for (int i = 0; i < m_Items.GetLength(); i++) {
		m_Items[i].Priority--;
	}

	return m_Items.Insert(Item);
}

/**
 * QueueItemNext
 *
 * Inserts a new item at the front of the queue.
 *
 * @param Line the item which is to be inserted
 */
RESULT<bool> CQueue::QueueItemNext(const char *Line) {
	for (int i = 0; i < m_Items.GetLength(); i++) {
		m_Items[i].Priority += 2;
	}

	return QueueItem(Line);
}

/**
 * GetLength
 *
 * Returns the number of items which are in the queue.
 */
int CQueue::GetLength(void) const {
	return m_Items.GetLength();
}

/**
 * Clear
 *
 * Removes all items from the queue.
 */
void CQueue::Clear(void) {
	for (int i = 0; i < m_Items.GetLength(); i++) {
		free(m_Items[i].Line);
	}

	m_Items.Clear();
}
