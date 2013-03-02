/**
 * MarkupResponse.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class MarkupResponse  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.MarkupContext markupContext;
    private oasis.names.tc.wsrp.v1.types.SessionContext sessionContext;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public MarkupResponse() {
    }

    public MarkupResponse(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.MarkupContext markupContext,
           oasis.names.tc.wsrp.v1.types.SessionContext sessionContext) {
           this.markupContext = markupContext;
           this.sessionContext = sessionContext;
           this.extensions = extensions;
    }


    /**
     * Gets the markupContext value for this MarkupResponse.
     * 
     * @return markupContext
     */
    public oasis.names.tc.wsrp.v1.types.MarkupContext getMarkupContext() {
        return markupContext;
    }


    /**
     * Sets the markupContext value for this MarkupResponse.
     * 
     * @param markupContext
     */
    public void setMarkupContext(oasis.names.tc.wsrp.v1.types.MarkupContext markupContext) {
        this.markupContext = markupContext;
    }


    /**
     * Gets the sessionContext value for this MarkupResponse.
     * 
     * @return sessionContext
     */
    public oasis.names.tc.wsrp.v1.types.SessionContext getSessionContext() {
        return sessionContext;
    }


    /**
     * Sets the sessionContext value for this MarkupResponse.
     * 
     * @param sessionContext
     */
    public void setSessionContext(oasis.names.tc.wsrp.v1.types.SessionContext sessionContext) {
        this.sessionContext = sessionContext;
    }


    /**
     * Gets the extensions value for this MarkupResponse.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this MarkupResponse.
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
        if (!(obj instanceof MarkupResponse)) return false;
        MarkupResponse other = (MarkupResponse) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.markupContext==null && other.getMarkupContext()==null) || 
             (this.markupContext!=null &&
              this.markupContext.equals(other.getMarkupContext()))) &&
            ((this.sessionContext==null && other.getSessionContext()==null) || 
             (this.sessionContext!=null &&
              this.sessionContext.equals(other.getSessionContext()))) &&
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
        if (getMarkupContext() != null) {
            _hashCode += getMarkupContext().hashCode();
        }
        if (getSessionContext() != null) {
            _hashCode += getSessionContext().hashCode();
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
        new org.apache.axis.description.TypeDesc(MarkupResponse.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "MarkupResponse"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("markupContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "markupContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "MarkupContext"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sessionContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "sessionContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "SessionContext"));
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
