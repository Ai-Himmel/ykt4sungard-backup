/**
 * PropertyList.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class PropertyList  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.Property[] properties;
    private oasis.names.tc.wsrp.v1.types.ResetProperty[] resetProperties;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public PropertyList() {
    }

    public PropertyList(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.Property[] properties,
           oasis.names.tc.wsrp.v1.types.ResetProperty[] resetProperties) {
           this.properties = properties;
           this.resetProperties = resetProperties;
           this.extensions = extensions;
    }


    /**
     * Gets the properties value for this PropertyList.
     * 
     * @return properties
     */
    public oasis.names.tc.wsrp.v1.types.Property[] getProperties() {
        return properties;
    }


    /**
     * Sets the properties value for this PropertyList.
     * 
     * @param properties
     */
    public void setProperties(oasis.names.tc.wsrp.v1.types.Property[] properties) {
        this.properties = properties;
    }

    public oasis.names.tc.wsrp.v1.types.Property getProperties(int i) {
        return this.properties[i];
    }

    public void setProperties(int i, oasis.names.tc.wsrp.v1.types.Property _value) {
        this.properties[i] = _value;
    }


    /**
     * Gets the resetProperties value for this PropertyList.
     * 
     * @return resetProperties
     */
    public oasis.names.tc.wsrp.v1.types.ResetProperty[] getResetProperties() {
        return resetProperties;
    }


    /**
     * Sets the resetProperties value for this PropertyList.
     * 
     * @param resetProperties
     */
    public void setResetProperties(oasis.names.tc.wsrp.v1.types.ResetProperty[] resetProperties) {
        this.resetProperties = resetProperties;
    }

    public oasis.names.tc.wsrp.v1.types.ResetProperty getResetProperties(int i) {
        return this.resetProperties[i];
    }

    public void setResetProperties(int i, oasis.names.tc.wsrp.v1.types.ResetProperty _value) {
        this.resetProperties[i] = _value;
    }


    /**
     * Gets the extensions value for this PropertyList.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this PropertyList.
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
        if (!(obj instanceof PropertyList)) return false;
        PropertyList other = (PropertyList) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.properties==null && other.getProperties()==null) || 
             (this.properties!=null &&
              java.util.Arrays.equals(this.properties, other.getProperties()))) &&
            ((this.resetProperties==null && other.getResetProperties()==null) || 
             (this.resetProperties!=null &&
              java.util.Arrays.equals(this.resetProperties, other.getResetProperties()))) &&
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
        if (getProperties() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getProperties());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getProperties(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getResetProperties() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getResetProperties());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getResetProperties(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
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
        new org.apache.axis.description.TypeDesc(PropertyList.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PropertyList"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("properties");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "properties"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Property"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("resetProperties");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "resetProperties"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ResetProperty"));
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
