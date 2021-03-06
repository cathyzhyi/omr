/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2015, 2017
 *
 *  This program and the accompanying materials are made available
 *  under the terms of the Eclipse Public License v1.0 and
 *  Apache License v2.0 which accompanies this distribution.
 *
 *      The Eclipse Public License is available at
 *      http://www.eclipse.org/legal/epl-v10.html
 *
 *      The Apache License v2.0 is available at
 *      http://www.opensource.org/licenses/apache2.0.php
 *
 * Contributors:
 *    Multiple authors (IBM Corp.) - initial implementation and documentation
 *******************************************************************************/

#ifndef CLASSUDT_HPP
#define CLASSUDT_HPP

#include "ddr/config.hpp"

#include "ddr/ir/ClassType.hpp"
#include "ddr/error.hpp"

/* This type represents both class and struct types */
class ClassUDT: public ClassType
{
public:
	ClassUDT *_superClass;
	bool _isClass;

	ClassUDT(size_t size, bool isClass = true, unsigned int lineNumber = 0);
	virtual ~ClassUDT();

	virtual string getSymbolKindName();

	virtual DDR_RC acceptVisitor(TypeVisitor const &visitor);

	bool operator==(Type const & rhs) const;
	virtual bool compareToClass(ClassUDT const &) const;
};

#endif /* CLASSUDT_HPP */
