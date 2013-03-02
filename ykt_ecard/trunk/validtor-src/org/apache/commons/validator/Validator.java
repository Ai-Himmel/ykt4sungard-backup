/*
 * $Header: /home/cvs/jakarta-commons/validator/src/share/org/apache/commons/validator/Validator.java,v 1.34 2004/02/21 17:10:29 rleland Exp $
 * $Revision: 1.34 $
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
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Validations are processed by the validate method. An instance of
 * <code>ValidatorResources</code> is used to define the validators
 * (validation methods) and the validation rules for a JavaBean.
 */
public class Validator implements Serializable {

    /**
     * Logger.
     * @deprecated Subclasses should use their own logging instance.
     */
    protected static Log log = LogFactory.getLog(Validator.class);

    /**
     * Resources key the JavaBean is stored to perform validation on.
     */
    public static final String BEAN_PARAM = "java.lang.Object";

    /**
     * Resources key the JavaBean is stored to perform validation on.
     * @deprecated Use BEAN_PARAM instead.
     */
    public static final String BEAN_KEY = BEAN_PARAM;

    /**
     * Resources key the <code>ValidatorAction</code> is stored under.
     * This will be automatically passed into a validation method
     * with the current <code>ValidatorAction</code> if it is
     * specified in the method signature.
     */
    public static final String VALIDATOR_ACTION_PARAM =
            "org.apache.commons.validator.ValidatorAction";

    /**
     * Resources key the <code>ValidatorAction</code> is stored under.
     * This will be automatically passed into a validation method
     * with the current <code>ValidatorAction</code> if it is
     * specified in the method signature.
     * @deprecated Use VALIDATOR_ACTION_PARAM instead.
     */
    public static final String VALIDATOR_ACTION_KEY = VALIDATOR_ACTION_PARAM;

    /**
     * Resources key the <code>Field</code> is stored under.
     * This will be automatically passed into a validation method
     * with the current <code>Field</code> if it is
     * specified in the method signature.
     */
    public static final String FIELD_PARAM = "org.apache.commons.validator.Field";

    /**
     * Resources key the <code>Field</code> is stored under.
     * This will be automatically passed into a validation method
     * with the current <code>Field</code> if it is
     * specified in the method signature.
     * @deprecated Use FIELD_PARAM instead.
     */
    public static final String FIELD_KEY = FIELD_PARAM;

    /**
     * Resources key the <code>Validator</code> is stored under.
     * This will be automatically passed into a validation method
     * with the current <code>Validator</code> if it is
     * specified in the method signature.
     */
    public static final String VALIDATOR_PARAM =
            "org.apache.commons.validator.Validator";

    /**
     * Resources key the <code>Validator</code> is stored under.
     * This will be automatically passed into a validation method
     * with the current <code>Validator</code> if it is
     * specified in the method signature.
     * @deprecated Use VALIDATOR_PARAM instead.
     */
    public static final String VALIDATOR_KEY = VALIDATOR_PARAM;

    /**
     * Resources key the <code>Locale</code> is stored.
     * This will be used to retrieve the appropriate
     * <code>FormSet</code> and <code>Form</code> to be
     * processed.
     */
    public static final String LOCALE_PARAM = "java.util.Locale";

    /**
     * Resources key the <code>Locale</code> is stored.
     * This will be used to retrieve the appropriate
     * <code>FormSet</code> and <code>Form</code> to be
     * processed.
     * @deprecated Use LOCALE_PARAM instead.
     */
    public static final String LOCALE_KEY = LOCALE_PARAM;

    protected ValidatorResources resources = null;

    protected String formName = null;

    /**
     * Maps validation method parameter class names to the objects to be passed
     * into the method.
     */
    protected Map parameters = new HashMap();

    /**
     * @deprecated Use parameters instead.
     */
    protected HashMap hResources = (HashMap) this.parameters;

    /**
     * The current page number to validate.
     */
    protected int page = 0;

    /**
     * The class loader to use for instantiating application objects.
     * If not specified, the context class loader, or the class loader
     * used to load Digester itself, is used, based on the value of the
     * <code>useContextClassLoader</code> variable.
     */
    protected ClassLoader classLoader = null;

    /**
     * Whether or not to use the Context ClassLoader when loading classes
     * for instantiating new objects.  Default is <code>false</code>.
     */
    protected boolean useContextClassLoader = false;

    /**
     * Set this to true to not return Fields that pass validation.  Only return failures.
     */
    protected boolean onlyReturnErrors = false;

    /**
     * Construct a <code>Validator</code> that will
     * use the <code>ValidatorResources</code>
     * passed in to retrieve pluggable validators
     * the different sets of validation rules.
     *
     * @param resources <code>ValidatorResources</code> to use during validation.
     */
    public Validator(ValidatorResources resources) {
        this(resources, null);
    }

    /**
     * Construct a <code>Validator</code> that will
     * use the <code>ValidatorResources</code>
     * passed in to retrieve pluggable validators
     * the different sets of validation rules.
     *
     * @param resources <code>ValidatorResources</code> to use during validation.
     * @param formName Key used for retrieving the set of validation rules.
     */
    public Validator(ValidatorResources resources, String formName) {
        if (resources == null) {
            throw new IllegalArgumentException("Resources cannot be null.");
        }

        this.resources = resources;
        this.formName = formName;
    }

