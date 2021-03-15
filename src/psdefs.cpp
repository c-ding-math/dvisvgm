/*************************************************************************
** psdefs.cpp                                                           **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2021 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#include "PSInterpreter.hpp"

const char *PSInterpreter::PSDEFS =
"<</Install{matrix setmatrix}/HWResolution[72 72]/PageSize[10000 10000]/Imaging"
"BBox null>>setpagedevice/@dodraw true store/@GD globaldict def/@SD systemdict "
"def/@UD userdict def @GD/@nulldev false put @GD/@patcnt 0 put true setglobal @"
"SD/:save @SD/save get put @SD/:restore @SD/restore get put @SD/:gsave @SD/gsav"
"e get put @SD/:grestore @SD/grestore get put @SD/:grestoreall @SD/grestoreall "
"get put @SD/:newpath @SD/newpath get put @SD/:stroke @SD/stroke get put @SD/:f"
"ill @SD/fill get put @SD/:eofill @SD/eofill get put @SD/:clip @SD/clip get put"
" @SD/:eoclip @SD/eoclip get put @SD/:charpath @SD/charpath get put @SD/:show @"
"SD/show get put @SD/:stringwidth @SD/stringwidth get put @SD/:nulldevice @SD/n"
"ulldevice get put @SD/:image @SD/image get put @SD/:colorimage @SD/colorimage "
"get put @SD/.setopacityalpha known not{@SD/.setopacityalpha{pop}put}if @SD/.se"
"tshapealpha known not{@SD/.setshapealpha{pop}put}if @SD/.setblendmode known no"
"t{@SD/.setblendmode{pop}put}if @SD/prseq{-1 1{-1 roll =only( )print}for(\\n)pr"
"int}put @SD/prcmd{( )exch(\\ndvi.)3{print}repeat prseq}put @SD/cvxall{{cvx}for"
"all}put @SD/defpr{[exch[/copy @SD]cvxall 5 -1 roll dup 6 1 roll[/get/exec]cvxa"
"ll 6 -1 roll dup 7 1 roll 4 -1 roll dup 5 1 roll dup length string cvs/prcmd c"
"vx]cvx def}put @SD/querypos{{currentpoint}stopped{$error/newerror false put}{2"
"(querypos)prcmd}ifelse}put @SD/applyscalevals{1 0 dtransform exch dup mul exch"
" dup mul add sqrt 0 1 dtransform exch dup mul exch dup mul add sqrt 1 0 dtrans"
"form dup mul exch dup dup mul 3 -1 roll add dup 0 eq{pop}{sqrt div}ifelse 3(ap"
"plyscalevals)prcmd}put @SD/prpath{{2(moveto)prcmd}{2(lineto)prcmd}{6(curveto)p"
"rcmd}{0(closepath)prcmd}pathforall}put @SD/nulldevice{@GD/@nulldev true put :n"
"ulldevice 1 1(setnulldevice)prcmd}put @SD/charpath{/@dodraw false store :charp"
"ath/@dodraw true store}put @SD/stringwidth{/@dodraw false store :stringwidth/@"
"dodraw true store}put @SD/show{@dodraw @GD/@nulldev get not and{dup :gsave cur"
"rentpoint 2{50 mul exch}repeat :newpath moveto 50 50/scale sysexec true charpa"
"th fill :grestore/@dodraw false store :show/@dodraw true store}{:show}ifelse}p"
"ut @SD/varxyshow{dup 0 ge{<</chr 3 -1 roll string/prc 5 -1 roll/arr 7 -1 roll/"
"str 9 -1 roll/idx 0>>begin 0 chr length str length 1 sub{str exch chr length g"
"etinterval/chr exch store :gsave chr show :grestore currentpoint prc moveto/id"
"x idx 1 add store}for end}{pop pop show}ifelse}put @SD/xyshow{dup dup type/arr"
"aytype eq exch length 0 gt and{dup length 2 idiv 2 index length exch idiv}{-1}"
"ifelse{exch arr idx 2 mul get add exch arr idx 2 mul 1 add get add}exch varxys"
"how}put @SD/xshow{dup dup type/arraytype eq exch length 0 gt and{dup length 2 "
"index length exch idiv}{-1}ifelse{exch arr idx get add exch}exch varxyshow}put"
" @SD/yshow{dup dup type/arraytype eq exch length 0 gt and{dup length 2 index l"
"ength exch idiv}{-1}ifelse{arr idx get add}exch varxyshow}put @SD/awidthshow{{"
"1 string dup 0 5 index put :gsave show :grestore pop 0 rmoveto 3 index eq{4 in"
"dex 4 index rmoveto}if 1 index 1 index rmoveto}exch cshow 5{pop}repeat}put @SD"
"/widthshow{0 0 3 -1 roll awidthshow}put @SD/ashow{0 0 0 6 3 roll awidthshow}pu"
"t @SD/newpath{:newpath 1 1(newpath)prcmd}put @SD/stroke{@dodraw @GD/@nulldev g"
"et not and{prcolor 0 1(newpath)prcmd prpath 0(stroke)prcmd :newpath}{:stroke}i"
"felse}put @SD/fill{@dodraw @GD/@nulldev get not and{prcolor 0 1(newpath)prcmd "
"prpath 0(fill)prcmd :newpath}{:fill}ifelse}put @SD/eofill{@dodraw @GD/@nulldev"
" get not and{prcolor 0 1(newpath)prcmd prpath 0(eofill)prcmd :newpath}{:eofill"
"}ifelse}put/.fillstroke{:gsave fill :grestore .swapcolors stroke .swapcolors}b"
"ind def/.eofillstroke{:gsave eofill :grestore .swapcolors stroke .swapcolors}b"
"ind def @SD/clip{:clip @GD/@nulldev get not{0 1(newpath)prcmd prpath 0(clip)pr"
"cmd}if}put @SD/eoclip{:eoclip @GD/@nulldev get not{0 1(newpath)prcmd prpath 0("
"eoclip)prcmd}if}put @SD/shfill{begin currentdict/ShadingType known currentdict"
"/ColorSpace known and currentdict/DataSource known and currentdict/Function kn"
"own not and ShadingType 4 ge{DataSource type/arraytype eq{<</DeviceGray 1/Devi"
"ceRGB 3/DeviceCMYK 4/bgknown currentdict/Background known/bbknown currentdict/"
"BBox known>>begin currentdict ColorSpace known{ShadingType ColorSpace load bgk"
"nown{1 Background aload pop}{0}ifelse bbknown{1 BBox aload pop}{0}ifelse Shadi"
"ngType 5 eq{VerticesPerRow}if DataSource aload length 4 add bgknown{ColorSpace"
" load add}if bbknown{4 add}if ShadingType 5 eq{1 add}if(shfill)prcmd}if end}if"
"}if end}put @SD/image{dup type/dicttype eq{dup}{<</Width 6 index/Height 7 inde"
"x/colorimg false>>}ifelse @execimg}put @SD/colorimage{<<2 index{/Width 2 index"
" 8 add index/Height 4 index 9 add index}{/Width 8 index/Height 9 index}ifelse/"
"colorimg true>>@execimg}put/@imgbase(./)def/@imgdevice(jpeg)def/@execimg{@GD/@"
"imgcnt 2 copy .knownget{1 add}{1}ifelse put begin<</imgdev null/imgid @GD/@img"
"cnt get/ispng @imgdevice 0 3 getinterval(png)eq dup/suffix exch{(.png)}{(.jpg)"
"}ifelse/colorimg currentdict/colorimg .knownget dup{pop}if/colordev 1 index cu"
"rrentcolorspace dup length 1 ne exch 0 get/DeviceGray ne or or>>begin @imgdevi"
"ce(png)ne @imgdevice(jpeg)ne and{@imgdevice cvn}{colordev{ispng{/png16m}{/jpeg"
"}ifelse}{ispng{/pnggray}{/jpeggray}ifelse}ifelse}ifelse dup devicedict exch kn"
"own{:gsave/imgdev exch finddevice def mark/OutputFile @imgbase imgid 20 string"
" cvs strconcat suffix strconcat/PageSize[Width Height]/UseFastColor true ispng"
"{@imgdevice(pngmonod)eq{/MinFeatureSize where{pop/MinFeatureSize MinFeatureSiz"
"e}if}if}{/JPEGQ where{pop/JPEGQ JPEGQ}if}ifelse imgdev putdeviceprops setdevic"
"e[Width 0 0 Height neg 0 Height]/setmatrix sysexec colorimg{:colorimage}{:imag"
"e}ifelse/copypage sysexec mark/OutputFile()imgdev putdeviceprops pop :grestore"
" imgid Width Height 3(image)prcmd}{pop colorimg{:colorimage}{:image}ifelse}ife"
"lse end end}def/@rect{4 -2 roll moveto exch dup 0 rlineto exch 0 exch rlineto "
"neg 0 rlineto closepath}bind def/@rectcc{4 -2 roll moveto 2 copy 0 lt exch 0 l"
"t xor{dup 0 exch rlineto exch 0 rlineto neg 0 exch rlineto}{exch dup 0 rlineto"
" exch 0 exch rlineto neg 0 rlineto}ifelse closepath}bind def @SD/rectclip{:new"
"path dup type/arraytype eq{aload length 4 idiv{@rectcc}repeat}{@rectcc}ifelse "
"clip :newpath}put @SD/rectfill{:gsave :newpath dup type/arraytype eq{aload len"
"gth 4 idiv{@rectcc}repeat}{@rectcc}ifelse fill :grestore}put @SD/rectstroke{gs"
"ave :newpath dup type/arraytype eq{aload length 4 idiv{@rect}repeat}{@rect}ife"
"lse stroke grestore}put false setglobal @SD readonly pop/initclip 0 defpr/clip"
"path 0 defpr/sysexec{@SD exch get exec}def/adddot{dup length 1 add string dup "
"0 46 put dup 3 -1 roll 1 exch putinterval}def/setlinewidth{dup/setlinewidth sy"
"sexec 1(setlinewidth)prcmd}def/setlinecap 1 defpr/setlinejoin 1 defpr/setmiter"
"limit 1 defpr/setdash{mark 3 1 roll 2 copy/setdash sysexec exch aload length 1"
" add -1 roll counttomark(setdash)prcmd pop}def/@setpagedevice{pop<<>>/setpaged"
"evice sysexec matrix setmatrix newpath 0(setpagedevice)prcmd}def/@checknulldev"
"{@GD/@nulldev get{currentpagedevice maxlength 0 ne{@GD/@nulldev false put 0 1("
"setnulldevice)prcmd}if}if}def/prcolor{currentcolorspace @setcolorspace current"
"rgbcolor 3(setrgbcolor)prcmd}def/printgstate{@dodraw @GD/@nulldev get not and{"
"matrix currentmatrix aload pop 6(setmatrix)prcmd applyscalevals currentlinewid"
"th 1(setlinewidth)prcmd currentlinecap 1(setlinecap)prcmd currentlinejoin 1(se"
"tlinejoin)prcmd currentmiterlimit 1(setmiterlimit)prcmd revision dup 952 lt{po"
"p}{.currentblendmode .setblendmode 952 eq{.currentopacityalpha .setopacityalph"
"a .currentshapealpha .setshapealpha}{.currentalphaisshape{1}{0}ifelse 1(setalp"
"haisshape)prcmd .currentstrokeconstantalpha 1(setstrokeconstantalpha)prcmd .cu"
"rrentfillconstantalpha 1(setfillconstantalpha)prcmd}ifelse}ifelse prcolor curr"
"entdash mark 3 1 roll exch aload length 1 add -1 roll counttomark(setdash)prcm"
"d pop}if}def/strconcat{exch dup length 2 index length add string dup dup 4 2 r"
"oll copy length 4 -1 roll putinterval}def/setgstate{/setgstate sysexec printgs"
"tate}def/save{@UD begin/@saveID vmstatus pop pop def end :save @saveID 1(save)"
"prcmd}def/restore{:restore @checknulldev printgstate @UD/@saveID known{@UD beg"
"in @saveID end}{0}ifelse 1(restore)prcmd}def/gsave 0 defpr/grestore{:grestore "
"@checknulldev printgstate 0(grestore)prcmd}def/grestoreall{:grestoreall @check"
"nulldev setstate 0(grestoreall)prcmd}def/rotate{dup type/arraytype ne @dodraw "
"and{dup 1(rotate)prcmd}if/rotate sysexec applyscalevals}def/scale{dup type/arr"
"aytype ne @dodraw and{2 copy 2(scale)prcmd}if/scale sysexec applyscalevals}def"
"/translate{dup type/arraytype ne @dodraw and{2 copy 2(translate)prcmd}if/trans"
"late sysexec}def/setmatrix{dup/setmatrix sysexec @dodraw{aload pop 6(setmatrix"
")prcmd applyscalevals}{pop}ifelse}def/initmatrix{matrix setmatrix}def/concat{m"
"atrix currentmatrix matrix concatmatrix setmatrix}def/makepattern{gsave<</mx 3"
" -1 roll>>begin<</XUID[1000000 @patcnt]>>copy mx/makepattern sysexec dup begin"
" PatternType 2 lt{PatternType @patcnt BBox aload pop XStep YStep PaintType mx "
"aload pop 15(makepattern)prcmd :newpath matrix setmatrix dup PaintProc 0 1(mak"
"epattern)prcmd @GD/@patcnt @patcnt 1 add put}if end end grestore}def/setpatter"
"n{begin PatternType 1 eq{PaintType 1 eq{XUID aload pop exch pop 1}{:gsave[curr"
"entcolorspace aload length -1 roll pop]/setcolorspace sysexec/setcolor sysexec"
" XUID aload pop exch pop currentrgbcolor :grestore 4}ifelse(setpattern)prcmd c"
"urrentcolorspace 0 get/Pattern ne{[/Pattern currentcolorspace]/setcolorspace s"
"ysexec}if currentcolorspace @setcolorspace}{/setpattern sysexec}ifelse end}def"
"/setcolor{dup type/dicttype eq{setpattern}{/setcolor sysexec/currentrgbcolor s"
"ysexec setrgbcolor}ifelse}def/setcolorspace{dup/setcolorspace sysexec @setcolo"
"rspace}def/@setcolorspace{dup type/arraytype eq{0 get}if/Pattern eq{1}{0}ifels"
"e 1(setcolorspace)prcmd}def/setgray 1 defpr/setcmykcolor 4 defpr/sethsbcolor 3"
" defpr/setrgbcolor 3 defpr/.setalphaisshape{@SD/.setalphaisshape known{dup/.se"
"talphaisshape sysexec}if{1}{0}ifelse 1(setalphaisshape)prcmd}bind def/.setfill"
"constantalpha{@SD/.setfillconstantalpha known{dup/.setfillconstantalpha sysexe"
"c}if 1(setfillconstantalpha)prcmd}bind def/.setstrokeconstantalpha{@SD/.setstr"
"okeconstantalpha known{dup/.setstrokeconstantalpha sysexec}if 1(setstrokeconst"
"antalpha)prcmd}bind def/.setopacityalpha{false .setalphaisshape dup .setfillco"
"nstantalpha .setstrokeconstantalpha}bind def/.setshapealpha{true .setalphaissh"
"ape dup .setfillconstantalpha .setstrokeconstantalpha}bind def/.setblendmode{d"
"up/.setblendmode sysexec<</Normal 0/Compatible 0/Multiply 1/Screen 2/Overlay 3"
"/SoftLight 4/HardLight 5/ColorDodge 6/ColorBurn 7/Darken 8/Lighten 9/Differenc"
"e 10/Exclusion 11/Hue 12/Saturation 13/Color 14/Luminosity 15/CompatibleOverpr"
"int 16>>exch get 1(setblendmode)prcmd}def/@pdfpagecount{(r)file runpdfbegin pd"
"fpagecount runpdfend}def/@pdfpagebox{(r)file runpdfbegin dup dup 1 lt exch pdf"
"pagecount gt or{pop}{pdfgetpage/MediaBox pget pop aload pop}ifelse runpdfend}d"
"ef DELAYBIND{.bindnow}if ";

