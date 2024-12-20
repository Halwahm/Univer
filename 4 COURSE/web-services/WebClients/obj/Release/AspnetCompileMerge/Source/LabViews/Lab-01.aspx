﻿<%@ Page Title="Lab-01" Language="C#" MasterPageFile="~/Site.Master" Theme="Lab-01" AutoEventWireup="true" CodeBehind="Lab-01.aspx.cs" Inherits="WebClients.LabViews.Lab_01" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2><%: Title %>.</h2>
    <asp:Table runat="server" BorderStyle="None" Width="500px">
        <asp:TableRow>
            <asp:TableCell Width="20%">
                <asp:Button runat="server" ID="GETBtn" Text="GET" OnClick="GETBtn_Click" />
            </asp:TableCell>
            <asp:TableCell Width="40%">
                <asp:TextBox runat="server" ID="GetResult" ReadOnly="true" ToolTip="Result">

                </asp:TextBox>
            </asp:TableCell>
            <asp:TableCell></asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell Width="20%">
                <asp:Button runat="server" ID="POSTBtn" Text="POST" OnClick="POSTBtn_Click" />
            </asp:TableCell>
            <asp:TableCell Width="40%">
                <asp:TextBox runat="server" ID="Result" ToolTip="Parameter 'Result'">

                </asp:TextBox>
            </asp:TableCell>
            <asp:TableCell>
                <asp:RegularExpressionValidator runat="server" 
                    ControlToValidate="Result" 
                    ValidationGroup="validators" 
                    Display="Dynamic" 
                    ErrorMessage="Invalid format of number!" 
                    Enabled="true" 
                    ForeColor="Red" 
                    ValidationExpression="^-?\d+$">
                </asp:RegularExpressionValidator>
                <asp:Label runat="server"
                    ForeColor="Red"
                    ID="customerr1">
                </asp:Label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell>
                <asp:Button runat="server" ID="PUTBtn" Text="PUT" OnClick="PUTBtn_Click" />
            </asp:TableCell>
            <asp:TableCell>
                <asp:TextBox runat="server" ID="Add" ToolTip="Parameter 'Add'">

                </asp:TextBox>
            </asp:TableCell>
            <asp:TableCell>
                <asp:RegularExpressionValidator runat="server" 
                    ControlToValidate="Add" 
                    ValidationGroup="validators" 
                    Display="Dynamic" 
                    ErrorMessage="Invalid format of number!" 
                    Enabled="true" 
                    ForeColor="Red" 
                    ValidationExpression="^-?\d+$">
                </asp:RegularExpressionValidator>
                <asp:Label runat="server"
                    ForeColor="Red"
                    ID="customerr2">
                </asp:Label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell ColumnSpan="2">
                <asp:Button runat="server" ID="DELETEBtn" Text="DELETE" OnClick="DELETEBtn_Click" />
            </asp:TableCell>
            <asp:TableCell></asp:TableCell>
        </asp:TableRow>
    </asp:Table>

</asp:Content>