    /**
     * Add a resource to be used during the processing
     * of validations.
     *
     * @param parameterClassName The full class name of the parameter of the
     * validation method that corresponds to the value/instance passed in with it.
     *
     * @param parameterValue The instance that will be passed into the
     * validation method.
     * @deprecated Use setParameter(String, Object) instead.
     */
    public void addResource(String parameterClassName, Object parameterValue) {
        this.setParameter(parameterClassName, parameterValue);
    }

    /**
     * Set a parameter of a pluggable validation method.
     *
     * @param parameterClassName The full class name of the parameter of the
     * validation method that corresponds to the value/instance passed in with it.
     *
     * @param parameterValue The instance that will be passed into the
     * validation method.
     */
    public void setParameter(String parameterClassName, Object parameterValue) {
        this.parameters.put(parameterClassName, parameterValue);
    }

    /**
     * Get a resource to be used during the processing of validations.
     *
     * @param parameterClassName The full class name of the parameter of the
     * validation method that corresponds to the value/instance passed in with it.
     * @deprecated Use getParameterValue(String) instead.
     */
    public Object getResource(String parameterClassName) {
        return this.getParameterValue(parameterClassName);
    }

    /**
     * Returns the value of the specified parameter that will be used during the
     * processing of validations.
     *
     * @param parameterClassName The full class name of the parameter of the
     * validation method that corresponds to the value/instance passed in with it.
     */
    public Object getParameterValue(String parameterClassName) {
        return this.parameters.get(parameterClassName);
    }

    /**
     * Gets the form name which is the key to a set of validation rules.
     */
    public String getFormName() {
        return formName;
    }

    /**
     * Sets the form name which is the key to a set of validation rules.
     */
    public void setFormName(String formName) {
        this.formName = formName;
    }

    /**
     * Gets the page.  This in conjunction with the page property of
     * a <code>Field<code> can control the processing of fields. If the field's
     * page is less than or equal to this page value, it will be processed.
     */
    public int getPage() {
        return page;
    }

    /**
     * Sets the page.  This in conjunction with the page property of
     * a <code>Field<code> can control the processing of fields. If the field's page
     * is less than or equal to this page value, it will be processed.
     */
    public void setPage(int page) {
        this.page = page;
    }

    /**
     * Clears the form name, resources that were added, and the page that was
     * set (if any).  This can be called to reinitialize the Validator instance
     * so it can be reused.  The form name (key to set of validation rules) and any
     * resources needed, like the JavaBean being validated, will need to
     * set and/or added to this instance again.  The
     * <code>ValidatorResources</code> will not be removed since it can be used
     * again and is thread safe.
     */
    public void clear() {
        this.formName = null;
        this.parameters = new HashMap();
        this.hResources = (HashMap) this.parameters;
        this.page = 0;
    }

    /**
     * Return the boolean as to whether the context classloader should be used.
     */
    public boolean getUseContextClassLoader() {
        return this.useContextClassLoader;
    }

    /**
     * Determine whether to use the Context ClassLoader (the one found by
     * calling <code>Thread.currentThread().getContextClassLoader()</code>)
     * to resolve/load classes that are defined in various rules.  If not
     * using Context ClassLoader, then the class-loading defaults to
     * using the calling-class' ClassLoader.
     *
     * @param use determines whether to use Context ClassLoader.
     */
    public void setUseContextClassLoader(boolean use) {
        this.useContextClassLoader = use;
    }

    /**
     * Return the class loader to be used for instantiating application objects
     * when required.  This is determined based upon the following rules:
     * <ul>
     * <li>The class loader set by <code>setClassLoader()</code>, if any</li>
     * <li>The thread context class loader, if it exists and the
     *     <code>useContextClassLoader</code> property is set to true</li>
     * <li>The class loader used to load the Digester class itself.
     * </ul>
     */
    public ClassLoader getClassLoader() {
        if (this.classLoader != null) {
            return this.classLoader;
        }

        if (this.useContextClassLoader) {
            ClassLoader contextLoader = Thread.currentThread().getContextClassLoader();
            if (contextLoader != null) {
                return contextLoader;
            }
        }

        return this.getClass().getClassLoader();
    }

    /**
     * Set the class loader to be used for instantiating application objects
     * when required.
     *
     * @param classLoader The new class loader to use, or <code>null</code>
     *  to revert to the standard rules
     */
    public void setClassLoader(ClassLoader classLoader) {
        this.classLoader = classLoader;
    }

    /**
     * Performs validations based on the configured resources.
     *
     * @return The <code>Map</code> returned uses the property of the
     * <code>Field</code> for the key and the value is the number of error the
     * field had.
     */
    public ValidatorResults validate() throws ValidatorException {
        Locale locale = (Locale) this.getParameterValue(LOCALE_PARAM);

        if (locale == null) {
            locale = Locale.getDefault();
        }

        this.setParameter(VALIDATOR_PARAM, this);

        Form form = this.resources.getForm(locale, this.formName);
        if (form != null) {
            return form.validate(
                this.parameters,
                this.resources.getValidatorActions(),
                this.page);
        }

        return new ValidatorResults();
    }

    /**
     * Returns true if the Validator is only returning Fields that fail validation.
     */
    public boolean getOnlyReturnErrors() {
        return onlyReturnErrors;
    }

    /**
     * Configures which Fields the Validator returns from the validate() method.  Set this
     * to true to only return Fields that failed validation.  By default, validate() returns
     * all fields.
     */
    public void setOnlyReturnErrors(boolean onlyReturnErrors) {
        this.onlyReturnErrors = onlyReturnErrors;
    }

}
