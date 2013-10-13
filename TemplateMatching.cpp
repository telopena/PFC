/*
# Copyright (C) 2013 Eutelo Pena Barreiro
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License Version 3
# as published by the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#  
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#include "TemplateMatching.h"


TemplateMatching::TemplateMatching(void) :Runnable()
{
}


TemplateMatching::~TemplateMatching(void)
{
}


void TemplateMatching::match(){
	matchTemplate(buscar_cara,template_cara,result,CV_TM_CCOEFF_NORMED);
}

void TemplateMatching::setTemplate(Mat temp){
	template_cara=temp;
}

void TemplateMatching::setBuscar(Mat busc){
	buscar_cara=busc;
}

Mat TemplateMatching::getResult(){
	return(result);
}

void TemplateMatching::run(){
	match();
}