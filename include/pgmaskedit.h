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
    Update Date:      $Date: 2002/04/15 13:31:30 $
    Source File:      $Source: /sources/paragui/paragui/include/pgmaskedit.h,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#ifndef PG_MASKEDIT_H
#define PG_MASKEDIT_H

#include "pglineedit.h"

#ifdef SWIG
%include "swigcommon.h"
%module pgmaskedit
%{
#include "pgmaskedit.h"
    %}
#endif

#ifndef SWIG
#include <string>
#endif

class DECLSPEC PG_MaskEdit : public PG_LineEdit {
public:

	/** */
	PG_MaskEdit(PG_Widget* parent, const PG_Rect& r, const char* style="LineEdit");

	/**
	Set the text of the maskedit control. The new text is merged with the current mask
	@param	new_text		pointer to new text string
	*/
	void SetText(const char* new_text);

	/**
	Set the valid input mask
	@param	mask			input mask (e.g. ##.##.####)
	*/
	void SetMask(const char* mask);

	/**
	Get current input mask
	@return						input mask
	*/
	const char* GetMask();

	/**
	Set the "spacer" character. This char is displayed instead of "#"
	@param	c					"spacer" character
	*/
	void SetSpacer(char c);

	/**
	Get the current "spacer" character.
	@return						"spacer" character
	*/
	char GetSpacer();

protected:

	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	void InsertChar(const char* c);

	void DeleteChar(Uint16 pos);

private:

#ifndef SWIG

	std::string my_mask;
	std::string my_displaymask;
#endif

	char my_spacer;

};

#endif	// PG_MASKEDIT_H
