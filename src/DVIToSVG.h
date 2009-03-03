/***********************************************************************
** DVIToSVG.h                                                         **
**                                                                    **
** This file is part of dvisvgm -- the DVI to SVG converter           **
** Copyright (C) 2005-2009 Martin Gieseking <martin.gieseking@uos.de> **
**                                                                    **
** This program is free software; you can redistribute it and/or      **
** modify it under the terms of the GNU General Public License        **
** as published by the Free Software Foundation; either version 2     **
** of the License, or (at your option) any later version.             **
**                                                                    **
** This program is distributed in the hope that it will be useful,    **
** but WITHOUT ANY WARRANTY; without even the implied warranty of     **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      **
** GNU General Public License for more details.                       **
**                                                                    **
** You should have received a copy of the GNU General Public License  **
** along with this program; if not, write to the Free Software        **
** Foundation, Inc., 51 Franklin Street, Fifth Floor,                 **
** Boston, MA 02110-1301, USA.                                        **
***********************************************************************/

#ifndef DVITOSVG_H
#define DVITOSVG_H

#include <iostream>
#include "DVIReader.h"


class CharmapTranslator;
class SpecialManager;
class XMLDocument;
class XMLDocTypeNode;
class XMLElementNode;

class DVIToSVG : public DVIReader
{
   public:
      DVIToSVG (std::istream &is, std::ostream &os);
		~DVIToSVG ();
		int convert (unsigned firstPage, unsigned lastPage);
		void setMetafontMag (double m);
		void setPageSize (string name)    {_pageSizeName = name;}
		const SpecialManager* setProcessSpecials (const char *ignorelist=0);
		void setTransformation (const string &cmds) {_transCmds = cmds;}
	
	protected:
		DVIToSVG (const DVIToSVG &);
		DVIToSVG operator = (const DVIToSVG &);
		void embedFonts (XMLElementNode *svgElement);

   private:
		std::ostream &_out;       ///< DVI output is written to this stream
		double _mag;              ///< magnification factor of Metafont output
		XMLDocument *svgDocument;
		XMLDocTypeNode *doctypeNode;
		XMLElementNode *svgElement;
		string _pageSizeName;
		string _transCmds;

	public:
		static bool CREATE_STYLE; ///< should <style>...</style> and class attributes be used to reference fonts?
		static bool USE_FONTS;    ///< if true, create font references and don't draw paths directly
};

#endif
