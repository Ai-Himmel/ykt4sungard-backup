/**
 * UserContext.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class UserContext  implements java.io.Serializable {
    private java.lang.String userContextKey;
    private java.lang.String[] userCategories;
    private oasis.names.tc.wsrp.v1.types.UserProfile profile;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public UserContext() {
    }

    public UserContext(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.UserProfile profile,
           java.lang.String[] userCategories,
           java.lang.String userContextKey) {
           this.userContextKey = userContextKey;
           this.userCategories = userCategories;
           this.profile = profile;
           this.extensions = extensions;
    }


    /**
     * Gets the userContextKey value for this UserContext.
     * 
     * @return userContextKey
     */
    public java.lang.String getUserContextKey() {
        return userContextKey;
    }


    /**
     * Sets the userContextKey value for this UserContext.
     * 
     * @param userContextKey
     */
    public void setUserContextKey(java.lang.String userContextKey) {
        this.userContextKey = userContextKey;
    }


    /**
     * Gets the userCategories value for this UserContext.
     * 
     * @return userCategories
     */
    public java.lang.String[] getUserCategories() {
        return userCategories;
    }


    /**
     * Sets the userCategories value for this UserContext.
     * 
     * @param userCategories
     */
    public void setUserCategories(java.lang.String[] userCategories) {
        this.userCategories = userCategories;
    }

    public java.lang.String getUserCategories(int i) {
        return this.userCategories[i];
    }

    public void setUserCategories(int i, java.lang.String _value) {
        this.userCategories[i] = _value;
    }


    /**
     * Gets the profile value for this UserContext.
     * 
     * @return profile
     */
    public oasis.names.tc.wsrp.v1.types.UserProfile getProfile() {
        return profile;
    }


    /**
     * Sets the profile value for this UserContext.
     * 
     * @param profile
     */
    public void setProfile(oasis.names.tc.wsrp.v1.types.UserProfile profile) {
        this.profile = profile;
    }


    /**
     * Gets the extensions value for this UserContext.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this UserContext.
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
        if (!(obj instanceof UserContext)) return false;
        UserContext other = (UserContext) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.userContextKey==null && other.getUserContextKey()==null) || 
             (this.userContextKey!=null &&
              this.userContextKey.equals(other.getUserContextKey()))) &&
            ((this.userCategories==null && other.getUserCategories()==null) || 
             (this.userCategories!=null &&
              java.util.Arrays.equals(this.userCategories, other.getUserCategories()))) &&
            ((this.profile==null && other.getProfile()==null) || 
             (this.profile!=null &&
              this.profile.equals(other.getProfile()))) &&
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
        if (getUserContextKey() != null) {
            _hashCode += getUserContextKey().hashCode();
        }
        if (getUserCategories() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getUserCategories());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getUserCategories(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getProfile() != null) {
            _hashCode += getProfile().hashCode();
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
        new org.apache.axis.description.TypeDesc(UserContext.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UserContext"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userContextKey");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userContextKey"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userCategories");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userCategories"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("profile");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "profile"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UserProfile"));
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
