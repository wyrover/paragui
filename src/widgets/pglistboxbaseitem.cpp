/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: braindead $
    Update Date:      $Date: 2002/05/02 08:45:36 $
    Source File:      $Source: /sources/paragui/paragui/src/widgets/pglistboxbaseitem.cpp,v $
    CVS/RCS Revision: $Revision: 1.3.6.2 $
    Status:           $State: Exp $
*/

#include "pglistboxbaseitem.h"
#include "pglistbox.h"

PG_ListBoxBaseItem::PG_ListBoxBaseItem(int height, void* userdata) : PG_Label(NULL, PG_Rect(0,0,100,20), NULL) {
	my_userdata = userdata;
	my_selected = false;
	my_hover = false;
	my_itemheight = height;

	SetAlignment(PG_TA_LEFT);
}

PG_ListBoxBaseItem::~PG_ListBoxBaseItem() {
	if(GetParent()->GetSelectedItem() == this) {
		GetParent()->SelectItem(NULL);
		GetParent()->RemoveWidget(this, true, true);
	}
}

void PG_ListBoxBaseItem::SetUserData(void* userdata) {
	my_userdata = userdata;
}

void* PG_ListBoxBaseItem::GetUserData() {
	return my_userdata;
}

bool PG_ListBoxBaseItem::IsSelected() {
	return my_selected;
}

void PG_ListBoxBaseItem::Select(bool select) {
	my_selected = select;

	if(GetParent() != NULL) {
		if(select) {
			GetParent()->SelectItem(this);
		}
	}
}

int PG_ListBoxBaseItem::Height() {
	return my_itemheight;
}

void PG_ListBoxBaseItem::eventSizeWidget(Uint16 w, Uint16 h) {
	my_itemheight = h;
}

void PG_ListBoxBaseItem::eventMouseEnter() {
	my_hover = true;
	Update();
}

void PG_ListBoxBaseItem::eventMouseLeave() {
	my_hover = false;
	PG_Label::eventMouseLeave();
	Update();
}

void PG_ListBoxBaseItem::eventHide() {
	my_hover = false;
}

bool PG_ListBoxBaseItem::eventMouseButtonUp (const SDL_MouseButtonEvent* button) {

	if(button->button != 1) {
		return false;
	}

	if(GetParent() == NULL) {
		return true;
	}

	if(GetParent()->GetMultiSelect()) {
		Select(!IsSelected());
	} else {
		Select(true);
	}

	return true;
}

PG_ListBox* PG_ListBoxBaseItem::GetParent() {
	return (PG_ListBox*)(PG_Label::GetParent());
}
