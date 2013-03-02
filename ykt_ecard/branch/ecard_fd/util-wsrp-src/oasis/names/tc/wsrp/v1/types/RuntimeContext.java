/**
 * RuntimeContext.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class RuntimeContext  implements java.io.Serializable {
    private java.lang.String userAuthentication;
    private java.lang.String portletInstanceKey;
    private java.lang.String namespacePrefix;
    private oasis.names.tc.wsrp.v1.types.Templates templates;
    private java.lang.String sessionID;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public RuntimeContext() {
    }

    public RuntimeContext(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           java.lang.String namespacePrefix,
           java.lang.String portletInstanceKey,
           java.lang.String sessionID,
           oasis.names.tc.wsrp.v1.types.Templates templates,
           java.lang.String userAuthentication) {
           this.userAuthentication = userAuthentication;
           this.portletInstanceKey = portletInstanceKey;
           this.namespacePrefix = namespacePrefix;
           this.templates = templates;
           this.sessionID = sessionID;
           this.extensions = extensions;
    }


    /**
     * Gets the userAuthentication value for this RuntimeContext.
     * 
     * @return userAuthentication
     */
    public java.lang.String getUserAuthentication() {
        return userAuthentication;
    }


    /**
     * Sets the userAuthentication value for this RuntimeContext.
     * 
     * @param userAuthentication
     */
    public void setUserAuthentication(java.lang.String userAuthentication) {
        this.userAuthentication = userAuthentication;
    }


    /**
     * Gets the portletInstanceKey value for this RuntimeContext.
     * 
     * @return portletInstanceKey
     */
    public java.lang.String getPortletInstanceKey() {
        return portletInstanceKey;
    }


    /**
     * Sets the portletInstanceKey value for this RuntimeContext.
     * 
     * @param portletInstanceKey
     */
    public void setPortletInstanceKey(java.lang.String portletInstanceKey) {
        this.portletInstanceKey = portletInstanceKey;
    }


    /**
     * Gets the namespacePrefix value for this RuntimeContext.
     * 
     * @return namespacePrefix
     */
    public java.lang.String getNamespacePrefix() {
        return namespacePrefix;
    }


    /**
     * Sets the namespacePrefix value for this RuntimeContext.
     * 
     * @param namespacePrefix
     */
    public void setNamespacePrefix(java.lang.String namespacePrefix) {
        this.namespacePrefix = namespacePrefix;
    }


    /**
     * Gets the templates value for this RuntimeContext.
     * 
     * @return templates
     */
    public oasis.names.tc.wsrp.v1.types.Templates getTemplates() {
        return templates;
    }


    /**
     * Sets the templates value for this RuntimeContext.
     * 
     * @param templates
     */
    public void setTemplates(oasis.names.tc.wsrp.v1.types.Templates templates) {
        this.templates = templates;
    }


    /**
     * Gets the sessionID value for this RuntimeContext.
     * 
     * @return sessionID
     */
    public java.lang.String getSessionID() {
        return sessionID;
    }


    /**
     * Sets the sessionID value for this RuntimeContext.
     * 
     * @param sessionID
     */
    public void setSessionID(java.lang.String sessionID) {
        this.sessionID = sessionID;
    }


    /**
     * Gets the extensions value for this RuntimeContext.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this RuntimeContext.
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
        if (!(obj instanceof RuntimeContext)) return false;
        RuntimeContext other = (RuntimeContext) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.userAuthentication==null && other.getUserAuthentication()==null) || 
             (this.userAuthentication!=null &&
              this.userAuthentication.equals(other.getUserAuthentication()))) &&
            ((this.portletInstanceKey==null && other.getPortletInstanceKey()==null) || 
             (this.portletInstanceKey!=null &&
              this.portletInstanceKey.equals(other.getPortletInstanceKey()))) &&
            ((this.namespacePrefix==null && other.getNamespacePrefix()==null) || 
             (this.namespacePrefix!=null &&
              this.namespacePrefix.equals(other.getNamespacePrefix()))) &&
            ((this.templates==null && other.getTemplates()==null) || 
             (this.templates!=null &&
              this.templates.equals(other.getTemplates()))) &&
            ((this.sessionID==null && other.getSessionID()==null) || 
             (this.sessionID!=null &&
              this.sessionID.equals(other.getSessionID()))) &&
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
        if (getUserAuthentication() != null) {
            _hashCode += getUserAuthentication().hashCode();
        }
        if (getPortletInstanceKey() != null) {
            _hashCode += getPortletInstanceKey().hashCode();
        }
        if (getNamespacePrefix() != null) {
            _hashCode += getNamespacePrefix().hashCode();
        }
        if (getTemplates() != null) {
            _hashCode += getTemplates().hashCode();
        }
        if (getSessionID() != null) {
            _hashCode += getSessionID().hashCode();
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
        new org.apache.axis.description.TypeDesc(RuntimeContext.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "RuntimeContext"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userAuthentication");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userAuthentication"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("portletInstanceKey");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "portletInstanceKey"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("namespacePrefix");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "namespacePrefix"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("templates");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "templates"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Templates"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sessionID");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "sessionID"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
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
