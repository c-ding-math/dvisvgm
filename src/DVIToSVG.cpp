/***********************************************************************
** DVIToSVG.cpp                                                       **
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

#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Calculator.h"
#include "CharmapTranslator.h"
#include "DVIToSVG.h"
#include "DVIToSVGActions.h"
#include "Font.h"
#include "FontManager.h"
#include "FileFinder.h"
#include "Message.h"
#include "PageSize.h"
#include "SVGFontEmitter.h"
#include "SVGFontTraceEmitter.h"
#include "TransformationMatrix.h"
#include "TFM.h"
#include "XMLDocument.h"
#include "XMLDocTypeNode.h"
#include "XMLString.h"


#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION ""
#endif

using namespace std;

// static class variables
bool DVIToSVG::CREATE_STYLE=true;
bool DVIToSVG::USE_FONTS=true;


/** Returns time stamp of current date/time. */
static string datetime () {
	time_t t;
	time(&t);
	struct tm *tm = localtime(&t);
	char *timestr = asctime(tm);
	timestr[24] = 0;  // remove newline
	return timestr;
}


DVIToSVG::DVIToSVG (istream &is, ostream &os) 
	: DVIReader(is), _out(os)
{
	svgDocument = 0;
	svgElement = new XMLElementNode("svg");
	replaceActions(new DVIToSVGActions(*this, svgElement));
	doctypeNode = 0;
	_mag = 4;
}


DVIToSVG::~DVIToSVG () {
	delete svgDocument;
	delete replaceActions(0);
}


/** Starts the conversion process. 
 *  @return number of processed pages */
int DVIToSVG::convert (unsigned firstPage, unsigned lastPage) {
	executePostamble();    // collect scaling and font information
	if (firstPage > getTotalPages()) {
		ostringstream oss;
		oss << "file contains only " << getTotalPages() << " page(s)";
		throw DVIException(oss.str());
	}	
	if (firstPage < 0)
		firstPage = 1;
	
	svgElement->addAttribute("version", "1.1");
	svgElement->addAttribute("xmlns", "http://www.w3.org/2000/svg");
	svgElement->addAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");

   svgDocument = new XMLDocument(svgElement);
	svgDocument->append(new XMLCommentNode(" This file was generated by dvisvgm "VERSION" "));
	svgDocument->append(new XMLCommentNode(" " + datetime() + " "));
	svgDocument->append(new XMLDocTypeNode("svg", "PUBLIC", 
		"\"-//W3C//DTD SVG 1.1//EN\"\n"
		"  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\""));

	if (CREATE_STYLE && USE_FONTS) {
		XMLElementNode *styleElement = new XMLElementNode("style");
		styleElement->addAttribute("type", "text/css");
		svgElement->append(styleElement);
		ostringstream style;
		FORALL(getFontManager()->getFonts(), vector<Font*>::const_iterator, i) {
			if (!dynamic_cast<VirtualFont*>(*i)) {  // skip virtual fonts
				style << "text.f"        << getFontManager()->fontID(*i) << ' '
						<< "{font-family:" << (*i)->name()
						<< ";font-size:"   << (*i)->scaledSize() << "}\n";
			}
		}
		XMLCDataNode *cdataNode = new XMLCDataNode(style.str());
		styleElement->append(cdataNode);
	}
	if (executePage(firstPage)) {  // @@ 
		Message::mstream() << endl;
		embedFonts(svgElement);

		// set bounding box and apply page transformations
		if (getActions()) {
			BoundingBox &bbox = getActions()->bbox();
			if (!_transCmds.empty()) {
				Calculator calc;
				calc.setVariable("ux", bbox.minX());
				calc.setVariable("uy", bbox.minY());
				calc.setVariable("w", bbox.width());
				calc.setVariable("h", bbox.height()); 
				calc.setVariable("pt", 1);
				calc.setVariable("in", 72.27);
				calc.setVariable("cm", 72.27/2.54);
				calc.setVariable("mm", 72.27/25.4);
				TransformationMatrix matrix(_transCmds, calc);
				static_cast<DVIToSVGActions*>(getActions())->setTransformation(matrix);
				if (_pageSizeName == "min")
					bbox.transform(matrix);
			}
			if (string("dvi none min").find(_pageSizeName) == string::npos) {
				// set explicitly given page format
				PageSize size(_pageSizeName);
				if (size.valid()) {
					// convention: DVI position (0,0) equals (1in, 1in) relative 
   				// to the upper left vertex of the page (see DVI specification)
 		 			const double border = -72.27;
		 			bbox = BoundingBox(border, border, size.widthInPT()+border, size.heightInPT()+border);
				}
				else
					Message::wstream(true) << "invalid page format '" << _pageSizeName << "'\n";
			}
			else if (_pageSizeName == "dvi") {
				// center page content
				double dx = (getPageWidth()-bbox.width())/2;
				double dy = (getPageHeight()-bbox.height())/2;
				bbox += BoundingBox(-dx, -dy, dx, dy);
			}
			if (bbox.width() > 0) {
				svgElement->addAttribute("width", XMLString(bbox.width())); 		
				svgElement->addAttribute("height", XMLString(bbox.height()));
				svgElement->addAttribute("viewBox", bbox.toSVGViewBox());

				Message::mstream() << "\npage size: " << bbox.width() << "pt"
					" x " << bbox.height() << "pt"
					" (" << bbox.width()/72.27*25.4 << "mm"
					" x " << bbox.height()/72.27*25.4 << "mm)\n";
			}
		}
		svgDocument->write(_out);
	}
	delete svgDocument;
	svgDocument = 0;
	
	return 1; // @@
}


