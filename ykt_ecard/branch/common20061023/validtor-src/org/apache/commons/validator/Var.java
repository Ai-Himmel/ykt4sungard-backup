/*
 * $Header: /home/cvs/jakarta-commons/validator/src/share/org/apache/commons/validator/Var.java,v 1.11 2004/02/21 17:10:29 rleland Exp $
 * $Revision: 1.11 $
 * $Date: 2004/02/21 17:10:29 $
 *
 * ====================================================================
 * Copyright 2001-2004 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.commons.validator;

import java.io.Serializable;

/**
 * A variable that can be associated with a <code>Field</code> for
 * passing in information to a pluggable validator.  Instances of this class are
 * configured with a &lt;var&gt; xml element.
 */
public class Var implements Cloneable, Serializable {

    /**
     * Int Constant for JavaScript type.  This can be used
     * when auto-generating JavaScript.
     */
    public static final String JSTYPE_INT = "int";

    /**
     * String Constant for JavaScript type.  This can be used
     * when auto-generating JavaScript.
     */
    public static final String JSTYPE_STRING = "string";

    /**
     * Regular Expression Constant for JavaScript type.  This can be used
     * when auto-generating JavaScript.
     */
    public static final String JSTYPE_REGEXP = "regexp";

    /**
     * The name of the variable.
     */
    private String name = null;

    /**
     * The name of the value.
     */
    private String value = null;

    /**
     * The optional JavaScript type of the variable.
     */
    private String jsType = null;

    public Var() {
        super();
    }

    public Var(String name, String value, String jsType) {
        this.name = name;
        this.value = value;
        this.jsType = jsType;
    }

    /**
     * Gets the name of the variable.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Sets the name of the variable.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Gets the value of the variable.
     */
    public String getValue() {
        return this.value;
    }

    /**
     * Sets the value of the variable.
     */
    public void setValue(String value) {
        this.value = value;
    }

    /**
     * Gets the JavaScript type of the variable.
     */
    public String getJsType() {
        return this.jsType;
    }

    /**
     * Sets the JavaScript type of the variable.
     */
    public void setJsType(String jsType) {
        this.jsType = jsType;
    }

    /**
     * Creates and returns a copy of this object.
     */
    public Object clone() {
        try {
            return super.clone();

        } catch(CloneNotSupportedException e) {
            throw new RuntimeException(e.toString());
        }
    }

    /**
     * Returns a string representation of the object.
     */
    public String toString() {
        StringBuffer results = new StringBuffer();

        results.append("Var: name=");
        results.append(name);
        results.append("  value=");
        results.append(value);
        results.append("  jsType=");
        results.append(jsType);
        results.append("\n");

        return results.toString();
    }

}