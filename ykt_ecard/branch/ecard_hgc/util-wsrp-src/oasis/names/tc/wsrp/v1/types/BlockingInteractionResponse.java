/**
 * BlockingInteractionResponse.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class BlockingInteractionResponse  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.UpdateResponse updateResponse;
    private java.lang.String redirectURL;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public BlockingInteractionResponse() {
    }

    public BlockingInteractionResponse(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           java.lang.String redirectURL,
           oasis.names.tc.wsrp.v1.types.UpdateResponse updateResponse) {
           this.updateResponse = updateResponse;
           this.redirectURL = redirectURL;
           this.extensions = extensions;
    }


    /**
     * Gets the updateResponse value for this BlockingInteractionResponse.
     * 
     * @return updateResponse
     */
    public oasis.names.tc.wsrp.v1.types.UpdateResponse getUpdateResponse() {
        return updateResponse;
    }


    /**
     * Sets the updateResponse value for this BlockingInteractionResponse.
     * 
     * @param updateResponse
     */
    public void setUpdateResponse(oasis.names.tc.wsrp.v1.types.UpdateResponse updateResponse) {
        this.updateResponse = updateResponse;
    }


    /**
     * Gets the redirectURL value for this BlockingInteractionResponse.
     * 
     * @return redirectURL
     */
    public java.lang.String getRedirectURL() {
        return redirectURL;
    }


    /**
     * Sets the redirectURL value for this BlockingInteractionResponse.
     * 
     * @param redirectURL
     */
    public void setRedirectURL(java.lang.String redirectURL) {
        this.redirectURL = redirectURL;
    }


    /**
     * Gets the extensions value for this BlockingInteractionResponse.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this BlockingInteractionResponse.
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
        if (!(obj instanceof BlockingInteractionResponse)) return false;
        BlockingInteractionResponse other = (BlockingInteractionResponse) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.updateResponse==null && other.getUpdateResponse()==null) || 
             (this.updateResponse!=null &&
              this.updateResponse.equals(other.getUpdateResponse()))) &&
            ((this.redirectURL==null && other.getRedirectURL()==null) || 
             (this.redirectURL!=null &&
              this.redirectURL.equals(other.getRedirectURL()))) &&
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
        if (getUpdateResponse() != null) {
            _hashCode += getUpdateResponse().hashCode();
        }
        if (getRedirectURL() != null) {
            _hashCode += getRedirectURL().hashCode();
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
        new org.apache.axis.description.TypeDesc(BlockingInteractionResponse.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "BlockingInteractionResponse"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("updateResponse");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "updateResponse"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UpdateResponse"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("redirectURL");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "redirectURL"));
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