/** Adds the font information to the SVG tree. 
 *  @param[in] svgElement the font nodes are added to this node */
void DVIToSVG::embedFonts (XMLElementNode *svgElement) {
	if (!svgElement)
		return; 
	if (!getActions())  // no dvi actions => no chars written => no fonts to embed
		return;
	
	XMLElementNode *defs = new XMLElementNode("defs");
	svgElement->prepend(defs);
	typedef const map<const Font*, set<int> > UsedCharsMap;
	const DVIToSVGActions *svgActions = static_cast<DVIToSVGActions*>(getActions());
	UsedCharsMap &usedChars = svgActions->getUsedChars();
		
	FORALL(usedChars, UsedCharsMap::const_iterator, i) {
		const Font *font = i->first;
		if (const PhysicalFont *ph_font = dynamic_cast<const PhysicalFont*>(font)) {
			CharmapTranslator *cmt = svgActions->getCharmapTranslator(font);
			if (ph_font->type() == PhysicalFont::MF) {
				SVGFontTraceEmitter emitter(font, getFontManager()->fontID(font), *cmt, defs, USE_FONTS);
				emitter.setMag(_mag);
				if (emitter.emitFont(i->second, font->name().c_str()) > 0)
					Message::mstream() << endl;
			}
			else if (font->path()) { // path to pfb/ttf file
				SVGFontEmitter emitter(font, getFontManager()->fontID(font), getFontManager()->encoding(font), *cmt, defs, USE_FONTS);
				emitter.emitFont(i->second, font->name().c_str());
			}
			else
				Message::wstream(true) << "can't embed font '" << font->name() << "'\n";
		}
		else
			Message::wstream(true) << "can't embed font '" << font->name() << "'\n";
	}
}


/** Enables or disables processing of specials. If ignorelist == 0, all 
 *  supported special handlers are loaded. To disable selected sets of specials,
 *  the corresponding prefixes can be given separated by non alpha-numeric characters,
 *  e.g. "color, ps, em" or "color: ps em" etc.
 *  A single "*" in the ignore list disables all specials.
 *  @param[in] ignorelist list of special prefixes to ignore */
const SpecialManager* DVIToSVG::setProcessSpecials (const char *ignorelist) {
	return (getActions() ? getActions()->setProcessSpecials(ignorelist) : 0);
}
		

void DVIToSVG::setMetafontMag (double m) {
	_mag = m;
	TFM::setMetafontMag(m);
}
