<%@ Page Title="Lab-01" Language="C#" MasterPageFile="~/Site.Master" Theme="Lab-01" AutoEventWireup="true" CodeBehind="Lab-01.aspx.cs" Inherits="WebClients.LabViews.Lab_01" %>

<asp:Content ID="HeaderContent" ContentPlaceHolderID="HeadContent" runat="server">
    <style>
        /* Основные стили для страницы */
        body {
            font-family: Arial, sans-serif !important;
            background-color: #f4f4f4 !important;
            margin: 0 !important;
            padding: 0 !important;
            color: #333 !important;
        }

        h2 {
            font-size: 24px !important;
            color: #4CAF50 !important;
            margin-bottom: 20px !important;
        }

        /* Стили для таблицы */
        table {
            width: 100% !important;
            border-collapse: collapse !important;
            margin-bottom: 20px !important;
        }

        td {
            padding: 10px !important;
            vertical-align: top !important;
        }

        table td:first-child {
            text-align: right !important;
        }

        /* Кнопки */
        button {
            background-color: #4CAF50 !important;
            color: white !important;
            border: none !important;
            padding: 10px 20px !important;
            text-align: center !important;
            display: inline-block !important;
            font-size: 14px !important;
            cursor: pointer !important;
            transition: background-color 0.3s ease !important;
            border-radius: 4px !important;
        }

        button:hover {
            background-color: #45a049 !important;
        }

        #GETBtn {
            background-color: antiquewhite;
        }

        /* Текстовые поля */
        input[type="text"], input[type="password"], textarea {
            width: 100% !important;
            padding: 8px !important;
            box-sizing: border-box !important;
            border: 1px solid #ccc !important;
            border-radius: 4px !important;
            font-size: 14px !important;
        }

        /* Ошибки */
        .error-label {
            color: red !important;
            font-size: 12px !important;
        }

        /* DELETE Button */
        button.delete {
            background-color: #f44336 !important;
        }

        button.delete:hover {
            background-color: #e53935 !important;
        }
    </style>
</asp:Content>

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
                <asp:Button runat="server" ID="POSTBtn" Text="POST" OnClick="POSTBtn_Click"/>
            </asp:TableCell>
            <asp:TableCell Width="40%">
                <asp:TextBox runat="server" ID="Result" ToolTip="Parameter 'Result'">
                </asp:TextBox>
            </asp:TableCell>
            <asp:TableCell>
                <asp:Label runat="server"
                    ForeColor="Red"
                    ID="customerr1">
                </asp:Label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell>
                <asp:Button runat="server" ID="PUTBtn" Text="PUT" OnClick="PUTBtn_Click"/>
            </asp:TableCell>
            <asp:TableCell>
                <asp:TextBox runat="server" ID="Add" ToolTip="Parameter 'Add'">
                </asp:TextBox>
            </asp:TableCell>
            <asp:TableCell>
                <asp:Label runat="server"
                    ForeColor="Red"
                    ID="customerr2">
                </asp:Label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell ColumnSpan="2">
                <asp:Button runat="server" ID="DELETEBtn" Text="DELETE" OnClick="DELETEBtn_Click"/>
            </asp:TableCell>
            <asp:TableCell></asp:TableCell>
        </asp:TableRow>
    </asp:Table>
</asp:Content>
