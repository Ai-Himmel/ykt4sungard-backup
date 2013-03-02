/**
 * UploadContext.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class UploadContext  implements java.io.Serializable {
    private java.lang.String mimeType;
    private byte[] uploadData;
    private oasis.names.tc.wsrp.v1.types.NamedString[] mimeAttributes;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public UploadContext() {
    }

    public UploadContext(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.NamedString[] mimeAttributes,
           java.lang.String mimeType,
           byte[] uploadData) {
           this.mimeType = mimeType;
           this.uploadData = uploadData;
           this.mimeAttributes = mimeAttributes;
           this.extensions = extensions;
    }


    /**
     * Gets the mimeType value for this UploadContext.
     * 
     * @return mimeType
     */
    public java.lang.String getMimeType() {
        return mimeType;
    }


    /**
     * Sets the mimeType value for this UploadContext.
     * 
     * @param mimeType
     */
    public void setMimeType(java.lang.String mimeType) {
        this.mimeType = mimeType;
    }


    /**
     * Gets the uploadData value for this UploadContext.
     * 
     * @return uploadData
     */
    public byte[] getUploadData() {
        return uploadData;
    }


    /**
     * Sets the uploadData value for this UploadContext.
     * 
     * @param uploadData
     */
    public void setUploadData(byte[] uploadData) {
        this.uploadData = uploadData;
    }


    /**
     * Gets the mimeAttributes value for this UploadContext.
     * 
     * @return mimeAttributes
     */
    public oasis.names.tc.wsrp.v1.types.NamedString[] getMimeAttributes() {
        return mimeAttributes;
    }


    /**
     * Sets the mimeAttributes value for this UploadContext.
     * 
     * @param mimeAttributes
     */
    public void setMimeAttributes(oasis.names.tc.wsrp.v1.types.NamedString[] mimeAttributes) {
        this.mimeAttributes = mimeAttributes;
    }

    public oasis.names.tc.wsrp.v1.types.NamedString getMimeAttributes(int i) {
        return this.mimeAttributes[i];
    }

    public void setMimeAttributes(int i, oasis.names.tc.wsrp.v1.types.NamedString _value) {
        this.mimeAttributes[i] = _value;
    }


    /**
     * Gets the extensions value for this UploadContext.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this UploadContext.
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
        if (!(obj instanceof UploadContext)) return false;
        UploadContext other = (UploadContext) obj;
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
            ((this.uploadData==null && other.getUploadData()==null) || 
             (this.uploadData!=null &&
              java.util.Arrays.equals(this.uploadData, other.getUploadData()))) &&
            ((this.mimeAttributes==null && other.getMimeAttributes()==null) || 
             (this.mimeAttributes!=null &&
              java.util.Arrays.equals(this.mimeAttributes, other.getMimeAttributes()))) &&
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
        if (getUploadData() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getUploadData());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getUploadData(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getMimeAttributes() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getMimeAttributes());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getMimeAttributes(), i);
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
        new org.apache.axis.description.TypeDesc(UploadContext.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UploadContext"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("mimeType");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "mimeType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("uploadData");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "uploadData"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "base64Binary"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("mimeAttributes");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "mimeAttributes"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "NamedString"));
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
