/*
 * $Header: /home/cvs/jakarta-commons/validator/src/share/org/apache/commons/validator/ValidatorResults.java,v 1.10 2004/02/21 17:10:29 rleland Exp $
 * $Revision: 1.10 $
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
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * This contains the results of a set of validation rules processed 
 * on a JavaBean.
 */
public class ValidatorResults implements Serializable {

    /**
     * Map of validation results.
     */
    protected Map hResults = new HashMap();

    /**
     * Merge another ValidatorResults into mine.
     */
    public void merge(ValidatorResults results) {
        this.hResults.putAll(results.hResults);
    }

    /**
     * Add a the result of a validator action.
     */
    public void add(Field field, String validatorName, boolean result) {
        this.add(field, validatorName, result, null);
    }

    /**
     * Add a the result of a validator action.
     */
    public void add(
            Field field,
            String validatorName,
            boolean result,
            Object value) {

        ValidatorResult validatorResult = this.getValidatorResult(field.getKey());

        if (validatorResult == null) {
            validatorResult = new ValidatorResult(field);
            this.hResults.put(field.getKey(), validatorResult);
        }

        validatorResult.add(validatorName, result, value);
    }

    /**
     * Clear all results recorded by this object.
     */
    public void clear() {
        this.hResults.clear();
    }

    /**
     * Return <code>true</code> if there are no messages recorded
     * in this collection, or <code>false</code> otherwise.
     * @deprecated Use isEmpty() instead.
     */
    public boolean empty() {
        return this.isEmpty();
    }

    /**
     * Return <code>true</code> if there are no messages recorded
     * in this collection, or <code>false</code> otherwise.
     */
    public boolean isEmpty() {
        return this.hResults.isEmpty();
    }

    /**
     * Gets the <code>ValidatorResult</code> associated
     * with the key passed in.  The key the <code>ValidatorResult</code>
     * is stored under is the <code>Field</code>'s getKey method.
     *
     * @param key The key generated from <code>Field</code> (this is often just
     * the field name).
     */
    public ValidatorResult getValidatorResult(String key) {
        return (ValidatorResult) this.hResults.get(key);
    }

    /**
     * Return the set of all recorded messages, without distinction
     * by which property the messages are associated with.  If there are
     * no messages recorded, an empty enumeration is returned.
     * @deprecated Use getPropertyNames() instead.
     */
    public Iterator get() {
        if (hResults.isEmpty()) {
            return Collections.EMPTY_LIST.iterator();
        }

        return hResults.keySet().iterator();
    }

    /**
     * Return the set of property names for which at least one message has
     * been recorded.  If there are no messages, an empty Iterator is returned.
     * If you have recorded global messages, the String value of
     * <code>ActionMessages.GLOBAL_MESSAGE</code> will be one of the returned
     * property names.
     * @deprecated Use getPropertyNames() instead.
     */
    public Iterator properties() {
        return hResults.keySet().iterator();
    }

    /**
     * Return the set of property names for which at least one message has
     * been recorded.
     * @return An unmodifiable Set of the property names.
     */
    public Set getPropertyNames() {
        return Collections.unmodifiableSet(this.hResults.keySet());
    }

    /**
     * Get a <code>Map</code> of any <code>Object</code>s returned from
     * validation routines.
     */
    public Map getResultValueMap() {
        Map results = new HashMap();

        for (Iterator i = hResults.keySet().iterator(); i.hasNext();) {
            String propertyKey = (String) i.next();
            ValidatorResult vr = this.getValidatorResult(propertyKey);

            Map actions = vr.getActionMap();
            for (Iterator x = actions.keySet().iterator(); x.hasNext();) {
                String actionKey = (String) x.next();
                ValidatorResult.ResultStatus rs =
                        (ValidatorResult.ResultStatus) actions.get(actionKey);

                if (rs != null) {
                    Object result = rs.getResult();

                    if (result != null && !(result instanceof Boolean)) {
                        results.put(propertyKey, result);
                    }
                }
            }
        }

        return results;
    }

}
