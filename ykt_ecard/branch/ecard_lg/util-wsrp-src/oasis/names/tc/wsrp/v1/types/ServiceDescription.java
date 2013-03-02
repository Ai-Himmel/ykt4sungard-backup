/**
 * ServiceDescription.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class ServiceDescription  implements java.io.Serializable {
    private boolean requiresRegistration;
    private oasis.names.tc.wsrp.v1.types.PortletDescription[] offeredPortlets;
    private oasis.names.tc.wsrp.v1.types.ItemDescription[] userCategoryDescriptions;
    private oasis.names.tc.wsrp.v1.types.ItemDescription[] customUserProfileItemDescriptions;
    private oasis.names.tc.wsrp.v1.types.ItemDescription[] customWindowStateDescriptions;
    private oasis.names.tc.wsrp.v1.types.ItemDescription[] customModeDescriptions;
    private oasis.names.tc.wsrp.v1.types.CookieProtocol requiresInitCookie;
    private oasis.names.tc.wsrp.v1.types.ModelDescription registrationPropertyDescription;
    private java.lang.String[] locales;
    private oasis.names.tc.wsrp.v1.types.ResourceList resourceList;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public ServiceDescription() {
    }

    public ServiceDescription(
           oasis.names.tc.wsrp.v1.types.ItemDescription[] customModeDescriptions,
           oasis.names.tc.wsrp.v1.types.ItemDescription[] customUserProfileItemDescriptions,
           oasis.names.tc.wsrp.v1.types.ItemDescription[] customWindowStateDescriptions,
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           java.lang.String[] locales,
           oasis.names.tc.wsrp.v1.types.PortletDescription[] offeredPortlets,
           oasis.names.tc.wsrp.v1.types.ModelDescription registrationPropertyDescription,
           oasis.names.tc.wsrp.v1.types.CookieProtocol requiresInitCookie,
           boolean requiresRegistration,
           oasis.names.tc.wsrp.v1.types.ResourceList resourceList,
           oasis.names.tc.wsrp.v1.types.ItemDescription[] userCategoryDescriptions) {
           this.requiresRegistration = requiresRegistration;
           this.offeredPortlets = offeredPortlets;
           this.userCategoryDescriptions = userCategoryDescriptions;
           this.customUserProfileItemDescriptions = customUserProfileItemDescriptions;
           this.customWindowStateDescriptions = customWindowStateDescriptions;
           this.customModeDescriptions = customModeDescriptions;
           this.requiresInitCookie = requiresInitCookie;
           this.registrationPropertyDescription = registrationPropertyDescription;
           this.locales = locales;
           this.resourceList = resourceList;
           this.extensions = extensions;
    }


    /**
     * Gets the requiresRegistration value for this ServiceDescription.
     * 
     * @return requiresRegistration
     */
    public boolean isRequiresRegistration() {
        return requiresRegistration;
    }


    /**
     * Sets the requiresRegistration value for this ServiceDescription.
     * 
     * @param requiresRegistration
     */
    public void setRequiresRegistration(boolean requiresRegistration) {
        this.requiresRegistration = requiresRegistration;
    }


    /**
     * Gets the offeredPortlets value for this ServiceDescription.
     * 
     * @return offeredPortlets
     */
    public oasis.names.tc.wsrp.v1.types.PortletDescription[] getOfferedPortlets() {
        return offeredPortlets;
    }


    /**
     * Sets the offeredPortlets value for this ServiceDescription.
     * 
     * @param offeredPortlets
     */
    public void setOfferedPortlets(oasis.names.tc.wsrp.v1.types.PortletDescription[] offeredPortlets) {
        this.offeredPortlets = offeredPortlets;
    }

    public oasis.names.tc.wsrp.v1.types.PortletDescription getOfferedPortlets(int i) {
        return this.offeredPortlets[i];
    }

    public void setOfferedPortlets(int i, oasis.names.tc.wsrp.v1.types.PortletDescription _value) {
        this.offeredPortlets[i] = _value;
    }


    /**
     * Gets the userCategoryDescriptions value for this ServiceDescription.
     * 
     * @return userCategoryDescriptions
     */
    public oasis.names.tc.wsrp.v1.types.ItemDescription[] getUserCategoryDescriptions() {
        return userCategoryDescriptions;
    }


    /**
     * Sets the userCategoryDescriptions value for this ServiceDescription.
     * 
     * @param userCategoryDescriptions
     */
    public void setUserCategoryDescriptions(oasis.names.tc.wsrp.v1.types.ItemDescription[] userCategoryDescriptions) {
        this.userCategoryDescriptions = userCategoryDescriptions;
    }

    public oasis.names.tc.wsrp.v1.types.ItemDescription getUserCategoryDescriptions(int i) {
        return this.userCategoryDescriptions[i];
    }

    public void setUserCategoryDescriptions(int i, oasis.names.tc.wsrp.v1.types.ItemDescription _value) {
        this.userCategoryDescriptions[i] = _value;
    }


    /**
     * Gets the customUserProfileItemDescriptions value for this ServiceDescription.
     * 
     * @return customUserProfileItemDescriptions
     */
    public oasis.names.tc.wsrp.v1.types.ItemDescription[] getCustomUserProfileItemDescriptions() {
        return customUserProfileItemDescriptions;
    }


    /**
     * Sets the customUserProfileItemDescriptions value for this ServiceDescription.
     * 
     * @param customUserProfileItemDescriptions
     */
    public void setCustomUserProfileItemDescriptions(oasis.names.tc.wsrp.v1.types.ItemDescription[] customUserProfileItemDescriptions) {
        this.customUserProfileItemDescriptions = customUserProfileItemDescriptions;
    }

    public oasis.names.tc.wsrp.v1.types.ItemDescription getCustomUserProfileItemDescriptions(int i) {
        return this.customUserProfileItemDescriptions[i];
    }

    public void setCustomUserProfileItemDescriptions(int i, oasis.names.tc.wsrp.v1.types.ItemDescription _value) {
        this.customUserProfileItemDescriptions[i] = _value;
    }


    /**
     * Gets the customWindowStateDescriptions value for this ServiceDescription.
     * 
     * @return customWindowStateDescriptions
     */
    public oasis.names.tc.wsrp.v1.types.ItemDescription[] getCustomWindowStateDescriptions() {
        return customWindowStateDescriptions;
    }


    /**
     * Sets the customWindowStateDescriptions value for this ServiceDescription.
     * 
     * @param customWindowStateDescriptions
     */
    public void setCustomWindowStateDescriptions(oasis.names.tc.wsrp.v1.types.ItemDescription[] customWindowStateDescriptions) {
        this.customWindowStateDescriptions = customWindowStateDescriptions;
    }

    public oasis.names.tc.wsrp.v1.types.ItemDescription getCustomWindowStateDescriptions(int i) {
        return this.customWindowStateDescriptions[i];
    }

    public void setCustomWindowStateDescriptions(int i, oasis.names.tc.wsrp.v1.types.ItemDescription _value) {
        this.customWindowStateDescriptions[i] = _value;
    }


    /**
     * Gets the customModeDescriptions value for this ServiceDescription.
     * 
     * @return customModeDescriptions
     */
    public oasis.names.tc.wsrp.v1.types.ItemDescription[] getCustomModeDescriptions() {
        return customModeDescriptions;
    }


    /**
     * Sets the customModeDescriptions value for this ServiceDescription.
     * 
     * @param customModeDescriptions
     */
    public void setCustomModeDescriptions(oasis.names.tc.wsrp.v1.types.ItemDescription[] customModeDescriptions) {
        this.customModeDescriptions = customModeDescriptions;
    }

    public oasis.names.tc.wsrp.v1.types.ItemDescription getCustomModeDescriptions(int i) {
        return this.customModeDescriptions[i];
    }

    public void setCustomModeDescriptions(int i, oasis.names.tc.wsrp.v1.types.ItemDescription _value) {
        this.customModeDescriptions[i] = _value;
    }


    /**
     * Gets the requiresInitCookie value for this ServiceDescription.
     * 
     * @return requiresInitCookie
     */
    public oasis.names.tc.wsrp.v1.types.CookieProtocol getRequiresInitCookie() {
        return requiresInitCookie;
    }


    /**
     * Sets the requiresInitCookie value for this ServiceDescription.
     * 
     * @param requiresInitCookie
     */
    public void setRequiresInitCookie(oasis.names.tc.wsrp.v1.types.CookieProtocol requiresInitCookie) {
        this.requiresInitCookie = requiresInitCookie;
    }


    /**
     * Gets the registrationPropertyDescription value for this ServiceDescription.
     * 
     * @return registrationPropertyDescription
     */
    public oasis.names.tc.wsrp.v1.types.ModelDescription getRegistrationPropertyDescription() {
        return registrationPropertyDescription;
    }


    /**
     * Sets the registrationPropertyDescription value for this ServiceDescription.
     * 
     * @param registrationPropertyDescription
     */
    public void setRegistrationPropertyDescription(oasis.names.tc.wsrp.v1.types.ModelDescription registrationPropertyDescription) {
        this.registrationPropertyDescription = registrationPropertyDescription;
    }


    /**
     * Gets the locales value for this ServiceDescription.
     * 
     * @return locales
     */
    public java.lang.String[] getLocales() {
        return locales;
    }


    /**
     * Sets the locales value for this ServiceDescription.
     * 
     * @param locales
     */
    public void setLocales(java.lang.String[] locales) {
        this.locales = locales;
    }

    public java.lang.String getLocales(int i) {
        return this.locales[i];
    }

    public void setLocales(int i, java.lang.String _value) {
        this.locales[i] = _value;
    }


    /**
     * Gets the resourceList value for this ServiceDescription.
     * 
     * @return resourceList
     */
    public oasis.names.tc.wsrp.v1.types.ResourceList getResourceList() {
        return resourceList;
    }


    /**
     * Sets the resourceList value for this ServiceDescription.
     * 
     * @param resourceList
     */
    public void setResourceList(oasis.names.tc.wsrp.v1.types.ResourceList resourceList) {
        this.resourceList = resourceList;
    }


    /**
     * Gets the extensions value for this ServiceDescription.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this ServiceDescription.
     * 
     * @param extensions
     */
    public void setExtensions(oasis.names.tc.wsrp.v1.types.Extension[] extensions) {
        this.extensions = extensions;
    }

    public oasis.names.tc.wsrp.v1.types.Extension getExtensions(int i) {
        return this.extensions[i];
    }

    public void setExtensions(int i, oasis.names.tc.wsrp.v1.types.Extension _value) {
        this.extensions[i] = _value;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof ServiceDescription)) return false;
        ServiceDescription other = (ServiceDescription) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            this.requiresRegistration == other.isRequiresRegistration() &&
            ((this.offeredPortlets==null && other.getOfferedPortlets()==null) || 
             (this.offeredPortlets!=null &&
              java.util.Arrays.equals(this.offeredPortlets, other.getOfferedPortlets()))) &&
            ((this.userCategoryDescriptions==null && other.getUserCategoryDescriptions()==null) || 
             (this.userCategoryDescriptions!=null &&
              java.util.Arrays.equals(this.userCategoryDescriptions, other.getUserCategoryDescriptions()))) &&
            ((this.customUserProfileItemDescriptions==null && other.getCustomUserProfileItemDescriptions()==null) || 
             (this.customUserProfileItemDescriptions!=null &&
              java.util.Arrays.equals(this.customUserProfileItemDescriptions, other.getCustomUserProfileItemDescriptions()))) &&
            ((this.customWindowStateDescriptions==null && other.getCustomWindowStateDescriptions()==null) || 
             (this.customWindowStateDescriptions!=null &&
              java.util.Arrays.equals(this.customWindowStateDescriptions, other.getCustomWindowStateDescriptions()))) &&
            ((this.customModeDescriptions==null && other.getCustomModeDescriptions()==null) || 
             (this.customModeDescriptions!=null &&
              java.util.Arrays.equals(this.customModeDescriptions, other.getCustomModeDescriptions()))) &&
            ((this.requiresInitCookie==null && other.getRequiresInitCookie()==null) || 
             (this.requiresInitCookie!=null &&
              this.requiresInitCookie.equals(other.getRequiresInitCookie()))) &&
            ((this.registrationPropertyDescription==null && other.getRegistrationPropertyDescription()==null) || 
             (this.registrationPropertyDescription!=null &&
              this.registrationPropertyDescription.equals(other.getRegistrationPropertyDescription()))) &&
            ((this.locales==null && other.getLocales()==null) || 
             (this.locales!=null &&
              java.util.Arrays.equals(this.locales, other.getLocales()))) &&
            ((this.resourceList==null && other.getResourceList()==null) || 
             (this.resourceList!=null &&
              this.resourceList.equals(other.getResourceList()))) &&
            ((this.extensions==null && other.getExtensions()==null) || 
             (this.extensions!=null &&
              java.util.Arrays.equals(this.extensions, other.getExtensions())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        _hashCode += (isRequiresRegistration() ? Boolean.TRUE : Boolean.FALSE).hashCode();
        if (getOfferedPortlets() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getOfferedPortlets());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getOfferedPortlets(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getUserCategoryDescriptions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getUserCategoryDescriptions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getUserCategoryDescriptions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getCustomUserProfileItemDescriptions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getCustomUserProfileItemDescriptions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getCustomUserProfileItemDescriptions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getCustomWindowStateDescriptions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getCustomWindowStateDescriptions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getCustomWindowStateDescriptions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getCustomModeDescriptions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getCustomModeDescriptions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getCustomModeDescriptions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getRequiresInitCookie() != null) {
            _hashCode += getRequiresInitCookie().hashCode();
        }
        if (getRegistrationPropertyDescription() != null) {
            _hashCode += getRegistrationPropertyDescription().hashCode();
        }
        if (getLocales() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getLocales());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getLocales(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getResourceList() != null) {
            _hashCode += getResourceList().hashCode();
        }
        if (getExtensions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getExtensions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getExtensions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(ServiceDescription.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ServiceDescription"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("requiresRegistration");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "requiresRegistration"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "boolean"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("offeredPortlets");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "offeredPortlets"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PortletDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userCategoryDescriptions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userCategoryDescriptions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ItemDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("customUserProfileItemDescriptions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "customUserProfileItemDescriptions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ItemDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("customWindowStateDescriptions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "customWindowStateDescriptions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ItemDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("customModeDescriptions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "customModeDescriptions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ItemDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("requiresInitCookie");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "requiresInitCookie"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "CookieProtocol"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("registrationPropertyDescription");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "registrationPropertyDescription"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ModelDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("locales");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "locales"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("resourceList");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "resourceList"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ResourceList"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("extensions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "extensions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Extension"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
