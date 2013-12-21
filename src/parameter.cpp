/*
 * This File is part of Pindel; a program to locate genomic variation.
 * https://trac.nbic.nl/pindel/
 *
 *   Copyright (C) 2011 Kai Ye
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// System header files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <getopt.h>
#include <omp.h>
#include <cstdlib>

// Pindel header files
#include "parameter.h"
#include "logdef.h"

/* 'Parameter' stores an individual parameter; it is set by the command line parameters, and used by the program. */
Parameter::Parameter ( const std::string & shortName, const std::string & longName,
                      const std::string & description,
                      const bool required ) {
    d_required = required;
    d_shortName = shortName;
    d_longName = longName;
    d_description = description;
    d_isSet = false;
}

// unshift one word per time
const std::string Parameter::getWord ( std::string & line, bool& forceLineEnd ) const {
    forceLineEnd = false;
    std::string head, tail;
    size_t endPos = line.find (" ");
    size_t returnPos = line.find("\n");
    if ( returnPos<endPos ) { 
        endPos = returnPos; 
        forceLineEnd = true;
    }
    if ( endPos == line.npos ) { 
        head = line; 
        tail = "";
    } else {
        head = line.substr (0, endPos);
        tail = line.substr (endPos + 1);
    }
    line = tail;
    
    return head;
}

// formatting output of paras
const std::string Parameter::makeNiceLine ( const std::string & rawDescription ) const {
    std::string neatLine = describeTab ();
    std::string words = rawDescription;
    std::string spaces (d_SPACES_WIDTH, ' ');
    const size_t LIMIT = d_MAX_LINE_WIDTH - d_DESCRIBE_WIDTH;
    size_t lineSize = 0;
    while ( words.size () > 0 ) {
        bool forceLineEnd = false;
        std::string newWord = getWord (words, forceLineEnd);
        if ( newWord.size () + lineSize > LIMIT || forceLineEnd ) {
            neatLine += '\n';
            neatLine += spaces;
            lineSize = 0;
        }
        neatLine += newWord + " ";
        lineSize += newWord.size() + 1;
    }
    
    return neatLine;
}

// paras output 
void Parameter::describe () const {
    (std::cout << std::string(d_DESCRIBE_WIDTH, ' '));

    if ( d_shortName.empty() ) {
        (std::cout << std::left << std::setw(d_MAX_LONG_PARA_WIDTH + 3) << d_longName << "  ");
    } else {
        (std::cout << d_shortName << ", "); 
        (std::cout << std::left << std::setw(d_MAX_LONG_PARA_WIDTH) << d_longName << " ");
    }

    (std::cout << makeNiceLine (d_description));
    (std::cout << std::endl << std::endl);
}

// Parameter initial 
IntParameter::IntParameter ( int *par_ptr, const std::string & shortName,
                            const std::string & longName,
                            const std::string & description, const bool required,
                            const int value ): Parameter (shortName, longName, description, required), d_data_ptr (par_ptr) {
   *d_data_ptr = value;
}

void IntParameter::setValue ( const std::string & value) { setValue (atoi (value.c_str ())); }
void IntParameter::setValue ( const int value ) { *d_data_ptr = value; set(); }

/* UIntParameter */
UIntParameter::UIntParameter (unsigned int *par_ptr, const std::string & shortName,
                              const std::string & longName,
                              const std::string & description, const bool required,
                              const unsigned int value): Parameter (shortName, longName, description, required), d_data_ptr (par_ptr){
   *d_data_ptr = value;
}

void UIntParameter::setValue (const std::string & value) { setValue ((unsigned int)atoi (value.c_str ())); }
void UIntParameter::setValue (const unsigned int value) { *d_data_ptr = value; set (); }
/* BoolParameter */
BoolParameter::BoolParameter ( bool * par_ptr, const std::string & shortName, 
                               const std::string & longName, const std::string & description, 
                               const bool required, 
                               const bool value): Parameter (shortName, longName, description, required) {
    d_data_ptr = par_ptr;
    *d_data_ptr = value;
}
void BoolParameter::setValue ( const std::string & value ) {
    char firstChar = tolower (value[0]);
    setValue ((firstChar == 'f' || firstChar == '0') ? false : true);
}

void BoolParameter::setValue ( const bool value ) { *d_data_ptr = value; set(); }
/* FloatParameter */
FloatParameter::FloatParameter ( double *par_ptr, const std::string & shortName,
                                const std::string & longName,
                                const std::string & description,
                                const bool required, 
                                const double value ): Parameter (shortName, longName, description, required) {
    d_data_ptr = par_ptr;
    *d_data_ptr = value;
}
void FloatParameter::setValue ( const std::string & value ) { setValue (atof (value.c_str ())); }
void FloatParameter::setValue ( const double value) { *d_data_ptr = value; set (); }
/* StringParameter */
StringParameter::StringParameter (std::string * par_ptr, const std::string & shortName,
                                  const std::string & longName,
                                  const std::string & description,
                                  const bool required, 
                                  const std::string & value): Parameter (shortName, longName, description, required) {
    d_data_ptr = par_ptr;
    *d_data_ptr = value;
}

void StringParameter::setValue ( const std::string & value ) { *d_data_ptr = value; set(); }

