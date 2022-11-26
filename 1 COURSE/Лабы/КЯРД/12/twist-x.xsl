<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<html> 
<body>
  <h2>Studenti</h2>
  <table border="1">
    <tr bgcolor="#9acd32">
      <th style="text-align:left; color:red">Name</th>
      <th style="text-align:left">Grade</th>
    </tr>
        <xsl:for-each select="NACH/TABLIZA">
      <tr bgcolor="#F5F5F5">
      <td><xsl:value-of select="NAME"/></td>
      <xsl:choose>
            <xsl:when test="OZENKA &gt; 7">
              <td bgcolor="green">
              <xsl:value-of select="OZENKA"/></td>
            </xsl:when>
            <xsl:when test="OZENKA &gt; 4">
              <td bgcolor="white">
              <xsl:value-of select="OZENKA"/></td>
            </xsl:when>
            <xsl:when test="OZENKA &gt; 0 ">
              <td bgcolor="red">
              <xsl:value-of select="OZENKA"/></td>
            </xsl:when>
      </xsl:choose>
    </tr>
    </xsl:for-each>
  </table>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
