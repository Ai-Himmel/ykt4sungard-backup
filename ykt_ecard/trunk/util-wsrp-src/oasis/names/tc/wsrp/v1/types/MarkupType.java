/**
 * MarkupType.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class MarkupType  implements java.io.Serializable {
    private java.lang.String mimeType;
    private java.lang.String[] modes;
    private java.lang.String[] windowStates;
    private java.lang.String[] locales;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public MarkupType() {
    }

    public MarkupType(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           java.lang.String[] locales,
           java.lang.String mimeType,
           java.lang.String[] modes,
           java.lang.String[] windowStates) {
           this.mimeType = mimeType;
           this.modes = modes;
           this.windowStates = windowStates;
           this.locales = locales;
           this.extensions = extensions;
    }


    /**
     * Gets the mimeType value for this MarkupType.
     * 
     * @return mimeType
     */
    public java.lang.String getMimeType() {
        return mimeType;
    }


    /**
     * Sets the mimeType value for this MarkupType.
     * 
     * @param mimeType
     */
    public void setMimeType(java.lang.String mimeType) {
        this.mimeType = mimeType;
    }


    /**
     * Gets the modes value for this MarkupType.
     * 
     * @return modes
     */
    public java.lang.String[] getModes() {
        return modes;
    }


    /**
     * Sets the modes value for this MarkupType.
     * 
     * @param modes
     */
    public void setModes(java.lang.String[] modes) {
        this.modes = modes;
    }

    public java.lang.String getModes(int i) {
        return this.modes[i];
    }

    public void setModes(int i, java.lang.String _value) {
        this.modes[i] = _value;
    }


    /**
     * Gets the windowStates value for this MarkupType.
     * 
     * @return windowStates
     */
    public java.lang.String[] getWindowStates() {
        return windowStates;
    }


    /**
     * Sets the windowStates value for this MarkupType.
     * 
     * @param windowStates
     */
    public void setWindowStates(java.lang.String[] windowStates) {
        this.windowStates = windowStates;
    }

    public java.lang.String getWindowStates(int i) {
        return this.windowStates[i];
    }

    public void setWindowStates(int i, java.lang.String _value) {
        this.windowStates[i] = _value;
    }


    /**
     * Gets the locales value for this MarkupType.
     * 
     * @return locales
     */
    public java.lang.String[] getLocales() {
        return locales;
    }


    /**
     * Sets the locales value for this MarkupType.
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
     * Gets the extensions value for this MarkupType.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this MarkupType.
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
        if (!(obj instanceof MarkupType)) return false;
        MarkupType other = (MarkupType) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.mimeType==null && other.getMimeType()==null) || 
             (this.mimeType!=null &&
              this.mimeType.equals(other.getMimeType()))) &&
            ((this.modes==null && other.getModes()==null) || 
             (this.modes!=null &&
              java.util.Arrays.equals(this.modes, other.getModes()))) &&
            ((this.windowStates==null && other.getWindowStates()==null) || 
             (this.windowStates!=null &&
              java.util.Arrays.equals(this.windowStates, other.getWindowStates()))) &&
            ((this.locales==null && other.getLocales()==null) || 
             (this.locales!=null &&
              java.util.Arrays.equals(this.locales, other.getLocales()))) &&
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
        if (getMimeType() != null) {
            _hashCode += getMimeType().hashCode();
        }
        if (getModes() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getModes());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getModes(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getWindowStates() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getWindowStates());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getWindowStates(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
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
        new org.apache.axis.description.TypeDesc(MarkupType.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "MarkupType"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("mimeType");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "mimeType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("modes");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "modes"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("windowStates");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "windowStates"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("locales");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "locales"));
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
